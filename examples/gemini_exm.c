#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

// Global for simplicity in this example
char *target_ip = "X.X.X.X";

void process_packet(const u_char *packet) {
    struct ip *ip = (struct ip *)(packet + 14);
    int ip_hl = ip->ip_hl * 4;

    if (ip->ip_p == IPPROTO_TCP) {
        struct tcphdr *tcp = (struct tcphdr *)(packet + 14 + ip_hl);
        if (tcp->th_flags == (TH_SYN | TH_ACK)) {
            printf("[!] Port %d is OPEN\n", ntohs(tcp->th_sport));
        } else if (tcp->th_flags & TH_RST) {
            printf("[-] Port %d is CLOSED\n", ntohs(tcp->th_sport));
        }
    } 
    else if (ip->ip_p == IPPROTO_ICMP) {
        // ... (Optional: Insert the ICMP "Inner Header" logic from previous steps)
    }
}

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    struct bpf_program fp;
    int sock;

    // 1. Setup Raw Socket
    sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);

    // 2. Setup PCAP in Non-Blocking Mode
    handle = pcap_open_live("eth0", BUFSIZ, 1, 1, errbuf); // 1ms timeout
    pcap_setnonblock(handle, 1, errbuf);

    char filter[100];
    sprintf(filter, "host %s or icmp", target_ip);
    pcap_compile(handle, &fp, filter, 0, PCAP_NETMASK_UNKNOWN);
    pcap_setfilter(handle, &fp);

    // 3. The Main Single-Threaded Loop
    for (int port = 22; port <= 222; port++) {
        // A. SEND
        // (Assuming you have a send_syn function as defined in previous messages)
        send_syn(sock, target_ip, port);
        printf("Sent SYN to %d... ", port);
        fflush(stdout);

        // B. POLL (Check for responses for 1 second)
        struct pcap_pkthdr *header;
        const u_char *packet;
        
        // We "spin" for a short duration to catch the response
        int attempts = 0;
        while (attempts < 1000) { // Approx 1 second of polling
            int res = pcap_next_ex(handle, &header, &packet);
            if (res == 1) {
                process_packet(packet);
            }
            usleep(1000); // Sleep 1ms
            attempts++;
        }
        printf("Moving to next port.\n");
    }

    pcap_close(handle);
    close(sock);
    return 0;
}