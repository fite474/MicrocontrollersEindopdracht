/*
 * fourSegmentDisplay.h
 *
 * Created: 26/03/2019 12:12:06
 *  Author: Timo
 */ 


#ifndef FOURSEGMENTDISPLAY_H_
#define FOURSEGMENTDISPLAY_H_

void spi_masterInit(void);
void spi_write( unsigned char data);
void spi_slaveSelect(unsigned char chipNumber);
void spi_slaveDeSelect(unsigned char chipNumber);
void displayDriverInit(void);
void displayOn(void);
void displayOff(void);
void spi_writeWord(unsigned char adress, unsigned char data);
void writeToLedDisplay(int value);
void clearDisplay(void);
void calculateNewScoreAppleCollected(void);
void calculateNewScoreMovement(void);

#endif /* FOURSEGMENTDISPLAY_H_ */