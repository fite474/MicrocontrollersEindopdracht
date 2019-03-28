/*
 * display.h
 *
 * Created: 1/16/2018 8:17:18 AM
 *  Author: Gebruiker
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

void displayInit(void);
void startLoaction(void);
void drawImage(void);
void displayInitHT16K33(uint8_t i2c_address) ;
void displaySetPixel(uint8_t x, uint8_t y);
void setStartLocation(int x,int y);
void displayClrPixel(uint8_t x, uint8_t y);
void update(void);
void displayRotl(void);
void displayRotr(void);
void displayClr(void);
void displayChar(char ch, uint8_t x, uint8_t y);
void displayString(char *str, uint8_t x, uint8_t y);

void twi_init(void);
void twi_start(void);
void twi_stop(void);
void twi_tx(unsigned char data);

int getLocationListSize();
void increaseSnakeSize(void);
void moveToNewLocation(int x, int y);

void moveSnakeUp(void);
void moveSnakeDown(void);
void moveSnakeLeft(void);
void moveSnakeRight(void);

#endif /* DISPLAY_H_ */