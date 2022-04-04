/**
 * EduART OS
 * (c) ESLab, OTHR, 2022
 */

#ifndef INTHANDLERS_H_
#define INTHANDLERS_H_


ISR(TIMER0_COMP_vect)
{
	TCNT0 = 0u;
	DDR_USB_CTRL ^= 0x02;

	sei();
}

ISR(TIMER1_COMPA_vect)
{

}


ISR(TIMER2_COMP_vect)
{
}

ISR(INT0_vect)
{

}

ISR(INT1_vect)
{

}


#endif /*INTHANDLERS_H_*/
