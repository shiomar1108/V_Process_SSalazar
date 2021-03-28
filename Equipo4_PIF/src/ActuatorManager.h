/*
 * Actuator.h
 *
 *  Created on: 12 mar. 2021
 *      Author: Javier
 */

#ifndef ACTUATORMANAGER_H_
#define ACTUATORMANAGER_H_

#define	LOCK_DOOR_ACTUATION 0
#define	UNLOCK_DOOR_ACTUATION 1
#define	OPEN_WINDOW_ACTUATION 2
#define	CLOSE_WINDOW_ACTUATION 3
#define	OPEN_GLOBAL_WINDOW_ACTUATION  4
#define CLOSE_GLOBAL_WINDOW_ACTUATION  5
#define CANCEL_WINDOW_ACTUATION 6

typedef enum {
	DOOR_LOCKED = 0,
	DOOR_UNLOCKED = 1,
	DOOR_UNKNOWN = 2,
	DOOR_ERROR = 3
}doorlock_sts_config_t;

typedef enum {
	IN_BETWEEN = 0,
	WINDOW_COMPLETELY_OPEN = 1,
	WINDOW_COMPLETELY_CLOSE = 2,
	WINDOW_ERROR = 3
}windowPosition_sts_config_t;

extern void Actuator_Manager_Init(void);
extern doorlock_sts_config_t determineDoorLockingStatus(void);
extern windowPosition_sts_config_t determineWindowPosition(void);
extern void setActuatorAction(int actuatorAction);
extern void processWindowControl(void);
extern void processDoorControl(void);
extern void setHWMotorStatus(bool Status);
extern void setHWSolenoidStatus(bool Status);



#endif /* ACTUATORMANAGER_H_ */
