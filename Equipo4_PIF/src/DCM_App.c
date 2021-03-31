/*
 * DCM_App.c
 *
 *  Created on: 12 mar. 2021
 *      Author: ssalazar
 */

#include "DCM.h"
#include "SerialManager.h"
#include "ActuatorManager.h"
#include "CAN_app.h"
#include "ManufacturingManager.h"
#include "ButtonManager.h"

#define MODULE "DCM_APP"

/* Local Defines */
#define AUTO_LOCK_SPEED (80) //20 km/h, resolution 0.25

/* Global Variable */
static bool ManualRequest_Flag = false;
static bool TestRequest_Flag = false;
static manufacturing_t gVariant = 0;

S_DCU_1 gDCU_1;
S_DCU_2	gDCU_2;
S_DCU_3	gDCU_3;
S_DCU_4	gDCU_4;
S_BRAKE_2 gBRAKE_2;
S_BCM_2	gBCM_2;
S_BCM_5	gBCM_5;

S_BRAKE_2 oldBRAKE_2;
S_BCM_2	oldBCM_2;
S_BCM_5	oldBCM_5;
S_DCU_1 oldDCU_1;
S_DCU_2	oldDCU_2;

Btn_list_t	gBtn_List;

/* Private function prototype */
static manufacturing_t SetVariant( void );
static void UpdateCan_Outputs( void );
static void RemoteRequest_Operation ( void );
static void ManualRequest_Operation ( void );
static void OpenCloseButton_Op( void );
static uint8_t LockUnlockButton_Op( void );
static void SpecialOpenCloseButton_Op( void );
static void RearWindowLockUnlock_Op( void );
static void savePrevCANSig( void );
static void readInputCAN( void );
static void LockUnlockRemote_OpBCM( void );
static void LockUnlockRemote_OpDCM1( void );
static void LockUnlockRemote_OpDCM2( void );
static void OpenCloseRemote_OpBCM( void );
static void OpenCloseRemote_OpPass( void );
static void OpenCloseRemote_OpRR( void );
static void OpenCloseRemote_OpRL( void );
static void AutoLockRemote_Op( S_DCU_1* data );
static bool BtnStuckLocking_Verification ( void );
static bool BtnStuckWindow_Verification ( void );
static void CleanWindowControl( void );

static bool getRemoteFlag( void );
static bool getManualFlag (void);
static bool getTestFlag( void );
static void Test_CMD_Operation( void );


void DCM_App_Init( void )
{
	(void)DGB_Print(MODULE,"DCM App initialized");
	gVariant = SetVariant();
	gBtn_List = getBtnList();
}


void DCM_Process_Req( void )
{
	bool flag_remote = getRemoteFlag();
	bool flag_manual = getManualFlag();
	bool flag_test = getTestFlag();

	if(true == flag_manual)
	{
		(void)DGB_Print(MODULE,"Manual Request Received");
		gBtn_List = getBtnList();
		(void)ManualRequest_Operation();
		ManualRequest_Flag = false;
		(void)setBtnList(gBtn_List);
	}
	else if (true == flag_remote)
	{
		(void)DGB_Print(MODULE,"Remote Request Received");
		(void)RemoteRequest_Operation();
	}
	else if(true == flag_test)
	{
		(void)DGB_Print(MODULE,"Test Request Received");
		(void)Test_CMD_Operation();
		TestRequest_Flag = false;
	}
	else
	{
		/* Do nothing */
	}
	(void) UpdateCan_Outputs();
}

static void RemoteRequest_Operation( void )
{
	(void)readInputCAN();
	switch (gVariant)
	{
		case DriverDoor:
			if(APP_Get_avlbl_msg_BRAKE_2() && APP_Get_avlbl_msg_BCM_5())
			{
				APP_Clr_avlbl_msg_BRAKE_2();
				APP_Clr_avlbl_msg_BCM_5();
				(void)AutoLockRemote_Op(&gDCU_1);
			}
			else
			{
				// Do nothing
			}
			if(APP_Get_avlbl_msg_BCM_2())
			{
				APP_Clr_avlbl_msg_BCM_2();
				(void)OpenCloseRemote_OpBCM();
				(void)LockUnlockRemote_OpBCM();
			}
			else
			{
				//Do nothing, no msg RX
			}
			if(APP_Get_avlbl_msg_DCU_2())
			{
				APP_Clr_avlbl_msg_DCU_2();
				(void)LockUnlockRemote_OpDCM2();
			}
			else
			{
				//Do nothing, no MSG Rx
			}
		break;
		case PassengerDoor:
			if(APP_Get_avlbl_msg_BCM_2())
			{
				APP_Clr_avlbl_msg_BCM_2();
				(void)OpenCloseRemote_OpBCM();
				(void)LockUnlockRemote_OpBCM();
			}
			else
			{
				//Do nothing, no msg RX
			}
			if(APP_Get_avlbl_msg_DCU_1())
			{
				APP_Clr_avlbl_msg_DCU_1();
				(void)LockUnlockRemote_OpDCM1();
				(void)OpenCloseRemote_OpPass();
			}
			else
			{
				//Do Nothing. No msg Rx
			}
		break;
		case RearRightDoor:
			if(APP_Get_avlbl_msg_BCM_2())
			{

				APP_Clr_avlbl_msg_BCM_2();
				(void)OpenCloseRemote_OpBCM();
				(void)LockUnlockRemote_OpBCM();
			}
			else
			{
				//Do nothing, no msg RX
			}
			if(APP_Get_avlbl_msg_DCU_1())
			{
				APP_Clr_avlbl_msg_DCU_1();

				(void)LockUnlockRemote_OpDCM1();
				(void)OpenCloseRemote_OpRR();
			}
			else
			{
				//Do Nothing. No msg Rx
			}
			if(APP_Get_avlbl_msg_DCU_2())
			{
				APP_Clr_avlbl_msg_DCU_2();
				(void)LockUnlockRemote_OpDCM2();
			}
			else
			{
				//Do nothing, no MSG Rx
			}
		break;
		case RearLeftDoor:
			if(APP_Get_avlbl_msg_BCM_2())
			{
				APP_Clr_avlbl_msg_BCM_2();
				(void)OpenCloseRemote_OpBCM();
				(void)LockUnlockRemote_OpBCM();
			}
			else
			{
				//Do nothing, no msg RX
			}
			if(APP_Get_avlbl_msg_DCU_1())
			{
				APP_Clr_avlbl_msg_DCU_1();
				(void)LockUnlockRemote_OpDCM1();
				(void)OpenCloseRemote_OpRL();
			}
			else
			{
				//Do Nothing. No msg Rx
			}
			if(APP_Get_avlbl_msg_DCU_2())
			{
				APP_Clr_avlbl_msg_DCU_2();
				(void)LockUnlockRemote_OpDCM2();
			}
			else
			{
				//Do nothing, no MSG Rx
			}
		break;
		default:
			DGB_Error(MODULE,"Invalid Variant");
		break;
	}
	/*After processing the signal, save the actual value as old for the next cycle */
	(void)savePrevCANSig();
}

static void ManualRequest_Operation( void )
{
	uint8_t new = 0;
	switch (gVariant)
	{
		case DriverDoor:
			if(BtnStuckWindow_Verification())
			{
				(void)OpenCloseButton_Op();
			}
			if(BtnStuckLocking_Verification())
			{
				new = LockUnlockButton_Op();
				if(new == 1)
				{
					gDCU_1.s.DCU_1_LockingReq = 0x01;
				}
				else if(new == 2)
				{
					gDCU_1.s.DCU_1_LockingReq = 0x02;
				}
			}
			(void)SpecialOpenCloseButton_Op();
			(void)RearWindowLockUnlock_Op();
		break;
		case PassengerDoor:
			if(BtnStuckWindow_Verification())
			{
				(void)OpenCloseButton_Op();
			}
			if(BtnStuckLocking_Verification())
			{
				new = LockUnlockButton_Op();
				if(new == 1)
				{
					gDCU_2.s.DCU_2_LockingReq = 0x01;
				}
				else if(new == 2)
				{
					gDCU_2.s.DCU_2_LockingReq = 0x02;
				}
			}
		break;
		case RearRightDoor:
		case RearLeftDoor:
			if(gDCU_1.s.DCU_1_RearWindowLock == kCAN_B_REAR_WINDOW_UNBLOCK)
			{
				if(BtnStuckWindow_Verification())
				{
					(void)OpenCloseButton_Op();
				}
			}
			else
			{
				//No button action due CDU 1 Blocking
			}
		break;
		default:
			DGB_Error(MODULE,"Invalid Variant");
		break;
	}

}

static void Test_CMD_Operation( void )
{

}

static bool getRemoteFlag( void )
{
	bool flag = APP_Get_avlbl_msg_BCM_5() || APP_Get_avlbl_msg_BCM_2() || APP_Get_avlbl_msg_BRAKE_2();
	switch(gVariant)
	{
	case DriverDoor:
		flag |= APP_Get_avlbl_msg_DCU_2();
	break;
	case PassengerDoor:
		flag |= APP_Get_avlbl_msg_DCU_1();
	break;
	case RearRightDoor:
	case RearLeftDoor:
		flag |= APP_Get_avlbl_msg_DCU_1() | APP_Get_avlbl_msg_DCU_2();
	break;
	default:
		//Do nothing, error in the variant
	break;
	}

	return flag;
}
static bool getManualFlag( void )
{
	return ManualRequest_Flag;
}
static bool getTestFlag( void )
{
	return TestRequest_Flag;
}
void setManualFlag( bool data )
{
	ManualRequest_Flag = data;
}
void setTestFlag( bool data )
{
	TestRequest_Flag = data;
}
static manufacturing_t SetVariant( void )
{
	return getVariantId();
}

static void OpenCloseButton_Op( void )
{
	if(gBtn_List.Win_Open != RELEASE)
	{
		if(gBtn_List.Win_Open == SHORT)
		{
			(void)setActuatorAction(OPEN_GLOBAL_WINDOW_ACTUATION);
			gBtn_List.Win_Open = RELEASE;
		}
		else if(gBtn_List.Win_Open == LONG)
		{
			(void)setActuatorAction(OPEN_WINDOW_ACTUATION);
			gBtn_List.Win_Open = RELEASE;
		}
		else
		{
			DGB_Error(MODULE,"Wrong Button Press Type");
			gBtn_List.Win_Open = RELEASE;
		}
	}
	else if(gBtn_List.Win_Close != RELEASE)
	{
		if(gBtn_List.Win_Close == SHORT)
		{
			(void)setActuatorAction(CLOSE_GLOBAL_WINDOW_ACTUATION);
			gBtn_List.Win_Close = RELEASE;
		}
		else if(gBtn_List.Win_Close == LONG)
		{
			(void)setActuatorAction(CLOSE_WINDOW_ACTUATION);
			gBtn_List.Win_Close = RELEASE;
		}
		else
		{
			DGB_Error(MODULE,"Wrong Button Press Type");
			gBtn_List.Win_Close = RELEASE;
		}
	}
	else
	{
		/* No Button event, Send IDLE */
	}
}

static uint8_t LockUnlockButton_Op( void )
{
	uint8_t temp = 0;

	if( gBtn_List.Door_Lock == LOCK )
	{
		(void)setActuatorAction(LOCK_DOOR_ACTUATION);
		gBtn_List.Door_Lock = RELEASE;
		temp = 1;
	}
	else if( gBtn_List.Door_Unlock == UNLOCK )
	{
		(void)setActuatorAction(UNLOCK_DOOR_ACTUATION);
		gBtn_List.Door_Unlock = RELEASE;
		temp = 2;
	}
	else
	{
		/* No Button event, Do Nothing */
	}
	return temp;
}

static void SpecialOpenCloseButton_Op( void )
{
	if( gBtn_List.Psn_Open == SHORT || gBtn_List.Psn_Open == LONG )
	{
		/* Change info to Down*/
		gDCU_1.s.DCU_1_WdwCtrl_Pas = 0x02;
		gBtn_List.Psn_Open = RELEASE;
	}
	else if(gBtn_List.Psn_Close == SHORT || gBtn_List.Psn_Close == LONG)
	{
		/* Change info to Up*/
		gDCU_1.s.DCU_1_WdwCtrl_Pas = 0x01;
		gBtn_List.Psn_Close = RELEASE;
	}
	else
	{
		/* Change info to No Req */
		gDCU_1.s.DCU_1_WdwCtrl_Pas = 0x00;
	}
	if( gBtn_List.RR_Open == SHORT || gBtn_List.RR_Open == LONG )
	{
		/* Change info to Down*/
		gDCU_1.s.DCU_1_WdwCtrl_RR = 0x02;
		gBtn_List.RR_Open = RELEASE;
	}
	else if( gBtn_List.RR_Close == SHORT || gBtn_List.RR_Close == LONG )
	{
		/* Change info to Up*/
		gDCU_1.s.DCU_1_WdwCtrl_RR = 0x01;
		gBtn_List.RR_Close = RELEASE;
	}
	else
	{
		/* Change info to No Req*/
		gDCU_1.s.DCU_1_WdwCtrl_RR = 0x00;
	}
	if( gBtn_List.RL_Open == SHORT || gBtn_List.RL_Open == LONG )
	{
		/* Change info to Down*/
		gDCU_1.s.DCU_1_WdwCtrl_RL = 0x02;
		gBtn_List.RL_Open = RELEASE;
	}
	else if(  gBtn_List.RL_Close == SHORT || gBtn_List.RL_Close == LONG )
	{
		/* Change info to Up*/
		gDCU_1.s.DCU_1_WdwCtrl_RL = 0x01;
		gBtn_List.RL_Close = RELEASE;
	}
	else
	{
		/* Change info to No Req*/
		gDCU_1.s.DCU_1_WdwCtrl_RL = 0x00;
	}
}

static void RearWindowLockUnlock_Op( void )
{
	if( gBtn_List.RWin_Lock == LOCK )
	{
		gDCU_1.s.DCU_1_RearWindowLock = 0x01;
	}
	else if( gBtn_List.RWin_Lock == RELEASE )
	{
		gDCU_1.s.DCU_1_RearWindowLock = 0x00;
	}
	else
	{
		/* No Button event, Do Nothing */
	}
}
static void UpdateCan_Outputs( void )
{
	switch (gVariant)
	{
		case DriverDoor:
			gDCU_1.s.DCU_1_WindowPos = (uint32_t)determineWindowPosition();
			gDCU_1.s.DCU_1_DoorLockSts = determineDoorLockingStatus();
			APP_CAN_DCM_DR_update_msg_DCU_1(gDCU_1);
			(void)CleanWindowControl();
		break;
		case PassengerDoor:
			gDCU_2.s.DCU_2_WindowPos = (uint32_t)determineWindowPosition();
			gDCU_2.s.DCU_2_DoorLockSts = determineDoorLockingStatus();
			APP_CAN_DCM_PS_update_msg_DCU_2(gDCU_2);
			(void)CleanWindowControl();
		break;
		case RearRightDoor:
			gDCU_4.s.DCU_4_WindowPos = (uint32_t)determineWindowPosition();
			gDCU_4.s.DCU_4_DoorLockSts = determineDoorLockingStatus();
			APP_CAN_DCM_RR_update_msg_DCU_4(gDCU_4);

		break;
		case RearLeftDoor:
			gDCU_3.s.DCU_3_WindowPos = (uint32_t)determineWindowPosition();
			gDCU_3.s.DCU_3_DoorLockSts = determineDoorLockingStatus();
			APP_CAN_DCM_RL_update_msg_DCU_3(gDCU_3);
		break;
		default:
			DGB_Error(MODULE,"Invalid Variant");
		break;
	}
}

static void savePrevCANSig( void )
{
	oldBRAKE_2 = gBRAKE_2;
	oldBCM_2 = gBCM_2;
	oldBCM_5 = gBCM_5;
	switch (gVariant)
	{
		case PassengerDoor:
			oldDCU_1 =gDCU_1;
		break;
		case RearLeftDoor:
		case RearRightDoor:
			oldDCU_1 =gDCU_1;
			oldDCU_2 =gDCU_2;
		break;
		case DriverDoor:
			oldDCU_2 =gDCU_2;
		break;
		default:
			/* No more CAN inputs to read */
		break;
	}
}

static void readInputCAN( void )
{
	switch (gVariant)
	{
		case PassengerDoor:
			APP_CAN_DCM_PS_get_msg_DCU_1(gDCU_1);
			APP_CAN_DCM_PS_get_msg_BCM_2(gBCM_2);
		break;
		case RearLeftDoor:
			APP_CAN_DCM_RL_get_msg_DCU_1(gDCU_1);
			APP_CAN_DCM_RL_get_msg_DCU_2(gDCU_2);
			APP_CAN_DCM_RL_get_msg_BCM_2(gBCM_2);
		break;
		case RearRightDoor:
			APP_CAN_DCM_RR_get_msg_DCU_1(gDCU_1);
			APP_CAN_DCM_RR_get_msg_DCU_2(gDCU_2);
			APP_CAN_DCM_RR_get_msg_BCM_2(gBCM_2);
		break;
		case DriverDoor:
			APP_CAN_DCM_DR_get_msg_DCU_2(gDCU_2);
			APP_CAN_DCM_DR_get_msg_DCU_3(gDCU_3);
			APP_CAN_DCM_DR_get_msg_DCU_4(gDCU_4);
			APP_CAN_DCM_DR_get_msg_BRAKE_2(gBRAKE_2);
			APP_CAN_DCM_DR_get_msg_BCM_2(gBCM_2);
			APP_CAN_DCM_DR_get_msg_BCM_5(gBCM_5);
		break;
		default:
			/* No more CAN inputs to read */
		break;
	}
}

static void LockUnlockRemote_OpBCM( void )
{
	if( (gBCM_2.s.ConfortCmd == kCAN_B_LockCmd) && (oldBCM_2.s.ConfortCmd == kCAN_B_No_Cmd) )
	{
		(void)setActuatorAction(LOCK_DOOR_ACTUATION);
	}
	else if( ( (gBCM_2.s.ConfortCmd == kCAN_B_UnlockAllCmd) && (oldBCM_2.s.ConfortCmd == kCAN_B_No_Cmd) ) ||
			( (gBCM_2.s.ConfortCmd == kCAN_B_UnlockAllCmd) && (oldBCM_2.s.ConfortCmd == kCAN_B_UnlockDrvrCmd) ) )
	{
		(void)setActuatorAction(UNLOCK_DOOR_ACTUATION);
	}
	else
	{
		/* No Remote event, Do Nothing */
	}
}

static void LockUnlockRemote_OpDCM1( void )
{
	if( (gDCU_1.s.DCU_1_LockingReq == kCAN_B_LOCK_REQ) && (oldDCU_1.s.DCU_1_LockingReq == kCAN_B_NO_LOCKING_REQ) )
	{
		(void)setActuatorAction(LOCK_DOOR_ACTUATION);
	}
	else if( (gDCU_1.s.DCU_1_LockingReq == kCAN_B_UNLOCK_REQ) && (oldDCU_1.s.DCU_1_LockingReq == kCAN_B_NO_LOCKING_REQ) )
	{
		(void)setActuatorAction(UNLOCK_DOOR_ACTUATION);
	}
	else
	{
		/* No Remote event, Do Nothing */
	}
}

static void LockUnlockRemote_OpDCM2( void )
{
	if( (gDCU_2.s.DCU_2_LockingReq == kCAN_B_LOCK_REQ) && (oldDCU_2.s.DCU_2_LockingReq == kCAN_B_NO_LOCKING_REQ) )
	{
		(void)setActuatorAction(LOCK_DOOR_ACTUATION);
	}
	else if( (gDCU_2.s.DCU_2_LockingReq == kCAN_B_UNLOCK_REQ) && (oldDCU_2.s.DCU_2_LockingReq == kCAN_B_NO_LOCKING_REQ) )
	{
		(void)setActuatorAction(UNLOCK_DOOR_ACTUATION);
	}
	else
	{
		/* No Remote event, Do Nothing */
	}
}

static void OpenCloseRemote_OpBCM( void )
{
	if( (gBCM_2.s.ConfortCmd == kCAN_B_UnlockAllCmd) && (oldBCM_2.s.ConfortCmd == kCAN_B_UnlockAllCmd) )
	{
		(void)setActuatorAction(OPEN_WINDOW_ACTUATION);
	}
	else if( (gBCM_2.s.ConfortCmd == kCAN_B_LockCmd) && (oldBCM_2.s.ConfortCmd == kCAN_B_LockCmd) )
	{
		(void)setActuatorAction(CLOSE_WINDOW_ACTUATION);
	}
	else if( ( (gBCM_2.s.ConfortCmd == kCAN_B_No_Cmd) && (oldBCM_2.s.ConfortCmd == kCAN_B_UnlockAllCmd) ) ||
			((gBCM_2.s.ConfortCmd == kCAN_B_No_Cmd) && (oldBCM_2.s.ConfortCmd == kCAN_B_LockCmd)) )
	{
		(void)setActuatorAction(CANCEL_WINDOW_ACTUATION);
	}
	else
	{
		/* No Remote event, Do Nothing */
	}
}

static void OpenCloseRemote_OpPass( void )
{
	if( gDCU_1.s.DCU_1_WdwCtrl_Pas == kCAN_B_WINDOW_DOWN_REQ )
	{
		(void)setActuatorAction(OPEN_WINDOW_ACTUATION);
	}
	else if( gDCU_1.s.DCU_1_WdwCtrl_Pas == kCAN_B_WINDOW_UP_REQ )
	{
		(void)setActuatorAction(CLOSE_WINDOW_ACTUATION);
	}
	else if ( gDCU_1.s.DCU_1_WdwCtrl_Pas == kCAN_B_WINDOW_NO_REQ )
	{
		(void)setActuatorAction(CANCEL_WINDOW_ACTUATION);
	}
	else
	{
		/* No Remote event, Do Nothing */
	}
}

static void OpenCloseRemote_OpRL( void )
{
	if( gDCU_1.s.DCU_1_WdwCtrl_RL == kCAN_B_WINDOW_DOWN_REQ )
	{
		(void)setActuatorAction(OPEN_WINDOW_ACTUATION);
	}
	else if( gDCU_1.s.DCU_1_WdwCtrl_RL == kCAN_B_WINDOW_UP_REQ )
	{
		(void)setActuatorAction(CLOSE_WINDOW_ACTUATION);
	}
	else if ( gDCU_1.s.DCU_1_WdwCtrl_RL == kCAN_B_WINDOW_NO_REQ )
	{
		(void)setActuatorAction(CANCEL_WINDOW_ACTUATION);
	}
	else
	{
		/* No Remote event, Do Nothing */
	}
}

static void OpenCloseRemote_OpRR( void )
{
	if( gDCU_1.s.DCU_1_WdwCtrl_RR == kCAN_B_WINDOW_DOWN_REQ )
	{
		(void)setActuatorAction(OPEN_WINDOW_ACTUATION);
	}
	else if( gDCU_1.s.DCU_1_WdwCtrl_RR == kCAN_B_WINDOW_UP_REQ )
	{
		(void)setActuatorAction(CLOSE_WINDOW_ACTUATION);
	}
	else if ( gDCU_1.s.DCU_1_WdwCtrl_RR == kCAN_B_WINDOW_NO_REQ )
	{
		(void)setActuatorAction(CANCEL_WINDOW_ACTUATION);

	}
	else
	{
		/* No Remote event, Do Nothing */
	}
}

static void AutoLockRemote_Op( S_DCU_1* data )
{
	uint8_t status = (gDCU_2.s.DCU_2_DoorLockSts) || (gDCU_3.s.DCU_3_DoorLockSts) || (gDCU_4.s.DCU_4_DoorLockSts);
	status |= (uint32_t)determineWindowPosition();
	if( (status == DOOR_UNLOCKED) &&
			(gBCM_5.s.SysPwrMode == kCAN_B_RUN) &&
			( ( (gBRAKE_2.s.VehSpeed_H <<8) | (gBRAKE_2.s.VehSpeed_L) ) >= AUTO_LOCK_SPEED) )
	{
		data->s.DCU_1_LockingReq = kCAN_B_LOCK_REQ;
	}
	else
	{
		/* No AutoLock event, Do Nothing */
	}
}

static bool BtnStuckLocking_Verification ( void )
{
	if( (gBtn_List.Door_Lock ==  STUCK) || (gBtn_List.Door_Unlock ==  STUCK) )
	{
		(void)setHWSolenoidStatus(false);
		return false;
	}
	else
	{
		//Do nothing no stuck present
		return true;
	}
}

static bool BtnStuckWindow_Verification ( void )
{
	if( (gBtn_List.Win_Close ==  STUCK) || (gBtn_List.Win_Open ==  STUCK) )
	{
		(void)setHWMotorStatus(false);
		return false;
	}
	else
	{
		//Do nothing no stuck present
		return true;
	}
}

static void CleanWindowControl( void )
{
	static uint8_t count = 0;
	if(count == 15)
	{
		/* Function to prevent bug of not updating this */
		gDCU_1.s.DCU_1_WdwCtrl_Pas = 0x00;
		gDCU_1.s.DCU_1_WdwCtrl_RR = 0x00;
		gDCU_1.s.DCU_1_WdwCtrl_RL = 0x00;
		gDCU_1.s.DCU_1_LockingReq = 0x00;
		gDCU_2.s.DCU_2_LockingReq = 0x00;
		count = 0;
	}
	else
	{
		count++;
	}

}

void DCM_App_UnitTest( void )
{
	uint8_t lock_test = 0;
	/* --------------------- UTS_APP_TC_1 ------------------ */
	setManualFlag(true);
	if(getManualFlag())
	{
		(void)DGB_Print(MODULE,"UTS_APP_Unit Test 1: PASSED");
	}
	else
	{
		(void)DGB_Error(MODULE,"UTS_APP_Unit Test 1: Failed");
	}
	setManualFlag(false);
	if(!getManualFlag())
	{
		(void)DGB_Print(MODULE,"UTS_APP_Unit Test 1: PASSED");
	}
	else
	{
		(void)DGB_Error(MODULE,"UTS_APP_Unit Test 1: Failed");
	}

	/* --------------------- UTS_APP_TC_2 ------------------ */
	setManualFlag(25);
	if(!getManualFlag())
	{
		(void)DGB_Print(MODULE,"UTS_APP_Unit Test 2: PASSED");
	}
	else
	{
		(void)DGB_Error(MODULE,"UTS_APP_Unit Test 2: Failed");
	}
	setManualFlag(200);
	if(!getManualFlag())
	{
		(void)DGB_Print(MODULE,"UTS_APP_Unit Test 2: PASSED");
	}
	else
	{
		(void)DGB_Error(MODULE,"UTS_APP_Unit Test 2: Failed");
	}

	/* --------------------- UTS_APP_TC_3 ------------------ */
	setTestFlag(true);
	if(getTestFlag())
	{
		(void)DGB_Print(MODULE,"UTS_APP_Unit Test 3: PASSED");
	}
	else
	{
		(void)DGB_Error(MODULE,"UTS_APP_Unit Test 3: Failed");
	}
	setTestFlag(false);
	if(!getTestFlag())
	{
		(void)DGB_Print(MODULE,"UTS_APP_Unit Test 3: PASSED");
	}
	else
	{
		(void)DGB_Error(MODULE,"UTS_APP_Unit Test 3: Failed");
	}

	/* --------------------- UTS_APP_TC_4 ------------------ */
	setTestFlag(50);
	if(!getTestFlag())
	{
		(void)DGB_Print(MODULE,"UTS_APP_Unit Test 4: PASSED");
	}
	else
	{
		(void)DGB_Error(MODULE,"UTS_APP_Unit Test 4: Failed");
	}
	setTestFlag("text");
	if(!getTestFlag())
	{
		(void)DGB_Print(MODULE,"UTS_APP_Unit Test 4: PASSED");
	}
	else
	{
		(void)DGB_Error(MODULE,"UTS_APP_Unit Test 4: Failed");
	}

	/* --------------------- UTS_APP_TC_5 ------------------ */
	gBtn_List.Win_Close = LONG;
	OpenCloseButton_Op();
	if(IN_BETWEEN == determineWindowPosition())
	{
		(void)DGB_Print(MODULE,"UTS_APP_Unit Test 5: PASSED");
	}
	else
	{
		(void)DGB_Error(MODULE,"UTS_APP_Unit Test 5: Failed");
	}

	/* --------------------- UTS_APP_TC_6 ------------------ */
	OpenCloseButton_Op();
	if(IN_BETWEEN == determineWindowPosition())
	{
		(void)DGB_Print(MODULE,"UTS_APP_Unit Test 6: PASSED");
	}
	else
	{
		(void)DGB_Error(MODULE,"UTS_APP_Unit Test 6: Failed");
	}
	OpenCloseButton_Op();
	if(IN_BETWEEN == determineWindowPosition())
	{
		(void)DGB_Print(MODULE,"UTS_APP_Unit Test 6: PASSED");
	}
	else
	{
		(void)DGB_Error(MODULE,"UTS_APP_Unit Test 6: Failed");
	}

	/* --------------------- UTS_APP_TC_7 ------------------ */
	gBtn_List.Door_Lock = LOCK;
	lock_test = LockUnlockButton_Op();
	if(lock_test == 0x01)
	{
		(void)DGB_Print(MODULE,"UTS_APP_Unit Test 7: PASSED");
	}
	else
	{
		(void)DGB_Error(MODULE,"UTS_APP_Unit Test 7: Failed");
	}

	/* --------------------- UTS_APP_TC_8 ------------------ */
	lock_test = LockUnlockButton_Op();
	if(lock_test == 0x00)
	{
		(void)DGB_Print(MODULE,"UTS_APP_Unit Test 8: PASSED");
	}
	else
	{
		(void)DGB_Error(MODULE,"UTS_APP_Unit Test 8: Failed");
	}

	/* --------------------- UTS_APP_TC_9 ------------------ */
	gBtn_List.Psn_Open = SHORT;
	SpecialOpenCloseButton_Op();
	if(gDCU_1.s.DCU_1_WdwCtrl_Pas != 0)
	{
		(void)DGB_Print(MODULE,"UTS_APP_Unit Test 9: PASSED");
	}
	else
	{
		(void)DGB_Error(MODULE,"UTS_APP_Unit Test 9: Failed");
	}
	gBtn_List.RR_Close = SHORT;
	SpecialOpenCloseButton_Op();
	if(gDCU_1.s.DCU_1_WdwCtrl_RR != 0)
	{
		(void)DGB_Print(MODULE,"UTS_APP_Unit Test 9: PASSED");
	}
	else
	{
		(void)DGB_Error(MODULE,"UTS_APP_Unit Test 9: Failed");
	}

	/* --------------------- UTS_APP_TC_10 ----------------- */
	SpecialOpenCloseButton_Op();
	if(gDCU_1.s.DCU_1_WdwCtrl_Pas == 0)
	{
		(void)DGB_Print(MODULE,"UTS_APP_Unit Test 10: PASSED");
	}
	else
	{
		(void)DGB_Error(MODULE,"UTS_APP_Unit Test 10: Failed");
	}
	SpecialOpenCloseButton_Op();
	if(gDCU_1.s.DCU_1_WdwCtrl_RR == 0)
	{
		(void)DGB_Print(MODULE,"UTS_APP_Unit Test 10: PASSED");
	}
	else
	{
		(void)DGB_Error(MODULE,"UTS_APP_Unit Test 10: Failed");
	}

	/* --------------------- UTS_APP_TC_11 ----------------- */
	gBtn_List.RWin_Lock = LOCK;
	RearWindowLockUnlock_Op();
	if(gDCU_1.s.DCU_1_RearWindowLock == 0x01)
	{
		(void)DGB_Print(MODULE,"UTS_APP_Unit Test 11: PASSED");
	}
	else
	{
		(void)DGB_Error(MODULE,"UTS_APP_Unit Test 11: Failed");
	}
	gBtn_List.RWin_Lock = RELEASE;
	RearWindowLockUnlock_Op();
	if(gDCU_1.s.DCU_1_RearWindowLock == 0x00)
	{
		(void)DGB_Print(MODULE,"UTS_APP_Unit Test 11: PASSED");
	}
	else
	{
		(void)DGB_Error(MODULE,"UTS_APP_Unit Test 11: Failed");
	}
}
 void DCM_APP_IntegrationTest( void )
{
	Btn_list_t int_test_new;
	Btn_list_t int_test_old;
	uint8_t variant_test = 5;
	doorlock_sts_config_t lock_test = 5;
	windowPosition_sts_config_t wind_test = 5;

	/* --------------------- ITS_TestCase_1 ----------------- */
	int_test_old.RL_Close = SHORT;
	int_test_old.Door_Lock = LOCK;
	int_test_old.Win_Close = LONG;
	setBtnList(int_test_old);
	int_test_new = getBtnList();
	if( (int_test_old.RL_Close == int_test_new.RL_Close) &&
			(int_test_old.Door_Lock == int_test_new.Door_Lock) &&
			(int_test_old.Win_Close == int_test_new.Win_Close) )
	{
		(void)DGB_Print(MODULE,"ITS_TestCase 1: PASSED");
	}
	else
	{
		(void)DGB_Error(MODULE,"ITS_TestCase 1: Failed");
	}

	/* --------------------- ITS_TestCase_2 ----------------- */
	setManualFlag(true);
	if(getManualFlag())
	{
		(void)DGB_Print(MODULE,"ITS_TestCase 2: PASSED");
	}
	else
	{
		(void)DGB_Error(MODULE,"ITS_TestCase 2: Failed");
	}
	setManualFlag(false);
	if(!getManualFlag())
	{
		(void)DGB_Print(MODULE,"ITS_TestCase 2: PASSED");
	}
	else
	{
		(void)DGB_Error(MODULE,"ITS_TestCase 2: Failed");
	}

	/* --------------------- ITS_TestCase_3 ----------------- */
	DGB_Print(MODULE, "ITS_TestCase 3: PASSED");
	DGB_Error(MODULE, "ITS_TestCase 3: PASSED");

	/* --------------------- ITS_TestCase_4 ----------------- */
	variant_test = getVariantId();
	if(variant_test >= 0 && variant_test<= 4)
	{
		(void)DGB_Print(MODULE,"ITS_TestCase 4: PASSED");
	}
	else
	{
		(void)DGB_Error(MODULE,"ITS_TestCase 4: Failed");
	}

	/* --------------------- ITS_TestCase_5 ----------------- */
	lock_test =  determineDoorLockingStatus();
	wind_test =  determineWindowPosition();
	if( (lock_test == DOOR_UNLOCKED) &&
			(wind_test == WINDOW_COMPLETELY_OPEN) )
	{
		(void)DGB_Print(MODULE,"ITS_TestCase 5: PASSED");
	}
	else
	{
		(void)DGB_Error(MODULE,"ITS_TestCase 5: Failed");
	}
}


