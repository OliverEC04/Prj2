///*
 //* X10Reciever.cpp
 //*
 //* Created: 26-04-2023 12:29:10
 //* Author : ZakiN
 //*/ 
//
//#include <avr/io.h>
//#include <avr/interrupt.h>
//#define F_CPU 16000000
//#include <util/delay.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stdio.h>
//
//#include "led.h"
//#include "manchesterDecoder2.cpp"
//#include "SlaveSetup.h"
//#include "X10Reciever_1.h"
//#include "X10Reciever_2.h"
//
//
//// Init intTrigger
//bool intTrigger = false;
//
//
//int main(void)
//{
	////Initiating interrupt
	//setUpInterruptZeroCross();
	//
	////Global interrupt enable
	//sei();
	//
	////Initiating interrupt
	//initLEDport();
	//
	//// Init switches
	//DDRA = 0;
	//
	//// Temp bytes
	//char addressByte = 0b00000111;
	//char dataByte = 0b10100101;
	//
	////Main-loop: Toggle LED7 every second
    //while (1) 
    //{
		//_delay_ms(1000);
		//
		//if(PINA == 0b10000000)
		//{
			//for(int i = 0; i < 12; i++)
			//{
				//if(PINA == 0b10000000)
				//{
					////tempArray[i] = 1;
				//} 
				//else
				//{
					////tempArray[i] = 0;
				//}
				//
				//if (intTrigger)
				//{
					//// IntTrigger aktiv her
					//
					//intTrigger = false;
				//}
				//
				//toggleLED(7);
				//
				//char decoded = manchesterDecoder2(addressByte, dataByte);
				//
				//_delay_us(5000);
			//}
		//}
    //}
//}
//
////Interrupt service rutine for INT5
//ISR (INT5_vect)
//{
	//intTrigger = true;	
//}