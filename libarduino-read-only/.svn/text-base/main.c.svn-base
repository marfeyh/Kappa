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
	uint16_t sample;

	serial_init();
	fdevopen(serial_putchar, serial_getchar);

	adc_init();

	sei(); /* enable interrupts */

	while (1)
	{
		c = getchar();
		sample = adc_get(0);
		printf("adc sample is %d\n\r", sample);
	}

	return 1;
}
