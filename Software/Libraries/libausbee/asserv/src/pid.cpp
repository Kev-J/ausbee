#include "pid.h"

namespace AUSBEE {

PID::PID(int16_t _Kp, int16_t _Ki, int16_t _Kd)
{
  Kp = _Kp;
  Kd = _Kd;
  Ki = _Ki;
}

} // namespace AUSBEE
