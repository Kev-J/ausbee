#include "AUSBEE/encoder.h"
#include "AUSBEE/device.h"

#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>

void ausbee_init_sampling_timer(TIM_TypeDef *TIMX, int32_t prescaler, int32_t period)
{
  // TODO : Check if another timer can be used

  if (TIMX == TIM8)
  {
    TIM_TimeBaseInitTypeDef timeBaseInitTypeDef;

    RCC_APB2PeriphClockCmd(RCC_APB2ENR_TIM8EN, ENABLE);

    TIM_TimeBaseStructInit(&timeBaseInitTypeDef);

    timeBaseInitTypeDef.TIM_Prescaler = prescaler;
    timeBaseInitTypeDef.TIM_Period = period;

    TIM_TimeBaseInit(TIM8, &timeBaseInitTypeDef);

    NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);
    TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);

    TIM_Cmd(TIM8, ENABLE);
  }
  else if (TIMX == TIM1)
  {
    TIM_TimeBaseInitTypeDef timeBaseInitTypeDef;

    RCC_APB2PeriphClockCmd(RCC_APB2ENR_TIM1EN, ENABLE);

    TIM_TimeBaseStructInit(&timeBaseInitTypeDef);

    timeBaseInitTypeDef.TIM_Prescaler = prescaler;
    timeBaseInitTypeDef.TIM_Period = period;

    TIM_TimeBaseInit(TIM1, &timeBaseInitTypeDef);

    NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

    TIM_Cmd(TIM1, ENABLE);
  }
}

/* TODO Add encoder type support (simple or quadrature) */
void ausbee_encoder_init_timer(TIM_TypeDef *TIMX)
{
  TIM_TimeBaseInitTypeDef timeBaseInitTypeDef;

  TIM_TimeBaseStructInit(&timeBaseInitTypeDef);

  timeBaseInitTypeDef.TIM_Period = 0xFFFF;

  TIM_TimeBaseInit(TIMX, &timeBaseInitTypeDef);

  TIM_TIxExternalClockConfig(TIMX, TIM_TS_TI1FP1, TIM_ICPolarity_Rising, 0x0);

  TIM_Cmd(TIMX, ENABLE);
}

void ausbee_encoder_clock_cmd(TIM_TypeDef *TIMX, FunctionalState new_state)
{
#ifdef STM32F4XX
  if (TIMX == TIM1)
  {
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_TIM1EN, new_state);
  }

  if (TIMX == TIM3)
  {
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM3EN, new_state);
  }
#else
#error Function not supported for this device /* TODO */
#endif
}

void ausbee_encoder_clock_enable(TIM_TypeDef *TIMX)
{
  ausbee_encoder_clock_cmd(TIMX, ENABLE);
}

void ausbee_encoder_clock_disable(TIM_TypeDef *TIMX)
{
  ausbee_encoder_clock_cmd(TIMX, DISABLE);
}
