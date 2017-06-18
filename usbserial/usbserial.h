/*
 * usbserial.h
 *
 * Created: 2017-05-26 
 *  Author: ChoYG
 */ 


#ifndef USBSERIAL_H_
#define USBSERIAL_H_

#include <stdint.h>
#include <avr/io.h>
#include <stdarg.h>
#include <stdio.h>

void USB_begin(uint32_t baudrate);

uint8_t USB_read();
void USB_write(uint8_t val);
void USB_print(const char* str);
void USB_printf(char *form, ...);
uint8_t USB_available();

#endif /* USBSERIAL_H_ */