#ifndef AUSBEE_INIT_H
#define AUSBEE_INIT_H

#include <stm32f4xx_rcc.h>

void ausbeeInitHSEPLL(uint32_t PLLM, uint32_t PLLN, uint32_t PLLP, uint32_t PLLQ);
void ausbeeGPIOInitPortD(void);
void ausbeeGPIOInitPortG(void);

#endif
