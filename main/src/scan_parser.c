#include <stdio.h>
#include "scan_parser.h"
#include "port_map.h"
#include "debug.h"

static port_state_t get_final_state(const scan_result_t *port_result)
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

static const char *get_state_label(port_state_t port_result)
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

static port_state_t get_syn_state(const scan_result_t *port_result)
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


static port_state_t get_ack_state(const scan_result_t *port_result)
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

static port_state_t get_null_state(const scan_result_t *port_result)
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

static port_state_t get_fin_state(const scan_result_t *port_result)
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

static port_state_t get_xmas_state(const scan_result_t *port_result)
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

static port_state_t get_udp_state(const scan_result_t *port_result)
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

static void print_scan_block(const char *title,
                             scan_result_t *results,
                             int start,
                             int end,
                             port_state_t (*get_scan_state)(const scan_result_t *))
{
    int i;
    printf("\n***** %s *****\n", title);
    printf("\n%-6s | %-14s | %s\n", "PORT", "STATE", "SERVICE");
    printf("-------|----------------|----------------\n");

    for (i = start; i < end; i++)
    {
        port_state_t response = get_scan_state(&results[i]);
        if (response != PORT_STATE_NOT_SCANNED)
            printf("%-6d | %-14s | %s\n", results[i].port, get_state_label(response), GET_SERVICE_NAME(results[i].port));
    }
}

// --- Print Results ---
void print_results(scan_result_t *results, int start, int end)
{
    print_scan_block("SYN", results, start, end, get_syn_state);
    print_scan_block("ACK", results, start, end, get_ack_state);
    print_scan_block("NULL", results, start, end, get_null_state);
    print_scan_block("FIN", results, start, end, get_fin_state);
    print_scan_block("XMAS", results, start, end, get_xmas_state);
    print_scan_block("UDP", results, start, end, get_udp_state);
    print_scan_block("FINAL", results, start, end, get_final_state);
}


