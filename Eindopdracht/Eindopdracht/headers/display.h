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
void drawImage(void);
void displaySetPixel(uint8_t x, uint8_t y);
void displayClrPixel(uint8_t x, uint8_t y);
void displayChar(char ch, uint8_t x, uint8_t y);
void displayString(char *str, uint8_t x, uint8_t y);
void displayRotl(void);
void displayRotr(void);
void displayClr(void);

void update(void);

int moveUp(void);
int moveDown(void);
int moveLeft(void);
int moveRight(void);
void setStartLocation(int x,int y);

void increaseSnakeSize(void);
void addCandy(void);

void drawCounting(int number);
void displayDrawStart(void);
void resetDisplay(void);




#endif /* DISPLAY_H_ */