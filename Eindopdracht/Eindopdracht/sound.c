
/*
 * sound.c
 *
 * Created: 29-3-2019 09:38:47
 *  Author: mauri
 */ 
#include <avr/io.h>
#include "headers/wait.h"

#define F_CPU 2000  // change this value to change the sound produced by the beep

void beepOn(void)
{
	 PORTE = 0xff;        // Turn ON the Buzzer conneted to PORTC
}

void beepOff(void)
{
	  PORTE = 0x00;        // Turn OFF the Buzzer connected to PORTC

}

void beepGameOver()
{
		PORTE = 0xff;        // Turn ON the Buzzer conneted to PORTC
		wait(300);
	    PORTE = 0x00;
	    wait(500);        // Turn OFF the Buzzer connected to PORTC
	  	PORTE = 0xff;        // Turn ON the Buzzer conneted to PORTC
	  	wait(500);
	    PORTE = 0x00;        // Turn OFF the Buzzer connected to PORTC
		wait(500);
		PORTE = 0xff;        // Turn ON the Buzzer conneted to PORTC
	    wait(2000);
		PORTE = 0x00;        // Turn OFF the Buzzer connected to PORTC
	  

}