#include "menu.h"
#include "view_log.h"

char *menu[] = {"View Log", "Set Time"};
static unsigned char index = 0;
static unsigned short up_count = 0;
static unsigned short down_count = 0;
static unsigned short idle_count = 0;

void display_menu(void)
{
    if(index == 0)
    {
        clcd_putch('*', LINE1(0));
        clcd_print(menu[0], LINE1(1));
        clcd_print(menu[1], LINE2(1));
    }
    else
    {
        clcd_print(menu[0], LINE1(1));
        clcd_putch('*', LINE2(0));
        clcd_print(menu[1], LINE2(1));
    }
}

void process_menu(State_t *state)
{
    unsigned char key;
    key = read_switches(LEVEL_CHANGE);

    if(key == MK_SW1)
    {
        up_count++;
        if(up_count >= 200)
        {
            if(index == 0)
            {
                reset_log_index();   /* FIX: reset log index before entering VIEW_LOG */
                *state = VIEW_LOG;
            }
            else
            {
                *state = SET_TIME;
            }
            CLEAR_DISP_SCREEN;
            up_count = 0;
            down_count = 0;
            idle_count = 0;
            index = 0;             /* FIX: reset menu index on exit */
            return;
        }
    }
    else
    {
        up_count = 0;
    }

    if(key == MK_SW2)
    {
        down_count++;
        if(down_count >= 200)
        {
            *state = DASHBOARD;
            CLEAR_DISP_SCREEN;
            down_count = 0;
            up_count = 0;
            idle_count = 0;
            index = 0;             /* FIX: reset menu index on exit */
            return;
        }
    }
    else
    {
        down_count = 0;
    }

    if(key == ALL_RELEASED)
    {
        idle_count++;
        if(idle_count >= 500)
        {
            *state = DASHBOARD;
            CLEAR_DISP_SCREEN;
            idle_count = 0;
            up_count = 0;
            down_count = 0;
            index = 0;             /* FIX: reset menu index on exit */
            return;
        }
    }
    else
    {
        idle_count = 0;
    }

    key = read_switches(STATE_CHANGE);

    if(key == MK_SW2)
    {
        if(index < 1)
        {
            index++;
        }
    }
    else if(key == MK_SW1)
    {
        if(index > 0)
        {
            index--;
        }
    }
}