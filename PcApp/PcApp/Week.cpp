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

string Week::getConfig()
{
	string config;
	for (size_t i = 0; i < 7; i++)
	{
		config += to_string(days_[i].getAlarmTime());
		config += to_string(days_[i].getCoffeeTime());
		config += to_string(days_[i].getLampTime());
		config += to_string(days_[i].getCurtainTime());
	}

	return config;
}
