/*
 * lcd.h
 *
 * Created: 2017-06-05 
 *  Author: ChoYG
 */ 


#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>

#define LCD_CTL_PORT 		PORTA // PORTG(RS : PG0, R/W : PG1, E : PG2)
#define LCD_DATA_PORT 		PORTC // PORTC(4bit : PC4-PC7, 8bit : PC0-PC7)
#define LCD_CTL_PORT_DDR 	DDRA //
#define LCD_DATA_PORT_DDR 	DDRC //
#define LCD_RS 				0 // RS : PG0
#define LCD_RW 				1 // R/W : PG1
#define LCD_E 				2 // E : PG2
#define LCD_COL 			16 // 캐릭터/라인

void lcd_init();
void lcd_print(uint8_t line, const char* str);

void lcd_process(uint32_t period_us);

#endif /* LCD_H_ */