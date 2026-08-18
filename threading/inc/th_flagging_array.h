#ifndef TH_FLAGGING_ARRAY_H
#define TH_FLAGGING_ARRAY_H

#include <stdint.h>
#include <stdlib.h>
#include "th_lock.h"

/* Define the structure for a flagging array. */
typedef struct
{
    size_t size; // The size of the flagging array
    uint8_t *array; // Pointer to the array of flags
    th_lock_control_t lock; // Control structure for managing access to the flagging array

} th_flagging_array_t;

/* Define the access structure for a thread to interact with the flagging array. */
typedef struct
{
    th_flagging_array_t *array; // Pointer to the flagging array structure
    th_lock_access_t access; // Access structure for managing thread access to the flagging array
} th_flagging_array_access_t;

/* Define the status codes for flagging array operations. */
typedef enum th_flagging_array_status
{
    TH_FLAGGING_ARRAY_OK_GENERIC = 0,
    TH_FLAGGING_ARRAY_ERR_GENERIC = -1,
    TH_FLAGGING_ARRAY_ERR_LOCK = -2,
    TH_FLAGGING_ARRAY_ERR_INVALID_PARAM = -3
} th_flagging_array_status_t;

/* Initialize a flagging array with the specified capacity. */
th_flagging_array_status_t th_flagging_array_init(th_flagging_array_t *arr, size_t capacity);

/* Initialize a flagging array access structure. */
th_flagging_array_status_t th_flagging_array_init_access(th_flagging_array_access_t *access, th_flagging_array_t *array, th_lock_priority_t priority);

/* Get the value of a flag at the specified index in the flagging array. */
th_flagging_array_status_t th_flagging_array_get(th_flagging_array_access_t *access, size_t idx, uint8_t *ret);

/* Set the value of a flag at the specified index in the flagging array. */
th_flagging_array_status_t th_flagging_array_set(th_flagging_array_access_t *access, size_t idx, uint8_t val);

/* Reset all flags in the flagging array. */
th_flagging_array_status_t th_flagging_array_reset(th_flagging_array_access_t *access);

/* Free resources held by the flagging array. */
void th_flagging_array_free(th_flagging_array_t *arr);

#endif /* TH_FLAGGING_ARRAY_H */