#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef DEBUG

#define DEBUG_BUILD_MESSAGE   0
#define DEBUG_DISPLAY_HELP    0
#define DEBUG_MAIN            1
#define DEBUG_PACKET_RECEIVE  1
#define DEBUG_PACKET_SEND     0
#define DEBUG_PORT_MAP        0
#define DEBUG_SCAN_PARSER     0

#else

#define DEBUG_BUILD_MESSAGE   0
#define DEBUG_DISPLAY_HELP    0
#define DEBUG_MAIN            0
#define DEBUG_PACKET_RECEIVE  0
#define DEBUG_PACKET_SEND     0
#define DEBUG_PORT_MAP        0
#define DEBUG_SCAN_PARSER     0

#endif

#if DEBUG_MAIN
# define DBG_MAIN(...) fprintf(stderr, __VA_ARGS__)
#else
# define DBG_MAIN(...)
#endif


#endif