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

