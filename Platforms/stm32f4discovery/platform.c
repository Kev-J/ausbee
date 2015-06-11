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

// @file	platform.c
// @brief	Platform support implementation for STM32F4Discovery
// @author	Vincent Cesson <cesson.vincent@gmail.com>

#include "platform.h"

// Initialize PLLs and clock system
void platform_init_HSE_PLL(void)
{
    RCC_DeInit();

    RCC_HSEConfig(RCC_HSE_ON);
    RCC_WaitForHSEStartUp();

    RCC_PLLConfig(RCC_PLLSource_HSE, PLATFORM_PLLM, PLATFORM_PLLN, PLATFORM_PLLP, PLATFORM_PLLQ);

    RCC_PLLCmd(ENABLE);

    while (!(RCC->CR & RCC_CR_PLLRDY))
	;

    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
}

// Configure GPIO for LEDs
void platform_init_LEDs(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	// GPIOD Periph clock enable
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	// Configure PD12, PD13, PD14 and PD15 (LEDs) in output pushpull mode
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

// Configures Timer 4 as PWM to control LEDs
// Note: After this initialization, LEDs cannot be controlled with regular GPIO
// functions. Use platform_set_led_pwm(led, ratio) to control them. 
void platform_init_PWM_LEDs(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	// --------------------------- System Clocks Configuration -----------------
	// TIM4 clock enable 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	// GPIOD clock enable 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	//-------------------------- GPIO Configuration ----------------------------
	// GPIOD Configuration: Pins 12, 13, 14 and 15 in output push-pull 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	// Connect TIM4 pins to AF2 
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4); 
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4); 

	// Time base configuration 
	TIM_TimeBaseStructure.TIM_Prescaler = 167;	// 168MHz/168 = 1MHz
	TIM_TimeBaseStructure.TIM_Period = 10000; // Period = 10000/1MHz = 10ms
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	// Enable TIM4 Preload register on ARR 
	TIM_ARRPreloadConfig(TIM4, ENABLE);

	// TIM PWM1 Mode configuration: Channel 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 5000; // Ratio: 5000/10000 = 50%

	// Output Compare PWM1 Mode configuration: Channel1 
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_CCxCmd(TIM4, TIM_Channel_1, DISABLE);

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

	// Output Compare PWM1 Mode configuration: Channel2 
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_CCxCmd(TIM4, TIM_Channel_2, DISABLE);

	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

	// Output Compare PWM1 Mode configuration: Channel3 
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_CCxCmd(TIM4, TIM_Channel_3, DISABLE);

	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

	// Output Compare PWM1 Mode configuration: Channel4 
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	TIM_CCxCmd(TIM4, TIM_Channel_4, DISABLE);

	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

	// TIM4 enable counter 
	TIM_Cmd(TIM4, ENABLE);
}

// Configure GPIO for the Push Button
void platform_init_PB(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	// GPIOA Periph clock enable
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	// Configure PA1 (push button) in input mode
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

// Initialize Accelerometer
// Communication with MEMS is done with SPI interface
void platform_init_MEMS(void)
{
	LIS302DL_InitTypeDef  LIS302DL_InitStruct;
	LIS302DL_FilterConfigTypeDef LIS302DL_FilterStruct;

	/* MEMS configuration */
	LIS302DL_InitStruct.Power_Mode = LIS302DL_LOWPOWERMODE_ACTIVE;
	LIS302DL_InitStruct.Output_DataRate = LIS302DL_DATARATE_100;
	LIS302DL_InitStruct.Axes_Enable = LIS302DL_XYZ_ENABLE;
	LIS302DL_InitStruct.Full_Scale = LIS302DL_FULLSCALE_2_3;
	LIS302DL_InitStruct.Self_Test = LIS302DL_SELFTEST_NORMAL;
	LIS302DL_Init(&LIS302DL_InitStruct);

	/* MEMS High Pass Filter configuration */
	LIS302DL_FilterStruct.HighPassFilter_Data_Selection = LIS302DL_FILTEREDDATASELECTION_OUTPUTREGISTER;
	LIS302DL_FilterStruct.HighPassFilter_CutOff_Frequency = LIS302DL_HIGHPASSFILTER_LEVEL_1;
	LIS302DL_FilterStruct.HighPassFilter_Interrupt = LIS302DL_HIGHPASSFILTERINTERRUPT_1_2;
	LIS302DL_FilterConfig(&LIS302DL_FilterStruct);
}

// Turn on LEDs
// leds can be a set of PLATFORM_LED_x
// where x = GREEN, ORANGE, RED or BLUE
void platform_set_led(uint8_t led)
{
	if(led & PLATFORM_LED_GREEN)
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
	if(led & PLATFORM_LED_ORANGE)
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
	if(led & PLATFORM_LED_RED)
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
	if(led & PLATFORM_LED_BLUE)
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
}

// Turn off LEDs
// leds can be a set of PLATFORM_LED_x
// where x = GREEN, ORANGE, RED or BLUE
void platform_reset_led(uint8_t led)
{
	if(led & PLATFORM_LED_GREEN)
		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	if(led & PLATFORM_LED_ORANGE)
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
	if(led & PLATFORM_LED_RED)
		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
	if(led & PLATFORM_LED_BLUE)
		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
}

// Toggle LEDs
// leds can be a set of PLATFORM_LED_x
// where x = GREEN, ORANGE, RED or BLUE
void platform_toggle_led(uint8_t led)
{
	if(led & PLATFORM_LED_GREEN)
		GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
	if(led & PLATFORM_LED_ORANGE)
		GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	if(led & PLATFORM_LED_RED)
		GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
	if(led & PLATFORM_LED_BLUE)
		GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
}
