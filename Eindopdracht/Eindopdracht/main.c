/*
 * Eindopdracht.c
 *
 * Created: 26-3-2019 15:05:34
 * Author : mauri
 */ 

#include <avr/io.h>
#include "display.h"
#include "wait.h"
#include "fourSegmentDisplay.h"


int main(void)
{
	//initializatie voor het scoreBord
	DDRB=0x01;					// Set PB0 pin as output for display select
	spi_masterInit();			// Initialize spi module
	displayDriverInit();		// Initialize display chip
	
	displayInit();
	wait(500);
	DDRA = 0x0F;

	//addCandy();
	setStartLocation(4,4);
	wait(1000);
	//int up=0;
	//int down=0;
	//int left=0;
	//int right=0;
	//
	//while (1)
	//{
	//if (PINA & 0x81 || up)
	//{
	//moveUp();
	//int up=1;
	//int down=0;
	//int left=0;
	//int right=0;
	//}
	//else if (PINA & 0x82 || down)
	//{
	//moveDown();
	//int up=0;
	//int down=1;
	//int left=0;
	//int right=0;
	//}
	//else if (PINA & 0x84 || left)
	//{
	//moveLeft();
	//int up=0;
	//int down=0;
	//int left=1;
	//int right=0;
	//}
	//else if (PINA & 0x88 || right)
	//{
	//moveRight();
	//int up=0;
	//int down=0;
	//int left=0;
	//int right=1;
	//}
	//wait(1000);
	//}
	addCandy();
	increaceSize();
	increaceSize();
	increaceSize();
	increaceSize();
	increaceSize();
	increaceSize();
	while(1){
		moveDown();
		wait(1000);
	}
	moveDown();
	wait(1000);
	moveDown();
	wait(1000);
	moveDown();
	wait(1000);
	moveLeft();
	wait(1000);
	moveLeft();
	wait(1000);
	moveUp();
	wait(1000);
	moveUp();
	wait(1000);
	moveUp();
	wait(1000);
	moveUp();
	wait(1000);
	moveUp();
	wait(1000);
	moveUp();
	wait(1000);
	moveRight();
	wait(1000);
	moveRight();
	wait(1000);
	moveRight();
	wait(1000);
	
	
	
	//displayChar('1', 0, 0);
	//displayClr();
	//display();
	//displaySetPixel(1,1);
	//displayString("LUL",0,0);
	//drawImage();
	//update();
	
	
	//int x = 0;
	//int pos = 1;
	//int y = 0;
	//while(1==1) {
		//displaySetPixel(3,3);
		//if(pos)
		//displaySetPixel(x++,y);
		//else
		//displaySetPixel(x--,y);
		//display();
		//if(x == 8 && pos){
		//pos = 0;
		//y++;
		//}
		//if(x == 0 && !pos){
		//pos = 1;
		//y++;
		//}
		//if(y == 8 ){
		//y = 0;
		//}
		//wait(100);
	//}

    while (1) 
    {
		
    }
}

