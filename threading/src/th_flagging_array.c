#define MODULE_DEBUG DEBUG_TH_FLAGGING_ARRAY
#include "debug.h"
#include "th_flagging_array.h"

/* TO be called before thread create */
th_flagging_array_status_t th_flagging_array_init(th_flagging_array_t *arr, size_t capcity)
{

    if (!(arr->array = calloc(capcity, sizeof(uint8_t))))
    {
        return TH_FLAGGING_ARRAY_ERR_GENERIC;
    }

    arr->size = capcity;

    return TH_FLAGGING_ARRAY_OK_GENERIC;
}

th_flagging_array_status_t th_flagging_array_init_access(th_flagging_array_access_t *access, th_flagging_array_t *array, th_lock_priority_t priority)
{
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
    if (arr->array)
    {
        free(arr->array);
        arr->array = NULL;
    }
    arr->size = 0;
}

