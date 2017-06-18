/*
 * time.c
 *
 * Created: 2017-05-27 
 *  Author: ChoYG
 */ 

#include "time.h"

volatile uint32_t _us;
volatile uint32_t _ms;

ISR(TIMER0_COMP_vect)
{
	_us++;

	static uint8_t i = 0;
	
	i++;
	
	if(i >= 10)
	{
		i = 0;
		_ms++;
	}
}

void time_init()
{
	TCCR0 = 0x0A; // 0000 1010 - clock/8 prescale & CTC 모드
	TCNT0 = 0; // R/W Count Value Register
	OCR0 = 16000000/10000/8; // Output Compare Value Register
	TIMSK |= 1 << OCIE0;   // Interrupt Requset Enable - 3 : CMP & OV 2 : CMP Int, 1 : OV Int
}

uint32_t millis()
{
	return _ms;
}

uint32_t micros()
{
	return _us*100;
}