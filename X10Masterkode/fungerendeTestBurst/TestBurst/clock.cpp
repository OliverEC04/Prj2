/*
 * clock.cpp
 *
 * Created: 10-05-2023 16:27:27
 *  Author: Karl-Emil
 */ 
#include "clock.h"

volatile int secCount = 0;
volatile bool minTrigger = false;

void timerClockSetup(){
	
	 // Timer1: CTC mode 
	 TCCR3A = 0b00000000;
	 TCCR3B = 0b00001100;//PreScaler = 256
	 // Match frekvens = 16000000/256/31250/2 = 1 (gange per sekund)
	 //OCR3A = 31250;
	 OCR3A = 62500;
	 // Enable Timer1 Compare Match interrupt (A-system)
	 TIMSK3 |= 0b00000010;
}

void incrementTime(volatile int& ct) {
	int days = ct / 10000;
	int hours = (ct % 10000) / 100;
	int minutes = ct % 100;

	//fra bunden op-inkrementering
	minutes++;
	if (minutes >= 60) {
		minutes = 0;
		hours++;
		if (hours >= 24) {
			hours = 0;
			days++;
			if (days > 7) {
				days = 1;
			}
		}
	}

	ct = days * 10000 + hours * 100 + minutes; //saml tiden til samme syntax
}

