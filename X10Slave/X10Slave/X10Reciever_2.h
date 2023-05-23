#pragma once
#define SIZE_2 4

class X10Reciever_2
{
	public:
	X10Reciever_2(int decodedByte = 0);
	void recieveCommand2(char decodedByte);

	void startCoffee();
	void stopCoffee();

	private:
	int command_2_;
}; //Slave2


