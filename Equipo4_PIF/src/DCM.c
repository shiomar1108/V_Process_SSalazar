/*
 * DCM.c
 *
 *  Created on: 11 mar. 2021
 *      Author: ssalazar
 */

#include "interrupt_manager.h"
#include "sdk_project_config.h"
#include "BoardDefines.h"
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "DCM.h"
#include "CAN_usr.h"
#include "CAN_app.h"
#include "SerialManager.h"
#include "DCM_App.h"
#include "ActuatorManager.h"
#include "ManufacturingManager.h"
#include "ButtonManager.h"

/*-----------------------------------------------------------*/
/* Task related definitions */
#define APP_TASK_10MS_PERIOD		(10)
#define	APP_TASK_10MS_PRIO			(3)
#define APP_TASK_50MS_PERIOD		(50)
#define	APP_TASK_50MS_PRIO			(4)
#define APP_TASK_100MS_PERIOD		(100)
#define	APP_TASK_100MS_PRIO			(5)
#define	APP_TASK_STACK_SIZE			((unsigned short) 200 )

#define MODULE "TASK"

#define DCM_APP_UT					(0)
#define SM_UT						(0)
#define DCM_APP_IT					(1)

/*-----------------------------------------------------------*/
/* Function Prototypes */

static void app_task_10ms( void *pvParameters );
static void app_task_50ms( void *pvParameters );
static void app_task_100ms( void *pvParameters );

/*-----------------------------------------------------------*/


/*-----------------------------------------------------------*/
/* CAN application relays on this variable to  work properly */
//#warning " CAN application relays on CAN_Debug_SW_Variant to  work properly "
uint8_t	CAN_Debug_SW_Variant;


void DCM_Init (void)
{
	/* Init 10 ms task */
	xTaskCreate( app_task_10ms, "T_10MS", APP_TASK_STACK_SIZE, NULL, APP_TASK_10MS_PRIO, NULL );
	/* Init 50 ms task */
	xTaskCreate( app_task_50ms, "T_50MS", APP_TASK_STACK_SIZE, NULL, APP_TASK_50MS_PRIO, NULL );
	/* Init 50 ms task */
	xTaskCreate( app_task_100ms, "T_100MS", APP_TASK_STACK_SIZE, NULL, APP_TASK_100MS_PRIO, NULL );

	/* Initialize ADC (POT) */
	ADC_DRV_ConfigConverter(ADC_INSTANCE, &ADC_0_ConvConfig0);
	ADC_DRV_AutoCalibration(ADC_INSTANCE);
	ADC_DRV_ConfigChan(ADC_INSTANCE, 0UL, &ADC_0_ChnConfig0);

	/* Initialize Pin */
	PINS_DRV_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);

	/* Here each SWC Init Functions */
	(void)ManufacturingManager_Init();
	(void)ButtonManager_Init();
	CAN_Debug_SW_Variant = getVariantId();
	(void)SerialManager_Init();
	(void)DCM_App_Init();
	Actuator_Manager_Init();
	CAN_HandlerInit(CAN_Debug_SW_Variant);
#if DCM_APP_UT
	(void)DCM_App_UnitTest();
#endif
#if SM_UT
	(void)SerialMananger_UnitTest();
#endif
#if DCM_APP_IT
	(void)DCM_APP_IntegrationTest();
#endif
}
/*-----------------------------------------------------------*/

static void app_task_10ms( void *pvParameters )
{
	TickType_t xNextWakeTime;

	/* Casting pvParameters to void because it is unused */
	(void)pvParameters;

	/* Initialize xNextWakeTime - this only needs to be done once. */
	xNextWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, the constant used converts ticks
		to ms.  While in the Blocked state this task will not consume any CPU
		time. */
		vTaskDelayUntil( &xNextWakeTime, APP_TASK_10MS_PERIOD );

		/* Task Functions Here */
		APP_CAN10ms_txProcess(CAN_Debug_SW_Variant);
		(void)ButtonManager();
	}
}
/*-----------------------------------------------------------*/

static void app_task_50ms( void *pvParameters )
{
	TickType_t xNextWakeTime;

	/* Casting pvParameters to void because it is unused */
	(void)pvParameters;

	/* Initialize xNextWakeTime - this only needs to be done once. */
	xNextWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, the constant used converts ticks
		to ms.  While in the Blocked state this task will not consume any CPU
		time. */
		vTaskDelayUntil( &xNextWakeTime, APP_TASK_50MS_PERIOD );
		/* Task Functions Here */
		APP_RxCAN_process(CAN_Debug_SW_Variant);
		processDoorControl();
		(void)DCM_Process_Req();

	}
}
/*-----------------------------------------------------------*/

static void app_task_100ms( void *pvParameters )
{
	TickType_t xNextWakeTime;

	/* Casting pvParameters to void because it is unused */
	(void)pvParameters;

	/* Initialize xNextWakeTime - this only needs to be done once. */
	xNextWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, the constant used converts ticks
		to ms.  While in the Blocked state this task will not consume any CPU
		time. */
		vTaskDelayUntil( &xNextWakeTime, APP_TASK_100MS_PERIOD );

		/* Task Functions Here */
		processWindowControl();
	}
}
/*-----------------------------------------------------------*/
