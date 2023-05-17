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
//#include "ManchesterDecoder.h"
//#include "manchesterDecoder2.cpp"
//#include "SlaveSetup.h"
//#include "X10Reciever_1.h"
//#include "X10Reciever_2.h"
//
//
//int mainNEJ(void)
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
	////Temparray
	//char tempArray[12] = {1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1};
	//
	////Main-loop: Toggle LED7 every second
    //while (1) 
    //{
		//
		////_delay_ms(1000);
		//
		//if(PINA == 0b10000000 || true)
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
				//intTrigger = false;
				//
				//if(intTrigger == false)
				//{
					//
				//}
				//
				////toggleLED(7);
				//char* decoded = manchester_decoder(tempArray, 12, 4);
				//char* myStr;
				//
				//for (int i = 0; i < 4; i++)
				//{
					//char appChar = decoded[i];
					//strncat(myStr, &appChar, 1);
				//}
				//
				//writeAllLEDs(char(atoi(myStr)));
				//
				////_delay_us(5000);
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