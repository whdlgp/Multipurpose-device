/*
 * gpio.h
 *
 * Created: 2017-05-26 
 *  Author: ChoYG
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include <avr/io.h>

#define gpio_init(x, dir) DDR##x = dir
#define gpio_write(x, val) PORT##x = val
#define gpio_read(x) PIN##x


#endif /* GPIO_H_ */