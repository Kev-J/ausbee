#ifndef GRAPH_GEN_H
#define GRAPH_GEN_H

#include "quadramp.h"
#include <cstdio>
#include <string>

class Graphic {
private:
  FILE *fp;
public:
  Graphic(std::string filename);
  ~Graphic();
  void addValue(int time, AUSBEE::Vector2 val);
};

#endif /* GRAPH_GEN_H */
