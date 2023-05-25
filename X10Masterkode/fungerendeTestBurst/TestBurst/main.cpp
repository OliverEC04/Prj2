/*
 * burstTest.cpp
 *
 * Created: 07-05-2023 13:56:06
 * Author : Karl-Emil
 */ 

#include "X10.h"
#include "UART.h"
#include "Alarms.h"
#include "RTC.h"
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

ISR(TIMER2_COMPA_vect){//SCL-taeller 100 kHz
	toggleSCL();
}


int main()	
{
	//denne blok kan in og ud-kommenteres for at påvise at hukommelsen er gemt.
	int testSettings[7][4];
	for(int i = 0; i < 7; i++){
		for(int j = 0; j < 4; j++){
			testSettings[i][j] = 99999;
		}
	}
	testSettings[2][0] = 31257;
	testSettings[2][1] = 31258;
	testSettings[2][2] = 31259;
	testSettings[2][3] = 31300;
	//initiering
	
	writeAlarmsEEPROM(testSettings);
	
	readAlarmsEEPROM(alarmSettings); // læs alarmer fra memory. OBS tjek om allerede skrevet - overskriv med 99999/00000 for at nulstille
	
	sei();
	//RTCsetup(); //setup RTC
	//currentTime = I2CreadTime(); // læs tiden fra RTC
	timerClockSetup(); //setup ur 
	setupX10(); //setup X10-buzzer
	InitUART(9600,8, 1);//baudrate 9600 std-uart, 8-databit, ingen paritet
	initLyd();
	//PORTB = 0;
	sei();
	
	
	while(1){
		if(checkReset()){ //tjek om der er trykket på resetknappen
			runCommand(slave1_buzzer_off);//kør alle off-kommandoer
			//_delay_us(50);
			runCommand(slave2_kaffe_off);
			//_delay_us(50);
			runCommand(slave1_lys_off);
			//_delay_us(50);
			runCommand(slave1_gardin_off);
		}
		
		if((~PINA & 0b00000010))
			runCommand(slave1_buzzer_on);
			
		if((~PINA & 0b00000100))
			runCommand(slave2_kaffe_on);
		
		//tjekker hvis nye alarmer skal modtages, eller de nuværende skal overføres
		if(charReceived){
			idle = false; //angiv at vi er optaget
			serialReadAlarms(); //modtag alarmer fra PC via UART, skriver til alarmSettings
			
			writeAlarmsEEPROM(alarmSettings); // skriv til EEPROM via alarm
			idle = true; 
			charReceived = false;
			/*for(int i = 0; i < 7; i++){
				for(int j = 0; j < 4; j++){
					PORTB = alarmSettings[i][j];
					_delay_ms(1000);
				}
			}*/
		}
		if(minTrigger){//tjek om der er gået et minut
			minTrigger = false;
			incrementTime(currentTime);
			alarmStatus = 0; // reset alarmstatus så alarmer kan køres igen.
		}
		//tjek alarmer
		if(idle && (alarmStatus << 4) != 0b11110000){ //hvis alle ON-alarmer er kørt dette minut behøves der ikke tjekkes for flere alarmer.
			chooseCommand(checkTime(currentTime)); //tjek om currentTime passer med nogle af alarmerne, og hvis de gør - kør dem
		}
		//tjek om tiden er gået for kaffe eller buzzer
		/*if(idle && (alarmStatus >> 6) != 0b00000011){ // skal ændres hvis flere alarmer tilføjes off-tid
			if(secCount == buzzerTime){
				chooseCommand(5);//slave1_buzzer_off
			}
			if(currentTime == coffeeTime){
				chooseCommand(6); //slave2_kaffe_off
			}
		}*/
	}
	return 0;
}
