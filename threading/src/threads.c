#define MODULE_DEBUG DEBUG_THREADS
#include "debug.h"
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>

// Compile with "gcc -g -pthread -o threading.out threads.c" 
// For debugging function copy debug.h into this folder and run "gcc -DDEBUG=1 -g -pthread -o threading.out threads.c"

#define NUM_READERS 4

//TODO Make enums
#define HIGH_PRIORITY   1
#define LOW_PRIORITY    0

//TODO Make enums
#define UDP_FLAG_RESSOURCE 1
#define SEND_INFORMATION_RESSOURCE 2

int g_array[100] = {0};

typedef struct ticket_system_s
{
    uint32_t high_prio_count;
    uint32_t high_prio_actual;
    pthread_cond_t high_prio_cond;
    uint32_t low_prio_count;
    uint32_t low_prio_actual;
    pthread_cond_t low_prio_cond;
    pthread_mutex_t assignment_lock;
    pthread_mutex_t ressource_lock;
} ticket_system_t;

ticket_system_t g_udp_flag_ressource = {
    .high_prio_count = 0,
    .high_prio_actual = 0,
    .high_prio_cond = PTHREAD_COND_INITIALIZER,
    .low_prio_count = 0,
    .low_prio_actual = 0,
    .low_prio_cond = PTHREAD_COND_INITIALIZER,
    .assignment_lock = PTHREAD_MUTEX_INITIALIZER,
    .ressource_lock = PTHREAD_MUTEX_INITIALIZER
};

ticket_system_t g_send_information_ressource = {
    .high_prio_count = 0,
    .high_prio_actual = 0,
    .high_prio_cond = PTHREAD_COND_INITIALIZER,
    .low_prio_count = 0,
    .low_prio_actual = 0,
    .low_prio_cond = PTHREAD_COND_INITIALIZER,
    .assignment_lock = PTHREAD_MUTEX_INITIALIZER,
    .ressource_lock = PTHREAD_MUTEX_INITIALIZER
};

void lock_lock(uint8_t priority, uint8_t ressource_type)
{
    uint32_t ticket = 0;
    ticket_system_t *ressource;
    if (ressource_type == UDP_FLAG_RESSOURCE)
        ressource = &g_udp_flag_ressource;
    else
        ressource = &g_send_information_ressource;
    pthread_mutex_lock(&(ressource->assignment_lock));
    if (priority == HIGH_PRIORITY)
    {
        ticket = ressource->high_prio_count;
        ressource->high_prio_count++;
        LOGI("High counter increase to %d\n", ressource->high_prio_count);
    }
    else
    {
        ticket = ressource->low_prio_count;
        ressource->low_prio_count++;
        LOGI("Low counter increase to %d\n", ressource->low_prio_count);
    }
    pthread_mutex_unlock(&(ressource->assignment_lock));

    pthread_mutex_lock(&(ressource->ressource_lock));
    if (priority == HIGH_PRIORITY)
    {
        while(!(ticket == ressource->high_prio_actual))
        {
             pthread_cond_wait(&(ressource->high_prio_cond), &(ressource->ressource_lock));
        }
        g_array[ticket % 100] = ressource->high_prio_actual;
        LOGI("Wrote %d to shared ressource at index [%d]\n", g_array[ticket % 100], ticket % 100);
        ressource->high_prio_actual++;
        //TODO as both conditions need to be broadcast, check if one cond would be sufficient
        pthread_cond_broadcast(&ressource->high_prio_cond);
        pthread_cond_broadcast(&ressource->low_prio_cond);
        pthread_mutex_unlock(&(ressource->ressource_lock));
    }
    else
    {
        while (ticket != ressource->low_prio_actual || ressource->high_prio_actual != ressource->high_prio_count)
        {
             pthread_cond_wait(&(ressource->low_prio_cond), &(ressource->ressource_lock));
        }
        LOGI("Reading %d from shared ressource at index [%d].\n", g_array[ticket % 100], ticket % 100);
        ressource->low_prio_actual++;
        pthread_cond_broadcast(&ressource->high_prio_cond);
        pthread_cond_broadcast(&ressource->low_prio_cond);
        pthread_mutex_unlock(&(ressource->ressource_lock));
    }
}

void unlock_lock()
{
    //TODO: Implement unlock function
}

static void *reader_thread(void *arg)
{
    LOGD("Reader thread started\n");
    (void)arg;

    while (1)
    {
        LOGD("Reader trying lock\n");
        lock_lock(LOW_PRIORITY, UDP_FLAG_RESSOURCE);

        usleep(1000);
    }

    return NULL;
}

int main(void)
{
    pthread_t readers[NUM_READERS];

    for (int i = 0; i < NUM_READERS; i++)
    {
        if (pthread_create(&readers[i], NULL, reader_thread, NULL) != 0)
        {
            LOGE_ERRNO("pthread_create");
            return 1;
        }
    }

    while (1)
    {
        LOGD("Writer trying lock\n");
        lock_lock(HIGH_PRIORITY, UDP_FLAG_RESSOURCE);

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