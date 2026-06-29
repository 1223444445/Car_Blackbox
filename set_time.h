  
#ifndef SET_TIME_H
#define	SET_TIME_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "main.h"

void display_time(Dashboard_t *dash);
void process_time(State_t *state,Dashboard_t *dash);
#endif	/* XC_HEADER_TEMPLATE_H */

