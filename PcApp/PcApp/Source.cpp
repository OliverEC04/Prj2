#include "Ui.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <string>

bool recieveSerial(CSerial& serial);

void main()
{
	string input;
	Ui ui;
	CSerial *serial = new CSerial();

	while (1)
	{
		/*if (recieveSerial(serial) == 1)
			cout << "recieveSerial(serial)";

		cin >> input;

		if (input.find("AlarmTime") != string::npos)
		{
			int spacePos = input.find(':');
			string timeStr = input.substr(spacePos + 1, spacePos + 5);

			int ourTime = stoi(timeStr);

			week.days_[0].setAlarmTime(ourTime);
		}


		week.sendConfig(serial);*/

		if (!serial->Open(10, 9600))
		{
			cout << "Serial working" << endl;
			serial->SendData("V", 1);
		}
		else
			cout << "Failed to open port!" << endl;

		//ui.update(serial);
	}
}

bool recieveSerial(CSerial& serial)
{
	if (serial.Open(10, 9600))
	{
		char* lpBuffer = new char[1];
		int nBytesRead = serial.ReadData(lpBuffer, 1);
		if (lpBuffer[0] > 0)
		{
			delete[]lpBuffer;
			return true;
		}
		else
		{
			delete[]lpBuffer;
			return false;
		}
	}
	else
		cout << "Failed to open port!" << endl;
	
	return 0;
}
