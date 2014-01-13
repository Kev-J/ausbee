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

#include <iostream>

namespace AUSBEE {
  struct Vector2 {
    int x, y;

    Vector2(): x(0), y(0) {}
    Vector2(int x, int y): x(x), y(y) {}
    Vector2(const Vector2 &);

    int norm(void) const;

    // Returns the difference between two vectors
    Vector2 operator+(const Vector2 &) const;
    Vector2 operator-(const Vector2 &) const;
    Vector2 operator*(int factor) const;
    Vector2 operator/(int factor) const;
  };

  class Quadramp {
  public:
    Quadramp(const Vector2 &xi, const Vector2 &xf,
             int maxSpeed, int maxAcceleration, int t0);
    ~Quadramp();

    // Returns the position for the given time
    Vector2 update(int time);

    // The following functions returns values for the last update
    int getLinearPosition(void) const;
    int getSpeed(void)          const;
    int getAcceleration(void)   const;
  private:
    // movement parameters
    Vector2 xi, xf, mvtVector;
    int maxSpeed, maxAcceleration;
    int mvtLength;

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
    Vector2 position;
  };
};

#endif
