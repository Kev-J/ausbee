/**
 ********************************************************************
 * @file    encoder.h
 * @author  David BITONNEAU <david.bitonneau@gmail.com>
 * @author  Fabien DEPRAETRE
 * @version V1.0
 * @date    18-Mar-2014
 * @brief   Encoders driver definition file.
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
#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>
#include <stm32f4xx_tim.h>

/**
  * @addtogroup Libausbee
  * @{
  */

/**
  * @addtogroup Encoder
  * @brief Encoder driver module
  * @{
  */

void ausbee_init_sampling_timer(TIM_TypeDef *TIMX, int32_t prescaler, int32_t period);
void ausbee_encoder_init_timer(TIM_TypeDef *TIMX);
void ausbee_encoder_clock_enable(TIM_TypeDef *TIMX);
void ausbee_encoder_clock_disable(TIM_TypeDef *TIMX);

#endif // ENCODER_H

/**
  * @}
  */

/**
  * @}
  */

/************** (C) COPYRIGHT 2013-2014 Eirbot **** END OF FILE ****/
