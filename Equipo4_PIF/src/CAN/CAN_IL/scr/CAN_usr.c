/*
 * CAN_usr.c
 *
 *  Created on: 13 mar. 2021
 *      Author: edgar
 */

/*FreeRtos includes*/
#include "FreeRTOS.h"
#include "task.h"

/*SDK includes*/
#include "interrupt_manager.h"
#include "sdk_project_config.h"
#include "BoardDefines.h"

/* CAN IL includes */
//#include "comgen_CAN_DCM_DR_core.h"
//#include "comgen_CAN_DCM_DR_hal.h"

/* Need to add to the Include Path (-I):
 * ../SDK/platform/drivers/src/flexcan
 * for the compiler to find "flexcan_hw_access.h" and
 * "flexcan_irq.h" */
#include "flexcan_irq.h"
#include "flexcan_hw_access.h"

/* ----------------------  CAN USER and IL includes  ---------------------- */
#include "CAN_usr.h"


/* ---------------------- ---------------------- ---------------------- /
 *
 * The following variables are just to test my branch (EDGAR)
 * they will be included in other SW modules
 *
 *--------------------- ---------------------- ---------------------- */
// hold the sw variant for CAN layer,
uint8_t	r_swVariant = 0xFF;

/* ---------------------- Here end my variables ---------------------- */



/* ---------------------- Private Function Prototypes ---------------------- */

static void CAN_pal_event_callback(uint32_t instance, can_event_t eventType, uint32_t objIdx, void *driverState);
static void isr_CAN_MB(void);
static void Set_CAN_SWVariat(uint8_t CAN_SWVariant);


/* ---------------------- CAN variable definitions ---------------------- */

#define FLEXCAN_INSTANCE 	can_instance0.instIdx
/* Symbol required for FLEXCAN_SetMsgBuffIntCmd API
 * A warning may be appear but it is necessary for the tool*/
extern CAN_Type * const  p_flexcanBase[] = CAN_BASE_PTRS;

/* ---------------------- Global private data definition ---------------------- */

can_message_t	s_rx_message;				// Global variable to receive the message from CAN PAL
can_event_t		e_can_event_type;			// Global variable to hold the last generated event from CAN

/* Default information for TX messages */
flexcan_data_info_t s_default_tx_info = {
	.msg_id_type = FLEXCAN_MSG_ID_STD, 	/* Send standard ID messages by default */
	.data_length = 8, 					/* By default assume 8 data bytes.
										 * Needs to change per each transmission. */
#if FEATURE_CAN_HAS_FD
	.fd_enable = false,					/* Assume no FD frame by default */
	.fd_padding = 0,					/* Assume padding of 0x00 by default */
	.enable_brs = false,            	/* Disable bit rate switch in CAN FD frame by default */
#endif
	.is_remote = false              	/* Assume data frame by default (not remote frame) */
};


/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/

/* ============================================================================
 * Function Name: CAN_HandlerInit
 * Description:	Function to initialize the corresponding DCU HAL.
 * Arguments: @r_swVariant,
 * Return:	N/A,
 * ========================================================================= */
void Set_CAN_SWVariat(const uint8_t CAN_SWVariant){
	uint8_t *p_CAN_SWVariat;			// Pointer to modify SW Variant global variable

	p_CAN_SWVariat = &r_swVariant;		// Get r_swVariant address,
	*p_CAN_SWVariat = CAN_SWVariant;	// Update SW variant

}

/* ============================================================================
 * Function Name: CAN_HandlerInit
 * Description:	Function to initialize the corresponding DCU HAL.
 * Arguments: @r_swVariant,
 * Return:	N/A,
 * ========================================================================= */
extern void CAN_HandlerInit(const uint8_t l_swVariant){

#ifdef EN_ASSERT
		/* A invalid SW variant was received*/
		DEV_ASSERT((l_swVariant == tSW_VARIANT_DR) ||
				(l_swVariant == tSW_VARIANT_PS) ||
				(l_swVariant == tSW_VARIANT_RL) ||
				(l_swVariant == tSW_VARIANT_RR)
				);
#endif

	/*Determine the SW variant*/
	switch(l_swVariant){

		case tSW_VARIANT_DR:
			/*Configure for driver door*/
			can_DCM_DR_coreInit();
			Set_CAN_SWVariat(tSW_VARIANT_DR);
		break;

			/*Configure for passenger door*/
		case tSW_VARIANT_PS:
			can_DCM_PS_coreInit();
			Set_CAN_SWVariat(tSW_VARIANT_PS);
		break;

			/*Configure for Rear Left door*/
		case tSW_VARIANT_RL:
			can_DCM_RL_coreInit();
			Set_CAN_SWVariat(tSW_VARIANT_RL);
		break;

			/*Configure for Rear Right door*/
		case tSW_VARIANT_RR:
			can_DCM_RR_coreInit();
			Set_CAN_SWVariat(tSW_VARIANT_RR);
		break;
	}
}

/* ============================================================================
 * Function Name: CAN_Init_ALL_DCM
 * Description:	This will initialize the CAN PAL to be used by all DCU modules.
 * Arguments: @ptr_can_pal_buff_config
 * Return: @l_error
 * ========================================================================= */
extern status_t CAN_Init_ALL_DCM(void){
	volatile status_t l_error;						// Save the l_error status

	can_buff_config_t s_can_pal_buff_config = { 	//Generic buffer configuration
			.enableFD 	= false,
			.enableBRS 	= false,
			.fdPadding 	= 0x00,
			.idType 	= CAN_MSG_ID_STD,
			.isRemote 	= false
	};

	/* Initialize CAN Pal  */
	l_error = CAN_Init(&can_instance0, &can_config0);

	/* Initialize CAN PAL RX Buffers */
	l_error = CAN_ConfigRxBuff(&can_instance0, CAN_PAL_RX_BUFFER_ALL, &s_can_pal_buff_config, 0x00);

	/* Set Global Acceptance filter (will override individual MB filters) */
	/* Filter will accept any incoming message */
	/* Set acceptance filter for Standard IDs */
	FLEXCAN_DRV_SetRxMaskType(FLEXCAN_INSTANCE, FLEXCAN_RX_MASK_GLOBAL);
	FLEXCAN_DRV_SetRxMbGlobalMask(FLEXCAN_INSTANCE,FLEXCAN_MSG_ID_STD,0);

	/* Initialize CAN Pal Tx Buffer */
	/* DCU 1 will transmit in buffer CAN_PAL_TX_BUFFER_DCU_1 */
	l_error = CAN_ConfigTxBuff(&can_instance0,CAN_PAL_TX_BUFFER_ALL, &s_can_pal_buff_config);

	/* Associate CAN event callback */
	/* This callback will be called within ISR context */
	l_error = CAN_InstallEventCallback(&can_instance0,&CAN_pal_event_callback,NULL);

	/* Install CAN0 MB interrupt handler */
	/* Same interrupt is shared for events on message buffers 0 to 15 */
	/* Using own ISR function */
	/* Enable CAN0 MB interrupt handler */
	INT_SYS_InstallHandler(CAN0_ORed_0_15_MB_IRQn, isr_CAN_MB, NULL);
	INT_SYS_EnableIRQ(CAN0_ORed_0_15_MB_IRQn);

	/* To allow calls safe APIs from FreeRTOS, setting interrupt priority to
	be equal to or lower than configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY. */
	/* Enable RX/TX interrupts */
	INT_SYS_SetPriority(CAN0_ORed_0_15_MB_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY );
	l_error = FLEXCAN_SetMsgBuffIntCmd(p_flexcanBase[FLEXCAN_INSTANCE],0,true);
	l_error = FLEXCAN_SetMsgBuffIntCmd(p_flexcanBase[FLEXCAN_INSTANCE],1,true);

	/* Set-up reception of MB 0 (reception message buffer) */
	/* Received data will be put into the global variable s_rx_message */
	l_error = CAN_Receive(&can_instance0, CAN_PAL_RX_BUFFER_ALL, &s_rx_message);

	#ifdef EN_ASSERT
		DEV_ASSERT(l_error == STATUS_SUCCESS);
	#endif

	return l_error;
}

/* ============================================================================
 * Function Name: CAN_pal_event_callback
 * Description: CAN callback, executed in ISR context
 * Arguments:
 * 	@instance
 * 	@eventType
 * 	@objIdx
 * 	@*driverState
 * Return: N/A
 * ========================================================================= */
static void CAN_pal_event_callback(uint32_t instance, can_event_t eventType,
							uint32_t objIdx,
							void *driverState){
	/* Set the received event to a global variable */
	e_can_event_type = eventType;

	if(eventType == CAN_EVENT_RX_COMPLETE)
	{
//		PINS_DRV_TogglePins(LED_GPIO, (1 << LED1));
		/* Successful reception has been completed */
		/* Data from CAN PAL shall be available at variable s_rx_message */
		switch(r_swVariant){

			case tSW_VARIANT_DR:
				can_DCM_DR_HALreceiveMsg(s_rx_message.id, s_rx_message.data, s_rx_message.length);
				break;
			case tSW_VARIANT_PS:
				/* call HALreceiveMsg function for DCM_PS */
				can_DCM_PS_HALreceiveMsg(s_rx_message.id, s_rx_message.data, s_rx_message.length);
				break;
			case tSW_VARIANT_RL:
				/* call HALreceiveMsg function for DCM_RL */
				can_DCM_RL_HALreceiveMsg(s_rx_message.id, s_rx_message.data, s_rx_message.length);
				break;
			case tSW_VARIANT_RR:
				/* call HALreceiveMsg function for DCM_RR */
				can_DCM_RR_HALreceiveMsg(s_rx_message.id, s_rx_message.data, s_rx_message.length);
				break;
		}
	}
	else if(eventType == CAN_EVENT_TX_COMPLETE){

//		PINS_DRV_TogglePins(LED_GPIO, (1 << LED2));

		/* Call CAN IL message TX confirmation and TX retry strategy */
		switch(r_swVariant){

			case tSW_VARIANT_DR:
				/* Successful transmission. Confirm TX */
				can_DCM_DR_HALconfirmTxMsg();
				/* Trigger retry strategy */
				can_DCM_DR_txRetry();

			break;
			case tSW_VARIANT_PS:
				//* Successful transmission. Confirm TX */
				can_DCM_PS_HALconfirmTxMsg();
				/* Trigger retry strategy */
				can_DCM_PS_txRetry();
			break;
			case tSW_VARIANT_RL:
				//* Successful transmission. Confirm TX */
				can_DCM_RL_HALconfirmTxMsg();
				/* Trigger retry strategy */
				can_DCM_RL_txRetry();
			break;
			case tSW_VARIANT_RR:
				//* Successful transmission. Confirm TX */
				can_DCM_RR_HALconfirmTxMsg();
				/* Trigger retry strategy */
				can_DCM_RR_txRetry();
			break;
		}
	}
	else{
		/* Nothing to do */
//		PINS_DRV_SetPins(LED_GPIO, (1 << LED1));
//		PINS_DRV_SetPins(LED_GPIO, (1 << LED2));
	}
}

/* ============================================================================
 * Function Name: isr_CAN_MB
 * Description:	CAN ISR handler
 * Arguments:
 * Return: N/A
 * ========================================================================= */
static void isr_CAN_MB(void){

	status_t l_error;

//	PINS_DRV_SetPins(LED_GPIO, (1 << LED1));
//	PINS_DRV_ClearPins(LED_GPIO, (1 << LED2));

	/* CAll generated ISR from CAN driver */
	CAN0_ORed_0_15_MB_IRQHandler();

	/* IRQ disables RX interrupt, re-enable it to have continuous reception. */
	if(e_can_event_type == CAN_EVENT_RX_COMPLETE){
		l_error = CAN_Receive(&can_instance0, CAN_PAL_RX_BUFFER_ALL, &s_rx_message);
#ifdef EN_ASSERT
	DEV_ASSERT(l_error == STATUS_SUCCESS);
#endif
	}(void)l_error;
}

/* ============================================================================
 * Function Name: SendCANMessage
 * Description:
 * Arguments:
 * 	@msg_id,	ID to the CAN frame that will be send
 * 	@msg_length, length of the message to be transmitted
 * 	@*p_data, pointer to an array that contains the data to be transmitted
 * Return:
 * 	@l_error, if there was a error, ths
 * ========================================================================= */
extern status_t SendCANMessage(const uint32_t msg_id, const uint32_t msg_length, uint8_t *p_data){

	volatile status_t l_error;


#if FEATURE_CAN_HAS_FD
	/* do nothing */
#else
	/*CAN is a standard frame*/
	#ifdef EN_ASSERT

		DEV_ASSERT(msg_length <= dMAX_STD_CAN_MSG_LENGTH);		// Check the length of the message

		DEV_ASSERT(msg_length == sizeof(*p_data));				// The size of the array match the size of the message

		DEV_ASSE RT((r_swVariant == tSW_VARIANT_DR) && (msg_id == 0x201UL) ||	/* check if its a valid ID*/
					(r_swVariant == tSW_VARIANT_PS) && (msg_id == 0x202UL) ||
					(r_swVariant == tSW_VARIANT_RL) && (msg_id == 0x203UL) ||
					(r_swVariant == tSW_VARIANT_RR) && (msg_id == 0x204UL) ||
				);
	#endif
#endif

	s_default_tx_info.data_length = msg_length;

		/* Request msg transmission to CAN driver */
		/* Will use the defined message buffer (1 for TX) */
	l_error = FLEXCAN_DRV_Send(FLEXCAN_INSTANCE,
								CAN_PAL_TX_BUFFER_ALL,
								&s_default_tx_info,
								msg_id,
								p_data);

#ifdef EN_ASSERT
		DEV_ASSERT(l_error == STATUS_SUCCESS);
#endif

		return l_error;
}



/* ============================================================================
 * Function Name: app_getTxdId
 * Description:
 * Arguments:
 * Return: 	@l_error, if there was a error, ths
 * ========================================================================= */
uint32_t app_getTxdId(void){
	uint32_t txd_msg_id;

	/* Since the same message buffer CAN_PAL_TX_BUFFER is used for ALL the
	 * nodes (DCM_DR, DCM_PS, DCM_RL, DCM_RR) this same function can be
	 * reused as it is for all the can_<NODEID>_HALgetTxdMsgId functions... */
	volatile uint32_t *flexcan_mb = \
			FLEXCAN_GetMsgBuffRegion(p_flexcanBase[FLEXCAN_INSTANCE], CAN_PAL_TX_BUFFER_ALL);
	volatile uint32_t *flexcan_mb_id   = &flexcan_mb[1];

	txd_msg_id = (*flexcan_mb_id >> CAN_ID_STD_SHIFT) \
			& (CAN_ID_STD_MASK >> CAN_ID_STD_SHIFT);

	return txd_msg_id;
}
