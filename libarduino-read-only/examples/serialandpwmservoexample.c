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
	uint8_t i;
	uint8_t c;
	uint8_t servo_pos = 0;
	uint8_t servo_num = 1;

	serial_init();
	fdevopen(serial_putchar, serial_getchar);

	for (i=1; i<5; i++) {
		pwmservo_init(i);
	}

	sei(); /* enable interrupts */

	while (1)
	{
		c = getchar();

		if (c == 'u') { /* u */
			servo_pos++;
			printf("setting servo to %d\n\r", servo_pos);
			pwmservo_set(servo_num, servo_pos);

		} else if (c == 'd') { /* d*/
			servo_pos--;
			printf("setting servo to %d\n\r", servo_pos);
			pwmservo_set(servo_num, servo_pos);

		} else if (c == 'n') { /* n */
			servo_num++;
			if (servo_num > 4)
				servo_num = 1;
			printf("now controlling servo %d\n\r", servo_num);

		} else
			printf("ignoring %d\n\r", c);
	}

	return 1;
}
