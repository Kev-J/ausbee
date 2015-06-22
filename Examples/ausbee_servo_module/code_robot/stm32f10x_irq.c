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

/**
  * @file    stm32f10x_irq.c
  * @author  vcesson
  * @version V1.0
  * @date    11-January-2014
  * @brief   This file contains interrupt handlers
  */

#include "FreeRTOS.h"
#include "semphr.h"
#include "platform.h"

// Global variables
// Extern variables
extern xSemaphoreHandle CANReceiveSemaphore;
extern CanRxMsg CAN_RxStruct;

void USB_LP_CAN1_RX0_IRQHandler(void) {
	// Check the cause of the interrupt
	if(CAN_GetITStatus(CAN1, CAN_IT_FMP0) == SET) { // Pending message in Fifo 0
		CAN_Receive(CAN1, CAN_FIFO0, &CAN_RxStruct);
		xSemaphoreGive(CANReceiveSemaphore);
	}
	else if(CAN_GetITStatus(CAN1, CAN_IT_FF0) == SET) { // Fifo 0 is full
	}
	else if(CAN_GetITStatus(CAN1, CAN_IT_FOV0) == SET) { // Fifo 0 overrun
	}
}
