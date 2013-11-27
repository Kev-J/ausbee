#include "AUSBEE/can.h"

namespace AUSBEE{

  CAN::CAN(int x)
  {
    //Test if x is 1 or 2
    if (x==2)
      {
	// if x=2 then CANx points to CAN2
	CAN_TypeDef* CAN2;
	_CANx=CAN2;
      }
    else 
      {
	// if x!=2 then CANx points to CAN1 (default CAN is CAN1)
	CAN_TypeDef* CAN1;
	_CANx=CAN1;
      }

    CAN_Init(_CANx, _canInitTypeDef);              // Init the bus
                                                 // TODO: give initial value to the struct
    CAN_FilterInit(_CANx, _canFilterInitTypeDef);  // Init the reception Filter
                                                 //TODO: give in initial value to the struct
    CAN_DBGFreeze(_CANx, _ENABLE);                 // Default: CAN is active during debug
    CAN_TTComModCmd(_CANx, _DISABLE);              // Default: Function disable
    
  }

  /* Brief function to change Global parameters of the CAN */

  uint8_t CAN::changeCanParameters(CAN_initTypeDef* canInitTypeDef)
  {
    uint8_t initStatus;
    _canInitTypeDef=canInitTypeDef;
    // Init the bus with new parameters
    initStatus=CAN_Init(_CANx, _canInitTypeDef);
    return initStatus;  
  }

  void CAN::changeCanFilterParameters(CAN_FilterInitTypeDef* canFilterInitTypeDef){
    _canFilterInitTypeDef=canFilterInitTypeDef;
    CAN_FilterInit()
