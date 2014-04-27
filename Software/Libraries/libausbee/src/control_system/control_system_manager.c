/**
 * \file control_system_manager.c
 * \brief Control system manager implementation file.
 * \author David BITONNEAU
 *
 * Control system manager implementation file.
 *
 */
#include <stdlib.h>
#include <AUSBEE/device.h>
#include <AUSBEE/l298_driver.h>
#include <AUSBEE/control_system_manager.h>

#define AUSBEE_DEBUG_PRINTF 1

#if AUSBEE_DEBUG_PRINTF == 1
#include <stdio.h>
#define debug_printf(args...) do { printf(args); } while(0)
#else
#define debug_printf(args...) do { } while(0)
#endif

/** \addtogroup Libausbee
  * \{
  */

/** \defgroup Control system manager
  * \brief Control engineering module.
  * \{
  */

/**
 * \fn void ausbee_cs_init(struct ausbee_cs *cs)
 * \brief ausbee_cs structure initialisation.
 *
 * \param cs The structure to initialise.
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
  * \fn void ausbee_cs_update(void *cs)
  * \brief Process the control loop to compute the command.
  *
  * \param data Control system structure reference.
  * \param measure The measure
  */
void ausbee_cs_update(struct ausbee_cs *cs, int32_t measure)
{
  cs->measure = measure;

  cs->command = cs->controller(cs->controller_params, cs->measure);

  debug_printf("[csm] Controller output command: %d\r\n", cs->command);
  cs->process_command(cs->process_command_params, cs->command);
}

/**
  * \}
  */

/**
  * \}
  */
