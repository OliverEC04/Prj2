#pragma once

#include <iostream>

using namespace std;

class Day
{
public:
	Day(int name = 9, int alarmTime = 99999, int coffeeTime = 99999, int lampTime = 99999, int curtainTime = 99999);

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

