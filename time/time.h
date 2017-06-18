/*
 * time.h
 *
 * Created: 2017-05-27 
 *  Author: ChoYG
 */ 


#ifndef TIME_H_
#define TIME_H_

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void time_init();

uint32_t millis();
uint32_t micros();

#endif /* TIME_H_ */