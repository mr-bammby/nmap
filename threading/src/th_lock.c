#define MODULE_DEBUG DEBUG_TH_LOCK
#include "debug.h"
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include "th_lock.h"


void th_lock_init_access(th_lock_priority_t priority, th_lock_control_t *control, th_lock_access_t *access)
{
    access->assigned_ticket_number = 0;
    access->priority = priority;
    access->control = control;
}

static void th_assign_ticket(th_lock_access_t *access)
{
    pthread_mutex_lock(&(access->control->assignment_lock));
    if (access->priority == TH_LOCK_PRIORITY_HIGH)
    {
        access->assigned_ticket_number = access->control->high_prio_total;
        access->control->high_prio_total++;
        LOGI("Assigned high prio ticket %d and total amount of high prio tickets increased to %d\n", access->assigned_ticket_number, access->control->high_prio_total);
    }
    else
    {
        access->assigned_ticket_number = access->control->low_prio_total;
        access->control->low_prio_total++;
        LOGI("Assigned low prio ticket %d and total amount of low prio tickets increased to %d\n", access->assigned_ticket_number , access->control->low_prio_total);
    }
    pthread_mutex_unlock(&(access->control->assignment_lock));
}

void th_lock_take(th_lock_access_t *access)
{
    th_assign_ticket(access);
    pthread_mutex_lock(&(access->control->lock));
    if (access->priority == TH_LOCK_PRIORITY_HIGH)
    {
        while(!(access->assigned_ticket_number == access->control->high_prio_serving))
        {
             pthread_cond_wait(&(access->control->high_prio_cond), &(access->control->lock));
        }
    }
    else
    {
        while (access->assigned_ticket_number != access->control->low_prio_serving || access->control->high_prio_serving != access->control->high_prio_total)
        {
             pthread_cond_wait(&(access->control->low_prio_cond), &((access->control->lock)));
        }
    }
    return;
}

void th_lock_release(th_lock_access_t *access)
{
    if (access->priority == TH_LOCK_PRIORITY_HIGH)
        access->control->high_prio_serving++;
    else
        access->control->low_prio_serving++;
    pthread_cond_broadcast(&(access->control->high_prio_cond));
    pthread_cond_broadcast(&(access->control->low_prio_cond));
    pthread_mutex_unlock(&(access->control->lock));
}
