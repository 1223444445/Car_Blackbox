#include "set_time.h"
#include "main.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "rtc.h"

static unsigned char field = 0;
static unsigned short up_count = 0;
static unsigned char blink = 0;
static unsigned short blink_count = 0;

void display_time(Dashboard_t *dash)
{
    clcd_print("TIME:", LINE1(0));
    clcd_print(dash->current_time, LINE2(0));

    blink_count++;
    if(blink_count >= 200)
    {
        blink = !blink;
        blink_count = 0;
    }

    if(blink)
    {
        if(field == 0)
        {
            clcd_print("  ", LINE2(0));
        }
        else if(field == 1)
        {
            clcd_print("  ", LINE2(3));
        }
        else
        {
            clcd_print("  ", LINE2(6));
        }
    }
}

void process_time(State_t *state, Dashboard_t *dash)
{
    unsigned char key;
    key = read_switches(LEVEL_CHANGE);

    if(key == MK_SW1)
    {
        up_count++;
        if(up_count >= 200)
        {
            set_time(dash->current_time);
            *state = MAIN_MENU;
            CLEAR_DISP_SCREEN;
            up_count = 0;
            field = 0;
            blink = 0;
            blink_count = 0;
            return;
        }
    }
    else
    {
        up_count = 0;
    }

    key = read_switches(STATE_CHANGE);

    if(key == MK_SW2)
    {
        field++;
        if(field > 2)
        {
            field = 0;
        }
    }

    if(key == MK_SW1)
    {
        if(field == 0)
        {
            unsigned char hr;
            hr = (dash->current_time[0] - '0') * 10 + (dash->current_time[1] - '0');
            hr++;
            if(hr >= 24)
            {
                hr = 0;
            }
            dash->current_time[0] = (hr / 10) + '0';
            dash->current_time[1] = (hr % 10) + '0';
        }
        else if(field == 1)
        {
            unsigned char min;
            min = (dash->current_time[3] - '0') * 10 + (dash->current_time[4] - '0');
            min++;
            if(min >= 60)
            {
                min = 0;
            }
            dash->current_time[3] = (min / 10) + '0';
            dash->current_time[4] = (min % 10) + '0';
        }
        else
        {
            unsigned char sec;
            sec = (dash->current_time[6] - '0') * 10 + (dash->current_time[7] - '0');
            sec++;
            if(sec >= 60)
            {
                sec = 0;
            }
            dash->current_time[6] = (sec / 10) + '0';
            dash->current_time[7] = (sec % 10) + '0';
        }
    }
}