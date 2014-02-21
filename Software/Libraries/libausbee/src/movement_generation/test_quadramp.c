#include <stdio.h>
#include "vector2.h"
#include "quadramp.h"
#include "graphic.h"

int main(void) {
  struct vector2 xi = {0, 10000}, xf = {20000, -30000};

  FILE* fp = NULL;
  new_graphic(&fp, "graph/test.txt");

  struct quadramp move;
  new_quadramp(&move, &xi, &xf, 500, 50, 0);

  int time = 0;
  for (; time < 100; time++) {
    add_abs    (fp, time                            );
    add_vector2(fp, update             (&move, time));
    add_int    (fp, get_linear_position(&move      ));
    add_int    (fp, get_speed          (&move      ));
    add_int    (fp, get_acceleration   (&move      ));
  }

  free_graphic(fp);

  return 0;
}
