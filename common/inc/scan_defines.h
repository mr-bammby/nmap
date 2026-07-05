#ifndef SCAN_DEFINES_H
#define SCAN_DEFINES_H

#define SCAN_FLG_SYN 0x01
#define SCAN_FLG_NULL 0x02
#define SCAN_FLG_ACK 0x04
#define SCAN_FLG_FIN 0x08
#define SCAN_FLG_XMAS 0x10
#define SCAN_FLG_UDP 0x20

#define SCAN_FLG_ALL 0xff

#define SCAN_NUMBER_OF_SCAN_TYPES 6

static const char *const scan_valid_tokens[SCAN_NUMBER_OF_SCAN_TYPES] =
    {
        "SYN",
        "ACK",
        "NULL",
        "FIN",
        "XMAS",
        "UDP"
    };

#endif /* SCAN_DEFINES_H */