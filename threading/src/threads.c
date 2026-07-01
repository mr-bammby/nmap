#define MODULE_DEBUG DEBUG_THREADS
#include "debug.h"
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

// Compile with "gcc -g -pthread -o threading.out threads.c" 
// For debugging function copy debug.h into this folder and run "gcc -DDEBUG=1 -g -pthread -o threading.out threads.c"

#define NUM_READERS 100

typedef enum {
    PRIORITY_HIGH,
    PRIORITY_LOW
} priority_t;

int g_array[100] = {0};

typedef struct resource_control_s
{
    uint32_t high_prio_total;
    uint32_t high_prio_serving;
    pthread_cond_t high_prio_cond;
    uint32_t low_prio_total;
    uint32_t low_prio_serving;
    pthread_cond_t low_prio_cond;
    pthread_mutex_t assignment_lock;
    pthread_mutex_t resource_lock;
} resource_control_t;

typedef struct resource_access_s
{
    uint32_t assigned_ticket_number;
    priority_t priority;
    resource_control_t *control;
} resource_access_t;

resource_control_t g_udp_flag_resource = {
    .high_prio_total = 0,
    .high_prio_serving = 0,
    .high_prio_cond = PTHREAD_COND_INITIALIZER,
    .low_prio_total = 0,
    .low_prio_serving = 0,
    .low_prio_cond = PTHREAD_COND_INITIALIZER,
    .assignment_lock = PTHREAD_MUTEX_INITIALIZER,
    .resource_lock = PTHREAD_MUTEX_INITIALIZER
};

resource_control_t g_send_information_resource = {
    .high_prio_total = 0,
    .high_prio_serving = 0,
    .high_prio_cond = PTHREAD_COND_INITIALIZER,
    .low_prio_total = 0,
    .low_prio_serving = 0,
    .low_prio_cond = PTHREAD_COND_INITIALIZER,
    .assignment_lock = PTHREAD_MUTEX_INITIALIZER,
    .resource_lock = PTHREAD_MUTEX_INITIALIZER
};

void th_lock_init_access(priority_t priority, resource_control_t *resource, resource_access_t *access)
{
    access->assigned_ticket_number = 0;
    access->priority = priority;
    access->control = resource;
}

void th_assign_ticket(resource_access_t *access)
{
    pthread_mutex_lock(&(access->control->assignment_lock));
    if (access->priority == PRIORITY_HIGH)
    {
        access->assigned_ticket_number = access->control->high_prio_total;
        access->control->high_prio_total++;
        LOGI("Total amount of high prio tickets increase to %d\n", access->control->high_prio_total);
    }
    else
    {
        access->assigned_ticket_number = access->control->low_prio_total;
        access->control->low_prio_total++;
        LOGI("Total amount of low prio tickets increase to %d\n", access->control->low_prio_total);
    }
    pthread_mutex_unlock(&(access->control->assignment_lock));
}

void th_lock_take(resource_access_t *access)
{
    th_assign_ticket(access);
    pthread_mutex_lock(&(access->control->resource_lock));
    if (access->priority == PRIORITY_HIGH)
    {
        while(!(access->assigned_ticket_number == access->control->high_prio_serving))
        {
             pthread_cond_wait(&(access->control->high_prio_cond), &(access->control->resource_lock));
        }
    }
    else
    {
        while (access->assigned_ticket_number != access->control->low_prio_serving || access->control->high_prio_serving != access->control->high_prio_total)
        {
             pthread_cond_wait(&(access->control->low_prio_cond), &((access->control->resource_lock)));
        }
    }
    return;
}

void th_lock_release(resource_access_t *access)
{
    if (access->priority == PRIORITY_HIGH)
        access->control->high_prio_serving++;
    else
        access->control->low_prio_serving++;
    pthread_cond_broadcast(&(access->control->high_prio_cond));
    pthread_cond_broadcast(&(access->control->low_prio_cond));
    pthread_mutex_unlock(&(access->control->resource_lock));
}

static void *th_sender_thread(void *arg)
{
    resource_access_t resource_access_udp_flag;
    LOGD("Sender thread started\n");
    (void)arg;

    while (1)
    {
        LOGD("Sender trying lock\n");
        th_lock_init_access(PRIORITY_LOW, &g_udp_flag_resource, &resource_access_udp_flag);

        th_lock_take(&resource_access_udp_flag);
        LOGI("Sender reading %d from shared resource at index [%d].\n", g_array[resource_access_udp_flag.assigned_ticket_number % 100], resource_access_udp_flag.assigned_ticket_number % 100);
        th_lock_release(&resource_access_udp_flag);
        usleep((rand() % 400 + 100) * 1000);
    }
    return NULL;
}

int main(void)
{
    pthread_t readers[NUM_READERS];

    for (int i = 0; i < NUM_READERS; i++)
    {
        if (pthread_create(&readers[i], NULL, th_sender_thread, NULL) != 0)
        {
            LOGE_ERRNO("pthread_create");
            return 1;
        }
    }

    resource_access_t resource_access_udp_flag;
    while (1)
    {
        LOGD("Receiver trying lock\n");
        th_lock_init_access(PRIORITY_HIGH, &g_udp_flag_resource, &resource_access_udp_flag);
        th_lock_take(&resource_access_udp_flag);
        g_array[resource_access_udp_flag.assigned_ticket_number % 100] = resource_access_udp_flag.control->high_prio_serving;
        LOGI("Receiver wrote %d to shared resource at index [%d]\n", g_array[resource_access_udp_flag.assigned_ticket_number % 100], resource_access_udp_flag.assigned_ticket_number % 100);
        th_lock_release(&resource_access_udp_flag);

        sleep(1);
    }

    // TODO Termination condition for threads and clean up
    for (int i = 0; i < NUM_READERS; i++)
    {
        pthread_join(readers[i], NULL);
    }

    pthread_mutex_destroy(&(g_udp_flag_resource.assignment_lock));
    pthread_mutex_destroy(&(g_udp_flag_resource.resource_lock));
    pthread_cond_destroy(&(g_udp_flag_resource.high_prio_cond));
    pthread_cond_destroy(&(g_udp_flag_resource.low_prio_cond));

    pthread_mutex_destroy(&(g_send_information_resource.assignment_lock));
    pthread_mutex_destroy(&(g_send_information_resource.resource_lock));
    pthread_cond_destroy(&(g_send_information_resource.high_prio_cond));
    pthread_cond_destroy(&(g_send_information_resource.low_prio_cond));

    return 0;
}