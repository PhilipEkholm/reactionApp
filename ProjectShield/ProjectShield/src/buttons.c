/*
 * buttons.c
 *
 * Created: 2015-06-12 16:28:53
 * Author: Aron Polner, Philip Ekholm
 */ 

#include "buttons.h"
#include "adcFunctions.h"	/* Must use the value from the ADC to figure out which button */

#define ANALOG_A0         0
#define BTN_THRESHOLD     80

buttonType readLCDbutton(void)
{
	uint32_t button_code = analogRead(ANALOG_A0);

	if (button_code > 3000 && button_code < 3150)
		return btnSELECT;
	else if (button_code > 2300 && button_code < 2400)
		return btnLEFT;
	else if (button_code > 700 && button_code < 900)
		return btnUP;
	else if (button_code > 1600 && button_code < 1700)
		return btnDOWN;
	else if (button_code >= 0 && button_code < 100)
		return btnRIGHT;
	else
		return btnNONE;	/* No button pressed */
}