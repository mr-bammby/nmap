#ifndef TIMER_UTILS_H
#define TIMER_UTILS_H

#include <stdint.h>
#include <time.h>

/* Measurement timer used for execution-time tracking */
typedef struct {
    struct timespec time;
    short state;
} nmap_timer_t;

/* Timeout/deadline helper used for non-blocking stop checks */
typedef struct {
    struct timespec start;
    uint32_t timeout_ms;
    uint8_t active;
    uint8_t auto_reload;
} nmap_timeout_t;

/* Function declarations */
void start_timer(nmap_timer_t *timer);
void stop_timer(nmap_timer_t *timer);
float read_time_s(const nmap_timer_t *timer);

/* Non-blocking timeout helpers */
void timeout_init(nmap_timeout_t *timeout, uint32_t timeout_ms, uint8_t auto_reload);
void timeout_start(nmap_timeout_t *timeout, uint32_t timeout_ms);
int timeout_check(nmap_timeout_t *timeout);
void timeout_stop(nmap_timeout_t *timeout);

#endif /* TIMER_UTILS_H */