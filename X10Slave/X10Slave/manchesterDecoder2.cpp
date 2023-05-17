/*
 * manchesterDecoder2.cpp
 *
 * Created: 17-05-2023 11:01:58
 *  Author: olive
 */ 

#define F_CPU 16000000

#include <util/delay.h>

#include "Led.h"

// HUSK AT LÆS FRA HØJRE !!!!!!!!!!!!!!

char manchesterDecoder2(char addressByte, char dataByte)
{
	char decodedByte = addressByte;
	
	if (addressByte == 0b00000111)
	{
		for (char i = 0; i < 4; i++)
		{
			char checkByte = dataByte << (i * 2); // Shift 2 left, since we only check the two left bits
			checkByte &= 0b11000000; // Set all other bits than the two left to 0
			
			if (checkByte == 0b10000000) // if 10 (0)
			{
				// Shift 1 left, and add 0 on right
				decodedByte = decodedByte << 1;
			}
			else if (checkByte == 0b01000000) // if 01 (1)
			{
				// Shift 1 left, and add 1 on right
				decodedByte = decodedByte << 1;
				decodedByte |= 0b00000001;
			}
			else
			{
				// Invalid number
			}
		}
	}
	else
	{
		// Wrong address
	}
	
	return decodedByte;
}

int manchesterDecoder2Test(void)
{
	initLEDport();
	
	char myDecode;
	
	myDecode = manchesterDecoder2(0b00000111, 0b10100101);
	
	writeAllLEDs(myDecode);
	
	_delay_ms(5000);
	
	return 0;
}

int main(void)
{
	manchesterDecoder2Test();
	
	return 0;
}