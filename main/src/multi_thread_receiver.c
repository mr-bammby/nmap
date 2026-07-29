
#define MODULE_DEBUG DEBUG_MULTI_THREAD_RECEIVER
#include "debug.h"
#include "multi_thread_shared.h"
#include <pcap.h>
#include "receiver.h"
#include <stdlib.h>

static int multi_thread_receiver_init(pcap_t **pcap_handle_out, char **local_ip_out, uint32_t *link_header_len_out)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldevs;
    const char *device_name;
    struct bpf_program fp;
    int datalink;
    char filter[100];

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

    snprintf(filter, sizeof(filter), "dst host %s and (tcp or udp or icmp)", *local_ip_out);

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

    return 0;
}

uint8_t multi_thread_receiver_run(const argparse_params_t *params, const multi_thread_command_queue_state_t *last_queued_cmd, scan_result_t *results, uint32_t results_rows, uint32_t results_cols)
{

    size_t count = 0;

    pcap_t *pcap_handle = NULL;
    int sock = -1;
    char *local_ip;
    uint32_t link_header_len;
    argparse_port_set_iterator_t port_it;
    unsigned int port_i;



    // Initialize receiver handle
    if (multi_thread_receiver_init(&pcap_handle, &local_ip, &link_header_len) < 0)
    {
        LOGE("Failed to initialize receiver\n");
        return -1;
    }
    LOGI("Receiver handle successfully inititalized\n");

    // Move head/tail of queue to let sender threads start sending
    th_queue_t *cmd_queue = &multi_thread_shared_cmd_queue;
    th_queue_access_t access;
    th_queue_init_access(&access, cmd_queue, TH_LOCK_PRIORITY_HIGH);
    multi_thread_command_t data;
    th_queue_read(&access, &data, NULL);

    // Set Receiver timeout
    //while (1)
        // Start receiving
        // if receiver timeout reached
            // Q write suppressed part XXXXXXXXXX
        // if packet reveived
            // if udp
                // set udp flag in flagging array
            // write result
        // if cmd DONE sent
            // if #threads == 0
                // exit while

    //
    // if (pcap_handle != NULL)
    // {
    //     pcap_close(pcap_handle);
    //     pcap_handle = NULL;
    //     LOGI("Receiver handle successfully destroyed\n");
    // }
}