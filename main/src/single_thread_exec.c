#include <pcap.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "nmap_types.h"
#include "scan_context.h"
#include "port_utils.h"
#include "port_map.h"
#include "packet_handler.h"

scan_result_t results[RESULTS_CAPACITY];

#define NUMBER_OF_SCAN_TYPES 6
#define RESPONSE_WAIT_ATTEMPTS 500
#define RESPONSE_POLL_SLEEP_US 1000

static const char *const known_scan_types[6] =
    {
        "SYN",
        "NULL",
        "ACK",
        "FIN",
        "XMAS",
        "UDP"
    };

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
char* get_local_ip(const char *iface_name)
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




// --- Initialize Results Array ---
void initialize_results(scan_result_t *results, int size)
{
    for (int i = 0; i < size; i++)
    {
        results[i].port = i + 1;
        results[i].protocol = 0;
        results[i].response_syn = RESPONSE_NOT_EXPECTED;
        results[i].response_null = RESPONSE_NOT_EXPECTED;
        results[i].response_ack = RESPONSE_NOT_EXPECTED;
        results[i].response_fin = RESPONSE_NOT_EXPECTED;
        results[i].response_xmas = RESPONSE_NOT_EXPECTED;
        results[i].response_udp = RESPONSE_NOT_EXPECTED;
    }
}

static const char *state_label_syn(response_type_t response)
{
    if (response == RESPONSE_SYN_ACK)
        return "OPEN";
    if (response == RESPONSE_RST)
        return "CLOSED";
    if (response == RESPONSE_NO_RESPONSE || response == RESPONSE_ICMP_UNREACHABLE)
        return "FILTERED";
    return "UNKNOWN";
}

static const char *state_label_ack(response_type_t response)
{
    if (response == RESPONSE_RST)
        return "UNFILTERED";
    if (response == RESPONSE_NO_RESPONSE || response == RESPONSE_ICMP_UNREACHABLE)
        return "FILTERED";
    return "UNKNOWN";
}

static const char *state_label_null_fin_xmas(response_type_t response)
{
    if (response == RESPONSE_RST)
        return "CLOSED";
    if (response == RESPONSE_NO_RESPONSE)
        return "OPEN|FILTERED";
    if (response == RESPONSE_ICMP_UNREACHABLE)
        return "FILTERED";
    return "UNKNOWN";
}

static const char *state_label_udp(response_type_t response)
{
    if (response == RESPONSE_UDP_REPLY)
        return "OPEN";
    if (response == RESPONSE_ICMP_UNREACHABLE)
        return "CLOSED";
    if (response == RESPONSE_ICMP_FILTERED)
        return "FILTERED";
    if (response == RESPONSE_NO_RESPONSE)
        return "OPEN|FILTERED";
    return "UNKNOWN";
}

static void print_scan_block(const char *title,
                             scan_result_t *results,
                             int start,
                             int end,
                             response_type_t (*get_response)(const scan_result_t *),
                             const char *(*state_label)(response_type_t))
{
    int i;
    printf("\n***** %s *****\n", title);
    printf("\n%-6s | %-14s | %s\n", "PORT", "STATE", "SERVICE");
    printf("-------|----------------|----------------\n");

    for (i = start; i < end; i++)
    {
        response_type_t response = get_response(&results[i]);
        if (response != RESPONSE_NOT_EXPECTED)
            printf("%-6d | %-14s | %s\n", results[i].port, state_label(response), GET_SERVICE_NAME(results[i].port));
    }
}

static response_type_t get_syn_response(const scan_result_t *result)
{
    return result->response_syn;
}

static response_type_t get_ack_response(const scan_result_t *result)
{
    return result->response_ack;
}

static response_type_t get_null_response(const scan_result_t *result)
{
    return result->response_null;
}

static response_type_t get_fin_response(const scan_result_t *result)
{
    return result->response_fin;
}

static response_type_t get_xmas_response(const scan_result_t *result)
{
    return result->response_xmas;
}

static response_type_t get_udp_response(const scan_result_t *result)
{
    return result->response_udp;
}

static response_type_t *response_slot_for_scan(scan_result_t *result, uint8_t scan_flag)
{
    if (scan_flag == SCAN_FLG_SYN)
        return &result->response_syn;
    if (scan_flag == SCAN_FLG_ACK)
        return &result->response_ack;
    if (scan_flag == SCAN_FLG_NULL)
        return &result->response_null;
    if (scan_flag == SCAN_FLG_FIN)
        return &result->response_fin;
    if (scan_flag == SCAN_FLG_XMAS)
        return &result->response_xmas;
    if (scan_flag == SCAN_FLG_UDP)
        return &result->response_udp;
    return NULL;
}

// --- Print Results ---
void print_results(scan_result_t *results, int start, int end)
{
    print_scan_block("SYN", results, start, end, get_syn_response, state_label_syn);
    print_scan_block("ACK", results, start, end, get_ack_response, state_label_ack);
    print_scan_block("NULL", results, start, end, get_null_response, state_label_null_fin_xmas);
    print_scan_block("FIN", results, start, end, get_fin_response, state_label_null_fin_xmas);
    print_scan_block("XMAS", results, start, end, get_xmas_response, state_label_null_fin_xmas);
    print_scan_block("UDP", results, start, end, get_udp_response, state_label_udp);
    print_scan_block("FINAL", results, start, end, final_result_logic, state_label_final);
}

int single_thread_exec(const char *target_ip, port_set_t ports, scan_bitmap_t scans)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    struct bpf_program fp;
    int sock;
    pcap_if_t *alldevs;
    char *device_name;
    char *local_ip;
    uint32_t link_header_len = 14;
    
    port_set_iterator_t port_it;
    init_port_iterator(&port_it, &ports);

    // Initialize results array
    initialize_results(results, PORT_END + 1);

    sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (sock < 0)
    {
        perror("Socket error"); return 1;
    }
    int one = 1;
    const int *val = &one;
    if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, val, sizeof(one)) < 0) {
        perror("Error setting IP_HDRINCL");
        exit(1);
    }

    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        return 1;
    }
    if (alldevs == NULL) return 1;
    device_name = alldevs->name;
    printf("Using device: %s\n", device_name);

    // Get the IP for this specific device
    local_ip = get_local_ip(device_name);
    if (!local_ip)
    {
        fprintf(stderr, "Could not find IP for %s\n", device_name);
        return 1;
    }
    printf("Using Local IP: %s\n", local_ip);

    handle = pcap_open_live(device_name, BUFSIZ, 1, 10, errbuf);
    if (handle == NULL)
    {
        return 1;
    }

    int datalink = pcap_datalink(handle);
    link_header_len = (uint32_t)get_link_header_len(datalink);
    if (link_header_len < 0)
    {
        fprintf(stderr, "Unsupported datalink type: %d\n", datalink);
        pcap_close(handle);
        close(sock);
        return 1;
    }

    pcap_setnonblock(handle, 1, errbuf);

    char filter[100];
    sprintf(filter, "src host %s", target_ip);
    pcap_compile(handle, &fp, filter, 0, PCAP_NETMASK_UNKNOWN);
    pcap_setfilter(handle, &fp);

    unsigned int port_i;
    while (port_iterator_next(&port_it, &port_i) == 0)
    {
        for (int scan_i = 0; scan_i < NUMBER_OF_SCAN_TYPES; scan_i++)
        {
            if (scans & (1 << scan_i))
            {
                uint8_t scan_flag = (uint8_t)(1u << scan_i);
                response_type_t *response_slot;
                printf("Scanning port %d with scan type %s...\n", port_i, known_scan_types[scan_i]);
                fflush(stdout);
                send_packet(sock, target_ip, port_i, local_ip, scan_flag, 0);
                response_slot = response_slot_for_scan(&results[port_i - 1], scan_flag);
                if (response_slot == NULL)
                {
                    printf("Done for port %d.\n", port_i);
                    continue;
                }

                *response_slot = RESPONSE_NO_RESPONSE;

                int max_attempts = RESPONSE_WAIT_ATTEMPTS;
                if (scan_flag == SCAN_FLG_UDP)
                    max_attempts = RESPONSE_WAIT_ATTEMPTS * UDP_TOTAL_PROBES;

                for (int attempt = 0; attempt < max_attempts; attempt++)
                {
                    if (scan_flag == SCAN_FLG_UDP &&
                        attempt > 0 &&
                        (attempt % RESPONSE_WAIT_ATTEMPTS) == 0 &&
                        *response_slot == RESPONSE_NO_RESPONSE)
                    {
                        uint8_t udp_probe_variant = (uint8_t)(attempt / RESPONSE_WAIT_ATTEMPTS);
                        send_packet(sock, target_ip, port_i, local_ip, scan_flag, udp_probe_variant);
                    }

                    // Wait in 1ms polls; UDP may span multiple windows via retries.
                    struct pcap_pkthdr *header;
                    const unsigned char *packet;
                    int res = pcap_next_ex(handle, &header, &packet);
                    if (res == 1)
                    {
                        printf("PACKET PROCESSING\n");
                        process_packet(packet, header->caplen, link_header_len);
                        /* Only stop when this specific probe got a conclusive response. */
                        if (*response_slot != RESPONSE_NO_RESPONSE)
                            break;
                    }
                    usleep(RESPONSE_POLL_SLEEP_US);
                }
                printf("Done for port %d.\n", port_i);
            }
        }
    }
    print_results(results, 0, NUMBER_OF_PORTS);
    pcap_close(handle);
    close(sock);
    return 0;
}