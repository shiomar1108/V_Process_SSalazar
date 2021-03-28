/*
 * SerialManager.c
 *
 *  Created on: 15 mar. 2021
 *      Author: ssalazar
 */

#include "SerialManager.h"
#include "sdk_project_config.h"
#include <stdio.h>
#include <string.h>

/* Welcome message displayed at the console */
#define welcomeMsg "[Serial Manager]: Serial Manager Initialized \r\n"


/* Public Function Implementation */
void SerialManager_Init()
{
	/* Initialize LPUART instance */
	LPUART_DRV_Init(INST_LPUART_LPUART_1, &lpUartState1, &lpUartInitConfig1);
	/* Send a welcome message */
	LPUART_DRV_SendDataPolling(INST_LPUART_LPUART_1, (uint8_t *)welcomeMsg, strlen(welcomeMsg));

}
void DGB_Print(char* module,char* text)
{
	char temp[200];

	strcpy(temp,"\033[32m [");
	strcat(temp, module);
	strcat(temp, "] : ");
	strcat(temp, text);
	strcat(temp, "\r\n \033[0m");

	LPUART_DRV_SendDataPolling(INST_LPUART_LPUART_1, (uint8_t *)temp, strlen(temp));
}
void DGB_Error(char* module, char*text)
{
	char temp[200];

	strcpy(temp,"\033[31m [ERROR IN ");
	strcat(temp, module);
	strcat(temp, "] : ");
	strcat(temp, text);
	strcat(temp, " !!! \r\n \033[0m");

	LPUART_DRV_SendDataPolling(INST_LPUART_LPUART_1, (uint8_t *)temp, strlen(temp));

}
