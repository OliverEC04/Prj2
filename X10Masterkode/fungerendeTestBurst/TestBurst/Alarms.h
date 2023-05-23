/*
 * Alarms.h
 *
 * Created: 10-05-2023 09:58:21
 *  Author: Karl-Emil
 */ 


#ifndef ALARMS_H_
#define ALARMS_H_

#include "UART.h"
#include "DE2.h"
#include "lyd.h"
#include <avr/boot.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>


extern int alarmSettings[][4];
extern uint8_t DATA_ADDRESS; 
extern volatile uint8_t alarmStatus;
extern char buffer[140];

void writeAlarmsEEPROM(int data[][4]);
void readAlarmsEEPROM(int data[][4]);
void serialReadAlarms();
void serialSendAlarms();
int checkTime(int);

#endif /* ALARMS_H_ */