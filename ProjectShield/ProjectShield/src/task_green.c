/*
 * task_green.c
 *
 * Created: 2018-10-05 15:49:02
 *  Author: Philip Ekholm
 */ 

#include "pin_mapper.h"

void task_player_green(void *pvParameters) {
	while(1){
		ioport_set_pin_level(pin_mapper(22), 1);
		ioport_set_pin_level(pin_mapper(22), 0);
	}
}
