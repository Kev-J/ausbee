#ifndef AUSBEE_DEVICE_H
#define AUSBEE_DEVICE_H

#if defined (STM32F40_41xxx) || defined (STM32F427_437xx) || defined (STM32F429_439xx) || defined (STM32F401xx)

#define STM32F4XX /* STM32 F4 serie */

#include <stm32f4xx.h>

#elif defined (STM32F10X_LD) || defined (STM32F10X_LD_VL) || defined (STM32F10X_MD) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD) || defined (STM32F10X_HD_VL) || defined (STM32F10X_XL) || defined (STM32F10X_CL)

#define STM32F10X/* STM32 F1 serie */

#include <stm32f10x.h>

#else

/* PC */

#endif /* STM32FXXX */

#endif /* AUSBEE_DEVICE_H */
