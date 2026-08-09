#ifndef _SIGNAL_HANDLER_H_
#define _SIGNAL_HANDLER_H_

typedef void (*interrupt_callback_t)(void);

void init_signal_handler(interrupt_callback_t callback);

#endif /* _SIGNAL_HANDLER_H_ */
