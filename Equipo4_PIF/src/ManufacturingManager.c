/*
 * ManufacturingManager.c
 *
 *  Created on: 19 mar. 2021
 *      Author: Abrah
 */
#include "sdk_project_config.h"
#include "ButtonManager.h"
#include "ManufacturingManager.h"

#define VariantPort		PTB
#define J0				2U
#define J1				3U

typedef enum {
	Press = true,
	NoPress = false
}jumper_state;

void setVariantId(manufacturing_t variantState);

manufacturing_t VariantId;

void ManufacturingManager_Init(void)
{
	volatile jumper_state JP0;
	volatile jumper_state JP1;
	/* Read input bits of PORTB */
	JP0 = (PINS_DRV_ReadPins(PTB)>>J0)&0x01;	/* Jumper 0 */
	JP1 = (PINS_DRV_ReadPins(PTB)>>J1)&0x01;	/* Jumper 1 */

	if(JP0 == NoPress && JP1 == NoPress)
	{
		//VariantId=DriverDoor;
		setVariantId(DriverDoor);
	}
	else if(JP0 == NoPress && JP1 == Press)
	{
		//VariantId=PassengerDoor;
		setVariantId(PassengerDoor);
	}
	else if(JP0 == Press && JP1 == NoPress)
	{
		//VariantId=RearLeftDoor;
		setVariantId(RearLeftDoor);
	}
	else if(JP0 == Press && JP1 == Press)
	{
		//VariantId=RearRightDoor;
		setVariantId(RearRightDoor);
	}
	else
	{
		/* Do nothing */
	}
}

manufacturing_t getVariantId(void)
{
	return VariantId;
}

void setVariantId(manufacturing_t variantState)
{
	VariantId = variantState;
}


void ProcessTesterCMD(char* cmd)
{

}
