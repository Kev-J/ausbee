/**
 ********************************************************************
 * @file    pid.c
 * @author  Kevin JOLY
 * @author  David BITONNEAU <david.bitonneau@gmail.com>
 * @version V1.0
 * @date    14-Mar-2014
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
 * <h2><centor>&copy;  Copyright 2013-2014 (C) EIRBOT </center></h2>
 ********************************************************************
 */
#include "AUSBEE/device.h"
#include "AUSBEE/pid.h"

#include <math.h>

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
 * @fn void ausbee_pid_init(struct ausbee_pid *pid, float Kp, float Ki, float Kd)
 * @brief ausbee_pid structure initialisation.
 *
 * @param pid Structure reference.
 * @param Kp Proportional value.
 * @param Ki Integral value.
 * @param Kd Derivative value.
 *
 */
void ausbee_pid_init(struct ausbee_pid *pid, float Kp, float Ki, float Kd)
{
  pid->Kp = Kp;
  pid->Ki = Ki;
  pid->Kd = Kd;

  pid->last_error = 0;
  pid->error_sum = 0;
  pid->error_diff = 0;

  pid->min_output = -INFINITY;
  pid->max_output =  INFINITY;

  pid->error_deadband = 0;
}

/**
 * @fn void ausbee_pid_set_output_range(struct ausbee_pid *pid, float min_output, float max_output)
 * @brief Define bounds for pid output
 *
 * @param pid Structure reference.
 * @param min_output Minimum saturation output value.
 * @param max_output Maximum saturation output value.
 *
 */
void ausbee_pid_set_output_range(struct ausbee_pid *pid, float min_output, float max_output)
{
  pid->min_output = min_output;
  pid->max_output = max_output;
}

/**
 * @fn void ausbee_pid_set_error_deadband(struct ausbee_pid *pid, float error_deadband)
 * @brief Define a deadband for pid error
 *
 * @param pid Structure reference.
 * @param error_deadband Error within [-error_deadband, error_deadband] is considered equaling zero.
 *                       Useful to avoid some problems resulting from using floats.
 *                       Must be a positive number.
 *
 */
void ausbee_pid_set_error_deadband(struct ausbee_pid *pid, float error_deadband)
{
  pid->error_deadband = error_deadband;
}

void ausbee_pid_set_kp(struct ausbee_pid *pid, float Kp)
{
  pid->Kp = Kp;
}

void ausbee_pid_set_ki(struct ausbee_pid *pid, float Ki)
{
  pid->Ki = Ki;
}

void ausbee_pid_set_kd(struct ausbee_pid *pid, float Kd)
{
  pid->Kd = Kd;
}

float ausbee_pid_get_kp(struct ausbee_pid *pid)
{
  return pid->Kp;
}

float ausbee_pid_get_ki(struct ausbee_pid *pid)
{
  return pid->Ki;
}

float ausbee_pid_get_kd(struct ausbee_pid *pid)
{
  return pid->Kd;
}

/**
  * @fn float ausbee_pid_eval(void *pid, float error)
  * @brief Compute PID control from the last error.
  *
  * @param pid Generic structure reference.
  * @param error Current computed error value.
  *
  * @return Output value of the controller (i.e. the command).
  *
  */
float ausbee_pid_eval(void *controller, float error)
{
  float output;

  struct ausbee_pid *pid = (struct ausbee_pid *)controller;

  if ((error < pid->error_deadband) && (error > -pid->error_deadband))
    error = 0;

  pid->error_sum += error;
  pid->error_diff = error - pid->last_error;

  output = pid->Kp * error + pid->Ki * pid->error_sum + pid->Kd * pid->error_diff;

  pid->last_error = error;

  if (output > pid->max_output) {
    output = pid->max_output;
  }

  if (output < pid->min_output) {
    output = pid->min_output;
  }

  return output;
}

/**
  * @fn float ausbee_pid_get_error(struct ausbee_pid *pid)
  * @brief Get last computed error
  *
  * @param pid Structure reference.
  *
  * @return Error value
  *
  */
float ausbee_pid_get_error(struct ausbee_pid *pid)
{
  return pid->last_error;
}

/**
  * @fn float ausbee_pid_get_error_sum(struct ausbee_pid *pid)
  * @brief Get last computed error_sum
  *
  * @param pid Structure reference.
  *
  * @return Error sum value
  *
  */
float ausbee_pid_get_error_sum(struct ausbee_pid *pid)
{
  return pid->error_sum;
}

/**
  * @fn float ausbee_pid_get_error_diff(struct ausbee_pid *pid)
  * @brief Get last computed error_diff
  *
  * @param pid Structure reference.
  *
  * @return Error diff value
  *
  */
float ausbee_pid_get_error_diff(struct ausbee_pid *pid)
{
  return pid->error_diff;
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

/************** (C) COPYRIGHT 2013-2014 Eirbot **** END OF FILE ****/
