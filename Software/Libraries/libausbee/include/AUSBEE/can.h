#ifndef CAN_H
#define CAN_H

#include <stdint.h>
#include <stm32f4xx_can.h>


namespace AUSBEE {
  class CAN {
  private:
    CAN_InitTypeDef canInitTypeDef;
    CAN_FilterInitTypeDef canFilterInitTypeDef;
    CanTxMsg canTxMsg;
    CanRxMsg canRxMsg;
    CAN_TypeDef* CANx;

  public:
    CAN(int x); // x must be 1 or 2 (select CAN 1 or CAN 2)
    void changeCanParameters(CAN_initTypeDef _canInitTypeDef);
    void changeCanFilterParameters(CAN_FilterInitTypeDef _canFilterInitTypeDef);
    
  };
}


#endif //CAN_H
