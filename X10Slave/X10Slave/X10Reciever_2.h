#pragma once
#define SIZE_2 4

class X10Reciever_2
{
	public:
	X10Reciever_2(int coffeemachine);
	void recieveCommand2(int command2[], const int size2);

	void startCoffee();
	void stopCoffee();

	private:
	int command_2[SIZE_2];
}; //Slave2


