/* TWI comms w/ RTC
 * 6 channels of PWM
 */

#include <avr/io.h>
#include "rtc.h"

int main(void) {
  PRR = 0x00 | _BV(PRTIM0) | _BV(PRTIM1) | _BV(PRTIM2);

  while(1) {
  }
}
