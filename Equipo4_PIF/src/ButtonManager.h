/*
 * ButtonManager.h
 *
 *  Created on: 15 mar. 2021
 *      Author: Abrah
 */

#ifndef BUTTONMANAGER_H_
#define BUTTONMANAGER_H_

/* Button state */
typedef enum {
	RELEASE = 0,
	SHORT = 1,
	LONG = 2,
	STUCK = 3,
	LOCK = 4,
	UNLOCK = 5,
	Not_Present = 6
} ButtonPress_t;

/* Struct for DCM App */
typedef struct{
	ButtonPress_t Win_Open;
	ButtonPress_t Win_Close;
	ButtonPress_t Psn_Open;
	ButtonPress_t Psn_Close;
	ButtonPress_t RR_Open;
	ButtonPress_t RR_Close;
	ButtonPress_t RL_Open;
	ButtonPress_t RL_Close;
	ButtonPress_t RWin_Lock;
	ButtonPress_t Door_Lock;
	ButtonPress_t Door_Unlock;
}Btn_list_t;


extern void ButtonManager_Init(void);
extern void ButtonManager(void);
extern Btn_list_t getBtnList(void);
extern void setBtnList(Btn_list_t data);

#endif /* BUTTONMANAGER_H_ */
