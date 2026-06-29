#include "rtc.h"
#include "i2c.h"

void init_rtc(void)
{
    /* Start I2C communication */
    i2c_start();

    /* Send DS1307 write address */
    i2c_write(DS1307_WRITE_ADDR);

    /* Point to seconds register */
    i2c_write(SEC_ADDR);

    /* Write 0x00 to clear the clock halt bit and start the clock */
    i2c_write(0x00);

    /* Stop I2C communication */
    i2c_stop();
}

void write_ds1307(unsigned char addr, unsigned char data)
{
    i2c_start();
    i2c_write(DS1307_WRITE_ADDR);
    i2c_write(addr);
    i2c_write(data);
    i2c_stop();
}

unsigned char read_ds1307(unsigned char addr)
{
    unsigned char data;

    i2c_start();
    i2c_write(DS1307_WRITE_ADDR);
    i2c_write(addr);
    i2c_rep_start();
    i2c_write(DS1307_READ_ADDR);
    data = i2c_read();
    i2c_stop();

    return data;
}

void get_time(char *time)
{
    unsigned char hr, min, sec;

    hr  = read_ds1307(HOUR_ADDR);
    min = read_ds1307(MIN_ADDR);
    sec = read_ds1307(SEC_ADDR);

    time[0] = ((hr >> 4) & 0x03) + '0';
    time[1] = (hr & 0x0F) + '0';
    time[2] = ':';
    time[3] = ((min >> 4) & 0x07) + '0';
    time[4] = (min & 0x0F) + '0';
    time[5] = ':';
    time[6] = ((sec >> 4) & 0x07) + '0';
    time[7] = (sec & 0x0F) + '0';
    time[8] = '\0';
}

void set_time(char *time)
{
    unsigned char hr, min, sec;

    hr  = ((time[0] - '0') << 4) | (time[1] - '0');
    min = ((time[3] - '0') << 4) | (time[4] - '0');
    sec = ((time[6] - '0') << 4) | (time[7] - '0');

    write_ds1307(HOUR_ADDR, hr);
    write_ds1307(MIN_ADDR, min);
    write_ds1307(SEC_ADDR, sec);
}