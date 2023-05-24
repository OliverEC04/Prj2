#include "X10Reciever_1.h"
#include "LED.h"
#include "lamp.h"
#include "lyd.h"

X10Reciever_1::X10Reciever_1(int decodedByte)
{
	command_1_ = decodedByte;
	
	//recieveCommand1(command_1_);
}

void X10Reciever_1::recieveCommand1(char decodedByte)
{
	decodedByte &= 0b00000111;
	
	switch(decodedByte)
	{
		case 0b00000110:
			alarmOn();
			break;
			
		case 0b00000111:
			alarmOff();
			break;
			
		case 0b00000100:
			lightOn();
			break;
		
		case 0b00000101:
			lightOff();
			break;
		
		case 0b00000000:
			rollUp();
			break;
		
		case 0b00000001:
			rollDown();
			break;
	}
}

void X10Reciever_1::alarmOn()
{
	turnOnLED(0);
	playAlarmSound();
}

void X10Reciever_1::alarmOff()
{
	turnOffLED(0);
}

void X10Reciever_1::rollUp()
{
	turnOnLED(1);
}

void X10Reciever_1::rollDown()
{
	turnOffLED(1);
}

void X10Reciever_1::lightOn()
{
	turnOnLED(2);
	fadeLampOn(100);
}

void X10Reciever_1::lightOff()
{
	turnOffLED(2);
	lampOff();
}
