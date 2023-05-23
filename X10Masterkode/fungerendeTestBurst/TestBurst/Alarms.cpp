/*
 * Alarms.cpp
 *
 * Created: 10-05-2023 09:58:54
 *  Author: Karl-Emil
 */ 
#include "Alarms.h"

uint8_t DATA_ADDRESS = 0; //brug multiple af 84 eller 0 
// 7 dage * 4 alarmer = 28 integers * 3 bytes fyldt = 84

int alarmSettings[7][4]; // nested array til de nuværende settings
//int currentDayRead = 0;
char buffer[140];

void serialReadAlarms(){ // modtager alarmer fra PC via UART
		//char myString[140];
		
		for (size_t i = 0; i < 140; i++)
		{
			char char1 = (ReadChar() - 48);
			buffer[i] = char1;
		}
		UCSR0B |= (1<<7);// enable RTX
		int index = 0;
		if(boardUnlocked()){
			//SendString("UUUUU"); // send unlocked-besked
			playUnlockedSound();
			for(int i = 0; i < 140; i+=5){
				int D = buffer[i];//dage
				int H10 = buffer[i + 1];//10timer 
				int H1 =  buffer[i + 2]; // timer
				int M10 = buffer[i + 3];// 10minutter
				int M1 =  buffer[i + 4];// minutter
			
				//alarmSettings[index / 4][index % 4] = D + H10 + H1 + M10 + M1; //saml chars til int på form: DHHMM
				alarmSettings[index / 4][index % 4] = D * 10000 + H10 * 1000 + H1 * 100 + M10 * 10 + M1; //saml chars til int på form: DHHMM
				index++;
			}
			
		}
		else {
			playLockedSound();
			//SendString("LLLLL");// send locked-besked
		}
}

void serialSendAlarms(){ // modtager alarmer fra PC via UART
	for(int i = 0; i < 7; i++){
		for(int j = 0; j < 4; j++){
			SendInteger(alarmSettings[i][j]);
		}
	}
}

void writeAlarmsEEPROM(int data[][4]){ // skriver alarmSettings til EEPROM
	uint8_t write_address = DATA_ADDRESS;//kopier adresse
	
	eeprom_busy_wait();//vent til klar
	
	for(int i = 0; i < 7; i++){
		for(int j = 0; j < 4; j++){
			
			uint8_t LSB = data[i][j]; //inddel int i 3 bytes
			uint8_t MID = (data[i][j] >> 8);
			uint8_t MSB = (data[i][j] >> 16);
			
			eeprom_write_byte((uint8_t*)write_address,LSB);//typecast til uint8-pointer og skriv bytes.
			eeprom_busy_wait();							   //vent på den er færdig
			++write_address;								//incrementer addressen
			eeprom_write_byte((uint8_t*)write_address,MID);
			eeprom_busy_wait();
			++write_address;
			eeprom_write_byte((uint8_t*)write_address,MSB);
			eeprom_busy_wait();
			++write_address;
		}
	}
}
void readAlarmsEEPROM(int data[][4]){// læser settings fra EEPROM og skriver til alarmSettings
	uint8_t read_address = DATA_ADDRESS; 
	
	eeprom_busy_wait();
	
	for (int i = 0; i < 28; i++) {
		
		uint8_t LSB = eeprom_read_byte((uint8_t*)read_address); //læs byte fra LBS til MSB
		++read_address;
		eeprom_busy_wait();
		uint8_t MID = eeprom_read_byte((uint8_t*)read_address);
		++read_address;
		eeprom_busy_wait();
		uint8_t MSB = eeprom_read_byte((uint8_t*)read_address);
		++read_address;
		eeprom_busy_wait();
		
		data[i / 4][i % 4] = LSB | (MID << 8) | (MSB << 16); //sammensæt 32-bit int ud fra de 3 8-bit ints, og gem på korrekt plads
	}
}


int checkTime(volatile int currentTime){
	for(int i = 0; i < 7; i++){
		for(int j = 0; j < 4; j++){
			if(currentTime == alarmSettings[i][j]){ //sammenlign vores nuværende tid med alarmtiden
				switch(j){
					case 0: //Buzzer
						if(!(alarmStatus & 0b00000001)){ //hvis ikke alarmen allerede er kørt
							return 1;
						}
						break;
					
					case 1: //Kaffetid
						if(!(alarmStatus & 0b00000010)){
							return 2;
						}
						break;
					
					case 2: //lys-tid
						if(!(alarmStatus & 0b00000100)){
							return 3;
						}
						break;
					
					case 3://Gardin-tid
						if(!(alarmStatus & 0b00001000)){
							return 4;
						}
						break;
					default:
						break;
				}
			}
		}
	}
	return 0;
}