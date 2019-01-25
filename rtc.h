/* This library is designed to interface an AVR microcontroller
 * with a DS1307 RTC chip over the I2C (TWI) interface. It's
 * primarily designed to use 24-hour mode.
 */

#ifndef RTC_H
#define RTC_H

// for the time struct
#include <time.h>

// error codes
typedef enum {
  RTC_OK
} rtc_err_t;

// we'll use the POSIX ctime broken-down structure
typedef struct tm time_struct_t;

/* prepare the AVR to talk to the rtc, and run any setup needed on the RTC
 * returns: error code or RTC_OK, from rtc_err_t enum
 */
void rtc_init(void);

/* set the RTC to a specific point in time
 * rtc_time: a pointer to a ctime-style broken down time structure
 * returns: error code or RTC_OK, from rtc_err_t enum
 */
rtc_err_t set_time(time_struct_t* rtc_time);

/* get the current time from the rtc
 * rtc_time: a pointer to a ctime-style broken down time structure
 * returns: error code or RTC_OK, from rtc_err_t enum
 */
rtc_err_t get_time(time_struct_t*);

#endif
