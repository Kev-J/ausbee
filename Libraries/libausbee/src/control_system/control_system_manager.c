/**
 ********************************************************************
 * @file    control_system_manager.c
 * @author  David BITONNEAU <david.bitonneau@gmail.com>
 * @version V1.3
 * @date    23-May-2014
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
 * <h2><centor>&copy;  Copyright 2013-2014 (C) EIRBOT </center></h2>
 ********************************************************************
 */
#include <stdlib.h>
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

static float safe_filter(float (*f)(void *, float), void *params, float value)
{
  if (f) {
    return f(params, value);
  }
  return value;
}

/**
 * @fn void ausbee_cs_init(struct ausbee_cs *cs)
 * @brief ausbee_cs structure initialisation.
 *
 * @param cs The structure to initialise.
 *
 */
void ausbee_cs_init(struct ausbee_cs *cs)
{
  cs->reference_filter = NULL;
  cs->reference_filter_params = NULL;

  cs->measure_fetcher = NULL;
  cs->measure_fetcher_params = NULL;

  cs->measure_filter = NULL;
  cs->measure_filter_params = NULL;

  cs->controller = NULL;
  cs->controller_params = NULL;

  cs->process_command = NULL;
  cs->process_command_params = NULL;

  cs->reference = 0;
  cs->filtered_reference = 0;
  cs->measure = 0;
  cs->filtered_measure = 0;
  cs->error = 0;
  cs->command = 0;
}

/**
 * @fn void ausbee_cs_set_reference_filter(struct ausbee_cs *cs,
 *         float (*reference_filter)(void *, float),
 *         void * reference_filter_params)
 * @brief Setting a function to filter the reference value used by the
 *        control system.
 *
 * @param cs                    Control system structure reference.
 * @param reference_filter        Function to filter the reference value.
 * @param reference_filter_params Parameters for the function.
 *
 */
void ausbee_cs_set_reference_filter(struct ausbee_cs *cs,
    float (*reference_filter)(void *, float),
    void * reference_filter_params)
{
  cs->reference_filter = reference_filter;
  cs->reference_filter_params = reference_filter_params;
}

/**
 * @fn void ausbee_cs_set_measure_fetcher(struct ausbee_cs *cs,
 *         float (*measure_fetcher)(void *),
 *         void * measure_fetcher_params)
 * @brief Setting a function to get measure value used by the
 *        control system.
 *
 * @param cs                     Control system structure reference.
 * @param measure_fetcher        Function to get the measure value.
 * @param measure_fetcher_params Parameters for the function.
 *
 */
void ausbee_cs_set_measure_fetcher(struct ausbee_cs *cs,
    float (*measure_fetcher)(void *),
    void * measure_fetcher_params)
{
  cs->measure_fetcher = measure_fetcher;
  cs->measure_fetcher_params = measure_fetcher_params;
}

/**
 * @fn void ausbee_cs_set_measure_filter(struct ausbee_cs *cs,
 *         float (*measure_filter)(void *, float),
 *         void * measure_filter_params)
 * @brief Setting a function to filter the measure value used by the
 *        control system.
 *
 * @param cs                    Control system structure reference.
 * @param measure_filter        Function to filter the measure value.
 * @param measure_filter_params Parameters for the function.
 *
 */
void ausbee_cs_set_measure_filter(struct ausbee_cs *cs,
    float (*measure_filter)(void *, float),
    void * measure_filter_params)
{
  cs->measure_filter = measure_filter;
  cs->measure_filter_params = measure_filter_params;
}

/**
 * @fn void ausbee_cs_set_controller(struct ausbee_cs *cs,
 *         float (*controller)(void *, float),
 *         void * controller_params)
 * @brief Setting the controller to use in the control system.
 *
 * @param cs                Control system structure reference.
 * @param controller        Controller processing function.
 * @param controller_params Parameters for the processing function.
 *
 */
void ausbee_cs_set_controller(struct ausbee_cs *cs,
    float (*controller)(void *, float),
    void * controller_params)
{
  cs->controller = controller;
  cs->controller_params = controller_params;
}

/**
 * @fn void ausbee_cs_set_process_command(struct ausbee_cs *cs,
    void (*process_command)(void *, float),
    void * process_command_params)
 * @brief Setting the processing function for the command
 *        computed by the control system.
 *
 * @param cs                     Control system structure reference.
 * @param process_command        Command processing function.
 * @param process_command_params Parameters for the processing function.
 *
 */
void ausbee_cs_set_process_command(struct ausbee_cs *cs,
    void (*process_command)(void *, float),
    void * process_command_params)
{
  cs->process_command = process_command;
  cs->process_command_params = process_command_params;
}

/**
  * @fn float ausbee_cs_update(struct ausbee_cs *cs, float ref)
  * @brief Process the control loop to compute the command.
  *
  * @param cs  Control system structure reference.
  * @param ref The reference we want to reach.
  *
  * @return Command value
  */
float ausbee_cs_update(struct ausbee_cs *cs, float ref)
{
  cs->reference = ref;
  debug_printf("[csm] Input reference: %f\r\n", cs->reference);

  cs->filtered_reference = safe_filter(cs->reference_filter, cs->reference_filter_params, cs->reference);
  debug_printf("[csm] Filtered Reference: %f\r\n", cs->filtered_reference);

  cs->measure = cs->measure_fetcher(cs->measure_fetcher_params);
  debug_printf("[csm] Measure: %f\r\n", cs->measure);

  cs->filtered_measure = safe_filter(cs->measure_filter, cs->measure_filter_params, cs->measure);
  debug_printf("[csm] Filtered Measure: %f\r\n", cs->filtered_measure);

  cs->error = cs->filtered_reference - cs->filtered_measure;
  debug_printf("[csm] Error: %f\r\n", cs->error);

  cs->command = cs->controller(cs->controller_params, cs->error);
  debug_printf("[csm] Controller output command: %f\r\n", cs->command);

  cs->process_command(cs->process_command_params, cs->command);

  return cs->command;
}

/**
  * @fn void ausbee_cs_manage(void *cs)
  * @brief Apply ausbee_cs_update to the structure cs.
  *
  * @param cs Control system structure reference.
  *           Should be a (struct ausbee_cs *)
  */
void ausbee_cs_manage(void *data)
{
  struct ausbee_cs *cs = (struct ausbee_cs *)data;

  ausbee_cs_update(cs, cs->reference);
}

/**
 * @fn float ausbee_cs_get_reference(struct ausbee_cs *cs)
 * @brief Getting the reference we want to reach.
 *
 * @return Reference value.
 *
 */
float ausbee_cs_get_reference(struct ausbee_cs *cs)
{
  return cs->reference;
}

/**
 * @fn float ausbee_cs_get_filtered_reference(struct ausbee_cs *cs)
 * @brief Getting the filtered reference.
 *
 * @return Filtered reference value.
 *
 */
float ausbee_cs_get_filtered_reference(struct ausbee_cs *cs)
{
  return cs->filtered_reference;
}

/**
 * @fn float ausbee_cs_get_measure(struct ausbee_cs *cs)
 * @brief Getting the measure.
 *
 * @return Measure value.
 *
 */
float ausbee_cs_get_measure(struct ausbee_cs *cs)
{
  return cs->measure;
}

/**
 * @fn float ausbee_cs_get_filtered_measure(struct ausbee_cs *cs)
 * @brief Getting the filtered measure.
 *
 * @return Filtered measure value.
 *
 */
float ausbee_cs_get_filtered_measure(struct ausbee_cs *cs)
{
  return cs->filtered_measure;
}

/**
 * @fn float ausbee_cs_get_error(struct ausbee_cs *cs)
 * @brief Getting the computed error.
 *
 * @return Error value.
 *
 */
float ausbee_cs_get_error(struct ausbee_cs *cs)
{
  return cs->error;
}

/**
 * @fn float ausbee_cs_get_command(struct ausbee_cs *cs)
 * @brief Getting the computed command.
 *
 * @return Command value.
 *
 */
float ausbee_cs_get_command(struct ausbee_cs *cs)
{
  return cs->command;
}

/**
 * @fn void ausbee_cs_set_reference(struct ausbee_cs *cs, float ref)
 * @brief Setting the reference we want to reach.
 *
 * @param ref Reference value.
 *
 */
void ausbee_cs_set_reference(struct ausbee_cs *cs, float ref)
{
  cs->reference = ref;
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

/************** (C) COPYRIGHT 2013-2014 Eirbot **** END OF FILE ****/
