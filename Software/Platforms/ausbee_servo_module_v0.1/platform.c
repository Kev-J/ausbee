/**
 *
 * \file platform.c
 * \brief Platform support implementation for AUSBEE Servo Module V0.1
 * \author Kevin JOLY <joly.kevin25@gmail.com>
 *
 */

#include "platform.h"

void platform_initClock(void)
{
	// Configure and start the PLL
	RCC_DeInit();											// Reset clock configuration

	RCC_HSEConfig(RCC_HSE_ON);								// Enable external clock
	RCC_WaitForHSEStartUp();								// Wait for HSE startup
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);	// Configure PLL: Source HSE, Mult x16 (8*9=72MHz)
	RCC_PLLCmd(ENABLE);										// Enable PLL

	while (!(RCC->CR & RCC_CR_PLLRDY));

	// Configure the Systick
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	// Configure the AHB Clock
	RCC_HCLKConfig(RCC_SYSCLK_Div1);                       // AHB clock = CLK 72MHz
	// Configure the Low Speed APB Cloc
	RCC_PCLK1Config(RCC_HCLK_Div2);                        // APB1 clock = HCLK/2 = 36MHz
	// Configure the High Speed APB Cloc
	RCC_PCLK2Config(RCC_HCLK_Div1);                        // APB2 clock = HCLK = 72MHz
	// Configure the RTC Clock
	RCC_RTCCLKConfig(RCC_RTCCLKSource_HSE_Div128);         // RTC clock = HSE/128

	// Enables or disables the High Speed APB (APB2) peripheral clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);    // Enable APB2 clock on AFIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   // Enable APB2 clock on GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   // Enable APB2 clock on GPIOB
}

void platform_initPwm(void)
{
	// Variables
	TIM_TimeBaseInitTypeDef TimeBaseInit_PWM;              // Create a TimeBaseInitTypeDef for PWM Timer 50Hz
	TIM_OCInitTypeDef OCInitTypeDef_PWM;                   // Create a OCInitTypeDef for PWM
	GPIO_InitTypeDef InitTypeDef_PWM;                      // Create a InitTypeDef structure for GPIOA

	// Clock
	// Enables or disables the Low Speed APB (APB1) peripheral clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);    // Enable APB1 clock on TIM2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);    // Enable APB1 clock on TIM3

	TIM_TimeBaseStructInit(&TimeBaseInit_PWM);
	TimeBaseInit_PWM.TIM_Prescaler = 7199;                 // APB1*2/(Prescaler+1) = 10kHz -> Prescaler = 7199
	TimeBaseInit_PWM.TIM_CounterMode = TIM_CounterMode_Up; // Counter mode UP
	TimeBaseInit_PWM.TIM_Period = 200;                     // 10kHz/200 = 50Hz
	TimeBaseInit_PWM.TIM_ClockDivision = 0x0000;           // Is not used
	TimeBaseInit_PWM.TIM_RepetitionCounter = 0x0000;       // Is not used
	TIM_TimeBaseInit(TIM2, &TimeBaseInit_PWM);             // Initialize TIM2
	TIM_TimeBaseInit(TIM3, &TimeBaseInit_PWM);             // Initialize TIM3

	TIM_OCStructInit(&OCInitTypeDef_PWM);
	OCInitTypeDef_PWM.TIM_OCMode = TIM_OCMode_PWM2;        // Set PWM Mode
	OCInitTypeDef_PWM.TIM_Pulse = 10;                      // Set duty cycle to 5%
	TIM_OC1Init(TIM2, &OCInitTypeDef_PWM);                 // Initialize OSC1
	TIM_OC2Init(TIM2, &OCInitTypeDef_PWM);                 // Initialize OSC2
	TIM_OC3Init(TIM2, &OCInitTypeDef_PWM);                 // Initialize OSC3
	TIM_OC4Init(TIM2, &OCInitTypeDef_PWM);                 // Initialize OSC4

	TIM_OC1Init(TIM3, &OCInitTypeDef_PWM);                 // Initialize OSC1
	TIM_OC2Init(TIM3, &OCInitTypeDef_PWM);                 // Initialize OSC2
	TIM_OC3Init(TIM3, &OCInitTypeDef_PWM);                 // Initialize OSC3
	TIM_OC4Init(TIM3, &OCInitTypeDef_PWM);                 // Initialize OSC4

	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM3, ENABLE);

	// IO
	GPIO_StructInit(&InitTypeDef_PWM);
	InitTypeDef_PWM.GPIO_Pin = Pin_PWM_GPIOA;
	InitTypeDef_PWM.GPIO_Speed = GPIO_Speed_50MHz;         // Output maximum frequency at 50MHz
	InitTypeDef_PWM.GPIO_Mode = GPIO_Mode_AF_PP;           // Mode alternate function push-pull
	GPIO_Init(GPIOA, &InitTypeDef_PWM);                    // Initialize PWM Pin on GPIOA

	InitTypeDef_PWM.GPIO_Pin = Pin_PWM_GPIOB;
	GPIO_Init(GPIOB, &InitTypeDef_PWM);                    // Initialize PWM Pin on GPIOB

}

void platform_initLeds(void)
{
	// Variables
	GPIO_InitTypeDef InitTypeDef_Led;                      // Create a InitTypeDef structure for GPIOB

	// IO
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);   // Disable JTAG on PB4
	GPIO_ResetBits(GPIOB,GPIO_Pin_4);                      // Reset PB4

	InitTypeDef_Led.GPIO_Pin = LedAll;                     // Leds Pin
	InitTypeDef_Led.GPIO_Speed = GPIO_Speed_50MHz;         // Output maximum frequency at 50MHz
	InitTypeDef_Led.GPIO_Mode = GPIO_Mode_Out_PP;          // Mode output push-pull
	GPIO_Init(GPIOB, &InitTypeDef_Led);                    // Initialize Led Pin on GPIOB
}

void platform_initUsart(void)
{
	// Variables
	GPIO_InitTypeDef GPIO_InitStruct_USART1;
	USART_InitTypeDef USART_InitStructure;

	// Clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	// IO
	GPIO_StructInit(&GPIO_InitStruct_USART1);
	GPIO_InitStruct_USART1.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStruct_USART1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct_USART1.GPIO_Mode = GPIO_Mode_AF_PP;
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

void platform_SetupHardware(void)
{
	platform_initClock();
	platform_initPwm();
	platform_initLeds();
	platform_initUsart();
}

