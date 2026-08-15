#define MODULE_DEBUG DEBUG_TH_LOCK
#include "debug.h"
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include "th_lock.h"


th_lock_status_t th_lock_init_access(th_lock_priority_t priority, th_lock_control_t *control, th_lock_access_t *access)
{
    access->assigned_ticket_number = 0;
    access->priority = priority;
    access->control = control;
    return TH_LOCK_OK_GENERIC;
}

static th_lock_status_t th_assign_ticket(th_lock_access_t *access)
{
    if (access == NULL || access->control == NULL)
    {
        LOGE("Invalid parameter: access or control is NULL\n");
        return TH_LOCK_ERR_INVALID_PARAM;
    }
    int ret = pthread_mutex_lock(&(access->control->assignment_lock));
    if (ret != 0)
    {
        LOGE("Failed to lock assignment mutex with error code %d\n", ret);
        return TH_LOCK_ERR_LOCK;
    }
    if (access->priority == TH_LOCK_PRIORITY_HIGH)
    {
        access->assigned_ticket_number = access->control->high_prio_total;
        access->control->high_prio_total++;
        LOGI("Assigned high prio ticket %ld and total amount of high prio tickets increased to %ld\n", access->assigned_ticket_number, access->control->high_prio_total);
    }
    else
    {
        access->assigned_ticket_number = access->control->low_prio_total;
        access->control->low_prio_total++;
        LOGI("Assigned low prio ticket %ld and total amount of low prio tickets increased to %ld\n", access->assigned_ticket_number , access->control->low_prio_total);
    }
    ret = pthread_mutex_unlock(&(access->control->assignment_lock));
    if (ret != 0)
    {
        LOGE("Failed to unlock assignment mutex with error code %d\n", ret);
        return TH_LOCK_ERR_LOCK;
    }
    return TH_LOCK_OK_GENERIC;
}

th_lock_status_t th_lock_take(th_lock_access_t *access)
{
    th_assign_ticket(access);
    int ret = pthread_mutex_lock(&(access->control->lock));
    if (ret != 0)
    {
        LOGE("Failed to lock main mutex with error code %d\n", ret);
        return TH_LOCK_ERR_LOCK;
    }
    if (access->priority == TH_LOCK_PRIORITY_HIGH)
    {
        while(!(access->assigned_ticket_number == access->control->high_prio_serving))
        {
            ret  = pthread_cond_wait(&(access->control->high_prio_cond), &(access->control->lock));
            if (ret != 0)
            {
                pthread_mutex_unlock(&(access->control->lock));
                LOGE("Failed to wait on high priority condition with error code %d\n", ret);
                return TH_LOCK_ERR_LOCK;
            }
        }
    }
    else
    {
        while (access->assigned_ticket_number != access->control->low_prio_serving || access->control->high_prio_serving != access->control->high_prio_total)
        {
            ret = pthread_cond_wait(&(access->control->low_prio_cond), &(access->control->lock));
            if (ret != 0)
            {
                pthread_mutex_unlock(&(access->control->lock));
                LOGE("Failed to wait on low priority condition with error code %d\n", ret);
                return TH_LOCK_ERR_LOCK;
            }
        }
    }
    return TH_LOCK_OK_GENERIC;
}

th_lock_status_t th_lock_release(th_lock_access_t *access)
{
    if (access->priority == TH_LOCK_PRIORITY_HIGH)
        access->control->high_prio_serving++;
    else
        access->control->low_prio_serving++;
    int ret;
    if ((ret = pthread_cond_broadcast(&(access->control->high_prio_cond))) != 0)
    {
        pthread_mutex_unlock(&(access->control->lock));
        LOGE("Failed to broadcast high priority condition with error code %d\n", ret);
        return TH_LOCK_ERR_LOCK;
    }
    if ((ret = pthread_cond_broadcast(&(access->control->low_prio_cond))) != 0)
    {
        pthread_mutex_unlock(&(access->control->lock));
        LOGE("Failed to broadcast low priority condition with error code %d\n", ret);
        return TH_LOCK_ERR_LOCK;
    }
    if ((ret = pthread_mutex_unlock(&(access->control->lock))) != 0)
    {
        LOGE("Failed to unlock main mutex with error code %d\n", ret);
        return TH_LOCK_ERR_LOCK;
    }
    return TH_LOCK_OK_GENERIC;
}
