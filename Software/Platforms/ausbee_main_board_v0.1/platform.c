/**
 *
 * \file platform.c
 * \brief Platform support implementation for AUSBEE mainboard V0.1
 * \author Kevin JOLY <joly.kevin25@gmail.com>
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

void platform_initPWM(uint8_t Timer)
{
	TIM_TimeBaseInitTypeDef TimeBaseInit_PWM;
	GPIO_InitTypeDef InitTypeDef_PWM;

	TIM_TimeBaseStructInit(&TimeBaseInit_PWM);
	
	TimeBaseInit_PWM.TIM_Prescaler=3300; //168MHz/50Khz

	TimeBaseInit_PWM.TIM_CounterMode = TIM_CounterMode_Up; //counter mode up
	TimeBaseInit_PWM.TIM_Period = 1000; //50Khz/50Hz

	TimeBaseInit_PWM.TIM_ClockDivision = 0x0000; //is not used

	TimeBaseInit_PWM.TIM_RepetitionCounter = 0x0000; //is not used	 


	if( (Timer & TIMER10) == TIMER10 )
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE); // Enable APB2 clock on TIM10
		TIM_TimeBaseInit(TIM10, &TimeBaseInit_PWM);          // Initialize TIM10
		TIM_Cmd(TIM10, ENABLE);
	}
	
	if( (Timer & TIMER11) == TIMER11 )
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE); // Enable APB2 clock on TIM11
		TIM_TimeBaseInit(TIM11, &TimeBaseInit_PWM);          // Initialize TIM11
		TIM_Cmd(TIM11, ENABLE);
	}
	
	if( (Timer & TIMER13) == TIMER13 )
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE); // Enable APB1 clock on TIM13
		TIM_TimeBaseInit(TIM13, &TimeBaseInit_PWM);          // Initialize TIM13
		TIM_Cmd(TIM13, ENABLE);
	}

	if( (Timer & TIMER14) == TIMER14 )
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE); // Enable APB1 clock on TIM14
		TIM_TimeBaseInit(TIM14, &TimeBaseInit_PWM);          // Initialize TIM14
		TIM_Cmd(TIM14, ENABLE);
	}

	// IO
	GPIO_StructInit(&InitTypeDef_PWM);
	InitTypeDef_PWM.GPIO_Pin = Pin_PWM_GPIOF;
	InitTypeDef_PWM.GPIO_Speed = GPIO_Speed_50MHz;         // Output maximum frequency at 50MHz
	InitTypeDef_PWM.GPIO_Mode = GPIO_Mode_AF;           // Mode alternate function push-pull
	GPIO_Init(GPIOF, &InitTypeDef_PWM);                    // Initialize PWM Pin on GPIOF
}


int platform_init_USART(USART_TypeDef *USARTx, uint32_t baudrate)
{
    GPIO_InitTypeDef init_GPIO_USART;
    USART_InitTypeDef init_USART;

    USART_StructInit(&init_USART);
    GPIO_StructInit(&init_GPIO_USART);

    if (USARTx == USART3) {
        /* Enable clock on GPIOB and USART3 devices */
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

        /* Select AF mode USART3 for pin B10 and B11 */
        init_GPIO_USART.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
        init_GPIO_USART.GPIO_Speed = GPIO_Speed_50MHz;
        init_GPIO_USART.GPIO_Mode = GPIO_Mode_AF;
        GPIO_Init(GPIOB, &init_GPIO_USART);

        GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

        /* Init USART 3 */
        init_USART.USART_BaudRate = baudrate;
        init_USART.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
        USART_Init(USARTx, &init_USART);

        USART_Cmd(USARTx, ENABLE);
    } else {
        return -1;
    }

    return 0;
}

void platform_init_LED(void)
{
    GPIO_InitTypeDef GPIOInitStruct_G;
    GPIO_InitTypeDef GPIOInitStruct_D;

    GPIO_StructInit(&GPIOInitStruct_G);
    GPIO_StructInit(&GPIOInitStruct_D);

    /* Clock configuration for GPIOG and GPIOD */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

    /* Init LED on GPIOD */
    GPIOInitStruct_D.GPIO_Pin= GPIO_Pin_6 | GPIO_Pin_7;
    GPIOInitStruct_D.GPIO_Speed = GPIO_Speed_50MHz;
    GPIOInitStruct_D.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(GPIOD, &GPIOInitStruct_D);

    /* Init LED on GPIOG */
    GPIOInitStruct_G.GPIO_Pin= GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
    GPIOInitStruct_G.GPIO_Speed = GPIO_Speed_50MHz;
    GPIOInitStruct_G.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(GPIOG, &GPIOInitStruct_G);
}

void platform_set_led(uint8_t led)
{
    if (led & PLATFORM_LED0)
        GPIO_SetBits(GPIOD, GPIO_Pin_6);
    if (led & PLATFORM_LED1)
        GPIO_SetBits(GPIOD, GPIO_Pin_7);
    if (led & PLATFORM_LED2)
        GPIO_SetBits(GPIOG, GPIO_Pin_9);
    if (led & PLATFORM_LED3)
        GPIO_SetBits(GPIOG, GPIO_Pin_10);
    if (led & PLATFORM_LED4)
        GPIO_SetBits(GPIOG, GPIO_Pin_11);
    if (led & PLATFORM_LED5)
        GPIO_SetBits(GPIOG, GPIO_Pin_12);
    if (led & PLATFORM_LED6)
        GPIO_SetBits(GPIOG, GPIO_Pin_13);
    if (led & PLATFORM_LED7)
        GPIO_SetBits(GPIOG, GPIO_Pin_14);
}

void platform_reset_led(uint8_t led)
{
    if (led & PLATFORM_LED0)
        GPIO_ResetBits(GPIOD, GPIO_Pin_6);
    if (led & PLATFORM_LED1)
        GPIO_ResetBits(GPIOD, GPIO_Pin_7);
    if (led & PLATFORM_LED2)
        GPIO_ResetBits(GPIOG, GPIO_Pin_9);
    if (led & PLATFORM_LED3)
        GPIO_ResetBits(GPIOG, GPIO_Pin_10);
    if (led & PLATFORM_LED4)
        GPIO_ResetBits(GPIOG, GPIO_Pin_11);
    if (led & PLATFORM_LED5)
        GPIO_ResetBits(GPIOG, GPIO_Pin_12);
    if (led & PLATFORM_LED6)
        GPIO_ResetBits(GPIOG, GPIO_Pin_13);
    if (led & PLATFORM_LED7)
        GPIO_ResetBits(GPIOG, GPIO_Pin_14);
}

void platform_toggle_led(uint8_t led)
{
    if (led & PLATFORM_LED0)
        GPIO_ToggleBits(GPIOD, GPIO_Pin_6);
    if (led & PLATFORM_LED1)
        GPIO_ToggleBits(GPIOD, GPIO_Pin_7);
    if (led & PLATFORM_LED2)
        GPIO_ToggleBits(GPIOG, GPIO_Pin_9);
    if (led & PLATFORM_LED3)
        GPIO_ToggleBits(GPIOG, GPIO_Pin_10);
    if (led & PLATFORM_LED4)
        GPIO_ToggleBits(GPIOG, GPIO_Pin_11);
    if (led & PLATFORM_LED5)
        GPIO_ToggleBits(GPIOG, GPIO_Pin_12);
    if (led & PLATFORM_LED6)
        GPIO_ToggleBits(GPIOG, GPIO_Pin_13);
    if (led & PLATFORM_LED7)
        GPIO_ToggleBits(GPIOG, GPIO_Pin_14);
}

void platform_init_io_motor1(void)
{
    	GPIO_InitTypeDef GPIO_InitTypeDef_E;

	/* Set the clock on TIM9 */
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);

	/* Init DIR signal for L298 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_StructInit(&GPIO_InitTypeDef_E);
	GPIO_InitTypeDef_E.GPIO_Pin = PLATFORM_DIR_MOTOR1_PIN;
	GPIO_InitTypeDef_E.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitTypeDef_E.GPIO_Speed = GPIO_High_Speed;

	GPIO_Init(PLATFORM_DIR_MOTOR1_PORT, &GPIO_InitTypeDef_E);

	/* Init ENABLE for L298 */
	GPIO_StructInit(&GPIO_InitTypeDef_E);
	GPIO_InitTypeDef_E.GPIO_Pin = PLATFORM_ENABLE_MOTOR1_PIN;
	GPIO_InitTypeDef_E.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitTypeDef_E.GPIO_Speed = GPIO_High_Speed;

	GPIO_Init(PLATFORM_ENABLE_MOTOR1_PORT, &GPIO_InitTypeDef_E);

	/* Init AF output */
	GPIO_StructInit(&GPIO_InitTypeDef_E);
	GPIO_InitTypeDef_E.GPIO_Pin = PLATFORM_PWM_MOTOR1_PIN;
	GPIO_InitTypeDef_E.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitTypeDef_E.GPIO_Speed = GPIO_High_Speed;

	GPIO_Init(PLATFORM_PWM_MOTOR1_PORT, &GPIO_InitTypeDef_E);

	GPIO_PinAFConfig(PLATFORM_PWM_MOTOR1_PORT, PLATFORM_PWM_MOTOR1_PIN_SOURCE, PLATFORM_PWM_MOTOR1_GPIO_AF);
}

void platform_init_io_motor2(void)
{
    	GPIO_InitTypeDef GPIO_InitTypeDef_E;

	/* Set the clock on TIM9 */
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);

	/* Set clock on GPIOE */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	/* Init DIR signal for L298 */
	GPIO_StructInit(&GPIO_InitTypeDef_E);
	GPIO_InitTypeDef_E.GPIO_Pin = PLATFORM_DIR_MOTOR2_PIN;
	GPIO_InitTypeDef_E.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitTypeDef_E.GPIO_Speed = GPIO_High_Speed;

	GPIO_Init(PLATFORM_DIR_MOTOR2_PORT, &GPIO_InitTypeDef_E);

	/* Init ENABLE signal for l298 */
	GPIO_StructInit(&GPIO_InitTypeDef_E);
	GPIO_InitTypeDef_E.GPIO_Pin = PLATFORM_ENABLE_MOTOR2_PIN;
	GPIO_InitTypeDef_E.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitTypeDef_E.GPIO_Speed = GPIO_High_Speed;

	GPIO_Init(PLATFORM_ENABLE_MOTOR2_PORT, &GPIO_InitTypeDef_E);

	/* Init AF output */
	GPIO_StructInit(&GPIO_InitTypeDef_E);
	GPIO_InitTypeDef_E.GPIO_Pin = PLATFORM_PWM_MOTOR2_PIN;
	GPIO_InitTypeDef_E.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitTypeDef_E.GPIO_Speed = GPIO_High_Speed;

	GPIO_Init(PLATFORM_PWM_MOTOR2_PORT, &GPIO_InitTypeDef_E);

	GPIO_PinAFConfig(GPIOE, PLATFORM_PWM_MOTOR2_PIN_SOURCE, PLATFORM_PWM_MOTOR2_GPIO_AF);
}

void platform_encoder2_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = PLATFORM_ENCODER2_A_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;

	GPIO_Init(PLATFORM_ENCODER2_PORT, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOC, PLATFORM_ENCODER2_PIN_SOURCE, PLATFORM_ENCODER2_GPIO_AF);

	GPIO_StructInit(&GPIO_InitStructure);
}

int platform_CAN_init(CAN_TypeDef* CANx)
{
    GPIO_InitTypeDef init_GPIO_CAN;

    GPIO_StructInit(&init_GPIO_CAN);

    if(CANx==CAN1){

      //enable the clock to the module
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

      //configure alternate function for the GPIO
      GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_CAN1); //CAN_RX
      GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_CAN1); //CAN_TX

      //init the GPIO
      init_GPIO_CAN.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
      init_GPIO_CAN.GPIO_Mode = GPIO_Mode_AF;
      init_GPIO_CAN.GPIO_Speed = GPIO_High_Speed;
      GPIO_Init(GPIOA,&init_GPIO_CAN);
    } else {
      return -1;
    }

    return 0;
}
