#ifndef PID_H
#define PID_H

#include <stdint>

namespace AUSBEE {
    class PID {
      private :
        int16_t Kp; /// Proportional coefficient
        int16_t Ki; /// Integral coefficient
        int16_t Kd; /// Derivative coefficient
      public :
        PID(int16_t Kp, int16_t Ki, int16_t Kd);
    };
}

#endif // PID_H
