/**
 ********************************************************************
 * @file    diff.c
 * @author  David BITONNEAU <david.bitonneau@gmail.com>
 * @version V1.0
 * @date    23-May-2014
 * @brief   Diff filter implementation file.
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
#include "AUSBEE/diff.h"

/** @addtogroup Libausbee
  * @{
  */

/** @addtogroup Control_System
  * @brief Control engineering module
  * @{
  */

/** @defgroup Filters
  * @brief Filters for the control engineering module
  * @{
  */

/** @defgroup Diff
  * @brief Diff filter
  * @{
  */

/**
 * @fn void ausbee_diff_init(struct ausbee_diff *diff)
 * @brief ausbee_diff structure initialisation.
 *
 * @param diff Structure reference.
 */
void ausbee_diff_init(struct ausbee_diff *diff)
{
  diff->prev_in = 0;
  diff->first_call = 1;
  diff->delta = 1;
}

/**
 * @fn void ausbee_diff_set_delta(struct ausbee_diff *diff, float delta)
 * @brief Set ausbee_diff delta parameter.
 *
 * @param diff  Structure reference.
 * @param delta Delta value.
 */
void ausbee_diff_set_delta(struct ausbee_diff *diff, float delta)
{
  diff->delta = delta;
}

/**
 * @fn void ausbee_diff_eval(void *diff, float in)
 * @brief Compute difference between previous and current input.
 *
 * @param diff Structure reference.
 * @param in The current input value
 */
float ausbee_diff_eval(void *filter, float in)
{
  struct ausbee_diff *diff = (struct ausbee_diff *)filter;

  if (diff->first_call) {
    diff->first_call = 0;
    diff->prev_in = in;
    return 0;
  }

  float out = (in - diff->prev_in) / (diff->delta);

  diff->prev_in = in;

  return out;
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

/**
  * @}
  */

/************** (C) COPYRIGHT 2013-2014 Eirbot **** END OF FILE ****/
