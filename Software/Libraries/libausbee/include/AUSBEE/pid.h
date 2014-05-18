/**
 ********************************************************************
 * @file    pid.h
 * @author  Kevin JOLY
 * @author  David BITONNEAU <david.bitonneau@gmail.com>
 * @version V1.1
 * @date    14-Mar-2014
 * @brief   PID controller definition file. Contain controllers
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
#ifndef PID_H
#define PID_H

#include <stdint.h>

/** @addtogroup Libausbee
  * @{
  */

/** @addtogroup Control_System
  * @brief Control engineering module
  * @{
  */

/** @addtogroup Controllers
  * @brief Controllers for the control engineering module
  * @{
  */

/** @addtogroup PID
  * @brief PID controller
  * @{
  */

/**
 * @struct ausbee_pid
 * @brief PID controller structure
 *
 * ausbee_pid contains all the parameters and status of the PID controller.
 *
 */
struct ausbee_pid {
  int32_t Kp; /*!< Proportional value. */
  int32_t Ki; /*!< Integral value. */
  int32_t Kd; /*!< Derivative value. */

  float last_error; /*!< Previous error observed. */
  float error_sum; /*!< Sum of previous errors. */

  float min_output; /*!< Minimum saturation output value. */
  float max_output; /*!< Maximum saturation output value. */

  float error_deadband; /*!< An error within this deadband is considered equaling zero. */
};

void ausbee_pid_init(struct ausbee_pid *pid, int32_t Kp, int32_t Ki, int32_t Kd);
void ausbee_pid_set_output_range(struct ausbee_pid *pid, float min_output, float max_output);
void ausbee_pid_set_error_deadband(struct ausbee_pid *pid, float error_deadband);

float ausbee_pid_eval(void *pid, float error);

float ausbee_pid_get_error(struct ausbee_pid *pid);
float ausbee_pid_get_error_sum(struct ausbee_pid *pid);

#endif

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
