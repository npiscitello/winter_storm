#ifndef RTC_H
#define RTC_H

// for the time struct
#include <time.h>

// register definitions and bitmasks
#define REG_SEC         0x00
#define MSK_SEC_CH      0x80
#define MSK_SEC_10      0x70
#define MSK_SEC_1       0x0F

#define REG_MIN         0x01
#define MSK_MIN_10      0x70
#define MSK_MIN_1       0x0F

#define REG_HOUR        0x02
#define MSK_HOUR_MODE   0x40
#define MSK_HOUR_10     0x30
#define MSK_HOUR_1      0x0F

#define REG_WDAY        0x03
#define MSK_WDAY_DAY    0x03

#define REG_MDAY        0x04
#define MSK_MDAY_10     0x30
#define MSK_MDAY_1      0x0F

#define REG_MON         0x05
#define MSK_MON_10      0x10
#define MSK_MON_1       0x0F

#define REG_YEAR        0x06
#define MSK_YEAR_10     0xF0
#define MSK_YEAR_1      0x0F

#define REG_CTRL        0x07
#define MSK_CTRL_OUT    0x80
#define MSK_CTRL_SQWE   0x10
#define MSK_CTRL_RS     0x30

// we'll use the POSIX ctime broken-down structure
typedef struct tm time_struct_t;

/* prepare the RTC for use
 */
void rtc_init(void);

/* set the RTC to a specific point in time
 * rtc_time: a pointer to a ctime-style broken down time structure
 */
void set_time(time_struct_t* rtc_time);

/* get the current time from the rtc
 * rtc_time: a pointer to a ctime-style broken down time structure
 */
void get_time(time_struct_t*);

#endif
