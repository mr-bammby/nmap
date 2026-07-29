#define MODULE_DEBUG DEBUG_MULTI_THREAD_SENDER
#include "debug.h"
#include "multi_thread_shared.h"
#include <pthread.h>
#include <time.h>
#include "th_queue.h"
#include <pcap.h>
#include <ifaddrs.h>

#include "sender.h"

#define MAX_ERR_COUNT 10
#define SLEEP_ERR_S 1
#define SLEEP_EXIT_S 3
#define SLEEP_ERR_NS 0
#define SLEEP_EXIT_NS 0

// --- Helper: Get Local IP for Checksum ---
static char* get_local_ip(const char *iface_name)
{
    struct ifaddrs *ifaddr, *ifa;
    static char ip_addr[INET_ADDRSTRLEN];

    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
        return NULL;
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr == NULL) continue;
        if (ifa->ifa_addr->sa_family == AF_INET)
        {
            if (strcmp(ifa->ifa_name, iface_name) == 0)
            {
                struct sockaddr_in *sa = (struct sockaddr_in *)ifa->ifa_addr;
                strcpy(ip_addr, inet_ntoa(sa->sin_addr));
                freeifaddrs(ifaddr);
                return ip_addr;
            }
        }
    }
    freeifaddrs(ifaddr);
    return NULL;
}

char *get_local_ip_sender(void)
{
    pcap_if_t *alldevs;
    char errbuf[PCAP_ERRBUF_SIZE];
    const char *device_name;

    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        LOGE("Error finding devices: %s\n", errbuf);
        return NULL;
    }

    if (alldevs == NULL)
    {
        LOGE("No devices found\n");
        return NULL;
    }

    device_name = alldevs->name;
    LOGD("Using device: %s\n", device_name);

    // Get the IP for this specific device
    char *local_ip = get_local_ip(device_name);
    if (!local_ip)
    {
        LOGE("Could not find IP for %s\n", device_name);
        return NULL;
    }
    LOGD("Using Local IP: %s\n", local_ip);
    return local_ip;
}

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
    int sock;
    th_queue_access_t access;
    int err_cnt = 0;
    struct timespec req_err, req_exit;
    char *local_ip = get_local_ip_sender();

    req_err.tv_sec = SLEEP_ERR_S;
    req_err.tv_nsec = SLEEP_ERR_NS;
    req_exit.tv_sec = SLEEP_EXIT_S;
    req_exit.tv_nsec = SLEEP_EXIT_NS;

    LOGD("Thread %d: Starting sender thread\n", thread_id);
    sender_init(&sock);
    LOGD("Thread %d: Sender socket initialized\n", thread_id);
    th_queue_init_access(&access, cmd_queue, TH_LOCK_PRIORITY_LOW);
    LOGD("Thread %d: Sender thread initialized and ready to process commands\n", thread_id);
    while (1)
    {
        if (atomic_load(&abort_flag))
        {
            LOGE("Thread %d: Abort flag set, exiting thread\n", thread_id);
            sender_cleanup(&sock);
            return (void *)-1; // Exit the thread if abort flag is set
        }
        if (err_cnt > MAX_ERR_COUNT)
        {
            LOGE("Thread %d: Exceeded maximum error count, exiting thread\n", thread_id);
            sender_cleanup(&sock);
            return (void *)-1; // Exit the thread if too many errors occur
        }
        TH_QUEUE_DATA_TYPE cmd;
        th_queue_status_t status;
        status = th_queue_read(&access, &cmd, is_normal_cmd);
        switch (status)
        {
            case TH_QUEUE_OK_GENERIC:
                LOGD("Thread %d: Received command: address=%s, port=%d, flag_arr_idx=%d, scan=%d\n", thread_id, cmd.address, cmd.port, cmd.udp_flag_arr_idx, cmd.scan);
                sender_run(sock, cmd.address, cmd.port, local_ip, cmd.scan, 0, NULL); //to do figure out UDP
                break;
            case TH_QUEUE_OK_EMPTY_AFTER_ACCEPT:
                LOGD("Thread %d: Queue is empty after accepting command, waiting for next command\n", thread_id);
                sender_run(sock, cmd.address, cmd.port, local_ip, cmd.scan, 0, NULL); //to do figure out UDP
                if(nanosleep(&req_err, NULL) != 0)
                {
                    LOGE("Thread %d: nanosleep interrupted while waiting for next command\n", thread_id);
                    return (-2); // Exit the thread if nanosleep is interrupted
                }
                continue;
                break;
            case TH_QUEUE_OK_CONDITION_REJECTED:
                if (cmd.scan == MULTI_TH_SP_CMD_SKIP) // Check if the highest bit of scan is set
                {
                    LOGD("Thread %d: Received skip command, waiting for next command\n", thread_id);
                    if(nanosleep(&req_err, NULL) != 0)
                    {
                        LOGE("Thread %d: nanosleep interrupted while waiting for next command\n", thread_id);
                        return (-2); // Exit the thread if nanosleep is interrupted
                    }
                    #ifdef MULTITHREAD_SENDER_TEST_MODE
                        err_cnt++;
                    #endif /* MULTITHREAD_SENDER_TEST_MODE */
                    continue;
                }
                else if (cmd.scan == MULTI_TH_SP_CMD_END)
                {
                    LOGD("Thread %d: Received end command, exiting thread\n", thread_id);
                    sender_cleanup(&sock);
                    if(nanosleep(&req_exit, NULL) != 0)
                    {
                        LOGE("Thread %d: nanosleep interrupted while waiting to exit\n", thread_id);
                        return (-2); // Exit the thread if nanosleep is interrupted
                    }
                    return NULL; // Exit the thread
                }
                else
                {
                    LOGE("Thread %d: Unexpected command received %d\n", thread_id, cmd.scan);
                    if(nanosleep(&req_err, NULL) != 0)
                    {
                        LOGE("Thread %d: nanosleep interrupted while waiting for next command\n", thread_id);
                        return (-2); // Exit the thread if nanosleep is interrupted
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
                    return (-2); // Exit the thread if nanosleep is interrupted
                }
                err_cnt++;
                break;
        }
    }

    sender_cleanup(&sock);


    return NULL; // Return NULL when the thread is done
}