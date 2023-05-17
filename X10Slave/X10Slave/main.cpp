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

#include "led.h"
#include "ManchesterDecoder.h"
#include "SlaveSetup.h"
#include "X10Reciever_1.h"
#include "X10Reciever_2.h"


int main(void)
{
	//Initiating interrupt
	setUpInterruptZeroCross();
	
	//Global interrupt enable
	sei();
	
	//Initiating interrupt
	initLEDport();
	
	//Temparray
	int tempArray[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	
	//Main-loop: Toggle LED7 every second
    while (1) 
    {
		toggleLED(7);
		_delay_ms(1000);
		
		if(PINB == 0b10000000)
		{
			for(int i = 0; i < 12; i++)
			{
				if(PINB == 0b10000000)
				{
					tempArray[i] = 1;
				} 
				else
				{
					tempArray[i] = 0;
				}
				
				intTrigger = false;
				
				while(intTrigger == false)
				{
					
				}
				
				manchester_decoder(tempArray, 12, 4);
				
				_delay_us(500);
			}
		}
    }
}

//Interrupt service rutine for INT5
ISR (INT5_vect)
{
	intTrigger = true;	
}