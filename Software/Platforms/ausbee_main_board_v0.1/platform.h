/**
 *
 * \file platform.h
 * \brief Platform support definitions for AUSBEE mainboard V0.1
 * \author Kevin JOLY <joly.kevin25@gmail.com>
 *
 */
#ifndef PLATFORM_H
#define PLATFORM_H

#include <stm32f4xx_usart.h>

/* Clocks */
#define PLATFORM_PLLM 8
#define PLATFORM_PLLN 336
#define PLATFORM_PLLP 2
#define PLATFORM_PLLQ 7

/* LEDS */
#define PLATFORM_LED0 0x1
#define PLATFORM_LED1 0x2
#define PLATFORM_LED2 0x4
#define PLATFORM_LED3 0x8
#define PLATFORM_LED4 0x10
#define PLATFORM_LED5 0x20
#define PLATFORM_LED6 0x40
#define PLATFORM_LED7 0x80

void platform_init_HSE_PLL(void);
void platform_init_LED(void);

int platform_init_USART(USART_TypeDef *USARTx, uint32_t baudrate);

void platform_set_led(uint8_t led);
void platform_reset_led(uint8_t led);
void platform_toggle_led(uint8_t led);

#endif
