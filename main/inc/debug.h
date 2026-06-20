#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <stdio.h>

/* ========================================================================= */
/* Global debug switch                                                       */
/* ========================================================================= */

#ifndef DEBUG
#define DEBUG 0
#endif

/* ========================================================================= */
/* Debug flags                                                               */
/* ========================================================================= */

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

/* ========================================================================= */
/* Log levels                                                                */
/* ========================================================================= */

#define LOG_DBG "DBG"
#define LOG_INF "INF"
#define LOG_WRN "WRN"
#define LOG_ERR "ERR"

/* ========================================================================= */
/* Generic logger implementation                                             */
/* ========================================================================= */

#define LOG_IMPL(level, module, fmt, ...)                           \
    fprintf(stderr, "[%s][%s][%s:%d:%s] " fmt "\n",                \
            level,                                                  \
            module,                                                 \
            __FILE__,                                               \
            __LINE__,                                               \
            __func__,                                               \
            ##__VA_ARGS__)

/* ========================================================================= */
/* Per-module logger setup                                                   */
/*                                                                           */
/* Usage in tcp.c:                                                           */
/*                                                                           */
/*      #define MODULE_DEBUG DEBUG_TCP                                       */
/*      #define MODULE_NAME  "TCP"                                           */
/*      #include "debug.h"                                                   */
/*                                                                           */
/*      LOG(LOG_DBG, "Sending packet");                                      */
/* ========================================================================= */

#ifndef MODULE_DEBUG
#define MODULE_DEBUG 0
#endif

#ifndef MODULE_NAME
#define MODULE_NAME "UNKNOWN"
#endif

#if MODULE_DEBUG
#define LOG(level, fmt, ...) \
    LOG_IMPL(level, MODULE_NAME, fmt, ##__VA_ARGS__)
#else
#define LOG(...)
#endif

#endif /* _DEBUG_H_ */