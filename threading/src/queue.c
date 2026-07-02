// Include lock

#include <inttypes.h>
#include <pthread.h>
#include <string.h>


typedef struct th_queue_iterator
{
    uint64_t addrress_idx;
    uint16_t port_idx;
    uint8_t scan_idx;
} th_cmd_t;

typedef uint16_t ticket_scheduler_t;

#define TH_HI_PRIO 1
#define TH_LO_PRIO 0

#define TH_QUEUE_DATA_TYPE th_cmd_t
#define TH_QUEUE_LOCK ticket_scheduler_t
#define TH_QUEUE_ACCEPT_COND(func_ptr) int (*func_ptr)(const TH_QUEUE_DATA_TYPE *)

typedef struct ticket_scheduler_s
{
    uint32_t high_prio_count;
    uint32_t low_prio_count;
    uint32_t high_prio_actual;
    uint32_t low_prio_actual;
    pthread_mutex_t lock;
}  th_lock_t;

typedef struct th_queue
{
    TH_QUEUE_DATA_TYPE* data;
    size_t capacity;
    size_t size;
    size_t head;
    size_t tail;
    uint8_t is_empty;
    uint8_t is_full;
    TH_QUEUE_LOCK lock;
} th_queue_t;





int th_queue_init(th_queue_t *queue,  size_t capacity)
{
    if (queue == NULL || capacity == 0)
        return -1;

    queue->data = (void **)malloc(sizeof(TH_QUEUE_DATA_TYPE) * capacity);
    if (queue->data == NULL)
        return -1;

    queue->capacity = capacity;
    queue->head = 0;
    queue->tail = 0;
    queue->is_empty = 1;
    queue->is_full = 0;

    if (th_lock_init(&queue->lock) != 0)
    {
        free(queue->data);
        return -1;
    }

    return 0;
}

int th_queue_write(th_queue_t *queue, const TH_QUEUE_DATA_TYPE *data)
{
    if (queue == NULL)
        return -1;
    
    th_lock(queue->lock, TH_HI_PRIO);
    if (queue->is_full)
    {
        th_unlock(queue->lock);
        return -2;
    }
    memcpy(&(queue->data[queue->tail]), data, sizeof(TH_QUEUE_DATA_TYPE));
    queue->is_empty = 0;
    queue->tail++;
    if (queue->tail >= queue->capacity)
    {
        queue->tail = 0;
    }
    if (queue->tail < (queue->capacity - 1))
    {
        if(queue->tail == (queue->head - 1))
        {
            queue->is_full = 1;
            th_unlock(queue->lock);
            return 1;
        }
    }
    else if (queue->tail == (queue->capacity - 1))
    {
        if (queue->head == 0)
        {
            queue->is_full = 1;
            th_unlock(queue->lock);
            return 1;
        }
    }
    th_unlock(queue->lock);
    return 0;
}

static int th_queue_chk(th_queue_t *queue, TH_QUEUE_DATA_TYPE *data)
{
    if (queue->is_empty)
    {
        th_unlock(queue->lock);
        return -2;
    }
    memcpy(data, &(queue->data[queue->head]), sizeof(TH_QUEUE_DATA_TYPE));
}

static int th_queue_accept(th_queue_t *queue)
{
    queue->head++;
    if (queue->head >= (queue->capacity))
    {
        queue->tail = 0;
    }
    if (queue->head == queue->tail)
    {
        queue->is_empty = 1;
        return(1);
    }
    return 0;
}

int th_queue_read(th_queue_t *queue, TH_QUEUE_DATA_TYPE *data,  TH_QUEUE_ACCEPT_COND(cond))
{
    if (queue == NULL)
        return -1; 
    th_lock(queue->lock, TH_LO_PRIO);
    if (th_queue_chk(queue, data) == 0)
    {
        if (cond != NULL)
        {
            if (cond(data) == 0)
            {
                th_unlock(queue->lock);
                return 2;
            }
        }
        int ret = th_queue_accept(queue);
        th_unlock(queue->lock);
        return(ret);
    }
    th_unlock(queue->lock);
    return(-1);

}