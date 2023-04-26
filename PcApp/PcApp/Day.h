#pragma once

#include <iostream>

using namespace std;

class Day
{
public:
	Day(string name = "undefined", int alarmTime = 0, int coffeeTime = 0, int lampTime = 0, int curtainTime = 0);

	void setAlarmTime(int time);
	void setCoffeeTime(int time);
	void setLampTime(int time);
	void setCurtainTime(int time);

	int getAlarmTime() const;
	int getCoffeeTime() const;
	int getLampTime() const;
	int getCurtainTime() const;

private:
	int name_;
	int alarmTime_;
	int coffeeTime_;
	int lampTime_;
	int curtainTime_;
};

