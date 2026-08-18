#ifndef TIMER_UTILS_H
#define TIMER_UTILS_H

#include <stdint.h>
#include <time.h>

/* Measurement timer used for execution-time tracking */
typedef struct {
    struct timespec time; // The time value when the timer was started or stopped
    short state; // 0 = not started, 1 = running, 2 = stopped
} nmap_timer_t;

/* Timeout/deadline helper used for non-blocking stop checks */
typedef struct {
    struct timespec start; // The time value when the timeout was started
    uint32_t timeout_ms; // The timeout duration in milliseconds
    uint8_t active; // 0 = inactive, 1 = active
    uint8_t auto_reload; // 0 = do not auto-reload, 1 = auto-reload after timeout
} nmap_timeout_t;

/* Timer utility functions */

/* Start the timer */
void start_timer(nmap_timer_t *timer);

/* Stop the timer */
void stop_timer(nmap_timer_t *timer);

/* Read the elapsed time in seconds */
float read_time_s(const nmap_timer_t *timer);

/* Timeout/deadline helper functions (non-blocking) */

/* Initialize the timeout structure */
void timeout_init(nmap_timeout_t *timeout, uint32_t timeout_ms, uint8_t auto_reload);

/* Start the timeout */
void timeout_start(nmap_timeout_t *timeout, uint32_t timeout_ms);

/* Check if the timeout has been reached */
int timeout_check(nmap_timeout_t *timeout);

/* Stop the timeout */
void timeout_stop(nmap_timeout_t *timeout);

#endif /* TIMER_UTILS_H */