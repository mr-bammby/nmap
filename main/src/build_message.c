#include "ip.h"
#include "tcp.h"
#include <stdio.h>

void print_message(const uint8_t *buffer, uint16_t length)
{
    printf("Constructed Packet (Hex):\n");
    for (int i = 0; i < length; i++)
    {
        printf("%02x ", buffer[i]);
        if ((i + 1) % 16 == 0)
        {
            printf("\n");
        }
    }
    printf("\n");
}

int16_t tcp_packet_create(uint8_t *buffer, uint32_t buffer_len, const ip_header_t *ip_header, const tcp_header_t *tcp_header, const uint32_t *payload, uint16_t payload_len)
{

    // Initialize IP header
    int16_t ip_header_len = ip_header_init(buffer, buffer_len, ip_header);
    if (ip_header_len < 0)
    {
        return ip_header_len; // Error initializing IP header
    }

    // Initialize TCP header
    int16_t tcp_header_len = tcp_header_create(buffer + ip_header_len, buffer_len - ip_header_len, tcp_header, ip_header, payload, payload_len);
    if (tcp_header_len < 0)
    {
        return tcp_header_len; // Error initializing TCP header
    }
    // Encapsulate the packet (finalize IP header)

    
    int16_t full_header_len = ip_header_encapsulate(buffer, tcp_header_len);
    #ifdef DEBUG_PACKET
    print_message(buffer, full_header_len);
    #endif

    return full_header_len;
}