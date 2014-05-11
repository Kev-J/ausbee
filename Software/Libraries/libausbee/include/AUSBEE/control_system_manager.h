/**
 ********************************************************************
 * @file    control_system_manager.c
 * @author  David BITONNEAU <david.bitonneau@gmail.com>
 * @version V1.1
 * @date    11-Mar-2014
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
 * <h2><centor>&copy;  Copyright 2013 (C) EIRBOT </center></h2>
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
  int32_t (*measure_fetcher)(void *);
  void * measure_fetcher_params;

  int32_t (*controller)(void *, int32_t);
  void * controller_params;

  void (*process_command)(void *, int32_t);
  void * process_command_params;

  int32_t reference; /*!< The value we when to reach. */
  int32_t measure;   /*!< Last measured value. */
  int32_t error;     /*!< Last computed error. */
  int32_t command;   /*!< Last command computed by the controller. */
};

void ausbee_cs_init(struct ausbee_cs *cs);

void ausbee_cs_set_measure_fetcher(struct ausbee_cs *cs,
    int32_t (*measure_fetcher)(void *),
    void * measure_fetcher_params);

void ausbee_cs_set_controller(struct ausbee_cs *cs,
    int32_t (*controller)(void *, int32_t),
    void * controller_params);

void ausbee_cs_set_process_command(struct ausbee_cs *cs,
    void (*process_command)(void *, int32_t),
    void * process_command_params);

int32_t ausbee_cs_update(struct ausbee_cs *cs, int32_t measure);
void    ausbee_cs_manage(void *cs);

int32_t ausbee_cs_get_reference(struct ausbee_cs *cs);
int32_t ausbee_cs_get_measure(struct ausbee_cs *cs);
int32_t ausbee_cs_get_error(struct ausbee_cs *cs);
int32_t ausbee_cs_get_command(struct ausbee_cs *cs);

void ausbee_cs_set_reference(struct ausbee_cs *cs, int32_t ref);

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

/************** (C) COPYRIGHT 2013 Eirbot **** END OF FILE ****/
