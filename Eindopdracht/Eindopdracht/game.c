
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
#include "headers/screen.h"

enum gameStatus{COUNTING, PLAYING, GAMEOVER, MENU};
enum gameStatus gStatus = MENU;
enum eStatus status = GOING_UP;

int gameSpeed = 0;
int tick = 0;
int check = 1;

void menu(){
	int inMenu = 1;
	int position = 0;
	lcd_write_command(12);
	while(inMenu){
		lcd_write_command(2);
		lcd_write_command(1);
	
		if(position == 0){
			lcd_write_string("> Easy");
			lcd_write_command(168);
			lcd_write_string(" ");
			lcd_write_command(168);
			lcd_write_string("  Normal");
		}else
		if(position == 1){
			lcd_write_string("> Normal");
			lcd_write_command(168);
			lcd_write_string(" ");
			lcd_write_command(168);
			lcd_write_string("  Hard");
		}else
		if(position == 2){
			lcd_write_string("  Normal");
			lcd_write_command(168);
			lcd_write_string(" ");
			lcd_write_command(168);
			lcd_write_string("> Hard");
		}
		wait(500);
		enum eStatus move = WAITING;
		while(move == WAITING){
			move = menuDirection();		
		}
		wait(500);
	
		

		switch(move){
			case GOING_UP :{
				if(position != 0){
					position--;
				}
				break;
			}
			case GOING_RIGHT :{
				inMenu = 0;
				gStatus = COUNTING;
				if(position == 0)
					gameSpeed = 1000;
				else if(position == 1)
					gameSpeed = 500;
				else if(position == 2)
					gameSpeed = 200;
				tick = 0;
				break;
			}
			case GOING_LEFT :{
				break;
			}
			case GOING_DOWN :{
				if (position != 2)
				{
					position++;
				}
			}
			case WAITING :{
				break;
			}
		}
	}
	//wait(1000);
}

void gameOver(){
	
	if(1 == tick)
	{
		drawImage();
		update();
		beepGameOver();
	}else
	if(tick > 3000)
	{
		gStatus = MENU;
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
	if (tick == gameSpeed)
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
		case MENU :
		{
			menu();
			break;
		}
	}
	tick++;
}

