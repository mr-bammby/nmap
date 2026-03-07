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

char *target_ip = "8.8.8.8";

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

int main()
{
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    struct bpf_program fp;
    int sock;
    pcap_if_t *alldevs;
    char *device_name;
    char *local_ip;

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

    for (int port = 440; port <= 445; port++)
    {
        send_syn(sock, target_ip, port, local_ip);
        printf("Sent SYN to %d... ", port);
        fflush(stdout);

        int attempts = 0;
        while (attempts < 500)
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
            attempts++;
        }
        printf("Done.\n");
    }

    pcap_close(handle);
    close(sock);
    return 0;
}