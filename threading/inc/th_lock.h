#ifndef TH_LOCK_H
#define TH_LOCK_H

#include <stdint.h>
#include <pthread.h>

typedef enum {
    TH_LOCK_PRIORITY_HIGH,
    TH_LOCK_PRIORITY_LOW
} th_lock_priority_t;

typedef struct
{
    uint32_t high_prio_total;
    uint32_t high_prio_serving;
    pthread_cond_t high_prio_cond;
    uint32_t low_prio_total;
    uint32_t low_prio_serving;
    pthread_cond_t low_prio_cond;
    pthread_mutex_t assignment_lock;
    pthread_mutex_t lock;
} th_lock_control_t;

typedef struct
{
    uint32_t assigned_ticket_number;
    th_lock_priority_t priority;
    th_lock_control_t *control;
} th_lock_access_t;

typedef enum th_lock_status
{
    TH_LOCK_OK_GENERIC = 0,
    TH_LOCK_ERR_GENERIC = -1,
    TH_LOCK_ERR_LOCK = -2,
    TH_LOCK_ERR_INVALID_PARAM = -3
} th_lock_status_t;

th_lock_status_t th_lock_init_access(th_lock_priority_t priority, th_lock_control_t *resource, th_lock_access_t *access);
th_lock_status_t th_lock_take(th_lock_access_t *access);
th_lock_status_t th_lock_release(th_lock_access_t *access);

#endif // TH_LOCK_H