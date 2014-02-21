#include "graphic.h"

void new_graphic(FILE **fp, const char * filename)
{
  *fp = fopen(filename, "w");
  if (NULL == *fp) {
    perror("fopen");
  }
}

void free_graphic(FILE *fp)
{
  if (fp != NULL) {
    fclose(fp);
  }
}

void add_abs(FILE *fp, int abs)
{
  if (fp != NULL) {
    fprintf(fp, "\n%d", abs);
  }
}

void add_vector2(FILE *fp, const struct vector2 *val)
{
  if (fp != NULL) {
    fprintf(fp, " %d %d", val->x, val->y);
  }
}

void add_int(FILE *fp, int val)
{
  if (fp != NULL) {
    fprintf(fp, " %d", val);
  }
}
