#define MODULE_DEBUG DEBUG_MULTI_THREAD_EXEC
#include "debug.h"
#include "multi_thread_shared.h"
#include <pcap.h>
#include "receiver.h"
#include <stdlib.h>
#include <pthread.h>


atomic_bool abort_flag = false;

th_queue_t multi_thread_shared_cmd_queue = {0};
th_flagging_array_t *multi_thread_shared_flagging_array;


void multi_thread_exec(const argparse_params_t *params, scan_result_t **results, uint32_t results_rows, uint32_t results_cols)
{
    multi_thread_command_queue_state_t queue_state;
    multithread_sender_args_t **args = malloc(sizeof(multithread_sender_args_t *) * (params->thread_num - 1)); // -1 for receiver thread
    pthread_t *thread_list = (pthread_t *)calloc((size_t)params->thread_num - 1, sizeof(pthread_t));

    if (args == NULL || thread_list == NULL)
    {
        free(args);
        free(thread_list);
        LOGE("Failed to allocate memory for thread arguments\n");
        return;
    }
    //First entry in queue is special command for sleep 

    if (multi_thread_init(params, &queue_state, results, results_rows, results_cols) != 0)
    {
        free(args);
        free(thread_list);
        LOGE("Failed to initialize multi-threading\n");
        return;
    }
    LOGD("Starting multi-threaded execution with %d threads...\n", params->thread_num);
    uint8_t senders_started = 1;
    for (unsigned int th_num = 0; th_num < (params->thread_num - 1); th_num++) // -1 for receiver thread
    {
        args[th_num] = malloc(sizeof(multithread_sender_args_t));
        if (args[th_num] == NULL)
        {
            atomic_store(&abort_flag, true);
            senders_started = 0;
            LOGE("Failed to allocate memory for thread arguments\n");
            break;
        }
        args[th_num]->cmd_queue = &multi_thread_shared_cmd_queue;
        args[th_num]->flagging_array = multi_thread_shared_flagging_array;
        args[th_num]->thread_id = th_num;

        if ( pthread_create(&thread_list[th_num], NULL, multi_thread_sender, (void *)args[th_num]) != 0)
        {
            LOGE("Failed to create sender thread %d\n", th_num);
            free(args[th_num]);
            args[th_num] = NULL;
            senders_started = 0;
            atomic_store(&abort_flag, true);
            break;
        }
    }
    if (senders_started)
    {
        multi_thread_receiver_run(params, &queue_state, *results, results_rows, results_cols);
    }
    for (unsigned int th_num = 0; th_num < (params->thread_num - 1); th_num++)
    {
        if (args[th_num] != NULL)
        {
            pthread_join(thread_list[th_num], NULL);
            LOGD("Thread %d joined successfully\n", th_num);
            free(args[th_num]);
        }
    }
    free(args);
    free(thread_list);
}