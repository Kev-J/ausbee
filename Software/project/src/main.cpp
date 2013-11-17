#include <stm32f10x.h>
#include <FreeRTOS.h>
#include <task.h>

void xPortPendSVHandler();
void xPortSysTickHandler();
void vPortSVCHandler();

void SVCall_handler(void)
{
    vPortSVCHandler();
}

void SysTick_handler(void)
{
    xPortSysTickHandler();
}

void PendSV_handler(void)
{
    xPortPendSVHandler();
}

static void prvSetupHardware(void)
{
//    init();
//    backlight_enable(1);
}

void vApplicationStackOverflowHook(xTaskHandle xTask, signed portCHAR *pcTaskName)
{
//    lcd_clear();
//    lcd_write_xy(0,0,"Stack overflow");
}

void vApplicationMallocFailedHook()
{
	while(1) {
	}
/*    lcd_clear();
    lcd_write_xy(0,0,"Malloc failed");

    while(1) {
        set_led(LED1 | LED2);
    }*/
}

void vApplicationIdleHook(void)
{
//    while(1)
//        set_led(LED2);
}

void initTsk(void)
{

    while(1) {
    }
}

int main(void)
{
    prvSetupHardware();

    //xTaskCreate((pdTASK_CODE)initTsk, (signed char *) "initTsk", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+2, NULL);

    vTaskStartScheduler();

    while(1) {
    }
}
