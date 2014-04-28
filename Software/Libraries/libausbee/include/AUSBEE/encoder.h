#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>
#include <stm32f4xx_tim.h>

void ausbee_init_sampling_timer(TIM_TypeDef *TIMX, int32_t prescaler, int32_t period);
void ausbee_encoder_init_timer(TIM_TypeDef *TIMX);

#endif // ENCODER_H
