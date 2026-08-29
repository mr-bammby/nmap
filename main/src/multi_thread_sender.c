#define MODULE_DEBUG DEBUG_MULTI_THREAD_SENDER
#include "debug.h"
#include "multi_thread_shared_res.h"
#include "multi_thread.h"
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "th_queue.h"
#include <pcap.h>
#include <ifaddrs.h>
#include "scan_defines.h"
#include "protocol_udp.h"

#include "sender.h"

#define MAX_ERR_COUNT 10
#define SLEEP_ERR_S 1
#define SLEEP_EXIT_S 0
#define SLEEP_TCP_S 0
#define SLEEP_UDP_S 10
#define SLEEP_ERR_NS 0
#define SLEEP_EXIT_NS 110000000
#define SLEEP_TCP_NS 12000
#define SLEEP_UDP_NS 1000000

#define THREAD_EXIT(retval) do { sender_cleanup(&sock); atomic_fetch_add(&thread_counter, -1); return (retval); } while(0)

int is_normal_cmd(const TH_QUEUE_DATA_TYPE * data_ptr)
{
    if (data_ptr == NULL)
        return 0;
    if (data_ptr->scan & 0x80) // Check if the highest bit of scan is set
        return 0;
    return 1;
}

void *multi_thread_sender(void *arg)
{
    multithread_sender_args_t *args = (multithread_sender_args_t *)arg;
    th_queue_t *cmd_queue = args->cmd_queue;
    th_flagging_array_t *flagging_array = args->flagging_array;
    uint16_t thread_id = args->thread_id;
    uint32_t local_ip = args->local_ip;
    int sock = -1;
    th_queue_access_t access;
    th_flagging_array_access_t flag_arr;
    int err_cnt = 0;
    struct timespec req_err, req_exit, req_tcp, req_udp;

#if MODULE_DEBUG
                char target_addr_str[INET_ADDRSTRLEN];
                struct in_addr target_addr;
    #endif
    req_err.tv_sec = SLEEP_ERR_S;
    req_err.tv_nsec = SLEEP_ERR_NS;
    req_exit.tv_sec = SLEEP_EXIT_S;
    req_exit.tv_nsec = SLEEP_EXIT_NS;
    req_tcp.tv_sec = SLEEP_TCP_S;
    req_tcp.tv_nsec = SLEEP_TCP_NS;
    req_udp.tv_sec = SLEEP_UDP_S;
    req_udp.tv_nsec = SLEEP_UDP_NS;

    LOGD("Thread %d: Starting sender thread\n", thread_id);
    atomic_fetch_add(&thread_counter, 1);
    if (sender_init(&sock) < 0)
    {
        LOGE("Thread %d: Failed to initialize sender socket, exiting thread\n", thread_id);
        sender_cleanup(&sock);
        atomic_fetch_add(&thread_counter, -1);
        return (void *)-1;
    }
    LOGD("Thread %d: Sender socket initialized\n", thread_id);
    /* Helper to cleanup socket and decrement thread counter before exiting */

    th_queue_init_access(&access, cmd_queue, TH_LOCK_PRIORITY_LOW);
    LOGD("Thread %d: Sender thread initialized and ready to process commands\n", thread_id);
    while (1)
    {
        if (atomic_load(&abort_flag))
        {
            LOGE("Thread %d: Abort flag set, exiting thread\n", thread_id);
            THREAD_EXIT((void *)-1);
        }
        if (err_cnt > MAX_ERR_COUNT)
        {
            LOGE("Thread %d: Exceeded maximum error count, exiting thread\n", thread_id);
            THREAD_EXIT((void *)-1);
        }
        TH_QUEUE_DATA_TYPE cmd;
        th_queue_status_t status;

        status = th_queue_read(&access, &cmd, is_normal_cmd);
        LOGD("Thread %d: th_queue_read status=%d\n", thread_id, status);
        switch (status)
        {
            case TH_QUEUE_OK_GENERIC:
                err_cnt = 0; // Reset error count on successful read
                if (cmd.scan == SCAN_FLG_UDP)
                {
                    th_flagging_array_init_access(&flag_arr, &(flagging_array[cmd.udp_flag_row_idx]), TH_LOCK_PRIORITY_LOW);
                }

#if MODULE_DEBUG
                target_addr.s_addr = cmd.address;
                inet_ntop(AF_INET, &target_addr, target_addr_str, sizeof(target_addr_str));
                LOGD("Thread %d: Received command: address=%s, port=%d, flag_arr_idx=%d, scan=%d\n", thread_id, target_addr_str, cmd.port, cmd.udp_flag_arr_idx, cmd.scan);
#endif
                for (int probe = 0; probe < ((cmd.scan == SCAN_FLG_UDP) ? PROTOCOL_UDP_TOTAL_PROBES : 1); probe++)
                {
                    sender_run(sock, cmd.address, cmd.port, local_ip, cmd.scan, probe, NULL);
                    struct timespec *sleep_time = (cmd.scan == SCAN_FLG_UDP) ? &req_udp : &req_tcp;
                    if (nanosleep(sleep_time, NULL) != 0) // Sleep for a short duration to avoid overwhelming the network
                    {
                        LOGE("Thread %d: nanosleep interrupted while waiting for next command\n", thread_id);
                        THREAD_EXIT((void *)-2);
                    }
                    if (atomic_load(&abort_flag))
                    {
                        LOGE("Thread %d: Abort flag set, exiting thread\n", thread_id);
                        THREAD_EXIT((void *)-1);
                    }

                    if (cmd.scan == SCAN_FLG_UDP)
                    {
                        uint8_t udp_flag = 0;
                        th_flagging_array_get(&flag_arr, cmd.udp_flag_arr_idx, &udp_flag); // Check if the UDP flag has been set
                        if (udp_flag)
                        {
                            char done_addr_str[INET_ADDRSTRLEN];
                            struct in_addr done_target_addr = { .s_addr = cmd.address };
                            inet_ntop(AF_INET, &done_target_addr, done_addr_str, sizeof(done_addr_str));
                            LOGD("Thread %d: UDP response received for address=%s, port=%d, stopping further probes\n", thread_id, done_addr_str, cmd.port);
                            break;
                        }
                    }
                }
                break;
            case TH_QUEUE_OK_EMPTY_AFTER_ACCEPT:
                err_cnt = 0; // Reset error count on successful read
                if (cmd.scan == SCAN_FLG_UDP)
                {
                    th_flagging_array_init_access(&flag_arr, &(flagging_array[cmd.udp_flag_row_idx]), TH_LOCK_PRIORITY_LOW);
                }

#if MODULE_DEBUG
                target_addr.s_addr = cmd.address;
                inet_ntop(AF_INET, &target_addr, target_addr_str, sizeof(target_addr_str));
                LOGD("Thread %d: Received command: address=%s, port=%d, flag_arr_idx=%d, scan=%d\n", thread_id, target_addr_str, cmd.port, cmd.udp_flag_arr_idx, cmd.scan);
#endif
                for (int probe = 0; probe < ((cmd.scan == SCAN_FLG_UDP) ? PROTOCOL_UDP_TOTAL_PROBES : 1); probe++)
                {
                    sender_run(sock, cmd.address, cmd.port, local_ip, cmd.scan, probe, NULL);
                    struct timespec *sleep_time = (cmd.scan == SCAN_FLG_UDP) ? &req_udp : &req_tcp;
                    if (nanosleep(sleep_time, NULL) != 0) // Sleep for a short duration to avoid overwhelming the network
                    {
                        LOGE("Thread %d: nanosleep interrupted while waiting for next command\n", thread_id);
                        THREAD_EXIT((void *)-2);
                    }
                    if (atomic_load(&abort_flag))
                    {
                        LOGE("Thread %d: Abort flag set, exiting thread\n", thread_id);
                        THREAD_EXIT((void *)-1);
                    }

                    if (cmd.scan == SCAN_FLG_UDP)
                    {
                        uint8_t udp_flag = 0;
                        th_flagging_array_get(&flag_arr, cmd.udp_flag_arr_idx, &udp_flag); // Check if the UDP flag has been set
                        if (udp_flag)
                        {
                            char done_addr_str[INET_ADDRSTRLEN];
                            struct in_addr done_target_addr = { .s_addr = cmd.address };
                            inet_ntop(AF_INET, &done_target_addr, done_addr_str, sizeof(done_addr_str));
                            LOGD("Thread %d: UDP response received for address=%s, port=%d, stopping further probes\n", thread_id, done_addr_str, cmd.port);
                            break;
                        }
                    }
                }
                if(nanosleep(&req_err, NULL) != 0)
                {
                    LOGE("Thread %d: nanosleep interrupted while waiting for next command\n", thread_id);
                    THREAD_EXIT((void *)-2);
                }
                break;
            case TH_QUEUE_OK_CONDITION_REJECTED:
                if (cmd.scan == MULTI_TH_SP_CMD_SKIP) // Check if the highest bit of scan is set
                {
                    LOGD("Thread %d: Received skip command, waiting for next command\n", thread_id);
                    if(nanosleep(&req_err, NULL) != 0)
                    {
                        LOGE("Thread %d: nanosleep interrupted while waiting for next command\n", thread_id);
                        THREAD_EXIT((void *)-2);
                    }
                    err_cnt++;
                    continue;
                }
                else if (cmd.scan == MULTI_TH_SP_CMD_END)
                {
                    LOGD("Thread %d: Received end command, exiting thread\n", thread_id);
                    if(nanosleep(&req_exit, NULL) != 0)
                    {
                        LOGE("Thread %d: nanosleep interrupted while waiting to exit\n", thread_id);
                        THREAD_EXIT((void *)-2);
                    }
                    THREAD_EXIT(NULL);
                }
                else
                {
                    LOGE("Thread %d: Unexpected command received %d\n", thread_id, cmd.scan);
                    if(nanosleep(&req_err, NULL) != 0)
                    {
                        LOGE("Thread %d: nanosleep interrupted while waiting for next command\n", thread_id);
                        THREAD_EXIT((void *)-2);
                    }
                    err_cnt++;
                    continue;
                }
                break;
            default:
                LOGE("Thread %d: Error reading from queue, status=%d\n", thread_id, status);
                if(nanosleep(&req_err, NULL) != 0)
                {
                    LOGE("Thread %d: nanosleep interrupted while waiting for next command\n", thread_id);
                    THREAD_EXIT((void *)-2);
                }
                err_cnt++;
                break;
        }
    }

    sender_cleanup(&sock);
    if (atomic_fetch_add(&thread_counter, -1))
    {
        LOGE("Thread %d: Abort flag set, exiting thread\n", thread_id);
        return (void *)-1; // Exit the thread if abort flag is set
    }

    return NULL; // Return NULL when the thread is done
}
