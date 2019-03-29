/*
 * buttons.c
 *
 * Created: 26-3-2019 17:19:58
 *  Author: Maurice
 */ 

#include <avr/io.h>
#include "headers/buttons.h"

enum eStatus moving = GOING_UP;

int checkDirection()
{
	//DDRB=0x01; // Set PB0 pin as output for display select
	//spi_masterInit(); // Initialize spi module
	//displayDriverInit(); // Initialize display chip
	
	DDRA = 0x0F;

	if (PINA & 0x81 && moving != GOING_DOWN)
	{
		moving = GOING_UP;
	}
	if (PINA & 0x82 && moving != GOING_UP)
	{
		moving = GOING_DOWN;
	}
	if (PINA & 0x84 && moving != GOING_RIGHT)
	{
		moving = GOING_LEFT;
	}
	if (PINA & 0x88 && moving != GOING_LEFT)
	{
		moving = GOING_RIGHT;
	}
	
	return moving;
	
}

int menuDirection()
{
	//DDRB=0x01; // Set PB0 pin as output for display select
	//spi_masterInit(); // Initialize spi module
	//displayDriverInit(); // Initialize display chip
	
	DDRA = 0x0F;

	if (PINA & 0x81)
	{
		moving = GOING_UP;
	}
	if (PINA & 0x82)
	{
		moving = GOING_DOWN;
	}
	if (PINA & 0x84)
	{
		moving = GOING_LEFT;
	}
	if (PINA & 0x88)
	{
		moving = GOING_RIGHT;
	}
	
	return moving;
	
}
