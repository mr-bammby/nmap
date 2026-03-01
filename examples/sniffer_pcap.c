#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>

static int packet_count = 0;

void print_payload(const u_char *payload, int len) {
    int i;
    for (i = 0; i < len; ++i) {
        unsigned char c = payload[i];
        printf("%02x ", c);
    }
    printf("\n");
    for (i = 0; i < len; ++i) {
        unsigned char c = payload[i];
        printf("%c", (c >= 32 && c <= 126) ? c : '.');
    }
    printf("\n");
}

void cb(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
    (void)user;
    int linktype = *(int*)user; // pass linktype via user
    const u_char *ip_pkt;
    int ip_off = 0;
    if (linktype == DLT_EN10MB) ip_off = 14;
    else if (linktype == DLT_NULL) ip_off = 4;
    else ip_off = 0;

    if ((int)h->caplen < ip_off + sizeof(struct ip)) return;
    ip_pkt = bytes + ip_off;
    struct ip *ip = (struct ip*)ip_pkt;
    if (ip->ip_p != IPPROTO_UDP) return;
    int ihl = ip->ip_hl * 4;
    struct udphdr *udp = (struct udphdr*)(ip_pkt + ihl);
    int sport = ntohs(udp->uh_sport);
    int dport = ntohs(udp->uh_dport);
    int udplen = ntohs(udp->uh_ulen) - sizeof(struct udphdr);
    const u_char *payload = (u_char*)udp + sizeof(struct udphdr);

    printf("--- packet %d ---\n", ++packet_count);
    char saddr[INET_ADDRSTRLEN], daddr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &ip->ip_src, saddr, sizeof(saddr));
    inet_ntop(AF_INET, &ip->ip_dst, daddr, sizeof(daddr));
    printf("%s:%d -> %s:%d  payload_len=%d\n", saddr, sport, daddr, dport, udplen);
    if (udplen > 0) print_payload(payload, udplen);

    (void)packet_count;
}

int main(int argc, char **argv) {
    char errbuf[PCAP_ERRBUF_SIZE];
    const char *dev = argc > 1 ? argv[1] : "lo";
    int port = argc > 2 ? atoi(argv[2]) : 9999;

    pcap_t *handle = pcap_open_live(dev, 65536, 1, 1000, errbuf);
    if (!handle) { fprintf(stderr, "pcap_open_live: %s\n", errbuf); return 1; }

    int linktype = pcap_datalink(handle);
    char filter[128];
    snprintf(filter, sizeof(filter), "udp and port %d", port);
    struct bpf_program fp;
    if (pcap_compile(handle, &fp, filter, 1, PCAP_NETMASK_UNKNOWN) < 0) {
        fprintf(stderr, "pcap_compile failed\n"); pcap_close(handle); return 1;
    }
    if (pcap_setfilter(handle, &fp) < 0) { fprintf(stderr, "pcap_setfilter failed\n"); pcap_close(handle); return 1; }

    printf("Listening on %s (linktype=%d) for UDP port %d\n", dev, linktype, port);

    // We need to pass both handle and linktype. Use handle as user pointer and store linktype in a small buffer.
    int user_data[2];
    user_data[0] = linktype;
    user_data[1] = 0;

    // Because the callback signature only takes u_char* user, pass a pointer to linktype stored on stack.
    // capture 4 packets (or until interrupted)
    pcap_loop(handle, 4, cb, (u_char*) &linktype);

    pcap_close(handle);
    return 0;
}
