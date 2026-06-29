  
#ifndef LOGIN_H
#define	LOGIN_H

#include "clcd.h"
#include "matrix_keypad.h"
#include "main.h"
#include <xc.h> 
// include processor files - each processor file is guarded.  
#define PASSWORD "1211"

void display_login(void);
void process_login(State_t *state);

#endif	/* XC_HEADER_TEMPLATE_H */

