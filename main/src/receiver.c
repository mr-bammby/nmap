#define MODULE_DEBUG DEBUG_RECEIVER
#include "debug.h"
#include <pcap.h>

#include <ifaddrs.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "receiver.h"
#include "packet_handler.h"

static int get_link_header_len(int datalink)
{
    switch (datalink)
    {
    case DLT_EN10MB:
        return 14;
    case DLT_NULL:
        return 4;
    case DLT_RAW:
        return 0;
#ifdef DLT_LINUX_SLL
    case DLT_LINUX_SLL:
        return 16;
#endif
#ifdef DLT_LINUX_SLL2
    case DLT_LINUX_SLL2:
        return 20;
#endif
    default:
        return -1;
    }
}

// --- Helper: Get Local IP for Checksum ---
static char* get_local_ip(const char *iface_name)
{
    struct ifaddrs *ifaddr, *ifa;
    static char ip_addr[INET_ADDRSTRLEN];

    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
        return NULL;
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr == NULL) continue;
        if (ifa->ifa_addr->sa_family == AF_INET)
        {
            if (strcmp(ifa->ifa_name, iface_name) == 0)
            {
                struct sockaddr_in *sa = (struct sockaddr_in *)ifa->ifa_addr;
                strcpy(ip_addr, inet_ntoa(sa->sin_addr));
                freeifaddrs(ifaddr);
                return ip_addr;
            }
        }
    }
    freeifaddrs(ifaddr);
    return NULL;
}

int receiver_init(const char *target_ip, uint8_t scans, const argparse_port_set_iterator_t *port_it, pcap_t **pcap_handle_out, char **local_ip_out, uint32_t *link_header_len_out)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldevs;
    const char *device_name;
    struct bpf_program fp;
    int datalink;
    char filter[100];

    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        receiver_cleanup(*pcap_handle_out);
        return -1;
    }
    if (alldevs == NULL)
    {
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

    pcap_setnonblock(*pcap_handle_out, 1, errbuf);

    sprintf(filter, "src host %s", target_ip);
    pcap_compile(*pcap_handle_out, &fp, filter, 0, PCAP_NETMASK_UNKNOWN);
    pcap_setfilter(*pcap_handle_out, &fp);

    return 0;
}

int receiver_cleanup(pcap_t *pcap_handle)
{
    if (pcap_handle != NULL)
    {
        pcap_close(pcap_handle);
        pcap_handle = NULL;
    }
    return 0;
}

int receiver_run(pcap_t *pcap_handle, uint32_t link_header_len, response_type_t *response_slot, scan_result_t *results)
{
    struct pcap_pkthdr *header;
    const unsigned char *packet;
    int res = pcap_next_ex(pcap_handle, &header, &packet);
    if (res == 1)
    {
        LOGD("PACKET PROCESSING\n");
        process_packet(packet, header->caplen, link_header_len, results);
        /* Only stop when this specific probe got a conclusive response. */
        if (*response_slot != RESPONSE_NO_RESPONSE)
            return 1; // Stop receiving for this probe
    }
    
    return 0; // Continue receiving
}