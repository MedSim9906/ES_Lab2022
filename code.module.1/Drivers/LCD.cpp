/**
 * EduART OS
 * (c) ESLab, OTHR, 2022
 */

#include "LCD.h"

using namespace std;


LCD::LCD()
{
	DDR_LCD = 0xFF;
}

LCD::~LCD()
{
}

void LCD::init()
{
	// Prepare the Port: EN has to be high, falling edge signals "Enable"
	PORT_LCD = (1<<PIN_LCD_EN);

	writeNibble(LCD_CMD_DISPLAY_INIT);	delay(15);
	writeNibble(LCD_CMD_DISPLAY_INIT);	delay(15);
	writeNibble(LCD_CMD_DISPLAY_INIT);	delay(15);
	writeNibble(LCD_CMD_RETURN_HOME);	delay(5);
	putCmd(LCD_CMD_DISPLAY_CLEAR);		delay(5);
	putCmd(LCD_CMD_DISPLAY_OFF);		delay(5);
	putCmd(LCD_CMD_SET_2LINE);			delay(5);
	putCmd(LCD_CMD_DISPLAY_CLEAR);		delay(5);
	putCmd(LCD_CMD_DISPLAY_ON);			delay(5);
}

void LCD::delay(int ms)
{
	int i, h;
	for(i = 0; i < ms; i++)
	{
		for (h=1297;h>0;h--)
		{	asm volatile("nop");
			asm volatile("nop");
			asm volatile("nop");
			asm volatile("nop");
			asm volatile("nop");
			asm volatile("nop");
			asm volatile("nop");
			asm volatile("nop");
		}
	}
}



/*
 * Interface methods
 */

/**
 * @brief Clears the display and returns the cursor
 */
void LCD::cls()
{
	putCmd(LCD_CMD_DISPLAY_CLEAR);
	delay(75);
}

/**
 * @brief Sets the curser to the first character of <line>
 * @param line 1 = upper line, 2 = lower line.
 */
void LCD::setLine(uint8_t line)
{
	uint8_t cmd;
	if(line == 1)
	{
		cmd = (1<<DB7);
	}
	else
	{
		cmd = (1<<DB7) | 0x40;
	}
	putCmd(cmd);
}

/**
 * @brief Prints the zero-terminated string at the current cursor
 * position. Line-wrapping is not handled! Be sure that the string
 * is not longer than the number of remaining characters in the
 * current line.
 * @param str zero-terminated string to print.
 */
void LCD::print(const char * str)
{
	uint8_t i = 0;
	while(*(str+i) != 0)
	{
		putChar(*(str+i));
		i++;
	}
}

/**
 * @brief Prints the zero-terminated string at the current cursor
 * position. Line-wrapping is not handled! Be sure that the string
 * is not longer than the number of remaining characters in the
 * current line.
 * This function accesses the given address in the PROGRAM memory,
 * not in the RAM. The string constants have to be defined as
 * PSTR("<string to print>");
 * which requires the header file <avr/pgmspace.h>.
 * @param str zero-terminated string to print in program memory
 */
void LCD::print_P(const char * str)
{
	uint8_t i = 1;
	char c = pgm_read_byte(str);
	while(c != 0)
	{
		putChar(c);
		c = pgm_read_byte(str+i);
		i++;
	}
}

/**
 * @brief Prints the int at the current cursor position.
 * Line-wrapping is not handled! Be sure that the string
 * is not longer than the number of remaining characters in the
 * current line.
 * @param str zero-terminated string to print.
 */
void LCD::print(int num)
{
	char buf[16];
	itoa(num, &buf[0], 10);
	print(&buf[0]);
}

/**
 * @brief Turns the background LED on or off.
 * @param true = led on, false = led off.
 */
void LCD::setLED(bool on)
{
	if(on)
	{
		PORT_LCD |= (1<<PIN_LCD_LED);
	}
	else
	{
		PORT_LCD &=~ (1<<PIN_LCD_LED);
	}
}




/*
 * Private methods - direct hardware access.
 */

/**
 * @brief Writes the low-nibble of the char parameter n to the
 * data lines DB4-DB7 (which must be on contiguous portpins!)
 * @param
 */
void LCD::writeNibble(char n)
{
	// isolate the low nibble
	n &= 0x0F;

	// shift it, so that bit0 matches the DB4 pin position
	n = (n<<PIN_LCD_DB4);

	// leave the controls lines unchanged and clear the current data lines
	PORT_LCD &= ((1<<PIN_LCD_RW)|(1<<PIN_LCD_RS)|(1<<PIN_LCD_LED)|(1<<PIN_LCD_EN));

	// put the nibble to write on the data lines
	PORT_LCD |= n;

	// and send the command
	enable();
}

/**
 * @brief Toggles the enable line to activate the command
 */
void LCD::enable()
{
	/*
	 * Toggle the Enable-Pin
	 */
	PORT_LCD |= (1<<PIN_LCD_EN);
	for(int i = 0; i < 500; i++)
	{
		asm volatile ("nop");
	}
	PORT_LCD &=~(1<<PIN_LCD_EN);
}

/**
 * @brief Outputs the character to the current cursor position.
 * @param c character to output
 */
void LCD::putChar(char c)
{
	// Set Data Mode
	PORT_LCD |= (1<<PIN_LCD_RS);

	/*
	 * First write the high-, then the
	 * low-nibble
	 */

	char nibble = c & 0xF0;
	nibble = (nibble>>4);
	writeNibble(nibble);

	nibble = c & 0x0F;
	writeNibble(nibble);

	// Leave Data Mode
	PORT_LCD &=~(1<<PIN_LCD_RS);
}

/**
 * @brief Sends the command to the display
 * @param c command to send. See the private static const uint8_t
 * for command set.
 */
void LCD::putCmd(uint8_t c)
{
	char nibble = c & 0xF0;
	nibble = (nibble>>4);
	writeNibble(nibble);

	nibble = c & 0x0F;
	writeNibble(nibble);
}



