/*
 * burstTest.cpp
 *
 * Created: 07-05-2023 13:56:06
 * Author : Karl-Emil
 */ 

#include "X10.h"
#include "UART.h"
#include "Alarms.h"
#include "clock.h"
#include "DE2.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000
#include <util/delay.h>

volatile bool charReceived = false;
ISR(USART0_RX_vect)
{
	charReceived = true;
	//PORTB = 0b11110000;
	UCSR0B &= ~(1<<7);
}

ISR(TIMER3_COMPA_vect){//1 sekundsur
	secCount++;
	if (secCount >= 60)// hvis et minut er gået
	{
		secCount = 0;
		minTrigger = true;
	}	
}

ISR(TIMER1_COMPA_vect)//120kHz burst
{
	
	if (burstEnabled)// Check om der skal burstes
	{
		
		PINB |= (1 << PB7); //toggle PB7(digital pin 13) == ca. 120kHz 
	}
	else
	{
		
		PORTB &= ~(1 << PB7);// sæt ben = 0V. ellers kan den ende på at være tændt
	}
}

ISR(INT2_vect){//læser firkantssignal 
	intTrigger = true; //angiver modtaget any-edge
}


int main()	
{	//initiering
	readAlarmsEEPROM(alarmSettings); // læs alarmer fra memory. OBS tjek om allerede skrevet - overskriv med 99999/00000 for at nulstille
	sei();//global enable interrupts
	timerClockSetup(); //setup ur 
	setupX10(); //setup X10-buzzer
	InitUART(9600,8, 1);//baudrate 9600 std-uart, 8-databit, ingen paritet
	initLyd(); // init buzzeren
	
	while(1){
		if(checkReset()){ //tjek om der er trykket på resetknappen
			runCommand(slave1_buzzer_off);//kør alle off-kommandoer
			runCommand(slave2_kaffe_off);
			runCommand(slave1_lys_off);
			runCommand(slave1_gardin_off);
		}
		
		//tjekker hvis nye alarmer skal modtages, eller de nuværende skal overføres
		if(charReceived){
			idle = false; //angiv at vi er optaget
			serialReadAlarms(); //modtag alarmer fra pc via uart, skriver til alarmsettings
			
			writeAlarmsEEPROM(alarmSettings); // skriv til eeprom via alarm
			idle = true; 
			charReceived = false;
		}
		if(minTrigger){//tjek om der er gået et minut
			minTrigger = false;
			incrementTime(currentTime);
			alarmStatus = 0; // reset alarmstatus så alarmer kan køres igen.
		}
		//tjek alarmer
		if(idle && (alarmStatus << 4) != 0b11110000){ //hvis alle on-alarmer er kørt dette minut behøves der ikke tjekkes for flere alarmer.
			chooseCommand(checkTime(currentTime)); //tjek om currenttime passer med nogle af alarmerne, og hvis de gør - kør dem
		}

	}
}
