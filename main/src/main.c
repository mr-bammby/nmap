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

// Port state definitions
typedef enum {
    PORT_STATE_INITIAL = 0,
    PORT_STATE_CONTACTED,
    PORT_STATE_OPEN,
    PORT_STATE_CLOSED,
    PORT_STATE_FILTERED,
    PORT_STATE_OPEN_FILTERED,
    PORT_STATE_UNFILTERED,
    PORT_STATE_UNKNOWN
} port_state_t;

// Response type definitions
typedef enum {
    RESPONSE_NO_RESPONSE = 0,
    RESPONSE_SYN_ACK,
    RESPONSE_RST,
    RESPONSE_ICMP_UNREACHABLE
} response_type_t;

// Scan result structure
typedef struct {
    int port;
    int protocol;
    port_state_t state;
    response_type_t response;
} scan_result_t;

char *target_ip = "45.33.32.156";
scan_result_t results[1024];

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

    //printf("Received packet from %s\n", inet_ntoa(ip->ip_src));
    if (ip->ip_p == IPPROTO_TCP)
    {
        struct tcphdr *tcp = (struct tcphdr *)(packet + 14 + ip_hl);
        
        // th_flags is used in some headers, check bitmask for SYN+ACK or RST
        if ((tcp->syn) && (tcp->ack))
        {
            results[ntohs(tcp->source) - 1].state = PORT_STATE_OPEN;
            results[ntohs(tcp->source) - 1].response = RESPONSE_SYN_ACK;
            //printf("[!] Port %d is OPEN\n\n", ntohs(tcp->source));
        } else if (tcp->rst)
        {
            results[ntohs(tcp->source) - 1].state = PORT_STATE_CLOSED;
            results[ntohs(tcp->source) - 1].response = RESPONSE_RST;
            //printf("\n[-] Port %d is CLOSED\n\n", ntohs(tcp->source));
        }
    }
    else //if (ip->ip_p == IPPROTO_ICMP)
    {
        struct icmphdr *icmp = (struct icmphdr *)(packet + 14 + ip_hl);
        if (icmp->type == 3) // Destination Unreachable
        {
            results[ntohs(icmp->un.gateway) - 1].state = PORT_STATE_FILTERED;
            results[ntohs(icmp->un.gateway) - 1].response = RESPONSE_ICMP_UNREACHABLE;
        }
        //printf("\n[-] Port Error (ICMP Unreachable)\n");
    }
    fflush(stdout);
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
void print_results(scan_result_t *results, int size)
{
    const char *state_strings[] = {
        "INITIAL",
        "CONTACTED",
        "OPEN",
        "CLOSED",
        "FILTERED",
        "OPEN/FILTERED",
        "UNFILTERED",
        "UNKNOWN"
    };
    
    printf("\n%-6s | %s\n", "PORT", "STATE");
    printf("-------|----------------\n");
    
    for (int i = 0; i < size; i++)
    {
        // Only print ports that have been scanned (not in INITIAL state)
        if (results[i].state != PORT_STATE_INITIAL)
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
    initialize_results(results, 1024);

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

    for (int port = 1; port <= 150; port++)
    {
        send_syn(sock, target_ip, port, local_ip);
        //printf("Sent SYN to %d... ", port);
        results[port - 1].state = PORT_STATE_CONTACTED;
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
            usleep(1); 
            attempts++;
        }
        //printf("Done for port %d.\n", port);
    }
    for (int port = 1; port <= 150; port++)
    {
        if (results[port - 1].state == PORT_STATE_INITIAL)
        {
            results[port - 1].state = PORT_STATE_OPEN_FILTERED;
            results[port - 1].response = RESPONSE_NO_RESPONSE;
            //printf("[?] Port %d is FILTERED (no response)\n", port);
        }
    }
    print_results(results, 150);
    pcap_close(handle);
    close(sock);
    return 0;
}