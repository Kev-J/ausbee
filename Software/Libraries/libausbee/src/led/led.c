#include <stm32f4xx_gpio.h>
#include <AUSBEE/led.h>

void ausbeeInitLed(struct ausbeeLed led)
{
	GPIO_InitTypeDef InitTypeDef_X;
	InitTypeDef_X.GPIO_Pin= led.pin;
	InitTypeDef_X.GPIO_Speed = GPIO_Speed_50MHz;
	InitTypeDef_X.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(led.port, &InitTypeDef_X);
}

void ausbeeInitLeds(struct ausbeeLeds leds)
{
	uint32_t ledCount = leds.count;

	do {
		ausbeeInitLed(leds.leds[--ledCount]);
	} while (ledCount);
}

void ausbeeSetLed(struct ausbeeLeds leds, uint32_t ledNum)
{
	if (ledNum > leds.count)
		return;
	
	GPIO_SetBits(leds.leds[ledNum].port, leds.leds[ledNum].pin);
}

void ausbeeResetLed(struct ausbeeLeds leds, uint32_t ledNum)
{
	if (ledNum > leds.count)
		return;
	
	GPIO_ResetBits(leds.leds[ledNum].port, leds.leds[ledNum].pin);
}

void ausbeeWriteBytesLed(struct ausbeeLeds leds, uint32_t bytes)
{
	uint32_t mask = 0x1;
	uint32_t i;

	for (i = 0 ; i < leds.count ; i++) {
		if (bytes & mask) {
			ausbeeSetLed(leds, i);
		} else {
			ausbeeResetLed(leds, i);
		}
		mask = mask << 1;
	}
}
