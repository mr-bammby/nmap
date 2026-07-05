// Compile with "gcc -I../inc -g -pthread -o threading.out th_main_queue.c th_lock.c th_queue.c " 
// For debugging function copy debug.h into this folder and run "gcc -I../inc -DDEBUG=1 -g -pthread -o threading.out th_main_queue.c th_lock.c th_queue.c "
#define MODULE_DEBUG DEBUG_TH_MAIN
#include "debug.h"
#include <unistd.h>
#include <stdlib.h>
#include "th_queue.h"

#define NUM_READERS 100

pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;

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
    uint32_t thread_id = (uint32_t)(uintptr_t)arg;
    LOGD("Sender thread %d started\n", thread_id);
    uint8_t ret;
    uint32_t assigned_ticket = 0;
    th_queue_init_access(&queue_access_send_info, &g_queue, TH_LOCK_PRIORITY_LOW);
    sleep(2);
    while (1)
    {
        
        LOGD("Thread %d trying lock\n", thread_id);
        
        uint8_t idx = assigned_ticket % 100;
        
        LOGD("READ head=%zu tail=%zu empty=%d full=%d\n",queue_access_send_info.queue->head, queue_access_send_info.queue->tail, queue_access_send_info.queue->is_empty, queue_access_send_info.queue->is_full);
        
        ret = th_queue_read(&queue_access_send_info, &data, NULL);
        if (ret != 0)
        {
            if (ret = 1)
                LOGW("Thread %d: Queue is empty\n", thread_id);
            else
                LOGW("Thread %d: Error while reading\n", thread_id);
            sleep(1);
            continue;
        }
        assigned_ticket = queue_access_send_info.access.assigned_ticket_number;
        
        LOGI("Thread %d with ticket number %d read port %d and scan type %d from shared resource at index [%d]\n", thread_id, assigned_ticket, data.port_idx, data.scan_idx, data.addrress_idx);
        
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
        data.scan_idx = idx + 2;
        
        LOGD("Before WRITE head=%zu tail=%zu empty=%d full=%d\n", access_send_info.queue->head, access_send_info.queue->tail, access_send_info.queue->is_empty, access_send_info.queue->is_full);
        
        int ret = 1;
        while (ret != 0)
        {
            ret = th_queue_write(&access_send_info, &data);
            if (ret == -2)
            {
                LOGD("Queue is full. Waiting!\n");
                sleep(1);
            }
            usleep(500);
        }
        
        
        LOGD("After WRITE head=%zu tail=%zu empty=%d full=%d\n", access_send_info.queue->head, access_send_info.queue->tail, access_send_info.queue->is_empty, access_send_info.queue->is_full);
        LOGD("WROTE addr=%llu port=%u scan=%u\n", data.addrress_idx, data.port_idx, data.scan_idx);
        
        
        LOGI("Receiver wrote port %d and scan id %d to shared resource at index [%d] with ticket %d \n" , data.port_idx, data.scan_idx, data.addrress_idx, access_send_info.access.assigned_ticket_number);
        
        idx++;
        if (idx == 100)
            idx = 0;
        usleep(100);
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