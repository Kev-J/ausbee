#ifndef PORTMACRO_H
#define PORTMACRO_H

#ifdef __cplusplus
extern "C" {
#endif

#define CONFIG_FREERTOS_USE_IDLE_HOOK 1
#undef configUSE_IDLE_HOOK
#define configUSE_IDLE_HOOK 1

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */
#define portCHAR		char
#define portFLOAT		float
#define portDOUBLE		double
#define portLONG		long
#define portSHORT		short
#define portSTACK_TYPE	size_t
#define portBASE_TYPE	long
#define portPOINTER_SIZE_TYPE size_t

typedef portSTACK_TYPE StackType_t;
typedef long BaseType_t;
typedef unsigned long UBaseType_t;

#if( configUSE_16_BIT_TICKS == 1 )
	typedef uint16_t TickType_t;
	#define portMAX_DELAY ( TickType_t ) 0xffff
#else
	typedef uint32_t TickType_t;
	#define portMAX_DELAY ( TickType_t ) 0xffffffffUL

	#define portTICK_TYPE_IS_ATOMIC 1
#endif
/*-----------------------------------------------------------*/

#define portSTACK_GROWTH			( -1 )
#define portTICK_PERIOD_MS			( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portINLINE __inline

#if defined( __x86_64__) || defined( _M_X64 )
	#define portBYTE_ALIGNMENT		8
#else
	#define portBYTE_ALIGNMENT		4
#endif

#define portSET_INTERRUPT_MASK_FROM_ISR()   0; vPortDisableInterrupts()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR(ux)  ( vPortEnableInterrupts() )
#define portSET_INTERRUPT_MASK()  ( vPortDisableInterrupts() )
#define portCLEAR_INTERRUPT_MASK()  ( vPortEnableInterrupts() )
#define portDISABLE_INTERRUPTS()  portSET_INTERRUPT_MASK()
#define portENABLE_INTERRUPTS()   portCLEAR_INTERRUPT_MASK()
#define portENTER_CRITICAL()    vPortEnterCritical()
#define portEXIT_CRITICAL()     vPortExitCritical()
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) void vFunction( void *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters ) void vFunction( void *pvParameters )
#define portYIELD()         vPortYield()
#define traceTASK_CREATE( pxNewTCB )      vPortAddTaskHandle( pxNewTCB )

extern void vPortDisableInterrupts( void );
extern void vPortEnableInterrupts( void );
extern void vPortEnterCritical( void );
extern void vPortExitCritical( void );
extern void vPortYield( void );
extern void vPortAddTaskHandle( void *pxTaskHandle );


///* Critical section management. */
//
//#define portDISABLE_INTERRUPTS()	asm volatile ( "cli" :: );
//#define portENABLE_INTERRUPTS()		asm volatile ( "sei" :: );
///*-----------------------------------------------------------*/
//
///* Architecture specifics. */
//#define portBYTE_ALIGNMENT			1
//#define portNOP()					asm volatile ( "nop" );
///*-----------------------------------------------------------*/

///* Kernel utilities. */
//#define portINTERRUPT_YIELD				( 0UL )
//#define portINTERRUPT_TICK				( 1UL )
//#define portYIELD()					vPortGenerateSimulatedInterrupt( portINTERRUPT_YIELD )
///*-----------------------------------------------------------*/
//
//#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) void vFunction( void *pvParameters )
//#define portTASK_FUNCTION( vFunction, pvParameters ) void vFunction( void *pvParameters )
//#define portDISABLE_INTERRUPTS() vPortEnterCritical()
//#define portENABLE_INTERRUPTS() vPortExitCritical()
//#define portENTER_CRITICAL()		vPortEnterCritical()
//#define portEXIT_CRITICAL()			vPortExitCritical()
//
//void vPortEnterCritical( void );
//void vPortExitCritical( void );
//void vPortGenerateSimulatedInterrupt( uint32_t ulInterruptNumber );

#undef configASSERT
#include <assert.h>
#define configASSERT( x ) assert(x)

#endif /* PORTMACRO_H */

