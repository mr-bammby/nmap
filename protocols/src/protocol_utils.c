#include <inttypes.h>

uint16_t checksum(const void *data, uint32_t len, uint16_t start_val)
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

    for (int i = 0; i < len; i++) {
        printf("%02x ", p[i]);
    }
    printf("\n\n");
}
