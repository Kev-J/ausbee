/**
 ********************************************************************
 * @file    quadramp.c
 * @author  David BITONNEAU <david.bitonneau@gmail.com>
 * @version V1.1
 * @date    24-May-2014
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
#include <string.h>
#include <math.h>

#include "AUSBEE/quadramp.h"

#define SQUARE(x) ((x) * (x))

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

/** @defgroup Quadramp
  * @brief Quadramp filter
  * @{
  */

void ausbee_quadramp_init(struct ausbee_quadramp *q)
{
	memset(q, 0, sizeof(*q));
	q->eval_period = 1;
}

void ausbee_quadramp_set_eval_period(struct ausbee_quadramp *q, float period)
{
  q->eval_period = period;
}

void ausbee_quadramp_set_2nd_order_vars(struct ausbee_quadramp * q,
				 float var_2nd_ord_pos,
				 float var_2nd_ord_neg)
{
	q->var_2nd_ord_pos = var_2nd_ord_pos;
	q->var_2nd_ord_neg = var_2nd_ord_neg;
}

void ausbee_quadramp_set_1st_order_vars(struct ausbee_quadramp * q,
				 float var_1st_ord_pos,
				 float var_1st_ord_neg)
{
	q->var_1st_ord_pos = var_1st_ord_pos;
	q->var_1st_ord_neg = var_1st_ord_neg;
}

/* TODO: handle float equality */
int ausbee_quadramp_is_finished(struct ausbee_quadramp *q)
{
	return (q->prev_out == q->prev_in && q->prev_var == 0);
}

float ausbee_quadramp_eval(void * data, float in)
{
	struct ausbee_quadramp * q = data;
	float d ;
	float pos_target;
	float var_1st_ord_pos = 0;
	float var_1st_ord_neg = 0;
	float var_2nd_ord_pos = 0;
	float var_2nd_ord_neg = 0;
	float prev_var, prev_out ;

	if ( q->var_1st_ord_pos )
		var_1st_ord_pos = q->var_1st_ord_pos * q->eval_period;

	if ( q->var_1st_ord_neg )
		var_1st_ord_neg = -q->var_1st_ord_neg * q->eval_period;

	if ( q->var_2nd_ord_pos )
		var_2nd_ord_pos = q->var_2nd_ord_pos * SQUARE(q->eval_period);

	if ( q->var_2nd_ord_neg )
		var_2nd_ord_neg = -q->var_2nd_ord_neg * SQUARE(q->eval_period);

	prev_var = q->prev_var;
	prev_out = q->prev_out;

	d = in - prev_out ;

	/* Deceleration ramp */
	if ( d > 0 && var_2nd_ord_neg) {
		float ramp_pos;
		/* var_2nd_ord_neg < 0 */
		/* real EQ : sqrtf( var_2nd_ord_neg^2/4 - 2.d.var_2nd_ord_neg ) + var_2nd_ord_neg/2 */
		ramp_pos = sqrtf( (var_2nd_ord_neg*var_2nd_ord_neg)/4 - 2*d*var_2nd_ord_neg ) + var_2nd_ord_neg/2;

		if(ramp_pos < var_1st_ord_pos)
			var_1st_ord_pos = ramp_pos ;
	}

	else if (d < 0 && var_2nd_ord_pos) {
		float ramp_neg;

		/* var_2nd_ord_pos > 0 */
		/* real EQ : sqrtf( var_2nd_ord_pos^2/4 - 2.d.var_2nd_ord_pos ) - var_2nd_ord_pos/2 */
		ramp_neg = -sqrtf( (var_2nd_ord_pos*var_2nd_ord_pos)/4 - 2*d*var_2nd_ord_pos ) - var_2nd_ord_pos/2;
	
		/* ramp_neg < 0 */
		if(ramp_neg > var_1st_ord_neg)
			var_1st_ord_neg = ramp_neg ;
	}

	/* try to set the speed : can we reach the speed with our acceleration ? */
	/* si on va moins vite que la Vmax */
	if ( prev_var < var_1st_ord_pos )  {
		/* acceleration would be to high, we reduce the speed */
		/* si rampe acceleration active ET qu'on ne peut pas atteindre Vmax,
		 * on sature Vmax a Vcourante + acceleration */
		if (var_2nd_ord_pos && ( var_1st_ord_pos - prev_var > var_2nd_ord_pos) )
			var_1st_ord_pos = prev_var + var_2nd_ord_pos ;
	}
	/* si on va plus vite que Vmax */
	else if ( prev_var > var_1st_ord_pos )  {
		/* deceleration would be to high, we increase the speed */
		/* si rampe deceleration active ET qu'on ne peut pas atteindre Vmax,
		 * on sature Vmax a Vcourante + deceleration */
		if (var_2nd_ord_neg && ( var_1st_ord_pos - prev_var < var_2nd_ord_neg) )
			var_1st_ord_pos = prev_var + var_2nd_ord_neg;
	}

	/* same for the neg */
	/* si on va plus vite que la Vmin (en negatif : en vrai la vitesse absolue est inferieure) */
	if ( prev_var > var_1st_ord_neg )  {
		/* acceleration would be to high, we reduce the speed */
		/* si rampe deceleration active ET qu'on ne peut pas atteindre Vmin,
		 * on sature Vmax a Vcourante + deceleration */
		if (var_2nd_ord_neg && ( var_1st_ord_neg - prev_var < var_2nd_ord_neg) )
			var_1st_ord_neg = prev_var + var_2nd_ord_neg ;
	}
	/* si on va moins vite que Vmin (mais vitesse absolue superieure) */
	else if ( prev_var < var_1st_ord_neg )  {
		/* deceleration would be to high, we increase the speed */
		/* si rampe acceleration active ET qu'on ne peut pas atteindre Vmin,
		 * on sature Vmax a Vcourante + deceleration */
		if (var_2nd_ord_pos && (var_1st_ord_neg - prev_var > var_2nd_ord_pos) )
			var_1st_ord_neg = prev_var + var_2nd_ord_pos;
	}

	/*
	 * Position consign : can we reach the position with our speed ?
	 */
	if ( /* var_1st_ord_pos &&  */d > var_1st_ord_pos ) {
		pos_target = prev_out + var_1st_ord_pos ;
		prev_var = var_1st_ord_pos ;
	}
	else if ( /* var_1st_ord_neg &&  */d < var_1st_ord_neg ) {
		pos_target = prev_out + var_1st_ord_neg ;
		prev_var = var_1st_ord_neg ;
	}
	else {
		pos_target = prev_out + d ;
		prev_var = d ;
	}

	// update prev_out and prev_var
	q->prev_var = prev_var;
	q->prev_out = pos_target;
	q->prev_in = in;

	return pos_target ;
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
