// @file	stm32f4xx_irq.c
// @author	vcesson <cesson.vincent@gmail.com>
// @date	08-February-2014
// @brief	This file contains interrupt handlers

#include <FreeRTOS.h>
#include <semphr.h>
#include <platform.h>

// Global variables
extern xSemaphoreHandle xTestSemaphore;

// Push Button interrupt handler
// Clear interrupt flag and give semaphore to unlock vTaskPB
void EXTI0_IRQHandler( void )
{
	xSemaphoreGive(xTestSemaphore);
	EXTI_ClearITPendingBit(EXTI_Line0);
}

