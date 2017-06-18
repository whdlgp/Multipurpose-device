/*
 * bit_calculator.c
 *
 * Created: 2017-05-29 
 *  Author: ChoYG
 */ 

#include "../usbserial/usbserial.h"

#include "../gpio/gpio.h"
#include "../time/time.h"
#include "../sensor_data/sensor_data.h"
#include "../lcd/lcd.h"

void bit_calculator_run(sensor_t* sensor)
{
	uint8_t pressed_key = 16; //if 16, means no key detected
	
	//detect which key pressed or not
	static uint8_t pre_keypad[16] = {0,};
	uint8_t i;
	for(i = 0; i < 16; i++)
	{
		if((pre_keypad[i] != sensor->keypad[i]) //key changed?
			&& (sensor->keypad[i] != 0))//check key pressed
		{
			pressed_key = i;
		}
		pre_keypad[i] = sensor->keypad[i];
	}
	
	//key detected, store 4 16bit character 
	static uint8_t str_16[5] = {0,};
	if(pressed_key != 16) 
	{
		str_16[0] = str_16[1];
		str_16[1] = str_16[2];
		str_16[2] = str_16[3];
		str_16[3] = pressed_key;
	}
	
	static uint8_t str_2[17] = {0,};
	for(i = 0; i < 4; i++)
	{
		str_2[i*4] = (str_16[i] >> 3) & 0x01;
		str_2[i*4+1] = (str_16[i] >> 2) & 0x01;
		str_2[i*4+2] = (str_16[i] >> 1) & 0x01;
		str_2[i*4+3] = str_16[i] & 0x01;
	}
	
	char str_16_ascii[17] = {'0',};
	
	str_16_ascii[0] = 'H';
	str_16_ascii[1] = 'E';
	str_16_ascii[2] = 'X';
	str_16_ascii[3] = ' ';
	
	for(i = 0; i < 4; i++)
	{
		if(str_16[i] < 10)
			str_16_ascii[i+4] = (char)(str_16[i] + (uint8_t)'0');
		else
			str_16_ascii[i+4] = (char)(str_16[i] - 10 + (uint8_t)'A');
	}
	
	str_16_ascii[8] = ' ';
	str_16_ascii[9] = 't';
	str_16_ascii[10] = 'o';
	str_16_ascii[11] = ' ';
	
	str_16_ascii[12] = 'B';
	str_16_ascii[13] = 'I';
	str_16_ascii[14] = 'N';
	
	char str_2_ascii[17] = {'0',};
	for(i = 0; i < 16; i++)
	{
		str_2_ascii[i] = (char)(str_2[i] + (uint8_t)'0');
	}
	
	//print str_16 and str_2 with LCD driver
	lcd_print(1, str_16_ascii);
	lcd_print(2, str_2_ascii);
	
	//USB_print("bit_calculator_run\n");
}

void bit_calculator_process(uint32_t period_us)
{
	sensor_t* sensor;
	sensor = sensor_data();
	
	static uint32_t pre_time = 0;
	uint32_t time = micros();
	
	if((time - pre_time) > period_us)
	{
		bit_calculator_run(sensor);
		
		pre_time = time;
	}
}