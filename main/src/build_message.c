#define MODULE_DEBUG DEBUG_BUILD_MESSAGE
#include "debug.h"
#include "ip.h"
#include "tcp.h"
#include "udp.h"
#include <stdio.h>
#include <string.h>

static void print_message(const uint8_t *buffer, uint16_t length)
{
    LOGD("Constructed Packet (Hex):\n");
    for (int i = 0; i < 16; i++)
    {
        if (i % 16 == 0)
            LOGD("%02d ", i);
        else
            LOGD_WF("%02d ", i);
    }
    LOGD_WF("\n");
    LOGD("");
    for (int i = 0; i < 16; i++)
    {
            LOGD_WF("---");
    }
    LOGD_WF("\n");

    for (int i = 0; i < length; i++)
    {

        if (i % 16 == 0)
            LOGD("%02x ", buffer[i]);
        else
            LOGD_WF("%02x ", buffer[i]);
        if ((i + 1) % 16 == 0)
        {
            LOGD_WF("\n");
        }
    }
    LOGD_WF("\n");
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

    #if DEBUG_BUILD_MESSAGE
    LOGD("tcp_packet_create\n");
    print_message(buffer, full_header_len);
    #endif /* DEBUG_BUILD_MEASSAGE */

    return full_header_len;
}

int16_t udp_packet_create(uint8_t *buffer, uint32_t buffer_len, const ip_header_t *ip_header, const udp_header_t *udp_header, const uint32_t *payload, uint16_t payload_len)
{
    // Initialize IP header
    int16_t ip_header_len = ip_header_init(buffer, buffer_len, ip_header);
    if (ip_header_len < 0)
    {
        return ip_header_len; // Error initializing IP header
    }

    // Initialize UDP header
    int16_t udp_header_len = udp_header_create(buffer + ip_header_len, buffer_len - ip_header_len, udp_header);
    if (udp_header_len < 0)
    {
        return udp_header_len; // Error initializing UDP header
    }

    // Copy payload after UDP header
    if (buffer_len < (uint32_t)(ip_header_len + udp_header_len + payload_len))
    {
        return UDP_ERR_BUFFER_TOO_SMALL; // Buffer too small for payload
    }

    if (payload != NULL && payload_len > 0)
    {
        memcpy(buffer + ip_header_len + udp_header_len, payload, payload_len);
    }

    // Encapsulate the packet (finalize IP header)
    int16_t full_packet_len = ip_header_encapsulate(buffer, udp_header_len + payload_len);
    
    #if DEBUG_BUILD_MESSAGE
    LOGD("udp_packet_create\n");
    print_message(buffer, full_packet_len);
    #endif /* DEBUG_BUILD_MEASSAGE */

    return full_packet_len;
}