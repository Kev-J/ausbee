/**
 *
 * \file platform.h
 * \brief Platform support definitions for AUSBEE mainboard V0.1
 * \author Kevin JOLY <joly.kevin25@gmail.com>
 *
 */
#ifndef PLATFORM_H
#define PLATFORM_H

#include <stm32f4xx_tim.h>
#include <stm32f4xx_usart.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_can.h>

/**********
 * Clocks *
 **********/
#define PLATFORM_PLLM 8
#define PLATFORM_PLLN 336
#define PLATFORM_PLLP 2
#define PLATFORM_PLLQ 7

/********
 * LEDS *
 ********/
#define PLATFORM_LED0 0x1
#define PLATFORM_LED1 0x2
#define PLATFORM_LED2 0x4
#define PLATFORM_LED3 0x8
#define PLATFORM_LED4 0x10
#define PLATFORM_LED5 0x20
#define PLATFORM_LED6 0x40
#define PLATFORM_LED7 0x80

/**********
 * Motors *
 *********/
/* ENABLE */
#define PLATFORM_ENABLE_MOTOR1_PIN GPIO_Pin_0
#define PLATFORM_ENABLE_MOTOR1_PORT GPIOE
#define PLATFORM_ENABLE_MOTOR2_PIN GPIO_Pin_1
#define PLATFORM_ENABLE_MOTOR2_PORT GPIOE

/* DIR */
#define PLATFORM_DIR_MOTOR1_PIN GPIO_Pin_2
#define PLATFORM_DIR_MOTOR1_PORT GPIOE
#define PLATFORM_DIR_MOTOR2_PIN GPIO_Pin_3
#define PLATFORM_DIR_MOTOR2_PORT GPIOE

/* PWM */
#define PLATFORM_PWM_MOTOR1_PIN GPIO_Pin_5
#define PLATFORM_PWM_MOTOR1_PORT GPIOE
#define PLATFORM_PWM_MOTOR1_PIN_SOURCE GPIO_PinSource5
#define PLATFORM_PWM_MOTOR1_GPIO_AF GPIO_AF_TIM9
#define PLATFORM_PWM_MOTOR2_PIN GPIO_Pin_6
#define PLATFORM_PWM_MOTOR2_PORT GPIOE
#define PLATFORM_PWM_MOTOR2_PIN_SOURCE GPIO_PinSource6
#define PLATFORM_PWM_MOTOR2_GPIO_AF GPIO_AF_TIM9

/************
 * Encoders *
 ************/
//Encoder 1
#define PLATFORM_ENC1A_PIN             GPIO_Pin_9
#define PLATFORM_ENC1A_PORT            GPIOE
#define PLATFORM_ENC1A_PIN_SOURCE      GPIO_PinSource9

#define PLATFORM_ENC1B_PIN             GPIO_Pin_11
#define PLATFORM_ENC1B_PORT            GPIOE
#define PLATFORM_ENC1B_PIN_SOURCE      GPIO_PinSource11

#define PLATFORM_ENC1_GPIO_AF          GPIO_AF_TIM1

//Encoder 2
#define PLATFORM_ENC2A_PIN             GPIO_Pin_6
#define PLATFORM_ENC2A_PORT            GPIOC
#define PLATFORM_ENC2A_PIN_SOURCE      GPIO_PinSource6

#define PLATFORM_ENC2B_PIN             GPIO_Pin_7
#define PLATFORM_ENC2B_PORT            GPIOC
#define PLATFORM_ENC2B_PIN_SOURCE      GPIO_PinSource7

#define PLATFORM_ENC2_GPIO_AF          GPIO_AF_TIM3


/********
 * GPIO *
 *******/
#define PLATFORM_GPIO1_PORT GPIOD 
#define PLATFORM_GPIO1_PIN GPIO_Pin_14
#define PLATFORM_GPIO2_PORT GPIOD 
#define PLATFORM_GPIO2_PIN GPIO_Pin_15
#define PLATFORM_GPIO3_PORT GPIOG 
#define PLATFORM_GPIO3_PIN GPIO_Pin_2
#define PLATFORM_GPIO4_PORT GPIOG 
#define PLATFORM_GPIO4_PIN GPIO_Pin_3
#define PLATFORM_GPIO5_PORT GPIOG 
#define PLATFORM_GPIO5_PIN GPIO_Pin_4
#define PLATFORM_GPIO6_PORT GPIOG 
#define PLATFORM_GPIO6_PIN GPIO_Pin_5
#define PLATFORM_GPIO7_PORT GPIOG 
#define PLATFORM_GPIO7_PIN GPIO_Pin_6
#define PLATFORM_GPIO8_PORT GPIOG 
#define PLATFORM_GPIO8_PIN GPIO_Pin_7
#define PLATFORM_GPIO9_PORT GPIOG 
#define PLATFORM_GPIO9_PIN GPIO_Pin_8

#define GPIO1 0x01
#define GPIO2 0x02
#define GPIO3 0x04
#define GPIO4 0x08
#define GPIO5 0x10
#define GPIO6 0x20
#define GPIO7 0x40
#define GPIO8 0x80
#define GPIO9 0x100
#define GPIOALL GPIO1|GPIO2|GPIO3|GPIO4|GPIO5|GPIO6|GPIO7|GPIO8|GPIO9



/*********
 * Servo *
 ********/
// Servo
#define SERVO1 0x01
#define SERVO2 0x02
#define SERVO3 0x04
#define SERVO4 0x08
#define SERVOALL SERVO1|SERVO2|SERVO3|SERVO4

/* PWM */
#define Pin_PWM1 GPIO_Pin_6 
#define Pin_PWM2 GPIO_Pin_7
#define Pin_PWM3 GPIO_Pin_8
#define Pin_PWM4 GPIO_Pin_9
#define Pin_PWM_GPIOF Pin_PWM1 | Pin_PWM2 | Pin_PWM3 | Pin_PWM3

/* Timer */
#define TIMER10 0x01
#define TIMER11 0x02
#define TIMER13 0x03
#define TIMER14 0x04
#define TIMERALL TIMER10 | TIMER11 | TIMER13 | TIMER14

/* Timers */
#define SERVO1_TIM TIM10 
#define SERVO2_TIM TIM11
#define SERVO3_TIM TIM13
#define SERVO4_TIM TIM14

/* Channel */
#define SERVO1_CHAN TIM_Channel_1
#define SERVO2_CHAN TIM_Channel_1
#define SERVO3_CHAN TIM_Channel_1
#define SERVO4_CHAN TIM_Channel_1

void platform_hse_pll_init(void);
void platform_led_init(void);

void platform_pwm_init(uint8_t timer);
void platform_led_set(uint8_t led);
void platform_led_reset(uint8_t led);
void platform_led_toggle(uint8_t led);

void platform_gpio_init(uint16_t gpio, uint8_t type, uint8_t mode, uint8_t speed, uint8_t pull_up_down);

void platform_gpio_set(uint16_t gpio);
void platform_gpio_reset(uint16_t gpio);

uint8_t platform_gpio_get_value(uint16_t gpio);

int platform_usart_init(USART_TypeDef *USARTx, uint32_t baudrate);

void platform_motor1_init_io(void);
void platform_motor2_init_io(void);

void platform_encoder_init(void);

int platform_can_init(CAN_TypeDef* CANx);

#endif
