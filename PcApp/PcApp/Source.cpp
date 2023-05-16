#include "Ui.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include "Serial.h"
#define length 1

//bool recieveSerial(CSerial& serial);

int main()
{
	string input;
	//Ui ui;
	CSerial *s = new CSerial();

	//

	string config = "0025299999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999900148";

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



		switch (_getch())
		{
		case 'f':
			if (!s->Open(7, 9600))
			{
				cout << "Failed to open port!" << endl;
			}
			else
			{
				s->SendData(config.c_str(), 140);
				cout << config.c_str();
			}
			break;
		}
		

		//ui.update(serial);
	}
}

//bool recieveSerial(CSerial& serial)
//{
//	if (serial.Open(10, 9600))
//	{
//		char* lpBuffer = new char[1];
//		int nBytesRead = serial.ReadData(lpBuffer, 1);
//		if (lpBuffer[0] > 0)
//		{
//			delete[]lpBuffer;
//			return true;
//		}
//		else
//		{
//			delete[]lpBuffer;
//			return false;
//		}
//	}
//	else
//		cout << "Failed to open port!" << endl;
//	
//	return 0;
//}
