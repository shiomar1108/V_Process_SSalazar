/*
 * CAN_app.h
 *
 *  Created on: 18 mar. 2021
 *      Author: edgar
 */

#ifndef CAN_CAN_IL_CAN_APP_H_
#define CAN_CAN_IL_CAN_APP_H_

#include "CAN_usr.h"
#include "stdbool.h"


typedef struct{
	uint32_t NewMessage_BCM_5:1;
	uint32_t NewMessage_BCM_2:1;
	uint32_t NewMessage_BRAKE_2:1;

	uint32_t NewMessage_DCU_1:1;
	uint32_t NewMessage_DCU_2:1;
	uint32_t NewMessage_DCU_3:1;
	uint32_t NewMessage_DCU_4:1;
}MessageAvail_t;

void APP_CAN10ms_txProcess(const uint8_t l_swVariant);
//extern void APP_WriteDCU_Procces(void * p_DCU_MSG_GEN, const uint8_t r_swVariant);
extern void APP_WriteDCU_1(void);
extern void APP_CAN_DCM_DR_update_msg_DCU_1(S_DCU_1 DCU_1_CANMessage);
extern void APP_CAN_DCM_PS_update_msg_DCU_2(S_DCU_2 s_DCU_2_Message);
extern void APP_CAN_DCM_RL_update_msg_DCU_3(S_DCU_3 s_DCU_3_Message);
extern void APP_CAN_DCM_RR_update_msg_DCU_4(S_DCU_4 s_DCU_4_Message);


//extern uint8_t APP_Get_MSG_BCM_2(S_BCM_2 *s_BCM_2_Message);
//extern uint8_t APP_Get_MSG_BCM_5(S_BCM_5 *s_BCM_5_Message);
//extern uint8_t APP_Get_MSG_BRAKE_2(S_BRAKE_2 *s_BRAKE_2_Message);
//extern uint8_t APP_Get_MSG_DCU_1(S_DCU_1 *s_DCU_1_Message);
//extern uint8_t APP_Get_MSG_DCU_2(S_DCU_2 *s_DCU_2_Message);
//extern uint8_t APP_Get_MSG_DCU_3(S_DCU_3 *s_DCU_2_Message);
//extern uint8_t APP_Get_MSG_DCU_4(S_DCU_4 *s_DCU_2_Message);
//
extern uint8_t APP_RxCAN_process(const uint8_t r_SW_Variant);

extern MessageAvail_t RxAvailFlgs;
extern S_BRAKE_2 	global_BRAKE_2;
extern S_BCM_2		global_BCM_2;
extern S_BCM_5		global_BCM_5;
// Next ones either send or receive
extern S_DCU_1 		global_DCU_1;
extern S_DCU_2		global_DCU_2;
extern S_DCU_3		global_DCU_3;
extern S_DCU_4		global_DCU_4;

/*Generic RX macros to handle flags*/
#define APP_Get_avlbl_msg_BCM_5()	(RxAvailFlgs.NewMessage_BCM_5)
#define APP_Clr_avlbl_msg_BCM_5()	(RxAvailFlgs.NewMessage_BCM_5 = false)
#define APP_Set_avlbl_msg_BCM_5()	(RxAvailFlgs.NewMessage_BCM_5 = true)

#define APP_Get_avlbl_msg_BCM_2()	(RxAvailFlgs.NewMessage_BCM_2)
#define APP_Clr_avlbl_msg_BCM_2()	(RxAvailFlgs.NewMessage_BCM_2 = false)
#define APP_Set_avlbl_msg_BCM_2()	(RxAvailFlgs.NewMessage_BCM_2 = true)

#define APP_Get_avlbl_msg_BRAKE_2()	(RxAvailFlgs.NewMessage_BRAKE_2)
#define APP_Clr_avlbl_msg_BRAKE_2()	(RxAvailFlgs.NewMessage_BRAKE_2 = false)
#define APP_Set_avlbl_msg_BRAKE_2()	(RxAvailFlgs.NewMessage_BRAKE_2 = true)

#define APP_Get_avlbl_msg_DCU_1()	(RxAvailFlgs.NewMessage_DCU_1)
#define APP_Clr_avlbl_msg_DCU_1()	(RxAvailFlgs.NewMessage_DCU_1 = false)
#define APP_Set_avlbl_msg_DCU_1()	(RxAvailFlgs.NewMessage_DCU_1 = true)

#define APP_Get_avlbl_msg_DCU_2()	(RxAvailFlgs.NewMessage_DCU_2)
#define APP_Clr_avlbl_msg_DCU_2()	(RxAvailFlgs.NewMessage_DCU_2 = false)
#define APP_Set_avlbl_msg_DCU_2()	(RxAvailFlgs.NewMessage_DCU_2 = true)

#define APP_Get_avlbl_msg_DCU_3()	(RxAvailFlgs.NewMessage_DCU_3)
#define APP_Clr_avlbl_msg_DCU_3()	(RxAvailFlgs.NewMessage_DCU_3 = false)
#define APP_Set_avlbl_msg_DCU_3()	(RxAvailFlgs.NewMessage_DCU_3 = true)

#define APP_Get_avlbl_msg_DCU_3()	(RxAvailFlgs.NewMessage_DCU_3)
#define APP_Clr_avlbl_msg_DCU_3()	(RxAvailFlgs.NewMessage_DCU_3 = false)
#define APP_Set_avlbl_msg_DCU_3()	(RxAvailFlgs.NewMessage_DCU_3 = true)




/* Driver Macros RX, to access to messages */
#define APP_CAN_DCM_DR_get_msg_BCM_5(data_struct) 	CAN_DCM_DR_get_msg_BCM_5(data_struct)
#define APP_CAN_DCM_DR_get_msg_BCM_2(data_struct) 	CAN_DCM_DR_get_msg_BCM_2(data_struct)
#define APP_CAN_DCM_DR_get_msg_BRAKE_2(data_struct) CAN_DCM_DR_get_msg_BRAKE_2(data_struct)

#define APP_CAN_DCM_DR_get_msg_DCU_1(data_struct) 	CAN_DCM_DR_get_msg_DCU_1(data_struct)
#define APP_CAN_DCM_DR_get_msg_DCU_2(data_struct) 	CAN_DCM_DR_get_msg_DCU_2(data_struct)
#define APP_CAN_DCM_DR_get_msg_DCU_3(data_struct) 	CAN_DCM_DR_get_msg_DCU_3(data_struct)
#define APP_CAN_DCM_DR_get_msg_DCU_4(data_struct) 	CAN_DCM_DR_get_msg_DCU_4(data_struct)

/* Passenger Macros RX, to access to messages */
#define APP_CAN_DCM_PS_get_msg_DCU_1(data_struct) 	CAN_DCM_PS_get_msg_DCU_1(data_struct)
#define APP_CAN_DCM_PS_get_msg_BCM_2(data_struct) 	CAN_DCM_PS_get_msg_BCM_2(data_struct)

/* Rear Left Macros RX, to access to messages */
#define APP_CAN_DCM_RL_get_msg_DCU_1(data_struct) 	CAN_DCM_RL_get_msg_DCU_1(data_struct)
#define APP_CAN_DCM_RL_get_msg_DCU_2(data_struct) 	CAN_DCM_RL_get_msg_DCU_2(data_struct)
#define APP_CAN_DCM_RL_get_msg_BCM_2(data_struct) 	CAN_DCM_RL_get_msg_BCM_2(data_struct)

/* Rear Left Macros RX, to access to messages */
#define APP_CAN_DCM_RR_get_msg_DCU_1(data_struct) 	CAN_DCM_RR_get_msg_DCU_1(data_struct)
#define APP_CAN_DCM_RR_get_msg_DCU_2(data_struct) 	CAN_DCM_RR_get_msg_DCU_2(data_struct)
#define APP_CAN_DCM_RR_get_msg_BCM_2(data_struct) 	CAN_DCM_RR_get_msg_BCM_2(data_struct)

/* Driver Macros TX, to access to messages */
//#define APP_CAN_DCM_DR_update_msg_DCU_1(data_struct)		CAN_DCM_DR_update_msg_DCU_1(data_struct)

/* Driver Macros TX, to access to messages */
//#define APP_CAN_DCM_PS_update_msg_DCU_2(data_struct)		CAN_DCM_PS_update_msg_DCU_2(data_struct)

/* Driver Macros TX, to access to messages */
//#define APP_CAN_DCM_RL_update_msg_DCU_3(data_struct)		CAN_DCM_RL_update_msg_DCU_3(data_struct)

/* Driver Macros TX, to access to messages */
//#define APP_CAN_DCM_RR_update_msg_DCU_4(data_struct)		CAN_DCM_RR_update_msg_DCU_4(data_struct)





#endif /* CAN_CAN_IL_CAN_APP_H_ */
