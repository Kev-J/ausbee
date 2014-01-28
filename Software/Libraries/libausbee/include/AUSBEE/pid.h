/**
 * \file pid.
 * \brief Controller definition file.
 * \author Kevin JOLY
 *
 * Controller definition file. Contain controllers for control engineering.
 *
 */
#ifndef PID_H
#define PID_H

struct ausbee_pid {
	int32_t Kp;
	int32_t Ki;
	int32_t Kd;

	int32_t command;

	int32_t last_error;
	int32_t error_sum;

	int32_t max_output;
	int32_t min_output;
};

void ausbee_init_pid(struct ausbee_pid *pid, int32_t Kp, int32_t Ki, int32_t Kd, int32_t command, int32_t max_output, int32_t min_output);
int32_t ausbee_eval_pid(struct ausbee_pid *pid, int32_t measure);

#endif
