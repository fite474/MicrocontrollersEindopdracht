
/*
 * buttons.c
 *
 * Created: 26-3-2019 17:19:58
 *  Author: mauri
 */ 

#include <avr/io.h>
#include "buttons.h"


enum eStatus status;

int checkDirection()
{
	//DDRB=0x01; // Set PB0 pin as output for display select
	//spi_masterInit(); // Initialize spi module
	//displayDriverInit(); // Initialize display chip
	
	DDRA = 0x0F;
	
	

	if (PINA & 0x81 && status != GOING_DOWN)
	{
		status = GOING_UP;
	}
	if (PINA & 0x82 && status != GOING_UP)
	{
		status = GOING_DOWN;
	}
	if (PINA & 0x84 && status != GOING_RIGHT)
	{
		status = GOING_LEFT;
	}
	if (PINA & 0x88 && status != GOING_LEFT)
	{
		status = GOING_RIGHT;
	}
	
	return status;
	
}
