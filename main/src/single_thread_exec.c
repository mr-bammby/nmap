#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "nmap_types.h"
#include "ip.h"
#include "tcp.h"
#include "exec.h"
#include "icmp.h"
#include "udp.h"
#include "scan_context.h"
#include "port_utils.h"

scan_result_t results[RESULTS_CAPACITY];
uint32_t g_link_header_len = 14;

#define NUMBER_OF_SCAN_TYPES 6
#define RESPONSE_WAIT_ATTEMPTS 500
#define RESPONSE_POLL_SLEEP_US 1000
#define UDP_TOTAL_PROBES 3

#define COOKIE_MAKE(scan_id, port) \
    ((COOKIE_MAGIC << 16) | (((uint32_t)(scan_id) & 0x7) << 13) | ((port) & 0x1FFF))

static const char *const valid_tokens[6] =
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


// --- Sender Logic ---
void send_packet(int sockfd, const char *target_ip, int port, const char *local_ip, uint8_t scan_type)
{
    uint8_t packet[128];
    ip_header_t ip_header;
    tcp_header_t tcp_header;
    udp_header_t udp_header;
    int16_t packet_len;

    struct sockaddr_in sin;

    memset(packet, 0, 128);
    ip_header.id = htons(rand() % 65536);
    ip_header.src = inet_addr(local_ip);
    ip_header.dst = inet_addr(target_ip);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = inet_addr(target_ip);

    uint32_t payload[1] = {0xb4050402}; // Example payload for SYN+ACK response
    uint8_t scan_id = 0;
    uint8_t scan_type_tmp = scan_type;
    uint32_t cookie;

    while ((scan_type_tmp & 1u) == 0u && scan_id < 7)
    {
        scan_type_tmp >>= 1;
        scan_id++;
    }
    cookie = COOKIE_MAKE(scan_id, port);
    switch (scan_type)
    {
        case SCAN_FLG_SYN:
            ip_header.protocol = IPPROTO_TCP;
            tcp_header.flags = TCP_FLAG_SYN;
            break;
        case SCAN_FLG_ACK:
            ip_header.protocol = IPPROTO_TCP;
            tcp_header.flags = TCP_FLAG_ACK;
            break;
        case SCAN_FLG_NULL:
            ip_header.protocol = IPPROTO_TCP;
            tcp_header.flags = 0;
            break;
        case SCAN_FLG_FIN:
            ip_header.protocol = IPPROTO_TCP;
            tcp_header.flags = TCP_FLAG_FIN;
            break;
        case SCAN_FLG_XMAS:
            ip_header.protocol = IPPROTO_TCP;
            tcp_header.flags = TCP_FLAG_FIN | TCP_FLAG_PSH | TCP_FLAG_URG;
            break;
        case SCAN_FLG_UDP:
            ip_header.protocol = IPPROTO_UDP;
            break;
        default:
            perror("Unsupported scan type");
            return;
            break;
    }
    if (ip_header.protocol == IPPROTO_UDP)
    {
        udp_header.src_port = rand() % 65536;
        udp_header.dst_port = port;
        udp_header.length = UDP_HEADER_SIZE + sizeof(payload);
        int16_t udp_packet_len = udp_packet_create(packet, sizeof(packet), &ip_header, &udp_header, payload, sizeof(payload));
        if (udp_packet_len < 0)        {
            perror("Packet creation failed");
            return;
        }
        packet_len = udp_packet_len;
    }
    else
    {
        tcp_header.src_port = rand() % 65536;
        tcp_header.dst_port = port;
        tcp_header.seq_num = cookie;
        
        int16_t tcp_packet_len = tcp_packet_create(packet, sizeof(packet), &ip_header, &tcp_header, payload, 1);
        if (tcp_packet_len < 0)
        {
            perror("Packet creation failed");
            return;
        }

        packet_len = tcp_packet_len;
    }
    

     // Prepare pseudo header for checksum

    if (sendto(sockfd, packet, packet_len, 0, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("sendto failed");
    }
}

int offset = 0;

// --- Receiver Logic ---
int8_t process_packet(const unsigned char *packet, uint32_t packet_len)
{
    //g_link_header_len is the number of bytes in the link-layer (L2) header of captured packets.
    //Captured packets start with L2 header (Ethernet/Linux cooked/etc), not IP directly.
    //The parser needs to skip those bytes before calling ip_header_parse().
    
    if (packet == NULL || packet_len < g_link_header_len + IP_MIN_HEADER_LEN)
        return 0;

    const uint8_t *ip_buf = (const uint8_t *)(packet + g_link_header_len);
    ip_header_t ip_hdr;
    int16_t ip_hl;
    const uint8_t *transport;
    uint32_t ip_payload_len;

    ip_hl = ip_header_parse(ip_buf, (uint8_t)(packet_len - g_link_header_len), &ip_hdr);
    if (ip_hl < 0)
        return 0;

    if (packet_len < (uint32_t)(g_link_header_len + ip_hl))
        return 0;

    transport = (const uint8_t *)(packet + g_link_header_len + ip_hl);
    ip_payload_len = packet_len - g_link_header_len - (uint32_t)ip_hl;

    switch (ip_hdr.protocol)
    {
    case IPPROTO_TCP:
        printf("Received TCP packet from %s\n", inet_ntoa(*(struct in_addr *)&ip_hdr.src));
        return tcp_response_process(transport, ip_payload_len, &ip_hdr);
    
    case IPPROTO_ICMP:
        printf("Received ICMP packet from %s\n", inet_ntoa(*(struct in_addr *)&ip_hdr.src));
        return icmp_response_process(transport, ip_payload_len, &ip_hdr);
    
    case IPPROTO_UDP:
        printf("Received UDP packet from %s\n", inet_ntoa(*(struct in_addr *)&ip_hdr.src));
        return udp_response_process(transport);
    default:
        return 0;
    }
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
    printf("\n%-6s | %s\n", "PORT", "STATE");
    printf("-------|----------------\n");

    for (i = start; i < end; i++)
    {
        response_type_t response = get_response(&results[i]);
        if (response != RESPONSE_NOT_EXPECTED)
            printf("%-6d | %s\n", results[i].port, state_label(response));
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
    g_link_header_len = (uint32_t)get_link_header_len(datalink);
    if (g_link_header_len < 0)
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
                printf("Scanning port %d with scan type %s...\n", port_i, valid_tokens[scan_i]);
                fflush(stdout);
                send_packet(sock, target_ip, port_i, local_ip, scan_flag);
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
                        send_packet(sock, target_ip, port_i, local_ip, scan_flag);
                    }

                    // Wait in 1ms polls; UDP may span multiple windows via retries.
                    struct pcap_pkthdr *header;
                    const unsigned char *packet;
                    int res = pcap_next_ex(handle, &header, &packet);
                    if (res == 1)
                    {
                        process_packet(packet, header->caplen);
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