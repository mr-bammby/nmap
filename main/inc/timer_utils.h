#ifndef TIMER_UTILS_H
#define TIMER_UTILS_H

#include <time.h>

/* Using struct timespec for nanosecond-level underlying accuracy */
typedef struct {
    struct timespec time;
    short state; 
} nmap_timer_t;

/* Function declarations */
void start_timer(nmap_timer_t *timer);
void stop_timer(nmap_timer_t *timer);
float read_time_s(const nmap_timer_t *timer);

#endif /* TIMER_UTILS_H */