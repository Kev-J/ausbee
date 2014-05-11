/**
 ********************************************************************
 * @file    pid.c
 * @author  Kevin JOLY
 * @author  David BITONNEAU <david.bitonneau@gmail.com>
 * @version V1.0
 * @date    11-Mar-2014
 * @brief   PID controller implementation file. Contain controllers
 *          for control engineering.
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
 * <h2><centor>&copy;  Copyright 2013 (C) EIRBOT </center></h2>
 ********************************************************************
 */
#include "AUSBEE/device.h"
#include "AUSBEE/pid.h"

/** @addtogroup Libausbee
  * @{
  */

/** @addtogroup Control_System
  * @brief Control engineering module
  * @{
  */

/** @defgroup Controllers
  * @brief Controllers for the control engineering module
  * @{
  */

/** @defgroup PID
  * @brief PID controller
  * @{
  */

/**
 * @fn void ausbee_init_pid(struct ausbee_pid *pid, int32_t Kp, int32_t Ki, int32_t Kd, int32_t max_output, int32_t min_output)
 * @brief ausbee_pid structure initialisation.
 *
 * @param pid Structure reference.
 * @param Kp Proportional value.
 * @param Ki Integral value.
 * @param Kd Derivative value.
 * @param max_output Maximum saturation output value.
 * @param min_output Minimum saturation output value.
 *
 */
void ausbee_init_pid(struct ausbee_pid *pid, int32_t Kp, int32_t Ki, int32_t Kd, int32_t max_output, int32_t min_output)
{
  pid->Kp = Kp;
  pid->Ki = Ki;
  pid->Kd = Kd;

  pid->last_error = 0;
  pid->error_sum = 0;

  pid->max_output = max_output;
  pid->min_output = min_output;
}

/**
  * @fn int32_t ausbee_eval_pid(void *pid, int32_t measure)
  * @brief Compute PID control with the last measure.
  *
  * @param pid Generic structure reference.
  * @param error Current computed error value.
  *
  * @return Output value of the controller (i.e. the command).
  *
  */
int32_t ausbee_eval_pid(void *controller, int32_t error)
{
  int32_t output;

  struct ausbee_pid *pid = (struct ausbee_pid *)controller;

  pid->error_sum += error;

  output = pid->Kp * error + pid->Ki * pid->error_sum + pid->Kd * (error - pid->last_error);

  pid->last_error = error;

  if (output > pid->max_output)
    output = pid->max_output;

  if (output < pid->min_output)
    output = pid->min_output;

  return output;
}

/**
  * @fn int32_t ausbee_get_pid_error(struct ausbee_pid *pid)
  * @brief Get last computed error
  *
  * @param pid Structure reference.
  *
  * @return Error value
  *
  */
int32_t ausbee_get_pid_error(struct ausbee_pid *pid)
{
  return pid->last_error;
}

/**
  * @fn int32_t ausbee_get_pid_error_sum(struct ausbee_pid *pid)
  * @brief Get last computed error_sum
  *
  * @param pid Structure reference.
  *
  * @return Error sum value
  *
  */
int32_t ausbee_get_pid_error_sum(struct ausbee_pid *pid)
{
  return pid->error_sum;
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

/**
  * @}
  */

/************** (C) COPYRIGHT 2013 Eirbot **** END OF FILE ****/
