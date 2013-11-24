#include "AUSBEE/can.h"

namespace AUSBEE{

  CAN::CAN(int x)
  {
    //Test if x is 1 or 2
    if (x==2)
      {
	// if x=2 then CANx points to CAN2
	CAN_TypeDef* CAN2;
	CANx=CAN2;
      }
    else 
      {
	// if x!=2 then CANx points to CAN1 (default CAN is CAN1)
	CAN_TypeDef* CAN1;
	CANx=CAN1;
      }

    CAN_Init(&CAN
  }
