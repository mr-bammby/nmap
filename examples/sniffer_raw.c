#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/udp.h>

int main(int argc, char **argv) {
    const char *iface = argc > 1 ? argv[1] : NULL; (void)iface;
    int port = argc > 2 ? atoi(argv[2]) : 9999;

    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (sock < 0) { perror("socket (raw)"); return 1; }

    printf("Raw sniffer started (requires root). Filtering UDP port %d\n", port);

    unsigned char buf[65536];
    for (int i = 0; i < 4; ++i) {
        ssize_t len = recv(sock, buf, sizeof(buf), 0);
        if (len <= 0) { perror("recv"); break; }
        struct ip *ip = (struct ip*)buf;
        if (ip->ip_p != IPPROTO_UDP) continue;
        int ihl = ip->ip_hl * 4;
        struct udphdr *udp = (struct udphdr*)(buf + ihl);
        int sport = ntohs(udp->uh_sport);
        int dport = ntohs(udp->uh_dport);
        int udplen = ntohs(udp->uh_ulen) - sizeof(struct udphdr);
        if (sport != port && dport != port) continue;
        char saddr[INET_ADDRSTRLEN], daddr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &ip->ip_src, saddr, sizeof(saddr));
        inet_ntop(AF_INET, &ip->ip_dst, daddr, sizeof(daddr));
        printf("%s:%d -> %s:%d  payload_len=%d\n", saddr, sport, daddr, dport, udplen);
        unsigned char *payload = buf + ihl + sizeof(struct udphdr);
        for (int j = 0; j < udplen; ++j) printf("%02x ", payload[j]);
        printf("\n");
    }

    close(sock);
    return 0;
}
