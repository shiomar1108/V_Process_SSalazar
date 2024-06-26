/*============================================================================*/
/*                           calvOS Project                                   */
/*============================================================================*/
/** \file		comgen_CAN_DCM_DR_node_network.h                              */
/** \brief     	Header file CAN Signals/Messages definitions of a given node.
 *  \details   	Declares macros, functions, etc. for the handling of signals and
 *  			messages for a given node taking into account the messages/
 *  			signals direction (TX/RX) with respect to the node.
 *  \author    	Carlos Calvillo
 *  \version   	1.0
 *  \date      	2020-11-15
 *  \copyright 	2020 Carlos Calvillo.
 */
/*============================================================================*/
/*  This file is part of calvOS project <https://github.com/calcore-io/calvos>.
 *
 *  calvOS is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  calvOS is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with calvOS.  If not, see <https://www.gnu.org/licenses/>. */
/*============================================================================*/
/*-----------------------------------------------------------------------------
 * This file was generated on (yyyy.mm.dd::hh:mm:ss): 2021.3.16::20:20:7
 * Generated from following source(s):
 *     Network file: "D:\Users\edgar\Desktop\Diplomado\Programs\..
                      CAN_Network_Definition\usr_in\..
                      template - CAN Network Definition.ods"
 *     Network name: "CAN-B"
 *     Network id: "B"
 *     Network date: "01/Mar/2021"
 *     Network version: "1"
 -----------------------------------------------------------------------------*/
#ifndef COMGEN_CAN_DCM_DR_NODE_NETWORK_H
#define COMGEN_CAN_DCM_DR_NODE_NETWORK_H

#include "calvos.h"
#include <string.h>

UBaseType_t uxSavedInterruptStatus;

/* -------------------------------------------------------------------------- */
// 		Network Messages
/* -------------------------------------------------------------------------- */
/* Message(s) direction */
#define kCAN_DCM_DR_msg_dir_BCM_5      (kDirRX)
#define kCAN_DCM_DR_msg_dir_BCM_2      (kDirRX)
#define kCAN_DCM_DR_msg_dir_BRAKE_2    (kDirRX)
#define kCAN_DCM_DR_msg_dir_DCU_1      (kDirTX)
#define kCAN_DCM_DR_msg_dir_DCU_2      (kDirRX)
#define kCAN_DCM_DR_msg_dir_DCU_3      (kDirRX)
#define kCAN_DCM_DR_msg_dir_DCU_4      (kDirRX)

/* Total data Length of TX message(s) */
#define kCAN_DCM_DR_TxMsgsTotalLen    (kCAN_msgLen_DCU_1)

/* Total data Length of RX message(s) */
#define kCAN_DCM_DR_RxMsgsTotalLen    (kCAN_msgLen_BCM_5 \
                                      + kCAN_msgLen_BCM_2 \
                                      + kCAN_msgLen_BRAKE_2 \
                                      + kCAN_msgLen_DCU_2 \
                                      + kCAN_msgLen_DCU_3 \
                                      + kCAN_msgLen_DCU_4)

/* Totals numbers for TX / RX message(s) */

/* RX message(s) timeout */
#define kCAN_DCM_DR_msgTimeout_BCM_5      (2500u)
#define kCAN_DCM_DR_msgTimeout_BCM_2      (2500u)
#define kCAN_DCM_DR_msgTimeout_BRAKE_2    (2500u)
#define kCAN_DCM_DR_msgTimeout_DCU_2      (1000u)
#define kCAN_DCM_DR_msgTimeout_DCU_3      (1000u)
#define kCAN_DCM_DR_msgTimeout_DCU_4      (1000u)

/* RX signal availability flag indexes */

/* RX signal availability flag buffer indexes*/
#define kCAN_DCM_DR_avlbl_buffer_idx_BCM_5      (0u)
#define kCAN_DCM_DR_avlbl_buffer_idx_BCM_2      (1u)
#define kCAN_DCM_DR_avlbl_buffer_idx_BRAKE_2    (2u)
#define kCAN_DCM_DR_avlbl_buffer_idx_DCU_2      (3u)
#define kCAN_DCM_DR_avlbl_buffer_idx_DCU_3      (4u)
#define kCAN_DCM_DR_avlbl_buffer_idx_DCU_4      (5u)

/* RX signal availability flags buffer slot sizes */
#define kCAN_DCM_DR_avlbl_slot_len_BCM_5      (1u)
#define kCAN_DCM_DR_avlbl_slot_len_BCM_2      (1u)
#define kCAN_DCM_DR_avlbl_slot_len_BRAKE_2    (1u)
#define kCAN_DCM_DR_avlbl_slot_len_DCU_2      (1u)
#define kCAN_DCM_DR_avlbl_slot_len_DCU_3      (1u)
#define kCAN_DCM_DR_avlbl_slot_len_DCU_4      (1u)

/* RX signals availability buffer size */
#define kCAN_DCM_DR_avlbl_buffer_len		(6u)

/* RX message(s) indexes - sorted by ID -*/
typedef enum{
	kCAN_DCM_DR_rxMsgIdx_BCM_5=0,
	kCAN_DCM_DR_rxMsgIdx_DCU_2,
	kCAN_DCM_DR_rxMsgIdx_DCU_3,
	kCAN_DCM_DR_rxMsgIdx_DCU_4,
	kCAN_DCM_DR_rxMsgIdx_BCM_2,
	kCAN_DCM_DR_rxMsgIdx_BRAKE_2,
	kCAN_DCM_DR_nOfRxMsgs
}CAN_DCM_DR_rxMsgs;

/* TX message(s) indexes */
typedef enum{
	kCAN_DCM_DR_txMsgIdx_DCU_1=0,
	kCAN_DCM_DR_nOfTxMsgs
}CAN_DCM_DR_txMsgs;

/* TX messages/signals direct access macros */

/* ----------- Macros for Rx message "BCM_5" ----------- */
/*** Message Level macros ***/
/* Get message data from unified buffer */
#define CAN_DCM_DR_get_msg_BCM_5(data_struct)		CALVOS_CRITICAL_ENTER(); \
															memcpy(data_struct.all, \
															can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BCM_5].data, \
															can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BCM_5].fields.len); \
															CALVOS_CRITICAL_EXIT();
/* ----------- Macro added by user to use pointers "BCM_5" ----------- */
#define p_CAN_DCM_DR_get_msg_BCM_5(data_struct)		CALVOS_CRITICAL_ENTER(); \
															memcpy(data_struct->all, \
															can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BCM_5].data, \
															can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BCM_5].fields.len); \
															CALVOS_CRITICAL_EXIT();


/* Get message available flags */
#define CAN_DCM_DR_get_msg_avlbl_flags_BCM_5()		(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BCM_5].dyn->available)

/* Clear message available flags */
#define CAN_DCM_DR_clr_msg_avlbl_flags_BCM_5()		can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BCM_5].dyn->available.all = 0u;

/* Clear all available flags (message and signals) */
#define CAN_DCM_DR_clr_all_avlbl_flags_BCM_5()		can_clearAllAvlblFlags(&can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BCM_5])

/*** Signal Level macros ***/
/* Macros for direct reading of signal "BCM_5_MC". */
#define CAN_DCM_DR_get_direct_BCM_5_MC()                  (CAN_extract_BCM_5_MC(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BCM_5].data))

/* Macros for available flags handling of signal "BCM_5_MC". */
#define CAN_DCM_DR_get_avlbl_BCM_5_MC()                   (can_DCM_DR_avlbl_buffer[0] & 0x01u)
#define CAN_DCM_DR_clr_avlbl_BCM_5_MC()                   (can_DCM_DR_avlbl_buffer[0] = can_DCM_DR_avlbl_buffer[0] & 0xfeu)

/* Macros for direct reading of signal "SysPwrMode". */
#define CAN_DCM_DR_get_direct_SysPwrMode()                  (CAN_extract_SysPwrMode(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BCM_5].data))

/* Macros for available flags handling of signal "SysPwrMode". */
#define CAN_DCM_DR_get_avlbl_SysPwrMode()                   ((can_DCM_DR_avlbl_buffer[0] >> 0x01u) & 0x01u)
#define CAN_DCM_DR_clr_avlbl_SysPwrMode()                   (can_DCM_DR_avlbl_buffer[0] = can_DCM_DR_avlbl_buffer[0] & 0xfdu)

/* Macros for direct reading of signal "BCM_5_CMAC". */
#define CAN_DCM_DR_get_direct_BCM_5_CMAC()                  (CAN_extract_BCM_5_CMAC(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BCM_5].data))

/* Macros for available flags handling of signal "BCM_5_CMAC". */
#define CAN_DCM_DR_get_avlbl_BCM_5_CMAC()                   ((can_DCM_DR_avlbl_buffer[0] >> 0x02u) & 0x01u)
#define CAN_DCM_DR_clr_avlbl_BCM_5_CMAC()                   (can_DCM_DR_avlbl_buffer[0] = can_DCM_DR_avlbl_buffer[0] & 0xfbu)

/* ----------- Macros for Rx message "BCM_2" ----------- */
/*** Message Level macros ***/
/* Get message data from unified buffer */
#define CAN_DCM_DR_get_msg_BCM_2(data_struct)		CALVOS_CRITICAL_ENTER(); \
															memcpy(data_struct.all, \
															can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BCM_2].data, \
															can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BCM_2].fields.len); \
															CALVOS_CRITICAL_EXIT();

/* ----------- Macro added by user to work with pointers "BRAKE_2" ----------- */
#define p_CAN_DCM_DR_get_msg_BCM_2(data_struct)		CALVOS_CRITICAL_ENTER(); \
															memcpy(data_struct->all, \
															can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BCM_2].data, \
															can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BCM_2].fields.len); \
															CALVOS_CRITICAL_EXIT();

/* Get message available flags */
#define CAN_DCM_DR_get_msg_avlbl_flags_BCM_2()		(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BCM_2].dyn->available)

/* Clear message available flags */
#define CAN_DCM_DR_clr_msg_avlbl_flags_BCM_2()		can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BCM_2].dyn->available.all = 0u;

/* Clear all available flags (message and signals) */
#define CAN_DCM_DR_clr_all_avlbl_flags_BCM_2()		can_clearAllAvlblFlags(&can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BCM_2])

/*** Signal Level macros ***/
/* Macros for direct reading of signal "BCM_2_MC". */
#define CAN_DCM_DR_get_direct_BCM_2_MC()                  (CAN_extract_BCM_2_MC(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BCM_2].data))

/* Macros for available flags handling of signal "BCM_2_MC". */
#define CAN_DCM_DR_get_avlbl_BCM_2_MC()                   (can_DCM_DR_avlbl_buffer[1] & 0x01u)
#define CAN_DCM_DR_clr_avlbl_BCM_2_MC()                   (can_DCM_DR_avlbl_buffer[1] = can_DCM_DR_avlbl_buffer[1] & 0xfeu)

/* Macros for direct reading of signal "ConfortCmd". */
#define CAN_DCM_DR_get_direct_ConfortCmd()                  (CAN_extract_ConfortCmd(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BCM_2].data))

/* Macros for available flags handling of signal "ConfortCmd". */
#define CAN_DCM_DR_get_avlbl_ConfortCmd()                   ((can_DCM_DR_avlbl_buffer[1] >> 0x01u) & 0x01u)
#define CAN_DCM_DR_clr_avlbl_ConfortCmd()                   (can_DCM_DR_avlbl_buffer[1] = can_DCM_DR_avlbl_buffer[1] & 0xfdu)

/* Macros for direct reading of signal "BCM_2_CMAC". */
#define CAN_DCM_DR_get_direct_BCM_2_CMAC()                  (CAN_extract_BCM_2_CMAC(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BCM_2].data))

/* Macros for available flags handling of signal "BCM_2_CMAC". */
#define CAN_DCM_DR_get_avlbl_BCM_2_CMAC()                   ((can_DCM_DR_avlbl_buffer[1] >> 0x02u) & 0x01u)
#define CAN_DCM_DR_clr_avlbl_BCM_2_CMAC()                   (can_DCM_DR_avlbl_buffer[1] = can_DCM_DR_avlbl_buffer[1] & 0xfbu)

/* ----------- Macros for Rx message "BRAKE_2" ----------- */
/*** Message Level macros ***/
/* Get message data from unified buffer */
#define CAN_DCM_DR_get_msg_BRAKE_2(data_struct)		CALVOS_CRITICAL_ENTER(); \
															memcpy(data_struct.all, \
															can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BRAKE_2].data, \
															can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BRAKE_2].fields.len); \
															CALVOS_CRITICAL_EXIT();

/* ----------- Macro added by user to use pointers "BRAKE_2" ----------- */
#define p_CAN_DCM_DR_get_msg_BRAKE_2(data_struct)		CALVOS_CRITICAL_ENTER(); \
															memcpy(data_struct->all, \
															can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BRAKE_2].data, \
															can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BRAKE_2].fields.len); \
															CALVOS_CRITICAL_EXIT();

/* Get message available flags */
#define CAN_DCM_DR_get_msg_avlbl_flags_BRAKE_2()		(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BRAKE_2].dyn->available)

/* Clear message available flags */
#define CAN_DCM_DR_clr_msg_avlbl_flags_BRAKE_2()		can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BRAKE_2].dyn->available.all = 0u;

/* Clear all available flags (message and signals) */
#define CAN_DCM_DR_clr_all_avlbl_flags_BRAKE_2()		can_clearAllAvlblFlags(&can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BRAKE_2])

/*** Signal Level macros ***/
/* Macros for direct reading of signal "VehSpeed". */
#define CAN_DCM_DR_get_direct_VehSpeed()                  (CAN_extract_VehSpeed(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BRAKE_2].data))

/* Macros for available flags handling of signal "VehSpeed". */
#define CAN_DCM_DR_get_avlbl_VehSpeed()                   (can_DCM_DR_avlbl_buffer[2] & 0x01u)
#define CAN_DCM_DR_clr_avlbl_VehSpeed()                   (can_DCM_DR_avlbl_buffer[2] = can_DCM_DR_avlbl_buffer[2] & 0xfeu)

/* Macros for direct reading of signal "BRAKE_2_MC". */
#define CAN_DCM_DR_get_direct_BRAKE_2_MC()                  (CAN_extract_BRAKE_2_MC(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BRAKE_2].data))

/* Macros for available flags handling of signal "BRAKE_2_MC". */
#define CAN_DCM_DR_get_avlbl_BRAKE_2_MC()                   ((can_DCM_DR_avlbl_buffer[2] >> 0x01u) & 0x01u)
#define CAN_DCM_DR_clr_avlbl_BRAKE_2_MC()                   (can_DCM_DR_avlbl_buffer[2] = can_DCM_DR_avlbl_buffer[2] & 0xfdu)

/* Macros for direct reading of signal "BRAKE_2_CRC". */
#define CAN_DCM_DR_get_direct_BRAKE_2_CRC()                  (CAN_extract_BRAKE_2_CRC(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_BRAKE_2].data))

/* Macros for available flags handling of signal "BRAKE_2_CRC". */
#define CAN_DCM_DR_get_avlbl_BRAKE_2_CRC()                   ((can_DCM_DR_avlbl_buffer[2] >> 0x02u) & 0x01u)
#define CAN_DCM_DR_clr_avlbl_BRAKE_2_CRC()                   (can_DCM_DR_avlbl_buffer[2] = can_DCM_DR_avlbl_buffer[2] & 0xfbu)

/* ----------- Macros for Tx message "DCU_1" ----------- */
/*** Message Level macros ***/
/* Get message data from unified buffer */
#define CAN_DCM_DR_get_msg_DCU_1(data_struct)		CALVOS_CRITICAL_ENTER(); \
															memcpy(data_struct.all, \
															can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].data, \
															can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].fields.len); \
															CALVOS_CRITICAL_EXIT();
/* ----------- Macro added by user to use pointers "DCU_1" ----------- */
#define p_CAN_DCM_DR_get_msg_DCU_1(data_struct)		CALVOS_CRITICAL_ENTER(); \
															memcpy(data_struct->all, \
															can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].data, \
															can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].fields.len); \
															CALVOS_CRITICAL_EXIT();

/* Update message data to be transmitted */
#define CAN_DCM_DR_update_msg_DCU_1(data_struct)		CALVOS_CRITICAL_ENTER(); \
															memcpy(can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].data, \
															data_struct.all, \
															can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].fields.len); \
															CALVOS_CRITICAL_EXIT();

/* Update message data to be transmitted, this uses a pointer to a struct */
#define p_CAN_DCM_DR_update_msg_DCU_1(data_struct)		CALVOS_CRITICAL_ENTER(); \
															memcpy(can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].data, \
															data_struct->all, \
															can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].fields.len); \
															CALVOS_CRITICAL_EXIT();


/* Get message transmission state macro */
#define CAN_DCM_DR_get_tx_state_DCU_1()		(can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].dyn->state)

/*** Signal Level macros ***/
/* Macros for direct reading of signal "DCU_1_WindowPos". */
#define CAN_DCM_DR_get_direct_DCU_1_WindowPos()                  (CAN_extract_DCU_1_WindowPos(can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].data))
/* Macros for direct writing of signal "DCU_1_WindowPos". */
#define CAN_DCM_DR_update_direct_DCU_1_WindowPos(data_in)        CAN_write_DCU_1_WindowPos(can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].data,data_in)

/* Macros for available flags handling of signal "DCU_1_WindowPos". */

/* Macros for direct reading of signal "DCU_1_LockingReq". */
#define CAN_DCM_DR_get_direct_DCU_1_LockingReq()                  (CAN_extract_DCU_1_LockingReq(can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].data))
/* Macros for direct writing of signal "DCU_1_LockingReq". */
#define CAN_DCM_DR_update_direct_DCU_1_LockingReq(data_in)        CAN_write_DCU_1_LockingReq(can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].data,data_in)

/* Macros for available flags handling of signal "DCU_1_LockingReq". */

/* Macros for direct reading of signal "DCU_1_WindowOp". */
#define CAN_DCM_DR_get_direct_DCU_1_WindowOp()                  (CAN_extract_DCU_1_WindowOp(can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].data))
/* Macros for direct writing of signal "DCU_1_WindowOp". */
#define CAN_DCM_DR_update_direct_DCU_1_WindowOp(data_in)        CAN_write_DCU_1_WindowOp(can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].data,data_in)

/* Macros for available flags handling of signal "DCU_1_WindowOp". */

/* Macros for direct reading of signal "DCU_1_RearWindowLock". */
#define CAN_DCM_DR_get_direct_DCU_1_RearWindowLock()                  (CAN_extract_DCU_1_RearWindowLock(can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].data))
/* Macros for direct writing of signal "DCU_1_RearWindowLock". */
#define CAN_DCM_DR_update_direct_DCU_1_RearWindowLock(data_in)        CAN_write_DCU_1_RearWindowLock(can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].data,data_in)

/* Macros for available flags handling of signal "DCU_1_RearWindowLock". */

/* Macros for direct reading of signal "DCU_1_DoorLockSts". */
#define CAN_DCM_DR_get_direct_DCU_1_DoorLockSts()                  (CAN_extract_DCU_1_DoorLockSts(can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].data))
/* Macros for direct writing of signal "DCU_1_DoorLockSts". */
#define CAN_DCM_DR_update_direct_DCU_1_DoorLockSts(data_in)        CAN_write_DCU_1_DoorLockSts(can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].data,data_in)

/* Macros for available flags handling of signal "DCU_1_DoorLockSts". */

/* Macros for direct reading of signal "DCU_1_WdwCtrl_RR". */
#define CAN_DCM_DR_get_direct_DCU_1_WdwCtrl_RR()                  (CAN_extract_DCU_1_WdwCtrl_RR(can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].data))
/* Macros for direct writing of signal "DCU_1_WdwCtrl_RR". */
#define CAN_DCM_DR_update_direct_DCU_1_WdwCtrl_RR(data_in)        CAN_write_DCU_1_WdwCtrl_RR(can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].data,data_in)

/* Macros for available flags handling of signal "DCU_1_WdwCtrl_RR". */

/* Macros for direct reading of signal "DCU_1_WdwCtrl_RL". */
#define CAN_DCM_DR_get_direct_DCU_1_WdwCtrl_RL()                  (CAN_extract_DCU_1_WdwCtrl_RL(can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].data))
/* Macros for direct writing of signal "DCU_1_WdwCtrl_RL". */
#define CAN_DCM_DR_update_direct_DCU_1_WdwCtrl_RL(data_in)        CAN_write_DCU_1_WdwCtrl_RL(can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].data,data_in)

/* Macros for available flags handling of signal "DCU_1_WdwCtrl_RL". */

/* Macros for direct reading of signal "DCU_1_WdwCtrl_Pas". */
#define CAN_DCM_DR_get_direct_DCU_1_WdwCtrl_Pas()                  (CAN_extract_DCU_1_WdwCtrl_Pas(can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].data))
/* Macros for direct writing of signal "DCU_1_WdwCtrl_Pas". */
#define CAN_DCM_DR_update_direct_DCU_1_WdwCtrl_Pas(data_in)        CAN_write_DCU_1_WdwCtrl_Pas(can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].data,data_in)

/* Macros for available flags handling of signal "DCU_1_WdwCtrl_Pas". */

/* Macros for direct reading of signal "DCU_1_MC". */
#define CAN_DCM_DR_get_direct_DCU_1_MC()                  (CAN_extract_DCU_1_MC(can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].data))
/* Macros for direct writing of signal "DCU_1_MC". */
#define CAN_DCM_DR_update_direct_DCU_1_MC(data_in)        CAN_write_DCU_1_MC(can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].data,data_in)

/* Macros for available flags handling of signal "DCU_1_MC". */

/* Macros for direct reading of signal "DCU_1_CRC". */
#define CAN_DCM_DR_get_direct_DCU_1_CRC()                  (CAN_extract_DCU_1_CRC(can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].data))
/* Macros for direct writing of signal "DCU_1_CRC". */
#define CAN_DCM_DR_update_direct_DCU_1_CRC(data_in)        CAN_write_DCU_1_CRC(can_DCM_DR_txMsgStaticData[kCAN_DCM_DR_txMsgIdx_DCU_1].data,data_in)

/* Macros for available flags handling of signal "DCU_1_CRC". */

/* ----------- Macros for Rx message "DCU_2" ----------- */
/*** Message Level macros ***/
/* Get message data from unified buffer */
#define CAN_DCM_DR_get_msg_DCU_2(data_struct)		CALVOS_CRITICAL_ENTER(); \
															memcpy(data_struct.all, \
															can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_2].data, \
															can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_2].fields.len); \
															CALVOS_CRITICAL_EXIT();

/* ----------- Macro added by user to use pointers "DCU_2" ----------- */
#define p_CAN_DCM_DR_get_msg_DCU_2(data_struct)		CALVOS_CRITICAL_ENTER(); \
															memcpy(data_struct->all, \
															can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_2].data, \
															can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_2].fields.len); \
															CALVOS_CRITICAL_EXIT();

/* Get message available flags */
#define CAN_DCM_DR_get_msg_avlbl_flags_DCU_2()		(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_2].dyn->available)

/* Clear message available flags */
#define CAN_DCM_DR_clr_msg_avlbl_flags_DCU_2()		can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_2].dyn->available.all = 0u;

/* Clear all available flags (message and signals) */
#define CAN_DCM_DR_clr_all_avlbl_flags_DCU_2()		can_clearAllAvlblFlags(&can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_2])

/*** Signal Level macros ***/
/* Macros for direct reading of signal "DCU_2_WindowPos". */
#define CAN_DCM_DR_get_direct_DCU_2_WindowPos()                  (CAN_extract_DCU_2_WindowPos(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_2].data))

/* Macros for available flags handling of signal "DCU_2_WindowPos". */
#define CAN_DCM_DR_get_avlbl_DCU_2_WindowPos()                   (can_DCM_DR_avlbl_buffer[3] & 0x01u)
#define CAN_DCM_DR_clr_avlbl_DCU_2_WindowPos()                   (can_DCM_DR_avlbl_buffer[3] = can_DCM_DR_avlbl_buffer[3] & 0xfeu)

/* Macros for direct reading of signal "DCU_2_LockingReq". */
#define CAN_DCM_DR_get_direct_DCU_2_LockingReq()                  (CAN_extract_DCU_2_LockingReq(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_2].data))

/* Macros for available flags handling of signal "DCU_2_LockingReq". */
#define CAN_DCM_DR_get_avlbl_DCU_2_LockingReq()                   ((can_DCM_DR_avlbl_buffer[3] >> 0x01u) & 0x01u)
#define CAN_DCM_DR_clr_avlbl_DCU_2_LockingReq()                   (can_DCM_DR_avlbl_buffer[3] = can_DCM_DR_avlbl_buffer[3] & 0xfdu)

/* Macros for direct reading of signal "DCU_2_WindowOp". */
#define CAN_DCM_DR_get_direct_DCU_2_WindowOp()                  (CAN_extract_DCU_2_WindowOp(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_2].data))

/* Macros for available flags handling of signal "DCU_2_WindowOp". */
#define CAN_DCM_DR_get_avlbl_DCU_2_WindowOp()                   ((can_DCM_DR_avlbl_buffer[3] >> 0x02u) & 0x01u)
#define CAN_DCM_DR_clr_avlbl_DCU_2_WindowOp()                   (can_DCM_DR_avlbl_buffer[3] = can_DCM_DR_avlbl_buffer[3] & 0xfbu)

/* Macros for direct reading of signal "DCU_2_DoorLockSts". */
#define CAN_DCM_DR_get_direct_DCU_2_DoorLockSts()                  (CAN_extract_DCU_2_DoorLockSts(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_2].data))

/* Macros for available flags handling of signal "DCU_2_DoorLockSts". */
#define CAN_DCM_DR_get_avlbl_DCU_2_DoorLockSts()                   ((can_DCM_DR_avlbl_buffer[3] >> 0x03u) & 0x01u)
#define CAN_DCM_DR_clr_avlbl_DCU_2_DoorLockSts()                   (can_DCM_DR_avlbl_buffer[3] = can_DCM_DR_avlbl_buffer[3] & 0xf7u)

/* Macros for direct reading of signal "DCU_2_MC". */
#define CAN_DCM_DR_get_direct_DCU_2_MC()                  (CAN_extract_DCU_2_MC(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_2].data))

/* Macros for available flags handling of signal "DCU_2_MC". */
#define CAN_DCM_DR_get_avlbl_DCU_2_MC()                   ((can_DCM_DR_avlbl_buffer[3] >> 0x04u) & 0x01u)
#define CAN_DCM_DR_clr_avlbl_DCU_2_MC()                   (can_DCM_DR_avlbl_buffer[3] = can_DCM_DR_avlbl_buffer[3] & 0xefu)

/* Macros for direct reading of signal "DCU_2_CRC". */
#define CAN_DCM_DR_get_direct_DCU_2_CRC()                  (CAN_extract_DCU_2_CRC(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_2].data))

/* Macros for available flags handling of signal "DCU_2_CRC". */
#define CAN_DCM_DR_get_avlbl_DCU_2_CRC()                   ((can_DCM_DR_avlbl_buffer[3] >> 0x05u) & 0x01u)
#define CAN_DCM_DR_clr_avlbl_DCU_2_CRC()                   (can_DCM_DR_avlbl_buffer[3] = can_DCM_DR_avlbl_buffer[3] & 0xdfu)

/* ----------- Macros for Rx message "DCU_3" ----------- */
/*** Message Level macros ***/
/* Get message data from unified buffer */
#define CAN_DCM_DR_get_msg_DCU_3(data_struct)		CALVOS_CRITICAL_ENTER(); \
															memcpy(data_struct.all, \
															can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_3].data, \
															can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_3].fields.len); \
															CALVOS_CRITICAL_EXIT();
/* ----------- Macro added by user to use pointes "DCU_3" ----------- */
#define p_CAN_DCM_DR_get_msg_DCU_3(data_struct)		CALVOS_CRITICAL_ENTER(); \
															memcpy(data_struct->all, \
															can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_3].data, \
															can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_3].fields.len); \
															CALVOS_CRITICAL_EXIT();

/* Get message available flags */
#define CAN_DCM_DR_get_msg_avlbl_flags_DCU_3()		(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_3].dyn->available)

/* Clear message available flags */
#define CAN_DCM_DR_clr_msg_avlbl_flags_DCU_3()		can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_3].dyn->available.all = 0u;

/* Clear all available flags (message and signals) */
#define CAN_DCM_DR_clr_all_avlbl_flags_DCU_3()		can_clearAllAvlblFlags(&can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_3])

/*** Signal Level macros ***/
/* Macros for direct reading of signal "DCU_3_WindowPos". */
#define CAN_DCM_DR_get_direct_DCU_3_WindowPos()                  (CAN_extract_DCU_3_WindowPos(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_3].data))

/* Macros for available flags handling of signal "DCU_3_WindowPos". */
#define CAN_DCM_DR_get_avlbl_DCU_3_WindowPos()                   (can_DCM_DR_avlbl_buffer[4] & 0x01u)
#define CAN_DCM_DR_clr_avlbl_DCU_3_WindowPos()                   (can_DCM_DR_avlbl_buffer[4] = can_DCM_DR_avlbl_buffer[4] & 0xfeu)

/* Macros for direct reading of signal "DCU_3_WindowOp". */
#define CAN_DCM_DR_get_direct_DCU_3_WindowOp()                  (CAN_extract_DCU_3_WindowOp(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_3].data))

/* Macros for available flags handling of signal "DCU_3_WindowOp". */
#define CAN_DCM_DR_get_avlbl_DCU_3_WindowOp()                   ((can_DCM_DR_avlbl_buffer[4] >> 0x01u) & 0x01u)
#define CAN_DCM_DR_clr_avlbl_DCU_3_WindowOp()                   (can_DCM_DR_avlbl_buffer[4] = can_DCM_DR_avlbl_buffer[4] & 0xfdu)

/* Macros for direct reading of signal "DCU_3_DoorLockSts". */
#define CAN_DCM_DR_get_direct_DCU_3_DoorLockSts()                  (CAN_extract_DCU_3_DoorLockSts(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_3].data))

/* Macros for available flags handling of signal "DCU_3_DoorLockSts". */
#define CAN_DCM_DR_get_avlbl_DCU_3_DoorLockSts()                   ((can_DCM_DR_avlbl_buffer[4] >> 0x02u) & 0x01u)
#define CAN_DCM_DR_clr_avlbl_DCU_3_DoorLockSts()                   (can_DCM_DR_avlbl_buffer[4] = can_DCM_DR_avlbl_buffer[4] & 0xfbu)

/* Macros for direct reading of signal "DCU_3_MC". */
#define CAN_DCM_DR_get_direct_DCU_3_MC()                  (CAN_extract_DCU_3_MC(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_3].data))

/* Macros for available flags handling of signal "DCU_3_MC". */
#define CAN_DCM_DR_get_avlbl_DCU_3_MC()                   ((can_DCM_DR_avlbl_buffer[4] >> 0x03u) & 0x01u)
#define CAN_DCM_DR_clr_avlbl_DCU_3_MC()                   (can_DCM_DR_avlbl_buffer[4] = can_DCM_DR_avlbl_buffer[4] & 0xf7u)

/* Macros for direct reading of signal "DCU_3_CRC". */
#define CAN_DCM_DR_get_direct_DCU_3_CRC()                  (CAN_extract_DCU_3_CRC(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_3].data))

/* Macros for available flags handling of signal "DCU_3_CRC". */
#define CAN_DCM_DR_get_avlbl_DCU_3_CRC()                   ((can_DCM_DR_avlbl_buffer[4] >> 0x04u) & 0x01u)
#define CAN_DCM_DR_clr_avlbl_DCU_3_CRC()                   (can_DCM_DR_avlbl_buffer[4] = can_DCM_DR_avlbl_buffer[4] & 0xefu)

/* ----------- Macros for Rx message "DCU_4" ----------- */
/*** Message Level macros ***/
/* Get message data from unified buffer */
#define CAN_DCM_DR_get_msg_DCU_4(data_struct)		CALVOS_CRITICAL_ENTER(); \
															memcpy(data_struct.all, \
															can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_4].data, \
															can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_4].fields.len); \
															CALVOS_CRITICAL_EXIT();
/* ----------- Macros added by user to use pointers "DCU_4" ----------- */
#define p_CAN_DCM_DR_get_msg_DCU_4(data_struct)		CALVOS_CRITICAL_ENTER(); \
															memcpy(data_struct->all, \
															can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_4].data, \
															can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_4].fields.len); \
															CALVOS_CRITICAL_EXIT();


/* Get message available flags */
#define CAN_DCM_DR_get_msg_avlbl_flags_DCU_4()		(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_4].dyn->available)

/* Clear message available flags */
#define CAN_DCM_DR_clr_msg_avlbl_flags_DCU_4()		can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_4].dyn->available.all = 0u;

/* Clear all available flags (message and signals) */
#define CAN_DCM_DR_clr_all_avlbl_flags_DCU_4()		can_clearAllAvlblFlags(&can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_4])

/*** Signal Level macros ***/
/* Macros for direct reading of signal "DCU_4_WindowPos". */
#define CAN_DCM_DR_get_direct_DCU_4_WindowPos()                  (CAN_extract_DCU_4_WindowPos(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_4].data))

/* Macros for available flags handling of signal "DCU_4_WindowPos". */
#define CAN_DCM_DR_get_avlbl_DCU_4_WindowPos()                   (can_DCM_DR_avlbl_buffer[5] & 0x01u)
#define CAN_DCM_DR_clr_avlbl_DCU_4_WindowPos()                   (can_DCM_DR_avlbl_buffer[5] = can_DCM_DR_avlbl_buffer[5] & 0xfeu)

/* Macros for direct reading of signal "DCU_4_WindowOp". */
#define CAN_DCM_DR_get_direct_DCU_4_WindowOp()                  (CAN_extract_DCU_4_WindowOp(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_4].data))

/* Macros for available flags handling of signal "DCU_4_WindowOp". */
#define CAN_DCM_DR_get_avlbl_DCU_4_WindowOp()                   ((can_DCM_DR_avlbl_buffer[5] >> 0x01u) & 0x01u)
#define CAN_DCM_DR_clr_avlbl_DCU_4_WindowOp()                   (can_DCM_DR_avlbl_buffer[5] = can_DCM_DR_avlbl_buffer[5] & 0xfdu)

/* Macros for direct reading of signal "DCU_4_DoorLockSts". */
#define CAN_DCM_DR_get_direct_DCU_4_DoorLockSts()                  (CAN_extract_DCU_4_DoorLockSts(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_4].data))

/* Macros for available flags handling of signal "DCU_4_DoorLockSts". */
#define CAN_DCM_DR_get_avlbl_DCU_4_DoorLockSts()                   ((can_DCM_DR_avlbl_buffer[5] >> 0x02u) & 0x01u)
#define CAN_DCM_DR_clr_avlbl_DCU_4_DoorLockSts()                   (can_DCM_DR_avlbl_buffer[5] = can_DCM_DR_avlbl_buffer[5] & 0xfbu)

/* Macros for direct reading of signal "DCU_4_MC". */
#define CAN_DCM_DR_get_direct_DCU_4_MC()                  (CAN_extract_DCU_4_MC(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_4].data))

/* Macros for available flags handling of signal "DCU_4_MC". */
#define CAN_DCM_DR_get_avlbl_DCU_4_MC()                   ((can_DCM_DR_avlbl_buffer[5] >> 0x03u) & 0x01u)
#define CAN_DCM_DR_clr_avlbl_DCU_4_MC()                   (can_DCM_DR_avlbl_buffer[5] = can_DCM_DR_avlbl_buffer[5] & 0xf7u)

/* Macros for direct reading of signal "DCU_4_CRC". */
#define CAN_DCM_DR_get_direct_DCU_4_CRC()                  (CAN_extract_DCU_4_CRC(can_DCM_DR_rxMsgStaticData[kCAN_DCM_DR_rxMsgIdx_DCU_4].data))

/* Macros for available flags handling of signal "DCU_4_CRC". */
#define CAN_DCM_DR_get_avlbl_DCU_4_CRC()                   ((can_DCM_DR_avlbl_buffer[5] >> 0x04u) & 0x01u)
#define CAN_DCM_DR_clr_avlbl_DCU_4_CRC()                   (can_DCM_DR_avlbl_buffer[5] = can_DCM_DR_avlbl_buffer[5] & 0xefu)


#endif /* COMGEN_CAN_DCM_DR_NODE_NETWORK_H */
