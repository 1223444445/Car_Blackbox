/*
 * File:   main.c
 * Author: Abinand V Nair
 *
 * Created on 21 June, 2026, 7:55 PM
 */

#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "i2c.h"
#include "matrix_keypad.h"
#include "rtc.h"
#include "dashboard.h"
#include "login.h"
#include "menu.h"
#include "adc.h"
#include "event.h"
#include "view_log.h"
#include "set_time.h"

State_t state = DASHBOARD;
Dashboard_t dashboard = {"ON", "00:00:00", 0};

void init_config(void)
{
    init_clcd();
    init_i2c();
    init_adc();
    init_matrix_keypad();
    init_rtc();
}

void main(void)
{
    init_config();
    get_time(dashboard.current_time);
    log_event(&dashboard);

    while(1)
    {
        if(state != SET_TIME)
            update_dashboard(&dashboard);

        switch(state)
        {
            case DASHBOARD:
                display_dashboard(&dashboard);
                process_events(&dashboard, &state);
                break;

            case LOGIN:
                display_login();
                process_login(&state);
                break;

            case MAIN_MENU:
                display_menu();
                process_menu(&state);
                break;

            case VIEW_LOG:
                display_log();
                process_log(&state);
                break;

            case SET_TIME:
                display_time(&dashboard);
                process_time(&state, &dashboard);
                break;
        }
    }
}