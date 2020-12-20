/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *  
 *
 */


 /*
  * Program for Attiny4-5-9-10
  * Make the lesd flash for 250ms every 4s on a kake random pattern
  */

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

volatile char i = 0; // Current index

const char array_led[] = {3, 1, 7, 4, 2, 3, 6, 1, 5, 2, 6, 3, 5, 2, 4, 1}; // Codes for ON leds (1=0B001, 2=0B010, ..., 7=0B111)
volatile char current_led;

int main (void) {
  sei(); //Enable interrupts
  CCP = 0xD8; // Unlock clock config
  CLKMSR = 0b01;  // 128 kHz WDT oscillator as clock source
  CCP = 0xD8; // Unlock clock config
  CLKPSR = 0b0111; // 256 clock prescaler, clock frequency = 1000 Hz -> 1 clock = 1 ms

  DDRB = 1 << DDB0 | 1 << DDB1 | 1 << DDB2;                 // PB0-2 as an output

  // Test leds
  PORTB = 0b111;
  __builtin_avr_delay_cycles(1000); // 1000 cycles = 1000 ms
  PORTB = 0b000;
  __builtin_avr_delay_cycles(1000);

  CCP = 0xD8; // Unlock watchdog config
  WDTCSR = 1 << WDIE | 1 << WDP3; // In interrupt mode, 4 s delay

  SMCR = 1 << SM1 | 1 << SE; // Select the deepest sleep mode
  __builtin_avr_sleep(); // Enable sleep
}

ISR(WDT_vect) //Interrupt on watchdog timer
{
  cli(); //Disable interrupts
  
  i = (i + 1); // Led turn on and turn off logic
  current_led = array_led[i & 0b1111];
  PORTB = current_led;
  __builtin_avr_delay_cycles(250); // 250 cycles = 250 ms
  PORTB = 0b000;

  sei(); //Enable interrupts
  SMCR = 1 << SM1 | 1 << SE; // Select the deepest sleep mode
  __builtin_avr_sleep(); // Enable sleep
}
