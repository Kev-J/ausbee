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
  * @file    main.c
  * @author  vcesson
  * @version V0.1
  * @date    11-January-2014
  * @brief   Servo module code. 
  */

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stm32f10x_conf.h>
#include <FreeRTOS.h>
#include <list.h>
#include <queue.h>
#include <task.h>
#include <semphr.h>
#include <platform.h>
#include <misc.h>
#include <AUSBEE/servo.h>

#define CAN_ID_SERVO1	0x80
#define CAN_ID_SERVO2	0x81
#define CAN_ID_SERVO3	0x82
#define CAN_ID_SERVO4	0x83
#define CAN_ID_SERVO5	0x84
#define CAN_ID_SERVO6	0x85
#define CAN_ID_SERVO7	0x86
#define CAN_ID_SERVO8	0x87

// Private function prototypes
void blink_thread();	
void can_receive_thread();
void can_transmit_thread();
int8_t can_init();	 
void servo_init();

// Global variables
xSemaphoreHandle CANReceiveSemaphore = NULL;
xSemaphoreHandle CANTransmitSemaphore = NULL;
CanRxMsg CAN_RxStruct;
CanTxMsg CAN_TxStruct;
ausbeeServo serv1;
ausbeeServo serv2;
ausbeeServo serv3;
ausbeeServo serv4;
ausbeeServo serv5;
ausbeeServo serv6;
ausbeeServo serv7;
ausbeeServo serv8;

int main(void) {
	// Call the platform initialization function
	platform_SetupHardware();
	// Call private initialization functions
	if(can_init() == -1) { // Check CAN init failure
		GPIO_SetBits(GPIOB, Led2);
		while(1);
	}
	servo_init();

	// Create tasks
	xTaskCreate(blink_thread, (const signed char *)"LED1", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate(can_receive_thread, (const signed char *)"CAN Receive Thread", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate(can_transmit_thread, (const signed char *)"CAN Transmit Thread", configMINIMAL_STACK_SIZE, NULL, 1, NULL );

	// Init the timer (Systick), enable interrupts and start the tasks
	vTaskStartScheduler();

	for(;;) {
	}

	return 0;
}

// Because a blinking LED is the coolest thing ever
void blink_thread() { 	
	for(;;) {
		platform_printString("Value : ", 8);
		GPIO_SetBits(GPIOB, Led1);
		vTaskDelay(100);
		platform_printHexa(0x42);
		GPIO_ResetBits(GPIOB, Led1);
		vTaskDelay(100);
	}
}

// This function take action depending on the data received. The semaphore is 
// released by the interrupt handler
void can_receive_thread(void) {
	while(1) {
		// Wait until the interrupt handler releases the semaphore (meaning a data has been received)
		if(xSemaphoreTake(CANReceiveSemaphore, portMAX_DELAY) == pdTRUE) { 
			GPIO_SetBits(GPIOB, Led3);
			// Check message type: RTR or Data
			if(CAN_RxStruct.RTR == CAN_RTR_Remote) {
				// Need to answer, unlock transmit thread to handle the response
				xSemaphoreGive(CANTransmitSemaphore);
			}
			else if(CAN_RxStruct.RTR == CAN_RTR_Data) {
				if		(CAN_RxStruct.StdId == CAN_ID_SERVO1) 
					ausbeeSetAngleServo(&serv1, CAN_RxStruct.Data[0]); // Set servo 1 angle
				else if	(CAN_RxStruct.StdId == CAN_ID_SERVO2) 
					ausbeeSetAngleServo(&serv2, CAN_RxStruct.Data[0]); // Set servo 2 angle
				else if	(CAN_RxStruct.StdId == CAN_ID_SERVO3) 
					ausbeeSetAngleServo(&serv3, CAN_RxStruct.Data[0]); // Set servo 3 angle
				else if	(CAN_RxStruct.StdId == CAN_ID_SERVO4) 
					ausbeeSetAngleServo(&serv4, CAN_RxStruct.Data[0]); // Set servo 4 angle
				else if	(CAN_RxStruct.StdId == CAN_ID_SERVO5) 
					ausbeeSetAngleServo(&serv5, CAN_RxStruct.Data[0]); // Set servo 5 angle
				else if	(CAN_RxStruct.StdId == CAN_ID_SERVO6) 
					ausbeeSetAngleServo(&serv6, CAN_RxStruct.Data[0]); // Set servo 6 angle
				else if	(CAN_RxStruct.StdId == CAN_ID_SERVO7) 
					ausbeeSetAngleServo(&serv7, CAN_RxStruct.Data[0]); // Set servo 7 angle
				else if	(CAN_RxStruct.StdId == CAN_ID_SERVO8) 
					ausbeeSetAngleServo(&serv8, CAN_RxStruct.Data[0]); // Set servo 8 angle
			}
			GPIO_ResetBits(GPIOB, Led3);
		}
	}
}

// Answer a RTR CAN message
void can_transmit_thread(void) {
	uint8_t mailbox_number = 0;
	CAN_TxStruct.StdId = 1;
	CAN_TxStruct.ExtId = 0;
	CAN_TxStruct.IDE = CAN_Id_Standard;
	CAN_TxStruct.RTR = CAN_RTR_Data;
	CAN_TxStruct.DLC = 2;

	while(1) {
		// Wait for a RTR message. This semaphore is released by can_receive_thread()
		if(xSemaphoreTake(CANTransmitSemaphore, portMAX_DELAY) == pdTRUE) { 
			if		(CAN_RxStruct.StdId == CAN_ID_SERVO1) 
				CAN_TxStruct.Data[0] = ausbeeGetAngleServo(&serv1); // Get servo 1 angle
			else if	(CAN_RxStruct.StdId == CAN_ID_SERVO2) 
				CAN_TxStruct.Data[0] = ausbeeGetAngleServo(&serv2); // Get servo 2 angle
			else if	(CAN_RxStruct.StdId == CAN_ID_SERVO3) 
				CAN_TxStruct.Data[0] = ausbeeGetAngleServo(&serv3); // Get servo 3 angle
			else if	(CAN_RxStruct.StdId == CAN_ID_SERVO4) 
				CAN_TxStruct.Data[0] = ausbeeGetAngleServo(&serv4); // Get servo 4 angle
			else if	(CAN_RxStruct.StdId == CAN_ID_SERVO5) 
				CAN_TxStruct.Data[0] = ausbeeGetAngleServo(&serv5); // Get servo 5 angle
			else if	(CAN_RxStruct.StdId == CAN_ID_SERVO6) 
				CAN_TxStruct.Data[0] = ausbeeGetAngleServo(&serv6); // Get servo 6 angle
			else if	(CAN_RxStruct.StdId == CAN_ID_SERVO7) 
				CAN_TxStruct.Data[0] = ausbeeGetAngleServo(&serv7); // Get servo 7 angle
			else if	(CAN_RxStruct.StdId == CAN_ID_SERVO8) 
				CAN_TxStruct.Data[0] = ausbeeGetAngleServo(&serv8); // Get servo 8 angle

			// Transmit the data
			mailbox_number = CAN_Transmit(CAN1, &CAN_TxStruct);
			if(mailbox_number == CAN_TxStatus_NoMailBox) {
				GPIO_SetBits(GPIOB, Led4);
			}	
			else {
				GPIO_ResetBits(GPIOB, Led4);
			}
		}
	}
}

// Initialize CAN:
//  Filters
//  Receive interrupt
//  Semaphores
int8_t can_init( void )
{
	// Init structures
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	// Configure filter. Allow IDs from 0x80 to 0x87
	CAN_FilterInitStructure.CAN_FilterNumber=0;
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit;
	CAN_FilterInitStructure.CAN_FilterIdLow=0x80 << 5;		// FR1 register (LSBs)	
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0;			// FR2 register (LSBs)
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0xFF00;		// FR1 register (MSBs)
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0xFFFF;	// FR2 register (MSBs)
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);

	// Configure interrupts
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE); // Enable CAN interruption on Fifo 0 Not Empty
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_PriorityGroup_0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_PriorityGroup_0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);			// Initialize NVIC

	// Init semaphores
	CANReceiveSemaphore = xSemaphoreCreateMutex();
	if(CANReceiveSemaphore == NULL) 
		return -1;
	CANTransmitSemaphore = xSemaphoreCreateMutex();
	if(CANTransmitSemaphore == NULL)
		return -1;

	return 0;
}

// Initialize Servo motors
void servo_init(void) {
	ausbeeInitStructServo(&serv1);                // Default parameters initialization
	serv1.TIMx = SERVO1_TIM;
	serv1.CHANx = SERVO1_CHAN;
	ausbeeInitServo(&serv1);                      // PWM initialization

	ausbeeInitStructServo(&serv2);                // Default parameters initialization
	serv2.TIMx = SERVO2_TIM;
	serv2.CHANx = SERVO2_CHAN;
	ausbeeInitServo(&serv2);                      // PWM initialization

	ausbeeInitStructServo(&serv3);                // Default parameters initialization
	serv3.TIMx = SERVO3_TIM;
	serv3.CHANx = SERVO3_CHAN;
	ausbeeInitServo(&serv3);                      // PWM initialization

	ausbeeInitStructServo(&serv4);                // Default parameters initialization
	serv4.TIMx = SERVO4_TIM;
	serv4.CHANx = SERVO4_CHAN;
	ausbeeInitServo(&serv4);                      // PWM initialization

	ausbeeInitStructServo(&serv5);                // Default parameters initialization
	serv5.TIMx = SERVO5_TIM;
	serv5.CHANx = SERVO5_CHAN;
	ausbeeInitServo(&serv5);                      // PWM initialization

	ausbeeInitStructServo(&serv6);                // Default parameters initialization
	serv6.TIMx = SERVO6_TIM;
	serv6.CHANx = SERVO6_CHAN;
	ausbeeInitServo(&serv6);                      // PWM initialization

	ausbeeInitStructServo(&serv7);                // Default parameters initialization
	serv7.TIMx = SERVO7_TIM;
	serv7.CHANx = SERVO7_CHAN;
	ausbeeInitServo(&serv7);                      // PWM initialization

	ausbeeInitStructServo(&serv8);                // Default parameters initialization
	serv8.TIMx = SERVO8_TIM;
	serv8.CHANx = SERVO8_CHAN;
	ausbeeInitServo(&serv8);                      // PWM initialization
}
