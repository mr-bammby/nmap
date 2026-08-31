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

int get_link_header_len(int datalink)
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
char* get_local_ip(const char *iface_name)
{
    struct ifaddrs *ifaddr, *ifa;

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
                char *ip_addr = malloc(INET_ADDRSTRLEN);
                if (ip_addr == NULL)
                {
                    freeifaddrs(ifaddr);
                    return NULL;
                }
                if (inet_ntop(AF_INET, &sa->sin_addr, ip_addr, INET_ADDRSTRLEN) == NULL)
                {
                    free(ip_addr);
                    freeifaddrs(ifaddr);
                    return NULL;
                }
                freeifaddrs(ifaddr);
                return ip_addr;
            }
        }
    }
    freeifaddrs(ifaddr);
    return NULL;
}

#include <pcap.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int receiver_init(const char *target_ip, 
                  const argparse_port_set_iterator_t *port_it, 
                  pcap_t **pcap_handle_out, 
                  char **local_ip_out, 
                  uint32_t *link_header_len_out)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldevs = NULL;
    const char *device_name;
    struct bpf_program fp;
    int datalink;
    int link_len;
    char filter[100];

    (void)port_it; /* Unused iterator parameter */

    if (pcap_findalldevs(&alldevs, errbuf) == -1 || alldevs == NULL)
    {
        LOGE("Failed to find network devices: %s\n", errbuf);
        return -1;
    }

    device_name = alldevs->name;
    LOGD("Using device: %s\n", device_name);

    /* Get the IP for this specific device */
    *local_ip_out = get_local_ip(device_name);
    if (!*local_ip_out)
    {
        LOGE("Could not find IP for %s\n", device_name);
        pcap_freealldevs(alldevs);
        return -1;
    }
    LOGD("Using Local IP: %s\n", *local_ip_out);

    /* 1. Create capture handle (unactivated state) */
    *pcap_handle_out = pcap_create(device_name, errbuf);
    pcap_freealldevs(alldevs); /* Free early once device name string is copied/used */

    if (*pcap_handle_out == NULL)
    {
        LOGE("Failed to create pcap handle: %s\n", errbuf);
        free(*local_ip_out);
        *local_ip_out = NULL;
        return -1;
    }

    /* 2. Configure handle options BEFORE activation */
    if (pcap_set_snaplen(*pcap_handle_out, BUFSIZ) != 0 ||
        pcap_set_promisc(*pcap_handle_out, 1) != 0 ||
        pcap_set_timeout(*pcap_handle_out, 10) != 0 ||
        pcap_set_buffer_size(*pcap_handle_out, 67108864) != 0 || /* 64 MB buffer */
        pcap_set_immediate_mode(*pcap_handle_out, 1) != 0)
    {
        LOGE("Failed to set pcap options\n");
        receiver_cleanup(*pcap_handle_out);
        *pcap_handle_out = NULL;
        return -1;
    }

    /* 3. Activate capture handle */
    if (pcap_activate(*pcap_handle_out) != 0)
    {
        LOGE("Failed to activate pcap handle: %s\n", pcap_geterr(*pcap_handle_out));
        receiver_cleanup(*pcap_handle_out);
        *pcap_handle_out = NULL;
        return -1;
    }

    /* 4. Datalink validation (Check signed int before casting to uint32_t) */
    datalink = pcap_datalink(*pcap_handle_out);
    link_len = get_link_header_len(datalink);
    if (link_len < 0)
    {
        LOGE("Unsupported datalink type: %d\n", datalink);
        receiver_cleanup(*pcap_handle_out);
        *pcap_handle_out = NULL;
        return -1;
    }
    *link_header_len_out = (uint32_t)link_len;

    /* 5. Set non-blocking mode AFTER activation */
    if (pcap_setnonblock(*pcap_handle_out, 1, errbuf) != 0)
    {
        LOGE("Failed to set non-blocking mode: %s\n", errbuf);
        receiver_cleanup(*pcap_handle_out);
        *pcap_handle_out = NULL;
        return -1;
    }

    /* 6. Compile and apply BPF filter */
    snprintf(filter, sizeof(filter), "src host %s and (tcp or udp or icmp)", target_ip);
    if (pcap_compile(*pcap_handle_out, &fp, filter, 1, PCAP_NETMASK_UNKNOWN) != 0)
    {
        LOGE("Failed to compile BPF filter: %s\n", pcap_geterr(*pcap_handle_out));
        receiver_cleanup(*pcap_handle_out);
        *pcap_handle_out = NULL;
        return -1;
    }

    if (pcap_setfilter(*pcap_handle_out, &fp) != 0)
    {
        LOGE("Failed to set BPF filter: %s\n", pcap_geterr(*pcap_handle_out));
        pcap_freecode(&fp);
        receiver_cleanup(*pcap_handle_out);
        *pcap_handle_out = NULL;
        return -1;
    }
    pcap_freecode(&fp);

    return 0;
}

int receiver_cleanup(pcap_t *pcap_handle)
{
    if (pcap_handle != NULL)
    {
        LOGD("Pcap clean up\n");
        pcap_close(pcap_handle);
        pcap_handle = NULL;
    }
    return 0;
}

int receiver_run(pcap_t *pcap_handle, uint32_t link_header_len, response_type_t *response_slot, scan_result_t *results, argparse_port_set_t *ports)
{
    struct pcap_pkthdr *header;
    const unsigned char *packet;
    int res = pcap_next_ex(pcap_handle, &header, &packet);
    if (res == 1)
    {
        LOGD("PACKET PROCESSING\n");
        if (process_packet(packet, header->caplen, link_header_len, results, ports) == 1)
        {
            return 1;
        }
    }
    
    return 0; 
}