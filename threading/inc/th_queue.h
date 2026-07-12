#ifndef TH_QUEUE_H
#define TH_QUEUE_H

#include "th_lock.h"
#include "threading_config.h"

#ifndef TH_QUEUE_DATA_TYPE
#error "TH_QUEUE_DATA_TYPE must be defined before including th_queue.h, define it to the type of data you want to store in the queue. It shall be define in thread_config.h or in the file."
#endif

typedef uint16_t ticket_scheduler_t;

#define TH_HI_PRIO 1
#define TH_LO_PRIO 0


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

int th_queue_init(th_queue_t *queue,  size_t capacity);
uint8_t th_queue_init_access(th_queue_access_t *access, th_queue_t *queue, th_lock_priority_t priority);
int th_queue_write(th_queue_access_t *queue, const TH_QUEUE_DATA_TYPE *data);
int th_queue_read(th_queue_access_t *queue, TH_QUEUE_DATA_TYPE *data,  TH_QUEUE_ACCEPT_COND(cond));

#endif // TH_QUEUE_H