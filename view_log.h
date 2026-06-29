
#ifndef VIEW_LOG_H
#define	VIEW_LOG_H

#include <xc.h>
#include "main.h"
#include "event.h"
#include "clcd.h"
#include "matrix_keypad.h"

void display_log(void);
void process_log(State_t *state); 
void reset_log_index(void);
#endif	/* XC_HEADER_TEMPLATE_H */

