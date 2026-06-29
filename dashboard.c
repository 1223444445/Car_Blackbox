#include "dashboard.h"
#include "adc.h"

char gear_events[6][3] =
{
    "GN", "G1", "G2", "G3", "G4", "GR"
};

static signed char gear = -1;
static unsigned short SW1_count = 0;
static unsigned char overspeed_flag = 0;

void process_events(Dashboard_t *dash, State_t *state)
{
    unsigned char key;
    key = read_switches(LEVEL_CHANGE);

    if(key == MK_SW1)
    {
        SW1_count++;

        if(SW1_count >= 200)
        {
            *state = LOGIN;
            CLEAR_DISP_SCREEN;
            SW1_count = 0;
            return;
        }
    }
    else
    {
        SW1_count = 0;
    }

    key = read_switches(STATE_CHANGE);

    if(key == MK_SW1)
    {
        if(gear < 5)
        {
            gear++;
            strcpy(dash->latest_event, gear_events[gear]);
            log_event(dash);
        }
    }
    else if(key == MK_SW2)
    {
        if(gear > 0)
        {
            gear--;
            strcpy(dash->latest_event, gear_events[gear]);
            log_event(dash);
        }
    }

    if(dash->speed > 80)
    {
        if(overspeed_flag == 0)
        {
            strcpy(dash->latest_event, "OS");
            log_event(dash);
            overspeed_flag = 1;
        }
    }
    else
    {
        if(overspeed_flag == 1)
        {
            if(gear == -1)
            {
                strcpy(dash->latest_event, "ON");
            }
            else
            {
                strcpy(dash->latest_event, gear_events[gear]);
            }
            log_event(dash);      
            overspeed_flag = 0;
        }
    }
}

void display_dashboard(Dashboard_t *dash)
{
    char speed[3];

    clcd_print((const unsigned char *)dash->current_time, LINE1(0));
    clcd_print((const unsigned char *)dash->latest_event, LINE1(13));

    speed[0] = (dash->speed / 10) + '0';
    speed[1] = (dash->speed % 10) + '0';
    speed[2] = '\0';

    clcd_print((const unsigned char *)"SP:", LINE2(0));
    clcd_print((const unsigned char *)speed, LINE2(3));
}

void update_dashboard(Dashboard_t *dash)
{
    get_time(dash->current_time);
    dash->speed = (unsigned char)((read_adc(CHANNEL4) * 99) / 1023);
}