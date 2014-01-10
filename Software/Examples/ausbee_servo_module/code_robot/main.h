/**
  * @file    main.h
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
