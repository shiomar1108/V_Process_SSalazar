/*
 * ManufacturingManager.h
 *
 *  Created on: 19 mar. 2021
 *      Author: Abrah
 */

#ifndef MANUFACTURINGMANAGER_H_
#define MANUFACTURINGMANAGER_H_

typedef enum {
	DriverDoor = 0,
	PassengerDoor = 1,
	RearLeftDoor = 2,
	RearRightDoor = 3
}manufacturing_t;

extern void ManufacturingManager_Init(void);
extern manufacturing_t getVariantId(void);
extern void ProcessTesterCMD(char* cmd);


#endif /* MANUFACTURINGMANAGER_H_ */
