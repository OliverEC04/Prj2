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


int main(void)
{
	//Initiating interrupt
	setUpInterruptZeroCross();
	
	//Global interrupt enable
	sei();
	
	//Initiating interrupt
	initLEDport();
	
	// Init switches
	DDRA = 0;
	
	// Temp bytes
	//char addressByte = 0b00000111;
	//char dataByte = 0b10100101;
	char addressByte = 0b00000000;
	char dataByte = 0b00000000;
	
	//Receiver 1 og 2
	X10Reciever_1 modtager1(0);
	X10Reciever_2 modtager2(0);
	
	char decoded;
	
	//Main-loop: Toggle LED7 every second
    while (1) 
    {
		_delay_ms(1000);
		
		if(PINA == 0b10000000)
		{
			for(int i = 0; i < 12; i++)
			{
				if(PINA == 0b10000000)
				{
					if(addressByte < 8)
					{
						addressByte = addressByte << 1;
						addressByte |= 0b00000001;
					}
					
					dataByte = dataByte << 1;
					dataByte |= 0b00000001;
				} 
				else
				{
					dataByte = dataByte << 1;
				}
				
				if (intTrigger)
				{
					// IntTrigger aktiv her
					
					intTrigger = false;
				}
				
				toggleLED(7);
				
				decoded = manchesterDecoder2(addressByte, dataByte);
				
				_delay_us(5000);
			}
		}
		
		modtager1.recieveCommand1(decoded);
		modtager2.recieveCommand2(decoded);
    }
}

//Interrupt service rutine for INT5
ISR (INT5_vect)
{
	intTrigger = true;	
}