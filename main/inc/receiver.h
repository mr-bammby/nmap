#ifndef RECEIVER_H
#define RECEIVER_H
#include <pcap.h>
#include "argument_parser_types.h"
#include "response_states.h"

/* Initialize the receiver */
int receiver_init(const char *target_ip, const argparse_port_set_iterator_t *port_it, pcap_t **pcap_handle_out, char **local_ip_out, uint32_t *link_header_len_out);

/* Clean up the receiver resources */
int receiver_cleanup(pcap_t *pcap_handle);

/* Run the receiver */
int receiver_run(pcap_t *pcap_handle, uint32_t link_header_len, response_type_t *response_slot, scan_result_t *results, argparse_port_set_t *ports);

/* Get the link header length */
int get_link_header_len(int datalink);

/* Get the local IP address for a given network interface */
char* get_local_ip(const char *iface_name);

#endif /* RECEIVER_H */