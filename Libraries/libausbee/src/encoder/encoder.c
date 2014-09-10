/**
 ********************************************************************
 * @file    encoder.c
 * @author  David BITONNEAU <david.bitonneau@gmail.com>
 * @author  Fabien DEPRAETRE
 * @version V1.0
 * @date    18-Mar-2014
 * @brief   Encoders driver implementation file.
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
#include "AUSBEE/encoder.h"
#include "AUSBEE/device.h"

#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>

/**
  * @addtogroup Libausbee
  * @{
  */

/**
  * @defgroup Encoder
  * @brief Encoder driver module
  * @{
  */

void ausbee_init_sampling_timer(TIM_TypeDef *TIMX, int32_t prescaler, int32_t period)
{
  // TODO : Check if another timer can be used

  if (TIMX == TIM8)
  {
    TIM_TimeBaseInitTypeDef timeBaseInitTypeDef;

    TIM_TimeBaseStructInit(&timeBaseInitTypeDef);

    timeBaseInitTypeDef.TIM_Prescaler = prescaler;
    timeBaseInitTypeDef.TIM_Period = period;

    TIM_TimeBaseInit(TIM8, &timeBaseInitTypeDef);

    NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);
    TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);

    TIM_Cmd(TIM8, ENABLE);
  }
  else if (TIMX == TIM1)
  {
    TIM_TimeBaseInitTypeDef timeBaseInitTypeDef;

    TIM_TimeBaseStructInit(&timeBaseInitTypeDef);

    timeBaseInitTypeDef.TIM_Prescaler = prescaler;
    timeBaseInitTypeDef.TIM_Period = period;

    TIM_TimeBaseInit(TIM1, &timeBaseInitTypeDef);

    NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

    TIM_Cmd(TIM1, ENABLE);
  }
}

/* TODO Add encoder type support (simple or quadrature) */
void ausbee_encoder_init_timer(TIM_TypeDef *TIMX)
{
  TIM_TimeBaseInitTypeDef timeBaseInitTypeDef;

  TIM_TimeBaseStructInit(&timeBaseInitTypeDef);

  timeBaseInitTypeDef.TIM_Period = 0xFFFF;

  TIM_TimeBaseInit(TIMX, &timeBaseInitTypeDef);

  TIM_TIxExternalClockConfig(TIMX, TIM_TS_TI1FP1, TIM_ICPolarity_Rising, 0x0);

  TIM_Cmd(TIMX, ENABLE);
}

void ausbee_encoder_clock_cmd(TIM_TypeDef *TIMX, FunctionalState new_state)
{
#ifdef STM32F4XX
  if (TIMX == TIM1)
  {
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_TIM1EN, new_state);
  }

  if (TIMX == TIM8)
  {
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_TIM8EN, new_state);
  }

  if (TIMX == TIM3)
  {
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM3EN, new_state);
  }
#else
#error Function not supported for this device /* TODO */
#endif
}

void ausbee_encoder_clock_enable(TIM_TypeDef *TIMX)
{
  ausbee_encoder_clock_cmd(TIMX, ENABLE);
}

void ausbee_encoder_clock_disable(TIM_TypeDef *TIMX)
{
  ausbee_encoder_clock_cmd(TIMX, DISABLE);
}

/**
  * @}
  */
/**
  * @}
  */

/************** (C) COPYRIGHT 2013-2014 Eirbot **** END OF FILE ****/
