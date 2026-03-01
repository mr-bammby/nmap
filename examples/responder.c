#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char **argv) {
    int port = argc > 1 ? atoi(argv[1]) : 9999;
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) { perror("socket"); return 1; }

    struct sockaddr_in srv;
    memset(&srv, 0, sizeof(srv));
    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = htonl(INADDR_ANY);
    srv.sin_port = htons(port);

    if (bind(sock, (struct sockaddr*)&srv, sizeof(srv)) < 0) { perror("bind"); close(sock); return 1; }
    printf("Responder listening on 0.0.0.0:%d\n", port);

    char buf[1500];
    struct sockaddr_in from;
    socklen_t flen = sizeof(from);
    ssize_t r = recvfrom(sock, buf, sizeof(buf)-1, 0, (struct sockaddr*)&from, &flen);
    if (r < 0) { perror("recvfrom"); close(sock); return 1; }
    buf[r] = '\0';
    char addr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &from.sin_addr, addr, sizeof(addr));
    printf("Received from %s:%d: %s\n", addr, ntohs(from.sin_port), buf);

    const char *reply_prefix = "Echo: ";
    char out[1600];
    snprintf(out, sizeof(out), "%s%s", reply_prefix, buf);
    if (sendto(sock, out, strlen(out), 0, (struct sockaddr*)&from, flen) < 0) perror("sendto");

    close(sock);
    return 0;
}
