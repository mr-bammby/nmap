#ifndef TH_QUEUE_H
#define TH_QUEUE_H

#include "th_lock.h"
#include "threading_config.h"

/* Compile-time assertion to ensure the data type is defined */
#ifndef TH_QUEUE_DATA_TYPE
#error "TH_QUEUE_DATA_TYPE must be defined before including th_queue.h, define it to the type of data you want to store in the queue. It shall be define in thread_config.h or in the file."
#endif

/* Define the status codes for queue operations. */
typedef enum th_queue_status
{
    TH_QUEUE_OK_GENERIC = 0,
    TH_QUEUE_ERR_GENERIC = -1,
    TH_QUEUE_ERR_FULL = -2,
    TH_QUEUE_ERR_EMPTY = -3,
    TH_QUEUE_ERR_LOCK = -4,
    TH_QUEUE_ERR_INVALID_PARAM = -5,
    TH_QUEUE_OK_EMPTY_AFTER_ACCEPT = 1,
    TH_QUEUE_OK_CONDITION_REJECTED = 2
} th_queue_status_t;

/* Define a function pointer type for the condition function used in th_queue_read. */
#define TH_QUEUE_ACCEPT_COND(func_ptr) int (*func_ptr)(const TH_QUEUE_DATA_TYPE *)

/* Define the queue structure. */
typedef struct th_queue
{
    TH_QUEUE_DATA_TYPE* data; // Pointer to the data buffer
    size_t capacity; // Maximum number of elements the queue can hold
    size_t head; // Index of the next element to be read
    size_t tail; // Index of the next element to be written
    uint8_t is_empty; // Flag indicating if the queue is empty
    uint8_t is_full; // Flag indicating if the queue is full
    th_lock_control_t lock; // Control structure for managing access to the queue
} th_queue_t;

/* Define the access structure for a thread to interact with the queue. */
typedef struct
{
    th_queue_t *queue; // Pointer to the queue structure
    th_lock_access_t access; // Access structure for managing thread access to the queue
} th_queue_access_t;

/* Initialize the queue structure */
th_queue_status_t th_queue_init(th_queue_t *queue,  size_t capacity);

/* Initialize the access structure for a thread to interact with the queue */
th_queue_status_t th_queue_init_access(th_queue_access_t *access, th_queue_t *queue, th_lock_priority_t priority);

/* Write data to the queue */
th_queue_status_t th_queue_write(th_queue_access_t *queue, const TH_QUEUE_DATA_TYPE *data);

/* Read data from the queue, optionally applying a condition function to determine if the data should be accepted */
th_queue_status_t th_queue_read(th_queue_access_t *queue, TH_QUEUE_DATA_TYPE *data,  TH_QUEUE_ACCEPT_COND(cond));

/* Free resources held by the queue (data buffer) */
void th_queue_free(th_queue_t *queue);

#endif /* TH_QUEUE_H */