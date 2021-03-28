/*
 * CAN_usr.h
 *
 *  Created on: 13 mar. 2021
 *      Author: edgar
 */

#ifndef CAN_DRIVERS_CAN_USR_H_
#define CAN_DRIVERS_CAN_USR_H_

#include "comgen_CAN_DCM_DR_hal.h"
#include "comgen_CAN_DCM_DR_core.h"
#include "comgen_CAN_DCM_PS_hal.h"
#include "comgen_CAN_DCM_PS_core.h"
#include "comgen_CAN_DCM_RL_hal.h"
#include "comgen_CAN_DCM_RL_core.h"
#include "comgen_CAN_DCM_RR_hal.h"
#include "comgen_CAN_DCM_RR_core.h"
#include "status.h"

/* ---------------------- DEBUG Related ---------------------- */

// Enables/disables DEV_ASSERT() function
//#define EN_ASSERT

#ifdef EN_ASSERT
	// Maximum data length for STD CAN
	#define dMAX_STD_CAN_MSG_LENGTH	8
	// A dummy message to send via CAN
	#define	TX_DUMMY_MESSAGE	{0xDE, 0xAD, 0xBE, 0xEF,0xDE, 0xAD, 0xBE, 0xEF}
#endif
/*--------------------- ---------------------- ---------------------- */


/* ---------------------- Temporal definitions---------------------- */
/* only to be used on Edgar's branch  */


#define tSW_VARIANT_DR	0U
#define tSW_VARIANT_PS	1U
#define tSW_VARIANT_RL	2U
#define tSW_VARIANT_RR	3U

/*--------------------- ---------------------- ---------------------- */

/* ---------------------- Rx/Tx Buffers location ---------------------- */

#define CAN_PAL_RX_BUFFER_ALL	0U
#define CAN_PAL_TX_BUFFER_ALL	1U
/*--------------------- ---------------------- ---------------------- */


/* ---------------------- Function Prototypes ---------------------- */

extern void CAN_HandlerInit(const uint8_t sw_variant);
extern uint32_t app_getTxdId(void);
extern status_t CAN_Init_ALL_DCM(void);
extern status_t SendCANMessage(const uint32_t msg_id, const uint32_t msg_length, uint8_t *p_data);
/*--------------------- ---------------------- ---------------------- */

#endif /* CAN_DRIVERS_CAN_USR_H_ */
