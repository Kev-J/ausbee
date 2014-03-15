/**********************************************************************
 * This file is part of LIBAUSBEE.
 * 
 * LIBAUSBEE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * LIBAUSBEE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with LIBAUSBEE.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2013 (C) EIRBOT
 *
 * Authors :    Kevin JOLY <joly.kevin25@gmail.com>
 *
 **********************************************************************/
#include "AUSBEE/l298_driver.h"
#include "AUSBEE/device.h"

#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>

enum AUSBEE_L298_DRIVER_ERROR ausbee_l298_init_chip(ausbee_l298_chip chip)
{
	uint32_t pclk, period;
	TIM_OCInitTypeDef TIM_OCInitTypeDef_TIMx;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeDef_TIMx;
	RCC_ClocksTypeDef RCC_Clocks;

#ifdef STM32F4XX

	TIM_DeInit(chip.TIMx);

	TIM_TimeBaseStructInit(&TIM_TimeBaseInitTypeDef_TIMx);
	RCC_GetClocksFreq(&RCC_Clocks);

	/* Get PCLKx according to the timer */
	if (	(chip.TIMx == TIM2) || (chip.TIMx == TIM3) ||
		(chip.TIMx == TIM4) || (chip.TIMx == TIM5) ||
		(chip.TIMx == TIM6) || (chip.TIMx == TIM7) ||
		(chip.TIMx == TIM12) || (chip.TIMx == TIM13) ||
		(chip.TIMx == TIM14)) {
		pclk = RCC_Clocks.PCLK1_Frequency;
	} else {
		pclk = RCC_Clocks.PCLK2_Frequency;
	}

	/* Compute period */
	period = pclk / chip.pwm_frequency;

	if (period < 100) {
		return EINVALID_FREQUENCY;
	}

	/* Init timer */
	TIM_TimeBaseInitTypeDef_TIMx.TIM_Prescaler = 0;
	TIM_TimeBaseInitTypeDef_TIMx.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitTypeDef_TIMx.TIM_Period = period;

	TIM_TimeBaseInit(chip.TIMx, &TIM_TimeBaseInitTypeDef_TIMx);

	/* Init output timer */
	TIM_OCStructInit(&TIM_OCInitTypeDef_TIMx);
	TIM_OCInitTypeDef_TIMx.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitTypeDef_TIMx.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitTypeDef_TIMx.TIM_Pulse = 0;

	/* Assign the output on the right channel */
	if (chip.timer_channel == 1) {
		TIM_OC1Init(chip.TIMx, &TIM_OCInitTypeDef_TIMx);
	} else if (chip.timer_channel == 2) {
		TIM_OC2Init(chip.TIMx, &TIM_OCInitTypeDef_TIMx);
	} else if (chip.timer_channel == 3) {
		TIM_OC3Init(chip.TIMx, &TIM_OCInitTypeDef_TIMx);
	} else if (chip.timer_channel == 4) {
		TIM_OC4Init(chip.TIMx, &TIM_OCInitTypeDef_TIMx);
	} else {
		return EINVALID_TIMER_CHANNEL;
	}

	/* Start timer */
	TIM_Cmd(chip.TIMx, ENABLE);

	ausbee_l298_enable_chip(chip, 0);
	ausbee_l298_invert_output(chip, 0);

	return ENO_ERROR;
#else
#error Function not supported for this device /* TODO */
#endif 
}

void ausbee_l298_enable_chip(ausbee_l298_chip chip, uint8_t enable)
{
	if (enable) {
		GPIO_SetBits(chip.gpio_enable_port, chip.gpio_enable_pin);
	} else {
		GPIO_ResetBits(chip.gpio_enable_port, chip.gpio_enable_pin);
	}
}

void ausbee_l298_invert_output(ausbee_l298_chip chip, uint8_t enable)
{
	uint16_t polarity;
	if (enable) {
		GPIO_SetBits(chip.gpio_dir_port, chip.gpio_dir_pin);
		polarity = TIM_OCPolarity_Low;
	} else {
		GPIO_ResetBits(chip.gpio_dir_port, chip.gpio_dir_pin);
		polarity = TIM_OCPolarity_High;
	}

	if (chip.timer_channel == 1) {
		TIM_OC1PolarityConfig(chip.TIMx, polarity);
	} else if (chip.timer_channel == 2) {
		TIM_OC2PolarityConfig(chip.TIMx, polarity);
	} else if (chip.timer_channel == 3) {
		TIM_OC3PolarityConfig(chip.TIMx, polarity);
	} else if (chip.timer_channel == 4) {
		TIM_OC4PolarityConfig(chip.TIMx, polarity);
	}
}

void ausbee_l298_set_duty_cycle(ausbee_l298_chip chip, uint8_t duty_cycle)
{
	uint32_t duty;

	/* Compute duty cycle */
	duty_cycle = duty_cycle > 100 ? 100 : duty_cycle;

	duty = ((uint32_t)(duty_cycle) * chip.TIMx->ARR)/100;

	if (chip.timer_channel == 1) {
		TIM_SetCompare1(chip.TIMx, duty);
	} else if (chip.timer_channel == 2) {
		TIM_SetCompare2(chip.TIMx, duty);
	} else if (chip.timer_channel == 3) {
		TIM_SetCompare3(chip.TIMx, duty);
	} else if (chip.timer_channel == 4) {
		TIM_SetCompare4(chip.TIMx, duty);
	}
}
