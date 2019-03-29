
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

void SetFreq(unsigned char freq)
{
	DDRB |= (1 << DDB5|1 << DDB6);

	TCCR1B |= (1 << WGM13 );
	TCCR1A |= (1 << COM1A1 | 1 << COM1A0 |1 << COM1B1 | 1 << COM1B0 );
	
	OCR1B   = 75; // for 1.2 ms off
	
	//For 40 us delay
	switch(freq)
	{
		case 2:
		ICR1 = 4608;
		OCR1A	= 4580;
		break;
		case 3:
		ICR1 = 3456;
		OCR1A	= 3428;
		break;
		case 4:
		ICR1 = 2764;
		OCR1A	= 2737;
		break;
		case 5:
		ICR1 = 208;
		OCR1A	= 205;
		break;
		case 6:
		ICR1 = 1975;
		OCR1A	= 1947;
		break;
		case 7:
		ICR1 = 1728;
		OCR1A	= 1700;
		break;
		case 0:
		case 1:
		default:
		ICR1 = 625;
		OCR1A	= 622;
		break;
	}
	
	TCCR1B |= (1 << CS11);
}

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
		PORTC = 0xff;        // Turn ON the Buzzer conneted to PORTC
		wait(3000);
		PORTC = 0x00;
		wait(500);
		SetFreq(2);     // Turn OFF the Buzzer connected to PORTC
		PORTC = 0xff;        // Turn ON the Buzzer conneted to PORTC
		wait(3000);
		PORTC = 0x00;        // T
				SetFreq(3);     // Turn OFF the Buzzer connected to PORTC
				PORTC = 0xff;        // Turn ON the Buzzer conneted to PORTC
				wait(3000);
				PORTC = 0x00;        // T
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