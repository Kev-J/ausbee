/*
    FreeRTOS V7.5.3 - Copyright (C) 2013 Real Time Engineers Ltd. 
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that has become a de facto standard.             *
     *                                                                       *
     *    Help yourself get started quickly and support the FreeRTOS         *
     *    project by purchasing a FreeRTOS tutorial book, reference          *
     *    manual, or both from: http://www.FreeRTOS.org/Documentation        *
     *                                                                       *
     *    Thank you!                                                         *
     *                                                                       *
    ***************************************************************************

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>!AND MODIFIED BY!<< the FreeRTOS exception.

    >>! NOTE: The modification to the GPL is included to allow you to distribute
    >>! a combined work that includes FreeRTOS without being obliged to provide
    >>! the source code for proprietary components outside of the FreeRTOS
    >>! kernel.

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available from the following
    link: http://www.freertos.org/a00114.html

    1 tab == 4 spaces!

    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?"                                     *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org - Documentation, books, training, latest versions,
    license and Real Time Engineers Ltd. contact details.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.OpenRTOS.com - Real Time Engineers ltd license FreeRTOS to High
    Integrity Systems to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/


/* The following #error directive is to remind users that a batch file must be
 * executed prior to this project being built.  The batch file *cannot* be 
 * executed from within CCS4!  Once it has been executed, re-open or refresh 
 * the CCS4 project and remove the #error line below.
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <generated/autoconf.h>

#include "projdefs.h" //needed to test FreeRTOS version

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

#ifdef CONFIG_FREERTOS_USE_PREEMPTION
# define configUSE_PREEMPTION			1
#else
# define configUSE_PREEMPTION			0
#endif

#ifdef CONFIG_FREERTOS_USE_TICKLESS_IDLE
# define configUSE_TICKLESS_IDLE			1
#else
# define configUSE_TICKLESS_IDLE			0
#endif

#define configCPU_CLOCK_HZ				( CONFIG_FREERTOS_CPU_CLOCK_HZ )	

#ifndef pdMS_TO_TICKS //FREERTOS v7
#define configTICK_RATE_HZ				( ( portTickType ) CONFIG_FREERTOS_TICK_RATE_HZ )
#else //FREERTOS v8
#define configTICK_RATE_HZ				( ( TickType_t ) CONFIG_FREERTOS_TICK_RATE_HZ )
#endif

#define configMAX_PRIORITIES			( CONFIG_FREERTOS_MAX_PRIORITIES )

#define configMINIMAL_STACK_SIZE		( ( unsigned short ) CONFIG_FREERTOS_MINIMAL_STACK_SIZE )

#define configTOTAL_HEAP_SIZE			( ( size_t ) CONFIG_FREERTOS_TOTAL_HEAP_SIZE )

#define configMAX_TASK_NAME_LEN			( CONFIG_FREERTOS_MAX_TASK_NAME_LEN )

#ifdef CONFIG_FREERTOS_USE_16_BIT_TICKS
# define configUSE_16_BIT_TICKS 1
#else
# define configUSE_16_BIT_TICKS 0
#endif

#ifdef CONFIG_FREERTOS_IDLE_SHOULD_YIELD
# define configIDLE_SHOULD_YIELD 1
#else
# define configIDLE_SHOULD_YIELD 0
#endif

#ifdef CONFIG_FREERTOS_USE_TASK_NOTIFICATIONS
# define configUSE_TASK_NOTIFICATIONS 1
#else
# define configUSE_TASK_NOTIFICATIONS 0
#endif

#ifdef CONFIG_FREERTOS_USE_MUTEXES
# define configUSE_MUTEXES 1
#else
# define configUSE_MUTEXES 0
#endif

#ifdef CONFIG_FREERTOS_USE_RECURSIVE_MUTEXES
# define configUSE_RECURSIVE_MUTEXES 1
#else
# define configUSE_RECURSIVE_MUTEXES 0
#endif

#ifdef CONFIG_FREERTOS_USE_COUNTING_SEMAPHORES
# define configUSE_COUNTING_SEMAPHORES 1
#else
# define configUSE_COUNTING_SEMAPHORES 0
#endif

#define configUSE_ALTERNATIVE_API 0 /* Deprecated! */

#define configQUEUE_REGISTRY_SIZE		( CONFIG_FREERTOS_QUEUE_REGISTRY_SIZE )

#ifdef CONFIG_FREERTOS_USE_QUEUE_SETS
# define configUSE_QUEUE_SETS 1
#else
# define configUSE_QUEUE_SETS 0
#endif

#ifdef CONFIG_FREERTOS_USE_TIME_SLICING
# define configUSE_TIME_SLICING 1
#else
# define configUSE_TIME_SLICING 0
#endif

#ifdef CONFIG_FREERTOS_ENABLE_BACKWARD_COMPATIBILITY
# define configENABLE_BACKWARD_COMPATIBILITY 1
#else
# define configENABLE_BACKWARD_COMPATIBILITY 0
#endif

#define configNUM_THREAD_LOCAL_STORAGE_POINTERS ( CONFIG_FREERTOS_NUM_THREAD_LOCAL_STORAGE_POINTERS)



/* Hook function related definitions. */

#ifdef CONFIG_FREERTOS_USE_IDLE_HOOK
# define configUSE_IDLE_HOOK 1
#else
# define configUSE_IDLE_HOOK 0
#endif

#ifdef CONFIG_FREERTOS_USE_TICK_HOOK
# define configUSE_TICK_HOOK 1
#else
# define configUSE_TICK_HOOK 0
#endif

#ifdef CONFIG_FREERTOS_CHECK_FOR_STACK_OVERFLOW
# define configCHECK_FOR_STACK_OVERFLOW 1
#else
# define configCHECK_FOR_STACK_OVERFLOW 0
#endif

#ifdef CONFIG_FREEROS_USE_MALLOC_FAILED_HOOK
# define configUSE_MALLOC_FAILED_HOOK 1
#else
# define configUSE_MALLOC_FAILED_HOOK 0
#endif



/* Run time and task stats gathering related definitions. */

#ifdef CONFIG_FREERTOS_GENERATE_RUN_TIME_STATS
# define configGENERATE_RUN_TIME_STATS 1
#else
# define configGENERATE_RUN_TIME_STATS 0
#endif

#ifdef CONFIG_FREERTOS_USE_TRACE_FACILITY
# define configUSE_TRACE_FACILITY 1
#else
# define configUSE_TRACE_FACILITY 0
#endif

#ifdef CONFIG_FREERTOS_USE_STATS_FORMATTING_FUNCTIONS
# define configUSE_STATS_FORMATTING_FUNCTION 1
#else
# define configUSE_STATS_FORMATTING_FUNCTION 0
#endif



/* Co-routine related definitions. */

#ifdef CONFIG_FREERTOS_USE_CO_ROUTINES
# define configUSE_CO_ROUTINES 1
#else
# define configUSE_CO_ROUTINES 0
#endif

#define configMAX_CO_ROUTINE_PRIORITIES ( CONFIG_FREERTOS_MAX_CO_ROUTINE_PRIORITIES )



/* Software timer related definitions. */

#ifdef CONFIG_FREERTOS_USE_TIMERS
# define configUSE_TIMERS 1
#else
# define configUSE_TIMERS 0
#endif

#define configTIMER_TASK_PRIORITY		( CONFIG_FREERTOS_TIMER_TASK_PRIORITY )

#define configTIMER_QUEUE_LENGTH		( CONFIG_FREERTOS_TIMER_QUEUE_LENGTH )

#define configTIMER_TASK_STACK_DEPTH	( configMINIMAL_STACK_SIZE )



/* FreeRTOS MPU specific definitions. */ 

#ifdef CONFIG_FREERTOS_INCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS
# define configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS 1PPLICATION_TASK_TAG
#else
# define configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS 1
#endif



/* Optional functions - most linkers will remove unused functions anyway. */

#ifdef CONFIG_FREERTOS_INCLUDE_VTASKPRIORITYSET
# define INCLUDE_vTaskPrioritySet 1
#else
# define INCLUDE_vTaskPrioritySet 0
#endif

#ifdef CONFIG_FREERTOS_INCLUDE_UXTASKPRIORITYGET
# define INCLUDE_uxTaskPriorityGet 1
#else
# define INCLUDE_uxTaskPriorityGet 0
#endif

#ifdef CONFIG_FREERTOS_INCLUDE_VTASKDELETE
# define INCLUDE_vTaskDelete 1
#else
# define INCLUDE_vTaskDelete 0
#endif

#ifdef CONFIG_FREERTOS_INCLUDE_VTASKSUSPEND
# define INCLUDE_vTaskSuspend 1
#else
# define INCLUDE_vTaskSuspend 0
#endif

#ifdef CONFIG_FREERTOS_INCLUDE_XRESUMEFROMISR
# define INCLUDE_xResumeFromISR 1
#else
# define INCLUDE_xResumeFromISR 0
#endif

#ifdef CONFIG_FREERTOS_INCLUDE_VTASKDELAY
# define INCLUDE_vTaskDelay 1
#else
# define INCLUDE_vTaskDelay 0
#endif

#ifdef CONFIG_FREERTOS_INCLUDE_VTASKDELAYUNTIL
# define INCLUDE_vTaskDelayUntil 1
#else
# define INCLUDE_vTaskDelayUntil 0
#endif

#ifdef CONFIG_FREERTOS_INCLUDE_XTASKGETSCHEDULERSTATE
# define INCLUDE_xTaskGetSchedulerState 1
#else
# define INCLUDE_vTaskGetSchedulerState 0
#endif

#ifdef CONFIG_FREERTOS_INCLUDE_VTASKGETCURRENTTASKHANDLE
# define INCLUDE_vTaskGetCurrentTaskHandle 1
#else
# define INCLUDE_vTaskGetCurrentTaskHandle 0
#endif

#ifdef CONFIG_FREERTOS_INCLUDE_UXTASKGETSTACKHIGHWATERMARK
# define INCLUDE_uxTaskGetStackHighWaterMark 1
#else
# define INCLUDE_uxTaskGetStackHighWaterMark 0
#endif

#ifdef CONFIG_FREERTOS_INCLUDE_PCTASKGETTASKNAME
# define INCLUDE_pcTaskGetTaskName 1
#else
# define INCLUDE_pcTaskGetTaskName 0
#endif

#ifdef CONFIG_FREERTOS_INCLUDE_ETASKGETSTATE
# define INCLUDE_eTaskGetState 1
#else
# define INCLUDE_eTaskGetState 0
#endif

#ifdef CONFIG_FREERTOS_INCLUDE_XEVENTGROUPSETBITFROMISR
# define INCLUDE_xEventGroupSetBitFromISR 1
#else
# define INCLUDE_xEventGroupSetBitFromISR 0
#endif

#ifdef CONFIG_FREERTOS_INCLUDE_XTIMERPENDFUNCTIONCALL
# define INCLUDE_xTimerPendFunctionCall 1
#else
# define INCLUDE_xTimerPendFunctionCall 0
#endif





/* --- */

#define configUSE_APPLICATION_TASK_TAG	0


/* Use the system definition, if there is one */
#ifdef __NVIC_PRIO_BITS
	#define configPRIO_BITS       __NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       4        /* 15 priority levels */
#endif

#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			15
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5

/* The lowest priority. */
#define configKERNEL_INTERRUPT_PRIORITY 	( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
/* Priority 5, or 95 as only the top four bits are implemented. */
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
	
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }	
	
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */

