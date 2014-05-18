/**
 ********************************************************************
 * @file    ax12.h
 * @author  Vincent CESSON <cesson.vincent@gmail.com>
 * @version V1.0
 * @date    20-Feb-2014
 * @brief   This file contains all the functions prototype  and 
 *			 definesfor the Ax12 library.
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

/* Define to prevent recursive inclusion */
#ifndef _AX12_H
#define _AX12_H

/* Includes */
//#include <platform.h> // WARNING no include of platform in libausbee
#include <stdint.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_usart.h>
#include <stm32f4xx_rcc.h>
/**
 * @addtogroup Libausbee
 * @{
 */

/**
 * @addtogroup AX12
 * @{
 */


/**
 * @defgroup AX12_Defines
 * @{
 */

#define LIBAUSBEE_AX12_BROADCAST_ID			0xFE
#define LIBAUSBEE_AX12_INSTR_PING			0x01
#define LIBAUSBEE_AX12_INSTR_RDATA			0x02
#define LIBAUSBEE_AX12_INSTR_WDATA			0x03
#define LIBAUSBEE_AX12_INSTR_REGWRITE		0x04
#define LIBAUSBEE_AX12_INSTR_ACTION			0x05
#define LIBAUSBEE_AX12_INSTR_RESET			0x06
#define LIBAUSBEE_AX12_INSTR_SYNCWRITE		0x83

#define LIBAUSBEE_AX12_REG_MODEL_NUM_L		0x00
#define LIBAUSBEE_AX12_REG_MODEL_NUM_H		0x01
#define LIBAUSBEE_AX12_REG_VERSION			0x02
#define LIBAUSBEE_AX12_REG_ID				0x03
#define LIBAUSBEE_AX12_REG_BAUDRATE			0x04
#define LIBAUSBEE_AX12_REG_GOAL_POS_L		0x1E
#define LIBAUSBEE_AX12_REG_GOAL_POS_H		0x1F
#define LIBAUSBEE_AX12_REG_PRESENT_POS_L	0x24
#define LIBAUSBEE_AX12_REG_PRESENT_POS_H	0x25

/**
 * @}
 */

/**
 * @defgroup AX12_Exported_Types
 * @{
 */

/**
 * @brief AX12 structure definition 
 */

typedef struct
{
	uint8_t id;
	uint8_t length;
	uint8_t instruct;
	uint8_t *parameters;
} ausbeeAX12packet;

/**
 * @}
 */

/**
 * @defgroup Servo_Exported_Functions
 * @{
 */

void    ausbeeInitAX12(uint32_t baudrate);                      // PWM initialization
void    ausbeeSetAngleAX12(); // Set servo angle
uint8_t ausbeeGetAngleAX12();                  // Return servo angle

#endif /* _AX12_H */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**************** (C) COPYRIGHT 2013-2014 Eirbot **** END OF FILE ****/
