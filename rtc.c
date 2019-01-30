// see rtc.h for complete documentation

#include "rtc.h"
#include "rtc_regdef.h"
#include "avr/io.h"

// safely overwrites the bits in BUF defined by MASK with VAL
#define EDIT_BITS(BUF, MASK, VAL) BUF = (BUF & !MASK) | ((VAL) & MASK)

// send a condition over TWI bus
#define SEND_START TWCR = 0x00 | _BV(TWSTA) | _BV(TWINT);
#define SEND_STOP TWCR = 0x00 | _BV(TWSTO) | _BV(TWINT);

void i2c_init() {
  PRR &= 0xFF & !_BV(PRTWI);
  // enable I2C interrupts (AFTER polling implementation works!) by setting TWIE
  TWCR |= 0x00 | _BV(TWEN) | _BV(TWEA);
  PORTC |= 0x00 | _BV(PORTC4) | _BV(PORTC5);
  return;
}

// i2c_init must have been called, otherwise the bus may not be set up
// get this working synchronously (polling-based), then split it up to run async (interrupt-based)
// addr: slave address, with read/write bit appended
rtc_err_t i2c_transaction(uint8_t addr, uint8_t* val, uint8_t count) {
  SEND_START;
  uint8_t bytes = 0;
  while( bytes < count ) {
    if( TWCR & _BV(TWINT) ) {
      switch( TWSR & MSK_STATUS ) {
        case STS_START:
          // start transmitted, send addr
          break;

        case STS_RSTART:
          // repeated start, send addr
          break;

        case STS_SLAW_ACK:
          // slave acknowledged address, send data
          break;

        case STS_SLAW_NACK:
          SEND_STOP;
          return(RTC_SLAW_NACK);
          break;

        case STS_DTRN_ACK:
          // slave acknowledged byte, increment byte counter and send next byte (if applicable)
          break;

        case STS_DTRN_NACK:
          SEND_STOP;
          return(RTC_DTRN_NACK);
          break;

        case STS_ARB_LOST :
          SEND_START;
          break;

        case STS_SLAR_ACK :
          // slave acknowledged address, perpare for data receipt
          break;

        case STS_SLAR_NACK:
          SEND_STOP;
          return(RTC_SLAR_NACK);
          break;

        case STS_DRCV_ACK :
          // we received a byte and acknowledged, increment byte counter
          break;

        case STS_DRCV_NACK:
          SEND_STOP;
          return(RTC_DRCV_NACK);
          break;

        default:
          SEND_STOP;
          return(RTC_BAD_STATUS);
          break;
      }
    }
  }
  SEND_STOP;
  return RTC_OK;
}

void i2c_write(uint8_t* val, uint8_t count) {
  i2c_transaction(VAL_ADDR_WRITE, val, count);
  return;
}

void i2c_read(uint8_t* val, uint8_t count) {
  i2c_transaction(VAL_ADDR_READ, val, count);
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
