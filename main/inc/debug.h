#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <stdio.h>
#include <errno.h>
#include <string.h>

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
#define DEBUG_MAIN                          (DEBUG && 1)
#define DEBUG_PACKET_RECEIVE                (DEBUG && 1)
#define DEBUG_PACKET_SEND                   (DEBUG && 0)
#define DEBUG_SINGLE_THREAD_EXEC            (DEBUG && 0)
#define DEBUG_TIMER_UTILS                   (DEBUG && 0)

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

/* result_printer */
#define DEBUG_PARSER_UTILS                  (DEBUG && 0)
#define DEBUG_PRINTER_UTILS                 (DEBUG && 0)
#define DEBUG_RESULT_PRINTER                (DEBUG && 0)


/* ========================================================================= */
/* Log levels                                                                */
/* ========================================================================= */

#define LOG_DBG "DBG"
#define LOG_INF "INF"
#define LOG_WRN "WRN"
#define LOG_ERR "ERR"
#define LOG_DWF ""

/* ========================================================================= */
/* Generic logger implementation                                             */
/* ========================================================================= */

#define LOG_IMPL(stream, level, fmt, ...)                     \
    fprintf((stream),                                         \
            "[%s][%s:%d:%s] " fmt,                            \
            (level),                                          \
            __FILE__,                                         \
            __LINE__,                                         \
            __func__,                                         \
            ##__VA_ARGS__)

#define LOG_IMPL_WF(stream, fmt, ...)                         \
    fprintf((stream),                                         \
            fmt,                                              \
            ##__VA_ARGS__)

/* ========================================================================= */
/* Per-module logger setup                                                   */
/*                                                                           */
/* Usage in tcp.c (needs to be defined before all other packages):           */
/*                                                                           */
/*      #define MODULE_DEBUG DEBUG_TCP                                       */
/*      #include "debug.h"                                                   */
/*                                                                           */
/*      LOGD("Sending packet\n");                                            */
/* ========================================================================= */

#ifndef MODULE_DEBUG
#define MODULE_DEBUG 0
#endif

#define LOGE(fmt, ...) LOG_IMPL(stderr, LOG_ERR, fmt, ##__VA_ARGS__)
#define LOGE_ERRNO(fmt, ...)                                      \
    do {                                                          \
        int err = errno;                                          \
        LOG_IMPL(stderr, LOG_ERR, fmt ": %s\n",                   \
                 ##__VA_ARGS__, strerror(err));                   \
    } while (0)
#define LOGW(fmt, ...) LOG_IMPL(stdout, LOG_WRN, fmt, ##__VA_ARGS__)
#define LOGI(fmt, ...) LOG_IMPL(stdout, LOG_INF, fmt, ##__VA_ARGS__)
#define LOGI_WF(fmt, ...) LOG_IMPL_WF(stdout, fmt, ##__VA_ARGS__)

#ifdef MODULE_DEBUG
#if MODULE_DEBUG
#define LOGD(fmt, ...) LOG_IMPL(stdout, LOG_DBG, fmt, ##__VA_ARGS__)
#define LOGD_WF(fmt, ...) LOG_IMPL_WF(stdout, fmt, ##__VA_ARGS__)
#else
#define LOGD(...) ((void)0)
#define LOGD_WF(...) ((void)0)
#endif
#else
#define LOGD(...) ((void)0)
#define LOGD_WF(...) ((void)0)
#endif

#endif /* _DEBUG_H_ */