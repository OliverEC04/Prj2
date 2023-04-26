#include "Serial.h"
#include "Week.h"
#include "Ui.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>

#define UNIX_LENGTH 1

bool sendString(int port, int baudRate, string data);
char receiveChar();

void main()
{
	CSerial* s = new CSerial();

	if (!s->Open(6, 9600))
	{
		cout << "Could not open COM" << 6 << endl;
	}


	s->SendData("7", UNIX_LENGTH);

	s->SendData("3", UNIX_LENGTH);

	char* lpBuffer = new char[3];

	while (1)
	{
		while (s->ReadDataWaiting() == 0)
		{ }
		
			s->ReadData(lpBuffer, 3);

			char buffer = *lpBuffer;

			if(buffer > 0 && buffer < 127)
				cout << buffer[]

			//arbejd videre med dette prøv med for-loop fx
			

		
	}

	delete[]lpBuffer;

	s->Close();

	delete s;
}

bool sendString(int port, int baudRate, string data)
{

	/*CSerial* s = new CSerial();

	if (!s->Open(port, baudRate))
	{
		cout << "Could not open COM" << port << endl;
		return false;
	}*/

	//s->SendData(const_cast<char*>(data.c_str()), UNIX_LENGTH);

	/*s->Close();

	delete s;*/

	return true;
}

//char receiveChar()
//{
//	CSerial* s = new CSerial();
//
//
//	return s->ReadData(0, 1);
//}

