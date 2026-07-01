#ifndef TH_FLAGGING_ARRAY_H
#define TH_FLAGGING_ARRAY_H

#include <stdint.h>
#include <stdlib.h>
#include "th_lock.h"

typedef struct
{
    size_t size;
    uint8_t *array;
    th_lock_resource_control_t lock;

} th_flagging_array_t;

typedef struct
{
    th_flagging_array_t *array;
    th_lock_resource_access_t access;
} th_flagging_array_access_t;


uint8_t th_flagging_array_init(th_flagging_array_t *arr, size_t capacity);
uint8_t th_flagging_array_init_access(th_flagging_array_access_t *access, th_flagging_array_t *array, th_lock_priority_t priority);
uint8_t th_flagging_array_get(th_flagging_array_access_t *access, size_t idx, uint8_t *ret);
uint8_t th_flagging_array_set(th_flagging_array_access_t *access, size_t idx, uint8_t val);

#endif // TH_FLAGGING_ARRAY_H