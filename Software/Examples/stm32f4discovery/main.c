// STM32F4Discovery code example, using FreeRTOS
// Cesson Vincent <cesson.vincent@gmail.com>
// 06/01/2014
//
// TODO: 
// Initialize Push Button
// Create interrupt handler for Push Button

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "FreeRTOS.h"
#include "list.h"
#include "queue.h"
#include "task.h"
#include "semphr.h"
#include <platform.h>

// Private function prototypes
void blink1();
void blink2();
void blink3();
void blink3();
void vTaskPB();

// Global variables
static xSemaphoreHandle xTestSemaphore = NULL;

int main(void) {
	platform_init_HSE_PLL();
	platform_init_LED();

	xTestSemaphore = xSemaphoreCreateMutex();

	xTaskCreate(blink1, (const signed char *)"LED1", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate(blink2, (const signed char *)"LED2", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate(blink3, (const signed char *)"LED3", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	//xTaskCreate(vTaskPB, (const signed char *)"PB_test", configMINIMAL_STACK_SIZE, NULL, 1, NULL );

	vTaskStartScheduler();

	for(;;) {
	}

	return 0;
}

void blink1() 
{
	for(;;) {
		platform_toggle_led(PLATFORM_LED_GREEN);
		vTaskDelay(50);
	}
}

void blink2() 
{
	for(;;) {
		platform_toggle_led(PLATFORM_LED_ORANGE);
		vTaskDelay(100);
	}
}


void blink3() 
{
	for(;;) {
		platform_toggle_led(PLATFORM_LED_RED);
		vTaskDelay(200);
	}
}

void vTaskPB( void ) 
{
	for( ;; )
	{
		if(xSemaphoreTake( xTestSemaphore, portMAX_DELAY ) == pdTRUE)
			GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
	}
}
