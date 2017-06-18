/*
 * sensor_data.c
 *
 * Created: 2017-05-29 
 *  Author: ChoYG
 */ 

#include "sensor_data.h"

sensor_t sensor;

void sensor_data_clear()
{
	uint8_t i;
	for(i = 0; i < 16; i++)
	{
		sensor.keypad[i] = 0;
	}
	
	sensor.mode = 0;
}

sensor_t* sensor_data()
{
	return &sensor;
}