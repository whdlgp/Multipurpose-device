/*
 * sensor_data.h
 *
 * Created: 2017-05-29 
 *  Author: ChoYG
 */ 


#ifndef SENSOR_DATA_H_
#define SENSOR_DATA_H_

#include <stdint.h>

typedef struct sensor_t 
{
	uint8_t keypad[16];
	uint8_t mode;
}sensor_t;

void sensor_data_clear();

sensor_t* sensor_data();

#endif /* SENSOR_DATA_H_ */