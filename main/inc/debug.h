#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <stdio.h>

/* Flags */

/* Global debug switch */
#ifndef DEBUG
#define DEBUG 0
#endif

/* main */
#define DEBUG_BUILD_MESSAGE                 (DEBUG && 1)
#define DEBUG_DISPLAY_HELP                  (DEBUG && 0)
#define DEBUG_MAIN                          (DEBUG && 1)
#define DEBUG_PACKET_RECEIVE                (DEBUG && 1)
#define DEBUG_PACKET_SEND                   (DEBUG && 0)
#define DEBUG_SCAN_PARSER                   (DEBUG && 0)
#define DEBUG_SINGLE_THREAD_EXEC            (DEBUG && 0)

/* argument_parser */
#define DEBUG_ADRESS_UTILS                  (DEBUG && 0)
#define DEBUG_ARGUMENT_HANDLER_ADRESS       (DEBUG && 0)
#define DEBUG_ARGUMENT_HANDLER_FILE         (DEBUG && 0)
#define DEBUG_ARGUMENT_HANDLER_HELP         (DEBUG && 0)
#define DEBUG_ARGUMENT_HANDLER_SCANS        (DEBUG && 0)
#define DEBUG_ARGUMENT_HANDLER_SPEEDUP      (DEBUG && 0)
#define DEBUG_ARGUMENT_PARSER               (DEBUG && 0)
#define DEBUG_ARGUMENT_HANDLER_PORTS        (DEBUG && 0)
#define DEBUG_PORT_UTILS                    (DEBUG && 0)

/* protocols */
#define DEBUG_ICMP                          (DEBUG && 0)
#define DEBUG_IP                            (DEBUG && 0)
#define DEBUG_PROTOCOL_UTILS                (DEBUG && 0)
#define DEBUG_TCP                           (DEBUG && 0)
#define DEBUG_UDP                           (DEBUG && 0)

/* Logger macros */

/* main */
#define DBG_BUILD_MESSAGE(...)          do { if (DEBUG_BUILD_MESSAGE)         fprintf(stderr, __VA_ARGS__); } while (0)
#define DBG_DISPLAY_HELP(...)           do { if (DEBUG_DISPLAY_HELP)          fprintf(stderr, __VA_ARGS__); } while (0)
#define DBG_MAIN(...)                   do { if (DEBUG_MAIN)                  fprintf(stderr, __VA_ARGS__); } while (0)
#define DBG_PACKET_RECEIVE(...)         do { if (DEBUG_PACKET_RECEIVE)        fprintf(stderr, __VA_ARGS__); } while (0)
#define DBG_PACKET_SEND(...)            do { if (DEBUG_PACKET_SEND)           fprintf(stderr, __VA_ARGS__); } while (0)
#define DBG_SCAN_PARSER(...)            do { if (DEBUG_SCAN_PARSER)           fprintf(stderr, __VA_ARGS__); } while (0)
#define DBG_SINGLE_THREAD_EXEC(...)     do { if (DEBUG_SINGLE_THREAD_EXEC)    fprintf(stderr, __VA_ARGS__); } while (0)

/* argument_parser */
#define DBG_ADDRESS_UTILS(...)          do { if (DEBUG_ADRESS_UTILS)          fprintf(stderr, __VA_ARGS__); } while (0)
#define DBG_ARG_ADDR(...)               do { if (DEBUG_ARGUMENT_HANDLER_ADRESS)  fprintf(stderr, __VA_ARGS__); } while (0)
#define DBG_ARG_FILE(...)               do { if (DEBUG_ARGUMENT_HANDLER_FILE) fprintf(stderr, __VA_ARGS__); } while (0)
#define DBG_ARG_HELP(...)               do { if (DEBUG_ARGUMENT_HANDLER_HELP) fprintf(stderr, __VA_ARGS__); } while (0)
#define DBG_ARG_SCANS(...)              do { if (DEBUG_ARGUMENT_HANDLER_SCANS) fprintf(stderr, __VA_ARGS__); } while (0)
#define DBG_ARG_SPEEDUP(...)            do { if (DEBUG_ARGUMENT_HANDLER_SPEEDUP) fprintf(stderr, __VA_ARGS__); } while (0)
#define DBG_ARG_PARSER(...)             do { if (DEBUG_ARGUMENT_PARSER)       fprintf(stderr, __VA_ARGS__); } while (0)
#define DBG_ARG_PORTS(...)              do { if (DEBUG_ARGUMENT_HANDLER_PORTS) fprintf(stderr, __VA_ARGS__); } while (0)
#define DBG_PORT_UTILS(...)             do { if (DEBUG_PORT_UTILS)            fprintf(stderr, __VA_ARGS__); } while (0)

/* protocols */
#define DBG_ICMP(...)                   do { if (DEBUG_ICMP)                  fprintf(stderr, __VA_ARGS__); } while (0)
#define DBG_IP(...)                     do { if (DEBUG_IP)                    fprintf(stderr, __VA_ARGS__); } while (0)
#define DBG_PROTOCOL_UTILS(...)         do { if (DEBUG_PROTOCOL_UTILS)        fprintf(stderr, __VA_ARGS__); } while (0)
#define DBG_TCP(...)                    do { if (DEBUG_TCP)                   fprintf(stderr, __VA_ARGS__); } while (0)
#define DBG_UDP(...)                    do { if (DEBUG_UDP)                   fprintf(stderr, __VA_ARGS__); } while (0)

#endif