#ifndef GRAPH_GEN_H
#define GRAPH_GEN_H

#include <stdio.h>
#include <string.h>
#include "vector2.h"

void new_graphic(FILE **fp, const char * filename);
void free_graphic(FILE *fp);
void add_abs(FILE *fp, int abs);
void add_vector2(FILE *fp, const struct vector2 *val);
void add_int(FILE *fp, int val);

#endif /* GRAPH_GEN_H */
