#define MODULE_DEBUG DEBUG_SENDER
#include "debug.h"
#include <netinet/ip.h>
#include <arpa/inet.h>

int sender_init(int *sock_out)
{
    int sock;
    sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (sock < 0)
    {
        LOGE_ERRNO("Socket error\n");
        return -1;
    }
    int one = 1;
    const int *val = &one;
    if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, val, sizeof(one)) < 0)
    {
        LOGE_ERRNO("Error setting IP_HDRINCL\n");
        close(sock);
        return -1;
    }
    *sock_out = sock;
    return 0;
}

int sender_cleanup(int *sock)
{
    if (*sock >= 0)
    {
        close(*sock);
        *sock = -1;
    }
    return 0;
}