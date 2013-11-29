#ifndef AUSBEE_LED_H
#define AUSBEE_LED_H

#include <stm32f4xx_gpio.h>

struct ausbeeLed{
	GPIO_TypeDef *port;
	uint32_t pin;
};

struct ausbeeLeds{
	struct ausbeeLed *leds;
	uint32_t count;
};

void ausbeeInitLed(struct ausbeeLed led);
void ausbeeInitLeds(struct ausbeeLeds leds);
void ausbeeSetLed(struct ausbeeLeds leds, uint32_t ledNum);
void ausbeeResetLed(struct ausbeeLeds leds, uint32_t ledNum);
void ausbeeWriteBytesLed(struct ausbeeLeds leds, uint32_t bytes);

#endif
