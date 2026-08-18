#ifndef TH_LOCK_H
#define TH_LOCK_H

#include <stdint.h>
#include <pthread.h>

/* Define the priority levels for lock access. */
typedef enum {
    TH_LOCK_PRIORITY_HIGH,
    TH_LOCK_PRIORITY_LOW
} th_lock_priority_t;

/* Control structure for managing access to a shared resource with priority-based access. */
typedef struct
{
    uint32_t high_prio_total; // Total number of high-priority tickets assigned
    uint32_t high_prio_serving; // Number of high-priority tickets currently being served
    pthread_cond_t high_prio_cond; // Condition variable for high-priority threads
    uint32_t low_prio_total; // Total number of low-priority tickets assigned
    uint32_t low_prio_serving; // Number of low-priority tickets currently being served
    pthread_cond_t low_prio_cond; // Condition variable for low-priority threads
    pthread_mutex_t lock; // Mutex to protect access to the control structure
} th_lock_control_t;


/* Access structure for a thread to interact with the lock control. */
typedef struct
{
    uint32_t assigned_ticket_number; // The ticket number assigned to this thread for access
    th_lock_priority_t priority; // The priority level of this thread (high or low)
    th_lock_control_t *control; // Pointer to the shared lock control structure
} th_lock_access_t;

/* Status codes for lock operations. */
typedef enum th_lock_status
{
    TH_LOCK_OK_GENERIC = 0,
    TH_LOCK_ERR_GENERIC = -1,
    TH_LOCK_ERR_LOCK = -2,
    TH_LOCK_ERR_INVALID_PARAM = -3
} th_lock_status_t;

/* Initialize a lock access structure for a thread with the specified priority and control structure. */
th_lock_status_t th_lock_init_access(th_lock_priority_t priority, th_lock_control_t *resource, th_lock_access_t *access);

/* Acquire the lock for the thread, blocking if necessary until it can proceed. */
th_lock_status_t th_lock_take(th_lock_access_t *access);

/* Release the lock held by the thread, allowing other threads to proceed. */
th_lock_status_t th_lock_release(th_lock_access_t *access);

#endif /* TH_LOCK_H */