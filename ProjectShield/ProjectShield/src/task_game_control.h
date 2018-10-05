/*
 * task_game_control.h
 *
 * Created: 2018-10-05 16:39:12
 *  Author: Philip Ekholm
 */ 

void task_game_control(void *pvParameters);

#define TASK_GAME_CONTROL_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_GAME_CONTROL_PRIORITY (2)
