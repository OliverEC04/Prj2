/*
 * manchesterDecoder2.cpp
 *
 * Created: 17-05-2023 11:01:58
 *  Author: olive
 */ 

#define F_CPU 16000000

#include <util/delay.h>

#include "Led.h"

// 10100101

// HUSK AT LÆS FRA HØJRE !!!!!!!!!!!!!!

char manchesterDecoder2(char addressByte, char dataByte)
{
	char decoded = addressByte << 4;
	
	if (addressByte == 0b00000111)
	{
		for (char i = 0; i < 4; i++)
		{
			if ((dataByte |= 0b00000010) && (dataByte &= 0b11111110)) // if 10
			{
				decoded &= 0b11111110 << i; // add 0 to end
			}
			else if ((dataByte &= 0b11111101) && (dataByte |= 0b00000001)) // if 01
			{
				decoded |= 0b00000001 << i; // add 1 to end
			}
			
			dataByte >> 2; // Move 2 right
			
			writeAllLEDs(dataByte);
			_delay_ms(2000);
		}
	}
	
	return decoded;
}

int main(void)
{
	initLEDport();
	
	char myDecode;
	
	myDecode = manchesterDecoder2(0b00000111, 0b10100101);
	
	writeAllLEDs(myDecode);
	
	return 0;
}
