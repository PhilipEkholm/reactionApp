#include <inttypes.h>
#include <stdio_serial.h>
#include <asf.h>
#include "../src/consoleFunctions.h"    /* functions to print on the terminal via USB */
#include "../unity/unity.h"             /* Contains declarations of all functions that Unity provides */
#include "../test/test_delayFunctions.h"	/* Contains declarations of the tests for the delay used in the init function for the LCD */
#include "../test/test_lcdFunctions.h"		/* Contains declarations of the tests for the LCD */
#include "../test/test_adcFunctions.h"
#include "../test/test_buttons.h"			/* Contains declarations of the tests for the buttons */
#include "../test/test_lcdApplication.h"	/* Contains declarations of the tests for the LCD */

#include "../src/delayFunctions.h"	/* Just using the delay to make sure there is time to read the printout to the LCD of the tested functions */
#include "LCDFunctions.h"
#include "lcdApplication.h"
#include "adcFunctions.h"


void setUp(void);
void tearDown(void);
void resetTest(void);

int main(void)
{
	sysclk_init();	/* Insert system clock initialization code here (sysclk_init()). */
	board_init();

	configureConsole();	/* Initialize the console UART used from within Atmel Studio*/
	
	/* From here on the program uses the Unity testing framework */
	UnityBegin("../test/test_delayFunctions.c");	/* Run the tests for the delay from the test-file */
	RUN_TEST(test_delayTimerIsInitialisedProperly, 12);
	RUN_TEST(test_delayCountsProperly, 14);
	UnityEnd();
	
	UnityBegin("../test/test_lcdFunctions.c");	/* Run the tests for the LCD from the test-file */
	RUN_TEST(test_initialisatinOfTheLCD, 20);
	RUN_TEST(test_writingCharactersToTheLCD, 22);
	//delayMicroseconds(1000000);	/* These delays are necessary if you want to see the text on the display before it disappears */
	RUN_TEST(test_clearingTheLCDDisplay, 23);
	UnityEnd();
	
	UnityBegin("../test/test_adcFunctions.c");	/* Run the tests for the ADC from the test-file */
	RUN_TEST(test_ADConverterInitialisesProperly, 30);
	RUN_TEST(test_ADConverterReadsValueWithNoButtonPressed, 35);
	UnityEnd();

	UnityBegin("../test/test_buttons.c");	/* Run the tests for the buttons from the test-file */
	RUN_TEST(test_noButtonIsPressed, 40);
	UnityEnd();
		
	UnityBegin("../test/test_lcdApplication.c");	/* Run the tests for displaying a button on the LCD from the test-file */
	RUN_TEST(test_writing4DigitNumberOnTheLCDDisplay, 50);
	//delayMicroseconds(1000000);	/* These delays are necessary if you want to see the text on the display before it disappears */
	RUN_TEST(test_writingAsciiStringOnTheLCDDisplay, 52);
	//delayMicroseconds(1000000);	/* These delays are necessary if you want to see the text on the display before it disappears */
	RUN_TEST(test_writingButtonOnTheLCDDisplay, 54);
	UnityEnd();
	
	/* Infinite loop to display the current button pressed */
	while(1)
	{
		lcdClearDisplay();
		lcdWriteButtonValue(readLCDbutton());
		delayMicroseconds(50000);
	}
	
	return 0;
}

void setUp(void)
{
	/* Do nothing */
}

void tearDown(void)
{
	/* Do nothing */
}

void resetTest(void)
{
	tearDown();
	setUp();
}

