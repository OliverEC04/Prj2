#pragma once
#define SIZE_1 4

class X10Reciever_1
{
	public:
	X10Reciever_1(int decodedByte = 0);
	void recieveCommand1(char decodedByte);

	void alarmOn();
	void alarmOff();

	void rollUp();
	void rollDown();

	void lightOn();
	void lightOff();

	private:
	int command_1_;
};