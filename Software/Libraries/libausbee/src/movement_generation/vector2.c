// TODO: write a function to perform sqrt
#include <math.h>
#include "vector2.h"

#define SQUARE(x) ((x) * (x))
#define SQRT(x)   sqrt(x)

int vector2_norm(const struct vector2 * v)
{
  return SQRT(SQUARE(v->x) + SQUARE(v->y));
}

