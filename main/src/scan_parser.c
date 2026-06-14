#include "scan_parser.h"

port_state_t final_result_logic(const scan_result_t *port_result)
{
    /* This function can be used to implement any final logic that combines
       multiple scan responses into a single state, if desired. */
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

const char *state_label_final(port_state_t port_result)
{
    switch (port_result)
    {
    case PORT_STATE_OPEN:
        return "OPEN";
    case PORT_STATE_CLOSED:
        return "CLOSED";
    case PORT_STATE_FILTERED:
        return "FILTERED";
    case PORT_STATE_OPEN_FILTERED:
        return "OPEN|FILTERED";
    case PORT_STATE_UNFILTERED:
        return "UNFILTERED";
    default:
        return "UNKNOWN";
    }
}

