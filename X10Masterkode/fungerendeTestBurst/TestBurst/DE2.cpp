/*
 * DE2.cpp
 *
 * Created: 15-05-2023 10:51:31
 *  Author: Karl-Emil
 */ 
#include "DE2.h"

bool boardUnlocked(){
	if(!(PINH & 0b00000001)){//hvis der er str�m ind p� PB6, angiver l�st op fra kodel�sen
		PORTB = 0b10000000;
		return true;
	}
	PORTB = 0b01000000;
	return false;
}