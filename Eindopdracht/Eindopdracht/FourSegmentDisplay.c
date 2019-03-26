/*
 * fourSegmentDisplay.c
 *
 * Created: 26/03/2019 12:11:58
 *  Author: Timo
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "fourSegmentDisplay.h"
//#define F_CPU 8000000


#define BIT(x) ( 1<<x )
#define DDR_SPI DDRB	// spi Data direction register
#define PORT_SPI PORTB	// spi Output register
#define SPI_SCK 1		// PB1: spi Pin System Clock
#define SPI_MOSI 2		// PB2: spi Pin MOSI
#define SPI_MISO 3		// PB3: spi Pin MISO
#define SPI_SS 0		// PB0: spi Pin Slave Select

int score = 0;

void spi_masterInit(void)
{
	DDR_SPI = 0xff;							// All pins output: MOSI, SCK, SS, SS_display
	DDR_SPI &= ~BIT(SPI_MISO);				// except: MISO input
	PORT_SPI |= BIT(SPI_SS);				// SS_ADC == 1: deselect slave
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1);	// or: SPCR = 0b11010010;
											// Enable spi, MasterMode, Clock rate fck/64
											// bitrate=125kHz, Mode = 0: CPOL=0, CPPH=0
}

// Write a byte from master to slave
void spi_write( unsigned char data)
{
	SPDR = data;					// Load byte --> starts transmission
	while( !(SPSR & BIT(SPIF)) );	// Wait for transmission complete
}


// Select device on pinnumer PORTB
void spi_slaveSelect(unsigned char chipNumber)
{
	PORTB &= ~BIT(chipNumber);
}

// Deselect device on pinnumer PORTB
void spi_slaveDeSelect(unsigned char chipNumber)
{
	PORTB |= BIT(chipNumber);
}

// Initialize the driver chip (type MAX 7219)
void displayDriverInit()
{
	spi_slaveSelect(0);		// Select display chip (MAX7219)
	spi_write(0x09);		// Register 09: Decode Mode
	spi_write(0xFF);		// -> 1's = BCD mode for all digits
	spi_slaveDeSelect(0);	// Deselect display chip
	spi_slaveSelect(0);		// Select dispaly chip
	spi_write(0x0A);		// Register 0A: Intensity
	spi_write(0x0F);		// -> Level 4 (in range [1..F])
	spi_slaveDeSelect(0);	// Deselect display chip
	spi_slaveSelect(0);		// Select display chip
	spi_write(0x0B);		// Register 0B: Scan-limit
	spi_write(0x03);		// -> 1 = Display digits 0..1
	spi_slaveDeSelect(0);	// Deselect display chip
	spi_slaveSelect(0);		// Select display chip
	spi_write(0x0C);		// Register 0B: Shutdown register
	spi_write(0x01);		// -> 1 = Normal operation
	spi_slaveDeSelect(0);	// Deselect display chip
}

// Set display on
void displayOn(void)
{
	spi_slaveSelect(0);		// Select display chip
	spi_write(0x0C);		// Register 0B: Shutdown register
	spi_write(0x01);		// -> 1 = Normal operation
	spi_slaveDeSelect(0);	// Deselect display chip
}

// Set display off
void displayOff(void)
{
	spi_slaveSelect(0);		// Select display chip
	spi_write(0x0C);		// Register 0B: Shutdown register
	spi_write(0x00);		// -> 1 = Normal operation
	spi_slaveDeSelect(0);	// Deselect display chip
}

void spi_writeWord(unsigned char adress, unsigned char data )
{
	spi_slaveSelect(0);		// Select display chip
	spi_write(adress);		// digit adress: (digit place)
	spi_write(data);		// digit value: 0
	spi_slaveDeSelect(0);	// Deselect display chip
}

void writeLedDisplay(int value)
{
	clearDisplay();
	if(value > 9999){
		value = 9999;
	}
	if(value < 0)
	{
		if(value < -999)
		{
			value = -999;
		}

		int tempValue = abs(value);
		int num3 = (tempValue / 1) % 10;
		int num2 = (tempValue / 10) % 10;
		int num1 = (tempValue / 100) % 10;

		spi_writeWord(4, 10);
		spi_writeWord(3, num1);
		spi_writeWord(2, num2);
		spi_writeWord(1, num3);

	}else
	{
		int num4 = (value / 1) % 10;
		int num3 = (value / 10) % 10;
		int num2 = (value / 100) % 10;
		int num1 = (value / 1000) % 10;

		spi_writeWord(4, num1);
		spi_writeWord(3, num2);
		spi_writeWord(2, num3);
		spi_writeWord(1, num4);
	}
}

void clearDisplay(void)
{
	for (char i =1; i<=4; i++)
	{
		spi_writeWord(i, 0);
	}
}

void calculateNewScoreAppleCollected()
{
	score += 20;
	writeLedDisplay(score);
}

void calculateNewScoreMovement()
{
	score += 2;
	writeLedDisplay(score);
}


