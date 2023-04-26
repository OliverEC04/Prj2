#include "Serial.h"
#include "Week.h"
#include "Ui.h"

#define UNIX_LENGTH 10

void main()
{
	cout << sendString(10, 9600, "1234567890");
}

bool sendString(int port, int baudRate, string data)
{

	CSerial* s = new CSerial();

	if (!s->Open(port, baudRate))
	{
		cout << "Could not open COM" << port << endl;
		return false;
	}

	s->SendData(const_cast<char*>(data.c_str()), UNIX_LENGTH);

	s->Close();

	delete s;

	return true;
}

