/*
 * buttons.h
 *
 * Created: 26-3-2019 17:20:20
 *  Author: Maurice
 */ 

#ifndef BUTTONS_H_
#define BUTTONS_H_

enum eStatus {GOING_UP,GOING_DOWN,GOING_LEFT,GOING_RIGHT, WAITING};

int checkDirection(void);

#endif /* BUTTONS_H_ */
