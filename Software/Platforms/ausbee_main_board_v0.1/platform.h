#ifndef PLATFORM_H
#define PLATFORM_H

#include <AUSBEE/led.h>

/* Clocks */
#define PLATFORM_PLLM 8
#define PLATFORM_PLLN 336
#define PLATFORM_PLLP 2
#define PLATFORM_PLLQ 7

/* Leds */
#define PLATFORM_LED_COUNT 8

struct ausbeeLed leds[PLATFORM_LED_COUNT] =	{{GPIOD,GPIO_Pin_6},
						{GPIOD,GPIO_Pin_7},
						{GPIOG, GPIO_Pin_9},
						{GPIOG, GPIO_Pin_10},
						{GPIOG, GPIO_Pin_11},
						{GPIOG, GPIO_Pin_12},
						{GPIOG, GPIO_Pin_13},
						{GPIOG, GPIO_Pin_14}};
struct ausbeeLeds platformLeds = {leds,
		PLATFORM_LED_COUNT};

#endif
