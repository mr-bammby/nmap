
#define MODULE_DEBUG DEBUG_MULTI_THREAD_RECEIVER
#include "debug.h"
#include "multi_thread_shared.h"
#include <pcap.h>
#include "receiver.h"
#include <stdlib.h>
#include <unistd.h>
#include <packet_handler.h>
#include "exec.h"

static int build_bpf_filter(const argparse_addr_node_t *addresses, const char *local_ip, char *filter, size_t filter_size){
    const argparse_addr_node_t *node = addresses;
    size_t used = 0;
    int written;

    if (filter == NULL || filter_size == 0)
        return -1;

    /* Start filter */
    written = snprintf(filter, filter_size, "(");
    if (written < 0 || (size_t)written >= filter_size)
        return -1;

    used = (size_t)written;

    while (node != NULL)
    {
        written = snprintf(filter + used,
                           filter_size - used,
                           "%ssrc host %s",
                           (node == addresses) ? "" : " or ",
                           node->addr);

        if (written < 0 || (size_t)written >= (filter_size - used))
            return -1;

        used += (size_t)written;
        node = node->next;
    }

    written = snprintf(filter + used,
                       filter_size - used,
                       ") and dst host %s and (tcp or udp or icmp)",
                       local_ip);

    if (written < 0 || (size_t)written >= (filter_size - used))
        return -1;

    return 0;
}

int multi_thread_receiver_init(const argparse_addr_node_t *addresses, pcap_t **pcap_handle_out, char **local_ip_out, uint32_t *link_header_len_out)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldevs;
    const char *device_name;
    struct bpf_program fp;
    int datalink;
    char filter[4096];

    if (pcap_findalldevs(&alldevs, errbuf) < 0)
    {
        LOGE("pcap_findalldevs failed: %s\n", errbuf);
        receiver_cleanup(*pcap_handle_out);
        return -1;
    }
    if (alldevs == NULL)
    {
        LOGE("No potential packet capture devices found");
        receiver_cleanup(*pcap_handle_out);
        return -1;
    }
    device_name = alldevs->name;
    LOGD("Using device: %s\n", device_name);

    // Get the IP for this specific device
    *local_ip_out = get_local_ip(device_name);
    if (!*local_ip_out)
    {
        LOGE("Could not find IP for %s\n", device_name);
        receiver_cleanup(*pcap_handle_out);
        return -1;
    }
    LOGD("Using Local IP: %s\n", *local_ip_out);

    *pcap_handle_out = pcap_open_live(device_name, BUFSIZ, 1, 10, errbuf);
    if (*pcap_handle_out == NULL)
    {
        LOGE("Failed to open handle: %s\n", errbuf);
        return -1;
    }
    pcap_freealldevs(alldevs);
    datalink = pcap_datalink(*pcap_handle_out);
    *link_header_len_out = (uint32_t)get_link_header_len(datalink);
    if (*link_header_len_out < 0)
    {
        LOGE("Unsupported datalink type: %d\n", datalink);
        receiver_cleanup(*pcap_handle_out);
        return -1;
    }

    //pcap_setnonblock(*pcap_handle_out, 1, errbuf);
    if (pcap_setnonblock(*pcap_handle_out, 1, errbuf) < 0)
    {
        LOGE("Failed to set non-blocking mode: %s\n", errbuf);
        receiver_cleanup(*pcap_handle_out);
        return -1;
    }

    if (build_bpf_filter(addresses,
                        *local_ip_out,
                        filter,
                        sizeof(filter)) < 0)
    {
        LOGE("Failed to build BPF filter\n");
        receiver_cleanup(*pcap_handle_out);
        return -1;
    }

    LOGD("BPF Filter: %s\n", filter);

    if (pcap_compile(*pcap_handle_out, &fp, filter, 1, PCAP_NETMASK_UNKNOWN) < 0)
    {
        LOGE("pcap_compile failed: %s\n", pcap_geterr(*pcap_handle_out));
        receiver_cleanup(*pcap_handle_out);
        return -1;
    }

    if (pcap_setfilter(*pcap_handle_out, &fp) < 0)
    {
        LOGE("pcap_setfilter failed: %s\n", pcap_geterr(*pcap_handle_out));
        pcap_freecode(&fp);
        receiver_cleanup(*pcap_handle_out);
        return -1;
    }
    pcap_freecode(&fp);
    return 0;
}

uint8_t multi_thread_receiver_run(pcap_t *pcap_handle, uint32_t link_header_len, scan_result_t **results, addr_hashmap_t *hash_map, const argparse_port_set_t *ports)
{

    // Set Receiver timeout
    // while
        // Start receiving
        // if receiver timeout reached
            // Q write suppressed part XXXXXXXXXX
        // if packet reveived
            // if udp
                // set udp flag in flagging array
            // write result
        // if #threads == 0
            // exit while
    uint8_t ret = 0;
    struct pcap_pkthdr *header;
    const unsigned char *packet;
    while (atomic_load(&thread_counter) > 0)
    {
        //LOGD("Receiver sniffing\n");
        if (atomic_load(&interrupt_flag))
        {
            atomic_store(&abort_flag, true);
            LOGE("Abort flag set, exiting receiver\n");
            ret = 1;
            break;
        }
        int res = pcap_next_ex(pcap_handle, &header, &packet);
        if (res == 1)
        {
            LOGD("PACKET PROCESSING\n");
            LOGD("Header len: %d\n", header->len);
            multi_thread_process_packet(packet, header->caplen, link_header_len, results, hash_map, ports);

        }
    }
    if (ret == 1)
    {
        uint8_t cnt = 0;
        while (atomic_load(&thread_counter) > 0)
        {
            LOGD("Waiting for sender threads to finish...\n");
            sleep(1);
            if (cnt > 10)
            {
                LOGE("Timeout waiting for sender threads to finish, forcing exit\n");
                break;
            }
            cnt++;
        }
    }
    return ret;
}