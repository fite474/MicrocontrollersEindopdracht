
/*
 * game.c
 *
 * Created: 29-3-2019 13:19:08
 *  Author: Bram
 */ 
//defines
#define F_CPU 8000000

//includes
#include <avr/io.h>
#include <avr/interrupt.h>
#include "headers/display.h"
#include "headers/wait.h"
#include "headers/fourSegmentDisplay.h"
#include "headers/buttons.h"
#include "headers/sound.h"
#include "headers/game.h"

enum gameStatus{COUNTING, PLAYING, GAMEOVER};
enum gameStatus gStatus = COUNTING;
enum eStatus status = GOING_UP;

int tick = 0;
int check = 1;


void gameOver(){
	
	if(1 == tick)
	{
		drawImage();
		update();
		beepGameOver();
	}else
	if(tick > 4000)
	{
		gStatus = COUNTING;
		resetDisplay();
		resetScore();
		displayClr();
		update();
		setStartLocation(4,4);
		tick = 0;
	}
	
}

void playing(){
	if(check)
	{
		enum eStatus newStatus = checkDirection();
		if(status != newStatus)
		{
			check = 0;
			status = newStatus;
		}
	}
	if (tick == 200)
	{
		tick = 0;
		switch (status)
		{
			case GOING_UP:
			if(!moveSnakeUp())
			{
				gStatus = GAMEOVER;
			}
			break;
			
			
			case GOING_DOWN :
			if(!moveSnakeDown())
			{
				gStatus = GAMEOVER;
			}
			break;
			
			
			case GOING_LEFT:
			if(!moveSnakeLeft())
			{
				gStatus = GAMEOVER;
			}
			break;
			
			
			case GOING_RIGHT:
			if(!moveSnakeRight())
			{
				gStatus = GAMEOVER;
			}
			break;
			
			
			case WAITING:
			break;
		}
		check = 1;
	}
}

void counting(){
	if(tick == 700)
	{
		beepOn();
		drawCounting(3);
		update();
		beepOff();
	}else
	if(tick == 1400)
	{
		beepOn();
		drawCounting(2);
		update();
		beepOff();
	}else
	if(tick == 2100)
	{
		beepOn();
		drawCounting(1);
		update();
		beepOff();
	}else
	if (tick == 2800)
	{
		beepOn();
		displayClr();
		displayDrawStart();
		addCandy();
		update();
		beepOff();
		gStatus = PLAYING;
		check = 0;
		tick = 0;
	}
}


void startGame()
{
	switch(gStatus)
	{
		case PLAYING :
		{
			playing();
			break;
		}
		
		
		case COUNTING :
		{
			counting();
			break;
		}
		
		
		case GAMEOVER :
		{
			gameOver();
			break;
		}
	}
	tick++;
}

