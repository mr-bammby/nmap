/* Required for clock_gettime and CLOCK_MONOTONIC on POSIX environments */
#define _POSIX_C_SOURCE 199309L

#define MODULE_DEBUG DEBUG_TIMER_UTILS
#include "debug.h"

#include "timer_utils.h"
#include <stddef.h>

static long timespec_diff_ms(const struct timespec *start, const struct timespec *end)
{
    long seconds_diff = end->tv_sec - start->tv_sec;
    long nanoseconds_diff = end->tv_nsec - start->tv_nsec;

    if (nanoseconds_diff < 0)
    {
        seconds_diff -= 1;
        nanoseconds_diff += 1000000000L;
    }

    return (seconds_diff * 1000L) + (nanoseconds_diff / 1000000L);
}

void start_timer(nmap_timer_t *timer)
{
    if (timer != NULL)
    {
        clock_gettime(CLOCK_MONOTONIC, &timer->time);
        timer->state = 1; // Mark timer as running
    }
}

void stop_timer(nmap_timer_t *timer)
{
    struct timespec temp_time;
    if (timer != NULL)
    {
        clock_gettime(CLOCK_MONOTONIC, &temp_time);
    }
    if (timer != NULL)
    {
        timer->time.tv_sec = temp_time.tv_sec - timer->time.tv_sec;
        timer->time.tv_nsec = temp_time.tv_nsec - timer->time.tv_nsec;

        if (timer->time.tv_nsec < 0)
        {
            timer->time.tv_sec -= 1; // Borrow one second
            timer->time.tv_nsec += 1000000000L; // Convert to positive nanoseconds
        }
        timer->state = 2; // Mark timer as stopped
    }
}

float read_time_s(const nmap_timer_t *timer)
{
    float elapsed_seconds = 0.0f;

    if (timer != NULL && timer->state == 2) // Ensure timer is stopped before reading
    {
        /* Calculate total float seconds from time differences */
        elapsed_seconds = (float)timer->time.tv_sec + ((float)timer->time.tv_nsec / 1000000000.0f);
    }
    else
    {
        /* Handle error case: timer is NULL or not stopped */
        elapsed_seconds = -1.0f; // Indicate error with a negative value
    }

    return elapsed_seconds;
}

void timeout_init(nmap_timeout_t *timeout, uint32_t timeout_ms, uint8_t auto_reload)
{
    if (timeout != NULL)
    {
        timeout->start = (struct timespec){0, 0};
        timeout->timeout_ms = timeout_ms;
        timeout->active = 0;
        timeout->auto_reload = auto_reload;
    }
}

void timeout_start(nmap_timeout_t *timeout, uint32_t timeout_ms)
{
    if (timeout != NULL)
    {
        if (timeout_ms > 0)
        {
            timeout->timeout_ms = timeout_ms;
        }
        timeout->active = 1;
        clock_gettime(CLOCK_MONOTONIC, &timeout->start);
    }
}

int timeout_check(nmap_timeout_t *timeout)
{
    struct timespec current_time;

    if (timeout == NULL)
    {
        return 0;
    }
    if (!timeout->active)
    {
        return 1; // Timeout is considered expired if not active
    }

    clock_gettime(CLOCK_MONOTONIC, &current_time);

    if (timespec_diff_ms(&timeout->start, &current_time) < (long)timeout->timeout_ms)
    {
        return 0;
    }

    if (timeout->auto_reload)
    {
        clock_gettime(CLOCK_MONOTONIC, &timeout->start);
    }
    else
    {
        timeout->active = 0;
    }

    return 1;
}

void timeout_stop(nmap_timeout_t *timeout)
{
    if (timeout != NULL)
    {
        timeout->active = 0;
    }
}


