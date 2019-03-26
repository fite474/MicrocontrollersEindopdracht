/*
 * Eindopdracht.c
 *
 * Created: 26-3-2019 15:05:34
 * Author : mauri
 */ 

#include <avr/io.h>
#include "wait.h"
#include "fourSegmentDisplay.h"


int main(void)
{
	//initializatie voor het scoreBord
	DDRB=0x01;					// Set PB0 pin as output for display select
	spi_masterInit();			// Initialize spi module
	displayDriverInit();		// Initialize display chip
	
	
    while (1) 
    {
		
    }
}

