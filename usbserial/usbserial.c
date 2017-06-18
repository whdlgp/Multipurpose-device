/*
 * usbserial.c
 *
 * Created: 2017-05-26 
 *  Author: ChoYG
 */ 

#include "usbserial.h"

void USB_begin(uint32_t baudrate)
{
		uint16_t baud_cal = 0;
		uint8_t baud_cal_high = 0;
		uint8_t baud_cal_low = 0;
		
		baud_cal = ((16000000/baudrate/16) - 1);
		baud_cal_high = (baud_cal >> 8) & 0xff;
		baud_cal_low = baud_cal & 0xff;
		
		UCSR0A=0x00;
		UCSR0B=0x18; //no interrupt
		UCSR0C=0x06;
		UBRR0H=baud_cal_high;
		UBRR0L=baud_cal_low;
}

uint8_t USB_read()
{
	return UDR0;
}

void USB_write(uint8_t val)
{
	while ( !(UCSR0A & (1<<UDRE0)) );
	
	UDR0 = val;
}

uint8_t USB_available()
{
	return (UCSR0A & (1<<RXC0)) >> RXC0;
}

void USB_print(const char* str)
{
	uint32_t i = 0;
	
	while(str[i] != 0)
	{
		USB_write((uint8_t)(str[i]));
		i++;
	}
}

void USB_printf(char *form, ...)
{
	char      buf[128];
	va_list   argptr;
	
	va_start(argptr, form);
	
	vsprintf(buf, form, argptr);
	
	USB_print(buf);
	
	va_end(argptr);
}