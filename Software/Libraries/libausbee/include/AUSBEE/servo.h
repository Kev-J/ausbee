/**
  ********************************************************************
  * @file    servo.h
  * @author  Luc PRAMPOLINI <luc.prampolini@gmail.com>
  * @version V1.0
  * @date    20-Dec-2013
  * @brief   This file contains all the functions prototype for the
  *          servo library.
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
#ifndef _SERVO_H
#define _SERVO_H

/* Includes */
#include <AUSBEE/device.h>


#ifdef STM32F4XX
#include <stm32f4xx_tim.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#else
#ifdef STM32F10X
#include <stm32f10x_tim.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#endif
#endif

//#include <platform.h>

/**
  * @addtogroup Libausbee
  * @{
  */

/**
  * @addtogroup Servo
  * @{
  */


/**
  * @defgroup TIM_Channel_Define
  * @{
  */
/*
#define TIM1_Ch1 GPIO_Pin_8  //!< Timer 1 Channel 1 selected 
#define TIM1_Ch2 GPIO_Pin_9  //!< Timer 1 Channel 2 selected 
#define TIM1_Ch3 GPIO_Pin_10 //!< Timer 1 Channel 3 selected 
#define TIM1_Ch4 GPIO_Pin_11 //!< Timer 1 Channel 4 selected 

#define TIM2_Ch1 GPIO_Pin_0  //!< Timer 2 Channel 1 selected 
#define TIM2_Ch2 GPIO_Pin_1  //!< Timer 2 Channel 2 selected 
#define TIM2_Ch3 GPIO_Pin_2  //!< Timer 2 Channel 3 selected 
#define TIM2_Ch4 GPIO_Pin_3  //!< Timer 2 Channel 4 selected 

#define TIM3_Ch1 GPIO_Pin_6  //!< Timer 3 Channel 1 selected 
#define TIM3_Ch2 GPIO_Pin_7  //!< Timer 3 Channel 2 selected 
#define TIM3_Ch3 GPIO_Pin_0  //!< Timer 3 Channel 3 selected 
#define TIM3_Ch4 GPIO_Pin_1  //!< Timer 3 Channel 4 selected 
*/
/**
  * @}
  */

/**
  * @defgroup Servo_Exported_Types
  * @{
  */

/**
  * @brief Servo structure definition 
  */

typedef struct
{
  uint16_t     maxValue; /*!< Maximum value for the high level in us */
  uint16_t     minValue; /*!< Minimum value for the high level in us */
  TIM_TypeDef* TIMx;     /*!< Timer used */
  uint16_t     CHANx;    /*!< Channel used, can be TIM_Channel_x with x={1..4} */
} ausbeeServo;

/**
  * @}
  */

/**
  * @defgroup Servo_Exported_Functions
  * @{
  */

void    ausbeeInitStructServo(ausbeeServo* servo);                // Default parameters initialization
void    ausbeeInitServo(ausbeeServo* servo);                      // PWM initialization
void    ausbeeSetAngleServo(ausbeeServo* servo, uint8_t inAngle); // Set servo angle
uint8_t ausbeeGetAngleServo(ausbeeServo* servo);                  // Return servo angle

#endif /* _SERVO_H */

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
