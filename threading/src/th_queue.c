
#define MODULE_DEBUG DEBUG_TH_QUEUE
#include "debug.h"
#include "th_queue.h"


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

    return 0;
}

uint8_t th_queue_init_access(th_queue_access_t *access, th_queue_t *queue, th_lock_priority_t priority)
{
    access->queue = queue;
    th_lock_init_access(priority, &(access->queue->lock), &(access->access));
    return 0;
}

int th_queue_write(th_queue_access_t *access, const TH_QUEUE_DATA_TYPE *data)
{
    if (access->queue == NULL)
        return -1;
    
    th_lock_take(&(access->access));
    if (access->queue->is_full)
    {
        th_lock_release(&(access->access));
        return -2;
    }
    memcpy(&(access->queue->data[access->queue->tail]), data, sizeof(TH_QUEUE_DATA_TYPE));
    access->queue->is_empty = 0;
    access->queue->tail++;
    if (access->queue->tail >= access->queue->capacity)
    {
        access->queue->tail = 0;
    }
    if (access->queue->tail < (access->queue->capacity - 1))
    {
        if(access->queue->tail == (access->queue->head - 1))
        {
            access->queue->is_full = 1;
            th_lock_release(&(access->access));
            return 1;
        }
    }
    else if (access->queue->tail == (access->queue->capacity - 1))
    {
        if (access->queue->head == 0)
        {
            access->queue->is_full = 1;
            th_lock_release(&(access->access));
            return 1;
        }
    }
    th_lock_release(&(access->access));
    return 0;
}

static int th_queue_chk(th_queue_access_t *access, TH_QUEUE_DATA_TYPE *data)
{
    if (access->queue->is_empty)
    {
        th_unlock(&(access->access));
        return -2;
    }
    memcpy(data, &(access->queue->data[access->queue->head]), sizeof(TH_QUEUE_DATA_TYPE));
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

int th_queue_read(th_queue_access_t *access, TH_QUEUE_DATA_TYPE *data,  TH_QUEUE_ACCEPT_COND(cond))
{
    if (access->queue == NULL)
        return -1; 
    th_lock_take(&(access->access));
    if (th_queue_chk(access->queue, data) == 0)
    {
        if (cond != NULL)
        {
            if (cond(data) == 0)
            {
                th_lock_release(&(access->access));
                return 2;
            }
        }
        int ret = th_queue_accept(access->queue);
        th_lock_release(&(access->access));
        return(ret);
    }
    th_lock_release(&(access->access));
    return(-1);

}