/*
 * sensor_read.c
 *
 * Created: 2017-05-29 
 *  Author: ChoYG
 */ 

#include "sensor_read.h"

#include "../gpio/gpio.h"
#include "../time/time.h"
#include "../sensor_data/sensor_data.h"

#include "../usbserial/usbserial.h"

void sensor_init()
{
	//mode select potentiometer to adc
	ADCSRA = ADCSRA
			| (0x01<<7) // ADC enable
			| (0x07); // 128 division
	
	ADMUX |= 1<<REFS0; //VCC ref
	
	ADMUX |= 0; //chennel select
	gpio_init(F, 0x00); //ADC input
	
	//keypad switch 
	gpio_init(B, 0x0f);
	gpio_write(B, 0xff);
	
	//debug
	USB_print("sensor_init\n");
}

void keypad_read(sensor_t* sensor)
{
	char c;
	// scan the first row ----------
	gpio_write(B, ~0x08);	
	asm("nop"::);
	
	c= ~(gpio_read(B) >> 4);
	
	if(c & 0x01)	sensor->keypad[0] = 1;
	else			sensor->keypad[0] = 0;
	
	if(c & 0x02)	sensor->keypad[4] = 1;
	else			sensor->keypad[4] = 0;
	
	if(c & 0x04)	sensor->keypad[8] = 1;
	else			sensor->keypad[8] = 0;
	
	if(c & 0x08)	sensor->keypad[12] = 1;
	else			sensor->keypad[12] = 0;
	
	// scan the second row----------
	gpio_write(B, ~0x04);
	asm("nop"::);
	
	c= ~(gpio_read(B) >> 4);
	
	if(c & 0x01)	sensor->keypad[1] = 1;
	else			sensor->keypad[1] = 0;
	
	if(c & 0x02)	sensor->keypad[5] = 1;
	else			sensor->keypad[5] = 0;
	
	if(c & 0x04)	sensor->keypad[9] = 1;
	else			sensor->keypad[9] = 0;
	
	if(c & 0x08)	sensor->keypad[13] = 1;
	else			sensor->keypad[13] = 0;
	
	// scan the third row----------
	gpio_write(B, ~0x02);
	asm("nop"::);
	
	c= ~(gpio_read(B) >> 4);
	
	if(c & 0x01)	sensor->keypad[2] = 1;
	else			sensor->keypad[2] = 0;
	
	if(c & 0x02)	sensor->keypad[6] = 1;
	else			sensor->keypad[6] = 0;
	
	if(c & 0x04)	sensor->keypad[10] = 1;
	else			sensor->keypad[10] = 0;
	
	if(c & 0x08)	sensor->keypad[14] = 1;
	else			sensor->keypad[14] = 0;	
	
	// scan the fourth row----------
	gpio_write(B, ~0x01);
	asm("nop"::);
	
	c= ~(gpio_read(B) >> 4);
	
	if(c & 0x01)	sensor->keypad[3] = 1;
	else			sensor->keypad[3] = 0;
	
	if(c & 0x02)	sensor->keypad[7] = 1;
	else			sensor->keypad[7] = 0;
	
	if(c & 0x04)	sensor->keypad[11] = 1;
	else			sensor->keypad[11] = 0;
	
	if(c & 0x08)	sensor->keypad[15] = 1;
	else			sensor->keypad[15] = 0;
}

void mode_select_read(sensor_t* sensor)
{
	uint8_t temp = 0;
	uint16_t adc_raw;
			
	ADCSRA = ADCSRA
			|(0x01<<6);// ADC start
			
	while(!(ADCSRA&(0x01<<4))); // wait ADC end
			
	temp = ADCL; //first, must be moved to another variable
			
	adc_raw = ((ADCH<<8)|temp);
	
	if(adc_raw > 750)
		sensor->mode = 0;
	else if(adc_raw > 500)
		sensor->mode = 1;
	else if(adc_raw > 250)
		sensor->mode = 2;
	else
		sensor->mode = 3;
}

void sensor_read_process(uint32_t period_us)
{	
	sensor_t* sensor;
	sensor = sensor_data();
	
	static uint32_t pre_time = 0;
	uint32_t time = micros();
	
	if((time - pre_time) > period_us)
	{
		keypad_read(sensor);
		mode_select_read(sensor);
		
		pre_time = time;
	}
}