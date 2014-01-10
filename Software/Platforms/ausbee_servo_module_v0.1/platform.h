/**
 *
 * \file platform.h
 * \brief Platform support definitions for AUSBEE Servo Module V0.1
 * \author Kevin JOLY <joly.kevin25@gmail.com>
 *
 */
#ifndef PLATFORM_H
#define PLATFORM_H

#include <stm32f10x_tim.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_usart.h>
#include <stm32f10x_can.h>

// Prototypes
void platform_initClock(void);
void platform_initPwm(uint8_t Timer);
void platform_initLeds(void);
void platform_initUsart(void);
int  platform_initCAN(CAN_TypeDef* CANx);
void platform_SetupHardware(void);
void platform_printHexa(uint32_t val);
void platform_printString(char *string, uint32_t nb);

// Define for Leds
#define Led1 GPIO_Pin_12
#define Led2 GPIO_Pin_13
#define Led3 GPIO_Pin_14
#define Led4 GPIO_Pin_15
#define Led5 GPIO_Pin_4
#define Led6 GPIO_Pin_5
#define Led7 GPIO_Pin_6
#define Led8 GPIO_Pin_7
#define LedAll Led1 | Led2 | Led3 | Led4 | Led5 | Led6 | Led7 | Led8

// Define for PWM
#define Pin_PWM1 GPIO_Pin_0 // On PORTA
#define Pin_PWM2 GPIO_Pin_1
#define Pin_PWM3 GPIO_Pin_2
#define Pin_PWM4 GPIO_Pin_3
#define Pin_PWM5 GPIO_Pin_6
#define Pin_PWM6 GPIO_Pin_7
#define Pin_PWM7 GPIO_Pin_0 // On PORTB
#define Pin_PWM8 GPIO_Pin_1
#define Pin_PWM_GPIOA Pin_PWM1 | Pin_PWM2 | Pin_PWM3 | Pin_PWM4 | Pin_PWM5 | Pin_PWM6
#define Pin_PWM_GPIOB Pin_PWM7 | Pin_PWM8

// Define for Timer
#define TIMER2 0x01
#define TIMER3 0x02
#define TIMER_ALL TIMER2 | TIMER3

// Define for Servos
#define SERVO1_TIM  TIM2
#define SERVO2_TIM  TIM2
#define SERVO3_TIM  TIM2
#define SERVO4_TIM  TIM2
#define SERVO5_TIM  TIM3
#define SERVO6_TIM  TIM3
#define SERVO7_TIM  TIM3
#define SERVO8_TIM  TIM3

#define SERVO1_CHAN TIM_Channel_1
#define SERVO2_CHAN TIM_Channel_2
#define SERVO3_CHAN TIM_Channel_3
#define SERVO4_CHAN TIM_Channel_4
#define SERVO5_CHAN TIM_Channel_1
#define SERVO6_CHAN TIM_Channel_2
#define SERVO7_CHAN TIM_Channel_3
#define SERVO8_CHAN TIM_Channel_4

#endif


