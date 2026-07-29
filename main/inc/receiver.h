#ifndef __RECEIVER_H__
#define __RECEIVER_H__
#include <pcap.h>
#include "argument_parser_types.h"
#include "response_states.h"

int receiver_init(const char *target_ip, const argparse_port_set_iterator_t *port_it, pcap_t **pcap_handle_out, char **local_ip_out, uint32_t *link_header_len_out);
int receiver_cleanup(pcap_t *pcap_handle);
int receiver_run(pcap_t *pcap_handle, uint32_t link_header_len, response_type_t *response_slot, scan_result_t *results);
int get_link_header_len(int datalink);
char* get_local_ip(const char *iface_name);

#endif /* __RECEIVER_H__ */