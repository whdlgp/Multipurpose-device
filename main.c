/*
 * MC_E02SM3_lib.cpp
 *
 * Created: 2017-05-26 
 *  Author: ChoYG
 */ 


#include <avr/io.h>
#include "gpio/gpio.h"
#include "usbserial/usbserial.h"
#include "time/time.h"
#include "sensor_data/sensor_data.h"
#include "sensor_read/sensor_read.h"
#include "stopwatch/stopwatch.h"
#include "bit_calculator/bit_calculator.h"
#include "allyouneedisbit/allyouneedisbit.h"
#include "lcd/lcd.h"

#include "test/test.h"

int main(void)
{
	//USB serial init for test print
	USB_begin(19200);
	
	//time initialize
	time_init();
	
	//sensor data structure zerofill
	sensor_data_clear();
	sensor_t* sensor;
	sensor = sensor_data();
	
	//sensor hardware initialize
	sensor_init();
	
	//lcd initialize
	lcd_init();
	//led initialize
	gpio_init(D, 0xf0);
	sei();
    
	while(1)
    {
		sensor_read_process(10000);//10ms
		
		//print mode number to LED
		gpio_write(D, ~((1 << sensor->mode) << 4) & 0xf0);
		
		//select mode
		switch(sensor->mode)
		{
			case 0:
			//bit calculator
			bit_calculator_process(50000); //50ms
			break;
			
			case 1:
			//stopwatch
			stopwatch_process(50000); //50ms
			break;
			
			case 2:
			//count the size of bit
			allyouneedisbit_process(50000); //50ms
			break;
			
			default:
			test_process(100000); //100ms
			break;
		}
		
		lcd_process(200000); //200ms
	}
}