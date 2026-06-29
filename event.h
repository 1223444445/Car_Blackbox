 
#ifndef EVENT_H
#define	EVENT_H
#include"main.h"
#define MAX_LOGS 10
#include <xc.h> // include processor files - each processor file is guarded.  
typedef struct{
    char event[3];
    char time[9];
    unsigned char speed;
}Log_t;
void log_event(Dashboard_t *dash);
extern Log_t logs[MAX_LOGS];
extern unsigned char write_index;
extern unsigned char log_count;
#endif	/* XC_HEADER_TEMPLATE_H */












