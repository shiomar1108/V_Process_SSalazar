/*
 * DCM_App.h
 *
 *  Created on: 12 mar. 2021
 *      Author: ssalazar
 */

#ifndef DCM_APP_H_
#define DCM_APP_H_

#include <stdint.h>
#include <stdbool.h>

/* Public Function Prototype */
extern void DCM_App_Init( void );
extern void DCM_Process_Req( void );

/* Flag setting function for CANManager and ButtonManager */
extern void setManualFlag (bool data);
extern void setTestFlag (bool data);

#endif /* DCM_APP_H_ */
