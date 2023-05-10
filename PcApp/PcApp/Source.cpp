#include "Serial.h"
#include "Week.h"
#include "Ui.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <string>

bool recieveSerial(CSerial& serial);

void main()
{
	CSerial serial;
	string input;
	Ui ui;

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

		ui.update();
	}
}

bool recieveSerial(CSerial& serial)
{
	if (serial.Open(6, 9600))
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
