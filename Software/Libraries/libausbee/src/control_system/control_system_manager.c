/**
 * \file control_system_manager.c
 * \brief Control system manager implementation file.
 * \author David BITONNEAU
 *
 * Control system manager implementation file.
 *
 */
#include <stdlib.h>
#include "AUSBEE/device.h"
#include "AUSBEE/control_system_manager.h"

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
    int32_t (*controller)(struct ausbee_pid *, int32_t),
    void * controller_params)
{
  cs->controller = controller;
  cs->controller_params = controller_params;
}

/**
  * \fn void ausbee_cs_update(void *cs)
  * \brief Process the control loop to compute the command.
  *
  * \param data Control system structure reference.
  */
void ausbee_cs_update(void *data)
{
  for (;;) {
    struct ausbee_cs *cs = (struct ausbee_cs *)data;
    // TODO
    // Read measure value
    cs->measure = 0;

    struct ausbee_pid *pid = (struct ausbee_pid *)cs->controller_params;
    cs->command = cs->controller(pid, cs->measure);
  }
}

/**
  * \}
  */

/**
  * \}
  */
