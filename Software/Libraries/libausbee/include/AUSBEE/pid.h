/**
 ********************************************************************
 * @file    pid.h
 * @author  Kevin JOLY
 * @author  David BITONNEAU <david.bitonneau@gmail.com>
 * @version V1.0
 * @date    11-Mar-2014
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
 * <h2><centor>&copy;  Copyright 2013 (C) EIRBOT </center></h2>
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
  int32_t Kp; /*!< Proportionnal value. */
  int32_t Ki; /*!< Integral value. */
  int32_t Kd; /*!< Derivative value. */

  int32_t reference; /*!< Instruction given to the process (i.e. input). */

  int32_t last_error; /*!< Previous error observed. */
  int32_t error_sum; /*!< Sum of previous errors. */

  int32_t max_output; /*!< Maximum saturation output value. */
  int32_t min_output; /*!< Minimum saturation output value. */
};

void ausbee_init_pid(struct ausbee_pid *pid, int32_t Kp, int32_t Ki, int32_t Kd, int32_t max_output, int32_t min_output);
int32_t ausbee_eval_pid(void *pid, int32_t measure);

void    ausbee_pid_set_ref(struct ausbee_pid *pid, int32_t reference);
int32_t ausbee_pid_get_ref(struct ausbee_pid *pid);
int32_t ausbee_get_pid_error(struct ausbee_pid *pid);
int32_t ausbee_get_pid_error_sum(struct ausbee_pid *pid);

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

/************** (C) COPYRIGHT 2013 Eirbot **** END OF FILE ****/
