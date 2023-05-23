#include "Day.h"


Day::Day(int name, int alarmTime, int coffeeTime, int lampTime, int curtainTime) :
	name_(name), alarmTime_(alarmTime), coffeeTime_(coffeeTime), lampTime_(lampTime), curtainTime_(curtainTime)
{
}

void Day::setAlarmTime(int time)
{
	alarmTime_ = (10000 <= time <= 72359 || time == 99999 ? time : 99999);
}

void Day::setCoffeeTime(int time)
{
	coffeeTime_ = (10000 <= time <= 72359 || time == 99999 ? time : 99999);
}

void Day::setLampTime(int time)
{
	lampTime_ = (10000 <= time <= 72359 || time == 99999 ? time : 99999);
}

void Day::setCurtainTime(int time)
{
	curtainTime_ = (10000 <= time <= 72359 || time == 99999 ? time : 99999);
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
