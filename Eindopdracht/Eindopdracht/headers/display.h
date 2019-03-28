/*
 * display.h
 *
 * Created: 1/16/2018 8:17:18 AM
 *  Author: Bram 
 */ 

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void displayInit(void);
void startLoaction(void);
void drawImage(void);
void drawCounting(int number);
void displayInitHT16K33(uint8_t i2c_address) ;
void displaySetPixel(uint8_t x, uint8_t y);
void setStartLocation(int x,int y);
void displayDrawStart();
void displayClrPixel(uint8_t x, uint8_t y);
void update(void);
void displayClr(void);

void twi_init(void);
void twi_start(void);
void twi_stop(void);
void twi_tx(unsigned char data);

int getLocationListSize(void);
void increaseSnakeSize(void);
void addCandy(void);
int checkForCollision(int x, int y);
void resetDisplay(void);

int moveToNewLocation(int x, int y);
int moveSnakeUp(void);
int moveSnakeDown(void);
int moveSnakeLeft(void);
int moveSnakeRight(void);


#endif /* DISPLAY_H_ */