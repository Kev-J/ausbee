#ifndef CAN_H
#define CAN_H

#include <stdint.h>
#include <stm32f4xx_can.h>


namespace AUSBEE {
  class CAN {
  private:
    CAN_InitTypeDef *_canInitTypeDef;
    CAN_FilterInitTypeDef *_canFilterInitTypeDef;
    CanTxMsg *_TxMsg;
    CanRxMsg *_RxMsg;
    CAN_TypeDef* _CANx;
    
  public:
    CAN(int x); // x must be 1 or 2 (select CAN 1 or CAN 2)
    uint8_t changeCanParameters(CAN_initTypeDef* canInitTypeDef);
    void changeCanFilterParameters(CAN_FilterInitTypeDef* canFilterInitTypeDef);
    
  };
}


#endif //CAN_H
