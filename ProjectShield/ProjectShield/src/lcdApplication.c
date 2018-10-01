/*
 * lcdApplication.c
 *
 * Created: 2015-09-10 08:44:50
 *  Author: Aron Polner, Philip Ekholm
 */ 

#include "lcdApplication.h"
#include "buttons.h"	/* to get the buttontype definiton */
#include "LCDFunctions.h"
#include "DelayFunctions.h"

err_code lcdWrite4DigitNumber(int number)
{
	char nbr_str[5];
	sprintf(nbr_str, "%d", number);
	lcdWriteAsciiString(nbr_str);
	
	return ERROR_OK;
}

err_code lcdWriteAsciiString(const char *string)
/* writes an ascii string up to 40 characters on the LCD display */
{
	while(*string != '\0'){
		lcdWrite(*string, CHARACTER);
		string++;
		delayMicroseconds(100);
	};
	
	return ERROR_OK;
}

err_code lcdWriteButtonValue(buttonType inputButton)
/* Writes the text corresponding to one of the buttons on the LCD dispaly using lcdWriteAsciiString() 
 * Output should be one of SELECT, LEFT, UP, DOWN, RIGHT on the LCD display
 * if no buttons is pushed you can chose on displaying nothing or NONE  */
{
	switch(inputButton) {
		case btnRIGHT:
			lcdWriteAsciiString("RIGHT");
		break;
		case btnUP:
			lcdWriteAsciiString("UP");
		break;
		case btnDOWN:
			lcdWriteAsciiString("DOWN");
		break;
		case btnLEFT:
			lcdWriteAsciiString("LEFT");
		break;
		case btnSELECT:
			lcdWriteAsciiString("SELECT");
		break;
		case btnNONE:
			lcdWriteAsciiString("NONE");
		break;
	}
	
	return ERROR_OK;
}