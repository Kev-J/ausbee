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
#ifndef QUADRAMP_H
#define QUADRAMP_H

#include "vector2.h"

struct quadramp {
  // movement parameters
  struct vector2 xi, xf, mvt_vector;
  int max_speed, max_acceleration;
  int mvt_length;

  // time slices
  int t0, t1, t2, tf;

  // Constants for fast computation of new position
  // for t in [0, t1]:  l(t) = A1 * t^2
  int A1;
  // for t in [t1, t2]: l(t) = A2 * t + B2
  int A2, B2;
  // for t in [t2, tf]: l(t) = A3 * (tf - t)^2 + B3
  int A3, B3;

  // result of update
  int l, v, a;
  struct vector2 position;
};

void new_quadramp(struct quadramp *qd, const struct vector2 *xi,
    const struct vector2 *xf, int max_speed, int max_acceleration, int t0);

// Returns the position for the given time
struct vector2 * update(struct quadramp *qd, int time);

// The following functions returns values for the last update
int get_linear_position(struct quadramp *qd);
int get_speed(struct quadramp *qd);
int get_acceleration(struct quadramp *qd);

#endif
