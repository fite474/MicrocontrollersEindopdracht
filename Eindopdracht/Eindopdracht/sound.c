
/*
 * sound.c
 *
 * Created: 29-3-2019 09:38:47
 *  Author: mauri
 */ 
#include <avr/io.h>
#include "headers/wait.h"

static int x = 2000;
#define F_CPU x  // change this value to change the sound produced by the beep



void testsound1(void)
{
	PORTC = 0xff;        // Turn ON the Buzzer conneted to PORTC
	wait(3000);
	PORTC = 0x00;
	wait(500);  
	x = 5000;      // Turn OFF the Buzzer connected to PORTC
	PORTC = 0xff;        // Turn ON the Buzzer conneted to PORTC
	wait(3000);
	PORTC = 0x00;        // T
	
	
}
void testsound2(void)
{
	
}
void testsound3(void)
{
	
}

void beepOn(void)
{
	 PORTC = 0xff;        // Turn ON the Buzzer conneted to PORTC
}

void beepOff(void)
{
	  PORTC = 0x00;        // Turn OFF the Buzzer connected to PORTC

}

void beepGameOver()
{

		PORTC = 0xff;        // Turn ON the Buzzer conneted to PORTC
		wait(300);
	    PORTC = 0x00;
	    wait(500);        // Turn OFF the Buzzer connected to PORTC
	  	PORTC = 0xff;        // Turn ON the Buzzer conneted to PORTC
	  	wait(500);
	    PORTC = 0x00;        // Turn OFF the Buzzer connected to PORTC
		wait(500);
		PORTC = 0xff;        // Turn ON the Buzzer conneted to PORTC
	    wait(2000);
		PORTC = 0x00;        // Turn OFF the Buzzer connected to PORTC
	  

}