/*
 * Actuator.c
 *
 *  Created on: 12 mar. 2021
 *      Author: Javier
 */

#include "DCM.h"
#include "ActuatorManager.h"
#include "BoardDefines.h"
#include "ManufacturingManager.h"
#include "CAN_app.h"

#define WINDOW_OPEN_PIN 17
#define WINDOW_CLOSE_PIN 11
#define ADC_THRESHOLD_ANTIPINCH 820
#define DOOR_WAIT_100MS_COUNTER 2
#define WINDOW_WAIT_500MS_COUNTER 5
#define CLOSE_WINDOW_INHIBIT_15S_COUNTER 150

#define WINDOW_INDICATOR1	3
#define WINDOW_INDICATOR2	5
#define WINDOW_INDICATOR3	12
#define WINDOW_INDICATOR4	11
#define	WINDOW_INDICATOR5	10
#define	WINDOW_INDICATOR6	17
#define WINDOW_INDICATOR7	8
#define WINDOW_INDICATOR8	9
#define WINDOW_INDICATOR9	2
#define WINDOW_INDICATOR10	1

typedef enum{
	SW_INACTIVE = false,
	SW_ACTIVE = true
}sw_actuator_config_t;


static bool HWSolenoidStatus;
static bool HWMotorStatus;
static bool flag_lockdoor;
static bool flag_unlockdoor;
static bool flag_OpenWindowAction;
static bool flag_CloseWindowAction;
static bool flag_close_global_window;
static bool flag_open_global_window;
static uint8_t counterWindow;
static bool Antipinch_Signal;
static bool FlagAntipinch_Operation;
static doorlock_sts_config_t DoorLockStatus;
static windowPosition_sts_config_t WindowPosition;

S_DCU_1 gDCU_1;
S_DCU_2	gDCU_2;
S_DCU_3	gDCU_3;
S_DCU_4	gDCU_4;
static manufacturing_t gVariant;


static void lockDoorActuation(void);
static void unlockDoorActuation(void);
static windowPosition_sts_config_t getWindowPosition(void);
static void deactivateControlWindow();
static void wait500msOpenWindow(void);
static void wait500msCloseWindow(void);
static void wait15sInhibit(void);

static bool getFlagUnlockDoor(void);
static bool getFlagLockDoor(void);

static bool getflag_OpenWindowAction(void);
static bool getflag_CloseWindowAction(void);
static bool getFlagAntipinch_Operation(void);
static bool getHWSolenoidStatus(void);
static bool getHWMotorStatus(void);
static bool getflag_close_global_window(void);
static bool getflag_open_global_window(void);
static void setFlagAntipinch_Operation(bool inhibit);
static void setDoorLockingStatus(doorlock_sts_config_t doorStatus);
static void setWindowPosition(windowPosition_sts_config_t windowPos);

void Actuator_Manager_Init(void)
{
	Antipinch_Signal = false;
	FlagAntipinch_Operation = false;
	DoorLockStatus = DOOR_UNLOCKED;
	HWSolenoidStatus = true;
	WindowPosition = WINDOW_COMPLETELY_OPEN;
	HWMotorStatus = true;
	flag_lockdoor = false;
	flag_unlockdoor = false;
	counterWindow = 0;
	flag_OpenWindowAction = false;
	flag_CloseWindowAction = false;
	PINS_DRV_SetPins(LED_GPIO, 1 << LED1);
	PINS_DRV_ClearPins(LED_GPIO, 1 << LED2);
	PINS_DRV_ClearPins(LED_GPIO, (1 << WINDOW_INDICATOR1)  | (1 << WINDOW_INDICATOR2) | (1 << WINDOW_INDICATOR3)
								| (1 << WINDOW_INDICATOR4) | (1 << WINDOW_INDICATOR5) | (1 << WINDOW_INDICATOR6)
								| (1 << WINDOW_INDICATOR7) | (1 << WINDOW_INDICATOR8) | (1 << WINDOW_INDICATOR9)
								| (1 << WINDOW_INDICATOR10));

	gVariant = getVariantId();
}

/*---------------------------------------------------------------------------------------------------------------------*/
/* Delay functions */
void wait15sInhibit()
{
	static int count = 0;

	if(count != CLOSE_WINDOW_INHIBIT_15S_COUNTER)
	{
		count++;
	}
	else{
		FlagAntipinch_Operation = false;
		count = 0;
	}
}

void wait500msOpenWindow(void)
{
	static int count = 0;

	if(count != WINDOW_WAIT_500MS_COUNTER)
	{
		count++;
	}
	else{
		flag_OpenWindowAction = false;
		count = 0;
		counterWindow--;
		setWindowPosition(determineWindowPosition());
	}
}

void wait500msCloseWindow(void)
{
	uint16_t adcRawValue;
	static int count = 0;

	ADC_DRV_GetChanResult(ADC_INSTANCE, 0U, &adcRawValue);

	if(adcRawValue >= ADC_THRESHOLD_ANTIPINCH)
	{
		count = 0;
		deactivateControlWindow();
	}
	else if(count != WINDOW_WAIT_500MS_COUNTER)
	{
		count++;
	}
	else
	{
		flag_CloseWindowAction = false;
		count = 0;
		counterWindow++;
		setWindowPosition(determineWindowPosition());
	}
}
/*---------------------------------------------------------------------------------------------------------------------*/
/* Periodic evaluation functions */
void processWindowControl(void)
{
	uint8_t data = 0;
	if ((getflag_close_global_window() == true) && (getWindowPosition() != WINDOW_ERROR) &&
			(getWindowPosition() != WINDOW_COMPLETELY_CLOSE))
	{
		setActuatorAction(CLOSE_WINDOW_ACTUATION);
	}
	else if ((getflag_open_global_window() == true) && (getWindowPosition() != WINDOW_ERROR) &&
				(getWindowPosition() != WINDOW_COMPLETELY_OPEN))
	{
		setActuatorAction(OPEN_WINDOW_ACTUATION);
	}
	else
	{
		data = 0x00;
	}

	/* 500ms transition */
	if(getflag_OpenWindowAction() == true)
	{
		data = 0x02;
		wait500msOpenWindow();
	}
	else if(getflag_CloseWindowAction() == true)
	{
		data = 0x01;
		wait500msCloseWindow();
	}
	/* 15s Close window and Global close window inhibit */
	if(getFlagAntipinch_Operation() == true)
	{
		wait15sInhibit();
	}
	switch (gVariant)
	{
		case DriverDoor:
			gDCU_1.s.DCU_1_WindowOp = data;
			APP_CAN_DCM_DR_update_msg_DCU_1(gDCU_1);
		break;
		case PassengerDoor:
			gDCU_2.s.DCU_2_WindowOp = data;
			APP_CAN_DCM_PS_update_msg_DCU_2(gDCU_2);
		break;
		case RearRightDoor:
			gDCU_4.s.DCU_4_WindowOp = data;
			APP_CAN_DCM_RR_update_msg_DCU_4(gDCU_4);
		break;
		case RearLeftDoor:
			gDCU_3.s.DCU_3_WindowOp = data;
			APP_CAN_DCM_RL_update_msg_DCU_3(gDCU_3);
		break;
		default:
		break;
	}
}

void processDoorControl(void)
{
	if(getFlagLockDoor() == true)
	{
		lockDoorActuation();
	}
	if(getFlagUnlockDoor() == true)
	{
		unlockDoorActuation();
	}
}
/*---------------------------------------------------------------------------------------------------------------------*/
/* Safety process function on detection of anti-pinch event */
void deactivateControlWindow()
{
	Antipinch_Signal = true;
	flag_CloseWindowAction = false;
	flag_close_global_window = false;
	FlagAntipinch_Operation = true;
	/*The counter is increased because the last LED on is not updated
	when canceling the window closing. It was detected when debugging that when executing
	 an OPEN_GLOBAL_WINDOW the last LED on, remains on. */
	counterWindow++;
	setActuatorAction(CANCEL_WINDOW_ACTUATION);
	setActuatorAction(OPEN_GLOBAL_WINDOW_ACTUATION);
}
/*---------------------------------------------------------------------------------------------------------------------*/
/* Actuator status determination functions */
doorlock_sts_config_t determineDoorLockingStatus(void)
{
	volatile sw_actuator_config_t SW_DOOR_LOCKED;
	volatile sw_actuator_config_t SW_DOOR_UNLOCKED;


	/* Read input bits of PORT */
	SW_DOOR_LOCKED = ~(PINS_DRV_ReadPins(LED_GPIO)>>LED1)&0x01;
	SW_DOOR_UNLOCKED = ~(PINS_DRV_ReadPins(LED_GPIO)>>LED2)&0x01;

	if(SW_DOOR_LOCKED == SW_ACTIVE && SW_DOOR_UNLOCKED == SW_INACTIVE )
	{
		setHWSolenoidStatus(true);
		return DOOR_LOCKED;
	}
	else if(SW_DOOR_LOCKED == SW_INACTIVE && SW_DOOR_UNLOCKED == SW_ACTIVE )
	{
		setHWSolenoidStatus(true);
		return DOOR_UNLOCKED;
	}
	else
	{
		setHWSolenoidStatus(false);
		return DOOR_ERROR;
	}
}

windowPosition_sts_config_t determineWindowPosition(void)
{
	volatile sw_actuator_config_t SW_WINDOW_OPEN, SW_WINDOW_CLOSE;

	SW_WINDOW_OPEN = (PINS_DRV_ReadPins(PTA)>>WINDOW_OPEN_PIN)&0x01; /* READ LED1 OUTPUT */
	SW_WINDOW_CLOSE = (PINS_DRV_ReadPins(PTA)>>WINDOW_CLOSE_PIN)&0x01; /* READ LED10 OUTPUT */

		if(SW_WINDOW_OPEN == SW_INACTIVE && SW_WINDOW_CLOSE == SW_INACTIVE)
		{
			if(Antipinch_Signal == true)
			{
				Antipinch_Signal = false;
				setFlagAntipinch_Operation(true);
			}
			flag_open_global_window = false;
			return WINDOW_COMPLETELY_OPEN;
		}
		else if(SW_WINDOW_OPEN == SW_ACTIVE && SW_WINDOW_CLOSE == SW_ACTIVE)
		{
			flag_close_global_window = false;
			return WINDOW_COMPLETELY_CLOSE;
		}
		else if(SW_WINDOW_OPEN == SW_ACTIVE && SW_WINDOW_CLOSE == SW_INACTIVE)
		{
			return IN_BETWEEN;
		}
		else
		{
			setHWMotorStatus(false);
			return WINDOW_ERROR;
		}
}
/*---------------------------------------------------------------------------------------------------------------------*/
/* Door locking actuators drive functions */
void lockDoorActuation()
{
	static uint8_t count = 0;
	if(count == DOOR_WAIT_100MS_COUNTER)
	{
		flag_lockdoor = false;
		PINS_DRV_ClearPins(LED_GPIO, 1 << LED1);
		count = 0;
		setDoorLockingStatus(determineDoorLockingStatus());
	}
	else
	{
		count++;
	}
}

void unlockDoorActuation()
{
	static uint8_t count = 0;
	if(count == DOOR_WAIT_100MS_COUNTER)
	{
		flag_unlockdoor = false;
		PINS_DRV_ClearPins(LED_GPIO, 1 << LED2);
		count = 0;
		setDoorLockingStatus(determineDoorLockingStatus());
	}
	else
	{
		count++;
	}
}
/*---------------------------------------------------------------------------------------------------------------------*/
/* Actuator run control function */
void setActuatorAction(int actuatorAction)
{
	if(getHWSolenoidStatus() == true)
	{
		if( actuatorAction == LOCK_DOOR_ACTUATION)
		{
			PINS_DRV_SetPins(LED_GPIO, 1 << LED2);
			flag_lockdoor = true;
		}
		else if( actuatorAction == UNLOCK_DOOR_ACTUATION)
		{
			PINS_DRV_SetPins(LED_GPIO, 1 << LED1);
			flag_unlockdoor = true;
		}
	}
	if(getHWMotorStatus() == true)
	{
		if(actuatorAction == OPEN_WINDOW_ACTUATION)
		{
			if((WindowPosition != WINDOW_COMPLETELY_OPEN) && (WindowPosition != WINDOW_ERROR))
			{
				if(counterWindow == 10)
				{
					PINS_DRV_ClearPins(LED_GPIO, 1 << WINDOW_INDICATOR10);
					flag_OpenWindowAction = true;
				}
				else if(counterWindow == 9)
				{
					PINS_DRV_ClearPins(LED_GPIO, 1 << WINDOW_INDICATOR9);
					flag_OpenWindowAction = true;
				}
				else if(counterWindow == 8)
				{
					PINS_DRV_ClearPins(LED_GPIO, 1 << WINDOW_INDICATOR8);
					flag_OpenWindowAction = true;
				}
				else if(counterWindow == 7)
				{
					PINS_DRV_ClearPins(LED_GPIO, 1 << WINDOW_INDICATOR7);
					flag_OpenWindowAction = true;
				}
				else if(counterWindow == 6)
				{
					PINS_DRV_ClearPins(LED_GPIO, 1 << WINDOW_INDICATOR6);
					flag_OpenWindowAction = true;
				}
				else if(counterWindow == 5)
				{
					PINS_DRV_ClearPins(LED_GPIO, 1 << WINDOW_INDICATOR5);
					flag_OpenWindowAction = true;
				}
				else if(counterWindow == 4)
				{
					PINS_DRV_ClearPins(LED_GPIO, 1 << WINDOW_INDICATOR4);
					flag_OpenWindowAction = true;
				}
				else if(counterWindow == 3)
				{
					PINS_DRV_ClearPins(LED_GPIO, 1 << WINDOW_INDICATOR3);
					flag_OpenWindowAction = true;
				}
				else if(counterWindow == 2)
				{
					PINS_DRV_ClearPins(LED_GPIO, 1 << WINDOW_INDICATOR2);
					flag_OpenWindowAction = true;
				}
				else if(counterWindow == 1)
				{
					PINS_DRV_ClearPins(LED_GPIO, 1 << WINDOW_INDICATOR1);
					flag_OpenWindowAction = true;
				}
			}
		}
		else if( actuatorAction == CLOSE_WINDOW_ACTUATION)
		{
			if(Antipinch_Signal == false && FlagAntipinch_Operation == false)
			{
				if((WindowPosition != WINDOW_COMPLETELY_CLOSE) && (WindowPosition != WINDOW_ERROR))
				{
					if(counterWindow == 0)
					{
						PINS_DRV_SetPins(LED_GPIO, 1 << WINDOW_INDICATOR1);
						flag_CloseWindowAction = true;
					}
					else if(counterWindow == 1)
					{
						PINS_DRV_SetPins(LED_GPIO, 1 << WINDOW_INDICATOR2);
						flag_CloseWindowAction = true;
					}
					else if(counterWindow == 2)
					{
						PINS_DRV_SetPins(LED_GPIO, 1 << WINDOW_INDICATOR3);
						flag_CloseWindowAction = true;
					}

					else if(counterWindow == 3)
					{
						PINS_DRV_SetPins(LED_GPIO, 1 << WINDOW_INDICATOR4);
						flag_CloseWindowAction = true;
					}
					else if(counterWindow == 4)
					{
						PINS_DRV_SetPins(LED_GPIO, 1 << WINDOW_INDICATOR5);
						flag_CloseWindowAction = true;
					}
					else if(counterWindow == 5)
					{
						PINS_DRV_SetPins(LED_GPIO, 1 << WINDOW_INDICATOR6);
						flag_CloseWindowAction = true;
					}
					else if(counterWindow == 6)
					{
						PINS_DRV_SetPins(LED_GPIO, 1 << WINDOW_INDICATOR7);
						flag_CloseWindowAction = true;
					}
					else if(counterWindow == 7)
					{
						PINS_DRV_SetPins(LED_GPIO, 1 << WINDOW_INDICATOR8);
						flag_CloseWindowAction = true;
					}
					else if(counterWindow == 8)
					{
						PINS_DRV_SetPins(LED_GPIO, 1 << WINDOW_INDICATOR9);
						flag_CloseWindowAction = true;
					}
					else if(counterWindow == 9)
					{
						PINS_DRV_SetPins(LED_GPIO, 1 << WINDOW_INDICATOR10);
						flag_CloseWindowAction = true;
					}
				}
			}
		}
		else if (actuatorAction == OPEN_GLOBAL_WINDOW_ACTUATION)
		{
			if((WindowPosition != WINDOW_COMPLETELY_OPEN) && (WindowPosition != WINDOW_ERROR))
			{
				flag_open_global_window = true;
			}
		}
		else if(actuatorAction == CLOSE_GLOBAL_WINDOW_ACTUATION)
		{
			if((WindowPosition != WINDOW_COMPLETELY_CLOSE) && (WindowPosition != WINDOW_ERROR))
			{
				if(Antipinch_Signal == false && FlagAntipinch_Operation == false)
				{
					flag_close_global_window = true;
				}
			}
		}
	else if(actuatorAction == CANCEL_WINDOW_ACTUATION)
	{
		flag_close_global_window = false;
	}
}
}
/*---------------------------------------------------------------------------------------------------------------------*/
/* Set and Get functions */

bool getFlagAntipinch_Operation()
{
	return FlagAntipinch_Operation;
}

bool getFlagUnlockDoor(void)
{
	return flag_unlockdoor;
}

bool getFlagLockDoor(void)
{
	return flag_lockdoor;
}

bool getflag_OpenWindowAction(void)
{
	return flag_OpenWindowAction;
}

bool getflag_CloseWindowAction(void)
{
	return flag_CloseWindowAction;
}

bool getflag_close_global_window(void)
{
	return flag_close_global_window;
}

bool getflag_open_global_window(void)
{
	return flag_open_global_window;
}

windowPosition_sts_config_t getWindowPosition(void)
{
	return WindowPosition;
}

bool getHWSolenoidStatus(void)
{
	return HWSolenoidStatus;
}

bool getHWMotorStatus(void)
{
	return HWMotorStatus;
}

void setHWMotorStatus(bool Status)
{
	HWMotorStatus = Status;
}
void setHWSolenoidStatus(bool Status)
{
	HWSolenoidStatus = Status;
}

void setWindowPosition(windowPosition_sts_config_t windowPos)
{
	WindowPosition = windowPos;
}
void setDoorLockingStatus(doorlock_sts_config_t doorStatus)
{
	DoorLockStatus = doorStatus;
}
void setFlagAntipinch_Operation(bool inhibit)
{
	FlagAntipinch_Operation = inhibit;
}
