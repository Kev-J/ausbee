/**
 ********************************************************************
 * @file    control_system_manager.c
 * @author  David BITONNEAU <david.bitonneau@gmail.com>
 * @version V1.0
 * @date    11-Mar-2014
 * @brief   Controller system manager implementation file.
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
#include <stdlib.h>
#include <inttypes.h>
#include <AUSBEE/device.h>
#include <AUSBEE/l298_driver.h>
#include <AUSBEE/control_system_manager.h>

#define AUSBEE_DEBUG_PRINTF 0

#if AUSBEE_DEBUG_PRINTF == 1
#include <stdio.h>
#define debug_printf(args...) do { printf(args); } while(0)
#else
#define debug_printf(args...) do { } while(0)
#endif

/** @addtogroup Libausbee
  * @{
  */

/** @addtogroup Control_System
  * @brief Control engineering module
  * @{
  */

/** @addtogroup Control_System_Manager
  * @brief Control system manager for the control engineering module.
  * @{
  */

/**
 * @fn void ausbee_cs_init(struct ausbee_cs *cs)
 * @brief ausbee_cs structure initialisation.
 *
 * @param cs The structure to initialise.
 *
 */
void ausbee_cs_init(struct ausbee_cs *cs)
{
  cs->controller = NULL;
  cs->controller_params = NULL;

  cs->measure = 0;
  cs->command = 0;
}

void ausbee_cs_set_controller(struct ausbee_cs *cs,
    int32_t (*controller)(void *, int32_t),
    void * controller_params)
{
  cs->controller = controller;
  cs->controller_params = controller_params;
}

void ausbee_cs_set_process_command(struct ausbee_cs *cs,
    void (*process_command)(void *, int32_t),
    void * process_command_params)
{
  cs->process_command = process_command;
  cs->process_command_params = process_command_params;
}

/**
  * @fn void ausbee_cs_update(void *cs)
  * @brief Process the control loop to compute the command.
  *
  * @param data Control system structure reference.
  * @param measure The measure
  *
  * @return Command value
  */
int32_t ausbee_cs_update(struct ausbee_cs *cs, int32_t measure)
{
  cs->measure = measure;
  debug_printf("[csm] Input measure: %"PRId32"\r\n", measure);

  cs->command = cs->controller(cs->controller_params, cs->measure);

  debug_printf("[csm] Controller output command: %"PRId32"\r\n", cs->command);
  cs->process_command(cs->process_command_params, cs->command);

  return cs->command;
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

/************** (C) COPYRIGHT 2013 Eirbot **** END OF FILE ****/
