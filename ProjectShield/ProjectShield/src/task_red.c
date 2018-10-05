/*
 * task_red.c
 *
 * Created: 2018-10-05 15:48:42
 *  Author: Philip Ekholm
 */ 

#include "pin_mapper.h"

void task_player_red(void *pvParameters)
{
	while(1)
	{
		ioport_set_pin_level(pin_mapper(23), 1);
		ioport_set_pin_level(pin_mapper(23), 0);
	}
}