#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/ip_icmp.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "ip.h"
#include "tcp.h"
#include "icmp.h"
#include <ifaddrs.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include "response_states.h"

#define PORT_START 1
#define PORT_END 150

char *target_ip = "45.33.32.156";
scan_result_t results[1024];
uint32_t g_link_header_len = 14;

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

// --- Helper: Checksum Calculation ---
unsigned short calculate_checksum(unsigned short *ptr, int nbytes)
{
    long sum = 0;
    unsigned short oddbyte;
    unsigned short answer;

    while (nbytes > 1)
    {
        sum += *ptr++;
        nbytes -= 2;
    }
    if (nbytes == 1)
    {
        oddbyte = 0;
        *((u_char *)&oddbyte) = *(u_char *)ptr;
        sum += oddbyte;
    }
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    answer = (unsigned short)~sum;
    return answer;
}

struct pseudo_header
{
    u_int32_t source_address;
    u_int32_t dest_address;
    u_int8_t placeholder;
    u_int8_t protocol;
    u_int16_t tcp_length;
};

// --- Sender Logic ---
void send_syn(int sockfd, char *target_ip, int port, char *local_ip)
{
    char datagram[4096];
    struct tcphdr *tcph = (struct tcphdr *) datagram;
    struct sockaddr_in sin;
    struct pseudo_header psh;

    memset(datagram, 0, 4096);

    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = inet_addr(target_ip);

    tcph->source = htons(12345);
    tcph->dest = htons(port);
    tcph->seq = htonl(rand());
    tcph->ack_seq = 0;
    tcph->doff = 5;
    tcph->syn = 1;
    tcph->window = htons(65535);
    tcph->check = 0;
    tcph->urg_ptr = 0;

    psh.source_address = inet_addr(local_ip);
    psh.dest_address = sin.sin_addr.s_addr;
    psh.placeholder = 0;
    psh.protocol = IPPROTO_TCP;
    psh.tcp_length = htons(sizeof(struct tcphdr));

    int psize = sizeof(struct pseudo_header) + sizeof(struct tcphdr);
    char *pseudogram = malloc(psize);
    memcpy(pseudogram, (char *)&psh, sizeof(struct pseudo_header));
    memcpy(pseudogram + sizeof(struct pseudo_header), tcph, sizeof(struct tcphdr));

    tcph->check = calculate_checksum((unsigned short *)pseudogram, psize);
    free(pseudogram);

    if (sendto(sockfd, datagram, sizeof(struct tcphdr), 0, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("sendto failed");
    }
}

// --- Receiver Logic ---
int process_packet(const unsigned char *packet, uint32_t packet_len)
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

    if (ip_hdr.protocol == IPPROTO_TCP)
    {
        tcp_header_t tcp_hdr;
        int16_t tcp_len = tcp_header_parse(transport, (uint8_t)ip_payload_len, &tcp_hdr);
        if (tcp_len < 0)
            return 0;

        if (tcp_hdr.src_port < PORT_START || tcp_hdr.src_port > PORT_END)
            return 0;

        if ((tcp_hdr.flags & TCP_FLAG_SYN) && (tcp_hdr.flags & TCP_FLAG_ACK))
        {
            results[tcp_hdr.src_port - 1].state = PORT_STATE_OPEN;
            results[tcp_hdr.src_port - 1].response = RESPONSE_SYN_ACK;
            return 1;
        }
        else if (tcp_hdr.flags & TCP_FLAG_RST)
        {
            results[tcp_hdr.src_port - 1].state = PORT_STATE_CLOSED;
            results[tcp_hdr.src_port - 1].response = RESPONSE_RST;
            return 1;
        }
    }
    else if (ip_hdr.protocol == IPPROTO_ICMP)
    {
        icmp_header_t icmp_hdr;
        int16_t icmp_len = icmp_header_parse(transport, (uint8_t)ip_payload_len, &icmp_hdr);
        if (icmp_len < 0)
            return 0;

        if (icmp_hdr.type == 3) // Destination Unreachable
        {
            ip_header_t inner_ip_hdr;
            // The ICMP payload embeds the original IP header + first 8 bytes
            // of the original transport header. The original destination port
            // (probe target) sits at byte offset 2 of that embedded header.
            const uint8_t *orig_ip = (const uint8_t *)(transport + ICMP_HEADER_LEN);
            int16_t orig_ip_hl;

            if (ip_payload_len < ICMP_HEADER_LEN + IP_MIN_HEADER_LEN + 4)
                return 0;

            orig_ip_hl = ip_header_parse(orig_ip,
                                         (uint8_t)(ip_payload_len - ICMP_HEADER_LEN),
                                         &inner_ip_hdr);
            if (orig_ip_hl < 0)
                return 0;

            if (ip_payload_len < (uint32_t)(ICMP_HEADER_LEN + orig_ip_hl + 4))
                return 0;

            uint16_t port = ntohs(*(const uint16_t *)(transport + ICMP_HEADER_LEN + orig_ip_hl + 2));
            if (port < PORT_START || port > PORT_END)
                return 0;

            results[port - 1].state = PORT_STATE_FILTERED;
            results[port - 1].response = RESPONSE_ICMP_UNREACHABLE;
            return 1;
        }
    }
    else if (ip_hdr.protocol == IPPROTO_UDP)
    {
        // For UDP, check if there is a response (open) or no response (filtered)
        uint16_t port = ntohs(*(const uint16_t *)(transport + 2)); // Destination port
        if (port < PORT_START || port > PORT_END)
            return 0;

        results[port - 1].state = PORT_STATE_OPEN;
        results[port - 1].response = RESPONSE_UDP_REPLY;
        return 1;
    }
    fflush(stdout);
    return 0;
}

// --- Initialize Results Array ---
void initialize_results(scan_result_t *results, int size)
{
    for (int i = 0; i < size; i++)
    {
        results[i].port = i + 1;
        results[i].protocol = 0;
        results[i].state = PORT_STATE_INITIAL;
        results[i].response = 0;
    }
}

// --- Print Results ---
void print_results(scan_result_t *results, int start, int end)
{
    const char *state_strings[] = {
        "INITIAL",
        "FILTERED/CONTACTED",
        "OPEN",
        "CLOSED",
        "FILTERED",
        "OPEN/FILTERED",
        "UNFILTERED",
        "UNKNOWN"
    };
    
    printf("\n%-6s | %s\n", "PORT", "STATE");
    printf("-------|----------------\n");
    
    for (int i = start; i < end; i++)
    {
        // Only print ports that have been scanned (not in INITIAL state)
        if (results[i].state != PORT_STATE_INITIAL && results[i].state != PORT_STATE_CLOSED)
        {
            printf("%-6d | %s\n", results[i].port, state_strings[results[i].state]);
        }
    }
}

int main()
{
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    struct bpf_program fp;
    int sock;
    pcap_if_t *alldevs;
    char *device_name;
    char *local_ip;

    // Initialize results array
    initialize_results(results, PORT_END + 1);

    sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (sock < 0)
    {
        perror("Socket error"); return 1;
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
    int link_header_len = get_link_header_len(datalink);
    if (link_header_len < 0)
    {
        fprintf(stderr, "Unsupported datalink type: %d\n", datalink);
        pcap_close(handle);
        close(sock);
        return 1;
    }
    g_link_header_len = (uint32_t)link_header_len;

    pcap_setnonblock(handle, 1, errbuf);

    char filter[100];
    sprintf(filter, "(src host %s) or icmp", target_ip);
    pcap_compile(handle, &fp, filter, 0, PCAP_NETMASK_UNKNOWN);
    pcap_setfilter(handle, &fp);

    for (int port = PORT_START; port <= PORT_END; port++)
    {
        send_syn(sock, target_ip, port, local_ip);
        //printf("Sent SYN to %d... ", port);
        results[port - 1].state = PORT_STATE_CONTACTED;
        fflush(stdout);

        int attempts = 0;
        while (attempts < 400)
        {
            // 500ms wait per port
            struct pcap_pkthdr *header;
            const unsigned char *packet;
            int res = pcap_next_ex(handle, &header, &packet);
            if (res == 1)
            {
                if (process_packet(packet, header->caplen))
                    break;
            }
            usleep(800); 
            attempts++;
        }
        printf("Done for port %d.\n", port);
    }
    for (int port = PORT_START; port <= PORT_END; port++)
    {
        if (results[port - 1].state == PORT_STATE_INITIAL ||
            results[port - 1].state == PORT_STATE_CONTACTED)
        {
            results[port - 1].state = PORT_STATE_OPEN_FILTERED;
            results[port - 1].response = RESPONSE_NO_RESPONSE;
            //printf("[?] Port %d is FILTERED (no response)\n", port);
        }
    }
    print_results(results, PORT_START - 1, PORT_END);
    pcap_close(handle);
    close(sock);
    return 0;
}