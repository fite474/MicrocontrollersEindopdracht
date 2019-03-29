/*
 * display.c
 *
 * Created: 1/16/2018 8:16:59 AM
 *  Author: Diederich Kroeske
 */ 

//defines
							// I2C address of display
#define D0_I2C_ADDR	((0x70 + 2) << 1)
							// Display buffer in ATMEGA memory
#define	width	8 * 1		// 1 displays width
#define	height	8			// 1 display height

//includes
#include <avr/io.h>
#include "headers/FourSegmentDisplay.h"
#include "headers/display.h"
#include "headers/fonts.h"

//variables
uint8_t buf[width*height/8];
time_t t;

int maxSnakeSize = 4;
int counter = 0;

//structs
typedef struct{
	int x;
	int y;
	}Location;

typedef struct{
	Location location;
	int number;
	void* next;	
	}LocationList;

LocationList *locationList;
Location candy;
Location currentLocation;



void displayInit(void) 
{
	twi_init();							// Enable TWI interface
	displayInitHT16K33(D0_I2C_ADDR);	// Iit display
	locationList = NULL;
	
	srand((unsigned)time(&t));
	rand(),rand(),rand();
}


void startLoaction(void)
{
	//method is never used
	//Location location;
}


void drawImage(void)
{
	
	buf[0]= 0b00000000;
	buf[1]= 0b01100110;
	buf[2]= 0b01100110;
	buf[3]= 0b00000000;
	buf[4]= 0b00111100;
	buf[5]= 0b01100110;
	buf[6]= 0b11000011;
	buf[7]= 0b00000000;
}


void drawCounting(int number)
{
	switch(number)
	{
		case 3 :
		{
		buf[0]= 0b01111110;
		buf[1]= 0b01111110;
		buf[2]= 0b00000110;
		buf[3]= 0b01111110;
		buf[4]= 0b01111110;
		buf[5]= 0b00000110;
		buf[6]= 0b01111110;
		buf[7]= 0b01111110;
		break;
		}
		case 2 :
		{
			buf[0]= 0b01111110;
			buf[1]= 0b01111110;
			buf[2]= 0b00000110;
			buf[3]= 0b01111110;
			buf[4]= 0b01111110;
			buf[5]= 0b01100000;
			buf[6]= 0b01111110;
			buf[7]= 0b01111110;
			break;
		}
		case 1 :
		{
			buf[0]= 0b00011000;
			buf[1]= 0b00111000;
			buf[2]= 0b01111000;
			buf[3]= 0b00011000;
			buf[4]= 0b00011000;
			buf[5]= 0b00011000;
			buf[6]= 0b01111110;
			buf[7]= 0b01111110;
			break;
		}
	}
}


void displayInitHT16K33(uint8_t i2c_address) 
{
							// System setup page 30 ht16k33 datasheet
	twi_start();
	twi_tx(i2c_address);	// Display I2C addres + R/W bit
	twi_tx(0x21);			// Internal osc on (page 10 HT16K33)
	twi_stop();
		
							// ROW/INT set. Page 31 ht16k33 datasheet
	twi_start();
	twi_tx(i2c_address);	// Display I2C address + R/W bit
	twi_tx(0xA0);			// HT16K33 pins all output (default)
	twi_stop();

							// Dimming set
	twi_start();
	twi_tx(i2c_address);	// Display I2C address + R/W bit
	twi_tx(0xE1);			// Display Dimming 2/16 duty cycle
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

void displaySetPixel(uint8_t x, uint8_t y)
{
									//int binary[8]={1,2,4,8,16,32,64,128};
		uint8_t newByte = 1 << y;
									//newByte = newByte << y;
		buf[x] = buf[x] | newByte;
									//buf[x] = binary[y];
}

void setStartLocation(int x,int y)
{
	currentLocation.x = x;
	currentLocation.y = y;
	
	locationList = (LocationList *)malloc(sizeof(LocationList));
	locationList->location = currentLocation;
	locationList->number = counter;
	locationList->next = NULL;
	counter++;
}


void displayDrawStart()
{
	displaySetPixel(locationList->location.x,locationList->location.y);
	update();
}

void displayClrPixel(uint8_t x, uint8_t y)
{
	uint8_t newByte = 1 << y;
								//newByte = newByte << y;
								//writeLedDisplay(x+y * 100);
	buf[x] = buf[x] ^ newByte;
}

void update( void )
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


void displayClr(void)
{
	for( uint8_t idx = 0; idx < width; idx++) {
		buf[idx] = 0;
	}
}

void twi_init(void)
{
	TWSR = 0;
	TWBR = 32;	 // TWI clock set to 100kHz, prescaler = 0
}

void twi_start(void)
{
	TWCR = (0x80 | 0x20 | 0x04);
	while( 0x00 == (TWCR & 0x80) );
}

void twi_stop(void)
{
	TWCR = (0x80 | 0x10 | 0x04);
}

void twi_tx(unsigned char data)
{
	//transmit 8 bits data
	TWDR = data;
	TWCR = (0x80 | 0x04);
	while( 0 == (TWCR & 0x80) );
}

int getLocationListSize(void)
{
	LocationList *locationlist = locationList;
	int locationListSize = 0;
	while (locationlist != NULL){
		locationListSize++;
		locationlist = locationlist->next;
	}
	return locationListSize;
}

void increaseSnakeSize(void)
{
	maxSnakeSize++;
	//calculateNewScoreAppleCollected();
}

void addCandy(void)
{
	
	//int random = (rand() % 8);

	
	rand(),rand(),rand(),rand(),rand(),rand();
	
	int x = (rand() % 8);
	int y = (rand() % 8);
	LocationList *locationlist = locationList;
	while(locationlist != NULL){
		if(locationlist->location.x == x && locationlist->location.y == y){
			rand(),rand();
			x = (rand() % 8);
			y = (rand() % 8);
			locationlist = locationList;
		}
		locationlist = locationlist->next;
	}
	candy.x = x;
	candy.y = y;
	displaySetPixel(x,y);
	update();
}

int checkForCollision(int x, int y)
{
	LocationList *locationlist = locationList;
	while(locationlist != NULL){
		if(locationlist->location.x == x && locationlist->location.y == y){
			return 1;
		}
		locationlist = locationlist->next;
	}
	return 0;
}

void resetDisplay(void)
{
	LocationList *locationlist = locationList;
	while(locationList == NULL){
		while(locationlist->next != NULL){
		locationlist = locationlist->next;
		}
		free(locationlist);
		locationlist = NULL;
		locationlist = locationList;
	}
	maxSnakeSize = 4;
}


int moveToNewLocation(int x, int y)
{
	
	if(x == candy.x && y == candy.y){
		increaseSnakeSize();
		addCandy();
		calculateNewScoreAppleCollected();
	}
	if(!checkForCollision(x,y)){
	Location location;
	location.x = x;
	location.y = y;
	calculateNewScoreMovement();
	// add sound
	int size = getLocationListSize();
	if(size < maxSnakeSize){
		displaySetPixel(x,y);
		LocationList *locactionlist = locationList;
		while(locactionlist->next != NULL){
			locactionlist = locactionlist->next;
		}
		
		LocationList *newLocation = (LocationList *)malloc(sizeof(LocationList));
		newLocation->location = location;
		newLocation->number = counter;
		//writeLedDisplay(counter);
		newLocation->next = NULL;
		locactionlist->next = newLocation;
		
		counter++;
		currentLocation.x = x;
		currentLocation.y = y;
	}else{
		//writeLedDisplay(2);
		displaySetPixel(x,y);
		LocationList *locationlist = locationList;
		int minimal = locationlist->number;
		int locationCounter = 0;
		int position = 0;
		while(locationlist != NULL){
			if(locationlist->number < minimal){
				minimal = locationlist->number;
				position = locationCounter;
			}
			locationCounter++;
			locationlist = locationlist->next;
		}
		
		locationlist = locationList;
		locationCounter = 0;
		LocationList *newLocation = (LocationList *)malloc(sizeof(LocationList));
		LocationList *previousLocation = NULL; 
		while(locationlist != NULL){
			if(locationCounter == position){
				displayClrPixel(locationlist->location.x,locationlist->location.y);
			//	writeLedDisplay(p->number);
				newLocation->location = location;
				newLocation->number = counter;
				newLocation->next = locationlist->next;
				counter++;
				free(locationlist);
				if(position == 0){
					locationList = newLocation;	
				}else{
					previousLocation->next = newLocation;
				}
				currentLocation.x = x;
				currentLocation.y = y;
				break;
			}
			previousLocation = locationlist;
			locationlist = locationlist->next;
			locationCounter++;
			
		}
		return 1;
		}
	}else
	{
		displayClr();
		return 0;
	}
	return 1;
}
		
int moveSnakeUp(){
	
	int x = currentLocation.x;
	int y = currentLocation.y;
	
	x--;
	if(x == -1){
		x = 7;
	}
	if(moveToNewLocation(x,y)){
		update();
		return 1;
	}else{
		return 0;
	}
	
}
int moveSnakeDown(){
	int x = currentLocation.x;
	int y = currentLocation.y;
	
	x++;
	if(x == 8){
		x = 0;
	}
	if(moveToNewLocation(x,y)){
		update();
		return 1;
	}else{
		return 0;
	}
}

int moveSnakeLeft(){
	int x = currentLocation.x;
	int y = currentLocation.y;

	y++;
	if(y == 8){
		y = 0;
	}
	if(moveToNewLocation(x,y)){
		update();
		return 1;
		}else{
		return 0;
	}
}

int moveSnakeRight(){
	int x = currentLocation.x;
	int y = currentLocation.y;
	
	y--;
	if(y == -1){
		y = 7;
	}
	if(moveToNewLocation(x,y)){
		update();
		return 1;
		}else{
		return 0;
	}
}