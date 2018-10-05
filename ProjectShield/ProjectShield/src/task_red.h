/*
 * task_red.h
 *
 * Created: 2018-10-05 15:49:12
 *  Author: Philip Ekholm
 */ 

#define TASK_PLAYER_RED_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_PLAYER_RED_PRIORITY (1)

void task_player_red(void *pvParameters);
