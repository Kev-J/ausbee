/**
 * @file	platform.c
 * @authors	vcesson <cesson.vincent@gmail.com>, Luc Prampolini <luc.prampolini@gmail.com>
 * @brief	Platform support implementation for AUSBEE Servo Module V0.1
 */

#include "platform.h"

// @brief	Init clock system
// @retval	None
void platform_initClock(void)
{
	// Configure and start the PLL
	RCC_DeInit();	                                      // Reset clock configuration
	RCC_HSEConfig(RCC_HSE_ON);			      // Enable external clock
	RCC_WaitForHSEStartUp();                            // Wait for HSE startup
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);// Configure PLL: Source HSE, Mult x16 (8*9=72MHz)
	RCC_PLLCmd(ENABLE);                                 // Enable PLL

	while (!(RCC->CR & RCC_CR_PLLRDY));                 // Configure the Systick
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);          // Configure the AHB Clock
	RCC_HCLKConfig(RCC_SYSCLK_Div1);                    // AHB clock = CLK 72MHz
	// Configure the Low Speed APB Cloc
	RCC_PCLK1Config(RCC_HCLK_Div2);                     // APB1 clock = HCLK/2 = 36MHz
	// Configure the High Speed APB Cloc
	RCC_PCLK2Config(RCC_HCLK_Div1);                     // APB2 clock = HCLK = 72MHz
	// Configure the RTC Clock
	RCC_RTCCLKConfig(RCC_RTCCLKSource_HSE_Div128);      // RTC clock = HSE/128

	// Enables or disables the High Speed APB (APB2) peripheral clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); // Enable APB2 clock on AFIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);// Enable APB2 clock on GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);// Enable APB2 clock on GPIOB
}

// @brief	Init clocks and GPIO for PWMs
// @retval	None
void platform_initPwm(uint8_t Timer)
{
	// Variables
	TIM_TimeBaseInitTypeDef TimeBaseInit_PWM; // Create a TimeBaseInitTypeDef for PWM Timer 50Hz
	TIM_OCInitTypeDef OCInitTypeDef_PWM;      // Create a OCInitTypeDef for PWM
	GPIO_InitTypeDef InitTypeDef_PWM;         // Create a InitTypeDef structure for GPIOA

	TIM_TimeBaseStructInit(&TimeBaseInit_PWM);
	TimeBaseInit_PWM.TIM_Prescaler = 1439;                 // APB1*2/50kHz-1
	TimeBaseInit_PWM.TIM_CounterMode = TIM_CounterMode_Up; // Counter mode UP
	TimeBaseInit_PWM.TIM_Period = 1000;                    // 50kHz/50Hz
	TimeBaseInit_PWM.TIM_ClockDivision = 0x0000;           // Is not used
	TimeBaseInit_PWM.TIM_RepetitionCounter = 0x0000;       // Is not used

	// Clock
	// Enables or disables the Low Speed APB (APB1) peripheral clock
	if( (Timer & TIMER2) == TIMER2 )
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); // Enable APB1 clock on TIM2
		TIM_TimeBaseInit(TIM2, &TimeBaseInit_PWM);          // Initialize TIM2
		TIM_Cmd(TIM2, ENABLE);
	}
	if( (Timer & TIMER3) == TIMER3 )
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); // Enable APB1 clock on TIM3
		TIM_TimeBaseInit(TIM3, &TimeBaseInit_PWM);          // Initialize TIM3
		TIM_Cmd(TIM3, ENABLE);
	}

	// IO
	GPIO_StructInit(&InitTypeDef_PWM);
	InitTypeDef_PWM.GPIO_Pin = Pin_PWM_GPIOA;
	InitTypeDef_PWM.GPIO_Speed = GPIO_Speed_50MHz;         // Output maximum frequency at 50MHz
	InitTypeDef_PWM.GPIO_Mode = GPIO_Mode_AF_PP;           // Mode alternate function push-pull
	GPIO_Init(GPIOA, &InitTypeDef_PWM);                    // Initialize PWM Pin on GPIOA

	InitTypeDef_PWM.GPIO_Pin = Pin_PWM_GPIOB;
	GPIO_Init(GPIOB, &InitTypeDef_PWM);                    // Initialize PWM Pin on GPIOB 
}

// @brief	Init IO for leds
// @retval	None
void platform_initLeds(void)
{
	// Remap
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);   // Disable JTAG on PB4
	GPIO_ResetBits(GPIOB,GPIO_Pin_4);                      // Reset PB4
	// Variables
	GPIO_InitTypeDef InitTypeDef_Led;                      // Create a InitTypeDef structure for GPIOB
	GPIO_StructInit(&InitTypeDef_Led);
	// IO
	InitTypeDef_Led.GPIO_Pin = LedAll;                     // Leds Pin
	InitTypeDef_Led.GPIO_Speed = GPIO_Speed_50MHz;         // Output maximum frequency at 50MHz
	InitTypeDef_Led.GPIO_Mode = GPIO_Mode_Out_PP;          // Mode output push-pull
	GPIO_Init(GPIOB, &InitTypeDef_Led);                    // Initialize Led Pin on GPIOB
}

// @brief	Init clocks and GPIO for UART1, and configure UART1 parameters
// @retval	None
void platform_initUsart(void)
{
	// Variables
	GPIO_InitTypeDef GPIO_InitStruct_USART1;
	USART_InitTypeDef USART_InitStructure;

	// Clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	// IO
	GPIO_StructInit(&GPIO_InitStruct_USART1);
	GPIO_InitStruct_USART1.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct_USART1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct_USART1.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct_USART1);

	GPIO_InitStruct_USART1.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct_USART1.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStruct_USART1);

	// Conf
	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &USART_InitStructure);

	// Enable
	USART_Cmd(USART1, ENABLE);
}

// @brief	Init clocks and GPIO for CANx
// @param	CAN to initialize: CAN1 or CAN2
// @retval	-1 if fail, else 0
int platform_initCAN(CAN_TypeDef* CANx)
{
	CAN_InitTypeDef CAN_InitTypeDef_1;
	GPIO_InitTypeDef init_GPIO_CAN;

	GPIO_StructInit(&init_GPIO_CAN);

	if(CANx==CAN1){
		//enable the clock to the module
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

		//init the GPIO
		init_GPIO_CAN.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
		init_GPIO_CAN.GPIO_Mode = GPIO_Mode_AF_PP;
		init_GPIO_CAN.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&init_GPIO_CAN);

		// Configure CAN1
		CAN_StructInit(&CAN_InitTypeDef_1);
		CAN_InitTypeDef_1.CAN_Prescaler = 72;
		CAN_InitTypeDef_1.CAN_Mode = CAN_Mode_Normal;
		CAN_InitTypeDef_1.CAN_AWUM = ENABLE;
		CAN_InitTypeDef_1.CAN_TXFP = ENABLE;
		if(CAN_Init(CAN1, &CAN_InitTypeDef_1) == CAN_InitStatus_Failed) 
			return -1;
		return 0;
	} else {
		return -1;
	}
}

// @brief	Call all initialization functions
// @retval	None
void platform_SetupHardware(void)
{
	platform_initClock();
	platform_initPwm(TIMER_ALL);
	platform_initLeds();
	platform_initUsart();
	platform_initCAN(CAN1);
}

// @brief	Convert an unsigned value into ascii hexadecimal equivalent and send it via USART
// @param	val: The value to print
// @retval	None
void platform_printHexa(uint32_t val) {
	uint32_t mask = 0x0F << 28;
	int test_val = 0;
	int i = 0;

	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	USART_SendData(USART1, '0');
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	USART_SendData(USART1, 'x');

	for(i = 7; i >= 0; i--) {
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		if((test_val = ((val & mask) >> i*4)) >= 10)
			USART_SendData(USART1, (test_val + 55));
		else
			USART_SendData(USART1, (test_val + 48));
		mask = mask >> 4;
	}
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	USART_SendData(USART1, '\n');
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	USART_SendData(USART1, '\r');
}

// @brief	Sent via USART the string contained in char *string
// @param	string: String to print
// @param	nb: Number of characters in the string
// @retval	None
void platform_printString(char *string, uint32_t nb) {
	uint32_t i = 0;
	for(i = 0; i < nb; i++) {
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		USART_SendData(USART1, string[i]);
	}
}

