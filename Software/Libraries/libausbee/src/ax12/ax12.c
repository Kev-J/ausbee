/**
 ********************************************************************
 * @file    ax12.c
 * @author  Vincent Cesson <cesson.vincent@gmail.com>
 * @version V1.0
 * @date    20-Feb-2014
 * @brief   This file provides functions for AX12 servomotors
 ********************************************************************
 * @attention
 *
 * This file is part of LIBAUSBEE.
 * 
 * LIBAUSBEE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * LIBAUSBEE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with LIBAUSBEE.  If not, see <http://www.gnu.org/licenses/>.
 *
 * <h2><centor>&copy;  Copyright 2013-2014 (C) EIRBOT </center></h2>
 ********************************************************************
 */

/* Includes */
#include <AUSBEE/ax12.h>

/**
 * @addtogroup Libausbee
 * @{
 */

/**
 * @defgroup AX12
 * @brief AX12 driver modules
 * @{
 */

/**
 * @defgroup AX12_Exported_Functions
 * @{
 */

/**
 * @brief  Initialize USART
 * @param  baudrate: USART baudrate
 * @retval None
 */
void ausbeeInitAX12(uint32_t baudrate)
{
	GPIO_InitTypeDef init_GPIO_USART;
	USART_InitTypeDef init_USART;

	USART_StructInit(&init_USART);
	GPIO_StructInit(&init_GPIO_USART);

	// Enable clock on GPIOBA and USART4 devices
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

	// Select AF mode USART3 for pin A0 and A1
	init_GPIO_USART.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	init_GPIO_USART.GPIO_Speed = GPIO_Speed_50MHz;
	init_GPIO_USART.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA, &init_GPIO_USART);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4);

	// Init USART 4
	init_USART.USART_BaudRate = baudrate;
	init_USART.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART4, &init_USART);

	USART_Cmd(UART4, ENABLE);
}

/**
 * @brief  Set the servo angle in %. Note that the angle is relative to the min
 *         and the max value set in the servo structure configuration.
 * @param  
 * @param  
 * @retval None
 */
void ausbeeSetAngleAX12()
{

}

/**
 * @brief  Return the angle value related to the specified AX12
 * @param  
 * @retval 
 */
uint8_t ausbeeGetAngleAX12()
{

}

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */

/************** (C) COPYRIGHT 2013-2014 Eirbot **** END OF FILE ****/
