#include "quadramp.h"
#include "graphic.h"

using namespace AUSBEE;

int main(void) {
    Vector2 xi(0, 10000), xf(20000, -30000);

    Graphic graphic("graph/test.txt");
    Quadramp move(xi, xf, 500, 50, 0);

    for (int time = 0 ; time < 100; time++) {
        graphic.addAbs(time);
        graphic.addValue(move.update(time));
        graphic.addValue(move.getLinearPosition());
        graphic.addValue(move.getSpeed());
        graphic.addValue(move.getAcceleration());
    }

    return 0;
}
