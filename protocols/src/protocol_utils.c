#define MODULE_DEBUG DEBUG_PROTOCOL_UTILS
#include "debug.h"
#include <stdio.h>
#include <inttypes.h>
#include <netinet/in.h>
#include "protocol_utils.h"
#include "scan_context.h"


/// --- Checksum Calculation Functions ---
// CAN BE DISABLED TO SAVE TIME IN RECEIVING PACKETS, WHEN INTEGRITY IS NOT A CONCERN 
// FOR TESTING TOOLS LIKE NMAP, IT'S USUALLY SAFE TO DISABLE CHECKSUM VERIFICATION,
// AS THE PACKETS ARE NOT USED FOR CRITICAL COMMUNICATIONS, AND THE FOCUS IS ON SCANNING 
// AND RESPONSE ANALYSIS.

uint32_t protocol_utils_checksum_accumulate(const void *data, uint32_t len, uint32_t start_val)
{
    const uint16_t *words = (const uint16_t *)data;
    const uint8_t *bytes = (const uint8_t *)data;
    uint32_t sum = start_val;
    uint32_t word_idx = 0;

    while (len > 1)
    {
        sum += ntohs(words[word_idx]);
        word_idx++;
        len -= 2;
    }

    // If there's a leftover byte, pad with zero
    if (len == 1)
    {
        sum += ntohs((uint16_t)(bytes[word_idx * 2] << 8));
    }

    return sum;
}

uint16_t protocol_utils_checksum_final(const void *data, uint32_t len, uint32_t start_val)
{
    const uint16_t *words = (const uint16_t *)data;
    const uint8_t *bytes = (const uint8_t *)data;
    uint32_t sum = start_val;
    uint32_t word_idx = 0;


    while (len > 1)
    {
        sum += ntohs(words[word_idx]);
        word_idx++;
        len -= 2;
    }

    // If there's a leftover byte, pad with zero
    if (len == 1)
    {
        sum += ntohs((uint16_t)(bytes[word_idx * 2] << 8));
    }

    // Fold 32-bit sum to 16 bits (carry wraparound)
    while (sum >> 16)
    {
        sum = (sum & 0xFFFF) + (sum >> 16);
    }
    // One’s complement
    return (uint16_t)~sum;
}

void print_bytes(const void *addr, uint32_t len)
{
    const uint8_t *p = (const uint8_t *)addr;

    for (uint32_t i = 0; i < len; i++) {
        printf("%02x ", p[i]);
    }
    printf("\n\n");
}

// --- Initialize Results Array ---
void protocol_utils_initialize_results(scan_result_t *results)
{
    for (int i = 0; i < (PORT_END - PORT_START + 1); i++)
    {
        results[i].port = i + PORT_START;
        results[i].protocol = 0;
        results[i].response_syn = RESPONSE_NOT_EXPECTED;
        results[i].response_null = RESPONSE_NOT_EXPECTED;
        results[i].response_ack = RESPONSE_NOT_EXPECTED;
        results[i].response_fin = RESPONSE_NOT_EXPECTED;
        results[i].response_xmas = RESPONSE_NOT_EXPECTED;
        results[i].response_udp = RESPONSE_NOT_EXPECTED;
    }
}
