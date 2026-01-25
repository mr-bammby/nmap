#ifndef PROTOCOL_UTILS_H
#define PROTOCOL_UTILS_H

#include <inttypes.h>
#include <stdio.h>

/**
 * Calculate checksum for data (typically used for IP/TCP/UDP headers)
 * 
 * @param data Pointer to data buffer
 * @param len Length of data in bytes
 * @param start_val Initial checksum value (usually 0)
 * @return Calculated 16-bit checksum value
 */
uint16_t checksum(const void *data, uint32_t len, uint16_t start_val);

/**
 * Print byte data in hexadecimal format
 * 
 * @param addr Pointer to data buffer
 * @param len Number of bytes to print
 */
void print_bytes(const void *addr, uint32_t len);

#endif // PROTOCOL_UTILS_H