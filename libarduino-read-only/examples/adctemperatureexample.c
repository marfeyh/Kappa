/********************************************************************
* libarduino example
********************************************************************/
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>
#include "libarduino.h"

/*************************************************************************
* getTempF - return the temp in Farenheight from 
*            Vishay thermistor NTCLE100E3103JB0
* v10bit - 10 bit value read from the A/D
* pdRes - value (in ohms) of the resistor that is in series with thermistor
*************************************************************************/
double getTempF(double v10bit, double pdRes)
{
	if (v10bit == 1024)
		return -1;

	// with therm on the bottom 
	double thermResistance = (pdRes * v10bit / 1024.0)/(1.0 - (v10bit/1024.0));

	// with therm on the top
	//double thermResistance = (pdRes * (1.0 - v10bit / 1024.0))/(v10bit/1024.0);
	//return thermResistance;

	double thermRefResistance = 10000.0;

	// Steinhart and Hart constants for Vishay thermistor NTCLE100E3103JB0
	double a = 3.354016 * pow(10, -3);
	double b = 2.56985 * pow(10, -4);
	double c = 2.620131 * pow(10, -6);
	double d = 6.383091 * pow(10, -8);

	//return v10bit;

	double celcius = 1.0/(a + b * log(thermResistance/thermRefResistance) + c * pow(log(thermResistance/thermRefResistance), 2) + d * pow(log(thermResistance/thermRefResistance), 3)) - 272.15;

	double farenheit = 9.0/5.0 * celcius + 32.0;

	return farenheit;
}

/***************************************************************************
* double2string
* convert a double to a string and place it in a pre-allocated space
***************************************************************************/
inline void double2string (double value, uint8_t* string)
{
	int temp;

	/* prep the string */
	string[2] = '.';
	string[5] = '\0';

	temp=(int16_t)(value * 10.0);   //to include decimal point for display
	if((value*10.0 - temp) >= 0.5) temp=temp+1;
	if(temp < 0)
	{
	  temp *= -1;
	}
	
	string[3] = ((uint8_t)(temp%10)) | 0x30;
	temp=temp/10;
	
	string[1] = ((uint8_t)(temp%10)) | 0x30;
	temp=temp/10;
	
	string[0] = ((uint8_t)(temp%10)) | 0x30;
	temp=temp/10;
	
}

int main (void)
{
	uint8_t c;
	uint16_t sample;
	double temperature;
	uint8_t tmp_string[] = "xx.x";

	serial_init();
	fdevopen(serial_putchar, serial_getchar);

	adc_init();

	sei(); /* enable interrupts */

	while (1)
	{
		/* once a sec */
		for (c=0; c<100; c++)
			_delay_ms(10);
		sample = adc_get(0);
		temperature = getTempF((double)sample, 10000);
		double2string(temperature, tmp_string);
		printf("%s\n\r", tmp_string);
	}

	return 1;
}
