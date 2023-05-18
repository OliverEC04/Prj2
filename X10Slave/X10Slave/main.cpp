/*
 * X10Reciever.cpp
 *
 * Created: 26-04-2023 12:29:10
 * Author : ZakiN
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "led.h"
#include "SlaveSetup.h"
#include "X10Reciever_1.h"
#include "X10Reciever_2.h"


// Init intTrigger
volatile bool intTrigger = false;


char manchesterDecoder2(char encodedByte)
{
	char decodedByte = 0;

	for (char i = 0; i < 4; i++)
	{
		char checkByte = encodedByte >> (i * 2); // Shift 2 right, since we only check the two right bits
		checkByte &= 0b00000011; // Set all other bits than the two left to 0
			
		if (checkByte == 0b00000010) // if 10 (1)
		{
			// Shift 1 left, and add 1 on right
			decodedByte = decodedByte << i;
			decodedByte |= 0b00000001;
		}
		else if (checkByte == 0b00000001) // if 01 (0)
		{
			// Shift 1 left
			decodedByte = decodedByte << 1;
		}
		else
		{
			// Invalid number
		}
	}
	
	return decodedByte;
}


int main(void)
{
	//Initiating interrupt
	setUpInterruptZeroCross();
	
	//Global interrupt enable
	sei();
	
	//Initiating interrupt
	initLEDport();
	
	// Init switches
	DDRL = 0;
	
	// Temp bytes
	char readByte = 0;
	
	//Receiver 1 og 2
	X10Reciever_1 modtager1(0);
	X10Reciever_2 modtager2(0);
	
	char decoded;
	int counter = 0;
	
	//Main-loop: Toggle LED7 every second
    while (1)
    {
		if (PINL == 0b01000000)
		{
			readByte = readByte << 1;
			readByte |= 1;
		}
		else if (PINL == 0b00000000)
		{
			readByte = readByte << 1;
		}
		else
		{
			// Fejl
		}
		
		counter++;
		
		if (counter == 4) // Når startbit er læst
		{
			if (readByte == 0b00001110)
			{
				readByte = 0;
			}
			else
			{
				// Fejl
			}
		}
		else if (counter >= 12) // Når det efterfølgende byte er læst
		{
			decoded = manchesterDecoder2(readByte);
			
			if (decoded & 0b00001000 == 0b00001000) // Tjek addresse bit
			{
				modtager1.recieveCommand1(decoded);
			}
			else
			{
				modtager2.recieveCommand2(decoded);
			}
			
			counter = 0;
			readByte = 0;
		}
		
		intTrigger = false;
		while(!intTrigger)
		{}
			
		_delay_us(500);
    }
}

//Interrupt service rutine for INT5
ISR (INT5_vect)
{
	intTrigger = true;
}