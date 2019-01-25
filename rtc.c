// see rtc.h for complete documentation

#include "rtc.h"
#include "rtc_regdef.h"
#include "avr/io.h"

// safely overwrites the bits in BUF defined by MASK with VAL
#define EDIT_BITS(BUF, MASK, VAL) BUF = (BUF & !MASK) | ((VAL) & MASK)

void i2c_init() {
  // enable I2C and pullup resistors
  TWCR |= 0x00 | _BV(TWEN);
  PORTC |= 0x00 | _BV(PORTC4) | _BV(PORTC5);
  return;
}

// i2c_init must have been called, otherwise the bus may not be set up
void i2c_write(uint8_t* val, uint8_t count) {
  // generate start
  // write write address
  // write data
  return;
}

// i2c_init must have been called, otherwise the bus may not be set up
void i2c_read(uint8_t* val, uint8_t count) {
  // generate start
  // write read address
  // read data
  return;
}

void rtc_init(void) {
  i2c_init();
  uint8_t hours_buf;
  i2c_read(&hours_buf, 1);

  // if it's in 12 hour mode, convert and re-write
  if( (hours_buf & MSK_HOUR_MODE) == (MODE_12 << OFS_HOUR_MODE) ) {
    // change to 24 hour mode
    EDIT_BITS(hours_buf, MSK_HOUR_MODE, MODE_24 << OFS_HOUR_MODE);

    // convert hour value
    if( (hours_buf & MSK_12HOUR_AMPM) == VAL_AM ) {
      // 12 AM is a special case - it turns into 00. Every other hour stays the same.
      if( (hours_buf & MSK_12HOUR_10) == (1 << OFS_HOUR_10) && 
          (hours_buf & MSK_HOUR_1) == (2 << OFS_HOUR_1) ) {
        EDIT_BITS(hours_buf, MSK_24HOUR_10, 0 << OFS_HOUR_10);
        EDIT_BITS(hours_buf, MSK_HOUR_1, 0 << OFS_HOUR_1);
      }

    } else {
      // 12 PM is a special case - it doesn't change. 12 is added to every other hour.
      if( !((hours_buf & MSK_12HOUR_10) == (1 << OFS_HOUR_10) && 
            (hours_buf & MSK_HOUR_1) == (2 << OFS_HOUR_1)) ) {
        EDIT_BITS(hours_buf, MSK_HOUR_1, (hours_buf & MSK_HOUR_1) + (2 << OFS_HOUR_1));
        if( (hours_buf & MSK_HOUR_1) > (9 << OFS_HOUR_1) ) {
          EDIT_BITS(hours_buf, MSK_HOUR_1, (hours_buf & MSK_HOUR_1) - (10 << OFS_HOUR_1));
          EDIT_BITS(hours_buf, MSK_24HOUR_10, 2 << OFS_HOUR_10);
        } else {
          EDIT_BITS(hours_buf, MSK_24HOUR_10, 1 << OFS_HOUR_10);
        }
      }
    }
  }

  i2c_write(&hours_buf, 1);

  return;
}

rtc_err_t set_time(time_struct_t* rtc_time) {
  return RTC_OK;
}

rtc_err_t get_time(time_struct_t* rtc_time) {
  return RTC_OK;
}
