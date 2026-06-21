#include <stdio.h>
#include "scan_parser.h"
#include "port_map.h"
#include "debug.h"

port_state_t get_final_state(const scan_result_t *port_result)
{
    if (port_result->response_syn == RESPONSE_SYN_ACK || \
        port_result->response_udp == RESPONSE_UDP_REPLY)
        return PORT_STATE_OPEN;
    else if (port_result->response_syn == RESPONSE_RST  || \
        port_result->response_null == RESPONSE_RST || \
        port_result->response_fin == RESPONSE_RST  || \
        port_result->response_xmas == RESPONSE_RST || \
        port_result->response_udp == RESPONSE_ICMP_UNREACHABLE)
        return PORT_STATE_CLOSED;
    else if (port_result->response_syn == RESPONSE_ICMP_UNREACHABLE  || \
        port_result->response_null == RESPONSE_ICMP_UNREACHABLE || \
        port_result->response_fin == RESPONSE_ICMP_UNREACHABLE  || \
        port_result->response_xmas == RESPONSE_ICMP_UNREACHABLE || \
        port_result->response_udp == RESPONSE_ICMP_FILTERED)
        return PORT_STATE_FILTERED;
    else if (port_result->response_syn != RESPONSE_NOT_EXPECTED)
        return PORT_STATE_FILTERED;
    else if (port_result->response_ack == RESPONSE_RST)
    {
        if (port_result->response_null == RESPONSE_NOT_EXPECTED && \
            port_result->response_fin == RESPONSE_NOT_EXPECTED  && \
            port_result->response_xmas == RESPONSE_NOT_EXPECTED && \
            port_result->response_udp == RESPONSE_NOT_EXPECTED)
            return PORT_STATE_UNFILTERED;
        else
            return PORT_STATE_OPEN; // assumed
    }
    else if (port_result->response_ack != RESPONSE_NOT_EXPECTED)
        return PORT_STATE_FILTERED;
    else if (port_result->response_null == RESPONSE_NOT_EXPECTED  && \
             port_result->response_fin == RESPONSE_NOT_EXPECTED   && \
             port_result->response_xmas == RESPONSE_NOT_EXPECTED && \
             port_result->response_udp == RESPONSE_NOT_EXPECTED && \
             port_result->response_syn == RESPONSE_NOT_EXPECTED && \
             port_result->response_ack == RESPONSE_NOT_EXPECTED)
        return PORT_STATE_NOT_SCANNED; // can't be sure if open or filtered
    else
        return PORT_STATE_OPEN_FILTERED;
}

port_state_t get_syn_state(const scan_result_t *port_result)
{
    if (port_result->response_syn == RESPONSE_NOT_EXPECTED)
        return PORT_STATE_NOT_SCANNED;
    else if (port_result->response_syn == RESPONSE_SYN_ACK)
        return PORT_STATE_OPEN;
    else if (port_result->response_syn == RESPONSE_RST)
        return PORT_STATE_CLOSED;
    else if (port_result->response_syn == RESPONSE_NO_RESPONSE || \
        port_result->response_syn == RESPONSE_ICMP_UNREACHABLE)
        return PORT_STATE_FILTERED;
    else
        return PORT_STATE_UNKNOWN;
}

port_state_t get_ack_state(const scan_result_t *port_result)
{
    if (port_result->response_ack == RESPONSE_NOT_EXPECTED)
        return PORT_STATE_NOT_SCANNED;
    else if (port_result->response_ack == RESPONSE_RST)
        return PORT_STATE_UNFILTERED;
    else if (port_result->response_ack == RESPONSE_NO_RESPONSE || port_result->response_ack == RESPONSE_ICMP_UNREACHABLE)
        return PORT_STATE_FILTERED;
    else
        return PORT_STATE_UNKNOWN;
}

port_state_t get_null_state(const scan_result_t *port_result)
{
    if (port_result->response_null == RESPONSE_NOT_EXPECTED)
        return PORT_STATE_NOT_SCANNED;
    else if (port_result->response_null == RESPONSE_RST)
        return PORT_STATE_CLOSED;
    else if (port_result->response_null == RESPONSE_NO_RESPONSE || port_result->response_null == RESPONSE_ICMP_UNREACHABLE)
        return PORT_STATE_FILTERED;
    else
        return PORT_STATE_UNKNOWN;
}

port_state_t get_fin_state(const scan_result_t *port_result)
{
    if (port_result->response_fin == RESPONSE_NOT_EXPECTED)
        return PORT_STATE_NOT_SCANNED;
    else if (port_result->response_fin == RESPONSE_RST)
        return PORT_STATE_CLOSED;
    else if (port_result->response_fin == RESPONSE_NO_RESPONSE || port_result->response_fin == RESPONSE_ICMP_UNREACHABLE)
        return PORT_STATE_FILTERED;
    else
        return PORT_STATE_UNKNOWN;
}

port_state_t get_xmas_state(const scan_result_t *port_result)
{
    if (port_result->response_xmas == RESPONSE_NOT_EXPECTED)
        return PORT_STATE_NOT_SCANNED;
    if (port_result->response_xmas == RESPONSE_RST)
        return PORT_STATE_CLOSED;
    else if (port_result->response_xmas == RESPONSE_NO_RESPONSE || port_result->response_xmas == RESPONSE_ICMP_UNREACHABLE)
        return PORT_STATE_FILTERED;
    else
        return PORT_STATE_UNKNOWN;
}

port_state_t get_udp_state(const scan_result_t *port_result)
{
    if (port_result->response_udp == RESPONSE_NOT_EXPECTED)
        return PORT_STATE_NOT_SCANNED;
    else if (port_result->response_udp == RESPONSE_UDP_REPLY)
        return PORT_STATE_OPEN;
    else if (port_result->response_udp == RESPONSE_ICMP_UNREACHABLE)
        return PORT_STATE_CLOSED;
    else if (port_result->response_udp == RESPONSE_ICMP_FILTERED)
        return PORT_STATE_FILTERED;
    else if (port_result->response_udp == RESPONSE_NO_RESPONSE)
        return PORT_STATE_OPEN_FILTERED;
    else
        return PORT_STATE_UNKNOWN;
}


