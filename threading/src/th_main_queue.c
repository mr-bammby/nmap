// Compile with "gcc -I../inc -g -pthread -o threading.out th_main_queue.c th_lock.c th_queue.c " 
// For debugging function copy debug.h into this folder and run "gcc -I../inc -DDEBUG=1 -g -pthread -o threading.out th_main_queue.c th_lock.c th_queue.c "
#define MODULE_DEBUG DEBUG_TH_MAIN
#include "debug.h"
#include <unistd.h>
#include <stdlib.h>
#include "th_queue.h"

#define NUM_READERS 100

th_queue_t g_queue = {
    .data = NULL,
    .capacity = 100,
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

static int cond(const TH_QUEUE_DATA_TYPE *data)
{
    return 1;
}


static void *th_sender_thread(void *arg)
{
    TH_QUEUE_DATA_TYPE data = {
        .addrress_idx = 0,
        .port_idx = 0,
        .scan_idx = 0
    };
    th_queue_access_t queue_access_send_info;
    LOGD("Sender thread started\n");
    uint32_t thread_id = (uint32_t)(uintptr_t)arg;
    uint8_t ret;
    uint32_t assigned_ticket;
    th_queue_init_access(&queue_access_send_info, &g_queue, TH_LOCK_PRIORITY_LOW);
    while (1)
    {
        LOGD("Thread %d trying lock\n", thread_id);
        assigned_ticket = queue_access_send_info.access.assigned_ticket_number;
        uint8_t idx = assigned_ticket % 100;
        if (th_queue_read(&queue_access_send_info, &data, &cond) != 0)
        {
            LOGW("Thread %d: Error in getting from arr.", thread_id);
        }
        LOGI("Thread %d with ticket number %d read %d from shared resource at index [%d]\n", thread_id, assigned_ticket, ret, idx);
        usleep((rand() % 400 + 100) * 1000);
    }
    return NULL;
}

int main(void)
{
    pthread_t readers[NUM_READERS];

    th_queue_init(&g_queue, 100);
    
    for (uint32_t i = 0; i < NUM_READERS; i++)
    {
        if (pthread_create(&readers[i], NULL, th_sender_thread, (void *)(uintptr_t)i) != 0)
        {

            return 1;
        }
    }

    TH_QUEUE_DATA_TYPE data;
    th_queue_access_t access_send_info;
    th_queue_init_access(&access_send_info, &g_queue, TH_LOCK_PRIORITY_HIGH);
    int idx = 0;
    while (1)
    {
        data.addrress_idx = idx;
        data.port_idx = idx + 1;
        data.scan_idx = idx % 6;
        
        th_queue_write(&access_send_info, &data);
        LOGI("Receiver wrote XXX to shared resource at index XXX with ticket %d \n" , access_send_info.access.assigned_ticket_number);
        idx++;
        if (idx == 100)
            idx = 99;
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