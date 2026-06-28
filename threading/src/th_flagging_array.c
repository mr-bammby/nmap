#include <stdint.h>
#include <stdlib.h>

#define PRIO_LOW 0
#define PRIO_HI 1

#define TH_LOCK_TYPE uint32_t

typedef struct
{
    size_t size;
    uint8_t *array;
    TH_LOCK_TYPE lock;

} th_flagging_array_t;

uint8_t th_flagging_array_init(th_flagging_array_t *arr, size_t capcity)
{

    if (!(arr->array = calloc(capcity, sizeof(uint8_t))))
    {
        return 1;
    }
    if (!(lock_init(&(arr->lock))))
    {
        free (arr->array);
        return 1;
    }
    arr->size = capcity;

    return 0;
}

uint8_t th_flagging_array_get(th_flagging_array_t *arr, size_t idx, uint8_t *ret)
{
    if (idx >= arr->size)
    {
        return 1;
    }
    lock_lock(&(arr->lock), PRIO_HI);
    ret = arr->array[idx];
    lock_unlock(&(arr->lock));
    return 0;
}


uint8_t th_flagging_array_get(th_flagging_array_t *arr, size_t idx, uint8_t val)
{
    if (idx >= arr->size)
    {
        return 1;
    }
    lock_lock(&(arr->lock), PRIO_HI);
    arr->array[idx] = val;
    lock_unlock(&(arr->lock));
    return 0;
}
