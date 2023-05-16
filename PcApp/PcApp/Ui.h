#pragma once

#include <iostream>
#include <conio.h>
#include "Week.h"
#include "Serial.h"

#define DAYS 7
#define TIMES 4
#define INPUTS 2

using namespace std;

class Ui
{
public:
	Ui();
	void update();
	void dayMenu();
	void timeMenu();
	void inputMenu();

private:
	Week week_;
	int menuSelector_ = 0;
	int daySelector_ = 0;
	int timeSelector_ = 0;
	int inputSelector_ = 0;
	int inputHrs_;
	int inputMin_;
	bool saveState_ = false;
	string dayStrings_[DAYS] = {
		">Monday",
		" Tuesday",
		" Wednesday",
		" Thursday",
		" Friday",
		" Saturday",
		" Sunday"
	};
	string timeStrings_[TIMES] = {
		">Alarm Time",
		" Coffee Time",
		" Lamp Time",
		" Curtain Time"
	};
	string inputStrings_[INPUTS] = {
		">Save",
		" Cancel"
	};
};

