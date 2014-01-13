#include "quadramp.h"
// TODO: write a function to perform sqrt
#include <math.h>
#include <iostream>

using namespace std;

namespace AUSBEE {

std::ostream& operator<< (std::ostream& os, const Vector2& v)
{
  return os << "(" << v.x << ", " << v.y << ")";
}

#define SQUARE(x) ((x) * (x))
#define SQRT(x)   sqrt(x)

Vector2::Vector2(const Vector2 &copy)
{
  x = copy.x;
  y = copy.y;
}

int Vector2::norm(void) const
{
  return SQRT(SQUARE(x) + SQUARE(y));
}

Vector2 Vector2::operator+(const Vector2 &v2) const
{
  return Vector2(x + v2.x, y + v2.y);
}

Vector2 Vector2::operator-(const Vector2 &v2) const
{
  return Vector2(x - v2.x, y - v2.y);
}

Vector2 Vector2::operator*(int factor) const
{
  return Vector2(x * factor, y * factor);
}

Vector2 Vector2::operator/(int factor) const
{
  return Vector2(x / factor, y / factor);
}

Quadramp::Quadramp(const Vector2 &xi, const Vector2 &xf,
         int maxSpeed, int maxAcceleration, int t0):
  xi(xi), xf(xf), mvtVector(xf - xi),
  maxSpeed(maxSpeed),
  maxAcceleration(maxAcceleration),
  t0(t0)
{
  // Compute movement lenght
  mvtLength = mvtVector.norm();

  // First  time slice (t0 to t1): speed from 0 to maxSpeed
  t1 = maxSpeed / maxAcceleration;
  // Second time slice (t1 to t2): constant speed to maxSpeed
  t2 = mvtLength / maxSpeed;
  // Check when Bang Bang triangle
  if (t1 >= t2) {
    t1 = SQRT(mvtLength / maxAcceleration);
    t2 = t1;
  }
  // Third  time slice (t2 to tf): speed from maxSpeed to 0
  tf = t1 + t2;

  // Initialise constants to compute l
  // for t in [0, t1]:  l(t) = -1/2 * maxAcceleration * t^2
  A1 =  1./2 * maxAcceleration;
  // for t in [t1, t2]: l(t) = maxAcceleration * t1 * t - 1/2 * maxAcceleration * t1^2
  A2 = maxAcceleration * t1;
  B2 = -1./2 * maxAcceleration * SQUARE(t1);

  // for t in [t2, tf]: l(t) = -1/2 * maxAcceleration * (tf - t)^2 + L
  A3 = -1./2 * maxAcceleration;
  B3 = mvtLength;
}

Vector2 Quadramp::getPosition(int t)
{
  t -= t0;

  if (t <= 0)
  {
    a = 0;
    v = 0;
    l = 0;
  }
  else if (t < t1) {
    a = maxAcceleration;
    v = maxAcceleration * t;
    l =  A1 * SQUARE(t);
  }
  else if (t < t2) {
    a = 0;
    v = maxAcceleration * t1;
    l = A2 * t + B2;
  }
  else if (t < tf) {
    a = - maxAcceleration;
    v = maxAcceleration * (tf - t);
    l = A3 * SQUARE(tf - t) + B3;
  }
  else {
    a = 0;
    v = 0;
    l = mvtLength;
  }

  position = xi + mvtVector * l / mvtLength;
  return position;
}

Quadramp::~Quadramp()
{
}

};
