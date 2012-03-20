/********************************************************************
* libarduino example
********************************************************************/
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "libarduino.h"

int main (void)
{
	uint8_t dir = 1;
	uint8_t c = 0;

	pwm_init(1);
	pwm_init(2);
	pwm_init(3);
	pwm_init(4);

	sei(); /* enable interrupts */

	while (1)
	{

		/* make our LED breath */
		if (dir) {
			if (c == 40) { dir = 0; } else c++;
		} else {
			if (c ==  0) { dir = 1; } else c--;
		}
		pwm_set(1, c);
		pwm_set(2, c);
		pwm_set(3, c);
		pwm_set(4, c);

		/* busy wait delay - really should use an interrupt */
		_delay_ms(16);
		_delay_ms(16);
	}

	return 1;
}

