/*============================================================================*/
/*                           calvOS Project                                   */
/*============================================================================*/
/** \file		comgen_CAN_DCM_PS_core.c                                      */
/** \brief     	Source file for CAN Core functionality.
 *  \details   	Implements the CAN core functionality for the handling of the
 *  			defined messages/signals in the given network and given node.
 *  \author    	Carlos Calvillo
 *  \version   	1.0
 *  \date      	2021-01-15
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
#include <string.h>
#include "calvos.h"
#include "comgen_CAN_DCM_PS_core.h"
#include "comgen_CAN_network.h"
#include "comgen_CAN_DCM_PS_callbacks.h"
#include "comgen_CAN_DCM_PS_hal.h"

/* Exported Function Prototypes */

/* Private Function Prototypes */

/* Private macro definitions */

/* Private type definitions */

/* Exported data */

/* Rx message data buffer */
uint8_t can_DCM_PS_RxDataBuffer[kCAN_DCM_PS_RxMsgsTotalLen];

/* Rx available flags buffer */
uint8_t can_DCM_PS_avlbl_buffer[kCAN_DCM_PS_avlbl_buffer_len];

/* RX available flags */
/* RX signal availability flag indexes */
#define kCAN_DCM_PS_sig_avlbl_idx_BCM_5_MC                (0u)
#define kCAN_DCM_PS_sig_avlbl_idx_SysPwrMode              (1u)
#define kCAN_DCM_PS_sig_avlbl_idx_BCM_5_CMAC              (2u)
#define kCAN_DCM_PS_sig_avlbl_idx_BCM_2_MC                (0u)
#define kCAN_DCM_PS_sig_avlbl_idx_ConfortCmd              (1u)
#define kCAN_DCM_PS_sig_avlbl_idx_BCM_2_CMAC              (2u)
#define kCAN_DCM_PS_sig_avlbl_idx_DCU_1_WindowPos         (0u)
#define kCAN_DCM_PS_sig_avlbl_idx_DCU_1_LockingReq        (1u)
#define kCAN_DCM_PS_sig_avlbl_idx_DCU_1_WindowOp          (2u)
#define kCAN_DCM_PS_sig_avlbl_idx_DCU_1_RearWindowLock    (3u)
#define kCAN_DCM_PS_sig_avlbl_idx_DCU_1_DoorLockSts       (4u)
#define kCAN_DCM_PS_sig_avlbl_idx_DCU_1_WdwCtrl_RR        (5u)
#define kCAN_DCM_PS_sig_avlbl_idx_DCU_1_WdwCtrl_RL        (6u)
#define kCAN_DCM_PS_sig_avlbl_idx_DCU_1_WdwCtrl_Pas       (7u)
#define kCAN_DCM_PS_sig_avlbl_idx_DCU_1_MC                (8u)
#define kCAN_DCM_PS_sig_avlbl_idx_DCU_1_CRC               (9u)

/* Array of Rx messages dynamic data */
CANrxMsgDynamicData can_DCM_PS_rxMsgDynamicData[kCAN_DCM_PS_nOfRxMsgs];

const CANrxMsgStaticData can_DCM_PS_rxMsgStaticData[kCAN_DCM_PS_nOfRxMsgs] = {\
		{kCAN_msgId_BCM_5,	kCAN_DCM_PS_msgTimeout_BCM_5,	&can_DCM_PS_BCM_5_rx_callback,	&can_DCM_PS_BCM_5_timeout_callback,	 \
				&can_DCM_PS_RxDataBuffer[0],	&can_DCM_PS_avlbl_buffer[kCAN_DCM_PS_avlbl_buffer_idx_BCM_5],	kCAN_DCM_PS_avlbl_slot_len_BCM_5,	 \
				&can_DCM_PS_rxMsgDynamicData[0],	{8u,	kFalse},	NULL,	NULL}, \
		{kCAN_msgId_DCU_1,	kCAN_DCM_PS_msgTimeout_DCU_1,	&can_DCM_PS_DCU_1_rx_callback,	&can_DCM_PS_DCU_1_timeout_callback,	 \
				&can_DCM_PS_RxDataBuffer[8],	&can_DCM_PS_avlbl_buffer[kCAN_DCM_PS_avlbl_buffer_idx_DCU_1],	kCAN_DCM_PS_avlbl_slot_len_DCU_1,	 \
				&can_DCM_PS_rxMsgDynamicData[1],	{8u,	kFalse},	&can_DCM_PS_rxMsgStaticData[0],	&can_DCM_PS_rxMsgStaticData[2]}, \
		{kCAN_msgId_BCM_2,	kCAN_DCM_PS_msgTimeout_BCM_2,	&can_DCM_PS_BCM_2_rx_callback,	&can_DCM_PS_BCM_2_timeout_callback,	 \
				&can_DCM_PS_RxDataBuffer[16],	&can_DCM_PS_avlbl_buffer[kCAN_DCM_PS_avlbl_buffer_idx_BCM_2],	kCAN_DCM_PS_avlbl_slot_len_BCM_2,	 \
				&can_DCM_PS_rxMsgDynamicData[2],	{8u,	kFalse},	NULL,	NULL}};

/* Rx search tree starting index */
#define kCAN_DCM_PS_RxSearchStartIdx		(1u)

/* Tx message data buffer */
uint8_t can_DCM_PS_TxDataBuffer[kCAN_DCM_PS_TxMsgsTotalLen];

/* Array of Tx messages dynamic data */
CANtxMsgDynamicData can_DCM_PS_txMsgDynamicData[kCAN_DCM_PS_nOfTxMsgs];

/* Tx transmission queue */
CANtxQueue can_DCM_PS_txQueue;

/* Message being transmitted */
const CANtxMsgStaticData* can_DCM_PS_transmittingMsg;

/* Array of Tx messages static data */
const CANtxMsgStaticData can_DCM_PS_txMsgStaticData[kCAN_DCM_PS_nOfTxMsgs] = {\
		{kCAN_msgId_DCU_2,	kCAN_msgTxPeriod_DCU_2,	&can_DCM_PS_DCU_2_tx_callback,	 \
				&can_DCM_PS_TxDataBuffer[0],	&can_DCM_PS_txMsgDynamicData[0],	{8u,	kFalse,	kCAN_msgTxType_DCU_2}}};

/* =============================================================================
 * 	Function definitions
 * ===========================================================================*/

/* ===========================================================================*/
/** Function for processing reception of a CAN msg.
 *
 * Verifies if received message belongs to this node and if so, signal its
 * reception and invokes the corresponding callback.
 * This function is typically called from the CAN RX ISR.
 *
 * @param msg_id 	Id of the received message.
 * @param data_in 	Pointer to the message's received data.
 *
 * IMPORTANT: This function needs to be called by user's application upon
 * indication of successful reception by the CAN HAL (typically within ISR
 * context).
 * ===========================================================================*/
void can_DCM_PS_processRxMessage(uint32_t msg_id, uint8_t * data_in, uint8_t data_len){
	const CANrxMsgStaticData* msg_static_data;
	// Search for message to see if its suscribed by this node.
	msg_static_data = can_traverseRxSearchTree(msg_id, \
			&can_DCM_PS_rxMsgStaticData[kCAN_DCM_PS_RxSearchStartIdx],  \
			kCAN_DCM_PS_nOfRxMsgs);
	if(msg_static_data != NULL){
		// Consider message as valid if it matches the expected length
		if(data_len == msg_static_data->fields.len){
			if(data_len != 0){
				// Copy data to buffer
				memcpy(msg_static_data->data, data_in, msg_static_data->fields.len);
				// Set Signals available flags
				if(msg_static_data->sig_avlbl_buf_len == 1){
					*msg_static_data->sig_avlbl_flags = kAllOnes8;
				}else{
					for(uint32_t i=0; i < msg_static_data->sig_avlbl_buf_len; i++){
						msg_static_data->sig_avlbl_flags[i] = kAllOnes8;
					}
				}
			}

			// Set Message available flags
			msg_static_data->dyn->available.all = kAllOnes32;

			// clear timeout flag
			msg_static_data->dyn->timedout = kFalse;
			// Invoke rx callback
			if(msg_static_data->rx_callback != NULL){
				(msg_static_data->rx_callback)();
			}
		}
	}
}
	

/* ===========================================================================*/
/** Function for transmitting a CAN msg.
 *
 * Triggers the transmission of the specified CAN message.
 *
 * @param msg_idx 	index of the message to be transmitted.
 * @Return 		Returns @c kNoError if message was triggered for transmission
 * 				by HAL or if it was successfully queued for a transmission
 * 				retry. Returns @c kError otherwise (HAL busy, queue full, wrong
 * 				message index provided).
 * ===========================================================================*/
CalvosError can_DCM_PS_transmitMsg(CAN_DCM_PS_txMsgs msg_idx){
	CalvosError return_value = kError;

	// Trigger CAN transmission to HAL
	if(msg_idx < kCAN_DCM_PS_nOfTxMsgs){
		return_value = can_commonTransmitMsg(&can_DCM_PS_txMsgStaticData[msg_idx], \
								  &can_DCM_PS_txQueue, \
								  &can_DCM_PS_HALtransmitMsg, \
								  &can_DCM_PS_transmittingMsg);
	}

	return return_value;
}
	

/* ===========================================================================*/
/** Function for processing cyclic CAN TX messages.
 *
 * Triggers the transmission of CAN messages set as cyclic or cyclic+spontan.
 * IMPORTANT: This function needs to be called by user's application in a
 * periodic task with the period indicated in this function's name.
 * ===========================================================================*/
void can_task_10ms_DCM_PS_txProcess(void){

	// TODO: Implement this as a timer wheel for efficiency
	// TODO: Group tx messages with same period in single timers rather than
	// individual ones for efficiency.

	// Increment timer (up-counter since they are initialized with zero)
	can_DCM_PS_txMsgStaticData[kCAN_DCM_PS_txMsgIdx_DCU_2].dyn->period_timer++;
	if(can_DCM_PS_txMsgStaticData[kCAN_DCM_PS_txMsgIdx_DCU_2].dyn->period_timer \
	>= can_DCM_PS_txMsgStaticData[kCAN_DCM_PS_txMsgIdx_DCU_2].period){
		// Timer expired, trigger message transmission
		can_DCM_PS_transmitMsg(kCAN_DCM_PS_txMsgIdx_DCU_2);
		// Reset timer
		can_DCM_PS_txMsgStaticData[kCAN_DCM_PS_txMsgIdx_DCU_2].dyn->period_timer = 0u;
	}

}

/* ===========================================================================*/
/** Function for processing CAN TX retry mechanism.
 *
 * Triggers transmission of queued CAN messages (retry mechanism).
 * IMPORTANT: This function needs to be called by user's application either in
 * a periodic task or right after a CAN transmission within ISR context.
 * ===========================================================================*/
void can_DCM_PS_txRetry(void){
	const CANtxMsgStaticData* msg_to_retry;
	CalvosError return_value;

	// TODO: Implement max retries per message, etc.?
	// TODO: Implement an option to also "freeze" the data to the message that
	// was queued. Right now, the data will be taken from common buffer when the
	// message finally is accepted for transmission.

	msg_to_retry = can_txQueueGetHead(&can_DCM_PS_txQueue);
	if(msg_to_retry != NULL){
		// Attempt the re-transmission
		return_value = can_commonTransmitMsg(msg_to_retry, \
								  NULL, \
								  &can_DCM_PS_HALtransmitMsg, \
								  &can_DCM_PS_transmittingMsg);
		if(return_value == kNoError){
			// Transmission succeeded. Dequeue the message.
			can_txQueueDequeue(&can_DCM_PS_txQueue, NULL);
		}
	}
}

/* ===========================================================================*/
/** Set signals initial values.
 *
 * Initializes the signals with defined initial value if this is different than
 * zero (all signal data buffers are previously initialized with zeros).
 * ===========================================================================*/
void can_DCM_PS_signalsInit(void){


//	can_DCM_PS_TxDataBuffer[BYTE_POS_DCU_2_WindowPos] 	= 0;
//	can_DCM_PS_TxDataBuffer[BYTE_POS_DCU_2_LockingReq] 	= 0;
//	can_DCM_PS_TxDataBuffer[BYTE_POS_DCU_2_WindowOp] 	= 0;
	can_DCM_PS_TxDataBuffer[BYTE_POS_DCU_2_reserved_0]	= 0xFF;
	can_DCM_PS_TxDataBuffer[BYTE_POS_DCU_2_DoorLockSts] = 2;
	can_DCM_PS_TxDataBuffer[BYTE_POS_DCU_2_reserved_1] 	= 0xFF;
//	can_DCM_PS_TxDataBuffer[BYTE_POS_DCU_2_MC] 			= 0;
//	can_DCM_PS_TxDataBuffer[BYTE_POS_DCU_2_CRC] 		= 0;


}

/* ===========================================================================*/
/** Function for initialization of CAN core.
 *
 * Initializes data for CAN core functionality of current node.
 * IMPORTANT: This function needs to be called by user's application during SW
 * initialization phase.
 * ===========================================================================*/
void can_DCM_PS_coreInit(void){
	// Clear RX data buffer
	memset(&can_DCM_PS_RxDataBuffer,kCAN_RxDataInitVal,kCAN_DCM_PS_RxMsgsTotalLen);
	// Clear RX available flags buffer
	memset(&can_DCM_PS_avlbl_buffer,0u,kCAN_DCM_PS_avlbl_buffer_len);
	// Clear TX data buffer
	memset(&can_DCM_PS_TxDataBuffer,kCAN_TxDataInitVal,kCAN_DCM_PS_TxMsgsTotalLen);
	// Clear RX dynamic data
	memset(&can_DCM_PS_rxMsgDynamicData,0u,sizeof(CANrxMsgDynamicData)*(kCAN_DCM_PS_nOfRxMsgs));
	// Clear TX dynamic data
	memset(&can_DCM_PS_txMsgDynamicData,0u,sizeof(CANtxMsgDynamicData)*(kCAN_DCM_PS_nOfTxMsgs));

	// Init signal values
	can_DCM_PS_signalsInit();

	// Init TX queue
	can_txQueueInit(&can_DCM_PS_txQueue);

	// Init transmitting message
	can_DCM_PS_transmittingMsg = can_DCM_PS_txMsgStaticData;

	// Init CAN HAL
	can_DCM_PS_HALinit();
}
