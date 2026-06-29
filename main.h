#ifndef MAIN_H
#define MAIN_H

#include <xc.h>
#include <string.h>

#define _XTAL_FREQ 20000000
#define INST_MODE  INSTRUCTION_COMMAND 

typedef enum
{
    DASHBOARD,
    LOGIN,
    MAIN_MENU,
    VIEW_LOG,
    SET_TIME
} State_t;

typedef struct
{
    char latest_event[3];
    char current_time[9];
    unsigned char speed;
} Dashboard_t;

#endif