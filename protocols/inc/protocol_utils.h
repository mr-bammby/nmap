#ifndef PROTOCOL_UTILS_H
#define PROTOCOL_UTILS_H

#include <inttypes.h>
#include <stdio.h>
#include "response_states.h"
#include "argument_parser_types.h"

/**
 * Calculate checksum for data (typically used for IP/TCP/UDP headers)
 * 
 * @param data Pointer to data buffer
 * @param len Length of data in bytes
 * @param start_val Initial checksum value (usually 0)
 * @return Calculated 16-bit checksum value
 */
uint32_t protocol_utils_checksum_accumulate(const void *data, uint32_t len, uint32_t start_val);

/**
 * Finalize checksum calculation (folding to 16 bits)
 * 
 * @param data Pointer to data buffer
 * @param len Length of data in bytes
 * @param start_val Initial checksum value (usually 0)
 * @return Final 16-bit checksum value
 */
uint16_t protocol_utils_checksum_final(const void *data, uint32_t len, uint32_t start_val);

/**
 * Print byte data in hexadecimal format
 * 
 * @param addr Pointer to data buffer
 * @param len Number of bytes to print
 */
void protocol_utils_print_bytes(const void *addr, uint32_t len);

/**
 * Initialize scan results for a given set of ports
 * 
 * @param results Pointer to scan_result_t structure to initialize
 * @param ports Pointer to argparse_port_set_t containing the ports to scan
 */
void protocol_utils_initialize_results(scan_result_t *results, const argparse_port_set_t *ports);


#endif /* PROTOCOL_UTILS_H */