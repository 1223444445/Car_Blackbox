#ifndef RTC_H
#define RTC_H

#define DS1307_WRITE_ADDR   0xD0
#define DS1307_READ_ADDR    0xD1

#define SEC_ADDR            0x00
#define MIN_ADDR            0x01
#define HOUR_ADDR           0x02

void init_rtc(void);
void get_time(char *time);
void set_time(char *time);

#endif