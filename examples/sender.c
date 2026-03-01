#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char **argv) {
    const char *dest = argc > 1 ? argv[1] : "127.0.0.1";
    int port = argc > 2 ? atoi(argv[2]) : 9999;
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) { perror("socket"); return 1; }

    struct sockaddr_in srv;
    memset(&srv, 0, sizeof(srv));
    srv.sin_family = AF_INET;
    srv.sin_port = htons(port);
    if (inet_pton(AF_INET, dest, &srv.sin_addr) != 1) { perror("inet_pton"); return 1; }

    const char *msg = "Hello from sender";
    if (sendto(sock, msg, strlen(msg), 0, (struct sockaddr*)&srv, sizeof(srv)) < 0) {
        perror("sendto"); close(sock); return 1;
    }
    printf("Sent to %s:%d: %s\n", dest, port, msg);

    // wait for response with timeout
    struct timeval tv = {3, 0};
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    char buf[1500];
    struct sockaddr_in from;
    socklen_t flen = sizeof(from);
    ssize_t r = recvfrom(sock, buf, sizeof(buf)-1, 0, (struct sockaddr*)&from, &flen);
    if (r < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) printf("No response (timeout)\n");
        else perror("recvfrom");
        close(sock);
        return 0;
    }
    buf[r] = '\0';
    char addr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &from.sin_addr, addr, sizeof(addr));
    printf("Received from %s:%d: %s\n", addr, ntohs(from.sin_port), buf);

    close(sock);
    return 0;
}
