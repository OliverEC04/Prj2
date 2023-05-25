/*
 * lamp.cpp
 *
 * Created: 24-05-2023 10:39:32
 *  Author: anton
 */ 
#include "lamp.h"
#include <math.h>

void initLamp()
{
	//Initierer lamp til Port E, ben 3 (PE3)
	DDRE |= 0b00001000;
	//No prescaling 
	TCCR3B |= 0b00000001;
	//Clear on compare match
	TCCR3A |= 0b10000011;

}

void fadeLampOn(double period)
{
	for (double i = 0; i < 1024*period; i++)
	{
		OCR3A = floor(i/period);
	}
}

void lampOff()
{
	OCR3A = 0;
}