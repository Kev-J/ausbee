/**********************************************************************
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
 * Copyright 2013 (C) EIRBOT
 *
 * Authors :    Luc PRAMPOLINI <luc.prampolini@gmail.com>
 *
 **********************************************************************/

#ifndef _SERVO_H
#define _SERVO_H

#include <stm32f10x_tim.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

#define TIM1_Ch1 GPIO_Pin_8  // PA
#define TIM1_Ch2 GPIO_Pin_9
#define TIM1_Ch3 GPIO_Pin_10
#define TIM1_Ch4 GPIO_Pin_11

#define TIM2_Ch1 GPIO_Pin_0  // PA
#define TIM2_Ch2 GPIO_Pin_1
#define TIM2_Ch3 GPIO_Pin_2
#define TIM2_Ch4 GPIO_Pin_3

#define TIM3_Ch1 GPIO_Pin_6  // PA
#define TIM3_Ch2 GPIO_Pin_7
#define TIM3_Ch3 GPIO_Pin_0  // PB
#define TIM3_Ch4 GPIO_Pin_1

typedef struct
{
  uint16_t     maxValue;      // Maximum value for the high level in us
  uint16_t     minValue;      // Minimum value for the high level in us
  TIM_TypeDef* TIMx;          // Timer used
  uint16_t     CHANx;         // Channel used, can be TIM_Channel_x with x={1..4}
} ausbeeServo;

void    ausbeeInitStructServo(ausbeeServo* servo);                // Default parameters initialization
void    ausbeeInitServo(ausbeeServo* servo);                      // PWM initialization
void    ausbeeSetAngleServo(ausbeeServo* servo, uint8_t inAngle); // Set servo angle
uint8_t ausbeeGetAngleServo(ausbeeServo* servo);                  // Return servo angle

#endif /* _SERVO_H */
