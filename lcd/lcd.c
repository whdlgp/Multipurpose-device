/*
 * lcd.c
 *
 * Created: 2017-06-05 
 *  Author: ChoYG
 */ 

#ifndef F_CPU

#define F_CPU 16000000UL

#endif

#include "lcd.h"

#include "../gpio/gpio.h"
#include "../time/time.h"
#include "../usbserial/usbserial.h"

#include <avr/io.h> // define port name
#include <util/delay.h> // define delay function

uint8_t lcd_buf_firstline[17];
uint8_t lcd_buf_secondline[17];

// global variable
uint8_t columns; // character number
uint8_t lines; // save current line

void LcdE(void)
{
	LCD_CTL_PORT |= _BV(LCD_E); // E = 0
	//_delay_us(300);
	LCD_CTL_PORT &= ~_BV(LCD_E); // E = 1
	_delay_ms(1);
}// clear LCD

void LcdCommand(uint8_t cmd)
{
	LCD_CTL_PORT = 00;
	LCD_DATA_PORT = cmd; //
	LcdE();
}// output data

void LcdData(uint8_t data)
{
	LCD_CTL_PORT |= _BV(LCD_RS);
	LCD_DATA_PORT = data;
	LcdE();
	++columns; // increase character number by 1
}

void LcdClear(void)
{
	LcdCommand(0x01);
}

void LcdLine(uint8_t row)
{
	columns = 0;
	lines = row;

	switch(row)
	{
		case 1: // first line
		LcdCommand(0x80);
		break;

		case 2: // second line
		LcdCommand(0xC0);
		break;

		default : ;
	}
}

void lcd_init()
{
	LCD_DATA_PORT_DDR = 0xFF; // data port : output mode
	LCD_CTL_PORT_DDR = 0x07; // control port : output mode
	LCD_CTL_PORT = 0;
	// initial LCD
	LcdCommand(0x30); _delay_ms(50); _delay_ms(100);
	LcdCommand(0x30); _delay_ms(50); _delay_ms(3);
	LcdCommand(0x30); _delay_ms(50); _delay_ms(1);
	LcdCommand(0x30); _delay_ms(50); _delay_us(100);
	LcdCommand(0x38); _delay_ms(50); _delay_us(40);
	LcdCommand(0x08); _delay_ms(50); _delay_us(40);
	LcdCommand(0x01); _delay_ms(50); _delay_us(40);
	LcdCommand(0x06); _delay_ms(50); _delay_us(40);
	LcdCommand(0x0C); _delay_ms(50); _delay_us(40); //display on, cursor off
	LcdClear(); _delay_ms(50); 
	columns = 0;
	lines = 1;
}

void lcd_print(uint8_t line, const char* str)
{
	uint32_t i = 0;
	
	if(line == 1)
	{
		while(str[i] != 0)
		{
			lcd_buf_firstline[i] = (uint8_t)str[i];
			i++;
		}	
		lcd_buf_firstline[i] = 0;
	}
	else if(line == 2)
	{
		while(str[i] != 0)
		{
			lcd_buf_secondline[i] = (uint8_t)str[i];
			i++;
		}
		lcd_buf_secondline[i] = 0;
	}
	else
	{
		USB_print("\"line\" must be 1 or 2\n");
	}
}

void LcdStringConst(const char *str)
{
	while(*str) LcdData(*str++);
}

void lcd_process(uint32_t period_us)
{	
	static uint32_t pre_time = 0;
	uint32_t time = micros();
	
	if((time - pre_time) > period_us)
	{	
		LcdClear();
		LcdLine(1);
		LcdStringConst((char*)lcd_buf_firstline);
		LcdLine(2);
		LcdStringConst((char*)lcd_buf_secondline);
		
		pre_time = time;
	}
}