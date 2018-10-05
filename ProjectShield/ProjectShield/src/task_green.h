/*
 * task_green.h
 *
 * Created: 2018-10-05 15:49:30
 *  Author: Philip Ekholm
 */ 

void task_player_green(void *pvParameters);

#define TASK_PLAYER_GREEN_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_PLAYER_GREEN_PRIORITY (1)
