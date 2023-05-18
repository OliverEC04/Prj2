#include "X10Reciever_1.h"
#include "LED.h"

X10Reciever_1::X10Reciever_1(int decodedByte)
{
	command_1_ = decodedByte;
	
	//recieveCommand1(command_1_);
}

void X10Reciever_1::recieveCommand1(char decodedByte)
{
	for (int i = 0; i < 4; i++)
	{
		if (decodedByte & 0b00000001 == 0b00000001)
		{
			alarmOn();											//Eventuelt lave en idle og toggle version for de forskellige komponenter
		}
		else
		{
			alarmOff();
		}

		if (decodedByte & 0b00000010 == 0b00000010)
		{
			rollUp();											//Eventuelt lave en idle og toggle version for de forskellige komponenter
		}
		else
		{
			rollDown();
		}

		if (decodedByte & 0b00000100 == 0b00000100)
		{
			lightOn();											//Eventuelt lave en idle og toggle version for de forskellige komponenter
		}
		else
		{
			lightOff();
		}

		break;
	}
}

void X10Reciever_1::alarmOn()
{
	turnOnLED(0);
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
}

void X10Reciever_1::lightOff()
{
	turnOffLED(2);
}
