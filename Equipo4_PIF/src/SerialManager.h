/*
 * SerialManager.h
 *
 *  Created on: 15 mar. 2021
 *      Author: ssalazar
 */

#ifndef SERIALMANAGER_H_
#define SERIALMANAGER_H_



extern void SerialManager_Init();
extern void DGB_Print(char* module, char*text);
extern void DGB_Error(char* module, char*text);

#endif /* SERIALMANAGER_H_ */
