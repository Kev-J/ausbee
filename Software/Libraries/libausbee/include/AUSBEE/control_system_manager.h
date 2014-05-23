/**
 ********************************************************************
 * @file    control_system_manager.h
 * @author  David BITONNEAU <david.bitonneau@gmail.com>
 * @version V1.3
 * @date    23-May-2014
 * @brief   Controller system manager definition file.
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
#ifndef CONTROL_SYSTEM_MANAGER_H
#define CONTROL_SYSTEM_MANAGER_H

/** @addtogroup Libausbee
  * @{
  */

/** @defgroup Control_System
  * @brief Control engineering module
  * @{
  */

/** @defgroup Control_System_Manager
  * @brief Control system manager for the control engineering module.
  * @{
  */

/**
 * @struct ausbee_cs
 * @brief Control system structure
 *
 * ausbee_cs contains all the parameters and status of the control system
 * manager.
 *
 */
struct ausbee_cs {
  float (*reference_filter)(void *, float);
  void * reference_filter_params;

  float (*measure_fetcher)(void *);
  void * measure_fetcher_params;

  float (*measure_filter)(void *, float);
  void * measure_filter_params;

  float (*controller)(void *, float);
  void * controller_params;

  void (*process_command)(void *, float);
  void * process_command_params;

  float reference;          /*!< The value we want to reach. */
  float filtered_reference; /*!< The value we think we can reach now. */
  float measure;            /*!< Last measured value. */
  float filtered_measure;   /*!< Last measured value filtered. */
  float error;              /*!< Last computed error. */
  float command;            /*!< Last command computed by the controller. */
};

void ausbee_cs_init(struct ausbee_cs *cs);

void ausbee_cs_set_reference_filter(struct ausbee_cs *cs,
    float (*reference_filter)(void *, float),
    void * reference_filter_params);

void ausbee_cs_set_measure_fetcher(struct ausbee_cs *cs,
    float (*measure_fetcher)(void *),
    void * measure_fetcher_params);

void ausbee_cs_set_measure_filter(struct ausbee_cs *cs,
    float (*measure_filter)(void *, float),
    void * measure_filter_params);

void ausbee_cs_set_controller(struct ausbee_cs *cs,
    float (*controller)(void *, float),
    void * controller_params);

void ausbee_cs_set_process_command(struct ausbee_cs *cs,
    void (*process_command)(void *, float),
    void * process_command_params);

float ausbee_cs_update(struct ausbee_cs *cs, float measure);
void    ausbee_cs_manage(void *cs);

float ausbee_cs_get_reference(struct ausbee_cs *cs);
float ausbee_cs_get_filtered_reference(struct ausbee_cs *cs);
float ausbee_cs_get_measure(struct ausbee_cs *cs);
float ausbee_cs_get_filtered_measure(struct ausbee_cs *cs);
float ausbee_cs_get_error(struct ausbee_cs *cs);
float ausbee_cs_get_command(struct ausbee_cs *cs);

void ausbee_cs_set_reference(struct ausbee_cs *cs, float ref);

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

/************** (C) COPYRIGHT 2013-2014 Eirbot **** END OF FILE ****/
