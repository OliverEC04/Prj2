/*
 * clock.h
 *
 * Created: 10-05-2023 16:27:09
 *  Author: Karl-Emil
 */ 


#ifndef CLOCK_H_
#define CLOCK_H_

#include <avr/io.h>

extern volatile int secCount;

extern volatile bool minTrigger;

void timerClockSetup();
void incrementTime(volatile int&);


#endif /* CLOCK_H_ */