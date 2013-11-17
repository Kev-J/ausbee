/********************************************************/
/* Startup code for STM32 Low density devices 		*/
/*							*/
/* Author: Kevin JOLY joly.kevin25@gmail.com		*/
/* Inspired by sources from http://www.embedds.com	*/
/*							*/
/********************************************************/

#include <stm32f10x.h>

extern unsigned long _data_flash;
extern unsigned long _data_begin;
extern unsigned long _data_end;
extern unsigned long _bss_begin;
extern unsigned long _bss_end;
extern unsigned long _stack_end;
extern unsigned long _estack;

extern int main(void);
extern void debug(int num);

void default_handler(void);

void __attribute__((weak)) NMI_handler(void);
void __attribute__((weak)) HardFault_handler(void);
void __attribute__((weak)) MemManage_handler(void);
void __attribute__((weak)) BusFault_handler(void);
void __attribute__((weak)) UsageFault_handler(void);
void __attribute__((weak)) SVCall_handler(void);
void __attribute__((weak)) Debug_Monitor_handler(void);
void __attribute__((weak)) PendSV_handler(void);
void __attribute__((weak)) SysTick_handler(void);

/*Interrupts*/
void __attribute__((weak)) WWDG_handler(void);
void __attribute__((weak)) PVD_handler(void);
void __attribute__((weak)) TAMPER_handler(void);
void __attribute__((weak)) RTC_handler(void);
void __attribute__((weak)) FLASH_handler(void);
void __attribute__((weak)) RCC_handler(void);
void __attribute__((weak)) EXTI0_handler(void);
void __attribute__((weak)) EXTI1_handler(void);
void __attribute__((weak)) EXTI2_handler(void);
void __attribute__((weak)) EXTI3_handler(void);
void __attribute__((weak)) EXTI4_handler(void);
void __attribute__((weak)) DMA1_Channel1_handler(void);
void __attribute__((weak)) DMA1_Channel2_handler(void);
void __attribute__((weak)) DMA1_Channel3_handler(void);
void __attribute__((weak)) DMA1_Channel4_handler(void);
void __attribute__((weak)) DMA1_Channel5_handler(void);
void __attribute__((weak)) DMA1_Channel6_handler(void);
void __attribute__((weak)) DMA1_Channel7_handler(void);
void __attribute__((weak)) ADC1_2_handler(void);
#ifdef STM32F10X_CL
void __attribute__((weak)) CAN1_TX_handler(void);
void __attribute__((weak)) CAN1_RX0_handler(void);
void __attribute__((weak)) CAN1_RX1_handler(void);
void __attribute__((weak)) CAN1_SCE_handler(void);
#elif STM32F10X_XL || STM32F10X_MD || STM32F10X_LD
void __attribute__((weak)) USB_HP_CAN_TX_handler(void);
void __attribute__((weak)) USB_LP_CAN_RX0_handler(void);
void __attribute__((weak)) CAN_RX1_handler(void);
void __attribute__((weak)) CAN_SCE_handler(void);
#endif
void __attribute__((weak)) EXTI9_5_handler(void);
void __attribute__((weak)) TIM1_BRK_handler(void);
void __attribute__((weak)) TIM1_UP_handler(void);

#if defined (STM32F10X_CL) || defined (STM32F10X_MD) || defined (STM32F10X_LD)
void __attribute__((weak)) TIM1_TRG_COM_handler(void);
#elif STM32F10X_XL
void __attribute__((weak)) TIM1_TRG_COM_TIM11_handler(void);
#endif
void __attribute__((weak)) TIM1_CC_handler(void);
void __attribute__((weak)) TIM2_handler(void);
void __attribute__((weak)) TIM3_handler(void);
void __attribute__((weak)) TIM4_handler(void);
void __attribute__((weak)) I2C1_EV_handler(void);
void __attribute__((weak)) I2C1_ER_handler(void);
void __attribute__((weak)) I2C2_EV_handler(void);
void __attribute__((weak)) I2C2_ER_handler(void);
void __attribute__((weak)) SPI1_handler(void);
void __attribute__((weak)) SPI2_handler(void);
void __attribute__((weak)) USART1_handler(void);
void __attribute__((weak)) USART2_handler(void);
void __attribute__((weak)) USART3_handler(void);
void __attribute__((weak)) EXTI15_10_handler(void);
void __attribute__((weak)) RTCAlarm_handler(void);
#ifdef STM32F10X_CL
void __attribute__((weak)) OTG_FS_WKUP_handler(void);
void __attribute__((weak)) TIM5_handler(void);
void __attribute__((weak)) SPI3_handler(void);
void __attribute__((weak)) UART4_handler(void);
void __attribute__((weak)) UART5_handler(void);
void __attribute__((weak)) TIM6_handler(void);
void __attribute__((weak)) TIM7_handler(void);
void __attribute__((weak)) DMA_Channel1_handler(void);
void __attribute__((weak)) DMA_Channel2_handler(void);
void __attribute__((weak)) DMA_Channel3_handler(void);
void __attribute__((weak)) DMA_Channel4_handler(void);
void __attribute__((weak)) DMA_Channel5_handler(void);
void __attribute__((weak)) ETH_handler(void);
void __attribute__((weak)) ETH_WKUP_handler(void);
void __attribute__((weak)) CAN2_TX_handler(void);
void __attribute__((weak)) CAN2_RX0_handler(void);
void __attribute__((weak)) CAN2_RX1_handler(void);
void __attribute__((weak)) CAN2_SCE_handler(void);
void __attribute__((weak)) OTG_FS_handler(void);
#elif STM32F10X_XL || STM32F10X_MD || STM32F10X_LD
void __attribute__((weak)) USBWakeUp_handler(void);
#ifdef STM32F10X_XL
void __attribute__((weak)) TIM8_BRK_TIM12_handler(void);
void __attribute__((weak)) TIM8_UP_TIM13_handler(void);
void __attribute__((weak)) TIM8_TRG_COM_TIM14_handler(void);
#else
void __attribute__((weak)) TIM8_BRK_handler(void);
void __attribute__((weak)) TIM8_UP_handler(void);
void __attribute__((weak)) TIM8_TRG_COM_handler(void);
#endif
void __attribute__((weak)) TIM8_CC_handler(void);
void __attribute__((weak)) ADC3_handler(void);
void __attribute__((weak)) FSMC_handler(void);
void __attribute__((weak)) SDIO_handler(void);
void __attribute__((weak)) TIM5_handler(void);
void __attribute__((weak)) SPI3_handler(void);
void __attribute__((weak)) UART4_handler(void);
void __attribute__((weak)) UART5_handler(void);
void __attribute__((weak)) TIM6_handler(void);
void __attribute__((weak)) TIM7_handler(void);
void __attribute__((weak)) DMA2_Channel1_handler(void);
void __attribute__((weak)) DMA2_Channel2_handler(void);
void __attribute__((weak)) DMA2_Channel3_handler(void);
void __attribute__((weak)) DMA2_Channel4_5_handler(void);
#endif

void default_handler(void)
{
	while (1);
}

void handler_reset(void)
{
	unsigned long *source, *destination;
	extern unsigned long _interrupt_vector_offs;

	source = &_data_flash;

	destination = &_data_begin;

	while (destination < &_data_end)
		*(destination++) = *(source++);

	destination = &_bss_begin;

	while (destination < &_bss_end)
		*(destination++) = 0;

	SCB->VTOR = 0x08000000 | ((uint32_t)&_interrupt_vector_offs & (uint32_t)0x1FFFFF80);

	/* Start main routine */
	main();
}

/* Interrupt vector */
__attribute__ ((section(".interrupt_vector")))
void (* const table_interrupt_vector[])(void) =
{
	(void *) &_estack, //stack
	handler_reset, // Reset
	NMI_handler, // NMI
	HardFault_handler, // hardFault
	MemManage_handler,
	BusFault_handler,
	UsageFault_handler,
	0,
	0,
	0,
	0,
	SVCall_handler,
	Debug_Monitor_handler,
	0,
	PendSV_handler,
	SysTick_handler,

	WWDG_handler,
	PVD_handler,
	TAMPER_handler,
	RTC_handler,
	FLASH_handler,
	RCC_handler,
	EXTI0_handler,
	EXTI1_handler,
	EXTI2_handler,
	EXTI3_handler,
	EXTI4_handler,
	DMA1_Channel1_handler,
	DMA1_Channel2_handler,
	DMA1_Channel3_handler,
	DMA1_Channel4_handler,
	DMA1_Channel5_handler,
	DMA1_Channel6_handler,
	DMA1_Channel7_handler,
	ADC1_2_handler,
#ifdef STM32F10X_CL
	CAN1_TX_handler,
	CAN1_RX0_handler,
	CAN1_RX1_handler,
	CAN1_SCE_handler,
#elif STM32F10X_XL || STM32F10X_MD || STM32F10X_LD
	USB_HP_CAN_TX_handler,
	USB_LP_CAN_RX0_handler,
	CAN_RX1_handler,
	CAN_SCE_handler,
#endif
	EXTI9_5_handler,
	TIM1_BRK_handler,
	TIM1_UP_handler,
#if defined (STM32F10X_CL) || defined (STM32F10X_MD) || defined (STM32F10X_LD)
	TIM1_TRG_COM_handler,
#elif STM32F10X_XL
	TIM1_TRG_COM_TIM11_handler,
#endif
	TIM1_CC_handler,
	TIM2_handler,
	TIM3_handler,
	TIM4_handler,
	I2C1_EV_handler,
	I2C1_ER_handler,
	I2C2_EV_handler,
	I2C2_ER_handler,
	SPI1_handler,
	SPI2_handler,
	USART1_handler,
	USART2_handler,
	USART3_handler,
	EXTI15_10_handler,
	RTCAlarm_handler,
#ifdef STM32F10X_CL
	OTG_FS_WKUP_handler,
	TIM5_handler,
	SPI3_handler,
	UART4_handler,
	UART5_handler,
	TIM6_handler,
	TIM7_handler,
	DMA_Channel1_handler,
	DMA_Channel2_handler,
	DMA_Channel3_handler,
	DMA_Channel4_handler,
	DMA_Channel5_handler,
	ETH_handler,
	ETH_WKUP_handler,
	CAN2_TX_handler,
	CAN2_RX0_handler,
	CAN2_RX1_handler,
	CAN2_SCE_handler,
	OTG_FS_handler,
#elif STM32F10X_XL || STM32F10X_MD || STM32F10X_LD
	USBWakeUp_handler,
#ifdef STM32F10X_XL
	TIM8_BRK_TIM12_handler,
	TIM8_UP_TIM13_handler,
	TIM8_TRG_COM_TIM14_handler,
#else
	TIM8_BRK_handler,
	TIM8_UP_handler,
	TIM8_TRG_COM_handler,
#endif
	TIM8_CC_handler,
	ADC3_handler,
	FSMC_handler,
	SDIO_handler,
	TIM5_handler,
	SPI3_handler,
	UART4_handler,
	UART5_handler,
	TIM6_handler,
	TIM7_handler,
	DMA2_Channel1_handler,
	DMA2_Channel2_handler,
	DMA2_Channel3_handler,
	DMA2_Channel4_5_handler
#endif

};

#pragma weak NMI_handler = default_handler
#pragma weak hardFault_handler = default_handler
#pragma weak MemManage_handler = default_handler
#pragma weak BusFault_handler = default_handler
#pragma weak UsageFault_handler = default_handler
#pragma weak SVCall_handler = default_handler
#pragma weak Debug_Monitor_handler = default_handler
#pragma weak PendSV_handler = default_handler
#pragma weak SysTick_handler = default_handler

#pragma weak WWDG_handler = default_handler
#pragma weak PVD_handler = default_handler
#pragma weak TAMPER_handler = default_handler
#pragma weak RTC_handler = default_handler
#pragma weak FLASH_handler = default_handler
#pragma weak RCC_handler = default_handler
#pragma weak EXTI0_handler = default_handler
#pragma weak EXTI1_handler = default_handler
#pragma weak EXTI2_handler = default_handler
#pragma weak EXTI3_handler = default_handler
#pragma weak EXTI4_handler = default_handler
#pragma weak DMA1_Channel1_handler = default_handler
#pragma weak DMA1_Channel2_handler = default_handler
#pragma weak DMA1_Channel3_handler = default_handler
#pragma weak DMA1_Channel4_handler = default_handler
#pragma weak DMA1_Channel5_handler = default_handler
#pragma weak DMA1_Channel6_handler = default_handler
#pragma weak DMA1_Channel7_handler = default_handler
#pragma weak ADC1_2_handler = default_handler

#ifdef STM32F10X_CL

#pragma weak CAN1_TX_handler = default_handler
#pragma weak CAN1_RX0_handler = default_handler
#pragma weak CAN1_RX1_handler = default_handler
#pragma weak CAN1_SCE_handler = default_handler

#elif STM32F10X_XL || STM32F10X_MD || STM32F10X_LD

#pragma weak USB_HP_CAN_TX_handler = default_handler
#pragma weak USB_LP_CAN_RX0_handler = default_handler
#pragma weak CAN_RX1_handler = default_handler
#pragma weak CAN_SCE_handler = default_handler

#endif

#pragma weak EXTI9_5_handler = default_handler
#pragma weak TIM1_BRK_handler = default_handler
#pragma weak TIM1_UP_handler = default_handler

#if defined (STM32F10X_CL) || defined (STM32F10X_MD) || defined (STM32F10X_LD)

#pragma weak TIM1_TRG_COM_handler = default_handler

#elif STM32F10X_XL

#pragma weak TIM1_TRG_COM_TIM11_handler = default_handler

#endif

#pragma weak TIM1_CC_handler = default_handler
#pragma weak TIM2_handler = default_handler
#pragma weak TIM3_handler = default_handler
#pragma weak TIM4_handler = default_handler
#pragma weak I2C1_EV_handler = default_handler
#pragma weak I2C1_ER_handler = default_handler
#pragma weak I2C2_EV_handler = default_handler
#pragma weak I2C2_ER_handler = default_handler
#pragma weak SPI1_handler = default_handler
#pragma weak SPI2_handler = default_handler
#pragma weak USART1_handler = default_handler
#pragma weak USART2_handler = default_handler
#pragma weak USART3_handler = default_handler
#pragma weak EXTI15_10_handler = default_handler
#pragma weak RTCAlarm_handler = default_handler

#ifdef STM32F10X_CL

#pragma weak OTG_FS_WKUP_handler = default_handler
#pragma weak TIM5_handler = default_handler
#pragma weak SPI3_handler = default_handler
#pragma weak UART4_handler = default_handler
#pragma weak UART5_handler = default_handler
#pragma weak TIM6_handler = default_handler
#pragma weak TIM7_handler = default_handler
#pragma weak DMA_Channel1_handler = default_handler
#pragma weak DMA_Channel2_handler = default_handler
#pragma weak DMA_Channel3_handler = default_handler
#pragma weak DMA_Channel4_handler = default_handler
#pragma weak DMA_Channel5_handler = default_handler
#pragma weak ETH_handler = default_handler
#pragma weak ETH_WKUP_handler = default_handler
#pragma weak CAN2_TX_handler = default_handler
#pragma weak CAN2_RX0_handler = default_handler
#pragma weak CAN2_RX1_handler = default_handler
#pragma weak CAN2_SCE_handler = default_handler
#pragma weak OTG_FS_handler = default_handler

#elif STM32F10X_XL || STM32F10X_MD || STM32F10X_LD

#pragma weak USBWakeUp_handler = default_handler

#ifdef STM32F10X_XL

#pragma weak TIM8_BRK_TIM12_handler = default_handler
#pragma weak TIM8_UP_TIM13_handler = default_handler
#pragma weak TIM8_TRG_COM_TIM14_handler = default_handler

#else

#pragma weak TIM8_BRK_handler = default_handler
#pragma weak TIM8_UP_handler = default_handler
#pragma weak TIM8_TRG_COM_handler = default_handler

#endif

#pragma weak TIM8_CC_handler = default_handler
#pragma weak ADC3_handler = default_handler
#pragma weak FSMC_handler = default_handler
#pragma weak SDIO_handler = default_handler
#pragma weak TIM5_handler = default_handler
#pragma weak SPI3_handler = default_handler
#pragma weak UART4_handler = default_handler
#pragma weak UART5_handler = default_handler
#pragma weak TIM6_handler = default_handler
#pragma weak TIM7_handler = default_handler
#pragma weak DMA2_Channel1_handler = default_handler
#pragma weak DMA2_Channel2_handler = default_handler
#pragma weak DMA2_Channel3_handler = default_handler
#pragma weak DMA2_Channel4_5_handler = default_handler

#endif

