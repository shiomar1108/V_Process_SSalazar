/*
 * CAN_app.c
 *
 *  Created on: 18 mar. 2021
 *      Author: edgar
 */


#include "CAN_app.h"

#define DCU_1_UPPER_LIMIT_MC	0xFF
#define DCU_1_RESET_VAL_MC		0x00
#define DCU_2_UPPER_LIMIT_MC	0xFF
#define DCU_2_RESET_VAL_MC		0x00
#define DCU_3_UPPER_LIMIT_MC	0xFF
#define DCU_3_RESET_VAL_MC		0x00
#define DCU_4_UPPER_LIMIT_MC	0xFF
#define DCU_4_RESET_VAL_MC		0x00

#define DCU_RESERVE_BYTE_VAL	0xFF


/*-----------------------------------------------------------*/
/* Local CAN Messages*/
//Next ones just to receive
S_BRAKE_2 	global_BRAKE_2;
S_BCM_2		global_BCM_2;
S_BCM_5		global_BCM_5;

// Next ones either send or receive
S_DCU_1 	global_DCU_1;
S_DCU_2		global_DCU_2;
S_DCU_3		global_DCU_3;
S_DCU_4		global_DCU_4;

MessageAvail_t RxAvailFlgs;


/*-----------------------------------------------------------*/



/* ============================================================================
 * Function Name:
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
void APP_CAN10ms_txProcess(const uint8_t l_swVariant){
	switch(l_swVariant){
		case tSW_VARIANT_DR:
			can_task_10ms_DCM_DR_txProcess();		// CAN IL function
		break;
		case tSW_VARIANT_PS:
			can_task_10ms_DCM_PS_txProcess();		// CAN IL function
		break;
		case tSW_VARIANT_RL:
			can_task_10ms_DCM_RL_txProcess();		// CAN IL function
		break;
		case tSW_VARIANT_RR:
			can_task_10ms_DCM_RR_txProcess();		// CAN IL function
		break;
	}
}


/* ============================================================================
 * Function Name: APP_WriteDCU_ALL
 * Description:
 * Arguments:
 * @s_DCU_1_Message,
 * Return:
 * ========================================================================= */
//extern void APP_WriteDCU_Procces(const uint8_t r_swVariant){

//	switch(r_swVariant){
//		case tSW_VARIANT_DR:
//			APP_WriteDCU_1(S_DCU_1 *s_DCU_1_Message);
//		break;
//
//		case tSW_VARIANT_PS:
//			APP_WriteDCU_2(S_DCU_2 *s_DCU_2_Message);
//		break;
//		case tSW_VARIANT_RL:
//			APP_WriteDCU_3(S_DCU_3 *s_DCU_3_Message);
//		break;
//
//		case tSW_VARIANT_RR:
//			APP_WriteDCU_4(S_DCU_4 *s_DCU_4_Message);
//		break;
//		}
//}

/* ============================================================================
 * Function Name: APP_CAN_DCM_DR_update_msg_DCU_1
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
extern void APP_CAN_DCM_DR_update_msg_DCU_1(S_DCU_1 s_DCU_1_Message){

	S_DCU_1 l_CAN_MEssage_DSU_1;
	// Get the previous message
	CAN_DCM_DR_get_msg_DCU_1(l_CAN_MEssage_DSU_1);
	// Update just variables modified for DCM app
	l_CAN_MEssage_DSU_1.all[BYTE_POS_DCU_1_WindowPos] 		= s_DCU_1_Message.all[BYTE_POS_DCU_1_WindowPos] ;
	l_CAN_MEssage_DSU_1.all[BYTE_POS_DCU_1_LockingReq] 		= s_DCU_1_Message.all[BYTE_POS_DCU_1_LockingReq];
	l_CAN_MEssage_DSU_1.all[BYTE_POS_DCU_1_WindowOp] 		= s_DCU_1_Message.all[BYTE_POS_DCU_1_WindowOp];
	l_CAN_MEssage_DSU_1.all[BYTE_POS_DCU_1_RearWindowLock]	= s_DCU_1_Message.all[BYTE_POS_DCU_1_RearWindowLock];
	l_CAN_MEssage_DSU_1.all[BYTE_POS_DCU_1_DoorLockSts] 	= s_DCU_1_Message.all[BYTE_POS_DCU_1_DoorLockSts];
	l_CAN_MEssage_DSU_1.all[BYTE_POS_DCU_1_WdwCtrl_RR]		= s_DCU_1_Message.all[BYTE_POS_DCU_1_WdwCtrl_RR];
	l_CAN_MEssage_DSU_1.s.DCU_1_WdwCtrl_Pas	= 	s_DCU_1_Message.s.DCU_1_WdwCtrl_Pas;
	l_CAN_MEssage_DSU_1.s.DCU_1_WdwCtrl_RL	=	s_DCU_1_Message.s.DCU_1_WdwCtrl_RL;
	l_CAN_MEssage_DSU_1.s.DCU_1_WdwCtrl_RR	=	s_DCU_1_Message.s.DCU_1_WdwCtrl_RR;
	l_CAN_MEssage_DSU_1.s.reserved_0 = 3;

	/*
	 *
	 * Here will be calculated the CRC
	 *
	 */
	CAN_DCM_DR_update_msg_DCU_1(l_CAN_MEssage_DSU_1);
}


/* ============================================================================
 * Function Name: APP_CAN_DCM_PS_update_msg_DCU_2
 * Description:	This function sends the message for DCU_2 module, calculates the
 * message counter and the CRC of the data.
 * Arguments:
 * @s_DCU_1_Message,
 * Return:
 * ========================================================================= */
extern void APP_CAN_DCM_PS_update_msg_DCU_2(S_DCU_2 s_DCU_2_Message){

	S_DCU_2 l_CAN_MEssage_DSU_2;
	// Get the previous message
	CAN_DCM_PS_get_msg_DCU_2(l_CAN_MEssage_DSU_2);
	// Update just variables modified for DCM app

	l_CAN_MEssage_DSU_2.all[BYTE_POS_DCU_2_WindowPos]	=	s_DCU_2_Message.all[BYTE_POS_DCU_2_WindowPos];
	l_CAN_MEssage_DSU_2.all[BYTE_POS_DCU_2_LockingReq]	=	s_DCU_2_Message.all[BYTE_POS_DCU_2_LockingReq];
	l_CAN_MEssage_DSU_2.all[BYTE_POS_DCU_2_WindowOp]	=	s_DCU_2_Message.all[BYTE_POS_DCU_2_WindowOp];
	l_CAN_MEssage_DSU_2.all[BYTE_POS_DCU_2_DoorLockSts]	=	s_DCU_2_Message.all[BYTE_POS_DCU_2_DoorLockSts];

	/*
	 *
	 * Here will be calculated the CRC
	 *
	 */
	CAN_DCM_PS_update_msg_DCU_2(l_CAN_MEssage_DSU_2);
}

/* ============================================================================
 * Function Name: APP_CAN_DCM_RL_update_msg_DCU_3
 * Description:	This function sends the message for DCU_3 module, calculates the
 * message counter and the CRC of the data.
 * Arguments:
 * @s_DCU_1_Message,
 * Return:
 * ========================================================================= */
extern void APP_CAN_DCM_RL_update_msg_DCU_3(S_DCU_3 s_DCU_3_Message){

	S_DCU_3 l_CAN_MEssage_DCU_3;
	// Get the previous message
	CAN_DCM_RL_get_msg_DCU_3(l_CAN_MEssage_DCU_3);
	// Update just variables modified for DCM app

		// Update Message Counter Value
	l_CAN_MEssage_DCU_3.all[BYTE_POS_DCU_3_WindowPos] 	=	s_DCU_3_Message.all[BYTE_POS_DCU_3_WindowPos];
	l_CAN_MEssage_DCU_3.all[BYTE_POS_DCU_3_WindowOp]	=	s_DCU_3_Message.all[BYTE_POS_DCU_3_WindowOp];
	l_CAN_MEssage_DCU_3.all[BYTE_POS_DCU_3_DoorLockSts]	=	s_DCU_3_Message.all[BYTE_POS_DCU_3_DoorLockSts];

	CAN_DCM_RL_update_msg_DCU_3(l_CAN_MEssage_DCU_3);
}



/* ============================================================================
 * Function Name: APP_WriteDCU_4
 * Description:	This function sends the message for DCU_4 module, calculates the
 * message counter and the CRC of the data.
 * Arguments:
 * @s_DCU_1_Message,
 * Return:
 * ========================================================================= */
extern void APP_CAN_DCM_RR_update_msg_DCU_4(S_DCU_4 s_DCU_4_Message){

	S_DCU_4 l_CAN_MEssage_DCU_4;
	// Get the previous message
	CAN_DCM_RR_get_msg_DCU_4(l_CAN_MEssage_DCU_4);
	// Update just variables modified for DCM app

		// Update Message Counter Value
	l_CAN_MEssage_DCU_4.all[BYTE_POS_DCU_4_WindowPos] 	=	s_DCU_4_Message.all[BYTE_POS_DCU_4_WindowPos];
	l_CAN_MEssage_DCU_4.all[BYTE_POS_DCU_4_WindowOp]	=	s_DCU_4_Message.all[BYTE_POS_DCU_4_WindowOp];
	l_CAN_MEssage_DCU_4.all[BYTE_POS_DCU_4_DoorLockSts]	=	s_DCU_4_Message.all[BYTE_POS_DCU_4_DoorLockSts];

	CAN_DCM_RR_update_msg_DCU_4(l_CAN_MEssage_DCU_4);
}


/* ============================================================================
 * Function Name:	APP_GetALLMessages
 * Description:
 * Arguments:
 * Return:
 * ========================================================================= */
extern uint8_t APP_RxCAN_process(const uint8_t r_SW_Variant){
	volatile FlagsNative msg_avlbl_flags;						// Flags to indicate new information

	switch(r_SW_Variant){
/* ========================================================================= */
		case tSW_VARIANT_DR:
			msg_avlbl_flags = CAN_DCM_DR_get_msg_avlbl_flags_BCM_5();
			if(msg_avlbl_flags.all){
				/* Message received. Clear flags. */
				CAN_DCM_DR_clr_msg_avlbl_flags_BCM_5();
//				CAN_DCM_DR_get_msg_BCM_5(global_BCM_5);

				/*
				 * Validate message with MC and CRC
				 *
				 * */

				if(1){
					APP_Set_avlbl_msg_BCM_5();
				}else{
					/*invalid message*/
					APP_Clr_avlbl_msg_BCM_5();
				}

			}

			msg_avlbl_flags = CAN_DCM_DR_get_msg_avlbl_flags_BCM_2();
			if(msg_avlbl_flags.all){
				/* Message received. Clear flags. */
				CAN_DCM_DR_clr_msg_avlbl_flags_BCM_2();
				/* Synchronize data from RX buffer to local data */
//				CAN_DCM_DR_get_msg_BCM_2(global_BCM_2);

				/*
				* Validate message with MC and CRC
				*
				* */
				if(1){
					APP_Set_avlbl_msg_BCM_2();
				}else{
					APP_Clr_avlbl_msg_BCM_2();
				}
			}

			msg_avlbl_flags = CAN_DCM_DR_get_msg_avlbl_flags_BRAKE_2();
			if(msg_avlbl_flags.all){
				/* Message received. Clear flags. */
				CAN_DCM_DR_clr_msg_avlbl_flags_BRAKE_2();
				/* Synchronize data from RX buffer to local data */
//				CAN_DCM_DR_get_msg_BRAKE_2(global_BRAKE_2);

				/*
				* Validate message with MC and CRC
				*
				* */
				if(1){
					APP_Set_avlbl_msg_BRAKE_2();
				}else{
					APP_Clr_avlbl_msg_BRAKE_2();
				}
			}

			msg_avlbl_flags = CAN_DCM_DR_get_msg_avlbl_flags_DCU_2();
			if(msg_avlbl_flags.all){
				/* Message received. Clear flags. */
				CAN_DCM_DR_clr_msg_avlbl_flags_DCU_2();
				/* Synchronize data from RX buffer to local data */
//				CAN_DCM_DR_get_msg_DCU_2(global_DCU_2);
				/*
				* Validate message with MC and CRC
				*
				* */
				if(1){
					APP_Set_avlbl_msg_DCU_2();
				}else{
					APP_Clr_avlbl_msg_DCU_2();
				}

			}

			msg_avlbl_flags = CAN_DCM_DR_get_msg_avlbl_flags_DCU_3();
			if(msg_avlbl_flags.all){
				/* Message received. Clear flags. */
				CAN_DCM_DR_clr_msg_avlbl_flags_DCU_3();
				/* Synchronize data from RX buffer to local data */
//				CAN_DCM_DR_get_msg_DCU_3(global_DCU_3);
				/*
				* Validate message with MC and CRC
				*
				* */
				if(1){
					APP_Set_avlbl_msg_DCU_3();
				}else{
					APP_Clr_avlbl_msg_DCU_3();
				}
			}

			msg_avlbl_flags = CAN_DCM_DR_get_msg_avlbl_flags_DCU_4();
			if(msg_avlbl_flags.all){
				/* Message received. Clear flags. */
				CAN_DCM_DR_clr_msg_avlbl_flags_DCU_4();
				/* Synchronize data from RX buffer to local data */
//				CAN_DCM_DR_get_msg_DCU_4(global_DCU_4);
				/*
				* Validate message with MC and CRC
				*
				* */
				if(1){
					APP_Set_avlbl_msg_DCU_3();
				}else{
					APP_Clr_avlbl_msg_DCU_3();
				}
			}
		break;

/* ========================================================================= */
		case tSW_VARIANT_PS:
			msg_avlbl_flags = CAN_DCM_PS_get_msg_avlbl_flags_BCM_2();
			if(msg_avlbl_flags.all){
				/* Message received. Clear flags. */
				CAN_DCM_PS_clr_msg_avlbl_flags_BCM_2();
				/* Synchronize data from RX buffer to local data */
				CAN_DCM_PS_get_msg_BCM_2(global_BCM_2);
				/*
				* Validate message with MC and CRC
				*
				* */
				if(1){
					APP_Set_avlbl_msg_BCM_2();
				}else{
					APP_Clr_avlbl_msg_BCM_2();
				}
			}
			msg_avlbl_flags = CAN_DCM_PS_get_msg_avlbl_flags_DCU_1();
			if(msg_avlbl_flags.all){
				/* Message received. Clear flags. */
				CAN_DCM_PS_clr_msg_avlbl_flags_DCU_1();
				/* Synchronize data from RX buffer to local data */
//				CAN_DCM_PS_get_msg_DCU_1(global_DCU_1);
				/*
				* Validate message with MC and CRC
				*
				* */
				if(1){
					APP_Set_avlbl_msg_DCU_1();
				}else{
					APP_Clr_avlbl_msg_DCU_1();
				}
			}
		break;

/* ========================================================================= */
		case tSW_VARIANT_RL:
			msg_avlbl_flags = CAN_DCM_RL_get_msg_avlbl_flags_BCM_2();
			if(msg_avlbl_flags.all){
				/* Message received. Clear flags. */
				CAN_DCM_RL_clr_msg_avlbl_flags_BCM_2();
				/* Synchronize data from RX buffer to local data */
//				CAN_DCM_RL_get_msg_BCM_2(global_BCM_2);
				/*
				* Validate message with MC and CRC
				*
				* */
				if(1){
					APP_Set_avlbl_msg_BCM_2();
				}else{
					APP_Clr_avlbl_msg_BCM_2();
				}
			}
			msg_avlbl_flags = CAN_DCM_RL_get_msg_avlbl_flags_DCU_1();
			if(msg_avlbl_flags.all){
				/* Message received. Clear flags. */
				CAN_DCM_RL_clr_msg_avlbl_flags_DCU_1();
				/* Synchronize data from RX buffer to local data */
//				CAN_DCM_RL_get_msg_DCU_1(global_DCU_1);
				/*
				* Validate message with MC and CRC
				*
				* */
				if(1){
					APP_Set_avlbl_msg_DCU_1();
				}else{
					APP_Clr_avlbl_msg_DCU_1();
				}
			}
			msg_avlbl_flags = CAN_DCM_RL_get_msg_avlbl_flags_DCU_2();
			if(msg_avlbl_flags.all){
				/* Message received. Clear flags. */
				CAN_DCM_RL_clr_msg_avlbl_flags_DCU_2();
				/* Synchronize data from RX buffer to local data */
//				CAN_DCM_RL_get_msg_DCU_2(global_DCU_2);
				/*
				* Validate message with MC and CRC
				*
				* */
				if(1){
					APP_Set_avlbl_msg_DCU_2();
				}else{
					APP_Clr_avlbl_msg_DCU_2();
				}
			}
		break;

/* ========================================================================= */
		case tSW_VARIANT_RR:
			msg_avlbl_flags = CAN_DCM_RR_get_msg_avlbl_flags_BCM_2();
			if(msg_avlbl_flags.all){
				/* Message received. Clear flags. */
				CAN_DCM_RR_clr_msg_avlbl_flags_BCM_2();
				/* Synchronize data from RX buffer to local data */
//				CAN_DCM_RR_get_msg_BCM_2(global_BCM_2);
				/*
				* Validate message with MC and CRC
				*
				* */
				if(1){
					APP_Set_avlbl_msg_BCM_2();
				}else{
					APP_Clr_avlbl_msg_BCM_2();
				}
			}

			msg_avlbl_flags = CAN_DCM_RR_get_msg_avlbl_flags_DCU_1();
			if(msg_avlbl_flags.all){
				/* Message received. Clear flags. */
				CAN_DCM_RR_clr_msg_avlbl_flags_DCU_1();
				/* Synchronize data from RX buffer to local data */
//				CAN_DCM_RR_get_msg_DCU_1(global_DCU_1);
				/*
				* Validate message with MC and CRC
				*
				* */
				if(1){
					APP_Set_avlbl_msg_DCU_1();
				}else{
					APP_Clr_avlbl_msg_DCU_1();
				}
			}
			msg_avlbl_flags = CAN_DCM_RR_get_msg_avlbl_flags_DCU_2();
			if(msg_avlbl_flags.all){
				/* Message received. Clear flags. */
				CAN_DCM_RR_clr_msg_avlbl_flags_DCU_2();
				/* Synchronize data from RX buffer to local data */
//				CAN_DCM_RR_get_msg_DCU_2(global_DCU_2);
				/*
				* Validate message with MC and CRC
				*
				* */
				if(1){
					APP_Set_avlbl_msg_DCU_2();
				}else{
					APP_Clr_avlbl_msg_DCU_2();
				}
			}
		break;
		}

	return 0;
}




