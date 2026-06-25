#define MODULE_DEBUG DEBUG_TICKET_SCHEDULER
#include "debug.h"
#include <stdint.h>
#include <pthreads.h>

#define HIGH_PRIORITY   1
#define LOW_PRIORITY    0

// Initialisieren: int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
// Sperren: int pthread_mutex_lock(pthread_mutex_t *mutex);
// Entsperren: int pthread_mutex_unlock(pthread_mutex_t *mutex);
// Freigeben: int pthread_mutex_destroy(pthread_mutex_t *mutex);

typedef struct ticket_scheduler_s
{
    uint32_t high_prio_count;
    uint32_t low_prio_count;
    uint32_t high_prio_actual;
    uint32_t low_prio_actual;
    pthread_mutex_t lock;
} ticket_scheduler_t;

typedef struct ticket_s
{
    uint8_t ticket_priority;
    uint32_t ticket_number;
} ticket_t;

extern ticket_scheduler_t g_ticket_scheduler = {
    .high_prio_count = 0,
    .low_prio_count = 0,
    .high_prio_actual = 0,
    .low_prio_actual = 0;
    .lock = PTHREAD_MUTEX_INITIALIZER
};

void lock(ticket_t *ticket)
{
    pthread_mutex_lock(&g_ticket_scheduler->lock);
    if (ticket->ticket_priority == HIGH_PRIORITY)
    {
        ticket->ticket_number = g_ticket_scheduler->high_prio_count;
        g_ticket_scheduler->high_prio_count++;
        LOGD("High counter increase to %d\n", g_ticket_scheduler->high_prio_count);
    }
    else
    {
        ticket->ticket_number = g_ticket_scheduler->low_prio_count;
        g_ticket_scheduler->low_prio_count++;
        LOGD("Low counter increase to %d\n", g_ticket_scheduler->low_prio_count);
    }
    pthread_mutex_unlock(&(g_ticket_scheduler->lock));



}

void unlock()
{

}

void main_usage()
{
    pthread_mutex_destroy(&g_ticket_scheduler->lock);
}