#ifndef SCAN_DEFINES_H
#define SCAN_DEFINES_H

/* Define scan type flags for command-line parsing and internal representation. */
#define SCAN_FLG_SYN 0x01
#define SCAN_FLG_NULL 0x02
#define SCAN_FLG_ACK 0x04
#define SCAN_FLG_FIN 0x08
#define SCAN_FLG_XMAS 0x10
#define SCAN_FLG_UDP 0x20

#define SCAN_FLG_ALL 0xff

/* Define the number of supported scan types. */
#define SCAN_NUMBER_OF_SCAN_TYPES 6

/* Define the valid scan tokens for command-line parsing. */
extern const char *const scan_valid_tokens[SCAN_NUMBER_OF_SCAN_TYPES];
#endif /* SCAN_DEFINES_H */