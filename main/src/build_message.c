#include "ip.h"
#include "tcp.h"

int16_t tcp_packet_create(uint8_t *buffer, uint32_t buffer_len, const ip_header_t *ip_header, const tcp_header_t *tcp_header)
{

    // Initialize IP header
    int16_t ip_header_len = ip_header_init(buffer, buffer_len, ip_header);
    if (ip_header_len < 0)
    {
        return ip_header_len; // Error initializing IP header
    }

    // Initialize TCP header
    int16_t tcp_header_len = tcp_header_create(buffer + ip_header_len, buffer_len - ip_header_len, tcp_header);
    if (tcp_header_len < 0)
    {
        return tcp_header_len; // Error initializing TCP header
    }
    // Encapsulate the packet (finalize IP header)
    return (ip_header_encapsulate(buffer, tcp_header_len));
}