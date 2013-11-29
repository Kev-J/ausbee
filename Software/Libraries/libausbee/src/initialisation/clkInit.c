#include <AUSBEE/init.h>

void ausbeeInitHSEPLL(uint32_t PLLM, uint32_t PLLN, uint32_t PLLP, uint32_t PLLQ)
{
	RCC_DeInit();

	RCC_HSEConfig(RCC_HSE_ON);
	RCC_WaitForHSEStartUp();

	RCC_PLLConfig(RCC_PLLSource_HSE, PLLM, PLLN, PLLP, PLLQ);

	RCC_PLLCmd(ENABLE);

	while (!(RCC->CR & RCC_CR_PLLRDY))
		;

	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
}
