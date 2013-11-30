#include <stm32f4xx.h>

#ifdef DEBUG
#define assert_param(x) ((x) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
void assert_failed((uint8_t *filename, uint32_t line);
#else
#define assert_param(x) ((void)0)
#endif
