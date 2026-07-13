#ifndef TH_FLAGGING_ARRAY_H
#define TH_FLAGGING_ARRAY_H

#include <stdint.h>
#include <stdlib.h>
#include "th_lock.h"

typedef struct
{
    size_t size;
    uint8_t *array;
    th_lock_control_t lock;

} th_flagging_array_t;

typedef struct
{
    th_flagging_array_t *array;
    th_lock_access_t access;
} th_flagging_array_access_t;

typedef enum th_flagging_array_status
{
    TH_FLAGGING_ARRAY_OK_GENERIC = 0,
    TH_FLAGGING_ARRAY_ERR_GENERIC = -1,
    TH_FLAGGING_ARRAY_ERR_LOCK = -2,
    TH_FLAGGING_ARRAY_ERR_INVALID_PARAM = -3
} th_flagging_array_status_t;


th_flagging_array_status_t th_flagging_array_init(th_flagging_array_t *arr, size_t capacity);
th_flagging_array_status_t th_flagging_array_init_access(th_flagging_array_access_t *access, th_flagging_array_t *array, th_lock_priority_t priority);
th_flagging_array_status_t th_flagging_array_get(th_flagging_array_access_t *access, size_t idx, uint8_t *ret);
th_flagging_array_status_t th_flagging_array_set(th_flagging_array_access_t *access, size_t idx, uint8_t val);
th_flagging_array_status_t th_flagging_array_reset(th_flagging_array_access_t *access);


#endif // TH_FLAGGING_ARRAY_H