#include "X10Reciever_2.h"
#include "LED.h"

X10Reciever_2::X10Reciever_2(int coffeemachine)
{
	command_2[0] = 0;
	command_2[1] = 0;
	command_2[2] = 0;
	command_2[3] = (coffeemachine == 1 || coffeemachine == 0 ? coffeemachine : 0);

	recieveCommand2(command_2, 4);
}

void X10Reciever_2::recieveCommand2(int command2[], const int size2)
{
	if (command_2[3] == 1)
	{
		//startCoffee();												//Eventuelt lave en idle og toggle version for de forskellige komponenter
	}
	else
	{
		//stopCoffee();													//Eventuelt lave en idle og toggle version for de forskellige komponenter

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


