
#define MODULE_DEBUG DEBUG_TH_QUEUE
#include "debug.h"
#include "th_queue.h"
#include <stdlib.h>

th_queue_status_t th_queue_init(th_queue_t *queue,  size_t capacity)
{
    if (queue == NULL || capacity == 0)
        return TH_QUEUE_ERR_INVALID_PARAM;

    queue->data = calloc(capacity, sizeof(TH_QUEUE_DATA_TYPE));
    if (queue->data == NULL)
        return TH_QUEUE_ERR_GENERIC;

    queue->capacity = capacity;
    queue->head = 0;
    queue->tail = 0;
    queue->is_empty = 1;
    queue->is_full = 0;

    /* Initialize lock control structure so th_lock_* functions can use it */
    queue->lock.high_prio_total = 0;
    queue->lock.high_prio_serving = 0;
    queue->lock.low_prio_total = 0;
    queue->lock.low_prio_serving = 0;
    if (pthread_cond_init(&queue->lock.high_prio_cond, NULL) != 0)
    {
        free(queue->data);
        queue->data = NULL;
        return TH_QUEUE_ERR_GENERIC;
    }
    if (pthread_cond_init(&queue->lock.low_prio_cond, NULL) != 0)
    {
        pthread_cond_destroy(&queue->lock.high_prio_cond);
        free(queue->data);
        queue->data = NULL;
        return TH_QUEUE_ERR_GENERIC;
    }
    if (pthread_mutex_init(&queue->lock.lock, NULL) != 0)
    {
        pthread_cond_destroy(&queue->lock.high_prio_cond);
        pthread_cond_destroy(&queue->lock.low_prio_cond);
        free(queue->data);
        queue->data = NULL;
        return TH_QUEUE_ERR_GENERIC;
    }

    return TH_QUEUE_OK_GENERIC;
}

th_queue_status_t th_queue_init_access(th_queue_access_t *access, th_queue_t *queue, th_lock_priority_t priority)
{
    access->queue = queue;
    if (th_lock_init_access(priority, &(access->queue->lock), &(access->access)) != TH_LOCK_OK_GENERIC)
    {
        LOGE("Failed to initialize lock access for queue\n");
        return TH_QUEUE_ERR_LOCK;
    }
    return TH_QUEUE_OK_GENERIC;
}

th_queue_status_t th_queue_write(th_queue_access_t *access, const TH_QUEUE_DATA_TYPE *data)
{
    if (access->queue == NULL)
        return TH_QUEUE_ERR_INVALID_PARAM;
    
    if (th_lock_take(&(access->access)) != TH_LOCK_OK_GENERIC)
    {
        LOGE("Failed to take lock for queue access\n");
        return TH_QUEUE_ERR_LOCK;
    }
    if (access->queue->is_full)
    {
        if (th_lock_release(&(access->access)) != TH_LOCK_OK_GENERIC)
        {
            LOGE("Failed to release lock for queue access\n");
            return TH_QUEUE_ERR_LOCK;
        }
        return TH_QUEUE_ERR_FULL;
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
            if (th_lock_release(&(access->access)) != TH_LOCK_OK_GENERIC)
            {
                LOGE("Failed to release lock for queue access\n");
                return TH_QUEUE_ERR_LOCK;
            }
            return TH_QUEUE_OK_EMPTY_AFTER_ACCEPT;
        }
    }
    else if (access->queue->tail == (access->queue->capacity - 1))
    {
        if (access->queue->head == 0)
        {
            access->queue->is_full = 1;
            if (th_lock_release(&(access->access)) != TH_LOCK_OK_GENERIC)
            {
                LOGE("Failed to release lock for queue access\n");
                return TH_QUEUE_ERR_LOCK;
            }
            return TH_QUEUE_OK_EMPTY_AFTER_ACCEPT;
        }
    }
    if (th_lock_release(&(access->access)) != TH_LOCK_OK_GENERIC)
    {
        LOGE("Failed to release lock for queue access\n");
        return TH_QUEUE_ERR_LOCK;
    }
    return TH_QUEUE_OK_GENERIC;
}

static th_queue_status_t th_queue_chk(th_queue_access_t *access, TH_QUEUE_DATA_TYPE *data)
{
    if (access->queue->is_empty)
    {
        return TH_QUEUE_ERR_EMPTY;
    }
    (void)memcpy(data, &(access->queue->data[access->queue->head]), sizeof(TH_QUEUE_DATA_TYPE));
    return TH_QUEUE_OK_GENERIC;
}

static th_queue_status_t th_queue_accept(th_queue_t *queue)
{
    queue->is_full = 0;
    queue->head++;
    if (queue->head >= (queue->capacity))
    {
        queue->head = 0;
    }
    if (queue->head == queue->tail)
    {
        queue->is_empty = 1;
        return TH_QUEUE_OK_EMPTY_AFTER_ACCEPT;
    }
    return TH_QUEUE_OK_GENERIC;
}

th_queue_status_t th_queue_read(th_queue_access_t *access, TH_QUEUE_DATA_TYPE *data,  TH_QUEUE_ACCEPT_COND(cond))
{
    size_t head;
    size_t tail;
    int is_empty;
    int is_full;
    th_queue_status_t chk;

    if (access->queue == NULL)
        return TH_QUEUE_ERR_INVALID_PARAM; 
    if (th_lock_take(&(access->access)) != TH_LOCK_OK_GENERIC)
    {
        LOGE("Failed to take lock for queue access\n");
        return TH_QUEUE_ERR_LOCK;
    }

    chk = th_queue_chk(access, data);
    head = access->queue->head;
    tail = access->queue->tail;
    is_empty = access->queue->is_empty;
    is_full = access->queue->is_full;

    if (chk == TH_QUEUE_OK_GENERIC)
    {
        if (cond != NULL)
        {
            if (cond(data) <= 0)
            {
                if (th_lock_release(&(access->access)) != TH_LOCK_OK_GENERIC)
                {
                    LOGE("Failed to release lock for queue access\n");
                    return TH_QUEUE_ERR_LOCK;
                }
                return TH_QUEUE_OK_CONDITION_REJECTED;
            }
        }
        int ret = th_queue_accept(access->queue);
        if (th_lock_release(&(access->access)) != TH_LOCK_OK_GENERIC)
        {
            LOGE("Failed to release lock for queue access\n");
            return TH_QUEUE_ERR_LOCK;
        }
        return(ret);
    }
    if (th_lock_release(&(access->access)) != TH_LOCK_OK_GENERIC)
    {
        LOGE("Failed to release lock for queue access\n");
        return TH_QUEUE_ERR_LOCK;
    }
    return(TH_QUEUE_ERR_EMPTY);

}

void th_queue_free(th_queue_t *queue)
{
    if (queue == NULL)
        return;
    if (queue->data != NULL)
    {
        /* Destroy synchronization primitives initialized in th_queue_init */
        (void)pthread_mutex_destroy(&queue->lock.lock);
        (void)pthread_cond_destroy(&queue->lock.high_prio_cond);
        (void)pthread_cond_destroy(&queue->lock.low_prio_cond);
        free(queue->data);
        queue->data = NULL;
    }
    queue->capacity = 0;
    queue->head = 0;
    queue->tail = 0;
    queue->is_empty = 1;
    queue->is_full = 0;
}