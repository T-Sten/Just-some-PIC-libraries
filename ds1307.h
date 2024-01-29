
/* 
 * DS1307 RTC module library by Tom Stenvall
 */

#ifndef DS1307_H
#define	DS1307_H

#include <xc.h>
#include "I2C.h"

//This address is the 7 bit type
#define DS1307_ADDRESS 0x68

//Register enumerations
typedef enum{
    REG_SECONDS,
    REG_MINUTES,
    REG_HOURS,
    REG_DAY,
    REG_DATE,
    REG_MONTH,
    REG_YEAR,
    REG_CONTROL
}DS1307_REG;

//Square wave settings enumerations
typedef enum{
    SQWFREQ_1HZ,
    SQWFREQ_4KHZ,
    SQWFREQ_8KHZ,
    SQWFREQ_32KHZ
}DS1307_SQWFREQ;

typedef struct{
    uint8_t time[6]; //thour, hour, tmin, min, tsec, sec
    uint16_t total_time_min;
}Ds1307_time;

//Enables SQWOUT function with a predefined setting
void DS1307_sqw_enable(DS1307_SQWFREQ freq_setting);

//Resets timekeeping registers, starts timekeeping
void DS1307_start(void);

//Reads time from DS1307 and parses it into the struct
void DS1307_time_read(Ds1307_time* time_struct);

//Writes time from the time struct to the DS1307
void DS1307_set_time(Ds1307_time *time_struct);


#endif

