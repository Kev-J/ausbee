

void platform_init_HSE_PLL(void)
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
