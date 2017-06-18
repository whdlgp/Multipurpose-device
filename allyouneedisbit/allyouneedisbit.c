/*
 * allyouneedisbit.c
 *
 * Created: 2017-06-16 
 *  Author: ChoYG
 */ 

#include "allyouneedisbit.h"

#include "../sensor_data/sensor_data.h"
#include "../time/time.h"
#include "../lcd/lcd.h"

uint64_t int_pow(uint8_t n, uint8_t x)
{
	uint8_t i;
	uint64_t a;
	a = n;
	
	switch (x)
	{
		case 0:
		return 1;
		case 1:
		return n;
		default:
		for (i = 1; i < x; ++i) {
			a *= n;
		}
		break;
	}
	return a;
}

void allyouneedisbit_run(sensor_t* sensor)
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
	
	//store input if key detected decimal
	static uint8_t str_10[16] = {0,};
	if(pressed_key < 10) 
	{
		uint8_t i;
		for(i = 0; i < 16; i++)
		{
			str_10[i] = str_10[i+1];
		}
		str_10[15] = pressed_key;
	}
	else if(pressed_key == 15)
	{
		uint8_t i;
		for(i = 0; i < 16; i++)
		{
			str_10[i] = 0;
		}
	}
	
	uint64_t input_integer = 0;
	uint8_t bit_count = 0;
	
	for(i = 0; i < 16 ; i++)
	{
		input_integer += str_10[15-i] * int_pow(10, i);
	}
	
	for(i = 64; i >= 1; i--)
	{
		if(((input_integer >> (i-1)) & 0x1) == 0x1)
		{
			bit_count = i;
			break;
		}
		else
		{
			bit_count = 0;
		}
	}
	
	uint8_t str_10_ascii[17] = {0,};
	uint8_t str_bitcount[17] = {0,};
	
	for(i = 0; i < 16; i++)
	{
		str_10_ascii[i] = str_10[i] + 48;
	}
	
	str_bitcount[0] = 'Y';
	str_bitcount[1] = 'o';
	str_bitcount[2] = 'u';
	str_bitcount[3] = ' ';
	
	str_bitcount[4] = 'n';
	str_bitcount[5] = 'e';
	str_bitcount[6] = 'e';
	str_bitcount[7] = 'd';
	str_bitcount[8] = ' ';	
	
	str_bitcount[9] = (bit_count / 10) + 48;
	str_bitcount[10] = (bit_count % 10) + 48;
	str_bitcount[11] = ' ';

	str_bitcount[12] = 'b';
	str_bitcount[13] = 'i';
	str_bitcount[14] = 't';
	
	lcd_print(1, (char*)str_10_ascii);
	lcd_print(2, (char*)str_bitcount);
}

void allyouneedisbit_process(uint32_t period_us)
{
	sensor_t* sensor;
	sensor = sensor_data();
	
	static uint32_t pre_time = 0;
	uint32_t time = micros();
	
	if((time - pre_time) > period_us)
	{
		allyouneedisbit_run(sensor);
		
		pre_time = time;
	}
}