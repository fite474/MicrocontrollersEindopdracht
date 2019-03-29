/*
 * Eindopdracht.c
 *
 * Created: 26-3-2019 15:05:34
 * Author : Maurice
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

//variables
enum gameStatus{COUNTING, PLAYING, GAMEOVER};
enum gameStatus gStatus = COUNTING;
enum eStatus status = GOING_UP;

int tick = 0;
int check = 1;


ISR( TIMER2_COMP_vect )
{
	switch(gStatus)
	{
		case PLAYING :
		{
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
		break;
		}
		
		
		case COUNTING :
		{
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
			break;
		}
	
	
		case GAMEOVER :
		{
			if(1 == tick)
			{
				beepGameOver();
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
	
	 DDRC = 0xff;           

	setStartLocation(4,4);


	    OCR2 = 519;
	    TCCR2 = 1<<WGM21;
	    
	    TIMSK = TIMSK | 1<<TOIE1 | 1<<OCIE2;
	    TCCR2 |= 1<<CS22 | 0<<CS21 | 1<<CS20;
	    TCNT2 = 0;
	sei();
	
	while (1)
	{
		
	}
	return 0;
}

