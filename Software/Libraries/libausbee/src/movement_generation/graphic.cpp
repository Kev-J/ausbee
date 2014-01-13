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

void Graphic::addAbs(int abs)
{
  if (fp != NULL) {
    fprintf(fp, "\n%d", abs);
  }
}

void Graphic::addValue(AUSBEE::Vector2 val)
{
  if (fp != NULL) {
    fprintf(fp, " %d %d", val.x, val.y);
  }
}

void Graphic::addValue(int val)
{
  if (fp != NULL) {
    fprintf(fp, " %d", val);
  }
}
