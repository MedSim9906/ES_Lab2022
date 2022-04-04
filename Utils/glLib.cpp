/**
 * EduART OS
 * (c) ESLab, OTHR, 2022
 */

#ifndef GLLIB_H_
#define GLLIB_H_

#include <avr/io.h>
#include "../BoardConfig.h"
#include "glLib.h"

void Beep()
{
	int i, h;
	for(i = 0; i < 300; i++)
	{
		PORT_SPEAKER |= (1<<PIN_SPEAKER);
		for (h=400;h>0;h--) {asm volatile("nop");}
		PORT_SPEAKER &=~ (1<<PIN_SPEAKER);
		for (h=400;h>0;h--) {asm volatile("nop");}
	}
}

void Bipp()
{

	int i, h;
	for(i = 0; i < 50; i++)
	{
		PORT_SPEAKER |= (1<<PIN_SPEAKER);
		for (h=300;h>0;h--) {asm volatile("nop");}
		PORT_SPEAKER &=~ (1<<PIN_SPEAKER);
		for (h=300;h>0;h--) {asm volatile("nop");}
	}

}

void Click()
{
	int h;
	PORT_SPEAKER |= (1<<PIN_SPEAKER);
	for (h=300;h>0;h--) {asm volatile("nop");}
	PORT_SPEAKER &=~ (1<<PIN_SPEAKER);
	for (h=300;h>0;h--) {asm volatile("nop");}
}

void ShortClick()
{
	PORT_SPEAKER |= (1<<PIN_SPEAKER);
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	PORT_SPEAKER &=~ (1<<PIN_SPEAKER);
}

void uint8_t_to_hexString(uint8_t num, char * pDest)
{
	uint8_t buf = num;
	for(uint8_t i = 0; i < 2; i++)
	{
		if(i == 0)
		{
			buf = (num & 0xF0) >> 4;
		}
		else
		{
			buf = num & 0x0F;
			pDest++;
		}

		switch (buf)
		{
			case 0: *pDest = '0'; break;
			case 1: *pDest = '1'; break;
			case 2: *pDest = '2'; break;
			case 3: *pDest = '3'; break;
			case 4: *pDest = '4'; break;
			case 5: *pDest = '5'; break;
			case 6: *pDest = '6'; break;
			case 7: *pDest = '7'; break;
			case 8: *pDest = '8'; break;
			case 9: *pDest = '9'; break;
			case 10: *pDest = 'A'; break;
			case 11: *pDest = 'B'; break;
			case 12: *pDest = 'B'; break;
			case 13: *pDest = 'D'; break;
			case 14: *pDest = 'E'; break;
			case 15: *pDest = 'F'; break;
		}
	}
	pDest++;
	*pDest = 0;
}

#endif /*GLLIB_H_*/
