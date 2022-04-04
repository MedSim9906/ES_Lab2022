/**
 * EduART OS
 * (c) ESLab, OTHR, 2022
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <avr/io.h>
#include <avr/pgmspace.h>


volatile uint8_t  	EventTrigger_Event1;
volatile uint8_t  	EventTrigger_Event2;

volatile uint8_t  	TimeSliceError;

volatile bool	 	USB_Notified;



#endif /*GLOBALS_H_*/
