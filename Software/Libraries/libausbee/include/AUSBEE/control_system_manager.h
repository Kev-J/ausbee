/**
 * \file control_system_manager.h
 * \brief Control system manager definition file.
 *
 * \author David BITONNEAU
 *
 * Control system definition file.
 *
 */
#ifndef CONTROL_SYSTEM_MANAGER_H
#define CONTROL_SYSTEM_MANAGER_H

/** \addtogroup Libausbee
  * \{
  */

/** \defgroup Control system manager
  * \brief Control engineering module.
  * \{
  */

/**
 * \struct ausbee_cs
 * \brief Control system structure
 *
 * ausbee_cs contains all the parameters and status of the control system
 * manager.
 *
 */
struct ausbee_cs {
  int32_t (*controller)(void *, int32_t);
  void * controller_params;

  void (*process_command)(void *, int32_t);
  void * process_command_params;

  int32_t measure; /*!< Last measured value. */
  int32_t command; /*!< Last command computed by the controller. */
};

void ausbee_cs_init(struct ausbee_cs *cs);

void ausbee_cs_set_controller(struct ausbee_cs *cs,
    int32_t (*controller)(void *, int32_t),
    void * controller_params);

void ausbee_cs_set_process_command(struct ausbee_cs *cs,
    void (*process_command)(void *, int32_t),
    void * process_command_params);

void ausbee_cs_update(struct ausbee_cs *cs, int32_t measure);

/**
  * \}
  */

/**
  * \}
  */

#endif
