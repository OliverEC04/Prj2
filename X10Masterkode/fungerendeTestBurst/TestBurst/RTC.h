/*
 * RTC.h
 *
 * Created: 03-05-2023 09:52:15
 *  Author: Karl-Emil
 */ 


#ifndef RTC_H_
#define RTC_H_
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "clock.h"

extern volatile bool SCLinterrupt;//skal ændres til

void RTCsetup();
void I2Cstart();
void I2Cstop();
uint8_t I2CSendByte();
uint8_t I2CReadByte();
void I2CSendBit(int);
int I2CReadBit();
uint8_t I2CreadTime();
void I2CwriteTime(int hrs, int min, int sec);
void toggleSCL();
int convertTime(int*, int*, int*,int*, volatile int&);


#endif /* RTC_H_ */