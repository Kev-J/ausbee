#include "graphic.h"

Graphic::Graphic(std::string filename)
{
  fp = fopen(filename.c_str(), "w");
  if (fp == NULL) {
    perror("fopen");
  }
}

Graphic::~Graphic()
{
  if (fp != NULL) {
    fclose(fp);
  }
}

void Graphic::addValue(int time, AUSBEE::Vector2 val)
{
  if (fp != NULL) {
    fprintf(fp, "%d %d %d\n", time, val.x, val.y);
  }
}
