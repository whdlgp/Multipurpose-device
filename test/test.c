/*
 * test.c
 *
 * Created: 2017-06-12 
 *  Author: ChoYG
 */ 

#include "test.h"
#include "../time/time.h"
#include "../sensor_data/sensor_data.h"
#include "../lcd/lcd.h"

void test_process(uint32_t period_us)
{
	uint8_t botton[17] = {0,};
	uint8_t mode[2] = {0,};
	
	sensor_t* sensor;
	sensor = sensor_data();
	
	static uint32_t pre_time = 0;
	uint32_t time = micros();
	
	if((time - pre_time) > period_us)
	{
		uint8_t i;
		for(i = 0; i < 16; i++)
		{
			botton[i] = sensor->keypad[i] + 48;
		}
		mode[0] = sensor->mode + 48;
		
		lcd_print(1, (char*)botton);
		lcd_print(2, (char*)mode);
		
		pre_time = time;
	}
}