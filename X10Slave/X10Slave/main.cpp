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

#include "lamp.h"
#include "lyd.h"
#include "led.h"
#include "SlaveSetup.h"
#include "X10Reciever_1.h"
#include "X10Reciever_2.h"


// Init intTrigger
volatile bool intTrigger = false;


char manchesterDecoder2(char encodedByte)
{
	char decodedByte = 0;
	char checkByte;

	for (char i = 0; i < 4; i++)
	{
		checkByte = (encodedByte << (i * 2)); // Shift 2 right, since we only check the two right bits
		checkByte &= 0b11000000; // Set all other bits than the two left to 0
			
		if (checkByte == 0b10000000) // if 10 (1)
		{
			// Shift 1 left, and add 1 on right
			decodedByte = (decodedByte << 1);
			decodedByte |= 0b00000001;
		}
		else if (checkByte == 0b01000000) // if 01 (0)
		{
			// Shift 1 left
			decodedByte = (decodedByte << 1);
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
	
	//Initiating sound
	initLyd();
	
	//Initiating lamp
	initLamp();
	
	// Init switches
	DDRL = 0;
	
	// Temp bytes
	char readByte = 0;
	bool startSeq = false;
	
	//Receiver 1 og 2
	//X10Reciever_1 modtager1(0);
	X10Reciever_2 modtager2(0);
	
	char decoded;
	int counter = 0;
	char testl = 0;
	
	
	
	//Main-loop: Toggle LED7 every second
    while (1)
    {
		if ((PINL & 0b01000000) == 0b01000000)
		{
			readByte = (readByte << 1);
			readByte |= 0b00000001;
		}
		else
		{
			readByte = (readByte << 1);
		}
		//else if ((PINL | 0b10111111) == 0b10111111)
		//{
			//readByte = (readByte << 1);
		//}
		
		if ((readByte & 0b00001110) == 0b00001110)
		{
			startSeq = true;
			readByte = 0;
			counter = -1;
		}
		
		if (startSeq && counter >= 7)
		{
			//writeAllLEDs(readByte);
			//_delay_ms(2000);
			decoded = manchesterDecoder2(readByte);
			//writeAllLEDs(decoded);
			//_delay_ms(2000);
			
			if ((decoded & 0b00001000) == 0b00001000) // Tjek addresse bit
			{
				//modtager1.recieveCommand1(decoded);
			}
			else
			{
				modtager2.recieveCommand2(decoded);
			}
			
			startSeq = false;
			counter = -1;
			readByte = 0;
		}
		
		counter++;
		
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