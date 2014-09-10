/**
 ********************************************************************
 * @file    quadramp.h
 * @author  David BITONNEAU <david.bitonneau@gmail.com>
 * @version V1.1
 * @date    24-May-2014
 * @brief   Quadramp filter implementation file.
 *          This is actually a bang-bang control on second order.
 *
 * @brief
 * @verbatim
 * Positive input:                    Negative input:
 *  ^                                  +---+-----+---+-->
 *  |______________ in                 |
 *  |                                  |
 *  |                                  |
 *  |                                  |
 *  |                                  |______________ in
 *  +---+-----+---+-->                 v
 *
 * Output:                            Output:
 *  ^                                  +___+-----+---+-->
 *  |           ___                    |   --_
 *  |        _--                       |      -_
 *  |      _-                          |        -_
 *  |    _-                            |          --__
 *  |__--                              |
 *  +---+-----+---+-->                 v
 *
 * 2nd order:                         2nd order:
 *  ^                                  ^
 *  |                                  |
 *  |___  var_2nd_ord_pos              |          ___  var_1st_ord_pos
 *  |   |                              |         |   |
 *  |   |                              |         |   |
 *  |   |                              |         |   |
 *  +---+-----+---+-->                 +---+-----+---+-->
 *            |   |                    |   |
 *            |   |                    |   |
 *            |___| var_2nd_ord_neg    |___| var_2nd_ord_neg
 *
 * 1st order:                         1st order:
 *  ^                                  +---+-----+---+-->
 *  |    _____  var_1st_ord_pos        | \           /
 *  |   /     \                        |  \         /
 *  |  /       \                       |   \       /
 *  | /         \                      |    \_____/
 *  |/           \                     |           var_1st_ord_neg
 *  +---+-----+---+-->                 v
 *  @endverbatim
 *
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
 * @struct ausbee_quadramp
 * @brief Quadramp filter structure
 *
 * ausbee_quadramp contains all the parameters and status of the quadramp
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

    float eval_period;
};

/** Initialization of the filter */
void ausbee_quadramp_init(struct ausbee_quadramp *q);

/**
 * By default eval period is set to 1.
 * Setting this parameter to the period ausbee_quadramp_eval is called
 * allows to have 1st and 2nd order variations value independent from
 * this period.
 *
 * Let [V] be the unit of the value given as input to
 * ausbee_quadramp_eval and [T] the calling period.
 * 1st and 2nd order variations' unit will be respectively [V]/[T] and
 * [V]/([T]^2).
 *
 * For instance let's say the input is a distance which unit is in mm.
 * The 1st order will be a speed in mm/[T] and 2nd order an
 * acceleration in mm/([T]^2).
 * This is not inconvenient to use for to reasons:
 *  - These units are not meaningful, it is more likely we want to set
 *  the speed in mm/s and the acceleration in mm/s^2.
 *  - If the period changes, we have 1st and 2nd order variations'
 *  value because their unit have changed.
 *
 * Thus this function is provided so that if we want [T] to be seconds
 * and ausbee_quadramp_eval is called 10 times per second we just have
 * to set the period to 0.1 (s) and things will get more pleasant.
 */
void ausbee_quadramp_set_eval_period(struct ausbee_quadramp *q, float period);

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
