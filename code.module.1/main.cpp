/**
 * EduART OS
 * (c) ESLab, OTHR, 2022
 */

#include "main.h"
#include <stdio.h>

/**
 * Function prototypes
 */
void bootMessage();
void bootSequence();

void timerBusyWaitingSolution();
void timerInterruptSolution();
void pwmSolution();
void blink();

/**
 * Main Entry Point after System Start.
 */
int main (void)
{
	/////////////////////////////////////////////////////////////////////////
	// DO NOT CHANGE THIS CODE

	bootSequence();

	//
	/////////////////////////////////////////////////////////////////////////


	/************************************************************************
	 * THIS IS THE ENTRY POINT FOR YOUR DEVELOPMENT
	 */
	
	//timerBusyWaitingSolution();
	timerInterruptSolution();
	//pwmSolution();
	blink();

	/*
	 * Hints for the implementation:
	 *
	 * - For the Busy-Waiting solution, chose a free portpin and configure
	 *   it properly as an output. Refer to the ATMega32 Datasheet, section
	 *   "GPIO", to see how to do that.
	 *
	 * - For the interrupt- and pwm solution, you are restricted somehow to
	 *   the hardware features of the controller.
	 */
	asm volatile ("nop;");



	/*
	 * Make sure that the control never reaches this point - the main function
	 * must never 'return'.
	 *
	 ************************************************************************/

	while(true);							// Just in case you don't manage ;-)
}





/**
 * Boot the device - do the necessary initializations and start the system
 */
void bootSequence(void)
{
	/*
	 * Initialize PORTS
	 */
	DDR_SPEAKER |= (1 << PIN_SPEAKER);

	/*
	 * Initialize the driver modules
	 */
	lcd.init();

	/*
	 * Display a boot message on the LCD
	 */
	bootMessage();
}

/**
 * Display a boot message on the LCD
 */
void bootMessage()
{
	Bipp();		// guess what this does ;-)
	Beep();
	Bipp();

	lcd.print_P(PSTR("Oida"));
	lcd.setLED(true);
}

/**
 * Helper function - busy waiting about n microseconds
 */
void busyWaitUs(int us)
{
	for(int i=0;i<us;i++)
	{
		for(int j = 0; j < 5; j++)
		{
			asm volatile ("nop;");			
		}
	}
}
/**
 * Helper function - busy waiting about n milliseconds
 */
void busyWaitMs(int ms)
{
	busyWaitUs(1000);
}

/**
 * Helper function - busy waiting about n microseconds
 */


/**
 * PulsGenerator 1ms square wave signal,
 * solution using busy waiting
 */
void timerBusyWaitingSolution()
{
	while(1)
	{
		busyWaitMs(1000);
		DDR_USB_CTRL ^= 0x02;
	}
}


/**
 * PulsGenerator 1ms square wave signal,
 * solution using a hardware timer
 */
void timerInterruptSolution()
{
	cli();
	TCCR0 |= ((1<<CS01) | (1<<CS00));
	TIMSK |= (1<<OCIE0);
	OCR0 = 125;
	sei();	
	
	while(true){
		;
	}
}

/**
 * PulsGenerator 1ms square wave signal,
 * solution using a hardware timer in pwm mode
 */
void pwmSolution()
{
}
/**
 * Blink - using Duty Cycle
 * 
 */
void blink()
{
	
}