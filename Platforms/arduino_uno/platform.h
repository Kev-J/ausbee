#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>

#define GPIO0   (1 << 0)
#define GPIO1   (1 << 1)
#define GPIO2   (1 << 2)
#define GPIO3   (1 << 3)
#define GPIO4   (1 << 4)
#define GPIO5   (1 << 5)
#define GPIO6   (1 << 6)
#define GPIO7   (1 << 7)
#define GPIO8   (1 << 8)
#define GPIO9   (1 << 9)
#define GPIO10  (1 << 10)
#define GPIO11  (1 << 11)
#define GPIO12  (1 << 12)
#define GPIO13  (1 << 13)

typedef enum
{
  PLATFORM_GPIO_INPUT,
  PLATFORM_GPIO_OUTPUT,
} platform_gpio_dir_t;

void platform_init(void);

void platform_gpio_init(uint16_t gpio, platform_gpio_dir_t direction);
void platform_gpio_set(uint16_t gpio);
void platform_gpio_clear(uint16_t gpio);

#endif// PLATFORM_H
