#include "login.h"
#include <string.h>

static char entered_password[5];
static unsigned char attempts = 3;
static unsigned char index = 0;
static unsigned char flag = 0;
static unsigned short lock_count = 0;
static unsigned short timeout_count = 0;  

void display_login(void)
{
    if(flag)
    {
        clcd_print((const unsigned char *)"System Locked", LINE1(0));
        clcd_print((const unsigned char *)"wait for 15 min", LINE2(0));
    }
    else
    {
        clcd_print((const unsigned char *)"Enter password", LINE1(0));
    }
}

void process_login(State_t *stat)
{
    if(flag)
    {
        lock_count++;
        if(lock_count >= 9000)
        {
            attempts = 3;
            flag = 0;
            lock_count = 0;
            CLEAR_DISP_SCREEN;
        }
        return;
    }

    unsigned char key;
    key = read_switches(STATE_CHANGE);

    if(index < 4)
    {
        if(key == MK_SW1)
        {
            entered_password[index] = '1';
            clcd_putch('*', LINE2(index));
            index++;
            timeout_count = 0;   /* reset timeout on each key press */
        }
        else if(key == MK_SW2)
        {
            entered_password[index] = '2';
            clcd_putch('*', LINE2(index));
            index++;
            timeout_count = 0;   /* reset timeout on each key press */
        }
        else
        {
            /* FIX: count idle time only when password entry is in progress */
            if(index > 0)
            {
                timeout_count++;
                if(timeout_count >= 3000)  /* ~3 seconds */
                {
                    index = 0;
                    timeout_count = 0;
                    memset(entered_password, '\0', sizeof(entered_password));
                    CLEAR_DISP_SCREEN;
                    *stat = DASHBOARD;
                    return;
                }
            }
        }
    }

    if(index == 4)
    {
        entered_password[4] = '\0';
        timeout_count = 0;

        if(strcmp(entered_password, PASSWORD) == 0)
        {
            attempts = 3;
            index = 0;
            memset(entered_password, '\0', sizeof(entered_password));
            *stat = MAIN_MENU;
            CLEAR_DISP_SCREEN;
        }
        else
        {
            attempts--;
            CLEAR_DISP_SCREEN;
            clcd_print((const unsigned char *)"Wrong Password", LINE1(0));
            __delay_ms(1000);
            index = 0;
            memset(entered_password, '\0', sizeof(entered_password));
            CLEAR_DISP_SCREEN;

            if(attempts == 0)
            {
                flag = 1;
                lock_count = 0;
            }
        }
    }
}