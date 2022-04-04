/**
 * EduART OS
 * (c) ESLab, OTHR, 2022
 */

#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <stdlib.h>
#include "../Utils/glLib.h"
#include "../BoardConfig.h"
#include <avr/interrupt.h>
#include <avr/pgmspace.h>


class LCD
{

private:
	static const uint8_t DB0 = 0;
	static const uint8_t DB1 = 1;
	static const uint8_t DB2 = 2;
	static const uint8_t DB3 = 3;
	static const uint8_t DB4 = 4;
	static const uint8_t DB5 = 5;
	static const uint8_t DB6 = 6;
	static const uint8_t DB7 = 7;

private:
	/*
	 * See datasheet_lcd_162c.pdf in "Tools&Docs" for these definitions
	 */
	static const uint8_t LCD_CMD_DISPLAY_INIT		= (1<<DB0)|(1<<DB1);
	static const uint8_t LCD_CMD_DISPLAY_CLEAR 		= (1<<DB0);
	static const uint8_t LCD_CMD_DISPLAY_ON 		= (1<<DB3)|(1<<DB2);
	static const uint8_t LCD_CMD_DISPLAY_OFF		= (0<<DB3);
	static const uint8_t LCD_CMD_CURSOR_ON			= (1<<DB1);
	static const uint8_t LCD_CMD_CURSOR_OFF			= (0<<DB1);
	static const uint8_t LCD_CMD_CURSOR_BLINK_ON 	= (1<<DB0);
	static const uint8_t LCD_CMD_CURSOR_BLINK_OFF	= (0<<DB0);
	static const uint8_t LCD_CMD_SET_4BIT_IFC		= (0<<DB4);
	static const uint8_t LCD_CMD_SET_8BIT_IFC		= (1<<DB4);
	static const uint8_t LCD_CMD_SET_1LINE			= (0<<DB3);
	static const uint8_t LCD_CMD_SET_2LINE			= (1<<DB3)|(1<<DB2)|(1<<DB5);
	static const uint8_t LCD_CMD_RETURN_HOME		= (1<<DB1);

private:
	void enable();
	void putCmd(uint8_t c);
	void writeNibble(char n);
	void delay(int ms);

public:
	LCD();
	~LCD();
	void init();
	void cls();
	void setLine(uint8_t line);
	void putChar(char c);
	void print(const char * str);
	void print_P(const char * str);
	void print(int num);
	void setLED(bool on);
};

#endif /*LCD_H_*/
