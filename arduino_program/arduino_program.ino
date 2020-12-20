A#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

volatile char i = 0;

const char array_led[] = {3, 1, 7, 4, 2, 3, 6, 1, 5, 2, 6, 3, 5, 2, 4, 1};
volatile char current_led;

int main (void) {
  sei();
  CCP = 0xD8; // Unlock clock config
  CLKMSR = 0b01;  // 128 kHz WDT oscillator as clock source
  CCP = 0xD8; // Unlock clock config
  CLKPSR = 0b0111; // 256 clock prescaler, clock frequency = 1000 Hz -> 1 clock = 1 ms

  DDRB = 1 << DDB0 | 1 << DDB1 | 1 << DDB2;                 // PB0-2 as an output

  PORTB = 0b111;
  __builtin_avr_delay_cycles(1000);
  PORTB = 0b000;
  __builtin_avr_delay_cycles(1000);

  CCP = 0xD8; // Unlock watchdog config
  WDTCSR = 1 << WDIE | 1 << WDP3; // In interrupt mode, 4 s delay

  SMCR = 1 << SM1 | 1 << SE;
  __builtin_avr_sleep();
}

ISR(WDT_vect)
{
  cli();
  i = (i+1);
  current_led = array_led[i&0b1111];
  PORTB = current_led;
  __builtin_avr_delay_cycles(250);
  PORTB = 0b000;
  //__builtin_avr_delay_cycles(1000);
  sei();
  SMCR = 1 << SM1 | 1 << SE;
  __builtin_avr_sleep();
}
