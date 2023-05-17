#pragma once
#define SIZE_1 4

class X10Reciever_1
{
	public:
	X10Reciever_1(int alarm, int curtain, int light);
	void recieveCommand1(int command1[], const int size1);

	void alarmOn();
	void alarmOff();

	void rollUp();
	void rollDown();

	void lightOn();
	void lightOff();

	private:
	int command_1[SIZE_1];
};