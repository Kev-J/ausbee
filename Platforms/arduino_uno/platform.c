#include <avr/io.h>
#include "platform.h"

void platform_init(void)
{
}

void platform_gpio_init(uint16_t gpio, platform_gpio_dir_t direction)
{
  switch(direction)
  {
    case PLATFORM_GPIO_INPUT:
      {
        if(gpio & GPIO0)
        {
          DDRD &= ~(1 << 0);
        }
        if(gpio & GPIO1)
        {
          DDRD &= ~(1 << 1);
        }
        if(gpio & GPIO2)
        {
          DDRD &= ~(1 << 2);
        }
        if(gpio & GPIO3)
        {
          DDRD &= ~(1 << 3);
        }
        if(gpio & GPIO4)
        {
          DDRD &= ~(1 << 4);
        }
        if(gpio & GPIO5)
        {
          DDRD &= ~(1 << 5);
        }
        if(gpio & GPIO6)
        {
          DDRD &= ~(1 << 6);
        }
        if(gpio & GPIO7)
        {
          DDRD &= ~(1 << 7);
        }
        if(gpio & GPIO8)
        {
          DDRB &= ~(1 << 0);
        }
        if(gpio & GPIO9)
        {
          DDRB &= ~(1 << 1);
        }
        if(gpio & GPIO10)
        {
          DDRB &= ~(1 << 2);
        }
        if(gpio & GPIO11)
        {
          DDRB &= ~(1 << 3);
        }
        if(gpio & GPIO12)
        {
          DDRB &= ~(1 << 4);
        }
        if(gpio & GPIO13)
        {
          DDRB &= ~(1 << 5);
        }
      }
      break;

    case PLATFORM_GPIO_OUTPUT:
      {
        if(gpio & GPIO0)
        {
          DDRD |= (1 << 0);
        }
        if(gpio & GPIO1)
        {
          DDRD |= (1 << 1);
        }
        if(gpio & GPIO2)
        {
          DDRD |= (1 << 2);
        }
        if(gpio & GPIO3)
        {
          DDRD |= (1 << 3);
        }
        if(gpio & GPIO4)
        {
          DDRD |= (1 << 4);
        }
        if(gpio & GPIO5)
        {
          DDRD |= (1 << 5);
        }
        if(gpio & GPIO6)
        {
          DDRD |= (1 << 6);
        }
        if(gpio & GPIO7)
        {
          DDRD |= (1 << 7);
        }
        if(gpio & GPIO8)
        {
          DDRB |= (1 << 0);
        }
        if(gpio & GPIO9)
        {
          DDRB |= (1 << 1);
        }
        if(gpio & GPIO10)
        {
          DDRB |= (1 << 2);
        }
        if(gpio & GPIO11)
        {
          DDRB |= (1 << 3);
        }
        if(gpio & GPIO12)
        {
          DDRB |= (1 << 4);
        }
        if(gpio & GPIO13)
        {
          DDRB |= (1 << 5);
        }
      }
      break;

  }
}

void platform_gpio_set(uint16_t gpio)
{
  if(gpio & GPIO0)
  {
    PORTD |= (1 << 0);
  }
  if(gpio & GPIO1)
  {
    PORTD |= (1 << 1);
  }
  if(gpio & GPIO2)
  {
    PORTD |= (1 << 2);
  }
  if(gpio & GPIO3)
  {
    PORTD |= (1 << 3);
  }
  if(gpio & GPIO4)
  {
    PORTD |= (1 << 4);
  }
  if(gpio & GPIO5)
  {
    PORTD |= (1 << 5);
  }
  if(gpio & GPIO6)
  {
    PORTD |= (1 << 6);
  }
  if(gpio & GPIO7)
  {
    PORTD |= (1 << 7);
  }
  if(gpio & GPIO8)
  {
    PORTB |= (1 << 0);
  }
  if(gpio & GPIO9)
  {
    PORTB |= (1 << 1);
  }
  if(gpio & GPIO10)
  {
    PORTB |= (1 << 2);
  }
  if(gpio & GPIO11)
  {
    PORTB |= (1 << 3);
  }
  if(gpio & GPIO12)
  {
    PORTB |= (1 << 4);
  }
  if(gpio & GPIO13)
  {
    PORTB |= (1 << 5);
  }
}

void platform_gpio_clear(uint16_t gpio)
{
  if(gpio & GPIO0)
  {
    PORTD &= ~(1 << 0);
  }
  if(gpio & GPIO1)
  {
    PORTD &= ~(1 << 1);
  }
  if(gpio & GPIO2)
  {
    PORTD &= ~(1 << 2);
  }
  if(gpio & GPIO3)
  {
    PORTD &= ~(1 << 3);
  }
  if(gpio & GPIO4)
  {
    PORTD &= ~(1 << 4);
  }
  if(gpio & GPIO5)
  {
    PORTD &= ~(1 << 5);
  }
  if(gpio & GPIO6)
  {
    PORTD &= ~(1 << 6);
  }
  if(gpio & GPIO7)
  {
    PORTD &= ~(1 << 7);
  }
  if(gpio & GPIO8)
  {
    PORTB &= ~(1 << 0);
  }
  if(gpio & GPIO9)
  {
    PORTB &= ~(1 << 1);
  }
  if(gpio & GPIO10)
  {
    PORTB &= ~(1 << 2);
  }
  if(gpio & GPIO11)
  {
    PORTB &= ~(1 << 3);
  }
  if(gpio & GPIO12)
  {
    PORTB &= ~(1 << 4);
  }
  if(gpio & GPIO13)
  {
    PORTB &= ~(1 << 5);
  }
}
