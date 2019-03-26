
/*
 * buttons.c
 *
 * Created: 26-3-2019 17:19:58
 *  Author: mauri
 */ 

#include <avr/io.h>
#include "buttons.h"


int direction = 0;



int checkDirection()
{
	//DDRB=0x01; // Set PB0 pin as output for display select
	//spi_masterInit(); // Initialize spi module
	//displayDriverInit(); // Initialize display chip
	
	DDRA = 0x0F;
	
	

	if (PINA & 0x81 && direction != GOING_DOWN)
	{
		direction = GOING_UP;
	}
	if (PINA & 0x82 && direction != GOING_UP)
	{
		direction = GOING_DOWN;
	}
	if (PINA & 0x84 && direction != GOING_RIGHT)
	{
		direction = GOING_LEFT;
	}
	if (PINA & 0x88 && direction != GOING_LEFT)
	{
		direction = GOING_RIGHT;
	}
	
	return direction;
	
}
