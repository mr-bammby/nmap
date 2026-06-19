#include <stdio.h>
#include <inttypes.h>
#include <netinet/in.h>
#include "protocol_utils.h"
#include "scan_context.h"
#include "debug.h"

uint32_t checksum_accumulate(const void *data, uint32_t len, uint32_t start_val)
{
    const uint16_t *p = data;
    uint32_t sum = start_val;

    // Sum 16-bit words
    while (len > 1)
    {
        sum += *p++;
        len -= 2;
    }

    // If there's a leftover byte, pad with zero
    if (len == 1)
    {
        uint16_t last = 0;
        *(uint8_t *)&last = *(const uint8_t *)p;
        sum += last;
    }

    return sum;
}

uint16_t checksum_final(const void *data, uint32_t len, uint32_t start_val)
{
    const uint16_t *p = data;
    uint32_t sum = start_val;

    // Sum 16-bit words
    while (len > 1)
    {
        sum += *p++;
        len -= 2;
    }

    // If there's a leftover byte, pad with zero
    if (len == 1)
    {
        uint16_t last = 0;
        *(uint8_t *)&last = *(const uint8_t *)p;
        sum += last;
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
void initialize_results(scan_result_t *results)
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
