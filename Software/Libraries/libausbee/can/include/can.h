#ifndef CAN_H
#define CAN_H

#include <stdint>
#include <stm32f4xx_can.h>

namespace AUSBEE {
  class CAN {
  private:
    CAN_InitTypeDef canInitTypeDef;
    CAN_FilterInitTypeDef canFilterInitTypeDef;
    CanTxMsg canTxMsg;
    CanRxMsg canRxMsg;
  public:
    CAN(CAN_TypeDef CANx); // x must be 1 or 2 (select CAN 1 or CAN 2)
    void 
  };
}


#endif //CAN_H
