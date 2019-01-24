// see rtc.h for complete documentation

#include "rtc.h"

void rtc_init(void) {
  // don't forget to set TWI pullups
  // make sure the RTC is in 24 hour mode
  // if it's in 12 hour mode, get the hour 
  // value, convert, swap modes, and re-write
  return;
}

rtc_err_t set_time(time_struct_t* rtc_time) {
  return RTC_OK;
}

rtc_err_t get_time(time_struct_t* rtc_time) {
  return RTC_OK;
}
