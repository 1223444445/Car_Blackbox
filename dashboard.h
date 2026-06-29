#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "rtc.h"
#include "event.h"

void display_dashboard(Dashboard_t *dash);
void update_dashboard(Dashboard_t *dash);
void process_events(Dashboard_t *dash, State_t *state);

#endif