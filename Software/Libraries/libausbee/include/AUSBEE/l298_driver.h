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
 * Copyright 2013-2014 (C) EIRBOT
 *
 * Authors :    Kevin JOLY <joly.kevin25@gmail.com>
 *
 **********************************************************************/
#ifndef LIBAUSBEE_L298_DRIVER_H
#define LIBAUSBEE_L298_DRIVER_H

#include <stm32f4xx_tim.h>

enum AUSBEE_L298_DRIVER_ERROR {ENO_ERROR = 0x0, EINVALID_FREQUENCY = 0x1, EINVALID_DUTY = 0x2, EINVALID_TIMER_CHANNEL = 0x4};

struct ausbee_l298_chip{
	uint8_t timer_channel;
	uint16_t gpio_enable_pin;
	uint16_t gpio_dir_pin;
	uint32_t pwm_frequency;
	GPIO_TypeDef* gpio_dir_port;
	GPIO_TypeDef* gpio_enable_port;
	TIM_TypeDef *TIMx;
};

enum AUSBEE_L298_DRIVER_ERROR ausbee_l298_init_chip(struct ausbee_l298_chip chip);
void ausbee_l298_enable_chip(struct ausbee_l298_chip chip, uint8_t enable);
void ausbee_l298_invert_output(struct ausbee_l298_chip chip, uint8_t enable);
void ausbee_l298_set_duty_cycle(struct ausbee_l298_chip chip, uint8_t duty_cycle);

#endif
