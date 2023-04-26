#pragma once

#include "Day.h"

class Week
{
public:
	Week();

	string getWeekConf();

private:
	Day* days_;
};

