/**
 *
 * \file platform.c
 * \brief Platform support implementation for AUSBEE mainboard V0.1
 * \author Kevin JOLY <joly.kevin25@gmail.com>
 *
 */
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>

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


int platform_CAN_init(CAN_TypeDef* CANx)
{
    GPIO_InitTypeDef init_GPIO_CAN;

    GPIO_StructInit(&init_GPIO_CAN);

    if(CANx==CAN1){
      //enable the clock to the module
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

      //configure alternate function for the GPIO
      GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_CAN1); //CAN_RX
      GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_CAN1); //CAN_TX

      //init the GPIO
      init_GPIO_CAN.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
      init_GPIO_CAN.GPIO_Mode = GPIO_Mode_AF;
      init_GPIO_CAN.GPIO_Speed = GPIO_High_Speed;
      GPIO_init(GPIOA,&init_GPIO_CAN);
    } else {
      return -1;
    }
    return 0;
}
