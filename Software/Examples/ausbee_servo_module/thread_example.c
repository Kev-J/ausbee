/**
  ******************************************************************************
  * @file    thread_example.c
  * @author  Vincent Cesson, vcesson@enseirb-matmeca.fr
  * @version V0.1
  * @date    11-December-2013
  * @brief   This file provides example code for the Servo Module Board with 
  *			 FreeRTOS: Thread creation, semaphore
  ******************************************************************************
  */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "stm32f10x_conf.h"
#include "FreeRTOS.h"
#include "list.h"
#include "queue.h"
#include "task.h"
#include "semphr.h"
#include "platform.h"
#include "misc.h"

// Private function prototypes
void blink1();
void blink_control();

// Global variables
xSemaphoreHandle BlinkSem = NULL;

int main(void) {
	// Call the platform initialization function
	platform_SetupHardware();

	xTaskCreate(blink1, (const signed char *)"LED1", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate(blink_control, (const signed char *)"Control LED1", configMINIMAL_STACK_SIZE, NULL, 1, NULL );

	// Start scheduler: initialize Systick and enable interrupts
	vTaskStartScheduler();

	for(;;) {
	}

	// Never reach
	return 0;
}

void blink1() {
	for(;;) {
		GPIO_SetBits(GPIOB, Led1);
		vTaskDelay(10);
		GPIO_ResetBits(GPIOB, Led1);
		vTaskDelay(10);
	}
}

void blink_control(void) {
}	
