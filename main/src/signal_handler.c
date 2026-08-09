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

static interrupt_callback_t g_interrupt_callback = NULL;

static void interrupt_handler(int signum)
{
    char buf[64];
    size_t idx = 0;

    if (g_interrupt_callback != NULL)
    {
        g_interrupt_callback();
    }


    const char *prefix = "Interrupted ";
    const char *suffix = " QUITING!\n";

    for (const char *p = prefix; *p != '\0'; p++)
    {
        buf[idx++] = *p;
    }

    unsigned int value = (unsigned int)signum;
    char digits[16];
    size_t digit_count = 0;

    if (value == 0)
    {
        digits[digit_count++] = '0';
    }
    else
    {
        while (value > 0)
        {
            digits[digit_count++] = (char)('0' + (value % 10));
            value /= 10;
        }
    }

    for (size_t i = 0; i < digit_count; i++)
    {
        buf[idx++] = digits[digit_count - 1 - i];
    }

    for (const char *p = suffix; *p != '\0'; p++)
    {
        buf[idx++] = *p;
    }

    (void)write(STDERR_FILENO, buf, idx);

    _exit(EXIT_FAILURE);
}

void init_signal_handler(interrupt_callback_t callback)
{
    g_interrupt_callback = callback;

    struct sigaction action = {0};
    action.sa_handler = interrupt_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    sigaction(SIGINT, &action, NULL);
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGQUIT, &action, NULL);
}
