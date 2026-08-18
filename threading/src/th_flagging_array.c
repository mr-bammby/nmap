#define MODULE_DEBUG DEBUG_TH_FLAGGING_ARRAY
#include "debug.h"
#include "th_flagging_array.h"

/* TO be called before thread create */
th_flagging_array_status_t th_flagging_array_init(th_flagging_array_t *arr, size_t capcity)
{
    if (arr == NULL || capcity == 0)
        return TH_FLAGGING_ARRAY_ERR_INVALID_PARAM;

    memset(&arr->lock, 0, sizeof(arr->lock));
    if (pthread_cond_init(&arr->lock.high_prio_cond, NULL) != 0)
        return TH_FLAGGING_ARRAY_ERR_GENERIC;
    if (pthread_cond_init(&arr->lock.low_prio_cond, NULL) != 0)
    {
        pthread_cond_destroy(&arr->lock.high_prio_cond);
        return TH_FLAGGING_ARRAY_ERR_GENERIC;
    }
    if (pthread_mutex_init(&arr->lock.lock, NULL) != 0)
    {
        pthread_cond_destroy(&arr->lock.high_prio_cond);
        pthread_cond_destroy(&arr->lock.low_prio_cond);
        return TH_FLAGGING_ARRAY_ERR_GENERIC;
    }

    arr->array = calloc(capcity, sizeof(uint8_t));
    if (arr->array == NULL)
    {
        pthread_mutex_destroy(&arr->lock.lock);
        pthread_cond_destroy(&arr->lock.high_prio_cond);
        pthread_cond_destroy(&arr->lock.low_prio_cond);
        return TH_FLAGGING_ARRAY_ERR_GENERIC;
    }

    arr->size = capcity;
    return TH_FLAGGING_ARRAY_OK_GENERIC;
}

th_flagging_array_status_t th_flagging_array_init_access(th_flagging_array_access_t *access, th_flagging_array_t *array, th_lock_priority_t priority)
{
    if (access == NULL || array == NULL)
        return TH_FLAGGING_ARRAY_ERR_INVALID_PARAM;

    access->array = array;
    if (th_lock_init_access(priority, &(access->array->lock), &(access->access)) != TH_LOCK_OK_GENERIC)
    {
        LOGE("Failed to initialize lock access for flagging array\n");
        return TH_FLAGGING_ARRAY_ERR_LOCK;
    }
    return TH_FLAGGING_ARRAY_OK_GENERIC;
}

th_flagging_array_status_t th_flagging_array_get(th_flagging_array_access_t *access, size_t idx, uint8_t *ret)
{
    if (access == NULL || access->array == NULL || ret == NULL)
        return TH_FLAGGING_ARRAY_ERR_INVALID_PARAM;
    if (idx >= access->array->size)
    {
        return TH_FLAGGING_ARRAY_ERR_INVALID_PARAM;
    }
    if (th_lock_take(&(access->access)) != TH_LOCK_OK_GENERIC)
    {
        LOGE("Failed to take lock for flagging array access\n");
        return TH_FLAGGING_ARRAY_ERR_LOCK;
    }
    *ret = access->array->array[idx];
    if (th_lock_release(&(access->access)) != TH_LOCK_OK_GENERIC)
    {
        LOGE("Failed to release lock for flagging array access\n");
        return TH_FLAGGING_ARRAY_ERR_LOCK;
    }
    return TH_FLAGGING_ARRAY_OK_GENERIC;
}


th_flagging_array_status_t th_flagging_array_set(th_flagging_array_access_t *access, size_t idx, uint8_t val)
{
    if (access == NULL || access->array == NULL)
        return TH_FLAGGING_ARRAY_ERR_INVALID_PARAM;
    if (idx >= access->array->size)
    {
        return TH_FLAGGING_ARRAY_ERR_INVALID_PARAM;
    }
    if (th_lock_take(&(access->access)) != TH_LOCK_OK_GENERIC)
    {
        LOGE("Failed to take lock for flagging array access\n");
        return TH_FLAGGING_ARRAY_ERR_LOCK;
    }
    access->array->array[idx] = val;
    if (th_lock_release(&(access->access)) != TH_LOCK_OK_GENERIC)
    {
        LOGE("Failed to release lock for flagging array access\n");
        return TH_FLAGGING_ARRAY_ERR_LOCK;
    }
    return TH_FLAGGING_ARRAY_OK_GENERIC;
}

th_flagging_array_status_t th_flagging_array_reset(th_flagging_array_access_t *access)
{
    if (access == NULL || access->array == NULL)
        return TH_FLAGGING_ARRAY_ERR_INVALID_PARAM;
    if (th_lock_take(&(access->access)) != TH_LOCK_OK_GENERIC)
    {
        LOGE("Failed to take lock for flagging array access\n");
        return TH_FLAGGING_ARRAY_ERR_LOCK;
    }
    (void)memset(access->array->array, 0, access->array->size);
    if (th_lock_release(&(access->access)) != TH_LOCK_OK_GENERIC)
    {
        LOGE("Failed to release lock for flagging array access\n");
        return TH_FLAGGING_ARRAY_ERR_LOCK;
    }
    return TH_FLAGGING_ARRAY_OK_GENERIC;
}

void th_flagging_array_free(th_flagging_array_t *arr)
{
    if (arr == NULL)
        return;
    if (arr->array)
    {
        pthread_mutex_destroy(&arr->lock.lock);
        pthread_cond_destroy(&arr->lock.high_prio_cond);
        pthread_cond_destroy(&arr->lock.low_prio_cond);
        free(arr->array);
        arr->array = NULL;
    }
    arr->size = 0;
}

