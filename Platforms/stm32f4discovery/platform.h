/*
 * This file is part of AUSBEE.
 *
 * Copyright (C) 2015 AUSBEE Developers <ausbee@googlegroups.com>
 *
 * AUSBEE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * AUSBEE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with AUSBEE.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 *
 * \file platform.h
 * \brief Platform support definitions for STM32F4Discovery
 * \author Cesson Vincent <cesson.vincent@gmail.com>
 *
 */
#ifndef PLATFORM_H
#define PLATFORM_H

#include "stm32f4_discovery_lis302dl.h"
#include <stm32f4xx_tim.h>
#include <stm32f4xx_usart.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_can.h>
#include <stm32f4xx_spi.h>
#include <stm32f4xx_exti.h>
#include <stm32f4xx_syscfg.h>
#include <misc.h>

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
#define PLATFORM_LED_GREEN		0x1
#define PLATFORM_LED_ORANGE		0x2
#define PLATFORM_LED_RED		0x4
#define PLATFORM_LED_BLUE		0x8

void platform_init_HSE_PLL(void);
void platform_init_LEDs(void);
void platform_init_PWM_LEDs(void);
void platform_init_PB(void);
void platform_init_MEMS(void);

void platform_set_led(uint8_t led);
void platform_reset_led(uint8_t led);
void platform_toggle_led(uint8_t led);

#endif
