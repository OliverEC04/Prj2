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
void playAlarmSound(){
	for(int i = 0; i < 5; i++){
		
		for(int i = 0; i < 100; i++){
			PORTB = ~PINB;
			_delay_us(250);
		}
		_delay_ms(25);
		for(int i = 0; i < 100; i++){
			PORTB = ~PINB;
			_delay_us(250);
		}
		_delay_ms(25);
		for(int i = 0; i < 100; i++){
			PORTB = ~PINB;
			_delay_us(250);
		}
		_delay_ms(25);
		for(int i = 0; i < 100; i++){
			PORTB = ~PINB;
			_delay_us(250);
		}
		
		_delay_ms(200);
	}
}


