/*
 * display.c
 *
 * Created: 1/16/2018 8:16:59 AM
 *  Author: Diederich Kroeske
 */ 

#include <avr/io.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FourSegmentDisplay.h"
#include "display.h"
#include "fonts.h"

// HT16K33 routines
void displayInitHT16K33(uint8_t i2c_address);

// I2C routines
void twi_init(void);
void twi_start(void);
void twi_stop(void);
void twi_tx(unsigned char data);

// I2C address of display
#define D0_I2C_ADDR	((0x70 + 2) << 1)

// Display buffer in ATMEGA memory
#define	width	8 * 1		// 1 displays width
#define	height	8			// 1 display height
uint8_t buf[width*height/8];
int maxSize = 4;
int counter = 0;
typedef struct{
	int x;
	int y;
	}locatie;

typedef struct{
	locatie loc;
	int number;
	void* next;	
	}locatieList;

locatieList *locList;

locatie currenLocation;
/******************************************************************/
void displayInit(void) 
/*
short:			Init display
inputs:			
outputs:		-
notes:			Init display
Version :    	DMK, Initial code
*******************************************************************/
{
	twi_init();							// Enable TWI interface
	displayInitHT16K33(D0_I2C_ADDR);	// Iit display
	locList = NULL;
}

void startLoaction(void){
	locatie loc;

}


void drawImage(void){
	
	buf[0]= 0b01111110;
	buf[1]= 0b10011001;
	buf[2]= 0b11000011;
	buf[3]= 0b11111111;
	buf[4]= 0b00011000;
	buf[5]= 0b00111100;
	buf[6]= 0b01111110;
	buf[7]= 0b11111111;
}
/******************************************************************/
void displayInitHT16K33(uint8_t i2c_address) 
/*
short:
inputs:
outputs:
notes:
Version :    	DMK, Initial code
*******************************************************************/
{
	// System setup page 30 ht16k33 datasheet
	twi_start();
	twi_tx(i2c_address);	// Display I2C addres + R/W bit
	twi_tx(0x21);	// Internal osc on (page 10 HT16K33)
	twi_stop();
		
	// ROW/INT set. Page 31 ht16k33 datasheet
	twi_start();
	twi_tx(i2c_address);	// Display I2C address + R/W bit
	twi_tx(0xA0);	// HT16K33 pins all output (default)
	twi_stop();

	// Dimming set
	twi_start();
	twi_tx(i2c_address);	// Display I2C address + R/W bit
	twi_tx(0xE1);	// Display Dimming 2/16 duty cycle
	twi_stop();

	// Display set
	twi_start();
	twi_tx(i2c_address);	// Display I2C address + R/W bit
	twi_tx(0x81);			// Display ON, Blinking OFF
	twi_stop();
	
	// Beeld een patroon af op display (test)
	twi_start();
	twi_tx(i2c_address);
	twi_tx(0x00);
	uint8_t a = 0x55;
	for( uint8_t idx = 0; idx < 8; idx++ ) {
		a ^= 0xFF;
		uint8_t data = (a >> 1) | ((a<<7) & 0x80);
		twi_tx( data);
		twi_tx( 0x00);
	}
	twi_stop();
}

/******************************************************************/
void displaySetPixel(uint8_t x, uint8_t y)
/*
short:			
inputs:			
outputs:		
notes:			
Version :    	DMK, Initial code
*******************************************************************/
{
	//int binary[8]={1,2,4,8,16,32,64,128};
		
	uint8_t newByte = 1 << y;
	//newByte = newByte << y;
	
	buf[x] = buf[x] | newByte;
	
	
	
	//buf[x] = binary[y];
}


void setStartLocation(int x,int y){
	currenLocation.x = x;
	currenLocation.y = y;
	
	locList = (locatieList *)malloc(sizeof(locatieList));
	locList->loc = currenLocation;
	locList->number = counter;
	locList->next = NULL;
	counter++;
	//(x,y);
	displaySetPixel(x,y);
	update();
}
/******************************************************************/
void displayClrPixel(uint8_t x, uint8_t y)
/*
short:
inputs:
outputs:
notes:
Version :    	DMK, Initial code
*******************************************************************/
{
	uint8_t newByte = 1 << y;
	//newByte = newByte << y;
	//writeLedDisplay(x+y * 100);
	buf[x] = buf[x] ^ newByte;
}

/******************************************************************/
void update()
/*
short:		Write buffer to display
inputs:
outputs:
notes:		Let op de 'vreemde' shift, foutje in printplaat?
Version:	DMK, Initial code
*******************************************************************/
{
	// Second display
	twi_start();
	twi_tx(D0_I2C_ADDR);
	twi_tx(0x00);
	for( uint8_t idx = 0; idx < 8; idx++ ) {
		uint8_t a = buf[7 + 0 * 8 - idx];
		uint8_t data = (a >> 1) | ((a<<7) & 0x80);
		twi_tx( data);
		twi_tx( 0x00);
	}
	twi_stop();
}

/******************************************************************/
void displayRotl(void)
/*
short:		Rotate buffer to the left
inputs:
outputs:
notes:
Version:	DMK, Initial code
*******************************************************************/
{
}

/******************************************************************/
void displayRotr(void)
/*
short:		Rotate buffer to the right
inputs:
outputs:
notes:
Version:	DMK, Initial code
*******************************************************************/
{
}

/******************************************************************/
void displayClr(void)
/*
short:		Clear display
inputs:
outputs:
notes:
Version:	DMK, Initial code
*******************************************************************/
{
	for( uint8_t idx = 0; idx < width - 1; idx++) {
		buf[idx] = 0;
	}
}


/******************************************************************/
void displayChar(char ch, uint8_t x, uint8_t y)
/*
short:		Print character op display
inputs:
outputs:
notes:
Version:	DMK, Initial code
*******************************************************************/
{	
}

/******************************************************************/
void displayString(char *str, uint8_t x, uint8_t y)
/*
short:		Print string op display
inputs:
outputs:
notes:		Maakt gebruik van displayChar(..)
Version:	DMK, Initial code
*******************************************************************/
{
}


/******************************************************************/
void twi_init(void)
/*
short:			Init AVR TWI interface and set bitrate
inputs:
outputs:
notes:			TWI clock is set to 100 kHz
Version :    	DMK, Initial code
*******************************************************************/
{
	TWSR = 0;
	TWBR = 32;	 // TWI clock set to 100kHz, prescaler = 0
}

/******************************************************************/
void twi_start(void)
/*
short:			Generate TWI start condition
inputs:
outputs:
notes:
Version :    	DMK, Initial code
*******************************************************************/
{
	TWCR = (0x80 | 0x20 | 0x04);
	while( 0x00 == (TWCR & 0x80) );
}

/******************************************************************/
void twi_stop(void)
/*
short:			Generate TWI stop condition
inputs:
outputs:
notes:
Version :    	DMK, Initial code
*******************************************************************/
{
	TWCR = (0x80 | 0x10 | 0x04);
}

/******************************************************************/
void twi_tx(unsigned char data)
/*
short:			transmit 8 bits data
inputs:
outputs:
notes:
Version :    	DMK, Initial code
*******************************************************************/
{
	TWDR = data;
	TWCR = (0x80 | 0x04);
	while( 0 == (TWCR & 0x80) );
}

int getSize(){
	locatieList *p = locList;
	int size = 0;
	while (p != NULL){
		size++;
		p = p->next;
	}
	return size;
}

void increaceSize(){
	maxSize++;
	calculateNewScoreAppleCollected();
}


void addLocation(int x, int y){
	locatie loc;
	loc.x = x;
	loc.y = y;
	calculateNewScoreMovement();
	// add sound
	int size = getSize();
	if(size < maxSize){
		displaySetPixel(x,y);
		locatieList *p = locList;
		while(p->next != NULL){
			p = p->next;
		}
		
		locatieList *newLoc = (locatieList *)malloc(sizeof(locatieList));
		newLoc->loc = loc;
		newLoc->number = counter;
		//writeLedDisplay(counter);
		newLoc->next = NULL;
		p->next = newLoc;
		
		counter++;
		currenLocation.x = x;
		currenLocation.y = y;
	}else{
		//writeLedDisplay(2);
		displaySetPixel(x,y);
		locatieList *p = locList;
		int min = p->number;
		int c = 0;
		int position = 0;
		while(p != NULL){
			if(p->number < min){
				min = p->number;
				position = c;
			}
			c++;
			p = p->next;
		}
		
		
		//writeLedDisplay(position);
		p = locList;
		c = 0;
		locatieList *newLoc = (locatieList *)malloc(sizeof(locatieList));
		locatieList *pervLoc = NULL; 
		while(p != NULL){
			if(c == position){
				displayClrPixel(p->loc.x,p->loc.y);
			//	writeLedDisplay(p->number);
				newLoc->loc = loc;
				newLoc->number = counter;
				newLoc->next = p->next;
				counter++;
				free(p);
				if(position == 0){
					locList = newLoc;	
				}else{
					pervLoc->next = newLoc;
				}
				currenLocation.x = x;
				currenLocation.y = y;
				break;
			}
			pervLoc = p;
			p = p->next;
			c++;
		}
	}
}
		
					
			
			
			//
			//if(p->number == max){
				//displayClrPixel(p->loc.x,p->loc.y);
				//locatie loc;
				//loc.x = x;
				//loc.y = y;
				//p->loc = loc;
				//p->number = counter;
				//counter++;
				//if(counter2 == 0){
					//p->next = locList->next;
					//locList = p;
				//}
				//startLocation.x = x;
				//startLocation.y = y;
				//break;
			//}
			//counter2++;
			//p = p->next;
		//}
		//
	//}
	


void moveUp(){
	
	int x = currenLocation.x;
	int y = currenLocation.y;
	
	x--;
	addLocation(x,y);
	update();
	
}
void moveDown(){
	int x = currenLocation.x;
	int y = currenLocation.y;
	
	x++;
	addLocation(x,y);
	update();
}

void moveLeft(){
	int x = currenLocation.x;
	int y = currenLocation.y;

	y++;
	addLocation(x,y);
	update();
}

void moveRight(){
	int x = currenLocation.x;
	int y = currenLocation.y;
	
	y--;
	addLocation(x,y);
	update();
	
}