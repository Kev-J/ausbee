/**
 *
 * \file platform.c
 * \brief Platform support implementation for STM32F4Discovery
 * \author Vincent Cesson <cesson.vincent@gmail.com>
 *
 */

#include "platform.h"

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

void platform_init_LED(void)
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
