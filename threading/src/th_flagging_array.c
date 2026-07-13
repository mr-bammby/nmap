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
    th_lock_init_access(priority, &(access->array->lock), &(access->access));
    return TH_FLAGGING_ARRAY_OK_GENERIC;
}

th_flagging_array_status_t th_flagging_array_get(th_flagging_array_access_t *access, size_t idx, uint8_t *ret)
{
    if (idx >= access->array->size)
    {
        return TH_FLAGGING_ARRAY_ERR_INVALID_PARAM;
    }
    th_lock_take(&(access->access));
    *ret = access->array->array[idx];
    th_lock_release(&(access->access));
    return TH_FLAGGING_ARRAY_OK_GENERIC;
}


th_flagging_array_status_t th_flagging_array_set(th_flagging_array_access_t *access, size_t idx, uint8_t val)
{
    if (idx >= access->array->size)
    {
        return TH_FLAGGING_ARRAY_ERR_INVALID_PARAM;
    }
    th_lock_take(&(access->access));
    access->array->array[idx] = val;
    th_lock_release(&(access->access));
    return TH_FLAGGING_ARRAY_OK_GENERIC;
}

th_flagging_array_status_t th_flagging_array_reset(th_flagging_array_access_t *access)
{
    th_lock_take(&(access->access));
    memset(access->array->array, 0, access->array->size);
    th_lock_release(&(access->access));
    return TH_FLAGGING_ARRAY_OK_GENERIC;
}
