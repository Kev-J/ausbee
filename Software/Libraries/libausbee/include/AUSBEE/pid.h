/**
 * \file pid.h
 * \brief Controller definition file.
 * \author Kevin JOLY
 *
 * Controller definition file. Contain controllers for control engineering.
 *
 */
#ifndef PID_H
#define PID_H

/** \addtogroup Libausbee
  * \{
  */

/** \defgroup Controller
  * \brief Control engineering module.
  * \{
  */

/**
 * \struct ausbee_pid
 * \brief PID controller structure
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

void ausbee_init_pid(struct ausbee_pid *pid, int32_t Kp, int32_t Ki, int32_t Kd, int32_t reference, int32_t max_output, int32_t min_output);
int32_t ausbee_eval_pid(struct ausbee_pid *pid, int32_t measure);

/** 
  * \}
  */

/** 
  * \}
  */

#endif
