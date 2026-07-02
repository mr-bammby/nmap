// Compile with "gcc -I../inc -g -pthread -o threading.out th_main.c th_lock.c th_flagging_array.c " 
// For debugging function copy debug.h into this folder and run "gcc -I../inc -DDEBUG=1 -g -pthread -o threading.out th_main.c th_lock.c th_flagging_array.c "
#define MODULE_DEBUG DEBUG_TH_MAIN
#include "debug.h"
#include <unistd.h>
#include <stdlib.h>
#include "th_flagging_array.h"

#define NUM_READERS 100

th_flagging_array_t g_flagging_array = {
    .size = 100,
    .array = NULL,
    .lock = {
        .high_prio_total = 0,
        .high_prio_serving = 0,
        .high_prio_cond = PTHREAD_COND_INITIALIZER,
        .low_prio_total = 0,
        .low_prio_serving = 0,
        .low_prio_cond = PTHREAD_COND_INITIALIZER,
        .assignment_lock = PTHREAD_MUTEX_INITIALIZER,
        .lock = PTHREAD_MUTEX_INITIALIZER
    }
};

static void *th_sender_thread(void *arg)
{
    th_flagging_array_access_t arr_access_udp_flag;
    LOGD("Sender thread started\n");
    (void)arg;
    uint8_t ret;

    while (1)
    {
        LOGD("Sender trying lock\n");
        th_flagging_array_init_access(&arr_access_udp_flag, &g_flagging_array, TH_LOCK_PRIORITY_LOW);
        uint32_t assigned_ticket = arr_access_udp_flag.access.assigned_ticket_number;
        uint8_t idx = assigned_ticket % 100;
        th_flagging_array_get(&arr_access_udp_flag, idx, &ret);
        LOGI("Sender with ticket number %d read %d from shared resource at index [%d]\n", assigned_ticket, ret, idx);
        usleep((rand() % 400 + 100) * 1000);
    }
    return NULL;
}

int main(void)
{
    pthread_t readers[NUM_READERS];

    th_flagging_array_init(&g_flagging_array, 100);
    
    for (int i = 0; i < NUM_READERS; i++)
    {
        if (pthread_create(&readers[i], NULL, th_sender_thread, NULL) != 0)
        {

            return 1;
        }
    }

    th_flagging_array_access_t access_udp_flag;
    while (1)
    {
        LOGD("Receiver trying lock\n");
        uint8_t idx = access_udp_flag.access.assigned_ticket_number % 100;
        uint8_t val = access_udp_flag.access.assigned_ticket_number % 100;
        th_flagging_array_init_access(&access_udp_flag, &g_flagging_array, TH_LOCK_PRIORITY_HIGH);
        th_flagging_array_set(&access_udp_flag, idx, val);
        LOGI("Receiver wrote %d to shared resource at index [%d]\n", val, idx);


        sleep(1);
    }

    // TODO Termination condition for threads and clean up
    for (int i = 0; i < NUM_READERS; i++)
    {
        pthread_join(readers[i], NULL);
    }

    // pthread_mutex_destroy(&(g_udp_flag_resource.assignment_lock));
    // pthread_mutex_destroy(&(g_udp_flag_resource.lock));
    // pthread_cond_destroy(&(g_udp_flag_resource.high_prio_cond));
    // pthread_cond_destroy(&(g_udp_flag_resource.low_prio_cond));

    // pthread_mutex_destroy(&(g_send_information_resource.assignment_lock));
    // pthread_mutex_destroy(&(g_send_information_resource.lock));
    // pthread_cond_destroy(&(g_send_information_resource.high_prio_cond));
    // pthread_cond_destroy(&(g_send_information_resource.low_prio_cond));

    return 0;
}