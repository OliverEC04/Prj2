/*
 * lyd.cpp
 *
 * Created: 17-05-2023 11:57:58
 *  Author: Karl-Emil
 */ 
#include "lyd.h"
#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
void initLyd(){
	DDRB = 0xFF;
}
void playLockedSound(){
	for(int i = 0; i < 210; i++){
		PORTB = ~PINB;
		_delay_us(506);
	}
	for(int i = 0; i < 180; i++){
		PORTB = ~PINB;
		_delay_us(638);
	}
	for(int i = 0; i < 170; i++){
		PORTB = ~PINB;
		_delay_us(758);
	}
	for(int i = 0; i < 400; i++){
		PORTB = ~PINB;
		_delay_us(956);
	}
}

void playUnlockedSound(){
		for(int i = 0; i < 150; i++){
			PORTB = ~PINB;
			_delay_us(956);
		}
		
		for(int i = 0; i < 170; i++){
			PORTB = ~PINB;
			_delay_us(758);
		}
		
		for(int i = 0; i < 180; i++){
			PORTB = ~PINB;
			_delay_us(638);
		}
		for(int i = 0; i < 600; i++){
			PORTB = ~PINB;
			_delay_us(506);
		}
		
}