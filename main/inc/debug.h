#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <stdio.h>
#include <errno.h>
#include <string.h>

/* ========================================================================= */
/* Global debug level                                                        */
/* ========================================================================= */

#define DEBUG_LEVEL_NONE 0
#define DEBUG_LEVEL_ERROR 1
#define DEBUG_LEVEL_WARNING 2
#define DEBUG_LEVEL_INFO 3
#define DEBUG_LEVEL_DEBUG 4

#ifndef DEBUG_LEVEL
#ifdef DEBUG
#define DEBUG_LEVEL DEBUG
#else
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#endif
#endif

/* ========================================================================= */
/* Debug flags                                                               */
/* ========================================================================= */

/* main */
#define DEBUG_ADDR_HASHMAP                  (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 0)
#define DEBUG_BUILD_MESSAGE                 (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 0)
#define DEBUG_MAIN                          (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 1)
#define DEBUG_MULTI_COMMAND_QUEUE           (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 0)
#define DEBUG_MULTI_THREAD_EXEC             (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 0)
#define DEBUG_MULTI_THREAD_INIT             (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 0)
#define DEBUG_MULTI_THREAD_RECEIVER         (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 1)
#define DEBUG_MULTI_THREAD_SENDER           (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 1)
#define DEBUG_PACKET_RECEIVE                (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 1)
#define DEBUG_PACKET_SEND                   (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 0)
#define DEBUG_RECEIVER                      (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 1)
#define DEBUG_SENDER                        (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 1)
#define DEBUG_SINGLE_THREAD_EXEC            (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 1)
#define DEBUG_TIMER_UTILS                   (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 0)

#define DEBUG_MULTI_THREAD_PACKET_RECEIVE   (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 1)


/* argument_parser */
#define DEBUG_ADRESS_UTILS                  (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 0)
#define DEBUG_ARGUMENT_HANDLER_ADRESS       (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 0)
#define DEBUG_ARGUMENT_HANDLER_FILE         (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 0)
#define DEBUG_ARGUMENT_HANDLER_HELP         (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 0)
#define DEBUG_ARGUMENT_HANDLER_SCANS        (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 0)
#define DEBUG_ARGUMENT_HANDLER_SPEEDUP      (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 0)
#define DEBUG_ARGUMENT_PARSER               (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 0)
#define DEBUG_ARGUMENT_HANDLER_PORTS        (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 0)
#define DEBUG_PORT_UTILS                    (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 0)

/* protocols */
#define DEBUG_ICMP                          (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 1)
#define DEBUG_IP                            (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 0)
#define DEBUG_PROTOCOL_UTILS                (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 0)
#define DEBUG_TCP                           (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 1)
#define DEBUG_UDP                           (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 1)

/* result_printer */
#define DEBUG_PARSER_UTILS                  (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 0)
#define DEBUG_PRINTER_UTILS                 (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 0)
#define DEBUG_RESULT_PRINTER                (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 0)

/* threading */
#define DEBUG_TH_LOCK                       (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 0)
#define DEBUG_TH_FLAGGING_ARRAY             (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 0)
#define DEBUG_TH_QUEUE                      (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG && 0)

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

#if DEBUG_LEVEL >= DEBUG_LEVEL_ERROR
#define LOGE(fmt, ...) LOG_IMPL(stderr, LOG_ERR, fmt, ##__VA_ARGS__)
#define LOGE_ERRNO(fmt, ...)                                      \
    do {                                                          \
        int err = errno;                                          \
        char buf[1024];                                           \
        (void)strerror_r(err, buf, sizeof(buf));                  \
        LOG_IMPL(stderr, LOG_ERR, fmt ": %s\n",                   \
                 ##__VA_ARGS__, buf);                             \
    } while (0)
#else
#define LOGE(...) ((void)0)
#define LOGE_ERRNO(...) ((void)0)
#endif

#if DEBUG_LEVEL >= DEBUG_LEVEL_WARNING
#define LOGW(fmt, ...) LOG_IMPL(stdout, LOG_WRN, fmt, ##__VA_ARGS__)
#else
#define LOGW(...) ((void)0)
#endif

#if DEBUG_LEVEL >= DEBUG_LEVEL_INFO
#define LOGI(fmt, ...) LOG_IMPL(stdout, LOG_INF, fmt, ##__VA_ARGS__)
#define LOGI_WF(fmt, ...) LOG_IMPL_WF(stdout, fmt, ##__VA_ARGS__)
#else
#define LOGI(...) ((void)0)
#define LOGI_WF(...) ((void)0)
#endif

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