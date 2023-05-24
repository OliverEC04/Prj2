#include "Ui.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int concatInts(int sel, int hrs, int min);

CSerial* s = new CSerial();

Ui::Ui()
{
	daySelector_ = 0;

	for (size_t i = 0; i < DAYS; i++)
	{
		cout << dayStrings_[i] << endl;
	}
}

void Ui::update()
{
	switch (menuSelector_)
	{
	case 0:
		dayMenu();
		break;

	case 1:
		timeMenu();
		break;

	case 2:
		inputMenu();
		break;
	}
}

void Ui::dayMenu()
{
	dayStrings_[daySelector_].replace(0, 1, " ");

	switch (_getch())
	{
		case KEY_UP:
			daySelector_--;
			if (daySelector_ < 0)
			{
				daySelector_ = DAYS - 1;
			}
			break;

		case KEY_DOWN:
			daySelector_++;
			if (daySelector_ > DAYS - 1)
			{
				daySelector_ = 0;
			}
			break;

		case KEY_RIGHT:
			menuSelector_ = 1;

			system("cls");
			for (size_t i = 0; i < 7; i++)
			{
				int pos = dayStrings_[i].find("disabled");
				dayStrings_[i].replace(pos, 8, "");
			}
			
			timeStrings_[timeSelector_].replace(0, 1, ">");
			for (size_t i = 0; i < TIMES; i++)
			{
				cout << timeStrings_[i] << endl;
			}

			return;
			break;

		case 'f':
			updateConfiguration();
			return;
			break;
		case 'x':
			dayStrings_[daySelector_]+="disabled";
			week_.days_[daySelector_].setAlarmTime(99999);
			week_.days_[daySelector_].setCoffeeTime(99999);
			week_.days_[daySelector_].setLampTime(99999);
			week_.days_[daySelector_].setCurtainTime(99999);
			return;
			break;
	}

	dayStrings_[daySelector_].replace(0, 1, ">");

	system("cls");

	for (size_t i = 0; i < DAYS; i++)
	{
		cout << dayStrings_[i] << endl;
	}
}

void Ui::timeMenu()
{
	timeStrings_[timeSelector_].replace(0, 1, " ");

	switch (_getch())
	{
	case KEY_UP:
		timeSelector_--;
		if (timeSelector_ < 0)
		{
			timeSelector_ = TIMES - 1;
		}
		break;

	case KEY_DOWN:
		timeSelector_++;
		if (timeSelector_ > TIMES - 1)
		{
			timeSelector_ = 0;
		}
		break;

	case KEY_LEFT:
		menuSelector_ = 0;

		system("cls");

		dayStrings_[daySelector_].replace(0, 1, ">");
		for (size_t i = 0; i < DAYS; i++)
		{
			cout << dayStrings_[i] << endl;
		}

		return;
		break;

	case KEY_RIGHT:
		menuSelector_ = 2;
		saveState_ = false;

		system("cls");

		return;
		break;
	}

	system("cls");

	timeStrings_[timeSelector_].replace(0, 1, ">");

	for (size_t i = 0; i < TIMES; i++)
	{
		cout << timeStrings_[i] << endl;
	}
}

void Ui::inputMenu()
{
	if (!saveState_)
	{
		cout << "Enter time: ";
		cin >> inputHrs_;
		system("cls");

		if (inputHrs_ < 0 || inputHrs_ > 23)
		{
			inputHrs_ = 23;
		}

		cout << "Enter time: " << inputHrs_ << ":";
		cin >> inputMin_;

		if (inputMin_ < 0 || inputMin_ > 59)
		{
			inputMin_ = 59;
		}
		
		system("cls");

		cout << "Entered time: " << inputHrs_ << ":" << inputMin_ << endl << endl;

		inputStrings_[inputSelector_].replace(0, 1, ">");
		for (size_t i = 0; i < INPUTS; i++)
		{
			cout << inputStrings_[i] << endl;
		}

		saveState_ = true;
	}

	inputStrings_[inputSelector_].replace(0, 1, " ");

	switch (_getch())
	{
	case KEY_UP:
		inputSelector_--;
		if (inputSelector_ < 0)
		{
			inputSelector_ = INPUTS - 1;
		}
		break;

	case KEY_DOWN:
		inputSelector_++;
		if (inputSelector_ > INPUTS - 1)
		{
			inputSelector_ = 0;
		}
		break;

	case KEY_RIGHT:
		menuSelector_ = 1;

		int timeSaved = concatInts(daySelector_ + 1, inputHrs_, inputMin_);

		switch (timeSelector_)
		{
			case 0:
				week_.days_[daySelector_].setAlarmTime(timeSaved);
				break;

			case 1:
				week_.days_[daySelector_].setCoffeeTime(timeSaved);
				break;

			case 2:
				week_.days_[daySelector_].setLampTime(timeSaved);
				break;

			case 3:
				week_.days_[daySelector_].setCurtainTime(timeSaved);
				break;
		}

		system("cls");

		timeStrings_[timeSelector_].replace(0, 1, ">");
		for (size_t i = 0; i < TIMES; i++)
		{
			cout << timeStrings_[i] << endl;
		}

		return;
		break;
	}

	system("cls");

	cout << "Entered time: " << inputHrs_ << ":" << inputMin_ << endl << endl;

	inputStrings_[inputSelector_].replace(0, 1, ">");

	for (size_t i = 0; i < INPUTS; i++)
	{
		cout << inputStrings_[i] << endl;
	}
}

void Ui::updateConfiguration()
{
	string config = week_.getConfig();

	if (!s->Open(3, 9600))
	{
		cout << "Failed to open port!" << endl;
	}
	else
	{
		for (size_t i = 0; i < 140; i++)
		{
			char temp = config[i];
			int bytesWritten = s->SendData(&temp, 1);
		}
	}

	cout << config;
}

int concatInts(int sel, int hrs, int min)
{
	string selStr = to_string(sel);
	string hrsStr = to_string(hrs);
	string minStr = to_string(min);

	if (hrs < 10)
	{
		hrsStr = "0" + hrsStr;
	}

	if (min < 10)
	{
		minStr = "0" + minStr;
	}

	return stoi(selStr + hrsStr + minStr);
}
