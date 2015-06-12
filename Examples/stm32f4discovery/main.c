/*
 * This file is part of AUSBEE.
 *
 * Copyright (C) 2015 AUSBEE Developers <ausbee@googlegroups.com>
 *
 * AUSBEE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * AUSBEE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with AUSBEE.  If not, see <http://www.gnu.org/licenses/>.
 */

// STM32F4Discovery code example, using FreeRTOS
// Cesson Vincent <cesson.vincent@gmail.com>
// 08/02/2014
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <FreeRTOS.h>
#include <list.h>
#include <queue.h>
#include <task.h>
#include <semphr.h>
#include <platform.h>

// Private function prototypes
void vTaskBlink();
void vTaskManager();
void vTaskMEMS();

// Global variables
xSemaphoreHandle xTestSemaphore = NULL;
xTaskHandle xHandleBlinkTask, xHandleMEMSTask;

int main(void) {
	// Platform specific initializations
	platform_init_HSE_PLL();
	platform_init_PB();
	
	// Task creation. Be aware of stack size!
	xTaskCreate(vTaskManager, (const signed char *)"Task Manager", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate(vTaskBlink, (const signed char *)"Blink LED", configMINIMAL_STACK_SIZE, NULL, 1, &xHandleBlinkTask);
	xTaskCreate(vTaskMEMS, (const signed char *)"Accelerometer test", configMINIMAL_STACK_SIZE, NULL, 1, &xHandleMEMSTask);

	vTaskStartScheduler();

	while(1);

	return 0;
}

// Initialize interrupts for the Push Button
// and wait for interrupt event to toggle a LED
void vTaskManager( void ) 
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	// Connect Button EXTI Line to Button GPIO Pin
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

	// Configure Button EXTI line
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	// Enable and set Button EXTI Interrupt to the lowest priority
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	xTestSemaphore = xSemaphoreCreateMutex();
	xSemaphoreTake(xTestSemaphore, portMAX_DELAY);

	uint8_t current_task = 0;
	vTaskResume(xHandleMEMSTask);
	while(1) {
		// Wait for interrupt handler to give the semaphore
		if(xSemaphoreTake( xTestSemaphore, portMAX_DELAY ) == pdTRUE) {
			if(current_task == 0) {
				vTaskSuspend(xHandleMEMSTask);
				platform_init_LEDs();
				vTaskResume(xHandleBlinkTask);
				current_task = 1;
			}
			else if(current_task == 1) {
				vTaskSuspend(xHandleBlinkTask);
				platform_init_PWM_LEDs();
				vTaskResume(xHandleMEMSTask);
				current_task = 0;
			}
		}
		vTaskDelay(10);
	}
}

// Because a blinking LED is the coolest thing ever
void vTaskBlink() 
{
	// Auto-suspend. Let the Task Manager resume this task
	vTaskSuspend(NULL);

	platform_init_LEDs();

	while(1) {
		platform_toggle_led(PLATFORM_LED_GREEN);
		vTaskDelay(50); // Wait 50 ticks = 50 * 10ms
	}
}

// Accelerometer task
// Move your board, it's magic
void vTaskMEMS(void)
{
	uint8_t buf = 0;

	// Auto-suspend. Let the Task Manager resume this task
	vTaskSuspend(NULL);

	// Clear LEDs
	platform_reset_led(PLATFORM_LED_GREEN);
	platform_reset_led(PLATFORM_LED_ORANGE);
	platform_reset_led(PLATFORM_LED_RED);
	platform_reset_led(PLATFORM_LED_BLUE);

	// Initialize accelerometer and PWM to control LEDs
	platform_init_MEMS();
	platform_init_PWM_LEDs();

	// Must wait 30ms after MEMs initialization
	vTaskDelay(3);

	while(1) {
		vTaskDelay(1);

		/* Disable All TIM4 Capture Compare Channels */
		TIM_CCxCmd(TIM4, TIM_Channel_1, DISABLE);
		TIM_CCxCmd(TIM4, TIM_Channel_2, DISABLE);
		TIM_CCxCmd(TIM4, TIM_Channel_3, DISABLE);
		TIM_CCxCmd(TIM4, TIM_Channel_4, DISABLE);

		// Get MEMS value on X axis
		LIS302DL_Read(&buf, LIS302DL_OUT_X_ADDR, 1);
		if((int8_t)buf < 0) {	// X axis
			TIM_SetCompare1(TIM4, (100 * (-(int8_t)buf)));
			TIM_CCxCmd(TIM4, TIM_Channel_1, ENABLE);
		}
		if((int8_t)buf > 0) {	// X axis
			TIM_SetCompare3(TIM4, (100 * ((int8_t)buf)));
			TIM_CCxCmd(TIM4, TIM_Channel_3, ENABLE);
		}
		// Get MEMS value on Y axis
		LIS302DL_Read(&buf, LIS302DL_OUT_Y_ADDR, 1);
		if((int8_t)buf < 0) {	// Y axis
			TIM_SetCompare4(TIM4, (100 * (-(int8_t)buf)));
			TIM_CCxCmd(TIM4, TIM_Channel_4, ENABLE);
		}
		if((int8_t)buf > 0) {	// Y axis
			TIM_SetCompare2(TIM4, (100 * ((int8_t)buf)));
			TIM_CCxCmd(TIM4, TIM_Channel_2, ENABLE);
		}
	}
}

