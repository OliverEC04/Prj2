/*
 * DE2.cpp
 *
 * Created: 15-05-2023 10:51:31
 *  Author: Karl-Emil
 */ 
#include "DE2.h"

bool boardUnlocked(){
	if(!(PINH & 0b00000001)){//hvis der er strøm ind på PB6, angiver låst op fra kodelåsen
		PORTB = 0b10000000;
		return true;
	}
	PORTB = 0b01000000;
	return false;
}