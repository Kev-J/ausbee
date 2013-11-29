#include <AUSBEE/init.h>

void ausbeeGPIOInitPortD()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
}

void ausbeeGPIOInitPortG()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
}
