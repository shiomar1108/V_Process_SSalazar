/*
 * ButtonManager.c
 *
 *  Created on: 15 mar. 2021
 *      Author: Abrah
 */

#include "sdk_project_config.h"
#include "ButtonManager.h"
#include "ManufacturingManager.h"
#include "DCM_App.h"

#define THRESHOLD_SHORT      	(5)
#define THRESHOLD_LONG        	(50)
#define THRESHOLD_STUCK       	(1000)
#define THRESHOLD_LOCK_UN		(5)

#define WindowUp_btn		13U
#define WindowDown_btn		12U
#define PsnWindowUp_btn 	4U
#define PsnWindowDown_btn 	5U
#define RRWindowUp_btn 		11U
#define RRWindowDown_btn 	10U
#define RLWindowUp_btn 		9U
#define RLWindowDown_btn 	8U
#define RWindow_btn 		3U
#define LockBtn_btn 		2U
#define UnlockBtn_btn 		9U


/* Var for DCM App */
static Btn_list_t btn_status;
static manufacturing_t VariantId;

/* Private struct for debounce */
typedef struct {
	uint16_t btn_counter;
	bool debounce_started;
	bool readyProcessing;
}Button_t;

/* Parameter for buttons */
Button_t WindowUp;
Button_t WindowDown;
Button_t PsnWindowUp;
Button_t PsnWindowDown;
Button_t RRWindowUp;
Button_t RRWindowDown;
Button_t RLWindowUp;
Button_t RLWindowDown;
Button_t RWindow;
Button_t LockBtn;
Button_t UnlockBtn;


void ButtonManager_Init(void)
{
	VariantId = getVariantId();
  /* Button init */
	WindowUp.btn_counter = 0;
	WindowUp.debounce_started = false;
	WindowUp.readyProcessing = false;
	WindowDown.btn_counter = 0;
	WindowDown.debounce_started = false;
	WindowDown.readyProcessing = false;

	switch(VariantId)
	{
		case DriverDoor:
			/* Passenger */
			PsnWindowUp.btn_counter = 0;
			PsnWindowUp.debounce_started = false;
			PsnWindowUp.readyProcessing = false;

			PsnWindowDown.btn_counter = 0;
			PsnWindowDown.debounce_started = false;
			PsnWindowDown.readyProcessing = false;

			RRWindowUp.btn_counter = 0;
			RRWindowUp.debounce_started = false;
			RRWindowUp.readyProcessing = false;

			RRWindowDown.btn_counter = 0;
			RRWindowDown.debounce_started = false;
			RRWindowDown.readyProcessing = false;

			RLWindowUp.btn_counter = 0;
			RLWindowUp.debounce_started = false;
			RLWindowUp.readyProcessing = false;

			RLWindowDown.btn_counter = 0;
			RLWindowDown.debounce_started = false;
			RLWindowDown.readyProcessing = false;

			RWindow.btn_counter = 0;
			RWindow.debounce_started = false;
			RWindow.readyProcessing = false;

			LockBtn.btn_counter = 0;
			LockBtn.debounce_started = false;
			LockBtn.readyProcessing = false;

			UnlockBtn.btn_counter = 0;
			UnlockBtn.debounce_started = false;
			UnlockBtn.readyProcessing = false;

			btn_status.Win_Open = RELEASE;
			btn_status.Win_Close = RELEASE;
			btn_status.Psn_Open = RELEASE;
			btn_status.Psn_Close = RELEASE;
			btn_status.RR_Open = RELEASE;
			btn_status.RR_Close = RELEASE;
			btn_status.RL_Open = RELEASE;
			btn_status.RL_Close = RELEASE;
			btn_status.RWin_Lock = RELEASE;
			btn_status.Door_Lock = RELEASE;
			btn_status.Door_Unlock = RELEASE;

		break;

		case PassengerDoor:

			LockBtn.btn_counter = 0;
			LockBtn.debounce_started = false;
			LockBtn.readyProcessing = false;

			UnlockBtn.btn_counter = 0;
			UnlockBtn.debounce_started = false;
			UnlockBtn.readyProcessing = false;

			btn_status.Win_Open = RELEASE;
			btn_status.Win_Close = RELEASE;
			btn_status.Psn_Open = Not_Present;
			btn_status.Psn_Close = Not_Present;
			btn_status.RR_Open = Not_Present;
			btn_status.RR_Close = Not_Present;
			btn_status.RL_Open = Not_Present;
			btn_status.RL_Close = Not_Present;
			btn_status.RWin_Lock = Not_Present;
			btn_status.Door_Lock = RELEASE;
			btn_status.Door_Unlock = RELEASE;

		break;

		case RearLeftDoor:
		case RearRightDoor:

			btn_status.Win_Open = RELEASE;
			btn_status.Win_Close = RELEASE;
			btn_status.Psn_Open = Not_Present;
			btn_status.Psn_Close = Not_Present;
			btn_status.RR_Open = Not_Present;
			btn_status.RR_Close = Not_Present;
			btn_status.RL_Open = Not_Present;
			btn_status.RL_Close = Not_Present;
			btn_status.RWin_Lock = Not_Present;
			btn_status.Door_Lock = Not_Present;
			btn_status.Door_Unlock = Not_Present;

		break;

		default:
			/* Do nothing */
		break;
	}
}


void ButtonManager( void )
{
	/* Var for RWindow */
	static volatile bool RearLock = false;

	if((PINS_DRV_ReadPins(PTC) & (1<<WindowUp_btn)) && (btn_status.Win_Open != Not_Present) && (WindowUp.btn_counter<THRESHOLD_STUCK))
	{
		WindowUp.debounce_started = true;
		WindowUp.btn_counter++;
	}
	else if ((!(PINS_DRV_ReadPins(PTC) & (1<<WindowUp_btn)) || (WindowUp.btn_counter == THRESHOLD_STUCK)) && (btn_status.Win_Open != Not_Present) && WindowUp.debounce_started == true)
	{
		WindowUp.debounce_started = false;
		WindowUp.readyProcessing = true;
	}
	else
	{
		/* Do nothing */
	}

	if((PINS_DRV_ReadPins(PTC) & (1<<WindowDown_btn)) && (btn_status.Win_Close != Not_Present) && (WindowDown.btn_counter<THRESHOLD_STUCK))
	{
		WindowDown.debounce_started = true;
		WindowDown.btn_counter++;
	}
	else if ((!(PINS_DRV_ReadPins(PTC) & (1<<WindowDown_btn)) || (WindowDown.btn_counter == THRESHOLD_STUCK)) && (btn_status.Win_Close != Not_Present) && WindowDown.debounce_started == true)
	{
		WindowDown.debounce_started = false;
		WindowDown.readyProcessing = true;
	}
	else
	{
		/* Do nothing */
	}

	if(true == WindowUp.readyProcessing)
	{
		if(WindowUp.btn_counter >= THRESHOLD_SHORT && WindowUp.btn_counter <= THRESHOLD_LONG)
		{
			btn_status.Win_Open = SHORT;
			setManualFlag(true);
		}
		else if(WindowUp.btn_counter > THRESHOLD_LONG && WindowUp.btn_counter < THRESHOLD_STUCK)
		{
			btn_status.Win_Open = LONG;
			setManualFlag(true);
		}
		else if(WindowUp.btn_counter >= THRESHOLD_STUCK)
		{
			btn_status.Win_Open = STUCK;
			setManualFlag(true);
		}
		else if(WindowUp.btn_counter <= THRESHOLD_SHORT)
		{
			btn_status.Win_Open = RELEASE;
		}
		else
		{
			/* Do nothing */
		}
		WindowUp.btn_counter = 0;
		WindowUp.readyProcessing = false;
	}
	else if (true == WindowDown.readyProcessing)
	{
		if(WindowDown.btn_counter >= THRESHOLD_SHORT && WindowDown.btn_counter <= THRESHOLD_LONG)
		{
			btn_status.Win_Close = SHORT;
			setManualFlag(true);
		}
		else if(WindowDown.btn_counter > THRESHOLD_LONG && WindowDown.btn_counter < THRESHOLD_STUCK)
		{
			btn_status.Win_Close = LONG;
			setManualFlag(true);
		}
		else if(WindowDown.btn_counter >= THRESHOLD_STUCK)
		{
			btn_status.Win_Close = STUCK;
			setManualFlag(true);
		}
		else if(WindowDown.btn_counter <= THRESHOLD_SHORT)
		{
			btn_status.Win_Close = RELEASE;
		}
		else
		{
			/* Do nothing */
		}
		WindowDown.btn_counter = 0;
		WindowDown.readyProcessing = false;
   }
   else
   {
	   /* Do nothing */
   }

	switch(VariantId)
	{
		case DriverDoor:
			if((PINS_DRV_ReadPins(PTB) & (1<<PsnWindowUp_btn)) && (btn_status.Psn_Open != Not_Present) && (PsnWindowUp.btn_counter<THRESHOLD_STUCK))
			{
				PsnWindowUp.debounce_started = true;
				PsnWindowUp.btn_counter++;
			}
			else if ((!(PINS_DRV_ReadPins(PTB) & (1<<PsnWindowUp_btn)) || (PsnWindowUp.btn_counter >= THRESHOLD_STUCK)) && (btn_status.Psn_Open != Not_Present) && PsnWindowUp.debounce_started == true)
			{
				PsnWindowUp.debounce_started = false;
				PsnWindowUp.readyProcessing = true;
			}
			else
			{
				/* Do nothing */
			}
			if((PINS_DRV_ReadPins(PTB) & (1<<PsnWindowDown_btn)) && (btn_status.Psn_Close != Not_Present) && (PsnWindowDown.btn_counter<THRESHOLD_STUCK))
			{
				PsnWindowDown.debounce_started = true;
				PsnWindowDown.btn_counter++;
			}
			else if ((!(PINS_DRV_ReadPins(PTB) & (1<<PsnWindowDown_btn)) || (PsnWindowDown.btn_counter >= THRESHOLD_STUCK)) && (btn_status.Psn_Close != Not_Present) && PsnWindowDown.debounce_started == true)
			{
				PsnWindowDown.debounce_started = false;
				PsnWindowDown.readyProcessing = true;
			}
			else
			{
				/* Do nothing */
			}
			if((PINS_DRV_ReadPins(PTB) & (1<<RRWindowUp_btn)) && (btn_status.RR_Open != Not_Present) && (RRWindowUp.btn_counter<THRESHOLD_STUCK))
			{
				RRWindowUp.debounce_started = true;
				RRWindowUp.btn_counter++;
			}
			else if ((!(PINS_DRV_ReadPins(PTB) & (1<<RRWindowUp_btn)) || (RRWindowUp.btn_counter >= THRESHOLD_STUCK)) && (btn_status.RR_Open != Not_Present) && RRWindowUp.debounce_started == true)
			{
				RRWindowUp.debounce_started = false;
				RRWindowUp.readyProcessing = true;
			}
			else
			{
				/* Do nothing */
			}
			if((PINS_DRV_ReadPins(PTB) & (1<<RRWindowDown_btn)) && (btn_status.RR_Close != Not_Present) && (RRWindowDown.btn_counter<THRESHOLD_STUCK))
			{
				RRWindowDown.debounce_started = true;
				RRWindowDown.btn_counter++;
			}
			else if ((!(PINS_DRV_ReadPins(PTB) & (1<<RRWindowDown_btn)) || (RRWindowDown.btn_counter >= THRESHOLD_STUCK)) && (btn_status.RR_Close != Not_Present) && RRWindowDown.debounce_started == true)
			{
				RRWindowDown.debounce_started = false;
				RRWindowDown.readyProcessing = true;
			}
			else
			{
				/* Do nothing */
			}
			if((PINS_DRV_ReadPins(PTB) & (1<<RLWindowUp_btn)) && (btn_status.RL_Open != Not_Present) && (RLWindowUp.btn_counter<THRESHOLD_STUCK))
			{
				RLWindowUp.debounce_started = true;
				RLWindowUp.btn_counter++;
			}
			else if ((!(PINS_DRV_ReadPins(PTB) & (1<<RLWindowUp_btn)) || (RLWindowUp.btn_counter >= THRESHOLD_STUCK)) && (btn_status.RL_Open != Not_Present) && RLWindowUp.debounce_started == true)
			{
				RLWindowUp.debounce_started = false;
				RLWindowUp.readyProcessing = true;
			}
			else
			{
				/* Do nothing */
			}
			if((PINS_DRV_ReadPins(PTB) & (1<<RLWindowDown_btn)) && (btn_status.RL_Close != Not_Present) && (RLWindowDown.btn_counter<THRESHOLD_STUCK))
			{
				RLWindowDown.debounce_started = true;
				RLWindowDown.btn_counter++;
			}
			else if ((!(PINS_DRV_ReadPins(PTB) & (1<<RLWindowDown_btn)) || (RLWindowDown.btn_counter >= THRESHOLD_STUCK)) && (btn_status.RL_Close != Not_Present) && RLWindowDown.debounce_started == true)
			{
				RLWindowDown.debounce_started = false;
				RLWindowDown.readyProcessing = true;
			}
			else
			{
				/* Do nothing */
			}
			if((PINS_DRV_ReadPins(PTA) & (1<<RWindow_btn)) && (btn_status.RWin_Lock != Not_Present) && (RWindow.btn_counter<THRESHOLD_LOCK_UN) && (RearLock == false))
			{
				RWindow.debounce_started = true;
				RWindow.btn_counter++;
			}
			else if ((!(PINS_DRV_ReadPins(PTA) & (1<<RWindow_btn)) || (RWindow.btn_counter >= THRESHOLD_LOCK_UN)) && (btn_status.RWin_Lock != Not_Present) && (RearLock == true))
			{
				RWindow.debounce_started = true;
				RWindow.btn_counter=0;
				RearLock = false;
			}
			else if ((RWindow.debounce_started == true) && (btn_status.RWin_Lock != Not_Present))
			{
				RWindow.debounce_started = false;
				RWindow.readyProcessing = true;
			}
			else
			{
				/* Do nothing */
			}

			if((PINS_DRV_ReadPins(PTA) & (1<<LockBtn_btn)) && (btn_status.Door_Lock != Not_Present) && (LockBtn.btn_counter<THRESHOLD_STUCK))
			{
				LockBtn.debounce_started = true;
				LockBtn.btn_counter++;
			}
			else if ((!(PINS_DRV_ReadPins(PTA) & (1<<LockBtn_btn)) || (LockBtn.btn_counter >= THRESHOLD_STUCK)) && (btn_status.Door_Lock != Not_Present) && LockBtn.debounce_started == true)
			{
				LockBtn.debounce_started = false;
				LockBtn.readyProcessing = true;
			}
			else
			{
				/* Do nothing */
			}
			if((PINS_DRV_ReadPins(PTA) & (1<<UnlockBtn_btn)) && (btn_status.Door_Unlock != Not_Present) && (UnlockBtn.btn_counter<THRESHOLD_STUCK))
			{
				UnlockBtn.debounce_started = true;
				UnlockBtn.btn_counter++;
			}
			else if ((!(PINS_DRV_ReadPins(PTA) & (1<<UnlockBtn_btn)) || (UnlockBtn.btn_counter >= THRESHOLD_STUCK)) && (btn_status.Door_Unlock != Not_Present) && UnlockBtn.debounce_started == true)
			{
				UnlockBtn.debounce_started = false;
				UnlockBtn.readyProcessing = true;
			}
			else
			{
				/* Do nothing */
			}

			if(true == PsnWindowUp.readyProcessing)
			{
				if(PsnWindowUp.btn_counter >= THRESHOLD_SHORT && PsnWindowUp.btn_counter <= THRESHOLD_LONG)
				{
					btn_status.Psn_Open = SHORT;
					setManualFlag(true);
				}
				else if(PsnWindowUp.btn_counter > THRESHOLD_LONG && PsnWindowUp.btn_counter < THRESHOLD_STUCK)
				{
					btn_status.Psn_Open = LONG;
					setManualFlag(true);
				}
				else if(PsnWindowUp.btn_counter >= THRESHOLD_STUCK)
				{
					btn_status.Psn_Open = STUCK;
				}
				else if(PsnWindowUp.btn_counter <= THRESHOLD_SHORT)
				{
					btn_status.Psn_Open = RELEASE;
				}
				else
				{
					/* Do nothing */
				}
					PsnWindowUp.btn_counter = 0;
					PsnWindowUp.readyProcessing = false;
			}
			else if (true == PsnWindowDown.readyProcessing)
			{
				if(PsnWindowDown.btn_counter >= THRESHOLD_SHORT && PsnWindowDown.btn_counter <= THRESHOLD_LONG)
				{
					btn_status.Psn_Close = SHORT;
					setManualFlag(true);
				}
				else if (PsnWindowDown.btn_counter > THRESHOLD_LONG && PsnWindowDown.btn_counter < THRESHOLD_STUCK)
				{
					btn_status.Psn_Close = LONG;
					setManualFlag(true);
				}
				else if(PsnWindowDown.btn_counter >= THRESHOLD_STUCK)
				{
					btn_status.Psn_Close = STUCK;
				}
				else if(PsnWindowDown.btn_counter <= THRESHOLD_SHORT)
				{
					btn_status.Psn_Close = RELEASE;
				}
				else
				{
					/* Do nothing */
				}
					PsnWindowDown.btn_counter = 0;
					PsnWindowDown.readyProcessing = false;
		   }
			else if (true == RRWindowUp.readyProcessing)
			{
				if(RRWindowUp.btn_counter >= THRESHOLD_SHORT && RRWindowUp.btn_counter <= THRESHOLD_LONG)
				{
					btn_status.RR_Open = SHORT;
					setManualFlag(true);
				}
				else if (RRWindowUp.btn_counter > THRESHOLD_LONG && RRWindowUp.btn_counter < THRESHOLD_STUCK)
				{
					btn_status.RR_Open = LONG;
					setManualFlag(true);
				}
				else if(RRWindowUp.btn_counter >= THRESHOLD_STUCK)
				{
					btn_status.RR_Open = STUCK;
				}
				else if(RRWindowUp.btn_counter <= THRESHOLD_SHORT)
				{
					btn_status.RR_Open = RELEASE;
				}
				else
				{
					/* Do nothing */
				}
					RRWindowUp.btn_counter = 0;
					RRWindowUp.readyProcessing = false;
		   }
			else if (true == RRWindowDown.readyProcessing)
			{
				if(RRWindowDown.btn_counter >= THRESHOLD_SHORT && RRWindowDown.btn_counter <= THRESHOLD_LONG)
				{
					btn_status.RR_Close = SHORT;
					setManualFlag(true);
				}
				else if (RRWindowDown.btn_counter > THRESHOLD_LONG && RRWindowDown.btn_counter < THRESHOLD_STUCK)
				{
					btn_status.RR_Close = LONG;
					setManualFlag(true);
				}
				else if(RRWindowDown.btn_counter >= THRESHOLD_STUCK)
				{
					btn_status.RR_Close = STUCK;
				}
				else if(RRWindowDown.btn_counter <= THRESHOLD_SHORT)
				{
					btn_status.RR_Close = RELEASE;
				}
				else
				{
					/* Do nothing */
				}
					RRWindowDown.btn_counter = 0;
					RRWindowDown.readyProcessing = false;
		   }
			else if (true == RLWindowUp.readyProcessing)
			{
				if(RLWindowUp.btn_counter >= THRESHOLD_SHORT && RLWindowUp.btn_counter <= THRESHOLD_LONG)
				{
					btn_status.RL_Open = SHORT;
					setManualFlag(true);
				}
				else if (RLWindowUp.btn_counter > THRESHOLD_LONG && RLWindowUp.btn_counter < THRESHOLD_STUCK)
				{
					btn_status.RL_Open = LONG;
					setManualFlag(true);
				}
				else if(RLWindowUp.btn_counter >= THRESHOLD_STUCK)
				{
					btn_status.RL_Open = STUCK;
				}
				else if(RLWindowUp.btn_counter <= THRESHOLD_SHORT)
				{
					btn_status.RL_Open = RELEASE;
				}
				else
				{
					/* Do nothing */
				}
					RLWindowUp.btn_counter = 0;
					RLWindowUp.readyProcessing = false;
		   }
			else if (true == RLWindowDown.readyProcessing)
			{
				if(RLWindowDown.btn_counter >= THRESHOLD_SHORT && RLWindowDown.btn_counter <= THRESHOLD_LONG)
				{
					btn_status.RL_Close = SHORT;
					setManualFlag(true);
				}
				else if (RLWindowDown.btn_counter > THRESHOLD_LONG && RLWindowDown.btn_counter < THRESHOLD_STUCK)
				{
					btn_status.RL_Close = LONG;
					setManualFlag(true);
				}
				else if(RLWindowDown.btn_counter >= THRESHOLD_STUCK)
				{
					btn_status.RL_Close = STUCK;
				}
				else if(RLWindowDown.btn_counter <= THRESHOLD_SHORT)
				{
					btn_status.RL_Close = RELEASE;
				}
				else
				{
					/* Do nothing */
				}
					RLWindowDown.btn_counter = 0;
					RLWindowDown.readyProcessing = false;
			}
			else if (true == RWindow.readyProcessing)
			{
				if(RWindow.btn_counter >= THRESHOLD_LOCK_UN)
				{
					btn_status.RWin_Lock = LOCK;
					setManualFlag(true);
					RearLock = true;
				}
				else if(RWindow.btn_counter < THRESHOLD_LOCK_UN)
				{
					btn_status.RWin_Lock = RELEASE;
					setManualFlag(true);
					RearLock = false;
				}
					RWindow.btn_counter = 0;
					RWindow.readyProcessing = false;
			}
		   else
		   {
			   /* Do nothing */
		   }
			if(true == LockBtn.readyProcessing)
			{
				if(LockBtn.btn_counter >= THRESHOLD_STUCK)
				{
					btn_status.Door_Lock = LOCK;
					setManualFlag(true);
				}
				else if(LockBtn.btn_counter >= THRESHOLD_LOCK_UN)
				{
					btn_status.Door_Lock = STUCK;
					setManualFlag(true);
				}
				else if(LockBtn.btn_counter < THRESHOLD_LOCK_UN)
				{
					btn_status.Door_Lock = RELEASE;
				}
				else
				{
					/* Do nothing */
				}
				LockBtn.btn_counter = 0;
				LockBtn.readyProcessing = false;
			}
			else if (true == UnlockBtn.readyProcessing)
			{
				if(UnlockBtn.btn_counter >= THRESHOLD_STUCK)
				{
					btn_status.Door_Unlock = UNLOCK;
					setManualFlag(true);
				}
				else if(UnlockBtn.btn_counter >= THRESHOLD_LOCK_UN)
				{
					btn_status.Door_Lock = STUCK;
					setManualFlag(true);
				}
				else if(UnlockBtn.btn_counter < THRESHOLD_LOCK_UN)
				{
					btn_status.Door_Lock = RELEASE;
				}
				else
				{
					/* Do nothing */
				}
				UnlockBtn.btn_counter = 0;
				UnlockBtn.readyProcessing = false;
		   }
		   else
		   {
			   /* Do nothing */
		   }

		break;

		case PassengerDoor:
			if((PINS_DRV_ReadPins(PTA) & (1<<LockBtn_btn)) && (btn_status.Door_Lock != Not_Present) && (LockBtn.btn_counter<THRESHOLD_STUCK))
			{
				LockBtn.debounce_started = true;
				LockBtn.btn_counter++;
			}
			else if ((!(PINS_DRV_ReadPins(PTA) & (1<<LockBtn_btn)) || (LockBtn.btn_counter >= THRESHOLD_STUCK)) && (btn_status.Door_Lock != Not_Present) && LockBtn.debounce_started == true)
			{
				LockBtn.debounce_started = false;
				LockBtn.readyProcessing = true;
			}
			else
			{
				/* Do nothing */
			}
			if((PINS_DRV_ReadPins(PTA) & (1<<UnlockBtn_btn)) && (btn_status.Door_Unlock != Not_Present) && (UnlockBtn.btn_counter<THRESHOLD_STUCK))
			{
				UnlockBtn.debounce_started = true;
				UnlockBtn.btn_counter++;
			}
			else if ((!(PINS_DRV_ReadPins(PTA) & (1<<UnlockBtn_btn)) || (UnlockBtn.btn_counter >= THRESHOLD_STUCK)) && (btn_status.Door_Unlock != Not_Present) && UnlockBtn.debounce_started == true)
			{
				UnlockBtn.debounce_started = false;
				UnlockBtn.readyProcessing = true;
			}
			else
			{
				/* Do nothing */
			}
			if(true == LockBtn.readyProcessing)
			{
				if(LockBtn.btn_counter >= THRESHOLD_LOCK_UN)
				{
					btn_status.Door_Lock = LOCK;
					setManualFlag(true);
				}
				else if(UnlockBtn.btn_counter >= THRESHOLD_STUCK)
				{
					btn_status.Door_Lock = STUCK;
					setManualFlag(true);
				}
				else if(UnlockBtn.btn_counter < THRESHOLD_LOCK_UN)
				{
					btn_status.Door_Lock = RELEASE;
				}
				else
				{
					/* Do nothing */
				}
				LockBtn.btn_counter = 0;
				LockBtn.readyProcessing = false;
			}
			else if (true == UnlockBtn.readyProcessing)
			{
				if(UnlockBtn.btn_counter >= THRESHOLD_LOCK_UN)
				{
					btn_status.Door_Unlock = UNLOCK;
					setManualFlag(true);
				}
				else if(UnlockBtn.btn_counter >= THRESHOLD_STUCK)
				{
					btn_status.Door_Lock = STUCK;
					setManualFlag(true);
				}
				else if(UnlockBtn.btn_counter < THRESHOLD_LOCK_UN)
				{
					btn_status.Door_Lock = RELEASE;
				}
				else
				{
					/* Do nothing */
				}
				UnlockBtn.btn_counter = 0;
				UnlockBtn.readyProcessing = false;
		   }
		   else
		   {
			   /* Do nothing */
		   }

		break;
		case RearLeftDoor:
		case RearRightDoor:
		default:
			/* Do nothing */
		break;
	}

}

void setBtnList(Btn_list_t data)
{
	btn_status = data;
}

Btn_list_t getBtnList(void)
{
	return btn_status;
}
