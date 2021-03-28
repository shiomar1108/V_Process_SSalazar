/*============================================================================*/
/*                           calvOS Project                                   */
/*============================================================================*/
/** \file		USER_comgen_CAN_DCM_RL_callbacks.c                            */
/** \brief     	Source file for CAN user callbacks.
 *  \details   	Definitions fo CAN callbacks to be filled-up with user code as
 *  			required.
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
#include "comgen_CAN_DCM_RL_callbacks.h"

#include "CAN_app.h"


/* =============================================================================
 * 	Function definitions
 * ===========================================================================*/

/* --------------------------- */
/* Message reception callbacks */
/* --------------------------- */
/* ===========================================================================*/
/** Callback for BCM_5 reception.
 *
 * Invoked within ISR context whenever BCM_5 is received by node DCM_RL
 *  of network B.
 * ===========================================================================*/
void can_DCM_RL_BCM_5_rx_callback(void){
	/* User code goes here... */
}

/* ===========================================================================*/
/** Callback for BCM_2 reception.
 *
 * Invoked within ISR context whenever BCM_2 is received by node DCM_RL
 *  of network B.
 * ===========================================================================*/
void can_DCM_RL_BCM_2_rx_callback(void){
	/* User code goes here... */
}

/* ===========================================================================*/
/** Callback for DCU_1 reception.
 *
 * Invoked within ISR context whenever DCU_1 is received by node DCM_RL
 *  of network B.
 * ===========================================================================*/
void can_DCM_RL_DCU_1_rx_callback(void){
	/* User code goes here... */
}

/* ===========================================================================*/
/** Callback for DCU_2 reception.
 *
 * Invoked within ISR context whenever DCU_2 is received by node DCM_RL
 *  of network B.
 * ===========================================================================*/
void can_DCM_RL_DCU_2_rx_callback(void){
	/* User code goes here... */
}


/* ------------------------- */
/* Message timeout callbacks */
/* ------------------------- */
/* ===========================================================================*/
/** Callback for BCM_5 timeout notification.
 *
 * Invoked when BCM_5 times out as per suscriber node DCM_RL
 * of network B.
 * ===========================================================================*/
void can_DCM_RL_BCM_5_timeout_callback(void){
	/* User code goes here... */
}
/* ===========================================================================*/
/** Callback for BCM_2 timeout notification.
 *
 * Invoked when BCM_2 times out as per suscriber node DCM_RL
 * of network B.
 * ===========================================================================*/
void can_DCM_RL_BCM_2_timeout_callback(void){
	/* User code goes here... */
}
/* ===========================================================================*/
/** Callback for DCU_1 timeout notification.
 *
 * Invoked when DCU_1 times out as per suscriber node DCM_RL
 * of network B.
 * ===========================================================================*/
void can_DCM_RL_DCU_1_timeout_callback(void){
	/* User code goes here... */
}
/* ===========================================================================*/
/** Callback for DCU_2 timeout notification.
 *
 * Invoked when DCU_2 times out as per suscriber node DCM_RL
 * of network B.
 * ===========================================================================*/
void can_DCM_RL_DCU_2_timeout_callback(void){
	/* User code goes here... */
}

/* ------------------------------ */
/* Message transmission callbacks */
/* ------------------------------ */
/* ===========================================================================*/
/** Callback for DCU_3 transmission notification.
 *
 * Invoked when DCU_3 is transmitted as per publisher node DCM_RL
 * of network B.
 * ===========================================================================*/
void can_DCM_RL_DCU_3_tx_callback(void){
	/* A message was successfully send*/
	uint8_t l_MessageCounter;

	l_MessageCounter = CAN_DCM_RL_get_direct_DCU_3_MC() + 1;
	if(l_MessageCounter > 0xFF){
		CAN_DCM_RL_update_direct_DCU_3_MC(0x00)
	}else{
		CAN_DCM_RL_update_direct_DCU_3_MC(l_MessageCounter)
	}
}
