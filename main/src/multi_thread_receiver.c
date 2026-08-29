
#define MODULE_DEBUG DEBUG_MULTI_THREAD_RECEIVER
#include "debug.h"
#include "multi_thread_shared_res.h"
#include <pcap.h>
#include "receiver.h"
#include <stdlib.h>
#include <unistd.h>
#include <packet_handler.h>
#include "timer_utils.h"
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
                       ")");

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

static argparse_addr_node_t *get_addr_node_by_idx(argparse_addr_node_t *address_list, uint16_t address_idx)
{
    argparse_addr_node_t *address_ptr = address_list;

    for (uint16_t counter = 0; counter < address_idx; counter++)
    {
        if (address_ptr == NULL)
            return NULL;

        address_ptr = address_ptr->next;
    }

    return address_ptr;
}

static void multi_thread_receiver_run_append_queue(th_queue_access_t *access, const argparse_params_t *params, const multi_thread_command_queue_state_t *queue_state, scan_result_t **results, uint64_t *sent_scan_count)
{
    static uint8_t init_flag = 0;
    static nmap_timeout_t timeout;
    static argparse_addr_node_t *current_addr = NULL;
    static uint16_t current_addr_idx = 0;

    static unsigned int current_port = 0;
    static argparse_port_set_iterator_t port_it = {0};

    static uint8_t current_scan = 0 ;
    static uint8_t end_added_successfully = 0;

    static uint8_t queue_full = 0;


    if (!access->queue->is_full)
        queue_full = 0;

    if (!init_flag)
    {
        timeout_start(&timeout, 3000);
        current_addr = get_addr_node_by_idx(params->address, queue_state->address_idx);
        current_addr_idx = queue_state->address_idx;

        current_port = queue_state->port_idx;
        argparse_port_iterator_init(&port_it, &(params->ports));
        current_scan = queue_state->scan_idx;

        if (queue_state->address_idx == 0 && queue_state->port_idx == 0 && queue_state->scan_idx == MULTI_TH_SP_CMD_END)
            end_added_successfully = 1;

        LOGD("Copied queue states: add %s, port idx %d and scan idx%d\n", current_addr->addr, current_port, current_scan);

        init_flag = 1;
    }

    sent_scan_count =  0;

    if (timeout_check(&timeout) && !end_added_successfully)
    {
        while (current_addr != NULL && !end_added_successfully)
        {
            LOGD("Adding %s...\n", current_addr->addr);
            //LOGD("Size of set %d and current port %d \n", port_it.set->count, current_port );
            argparse_port_iterator_set_index(&port_it, current_port);
            unsigned int port_value;

            while (argparse_port_iterator_next(&port_it, &port_value) == 0)
            {
                if (atomic_load(&interrupt_flag))
                {
                    atomic_store(&abort_flag, true);
                    LOGE("Abort flag set, exiting receiver\n");
                    return; //implement graceful termination
                }
                //LOGD("Port iterator loop with port idx%d\n", port_it.index);
                for (; current_scan < 6; current_scan++)
                {
                    //LOGD("Scan index loop with scan_i %d\n", current_scan);
                    if (!(params->scans & (1 << current_scan)))
                        continue;
                    //LOGD("Receiver adding scan for address %s, port %d and scan id %d\n", current_addr->addr, port_value, current_scan); 
                    uint8_t result = append_scan_receiver_run(current_addr->addr,  current_addr_idx, (uint16_t)port_value, (uint16_t)port_it.index - 1, (uint8_t)(1u << current_scan), access);//const char *address_str, uint16_t flag_row_idx, uint16_t port, uint16_t flag_arr_idx, uint8_t scan_flag, th_queue_access_t *access)
                    scan_result_t *row = results[current_addr_idx];
                    if (result == 0)
                    {
                        LOGD("Successfully appended address %s, port %d and scan id %d to command queue\n", current_addr->addr, port_value, current_scan);
                    }
                    else if (result == MULTI_TH_QUEUE_APPEND_OK_FULL_AFTER)
                    {
                        LOGE("Queue is full while receiver is adding scan command for address %s, port %d and scan id %d\n", current_addr->addr, port_value, current_scan);
                        queue_full = 1;
                        timeout_start(&timeout, 3000);
                        break;
                    }
                    else
                    {
                        LOGD("Error while appending command in receiver thread\n");
                        atomic_store(&abort_flag, true);
                        return; //implement graceful termination
                    }
                    if (argparse_port_find(&params->ports, port_value, &current_port) == 0 && current_port >= 0)
                    {
                        sent_scan_count++;
                        switch (1u << current_scan)
                        {
                            case SCAN_FLG_SYN:  row[current_port].response_syn  = RESPONSE_NO_RESPONSE; break;
                            case SCAN_FLG_NULL: row[current_port].response_null = RESPONSE_NO_RESPONSE; break;
                            case SCAN_FLG_ACK:  row[current_port].response_ack  = RESPONSE_NO_RESPONSE; break;
                            case SCAN_FLG_FIN:  row[current_port].response_fin  = RESPONSE_NO_RESPONSE; break;
                            case SCAN_FLG_XMAS: row[current_port].response_xmas = RESPONSE_NO_RESPONSE; break;
                            case SCAN_FLG_UDP:  row[current_port].response_udp  = RESPONSE_NO_RESPONSE; break;
                            default: break;
                        }
                    }
                }
                current_scan++;
                if (current_scan >= 6)
                {
                    current_port++;
                    current_scan = 0;
                }
                if (port_it.set->count >= current_port)
                    current_port = 0;
                if (queue_full)
                    break;
                
            }
            if (queue_full)
                break;
            current_addr = current_addr->next;
            current_addr_idx++;
            current_port = 0;
            current_scan = 0;
            LOGD("Queue state indexes for address %s, port %d and scan %d\n", current_addr->addr, current_port, current_scan);     
        }

        if (current_addr == NULL)
        {
            uint8_t result = append_special_receiver_run(MULTI_TH_SP_CMD_END, access); // Add an end command to signal completion
            if (result == 1)
            {
                LOGE("Failed to add end command to queue in receiver run\n");
                //return 1; // Error, terminate gracefully
            }
            else if (result == 2)
            {
                LOGE("Queue is full while adding end command in receiver run\n");
                timeout_start(&timeout, 1000);
            }
            else
            {
                end_added_successfully = 1;
                timeout_stop(&timeout);
                LOGD("All commands added to queue successfully.\n");
            }
        }
    }
    return;
}

uint8_t multi_thread_receiver_run(pcap_t *pcap_handle, uint32_t link_header_len, scan_result_t **results, const addr_hashmap_t *hash_map, th_queue_access_t *access, const argparse_params_t *params, const multi_thread_command_queue_state_t *queue_state, uint32_t results_rows, uint32_t results_cols)
{
    struct pcap_pkthdr *header;
    const unsigned char *packet;
    int8_t ret = 0;
    uint64_t sent_count, all_sent_scan_count = queue_state->sent_scan_cnt;
    uint64_t received_count = 0;
    
    LOGD("Sender threads1 num %d\n", atomic_load(&thread_counter));
    while (atomic_load(&thread_counter) > 0)
    {
        //Append of command queue
        /*multi_thread_receiver_run_append_queue(access, params, queue_state, results, &sent_count);
        all_sent_scan_count += sent_count;

        //LOGD("Receiver sniffing\n");
        if (atomic_load(&interrupt_flag))
        {
            atomic_store(&abort_flag, true);
            LOGE("Abort flag set, exiting receiver\n");
            ret = -1;
            break;
        }
        int res = pcap_next_ex(pcap_handle, &header, &packet);
        if (atomic_load(&interrupt_flag) || atomic_load(&abort_flag))
        {
            atomic_store(&abort_flag, true);
            LOGE("Abort flag set, exiting receiver\n");
            ret = -1;
            break;
        }*/
       int res = pcap_next_ex(pcap_handle, &header, &packet);
        if (res == 1)
        {
            LOGD("PACKET PROCESSING\n");
            LOGD("Header len: %d\n", header->len);
            if (multi_thread_process_packet(packet, header->caplen, link_header_len, results, hash_map, &(params->ports)) == 1)
            {
                received_count++;
            }

        }
    }
    LOGD("Sender threads3 num %d\n", atomic_load(&thread_counter));
    if (received_count < all_sent_scan_count)
    {
        LOGD("Receiver finished but not all sent scans were received. Sent: %llu, Received: %llu\n", (unsigned long long)all_sent_scan_count, (unsigned long long)received_count);
        uint16_t cnt = 0;
        // Wait for return packet for 1s
        while (cnt < 1000)
        {
            if (atomic_load(&interrupt_flag) || atomic_load(&abort_flag) || ret == -1)
            {
                atomic_store(&abort_flag, true);
                LOGE("Abort flag set, exiting receiver\n");
                ret = -1;
                break;
            }
            int res = pcap_next_ex(pcap_handle, &header, &packet);
            if (atomic_load(&interrupt_flag) || atomic_load(&abort_flag))
            {
                atomic_store(&abort_flag, true);
                LOGE("Abort flag set, exiting receiver\n");
                ret = -1;
                break;
            }
            if (res == 1)
            {
                LOGD("PACKET PROCESSING\n");
                LOGD("Header len: %d\n", header->len);
                if (multi_thread_process_packet(packet, header->caplen, link_header_len, results, hash_map, &(params->ports)) == 1)
                {
                    received_count++;
                }

            }
            usleep(1000);
            cnt++;
        }
    }

    if (ret < 0)
    {
        uint16_t cnt = 0;
        atomic_store(&abort_flag, true);
        while (atomic_load(&thread_counter) > 0)
        {
            LOGD("Waiting for sender threads to finish...\n");
            usleep(100);
            if (cnt > 1000)
            {
                LOGE("Timeout waiting for sender threads to finish, forcing exit\n");
                break;
            }
            cnt++;
        }
    }
    return ret;
}