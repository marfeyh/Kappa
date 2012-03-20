/********************************************************************
* libarduino example
* 
* Connect LED and resistor between GND and digital pin 9. 
* Connect potentiomenter to GND, 5V, and center to analog pin 0.
* Connect AREF to 5V or digital pin 12 (we set it HIGH in sw here).
********************************************************************/
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "libarduino.h"

int main (void)
{
	uint16_t c = 0;

	pwm_init(1);
	//serial_init();
	//fdevopen(serial_putchar, serial_getchar);

	adc_init();

	pinMode(12, OUTPUT);
	digitalWrite(12, HIGH);

	sei(); /* enable interrupts */

	while (1)
	{

		c = adc_get(0);
		pwm_set(1, c/4);

		/* busy wait delay - really should use an interrupt */
		_delay_ms(16);
	}

	return 1;
}

