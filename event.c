#include"event.h"

Log_t logs[MAX_LOGS];
unsigned char write_index=0;
unsigned char log_count=0;

void log_event(Dashboard_t *dash)
{
    strcpy(logs[write_index].event,dash->latest_event);
    strcpy(logs[write_index].time,dash->current_time);
    logs[write_index].speed=dash->speed;
    write_index++;
    if(write_index>=MAX_LOGS)
    {
        write_index=0;
    }
    if(log_count<MAX_LOGS)
    {
     log_count++;      
    }
    
}
