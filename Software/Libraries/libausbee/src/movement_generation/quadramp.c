/**********************************************************************
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
 * Copyright 2013 (C) EIRBOT
 *
 * Authors :    David Bitonneau <david.bitonneau@gmail.com>
 *
 **********************************************************************/
/**********************************************************************
 * Movement generation with Bang Bang on acceleration.
 * Acceleration generation:
 *  ^
 *  |
 *  |___
 *  |   |
 *  |   |
 *  |   |    t2   tf
 *  +---+-----+---+-->
 *  0   t1    |   |
 *            |   |
 *            |___|
 *
 * Speed generation:
 *  ^
 *  |    _____
 *  |   /     \
 *  |  /       \
 *  | /         \
 *  |/       t2  \tf
 *  +---+-----+---+-->
 *  0   t1
 *
 * Position generation:
 *  ^
 *  |           ___
 *  |        _--
 *  |      _-
 *  |    _-
 *  |__--      t2
 *  +---+-----+---+-->
 *  0   t1       tf
 *
 * (tf - t2 = t1)
 *
 **********************************************************************/
#include "vector2.h"
#include "quadramp.h"
// TODO: write a function to perform sqrt
#include <math.h>

#define SQUARE(x) ((x) * (x))
#define SQRT(x)   sqrt(x)

void new_quadramp(struct quadramp *qd, const struct vector2 *xi, 
    const struct vector2 *xf, int max_speed, int max_acceleration, int t0)
{
  qd->xi.x = xi->x;
  qd->xi.y = xi->y;
  qd->xf.x = xf->x;
  qd->xf.y = xf->y;
  qd->mvt_vector.x = qd->xf.x - qd->xi.x;
  qd->mvt_vector.y = qd->xf.y - qd->xi.y;
  qd->max_speed = max_speed;
  qd->max_acceleration = max_acceleration;
  qd->t0 = t0;

  // Compute movement lenght
  qd->mvt_length = vector2_norm(&(qd->mvt_vector));

  // First  time slice (t0 to t1): speed from 0 to max_speed
  qd->t1 = qd->max_speed / qd->max_acceleration;
  // Second time slice (t1 to t2): constant speed to max_speed
  qd->t2 = qd->mvt_length / qd->max_speed;
  // Check when Bang Bang triangle
  if (qd->t1 >= qd->t2) {
    qd->t1 = SQRT(qd->mvt_length / qd->max_acceleration);
    qd->t2 = qd->t1;
  }
  // Third  time slice (t2 to tf): speed from max_speed to 0
  qd->tf = qd->t1 + qd->t2;

  // Initialise constants to compute l
  // for t in [0, t1]:  l(t) = -1/2 * max_acceleration * t^2
  qd->A1 =  1./2 * qd->max_acceleration;
  // for t in [t1, t2]: l(t) = max_acceleration * t1 * t - 1/2 * max_acceleration * t1^2
  qd->A2 = qd->max_acceleration * qd->t1;
  qd->B2 = -1./2 * qd->max_acceleration * SQUARE(qd->t1);

  // for t in [t2, tf]: l(t) = -1/2 * max_acceleration * (tf - t)^2 + L
  qd->A3 = -1./2 * qd->max_acceleration;
  qd->B3 = qd->mvt_length;
}

struct vector2 * update(struct quadramp *qd, int t)
{
  t -= qd->t0;

  if (t <= 0)
  {
    qd->a = 0;
    qd->v = 0;
    qd->l = 0;
  }
  else if (t < qd->t1) {
    qd->a = qd->max_acceleration;
    qd->v = qd->max_acceleration * t;
    qd->l = qd->A1 * SQUARE(t);
  }
  else if (t < qd->t2) {
    qd->a = 0;
    qd->v = qd->max_acceleration * qd->t1;
    qd->l = qd->A2 * t + qd->B2;
  }
  else if (t < qd->tf) {
    qd->a = - qd->max_acceleration;
    qd->v = qd->max_acceleration * (qd->tf - t);
    qd->l = qd->A3 * SQUARE(qd->tf - t) + qd->B3;
  }
  else {
    qd->a = 0;
    qd->v = 0;
    qd->l = qd->mvt_length;
  }

  qd->position.x = qd->xi.x + qd->mvt_vector.x * qd->l / qd->mvt_length;
  qd->position.y = qd->xi.y + qd->mvt_vector.y * qd->l / qd->mvt_length;
  return &(qd->position);
}

int get_linear_position(struct quadramp *qd)
{
  return qd->l;
}

int get_speed(struct quadramp *qd)
{
  return qd->v;
}

int get_acceleration(struct quadramp *qd)
{
  return qd->a;
}
