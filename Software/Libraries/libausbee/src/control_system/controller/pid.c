/**
 * \file pid.c
 * \brief Controller implementation file.
 * \author Kevin JOLY
 *
 * Controller implementation file. Contain controllers for control engineering.
 *
 */
#include "AUSBEE/device.h"
#include "AUSBEE/pid.h"

/** \addtogroup Libausbee
  * \{
  */

/** \defgroup Controller
  * \brief Control engineering module.
  * \{
  */

/**
 * \fn void ausbee_init_pid(struct ausbee_pid *pid, int32_t Kp, int32_t Ki, int32_t Kd, int32_t reference, int32_t max_output, int32_t min_output)
 * \brief ausbee_pid structure initialisation.
 *
 * \param pid Structure reference.
 * \param Kp Proportional value.
 * \param Ki Integral value.
 * \param Kd Derivative value.
 * \param reference Initial reference value.
 * \param max_output Maximum saturation output value.
 * \param min_output Minimum saturation output value.
 *
 */
void ausbee_init_pid(struct ausbee_pid *pid, int32_t Kp, int32_t Ki, int32_t Kd, int32_t reference, int32_t max_output, int32_t min_output)
{
  pid->Kp = Kp;
  pid->Ki = Ki;
  pid->Kd = Kd;

  pid->reference = reference;

  pid->last_error = 0;
  pid->error_sum = 0;

  pid->max_output = max_output;
  pid->min_output = min_output;
}

/**
  * \fn int32_t ausbee_eval_pid(struct ausbee_pid *pid, int32_t measure)
  * \brief Compute PID control with the last measure.
  *
  * \param pid Generic structure reference.
  * \param measure Current measured value.
  *
  * \return Output value of the controller (i.e. the command).
  *
  */
int32_t ausbee_eval_pid(void *controller, int32_t measure)
{
  int32_t error;
  int32_t output;

  struct ausbee_pid *pid = (struct ausbee_pid *)controller;

  error = pid->reference - measure;

  pid->error_sum += error;

  output = pid->Kp * error + pid->Ki * pid->error_sum + pid->Kd * (error - pid->last_error);

  pid->last_error = error;

  if (output > pid->max_output)
    output = pid->max_output;

  if (output < pid->min_output)
    output = pid->min_output;

  return output;
}

/** 
  * \}
  */

/** 
  * \}
  */
