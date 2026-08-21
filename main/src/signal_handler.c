#define MODULE_DEBUG DEBUG_MAIN
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L // For VS Code intellisense to recognize sigaction and related functions
#endif
#include "debug.h"
#include <stddef.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "signal_handler.h"
#include <pthread.h>
#include <stdatomic.h>
#include <string.h>

static interrupt_callback_t g_interrupt_callback = NULL;
static sigset_t g_sigset;

static pthread_t g_tid = 0;
static atomic_int g_should_exit = ATOMIC_VAR_INIT(0);

static void *signal_waiter(void *arg)
{
    (void)arg;
    int sig;
    while (atomic_load(&g_should_exit) == 0)
    {
        if (sigwait(&g_sigset, &sig) == 0)
        {
            if (g_interrupt_callback != NULL)
            {
                g_interrupt_callback();
            }
#if DEBUG_MAIN
            /* Write a brief message to stderr in a safe way */
            const char *msg = "Interrupted - quitting!\n";
            (void)write(STDERR_FILENO, msg, strlen(msg));
#endif
        }
    }
    return NULL;
}

void init_signal_handler(interrupt_callback_t callback)
{
    g_interrupt_callback = callback;

    sigemptyset(&g_sigset);
    sigaddset(&g_sigset, SIGINT);
    sigaddset(&g_sigset, SIGTERM);
    sigaddset(&g_sigset, SIGQUIT);

    /* Block signals in all threads; the signal waiter thread will handle them */
    pthread_sigmask(SIG_BLOCK, &g_sigset, NULL);

    pthread_t tid;
    if (pthread_create(&tid, NULL, signal_waiter, NULL) != 0)
    {
        /* Fallback: if thread creation fails, leave default handlers */
        sigemptyset(&g_sigset);
        sigaddset(&g_sigset, SIGINT);
        sigaddset(&g_sigset, SIGTERM);
        sigaddset(&g_sigset, SIGQUIT);
        struct sigaction action = {0};
        action.sa_handler = SIG_DFL;
        sigaction(SIGINT, &action, NULL);
        sigaction(SIGTERM, &action, NULL);
        sigaction(SIGQUIT, &action, NULL);

        return;
    }
    else
    {
        g_tid = tid;
        /* Leave thread joinable so we can cleanly shut it down */
    }
}

void shutdown_signal_handler(void)
{
    if (g_tid != 0)
    {
        atomic_store(&g_should_exit, 1);
        /* Wake the sigwait by sending one of the caught signals to the thread */
        pthread_kill(g_tid, SIGINT);
        /* If called from the signal waiter thread itself, don't join (would deadlock) */
        if (!pthread_equal(pthread_self(), g_tid))
        {
            pthread_join(g_tid, NULL);
        }
        g_tid = 0;
    }
}
