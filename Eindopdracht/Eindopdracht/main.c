/*
 * Eindopdracht.c
 *
 * Created: 26-3-2019 15:05:34
 * Author : mauri
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "display.h"
#include "wait.h"
#include "fourSegmentDisplay.h"
#include "buttons.h"
#define F_CPU 8000000

int tick = 0;
enum gameStatus{COUNTING, PLAYING, GAMEOVER};

enum gameStatus gStatus = COUNTING;
enum eStatus status = GOING_UP;
int check = 1;


ISR( TIMER2_COMP_vect )
{
	switch(gStatus){
	case PLAYING :{
	
	if(check){
	enum eStatus newStatus = checkDirection();
	if(status != newStatus){
		check = 0;
			status = newStatus;//checkDirection();

		}
	}
	//status = checkDirection();
	if (tick == 200)
	{
		tick = 0;
		switch (status)
		{
		case GOING_UP:
			if(!moveUp()){
				gStatus = GAMEOVER;
			}
			break;
		case GOING_DOWN:
			if(!moveDown()){
				gStatus = GAMEOVER;
			}
			break;
		case GOING_LEFT:
			if(!moveLeft()){
				gStatus = GAMEOVER;
			}
			break;
		case GOING_RIGHT:
			if(!moveRight()){
				gStatus = GAMEOVER;
			}
			break;
		case WAITING:
			break;
		}
		check = 1;
	}
	break;
	}
	case COUNTING :{
		if(tick == 700){
			drawCounting(3);
			update();
		}else
		if(tick == 1400){
			drawCounting(2);
			update();
		}else
		if(tick == 2100){
			drawCounting(1);
			update();
		}else
		if (tick == 2800)
		{
			displayClr();
			displayDrawStart();
			addCandy();
			update();
			gStatus = PLAYING;
			check = 0;
			tick = 0;
		}
		
		break;
	}
	case GAMEOVER :
	{
		if(1 == tick){
			drawImage();
			update();
		}else
		if(tick > 4000){
				gStatus = COUNTING;
				displayReset();
				resetScore();
				displayClr();
				update();
				setStartLocation(4,4);
				tick = 0;
		}
		break;
	}
	}
	tick++;
}

void startGame()
{
	while (WAITING == checkDirection())
	{
	}
		

}


int main(void)
{
	//initializatie voor het scoreBord
	DDRB=0x01;					// Set PB0 pin as output for display select
	spi_masterInit();			// Initialize spi module
	displayDriverInit();		// Initialize display chip
	status = WAITING;
	displayInit();
	wait(500);
	DDRA = 0x0F;

	//addCandy();
	setStartLocation(4,4);
	
	//
		//EICRA |= 0x30;			// INT2 rising edge
		//EIMSK |= 0x04;			// Enable INT2
	//
	
	    OCR2 = 519;
	    TCCR2 = 1<<WGM21;
	    
	    TIMSK = TIMSK | 1<<TOIE1 | 1<<OCIE2;
	    TCCR2 |= 1<<CS22 | 0<<CS21 | 1<<CS20;
	    TCNT2 = 0;
	sei();

	//startGame();
	
	
	
	while (1)
	{
	}
}

