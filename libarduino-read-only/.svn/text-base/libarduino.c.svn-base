/* ***********************************************************************
**  libarduino - a GNU library for using GNU toolchain with Arduino
**  Copyright (C) 2009 Michael Spiceland
*************************************************************************
**
**  This program is free software; you can redistribute it and/or
**  modify it under the terms of the GNU General Public License
**  as published by the Free Software Foundation; either version 2
**  of the License, or (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software Foundation, 
**  Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
**
*************************************************************************/
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "libarduino.h"
#include "irkeys.h"

/* stuff used in all modes */
inline void onboard_led_enable(void) {
	setpin_out(DDRB, 5);
}

inline void onboard_led_on(void) {
	setpin(PORTB, 5);
}

inline void onboard_led_off(void) {
	clearpin(PORTB, 5);
}

/* arduino compatibility functions */
#ifdef ENABLE_ARDUINO_COMPAT /* subset of arduino functions */
void pinMode(uint8_t pin, enum pinmode mode)
{
	if (pin < 8)
	{	
		if (mode == INPUT)
			setpin_in(DDRD, pin);
		else
			setpin_out(DDRD, pin);
	} else {
		pin = pin - 8;
		if (mode == INPUT)
			setpin_in(DDRB, pin);
		else
			setpin_out(DDRB, pin);
	}
}

void digitalWrite(uint8_t pin, enum pinstate value)
{
	if (pin < 8)
	{	
		if (value == HIGH)
			setpin(PORTD, pin);
		else
			clearpin(PORTD, pin);
	} else {
		pin = pin - 8;
		if (value == HIGH)
			setpin(PORTB, pin);
		else
			clearpin(PORTB, pin);
	}
}

uint8_t digitalRead(uint8_t pin) 
{
	if (pin < 8)
		return (PIND & (1<<pin));
	else {
		pin = pin - 8;
		return (PINB & (1<<pin));
	}
}

#ifdef ENABLE_PWM
/* we have arduino api compat and pwm enabled */
void analogWrite(uint8_t pin, uint8_t value)
{
	switch(pin) {
	case 9:
		pwm_set(1, value);
		break;
	case 10:
		pwm_set(2, value);
		break;
	case 11:
		pwm_set(3, value);
		break;
	case 3:
		pwm_set(4, value);
		break;
	default:
		return;
		break;
	}
}
#endif 

#endif

#ifdef ENABLE_SERIAL
uint8_t uart_buffer[UART_BUFFER_SIZE];
volatile uint8_t uart_readptr;
volatile uint8_t uart_writeptr;

ISR(UART0_ISR_VECT)
{
	uart_buffer[uart_writeptr] = UART0_DATA;
	uart_writeptr = (uart_writeptr + 1) % UART_BUFFER_SIZE;
}

void serial_init(void)
{
	uart_writeptr = 0;
	uart_readptr = 0;

	// set default baud rate 
	UBRR0H = UART_BAUD_SELECT >> 8;  
	UBRR0L = UART_BAUD_SELECT;

	// enable receive, transmit and ensable receive interrupts 
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);

	/* dont forget sei() */
}

int serial_getchar(FILE* stream)
{
	uint8_t c;

	while( uart_writeptr == uart_readptr); /* block waiting */
	c = uart_buffer[uart_readptr];    	
	uart_readptr = (uart_readptr + 1) % UART_BUFFER_SIZE;
  
	return c;
}

int serial_putchar(char data, FILE* stream)
{   
	while ( !(UCSR0A & (1<<UDRE0)) ); /* block till we have space */
	UART0_DATA = data; /* send */
	return data;
}
#endif

#ifdef ENABLE_IR
volatile uint8_t ir_readptr = 0;
volatile uint8_t ir_writeptr = 0;
volatile uint8_t ir_buffer[IR_BUFFER_SIZE];

/*************************************************************************
 *  receive from IR Receiver - external interrupt 0 on pin PD2 (arduino pin 2)
 *
 * Use the external interrupt to decode the Sony IR protocol.  We use
 * both rising and falling edges to measure pulse widths.  The timer/counter
 * is needed to take these measurements.  If the address matches our device,
 * we store the command in a circular buffer for retreval outside of
 * interrupt context.
 *
 * tested with Vishay TSOP392 IR receiver and universal remote
 *************************************************************************/
ISR(INT0_vect)
{
	static uint8_t value;
	static uint8_t address;
	static uint8_t sigcount = 0;

	if (PIND & _BV(2)) { // rising edge
		unsigned short count;
		count = TCNT0;

		onboard_led_off();

#if (F_CPU == 16000000)
		if (count < 14) { // 0
#endif
#if (F_CPU == 8000000)
		if (count < 7) { // 0
#endif
			sigcount++;
			if (sigcount < 8) {
				value = value & ~(1 << (sigcount-1));
			} else {
				address = address & ~(1 << (sigcount-8));
			}
#if (F_CPU == 16000000)
		} else if (count < 30) { // 1
#endif
#if (F_CPU == 8000000)
		} else if (count < 15) { // 1
#endif
			sigcount++;
			if (sigcount < 8) {
				value = value | (1 << (sigcount-1));
			} else {
				address = address | (1 << (sigcount-8));
			}
		} else { // this starts a new one
			sigcount = 0;
			value = 0;
			address = 0;
		}

		/* we have a command and it is for us */
		if ((sigcount == 12) && ((address == 26) || (address == 17)
			|| (address == REMOTE_DEVICE_SONY_TV000)))
		{
			ir_buffer[ir_writeptr] = value;
			ir_writeptr = (ir_writeptr + 1) % IR_BUFFER_SIZE;
#ifdef IR_DEBOUNCE
			_delay_ms(200); /* debounce */
#endif
		}
		
	} else { // falling edge
		TCNT0 = 0; // reset
		onboard_led_on();
	}
}

/**************************************************************************
* ir_init
* AVR PD3 pin 5 - arduino digital pin 3
**************************************************************************/
void ir_init(void)
{
	setpin_in(DDRD, 2);

	/* 8-bit timer to count IR stuff */
	TCCR0B |= _BV(CS02) | _BV(CS00); //CLK / 64 for 8mhz
	TCNT0 = 0; //reset the timer

	/* we use external interrupt INT1 for the IR receiver */
	EICRA |= _BV(ISC00); // interrupt on rising and falling edge of INT1
	EIMSK |= _BV(INT0);  // enable int1 interrupts

	ir_readptr = 0;
	ir_writeptr = 0;
		
	enable_onboard_led();

	/* dont forget sei() */
}

/*************************************************************************
 * ir_get() 
 * 
 * blocks until we get the next IR value out of our buffer
 * returns the value of the command
 *************************************************************************/
uint8_t ir_get(void)
{
	uint8_t value;
	while( ir_writeptr == ir_readptr); /* block waiting for a value */
	value = ir_buffer[ir_readptr]; /* pull out a sampe*/
	ir_readptr = (ir_readptr + 1) % IR_BUFFER_SIZE;
	return value;
}

/*************************************************************************
 * ir_get_nonblock() 
 * 
 * returns the value of the command
 * returns 255 if there is not a new value for us
 *************************************************************************/
uint8_t ir_get_nonblock(void)
{
	if (ir_writeptr == ir_readptr) /* don't block waiting for a value */
		return 255;

	uint8_t value;
	value = ir_buffer[ir_readptr]; /* pull out a sample */
	ir_readptr = (ir_readptr + 1) % IR_BUFFER_SIZE;
	return value;
}
#endif

#ifdef ENABLE_PWMSERVO
/*************************************************************************
* pwmservo_init(pwmno)
* pwmno 1 & 2 are preferred b/c they provide higher resolution
* pwmno:
* 1 - OC1A (avr pin 15 PB1) - arduino digital pin 9
* 2 - OC1B (avr pin 16 PB2) - arduino digital pin 10
* 3 - OC2A (avr pin 17 PB3) - arduino digital pin 11
* 4 - OC2B (avr pin  5 PD3) - arduino digital pin 3
* 5 - OC0A (avr pin 12 PD6) - arduino digital pin 6  (conflicts with IR) FIXME
* 6 - OC0B (avr pin 11 PD5) - arduino digital pin 5  (conflicts with IR) FIXME
*************************************************************************/
void pwmservo_init(uint8_t pwmno)
{
	/* FIXME: need to reserve pins and counters at compile time */
	/* FIXME: conflict w/ IR if it runs at 8MHz */
	if (!pwmno || (pwmno > 6)) /* invalid */
		return;

	if ((pwmno == 1) || (pwmno == 2)) /* TCNT1 */
	{
		if (pwmno == 1) {
			setpin_out(DDRB, 1);
			OCR1A = SERVO_MID_POS16; /* initial value */
			TCCR1A |= _BV(COM1A1); /* turn on PWM 1 */
		}
		if (pwmno == 2) {
			setpin_out(DDRB, 2);
			OCR1B = SERVO_MID_POS16;
			TCCR1A |= _BV(COM1B1); /* turn on PWM 2 */
		}
		TCCR1A |= _BV(WGM11); /* PWM phase correct */
		TCCR1B |= _BV(WGM13) | _BV(WGM12); /* PWM phase correct */
		TCCR1B |= _BV(CS11);
#if (F_CPU == 16000000)
		ICR1 = 0x9C3F; /* 16bit */
#endif
#if (F_CPU == 8000000)
		ICR1 = 0x4E1F; /* 16bit */
#endif
		TCNT1H = 0;/* initial value */
		TCNT1L = 0;/* initial value */
	}

	if ((pwmno == 3) || (pwmno == 4)) /* TCNT1 */
	{
		if (pwmno == 3) {
			setpin_out(DDRB, 3);
			OCR2A = SERVO_MID_POS8; /* initial value */
			TCCR2A |= _BV(COM2A1); /* turn on PWM 1 */
		}
		if (pwmno == 4) {
			setpin_out(DDRD, 3);
			OCR2B = SERVO_MID_POS8;
			TCCR2A |= _BV(COM2B1); /* turn on PWM 2 */
		}
#if (F_CPU == 16000000)
		TCCR2A |= _BV(WGM20) | _BV(WGM21); /* fast PWM */
#endif
#if (F_CPU == 8000000)
		TCCR2A |= _BV(WGM20); /* fast PWM */
#endif
		TCCR2B |= _BV(CS20) | _BV(CS21) | _BV(CS22);
		TCNT2 = 0;/* initial value */
	}
	
}

void __pwmservo_set(uint8_t servo, uint16_t pwmval)
{
	//printf("__pwmservo_set setting %d\n\r", pwmval);
	if (servo == 1)
		OCR1A = pwmval;
	else if (servo == 2)
		OCR1B = pwmval;
	else if (servo == 3)
		OCR2A = pwmval;
	else if (servo == 4)
		OCR2B = pwmval;
}

/***************************************************************************
* pwmservo_set
* servo - 1-6 (servo number that we already called init on)
* pwmval - from 0-255 - provides the position for the servo
*          0 makes a 1.5ms pulse
*          255 makes a 2.5ms pulse
***************************************************************************/
void pwmservo_set(uint8_t servo, uint8_t pwmval)
{
	//printf("pwmservo_set setting %d to %d\n\r", servo, pwmval);

	if ((servo == 1) || (servo == 2))
		__pwmservo_set(
			servo,
			(((uint32_t)pwmval*((uint32_t)SERVO_MAX_POS16-(uint32_t)SERVO_MIN_POS16))/(uint32_t)256) + (uint32_t)SERVO_MIN_POS16
			);

	if ((servo == 3) || (servo == 4))
		__pwmservo_set(
			servo,
			(((uint32_t)pwmval*((uint32_t)SERVO_MAX_POS8-(uint32_t)SERVO_MIN_POS8))/(uint32_t)256) + (uint32_t)SERVO_MIN_POS8
			);
}

/* not tested yet
void pwmservo_setf(uint8_t servo, float pwmval)
{
	if (servo == 1)
		OCR1A = pwmval * 255.0;
	else if (servo == 2)
		OCR1B = pwmval * 255.0;
} */
#endif

#ifdef ENABLE_PWM
/*************************************************************************
* pwm_init(pwmno)
* pwmno:
* 1 - OC1A (avr pin 15 PB1) - arduino digital pin 9
* 2 - OC1B (avr pin 16 PB2) - arduino digital pin 10
* 3 - OC2A (avr pin 17 PB3) - arduino digital pin 11
* 4 - OC2B (avr pin  5 PD3) - arduino digital pin 3
* 5 - OC0A (avr pin 12 PD6) - arduino digital pin 6  (conflicts with IR) FIXME
* 6 - OC0B (avr pin 11 PD5) - arduino digital pin 5  (conflicts with IR) FIXME
*************************************************************************/
void pwm_init(uint8_t pwmno)
{
	/* FIXME: need to reserve pins and counters at compile time */
	if (!pwmno || (pwmno > 6)) /* invalid */
		return;

	if ((pwmno == 1) || (pwmno == 2)) /* TCNT1 */
	{
		if (pwmno == 1) {
			setpin_out(DDRB, 1);
			OCR1A = 0; /* initial value */
			TCCR1A |= _BV(COM1A1); /* turn on PWM 1 */
		}
		if (pwmno == 2) {
			setpin_out(DDRB, 2);
			OCR1B = 0;
			TCCR1A |= _BV(COM1B1); /* turn on PWM 2 */
		}
		TCCR1A |= _BV(WGM10); /* PWM 8bit */
		//TCCR1B |= _BV(WGM13) | _BV(WGM12); /* PWM phase correct */
		TCCR1B |= _BV(CS12); /* div by 256 */
		TCNT1H = 0;/* initial value */
		TCNT1L = 0;/* initial value */
	}

	if ((pwmno == 3) || (pwmno == 4)) /* TCNT1 */
	{
		if (pwmno == 3) {
			setpin_out(DDRB, 3);
			OCR2A = 0; /* initial value */
			TCCR2A |= _BV(COM2A1); /* turn on PWM 1 */
		}
		if (pwmno == 4) {
			setpin_out(DDRD, 3);
			OCR2B = 0;
			TCCR2A |= _BV(COM2B1); /* turn on PWM 2 */
		}
		TCCR2A |= _BV(WGM20); /* PWM 8bit */
		TCCR2B |= _BV(CS21) | _BV(CS22); /* div by 256 for ovfl 244hz*/
		TCNT2 = 0;/* initial value */
	}
	
}

/***************************************************************************
* pwm_set
* pwmchan - 1-6 (servo number that we already called init on)
* pwmval - from 0-255 - provides the position for the servo
*          0 makes a 1.5ms pulse
*          255 makes a 2.5ms pulse
***************************************************************************/
void pwm_set(uint8_t pwmchan, uint8_t pwmval)
{
	//printf("__pwm_set setting %d\n\r", pwmval);
	if (pwmchan == 1)
		OCR1A = pwmval;
	else if (pwmchan == 2)
		OCR1B = pwmval;
	else if (pwmchan == 3)
		OCR2A = pwmval;
	else if (pwmchan == 4)
		OCR2B = pwmval;
}

/* not tested yet
void pwm_setf(uint8_t pwmchan, float pwmval)
{
	if (pwmchan == 1)
		OCR1A = pwmval * 255.0;
	else if (servo == 2)
		OCR1B = pwmval * 255.0;
} */
#endif

#ifdef ENABLE_ADC
/***************************************************************************
* adc_init()
*  
* gets our ADC ready to take 10bit samples 
* compares analog input against voltage on AREF pin
* you probably want to connect AREF to VCC
***************************************************************************/
void adc_init(void)
{
	/* initialize the ADC - 10bit mode */
	//ADMUX |= _BV(ADLAR); /* uncomment for 8-bit mode */
	ADCSRA |= _BV(ADEN); // for now we don't do this in the ISR | _BV(ADIE);
	ADCSRA |= _BV(ADPS2) | _BV(ADPS1); 
	PRR &= ~_BV(PRADC);
	
	/* set up all of our analog pins to be inputs */
	/* FIXME: perhaps this should be dynamic */
	setpin_in(DDRC, 0);
	setpin_in(DDRC, 1);
	setpin_in(DDRC, 2);
	setpin_in(DDRC, 3);
	setpin_in(DDRC, 4);
	setpin_in(DDRC, 5);
}

/***************************************************************************
* adc_get()
* 
* adcnum - specifies which ADC pin you want to read from
*        - 0 through 5 corresponds to ADC0-ADC5 (avr pins 14-19) and
*          Arduino Analog pins 0-5.
*
* returns 16 bit unsigned value between 0 and 1024 with 0 meaning 0v and
*          1024 meaning at or above voltage on AREF pin
***************************************************************************/
uint16_t adc_get(uint8_t adcnum)
{
	static uint8_t current_adcnum = 9;

	if (adcnum > 5)
		return 0; /* invalid */
	
	if (adcnum != current_adcnum)
		ADMUX = (ADMUX & 0xF0) | adcnum; /* set up mux */
	current_adcnum = adcnum; /* cache for next time */

	ADCSRA |= (1 << ADSC); /* start ADC conversion */
	while (ADCSRA & (1 << ADSC)) {;} /* block for the result */
	return ADC;
}
#endif

