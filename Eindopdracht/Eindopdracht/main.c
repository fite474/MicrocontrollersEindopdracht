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
#include "headers/game.h"
#include "headers/screen.h"

ISR( TIMER2_COMP_vect )
{
	startGame();
}


int main(void)
{
								//initializatie voor het scoreBord
	DDRB=0x01;					// Set PB0 pin as output for display select
	spi_masterInit();			// Initialize spi module
	displayDriverInit();		// Initialize display chip
	displayInit();
	wait(500);
	DDRA = 0x0F;
	init_4bits_mode();
	resetScore();
	//DDRC = 0xff;
	
	// DDRE = 0xff;     
	setStartLocation(4,4);


	    OCR2 = 519;
	    TCCR2 = 1<<WGM21;
	    
	    TIMSK = TIMSK | 1<<TOIE1 | 1<<OCIE2;
	    TCCR2 |= 1<<CS22 | 0<<CS21 | 1<<CS20;
	    TCNT2 = 0;
	sei();
	
	while (1)
	{}		
		
	return 0;
}
