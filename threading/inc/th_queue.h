#ifndef TH_QUEUE_H
#define TH_QUEUE_H

#include "th_lock.h"
#include "threading_config.h"

#ifndef TH_QUEUE_DATA_TYPE
#error "TH_QUEUE_DATA_TYPE must be defined before including th_queue.h, define it to the type of data you want to store in the queue. It shall be define in thread_config.h or in the file."
#endif

typedef uint16_t ticket_scheduler_t;

typedef enum th_queue_status
{
    TH_QUEUE_OK_GENERIC = 0,
    TH_QUEUE_ERR_GENERIC = -1,
    TH_QUEUE_ERR_FULL = -2,
    TH_QUEUE_ERR_EMPTY = -3,
    TH_QUEUE_ERR_LOCK = -4,
    TH_QUEUE_ERR_INVALID_PARAM = -5,
    TH_QUEUE_OK_EMPTY_AFTER_ACCEPT = 1,
    TH_QUEUE_OK_CONDITION_REJECTED = 2,
    TH_QUEUE_OK_FULL_AFTER  = 3
} th_queue_status_t;

#define TH_QUEUE_ACCEPT_COND(func_ptr) int (*func_ptr)(const TH_QUEUE_DATA_TYPE *)

typedef struct th_queue
{
    TH_QUEUE_DATA_TYPE* data;
    size_t capacity;
    size_t head;
    size_t tail;
    uint8_t is_empty;
    uint8_t is_full;
    th_lock_control_t lock;
} th_queue_t;

typedef struct
{
    th_queue_t *queue;
    th_lock_access_t access;
} th_queue_access_t;

th_queue_status_t th_queue_init(th_queue_t *queue,  size_t capacity);
th_queue_status_t th_queue_init_access(th_queue_access_t *access, th_queue_t *queue, th_lock_priority_t priority);
th_queue_status_t th_queue_write(th_queue_access_t *queue, const TH_QUEUE_DATA_TYPE *data);
th_queue_status_t th_queue_read(th_queue_access_t *queue, TH_QUEUE_DATA_TYPE *data,  TH_QUEUE_ACCEPT_COND(cond));

#endif // TH_QUEUE_H