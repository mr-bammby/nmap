/* Required for clock_gettime and CLOCK_MONOTONIC on POSIX environments */
#define _POSIX_C_SOURCE 199309L

#include "timer_utils.h"
#include <stddef.h>

void start_timer(nmap_timer_t *timer)
{
    if (timer != NULL)
    {
        clock_gettime(CLOCK_MONOTONIC, &timer->time);
    }
    if (timer != NULL)
    {
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
        // For this implementation, we return 0.0f to indicate an invalid read
        elapsed_seconds = -1.0f; // Indicate error with a negative value
    }

    return elapsed_seconds;
}
