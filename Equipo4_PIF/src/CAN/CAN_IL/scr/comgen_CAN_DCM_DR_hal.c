/*============================================================================*/
/*                           calvOS Project                                   */
/*============================================================================*/
/** \file		USER_comgen_CAN_DCM_DR_hal.c                                  */
/** \brief     	Source file for CAN Hardware Abstraction Layer functions.
 *  \details   	Defines functions that need to be filled with user code in order
 *  			to integrate the CAN interaction layer with the hardware
 *  			abstraction layer in the target MCU.
 *  \author    	Carlos Calvillo
 *  \version   	0.1
 *  \date      	2021-02-01
 *  \copyright 	2021 Carlos Calvillo.
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
#include "calvos.h"
#include "comgen_CAN_common.h"
#include "comgen_CAN_DCM_DR_hal.h"
#include "comgen_CAN_DCM_DR_core.h"

/* ----------------------  CAN -User-includes  ---------------------- */
#include "flexcan_hw_access.h"
#include  "CAN_usr.h"




/* Macro for confirming TX msg ID */
/* This macro is generated based on parameter "CAN_tx_confirm_msg_id" */
#define CAN_DCM_DR_CONFIRM_MSG_ID		kTrue

#if CAN_DCM_DR_CONFIRM_MSG_ID==kTrue
uint32_t can_DCM_DR_HALgetTxdMsgId(void);
#endif

/* =============================================================================
 * 	Function definitions
 * ===========================================================================*/

/* ===========================================================================*/
/** Function for triggering a CAN msg transmission from HAL.
 *
 * This hardware-abstraction-layer function triggers the transmission of the
 * given CAN message in the target MCU.
 *
 * @param msg_info 	Pointer to the structure containing the message information.
 * @return 	Returns @c kNoError if transmission was accepted by the HAL, returns
 * 			@c kError if it was not accepted.
 * ===========================================================================*/
CalvosError can_DCM_DR_HALtransmitMsg(const CANtxMsgStaticData* msg_info){

	CalvosError return_value = kError;		//
	status_t l_error;						// get the error returned by functions

	// Send the message
	l_error = SendCANMessage(msg_info->id, msg_info->fields.len, msg_info->data);

#ifdef DEBUG
	DEV_ASSERT(l_error == STATUS_SUCCESS);
#endif

	if(l_error == STATUS_SUCCESS){
		return_value = kNoError;
	}
	return return_value;
}

/* ===========================================================================*/
/** Function for getting the id of the message just transmitted by the HAL.
 *
 * This function returns the id of the CAN message just transmitted by the
 * target CAN HAL. This function is invoked by the TX confirmation function
 * "can_NWID_NODEID_HALconfirmTxMsg".
 * ===========================================================================*/
#if CAN_DCM_DR_CONFIRM_MSG_ID==kTrue
uint32_t can_DCM_DR_HALgetTxdMsgId(void){

	uint32_t txd_msg_id;
	// Write user code to return the ID of the CAN message just transmitted
	// by the CAN HAL.
	txd_msg_id = app_getTxdId();


	return txd_msg_id;
}
#endif

/* ===========================================================================*/
/** Function for confirming transmission of CAN message for given node.
 *
 * This function shall be called when the target MCU confirms the transmission
 * of the lastly requested tx message.
 * ===========================================================================*/
void can_DCM_DR_HALconfirmTxMsg(void){

#if CAN_DCM_DR_CONFIRM_MSG_ID==kTrue
	uint32_t txd_msg_id;
	// Get ID of the message just transmitted
	txd_msg_id = can_DCM_DR_HALgetTxdMsgId();
	// Confirm TX message if ID matches
	can_commonConfirmTxMsg(can_DCM_DR_transmittingMsg, kTrue, txd_msg_id);
#else
	can_commonConfirmTxMsg(can_DCM_DR_transmittingMsg, kFalse, NULL);
#endif
}

/* ===========================================================================*/
/** Function for processing a received CAN msg from HAL.
 *
 * This hardware-abstraction-layer function shall be called when a CAN message
 * is received in the target MCU.
 *
 * @param msg_id 	ID of the received message.
 * @param data_in	Pointer to the received data.
 * @param data_len	Length of the received data. If it will depend on message
 * 					definition pass this parameter as zero.
 * ===========================================================================*/
void can_DCM_DR_HALreceiveMsg(uint32_t msg_id, uint8_t* data_in, uint8_t data_len){

	// Call RX processor function
	can_DCM_DR_processRxMessage(msg_id, data_in, data_len);
}

/* ===========================================================================*/
/** Function for initializing CAN Hardware Abstraction Layer (HAL).
 *
 * This function is called by can_NWID_NODEID_coreInit function and is in charge
 * of initializing the CAN HAL for the target MCU.
 * ===========================================================================*/
void can_DCM_DR_HALinit(void){

	// Write user code to initialize CAN HAL in the target MCU.
	CAN_Init_ALL_DCM();

}
