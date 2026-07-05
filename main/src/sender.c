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

void sender_run(int sock, const char *target_ip, int port_i, const char *local_ip, uint8_t scan_flag, uint8_t attempt, response_type_t *response_slot)
{
    if (scan_flag == SCAN_FLG_UDP &&
        attempt > 0 &&
        (attempt % RESPONSE_WAIT_ATTEMPTS) == 0 &&
        *response_slot == RESPONSE_NO_RESPONSE)
    {
        uint8_t udp_probe_variant = (uint8_t)(attempt / RESPONSE_WAIT_ATTEMPTS);
        send_packet(sock, target_ip, port_i, local_ip, scan_flag, udp_probe_variant);
    }
    else if (scan_flag != SCAN_FLG_UDP &&
            attempt == 0 &&
            *response_slot == RESPONSE_NO_RESPONSE)
    {
        send_packet(sock, target_ip, port_i, local_ip, scan_flag, 0);
    }
}