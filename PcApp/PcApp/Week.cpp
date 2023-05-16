#include "Week.h"

#define CONFIG_LENGTH 168

using namespace std;

Week::Week()
{
	for (size_t i = 0; i < 7; i++)
	{
		days_[i] = Day(i);
	}
}

string Week::getConfig(int day)
{
	string config;
	day--;

	config += to_string(days_[day].getAlarmTime());
	config += to_string(days_[day].getCoffeeTime());
	config += to_string(days_[day].getLampTime());
	config += to_string(days_[day].getCurtainTime());

	return config;
}
