#include "Day.h"


Day::Day(int name, int alarmTime, int coffeeTime, int lampTime, int curtainTime) :
	name_(name), alarmTime_(alarmTime), coffeeTime_(coffeeTime), lampTime_(lampTime), curtainTime_(curtainTime)
{
}

void Day::setAlarmTime(int time)
{
	alarmTime_ = time;
}

void Day::setCoffeeTime(int time)
{
	coffeeTime_ = time;
}

void Day::setLampTime(int time)
{
	lampTime_ = time;
}

void Day::setCurtainTime(int time)
{
	curtainTime_ = time;
}

int Day::getAlarmTime() const
{
	return alarmTime_;
}

int Day::getCoffeeTime() const
{
	return coffeeTime_;
}

int Day::getLampTime() const
{
	return lampTime_;
}

int Day::getCurtainTime() const
{
	return curtainTime_;
}
