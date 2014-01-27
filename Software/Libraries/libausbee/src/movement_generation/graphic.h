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

  void addAbs(int abs);
  void addValue(AUSBEE::Vector2 val);
  void addValue(int val);
};

#endif /* GRAPH_GEN_H */
