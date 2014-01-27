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

// Private function prototypes
void blink1();
void cantx();
void canrx();
void testscan();
// Global variables
//static xSemaphoreHandle xTestSemaphore = NULL;

xSemaphoreHandle CANReceiveSemaphore;
CanRxMsg CAN_RxStruct;

int main(void) {
	// Call the platform initialization function
	platform_init_HSE_PLL();
	platform_init_USART(USART_DEBUG, 115200);
	platform_init_LED();
	platform_CAN_init(CAN1);

	//xTaskCreate(testscan, (const signed char *)"SCANF", 400, NULL, 1, NULL );
	xTaskCreate(blink1, (const signed char *)"LED1", 140, NULL, 1, NULL );
	xTaskCreate(cantx, (const signed char *)"CAN TX", 140, NULL, 1, NULL );
	xTaskCreate(canrx,  (const signed char *)"CAN RX", 140, NULL, 1, NULL );
	vTaskStartScheduler();

	for(;;) {

	}

	return 0;
}

void testscan (void){
	char value;
	while (1){
		value=getchar();
		printf("value= %c\r\n", value);
		vTaskDelay(10);
		platform_toggle_led(PLATFORM_LED4);
	}
}	

void blink1() {
	for(;;) {
		platform_toggle_led(PLATFORM_LED0);
		//printf("super\r\n");
		vTaskDelay(20);
	}
}

void canrx( void )
{
	NVIC_InitTypeDef NVIC_InitStructure;
	CAN_ITConfig(CAN1,CAN_IT_FMP0, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel=CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=NVIC_PriorityGroup_0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=NVIC_PriorityGroup_0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	CANReceiveSemaphore = xSemaphoreCreateMutex();
	if(CANReceiveSemaphore == NULL) {
		while(1) {
			platform_set_led(PLATFORM_LED6);	
			vTaskDelay(5);
			platform_reset_led(PLATFORM_LED6);
			vTaskDelay(5);
		}
	}

	while(1) {
		if(xSemaphoreTake(CANReceiveSemaphore, portMAX_DELAY) == pdTRUE) { // A message has been received and stored in CAN_RxStruct
				printf("value_angle: %d\r\n", CAN_RxStruct.Data[0]);
				platform_set_led(PLATFORM_LED1);
		}
	}
}

void cantx( void )
{
	platform_set_led(PLATFORM_LED1);
	CAN_InitTypeDef CAN_InitTypeDef_1;
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
	CanTxMsg CAN_TxStruct;
	uint8_t mailbox_number = 0;
	uint8_t error=0;
	char num_servo;
	char pos_servo; 

	CAN_StructInit(&CAN_InitTypeDef_1);
	CAN_InitTypeDef_1.CAN_Prescaler = 336;
	CAN_InitTypeDef_1.CAN_Mode = CAN_Mode_Normal;
	CAN_InitTypeDef_1.CAN_AWUM = ENABLE;
	CAN_InitTypeDef_1.CAN_TXFP = ENABLE;
	if(CAN_Init(CAN1, &CAN_InitTypeDef_1) == CAN_InitStatus_Failed) {
		platform_set_led(PLATFORM_LED2);
		while(1);
	}

	// CAN filter init 

	CAN_FilterInitStructure.CAN_FilterNumber=0;
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0001;
	CAN_FilterInitStructure.CAN_FilterIdLow=0x0001;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0001;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0001;  
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=0;
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	while(1)
	{
		vTaskDelay(100);
		platform_reset_led(PLATFORM_LED1);
		platform_reset_led(PLATFORM_LED2);
		platform_reset_led(PLATFORM_LED3);
		platform_reset_led(PLATFORM_LED4);
		platform_reset_led(PLATFORM_LED5);
		platform_reset_led(PLATFORM_LED6);
		platform_reset_led(PLATFORM_LED7);
		
		printf("num_servo?\r\n");	
		num_servo=getchar();
		printf("num_servo: %c\r\n", num_servo);
		printf("pos_servo?\r\n");	
		pos_servo=getchar();
		printf("pos_servo: %c\r\n", pos_servo);

		switch (num_servo)
		{
			case '0':
				CAN_TxStruct.StdId = 0x80;
				break;
			case '1':
				CAN_TxStruct.StdId = 0x81;
				break;
			case '2':
				CAN_TxStruct.StdId = 0x82;
				break;
			case '3':
				CAN_TxStruct.StdId = 0x83;
				break;
			case '4':
				CAN_TxStruct.StdId = 0x84;
				break;
			case '5':
				CAN_TxStruct.StdId = 0x85;
				break;
			case '6':
				CAN_TxStruct.StdId = 0x86;
				break;
			case '7':
				CAN_TxStruct.StdId = 0x87;
				break;
		}

		switch (pos_servo)
		{
			case '0':
				CAN_TxStruct.Data[0] = 5;
				break;
			case '1':
				CAN_TxStruct.Data[0] = 10;
				break;
			case '2':
				CAN_TxStruct.Data[0] = 20;
				break;
			case '3':
				CAN_TxStruct.Data[0] = 30;
				break;
			case '4':
				CAN_TxStruct.Data[0] = 40;
				break;
			case '5':
				CAN_TxStruct.Data[0] = 50;
				break;
			case '6':
				CAN_TxStruct.Data[0] = 60;
				break;
			case '7':
				CAN_TxStruct.Data[0] = 70;
				break;
			case '8':
				CAN_TxStruct.Data[0] = 80;
				break;
			case '9':
				CAN_TxStruct.Data[0] = 90;
				break;
		}

		CAN_TxStruct.ExtId = 0;
		CAN_TxStruct.IDE = CAN_Id_Standard;
		CAN_TxStruct.RTR = CAN_RTR_Data;
		CAN_TxStruct.DLC = 1;

		mailbox_number = CAN_Transmit(CAN1, &CAN_TxStruct);
		if(mailbox_number == CAN_TxStatus_NoMailBox)
			platform_set_led(PLATFORM_LED3);
		uint8_t transmit_status = CAN_TransmitStatus(CAN1, mailbox_number); 
		while(transmit_status!=CAN_TxStatus_Ok){
			transmit_status = CAN_TransmitStatus(CAN1, mailbox_number);
			if(transmit_status == CAN_TxStatus_Ok)
			{
				platform_set_led(PLATFORM_LED4);
				platform_reset_led(PLATFORM_LED7);
			}
			else if( transmit_status == CAN_TxStatus_Pending)
			{
				platform_set_led(PLATFORM_LED7);
			}
			else
				platform_set_led(PLATFORM_LED6);
		}

		vTaskDelay(100);

		platform_reset_led(PLATFORM_LED1);
		platform_reset_led(PLATFORM_LED2);
		platform_reset_led(PLATFORM_LED3);
		platform_reset_led(PLATFORM_LED4);
		platform_reset_led(PLATFORM_LED5);
		platform_reset_led(PLATFORM_LED6);
		platform_reset_led(PLATFORM_LED7);
		
		CAN_TxStruct.ExtId = 0;
		CAN_TxStruct.IDE = CAN_Id_Standard;
		CAN_TxStruct.RTR = CAN_RTR_Remote;
		CAN_TxStruct.DLC = 0;

		mailbox_number = CAN_Transmit(CAN1, &CAN_TxStruct);
		if(mailbox_number == CAN_TxStatus_NoMailBox)
			platform_set_led(PLATFORM_LED3);
		transmit_status = CAN_TransmitStatus(CAN1, mailbox_number); 
		while(transmit_status!=CAN_TxStatus_Ok){
			transmit_status = CAN_TransmitStatus(CAN1, mailbox_number);
			if(transmit_status == CAN_TxStatus_Ok)
			{
				platform_set_led(PLATFORM_LED4);
				platform_reset_led(PLATFORM_LED7);
			}
			else if( transmit_status == CAN_TxStatus_Pending)
			{
				platform_set_led(PLATFORM_LED7);
			}
			else
				platform_set_led(PLATFORM_LED6);
		}
	}
	while(1) {
		vTaskDelay(10);
	}
}
