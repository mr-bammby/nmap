#define MODULE_DEBUG DEBUG_MULTI_THREAD_EXEC
#include "debug.h"
#include "multi_thread_shared.h"
#include <pcap.h>
#include "receiver.h"
#include <stdlib.h>
#include <pthread.h>

th_flagging_array_t *multi_thread_shared_flagging_array = NULL;
th_queue_t multi_thread_shared_cmd_queue = {0};

/* Define the global atomic flags declared in multi_thread_shared.h */
atomic_bool abort_flag = ATOMIC_VAR_INIT(false);
atomic_int thread_counter = ATOMIC_VAR_INIT(0);

struct multi_thread_allocs
{
    uint32_t address_count;

    pthread_t *thread_list;
    multithread_sender_args_t **args;
    uint32_t thread_num;

    addr_hashmap_t hash_map;

    pcap_t *pcap_handle;
    int sock;
    char *local_ip;

};

struct multi_thread_allocs g_multi_thread_allocs = {0, NULL, NULL, 0, {0}, NULL, -1, NULL };


void multi_thread_cleanup(void)
{
    atomic_store(&abort_flag, true);

    if (g_multi_thread_allocs.pcap_handle != NULL)
    {
        receiver_cleanup(g_multi_thread_allocs.pcap_handle);
        g_multi_thread_allocs.pcap_handle = NULL;
    }

    if (g_multi_thread_allocs.local_ip != NULL)
    {
        free(g_multi_thread_allocs.local_ip);
        g_multi_thread_allocs.local_ip = NULL;
    }

    th_queue_free(&multi_thread_shared_cmd_queue);

    if (multi_thread_shared_flagging_array != NULL)
    {
        for (uint32_t i = 0; i < g_multi_thread_allocs.address_count; i++)
        {
            th_flagging_array_free(&multi_thread_shared_flagging_array[i]);
        }
    }

    free(multi_thread_shared_flagging_array);
    multi_thread_shared_flagging_array = NULL;

    addr_hashmap_free(&g_multi_thread_allocs.hash_map);
    if (g_multi_thread_allocs.thread_list != NULL || g_multi_thread_allocs.args != NULL)
    {
        /* Join all sender threads and free per-thread args */
        for (unsigned int th_num = 0; th_num < g_multi_thread_allocs.thread_num; th_num++)
        {
            if (g_multi_thread_allocs.thread_list != NULL && g_multi_thread_allocs.thread_list[th_num] != 0)
            {
                (void)pthread_join(g_multi_thread_allocs.thread_list[th_num], NULL);
                g_multi_thread_allocs.thread_list[th_num] = 0;
            }
            if (g_multi_thread_allocs.args != NULL && g_multi_thread_allocs.args[th_num] != NULL)
            {
                free(g_multi_thread_allocs.args[th_num]);
                g_multi_thread_allocs.args[th_num] = NULL;
            }
        }
        free(g_multi_thread_allocs.args);
        g_multi_thread_allocs.args = NULL;
        free(g_multi_thread_allocs.thread_list);
        g_multi_thread_allocs.thread_list = NULL;
    }
}

uint8_t multi_thread_exec(const argparse_params_t *params, scan_result_t **results, uint32_t results_rows, uint32_t results_cols)
{

    multi_thread_command_queue_state_t queue_state;
    g_multi_thread_allocs.address_count = results_rows;
    g_multi_thread_allocs.thread_num = params->thread_num - 1; // -1 for receiver thread
    g_multi_thread_allocs.args = malloc(sizeof(multithread_sender_args_t *) * g_multi_thread_allocs.thread_num);
    g_multi_thread_allocs.thread_list = (pthread_t *)calloc((size_t)g_multi_thread_allocs.thread_num, sizeof(pthread_t));

    if (g_multi_thread_allocs.args == NULL || g_multi_thread_allocs.thread_list == NULL)
    {
        multi_thread_cleanup();
        LOGE("Failed to allocate memory for thread arguments\n");
        return 1;
    }
    //First entry in queue is special command for sleep 

    if (multi_thread_init(params, &queue_state, results, results_rows, results_cols, &g_multi_thread_allocs.hash_map) != 0)
    {
        multi_thread_cleanup();
        LOGE("Failed to initialize multi-threading\n");
        return 1;
    }
    LOGD("Starting multi-threaded execution with %d threads...\n", params->thread_num);
    uint8_t senders_started = 1;

    size_t count = 0;

    
    uint32_t link_header_len;
    argparse_port_set_iterator_t port_it;
    unsigned int port_i;
    if (senders_started)
    {
        // Initialize receiver handle
        if (multi_thread_receiver_init(params->address, &g_multi_thread_allocs.pcap_handle, &g_multi_thread_allocs.local_ip, &link_header_len) < 0)
        {
            LOGE("Failed to initialize receiver\n");
            return 1;
        }
        LOGI("Receiver handle successfully inititalized\n");

            // Move head of queue to let sender threads start sending
            th_queue_t *cmd_queue = &multi_thread_shared_cmd_queue;
            th_queue_access_t access;
            LOGI("Queue state before initial read: head=%zu tail=%zu is_empty=%u is_full=%u capacity=%zu\n", cmd_queue->head, cmd_queue->tail, cmd_queue->is_empty, cmd_queue->is_full, cmd_queue->capacity);
            th_queue_init_access(&access, cmd_queue, TH_LOCK_PRIORITY_HIGH);
            multi_thread_command_t data;
            th_queue_read(&access, &data, NULL);

            // Now start sender threads (after receiver and initial read to avoid races)
            for (unsigned int th_num = 0; th_num < g_multi_thread_allocs.thread_num; th_num++) // -1 for receiver thread
            {
                g_multi_thread_allocs.args[th_num] = calloc(1, sizeof(multithread_sender_args_t));
                if (g_multi_thread_allocs.args[th_num] == NULL)
                {
                    multi_thread_cleanup();
                    senders_started = 0;
                    LOGE("Failed to allocate memory for thread arguments\n");
                    break;
                }
                g_multi_thread_allocs.args[th_num]->cmd_queue = &multi_thread_shared_cmd_queue;
                g_multi_thread_allocs.args[th_num]->flagging_array = multi_thread_shared_flagging_array;
                g_multi_thread_allocs.args[th_num]->thread_id = th_num;
                g_multi_thread_allocs.args[th_num]->local_ip = inet_addr(g_multi_thread_allocs.local_ip);

                if ( pthread_create(&g_multi_thread_allocs.thread_list[th_num], NULL, multi_thread_sender, (void *)g_multi_thread_allocs.args[th_num]) != 0)
                {
                    LOGE("Failed to create sender thread %d\n", th_num);
                    free(g_multi_thread_allocs.args[th_num]);
                    g_multi_thread_allocs.args[th_num] = NULL;
                    senders_started = 0;
                    atomic_store(&abort_flag, true);
                    break;
                }
            }

        if (multi_thread_receiver_run(g_multi_thread_allocs.pcap_handle, link_header_len, results, &g_multi_thread_allocs.hash_map) != 0)
        {
            LOGE("Receiver encountered an error during execution\n");
            multi_thread_cleanup();
            return 1;
        }
    }
    
    for (unsigned int th_num = 0; th_num < g_multi_thread_allocs.thread_num; th_num++)
    {
        if (g_multi_thread_allocs.args[th_num] != NULL)
        {
            pthread_join(g_multi_thread_allocs.thread_list[th_num], NULL);
            LOGD("Thread %d joined successfully\n", th_num);
            g_multi_thread_allocs.thread_list[th_num] = 0;
            free(g_multi_thread_allocs.args[th_num]);
            g_multi_thread_allocs.args[th_num] = NULL;
        }
    }
    /* Free thread arrays once after joining */
    if (g_multi_thread_allocs.thread_list != NULL)
    {
        free(g_multi_thread_allocs.thread_list);
        g_multi_thread_allocs.thread_list = NULL;
    }
    if (g_multi_thread_allocs.args != NULL)
    {
        free(g_multi_thread_allocs.args);
        g_multi_thread_allocs.args = NULL;
    }
    multi_thread_cleanup();
    return 0;
}