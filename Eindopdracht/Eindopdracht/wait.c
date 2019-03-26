/*
 * wait.c
 *
 * Created: 26/03/2019 15:12:58
 *  Author: Timo
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}