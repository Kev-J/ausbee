// stm32f10x_irq.c
// vcesson, 2013/12/16
// This file contains the interrupts handlers

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "stm32f4xx_conf.h"
#include "FreeRTOS.h"
#include "list.h"
#include "queue.h"
#include "task.h"
#include "semphr.h"
#include "platform.h"
#include "misc.h"

// Global variables
// Extern variables
extern xSemaphoreHandle CANReceiveSemaphore;
extern CanRxMsg CAN_RxStruct;

void CAN1_RX0_IRQHandler(void) {
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
