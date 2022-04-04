/**
 * EduART OS
 * (c) ESLab, OTHR, 2022
 */

using namespace std;
#ifndef BOARDCONFIG_H_
#define BOARDCONFIG_H_

#define PORT_DIRECTION_OUTPUT		0xFF
#define PORT_DIRECTION_INPUT		0x00
#define PIN_DIRECTION_OUTPUT		1
#define PIN_DIRECTION_INPUT			0


/**
 * Port assignments
 */
#define PORT_SPEAKER 					PORTD
#define DDR_SPEAKER						DDRD

#define PORT_USB_CTRL					PORTC
#define PORT_USB_DATA					PORTA
#define PIN_USB_CTRL					PINC
#define PIN_USB_DATA					PINA
#define DDR_USB_DATA					DDRA
#define DDR_USB_CTRL					DDRC

#define PORT_LCD						PORTB
#define DDR_LCD							DDRB



/**
 * Pin assignments
 */

#define PIN_SPEAKER						7
#define PIN_RTCOMM_LINKSTATE			5
#define PIN_RTCOMM_IDLE					4

#define PIN_USB_RD						0
#define PIN_USB_WR						1
#define PIN_USB_TXE						2
#define PIN_USB_RXF						3

#define PIN_LCD_RS						0
#define PIN_LCD_RW						1
#define PIN_LCD_EN						2
#define PIN_LCD_LED						3
#define PIN_LCD_DB4 					4
#define PIN_LCD_DB5						5
#define PIN_LCD_DB6						6
#define PIN_LCD_DB7						7

#define PIN_UART_RX						0
#define PIN_UART_TX						1



/**
 * Stack sizes
 */
#define DEF_STACKSIZE_STD 				125
#define DEF_STACKSIZE_APPLICATION1 		100
#define DEF_STACKSIZE_APPLICATION2		100
#define DEF_STACKSIZE_COORDINATOR		125
#define DEF_STACKSIZE_USB				100
#define DEF_STACKSIZE_RTCOMM			250
#define DEF_STACKSIZE_IDLE				50

/**
 * CSPQueue size and threshold
 */
#define DEF_CSPQSize				 	15
#define DEF_CSPQ_THRESHOLD				7


/**
 * Constants for conditional compilation
 */
#define DEF_USB_CSP_ENABLE
#define DEF_COORD_DISPLAY_ENABLE



#endif /*BOARDCONFIG_H_*/
