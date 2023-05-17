#include "X10Reciever_1.h"
#include "LED.h"

X10Reciever_1::X10Reciever_1(int alarm, int curtain, int light)
{
	command_1[0] = (alarm == 1 || alarm == 0 ? alarm : 0);
	command_1[1] = (curtain == 1 || curtain == 0 ? curtain : 0);
	command_1[2] = (light == 1 || light == 0 ? light : 0);
	command_1[3] = 0;

	recieveCommand1(command_1, 4);
}

void X10Reciever_1::recieveCommand1(int command1[], const int size1)
{
	for (int i = 0; i < size1; i++)
	{
		if (command_1[i] = 1)
		{
			alarmOn();										//Eventuelt lave en idle og toggle version for de forskellige komponenter
		}
		else
		{
			alarmOff();
		}

		if (command_1[i] = 1)
		{
			rollUp();											//Eventuelt lave en idle og toggle version for de forskellige komponenter
		}
		else
		{
			rollDown();
		}

		if (command_1[i] = 1)
		{
			lightOn();										//Eventuelt lave en idle og toggle version for de forskellige komponenter
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
