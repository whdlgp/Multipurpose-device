/*
 * stopwatch.c
 *
 * Created: 2017-05-29 
 *  Author: ChoYG
 */ 

#include <avr/io.h>
#include "stopwatch.h"

#include "../gpio/gpio.h"
#include "../usbserial/usbserial.h"

#include "../time/time.h"
#include "../sensor_data/sensor_data.h"

#include "../lcd/lcd.h"

void stopwatch_run(sensor_t* sensor)
{
	uint8_t pressed_key = 16; //if 16, means no key detected
	
	//detect which key pressed or not
	static uint8_t pre_keypad[3] = {0,};
	uint8_t i;
	for(i = 0; i < 3; i++)
	{
		if((pre_keypad[i] != sensor->keypad[i]) //key changed?
		&& (sensor->keypad[i] != 0))//check key pressed
		{
			pressed_key = i;
		}
		pre_keypad[i] = sensor->keypad[i];
	}
	
	static uint8_t stopwatch_state = 2; //initial state is 'clear'
	
	static uint8_t time_tic = 0; //store time, 1 means 50ms
	static uint8_t time_ms100 = 0; //store time, 1 means 100ms
	static uint8_t time_sec = 0; //store time, 1 means 1sec
	static uint8_t time_min = 0; //store time, 1 means 1minute
	
	//key detected, determine how to calculate timer variable
	if(pressed_key != 16)
	{
		stopwatch_state = pressed_key;
	}
	
	//calculate timer variable according to determined state
	switch(stopwatch_state)
	{
		case 0: //start
		time_tic++;
		if(time_tic == 2)
		{
			time_ms100++;
			time_tic = 0;
		}
		if(time_ms100 == 10)
		{
			time_sec++;
			time_ms100 = 0;
		}
		if(time_sec == 60)
		{
			time_min++;
			time_sec = 0;
		}
		if(time_min == 60)
		{
			time_min = 0;
		}
		break;
		
		case 1: //stop
		//do nothing
		break;
		
		case 2: //clear
		time_tic = 0;
		time_ms100 = 0;
		time_sec = 0;
		time_min = 0;
		break;
		
		default:
		break;
	}
	//print stopwatch time
	
	uint8_t str[11] = {0,};
	str[0] = time_min/10 + 48;
	str[1] = time_min%10 + 48;
	str[2] = 'M';
	str[3] = ' ';
	
	str[4] = time_sec/10 + 48;
	str[5] = time_sec%10 + 48;
	str[6] = ',';
	str[7] = time_ms100%10 + 48;
	str[8] = 'S';
	
	lcd_print(1, "Run0 Stop1 Clr2");
	lcd_print(2, (char*)str);
}

void stopwatch_process(uint32_t period_us)
{
	sensor_t* sensor;
	sensor = sensor_data();
	
	static uint32_t pre_time = 0;
	uint32_t time = micros();
	
	if((time - pre_time) > period_us)
	{
		stopwatch_run(sensor);
		
		pre_time = time;
	}
}