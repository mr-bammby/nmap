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

#define NUMBER_OF_SCAN_TYPES 6

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
void send_packet(int sockfd, const char *target_ip, int port, const char *local_ip, uint8_t scan_type)
{
    uint8_t packet[128];
    ip_header_t ip_header;
    tcp_header_t tcp_header;

    struct sockaddr_in sin;
    struct pseudo_header psh;

    memset(packet, 0, 128);
    ip_header.id = htons(rand() % 65536);
    ip_header.protocol = IPPROTO_TCP;
    ip_header.src = inet_addr(local_ip);
    ip_header.dst = inet_addr(target_ip);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = inet_addr(target_ip);

    tcp_header.src_port = rand() % 65536;
    tcp_header.dst_port = port;
    tcp_header.seq_num = rand() % 4294967296;
    switch (scan_type)
    {
        case SCAN_FLG_SYN:
            tcp_header.flags = TCP_FLAG_SYN;
            break;
        case SCAN_FLG_ACK:
            tcp_header.flags = TCP_FLAG_ACK;
            break;
        case SCAN_FLG_NULL:
            tcp_header.flags = 0;
            break;
        case SCAN_FLG_FIN:
            tcp_header.flags = TCP_FLAG_FIN;
            break;
        case SCAN_FLG_XMAS:
            tcp_header.flags = TCP_FLAG_FIN | TCP_FLAG_PSH | TCP_FLAG_URG;
            break;
        default:
            perror("Unsupported scan type");
            return;
            break;
    }
    int16_t tcp_packet_len = tcp_packet_create(packet, sizeof(packet), &ip_header, &tcp_header);
    if (tcp_packet_len < 0)
    {
        perror("Packet creation failed");
        return;
    }

     // Prepare pseudo header for checksum

    if (sendto(sockfd, packet, tcp_packet_len, 0, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("sendto failed");
    }
}

// --- Receiver Logic ---
void process_packet(const u_char *packet)
{
    struct ip *ip = (struct ip *)(packet + 14);
    int ip_hl = ip->ip_hl * 4;

    printf("Received packet from %s\n", inet_ntoa(ip->ip_src));
    if (ip->ip_p == IPPROTO_TCP)
    {
        struct tcphdr *tcp = (struct tcphdr *)(packet + 14 + ip_hl);
        
        // th_flags is used in some headers, check bitmask for SYN+ACK or RST
        if ((tcp->syn) && (tcp->ack))
        {
            printf("\n[!] Port %d is OPEN\n", ntohs(tcp->source));
        } else if (tcp->rst)
        {
            printf("\n[-] Port %d is CLOSED\n", ntohs(tcp->source));
        }
    }
    else if (ip->ip_p == IPPROTO_ICMP)
    {
        printf("\n[-] Port Error (ICMP Unreachable)\n");
    }
    fflush(stdout);
}

int single_thread_exec(const char *target_ip, port_bitmap_t ports, scan_bitmap_t scans)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    struct bpf_program fp;
    int sock;
    pcap_if_t *alldevs;
    char *device_name;
    char *local_ip;

    if (scans != SCAN_FLG_SYN)
    {
        fprintf(stderr, "Only SYN scan is supported in current single-threaded implementation.\n");
        return 1;
    }

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
    pcap_setnonblock(handle, 1, errbuf);

    char filter[100];
    sprintf(filter, "(src host %s) or icmp", target_ip);
    pcap_compile(handle, &fp, filter, 0, PCAP_NETMASK_UNKNOWN);
    pcap_setfilter(handle, &fp);

    for (int port_i = 0; port_i < NUMBER_OF_PORTS; port_i++)
    {
        if (ports[port_i / 8] & (1 << (port_i % 8)))
        {
            for (int scan_i = 0; scan_i < NUMBER_OF_SCAN_TYPES; scan_i++)
            {
                if (scans & (1 << scan_i))
                {
                    printf("Scanning port %d with scan type %d...\n", port_i, scan_i);
                    fflush(stdout);
                    send_packet(sock, target_ip, port_i, local_ip, 1 << scan_i);
                    for (int attempt = 0; attempt < 500; attempt++)
                    {
                        // 500ms wait per port
                        struct pcap_pkthdr *header;
                        const u_char *packet;
                        int res = pcap_next_ex(handle, &header, &packet);
                        if (res == 1)
                        {
                            process_packet(packet);
                        }
                        usleep(1000); 
                    }
                    printf("Done.\n");
                }
            }
        }
    }

    pcap_close(handle);
    close(sock);
    return 0;
}