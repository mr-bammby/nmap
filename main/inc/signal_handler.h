#ifndef _SIGNAL_HANDLER_H_
#define _SIGNAL_HANDLER_H_

/* Signal handler callback type */
typedef void (*interrupt_callback_t)(void);

/* Initialize the signal handler */
void init_signal_handler(interrupt_callback_t callback);

/* Shutdown the signal handler */
void shutdown_signal_handler(void);

#endif /* _SIGNAL_HANDLER_H_ */
