/**
 ********************************************************************
 * @file    quadramp.h
 * @author  David BITONNEAU <david.bitonneau@gmail.com>
 * @version V1.0
 * @date    23-May-2014
 * @brief   Quadramp filter implementation file.
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
#ifndef QUADRAMP_H
#define QUADRAMP_H

/** @addtogroup Libausbee
  * @{
  */

/** @addtogroup Control_System
  * @brief Control engineering module
  * @{
  */

/** @addtogroup Filters
  * @brief Filters for the control engineering module
  * @{
  */

/** @addtogroup Quadramp
  * @brief Quadramp filter
  * @{
  */

/**
 * @struct ausbee_diff
 * @brief PID controller structure
 *
 * ausbee_diff contains all the parameters and status of the diff
 * filter.
 *
 */
struct ausbee_quadramp {
    float var_2nd_ord_pos;
    float var_2nd_ord_neg;
    float var_1st_ord_pos;
    float var_1st_ord_neg;

    float prev_var; /*!< Previous variation. */
    float prev_out; /*!< Previous ouput value. */
    float prev_in;  /*!< Previous input value. */
};

/** Initialization of the filter */
void ausbee_quadramp_init(struct ausbee_quadramp *q);

void ausbee_quadramp_set_2nd_order_vars(struct ausbee_quadramp *q,
				 float var_2nd_ord_pos,
				 float var_2nd_ord_neg);

void ausbee_quadramp_set_1st_order_vars(struct ausbee_quadramp *q,
				 float var_1st_ord_pos,
				 float var_1st_ord_neg);

/**
 * Return 1 when (filter_input == filter_output && 1st_ord variation
 * is 0 --speed is 0-- ).
 */
int ausbee_quadramp_is_finished(struct ausbee_quadramp *q);
float ausbee_quadramp_eval(void *q, float in);

#endif /* QUADRAMP_H */

/**
  * @}
  */

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
