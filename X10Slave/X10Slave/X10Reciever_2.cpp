#include "X10Reciever_2.h"
#include "LED.h"

X10Reciever_2::X10Reciever_2(int decodedByte)
{
	command_2_ = decodedByte;
	
	//recieveCommand2(command_2_);
}

void X10Reciever_2::recieveCommand2(char decodedByte)
{
	if (decodedByte & 0b00001000 == 0b00001000)
	{
		startCoffee();
	}
	else
	{
		stopCoffee();
	}
}

void X10Reciever_2::startCoffee()
{
	turnOnLED(3);
}

void X10Reciever_2::stopCoffee()
{
	turnOffLED(3);
}


