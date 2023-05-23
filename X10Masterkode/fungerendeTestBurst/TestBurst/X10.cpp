/*
 * X10.cpp
 *
 * Created: 09-05-2023 13:15:25
 *  Author: Karl-Emil
 */ 
#include "X10.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000
#include <util/delay.h>

volatile bool burstEnabled = false; //når true sendes der burst

volatile bool intTrigger = false; //sættes true når der er modtaget any-edge interrupt fra firkantsignal

volatile bool idle = true; //angiver om vi er igang med at burste

volatile uint8_t alarmStatus = 0; //hver bit representerer om en kommando er blevet kørt i dette minut. 

volatile int currentTime = 41451; // variabel til at tiden DHHMM 

// evt kan disse assignments smides ind i main for overskueligheden
int coffeeTime = 0; // tiden kaffen skal slukkes(minutter) - bliver aldrig 0, mindst 10000
int coffeeDelay = 1; //antal minutter efter den er startet, den skal slukkes
int buzzerTime = 99; //tiden buzzer skal slukkes(sekunder)
int buzzerDelay = 20;//antal sekunder buzzeren skal køre
//Gardin og lys bliver ikke slukket



int slave1_buzzer_on[12]  = {1,1,1,0,1,0,1,0,1,0,0,1}; //kommando 1
int slave2_kaffe_on[12]  = {1,1,1,0,0,1,1,0,1,0,0,1};  //kommando 2
int slave1_lys_on[12]  = {1,1,1,0,1,0,1,0,0,1,0,1};    //kommando 3
int slave1_gardin_on[12]  = {1,1,1,0,1,0,0,1,0,1,0,1}; //kommando 4
int slave1_buzzer_off[12] = {1,1,1,0,1,0,1,0,1,0,1,0}; //kommando 5
int slave2_kaffe_off[12]  = {1,1,1,0,0,1,1,0,1,0,1,0}; //kommando 6
int slave1_lys_off[12]  = {1,1,1,0,1,0,1,0,0,1,1,0};   //kommando 7
int slave1_gardin_off[12]  = {1,1,1,0,1,0,0,1,0,1,1,0};//kommando 8

void setupX10()
{
	//burst
	DDRB |= (1 << PB7);//  PB7 (Digital pin 13) som burst pin
	
	TCCR1A |= 0b00000000;
	TCCR1B |= 0b00001001;// Set timer 1 i CTCmode
	
	OCR1A = 66;//udregnet 66 - giver 120khz
	
	TIMSK1 |= (1 << OCIE1A);// Enable compare match interrupt
	
	
	//EL-net interrupt initialisering
	DDRD &= ~(1 << PD2); // set PD2 som indgang
	EIMSK |= 0b00000100; //enable interrupt 2
	EICRA |= 0b00010000; // enable any edge trigger
	EICRB |= 0b00000000;
	
	//reset-knap
	DDRA = 0; //SW-knapper sættes som input, er active low
	
}

void sendBurst() //sender burst i 1 ms
{
	burstEnabled = true;
	_delay_us(340);//prøvet mig frem til, har ca 1 ms varighed
	burstEnabled = false;
}

void runCommand(int* command)//sender kommando
{
	idle = false; //angiv at vi er optaget
	
	intTrigger = false; // vent på næste edge fra firkantsignal
	while(!intTrigger)
	{
	}

	for(int i = 0; i < 12; i++) //gennemløb givne kommando
	{
		if(command[i] == 1) // hvis 1: send et burst, ellers ikke
		{
			sendBurst();
		}
		intTrigger = false; // vent på næste edge
		while(!intTrigger)
		{
		}
	}

	idle = true; //færdig med at køre kommando
}

bool checkReset(){
	return (~PINA & 0b00000001); //da PINA(SW0-7
}

void chooseCommand(int res){
	switch (res)
	{
		case 1:
			if(!(alarmStatus & 0b00000001)){
				runCommand(slave1_buzzer_on); //kør valgt kommando (med resultat fra checkTime(currentTime))
				alarmStatus |= 0b00000001;	//sæt status bit'et for kommandoen
				buzzerTime = secCount + buzzerDelay;
			}
			break;
		case 2:
			if(!(alarmStatus & 0b00000010)){
				runCommand(slave2_kaffe_on);
				alarmStatus |= 0b00000010;
				coffeeTime = currentTime + coffeeDelay;//sæt tiden den skal slukkes
			}
			break;
		case 3:
			if(!(alarmStatus & 0b00000100)){
				runCommand(slave1_lys_on);
				alarmStatus |= 0b00000100;
			}
			break;
		case 4:
			if(!(alarmStatus & 0b00001000)){
				runCommand(slave1_gardin_on);
				alarmStatus |= 0b00001000;
			}
			break;
		case 5:
			if(!(alarmStatus & 0b00010000)){
				runCommand(slave1_buzzer_off);
				alarmStatus |= 0b00010000;
			}
			break;
		case 6:
			if(!(alarmStatus & 0b00100000)){
				runCommand(slave2_kaffe_off);
				alarmStatus |= 0b00100000;
			}
			break;
		case 7:
			if(!(alarmStatus & 0b0100000)){
				runCommand(slave1_lys_off);
				alarmStatus |= 0b01000001;
			}
			break;
		case 8:
			if(!(alarmStatus & 0b10000000)){
				runCommand(slave1_gardin_off);
				alarmStatus |= 0b10000000;
			}
			break;
		default:
			break;
	}
}


