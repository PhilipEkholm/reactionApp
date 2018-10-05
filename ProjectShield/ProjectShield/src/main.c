#include <inttypes.h>
#include <stdio_serial.h>
#include <asf.h>
#include "drivers/consoleFunctions.h"    /* functions to print on the terminal via USB */
#include "drivers/delayFunctions.h"	/* Just using the delay to make sure there is time to read the printout to the LCD of the tested functions */
#include "drivers/LCDFunctions.h"
#include "drivers/lcdApplication.h"
#include "drivers/adcFunctions.h"

#include "pin_mapper.h"
#include "task_green.h"
#include "task_red.h"
#include "task_game_control.h"

#define LEFT_LED   53
#define MIDDLE_LED 51
#define RIGHT_LED  49
#define BLUE_BTN   47
#define RED_BTN    45
#define VCC        43

xSemaphoreHandle player1, player2;

void enable_pins(void) {
	ioport_enable_pin(pin_mapper(LEFT_LED));
	ioport_enable_pin(pin_mapper(MIDDLE_LED));
	ioport_enable_pin(pin_mapper(RIGHT_LED));
	ioport_enable_pin(pin_mapper(BLUE_BTN));
	ioport_enable_pin(pin_mapper(RED_BTN));
	ioport_enable_pin(pin_mapper(VCC));
	
	ioport_enable_pin(pin_mapper(22));
	ioport_enable_pin(pin_mapper(23));
	
	ioport_set_pin_dir(pin_mapper(LEFT_LED), IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(pin_mapper(MIDDLE_LED), IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(pin_mapper(RIGHT_LED), IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(pin_mapper(VCC), IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(pin_mapper(22), IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(pin_mapper(23), IOPORT_DIR_OUTPUT);
	
	ioport_set_pin_level(pin_mapper(VCC), 1);
	
	ioport_set_pin_dir(pin_mapper(BLUE_BTN), IOPORT_DIR_INPUT);
	ioport_set_pin_dir(pin_mapper(RED_BTN), IOPORT_DIR_INPUT);
	
	/* Unfortunately PIO-system doesn't follow ioport convention so we must enter SAM-pins */
	PIOC->PIO_PUDR  |= PIO_PC18 | PIO_PC16; /* Set pull-up for both buttons */
	PIOC->PIO_IFER  |= PIO_PC18 | PIO_PC16; /* Enable switch debounce filter for both buttons */
	PIOC->PIO_DIFSR |= PIO_PC18 | PIO_PC16;
}

void poll_buttons(void) {
	uint8_t button1_pressed = 0,
			button2_pressed = 0;

	button1_pressed = ~ioport_get_pin_level(pin_mapper(BLUE_BTN)) & 1;
	button2_pressed = ~ioport_get_pin_level(pin_mapper(RED_BTN)) & 1;
	
	if (button1_pressed && button2_pressed) {
		ioport_set_pin_level(pin_mapper(RIGHT_LED), 1);
		ioport_set_pin_level(pin_mapper(MIDDLE_LED), 1);
		ioport_set_pin_level(pin_mapper(LEFT_LED), 1);
		printf("Both buttons pressed\n");
	}
	else if (button1_pressed) {
		ioport_set_pin_level(pin_mapper(RIGHT_LED), 0);
		ioport_set_pin_level(pin_mapper(MIDDLE_LED), 0);
		ioport_set_pin_level(pin_mapper(LEFT_LED), 1);
		printf("Button 1 pressed\n");
	}
	else if (button2_pressed) {
		ioport_set_pin_level(pin_mapper(RIGHT_LED), 1);
		ioport_set_pin_level(pin_mapper(MIDDLE_LED), 0);
		ioport_set_pin_level(pin_mapper(LEFT_LED), 0);
		printf("Button 2 pressed\n");
	}
	else {
		ioport_set_pin_level(pin_mapper(RIGHT_LED), 0);
		ioport_set_pin_level(pin_mapper(MIDDLE_LED), 0);
		ioport_set_pin_level(pin_mapper(LEFT_LED), 0);
		printf("No button pressed\n");
	}
}

int main(void)
{
	sysclk_init();
	board_init();
	delayInit();
	analogInit(0);
	lcdInit();
	configureConsole();
	ioport_init();
	enable_pins();
	
	pmc_enable_periph_clk(ID_TRNG);
	trng_enable(TRNG);
	
	vSemaphoreCreateBinary(player1);
	vSemaphoreCreateBinary(player2);
	
	lcdClearDisplay();
	
	xTaskCreate(task_game_control, (const signed char * const)"Game Control", TASK_GAME_CONTROL_STACK_SIZE, NULL, TASK_GAME_CONTROL_PRIORITY, NULL);
	xTaskCreate(task_player_green, (const signed char * const)"Player Green", TASK_PLAYER_GREEN_STACK_SIZE, NULL, TASK_PLAYER_GREEN_PRIORITY, NULL);
	xTaskCreate(task_player_red, (const signed char * const)"Player Red", TASK_PLAYER_RED_STACK_SIZE, NULL, TASK_PLAYER_RED_PRIORITY, NULL);
	
	vTaskSuspend(task_player_red);
	vTaskSuspend(task_player_green);

	vTaskStartScheduler();

	return 0;
}


