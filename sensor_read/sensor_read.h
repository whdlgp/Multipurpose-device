/*
 * sensor_read.h
 *
 * Created: 2017-05-29 
 *  Author: ChoYG
 */ 


#ifndef SENSOR_READ_H_
#define SENSOR_READ_H_

#include <stdint.h>

void sensor_init();
void sensor_read_process(uint32_t period_us);

#endif /* SENSOR_READ_H_ */