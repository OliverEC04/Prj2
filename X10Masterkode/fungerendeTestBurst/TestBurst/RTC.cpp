/*
 * RTC.cpp
 *
 * Created: 03-05-2023 09:53:08
 *  Author: Karl-Emil
 */ 
#include "RTC.h"
#include <avr/iom2560.h>
#include <avr/io.h>
#include <stdint.h>

volatile bool SCLinterrupt = false;

void RTCsetup(){
	DDRD |= (1 << 2);//set pin20 til output
	DDRD |= (1 << 3);// set pin21 til output
	TIMSK2 |= (1 << OCIE2A); 
	TCCR2A |= 0b00000010; // set til CTC-mode
	TCCR2B |= 0b00000001; // set prescaler til 1 og enable comparematch-intterupt
	OCR2A = 39;// 200kHz, men den skifter tilstand per ISR, s� effektivt 100 kHz
}


void I2Cstart(){
	
	//SDA g�r lav mens SCL er h�j
	PORTD |= 0b00001000; //SLC h�j
	//evt. et delay her
	PORTD &= ~(0b00000100);//SDA g�r lav
	//start timer for SCL
	
}
void I2Cstop(){
	//stop timer for SLC
	
	//SDA g�r h�j mens SCL er h�j 
	PORTD |= 0b00001000; //SLC h�j
	//evt delay
	PORTD |= 0b00000100; //SDA g�r h�j
}

void I2CSendBit(int bit){
	if(bit != 0){
		PORTD |= 0b00000100; // h�j p� SDA
	}
	else{
		PORTD &= ~(0b000000100); // lav p� SDA
	}
}
int I2CReadBit(){
	if((PIND & 0b00000100)){ // hvis der er et 1 p� SDA
		return 1;
	}
	else {
		return 0;
	}
}

void toggleSCL(){
	if((PIND & 0b00001000)){
		PORTD &= ~(0b00001000);
		SCLinterrupt = false;
	}
	else{
		PORTD |= 0b00001000;
		SCLinterrupt = true;
	}
}

int convertTime(int* days, int* hrs, int* min, int* sec, volatile int& setSeconds) {

	int day = 0, hour10 = 0, hour = 0, minute10 = 0, minute = 0, seconds10 = 0, seconds = 0;

	//dage -- ignorer de f�rste 4
	day = (days[5] << 2) | (days[6] << 1) | days[7];
	
	//hour10
	if (hrs[2]) {
		hour10 = 2;
	}
	else if (hrs[3]) {
		hour10 = 1;
	}

	//hour
	hour = (hrs[4] << 3) | (hrs[5] << 2) | (hrs[6] << 1) | hrs[7];

	//min10
	minute10 = (min[1] << 2) | (min[2] << 1) | min[3];

	//min
	minute = (min[4] << 3) | (min[5] << 2) | (min[6] << 1) | min[7];
	
	//sec10
	seconds10 = (sec[1] << 2)| (sec[2] << 1) | sec[3];
	
	seconds = (sec[4] << 3)|(sec[5] << 2)| (sec[6] << 1)| sec[7]; 

	setSeconds = (seconds10 * 10) + seconds; //overskriv sekundt�lleren

	// saml alle data p� 5-digit-form
	return (day * 10000) + (hour10 * 1000) + (hour * 100) + (minute10 * 10) + minute;
}

uint8_t I2CreadTime(){
	I2Cstart();
	DDRD |= (1 << 2);//set pin20 til output
	
	//skriv adresse
	int write[8] ={1,1,0,1,0,0,0,1}; // 7 bit Adresse +  1 read-bit
	for(int k = 0; k < 8; k++)
	{
		while(!SCLinterrupt){} //vent p� SCL
			I2CSendBit(write[k]);	
			SCLinterrupt = false;
	}
	//l�s ACK og sekunder
	DDRD &= ~(1 << 2);//set pin20 til intput
	
	while(!SCLinterrupt){}
	if(!I2CReadBit()){
		return 0;
	}
	int ICseconds[8];
	for (int a = 0; a < 8; a++){
		while(!SCLinterrupt){}
		ICseconds[a] = I2CReadBit();
		SCLinterrupt = false;
	}
	//send ACK
	DDRD |= (1 << 2);//set pin20 til output
	while(!SCLinterrupt){}
	I2CSendBit(0);
	// l�s minutter
	DDRD &= ~(1 << 2);//set pin20 til intput
	
	int ICminutes[8];
	for (int j = 0; j < 8; j++){
		while(!SCLinterrupt){}
		ICminutes[j] = I2CReadBit();
		SCLinterrupt = false;
	}
	//send ACK
	DDRD |= (1 << 2);//set pin20 til output
	while(!SCLinterrupt){}
	I2CSendBit(0);
	//l�s timer
	DDRD &= ~(1 << 2);//set pin20 til intput
	
	int IChours[8];
	for (int n = 0; n < 8; n++){
		while(!SCLinterrupt){}
		IChours[n] = I2CReadBit();
		SCLinterrupt = false;
	}
	//send ACK
	DDRD |= (1 << 2);//set pin20 til output
	while(!SCLinterrupt){}
	I2CSendBit(0);
	
	DDRD &= ~(1 << 2);//set pin20 til intput
	
	int ICday[8];
	for(int g = 0; g < 8; g++)
	{
		while(!(SCLinterrupt)){}
		ICday[g] = I2CReadBit();
		SCLinterrupt = false;
	}
	//send NACK
	while(!SCLinterrupt){}
	I2CSendBit(1);
	
	I2Cstop();
	
	return convertTime(ICday, IChours, ICminutes, ICseconds, secCount);
	
}
