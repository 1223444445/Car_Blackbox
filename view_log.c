#include "view_log.h"
#include "event.h"
#include "clcd.h"
#include "matrix_keypad.h"

static unsigned char index = 0;

/* FIX: reset index when entering VIEW_LOG state */
void reset_log_index(void)
{
    index = 0;
}

void display_log(void)
{
    char speed[3];

    /* FIX: guard against empty log */
    if(log_count == 0)
    {
        clcd_print("No logs yet", LINE1(0));
        return;
    }

    clcd_putch('#', LINE1(0));
    clcd_putch(index + '0', LINE1(1));

    clcd_print(logs[index].event, LINE1(3));
    clcd_print(logs[index].time, LINE1(6));

    speed[0] = (logs[index].speed / 10) + '0';
    speed[1] = (logs[index].speed % 10) + '0';
    speed[2] = '\0';

    clcd_print("SP:", LINE2(0));
    clcd_print(speed, LINE2(3));
}

void process_log(State_t *state)
{
    unsigned char key;
    static unsigned short up_count = 0;
    static unsigned short down_count = 0;  /* FIX: for long press DOWN to logout */

    if(log_count == 0)
    {
        return;
    }

    key = read_switches(LEVEL_CHANGE);

    /* long press SW1 (UP) -> back to main menu */
    if(key == MK_SW1)
    {
        up_count++;
        if(up_count >= 200)
        {
            *state = MAIN_MENU;
            CLEAR_DISP_SCREEN;
            up_count = 0;
            down_count = 0;
            return;
        }
    }
    else
    {
        up_count = 0;
    }

    /* FIX: long press SW2 (DOWN) -> logout to dashboard */
    if(key == MK_SW2)
    {
        down_count++;
        if(down_count >= 200)
        {
            *state = DASHBOARD;
            CLEAR_DISP_SCREEN;
            down_count = 0;
            up_count = 0;
            return;
        }
    }
    else
    {
        down_count = 0;
    }

    key = read_switches(STATE_CHANGE);

    if(key == MK_SW1)
    {
        if(index > 0)
        {
            index--;
        }
    }
    else if(key == MK_SW2)
    {
        /* FIX: rollover on reaching max log entries */
        index = (index + 1) % log_count;
    }
}