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
