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
	uint8_t c;

	serial_init();
	fdevopen(serial_putchar, serial_getchar);

	sei(); /* enable interrupts */

	printf("simple pin manipulation example\n\r");

	pinMode(12, OUTPUT); /* led on digital pin 12 */
	pinMode(2, INPUT); /* button on digital pin 2*/

	while (1)
	{
		if (digitalRead(2) == 0)
			digitalWrite(12, HIGH);
		else
			digitalWrite(12, LOW);
	}

	return 1;
}
