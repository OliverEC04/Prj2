#include "Ui.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

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

	//cout << daySelector_ << " " << timeSelector_;
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

			timeStrings_[timeSelector_].replace(0, 1, ">");
			for (size_t i = 0; i < TIMES; i++)
			{
				cout << timeStrings_[i] << endl;
			}

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
