#include <stm32f10x.h>

#ifdef USE_ASSERT_PARAM
#define assert_param(x) ((x) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
void assert_failed((uint8_t *filename, uint32_t line);
#else
#define assert_param(x) ((void)0)
#endif
