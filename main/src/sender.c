#define MODULE_DEBUG DEBUG_SENDER
#include "debug.h"
#include <unistd.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "sender.h"
#include "packet_handler.h"
#include "scan_defines.h"

int sender_init(int *sock_out)
{
    int sock;
    LOGD("Initializing sender socket\n");
    sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (sock < 0)
    {
        LOGE_ERRNO("Socket error\n");
        return -1;
    }
    LOGD("Sender socket created successfully\n");
    int one = 1;
    const int *val = &one;
    if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, val, sizeof(one)) < 0)
    {
        LOGE_ERRNO("Error setting IP_HDRINCL\n");
        close(sock);
        return -1;
    }
    LOGD("IP_HDRINCL set successfully\n");
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

void sender_run(int sock, uint32_t target_ip, int port_i, uint32_t local_ip, uint8_t scan_flag, uint8_t probe, response_type_t *response_slot)
{
#if DEBUG_SENDER
    char target_ip_str[INET_ADDRSTRLEN];
    char local_ip_str[INET_ADDRSTRLEN];
    struct in_addr target_addr = { .s_addr = target_ip };
    struct in_addr local_addr = { .s_addr = local_ip };
    inet_ntop(AF_INET, &target_addr, target_ip_str, sizeof(target_ip_str));
    inet_ntop(AF_INET, &local_addr, local_ip_str, sizeof(local_ip_str));
    LOGD("Sender run: target_ip=%s, port=%d, local_ip=%s, scan_flag=%u, probe=%u\n", target_ip_str, port_i, local_ip_str, scan_flag, probe);
#endif
    response_type_t null_response = RESPONSE_NO_RESPONSE;
    if (response_slot == NULL)
    {
        response_slot = &null_response;
    }
    send_packet_ip(sock, target_ip, port_i, local_ip, scan_flag, probe);
}
