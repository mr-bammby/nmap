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

typedef enum {
    RESSOURCE_UDP_FLAG,
    RESSOURCE_PACKET_INFORMATION
} ressource_type_t;

int g_array[100] = {0};

typedef struct ressource_control_s
{
    uint32_t high_prio_total;
    uint32_t high_prio_serving;
    pthread_cond_t high_prio_cond;
    uint32_t low_prio_total;
    uint32_t low_prio_serving;
    pthread_cond_t low_prio_cond;
    pthread_mutex_t assignment_lock;
    pthread_mutex_t ressource_lock;
} ressource_control_t;

typedef struct ressource_access_s
{
    uint32_t assigned_ticket_number;
    priority_t priority;
    ressource_control_t *control;
} ressource_access_t;

ressource_control_t g_udp_flag_ressource = {
    .high_prio_total = 0,
    .high_prio_serving = 0,
    .high_prio_cond = PTHREAD_COND_INITIALIZER,
    .low_prio_total = 0,
    .low_prio_serving = 0,
    .low_prio_cond = PTHREAD_COND_INITIALIZER,
    .assignment_lock = PTHREAD_MUTEX_INITIALIZER,
    .ressource_lock = PTHREAD_MUTEX_INITIALIZER
};

ressource_control_t g_send_information_ressource = {
    .high_prio_total = 0,
    .high_prio_serving = 0,
    .high_prio_cond = PTHREAD_COND_INITIALIZER,
    .low_prio_total = 0,
    .low_prio_serving = 0,
    .low_prio_cond = PTHREAD_COND_INITIALIZER,
    .assignment_lock = PTHREAD_MUTEX_INITIALIZER,
    .ressource_lock = PTHREAD_MUTEX_INITIALIZER
};

static __thread ressource_access_t ressource_access_udp_flag;
static __thread ressource_access_t ressource_access_send_information;

void initialize_ressource_access(priority_t priority, ressource_type_t ressource_type, ressource_access_t *access)
{
    access->assigned_ticket_number = 0;
    access->priority = priority;
    switch(ressource_type)
    {
        case RESSOURCE_UDP_FLAG:
            access->control = &g_udp_flag_ressource;
            break;
        case RESSOURCE_PACKET_INFORMATION:
            access->control = &g_send_information_ressource;
    }
}

void assign_ticket(ressource_access_t *access)
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

void lock_ressource(ressource_access_t *access)
{
    pthread_mutex_lock(&(access->control->ressource_lock));
    if (access->priority == PRIORITY_HIGH)
    {
        while(!(access->assigned_ticket_number == access->control->high_prio_serving))
        {
             pthread_cond_wait(&(access->control->high_prio_cond), &(access->control->ressource_lock));
        }
    }
    else
    {
        while (access->assigned_ticket_number != access->control->low_prio_serving || access->control->high_prio_serving != access->control->high_prio_total)
        {
             pthread_cond_wait(&(access->control->low_prio_cond), &((access->control->ressource_lock)));
        }
    }
    return;
}

void unlock_ressource(ressource_access_t *access)
{
    pthread_cond_broadcast(&(access->control->high_prio_cond));
    pthread_cond_broadcast(&(access->control->low_prio_cond));
    pthread_mutex_unlock(&(access->control->ressource_lock));
}

static void *sender_thread(void *arg)
{
    LOGD("Sender thread started\n");
    (void)arg;

    while (1)
    {
        LOGD("Sender trying lock\n");
        initialize_ressource_access(PRIORITY_LOW, RESSOURCE_UDP_FLAG, &ressource_access_udp_flag);
        assign_ticket(&ressource_access_udp_flag);
        lock_ressource(&ressource_access_udp_flag);
        LOGI("Sender reading %d from shared ressource at index [%d].\n", g_array[ressource_access_udp_flag.assigned_ticket_number % 100], ressource_access_udp_flag.assigned_ticket_number % 100);
        ressource_access_udp_flag.control->low_prio_serving++;
        unlock_ressource(&ressource_access_udp_flag);
        usleep((rand() % 400 + 100) * 1000);
    }
    return NULL;
}

int main(void)
{
    pthread_t readers[NUM_READERS];

    for (int i = 0; i < NUM_READERS; i++)
    {
        if (pthread_create(&readers[i], NULL, sender_thread, NULL) != 0)
        {
            LOGE_ERRNO("pthread_create");
            return 1;
        }
    }

    while (1)
    {
        LOGD("Receiver trying lock\n");
        initialize_ressource_access(PRIORITY_HIGH, RESSOURCE_UDP_FLAG, &ressource_access_udp_flag);
        assign_ticket(&ressource_access_udp_flag);
        lock_ressource(&ressource_access_udp_flag);
        g_array[ressource_access_udp_flag.assigned_ticket_number % 100] = ressource_access_udp_flag.control->high_prio_serving;
        LOGI("Receiver wrote %d to shared ressource at index [%d]\n", g_array[ressource_access_udp_flag.assigned_ticket_number % 100], ressource_access_udp_flag.assigned_ticket_number % 100);
        ressource_access_udp_flag.control->high_prio_serving++;
        unlock_ressource(&ressource_access_udp_flag);

        sleep(1);
    }

    // TODO Termination condition for threads and clean up
    for (int i = 0; i < NUM_READERS; i++)
    {
        pthread_join(readers[i], NULL);
    }

    pthread_mutex_destroy(&(g_udp_flag_ressource.assignment_lock));
    pthread_mutex_destroy(&(g_udp_flag_ressource.ressource_lock));
    pthread_cond_destroy(&(g_udp_flag_ressource.high_prio_cond));
    pthread_cond_destroy(&(g_udp_flag_ressource.low_prio_cond));

    pthread_mutex_destroy(&(g_send_information_ressource.assignment_lock));
    pthread_mutex_destroy(&(g_send_information_ressource.ressource_lock));
    pthread_cond_destroy(&(g_send_information_ressource.high_prio_cond));
    pthread_cond_destroy(&(g_send_information_ressource.low_prio_cond));

    return 0;
}