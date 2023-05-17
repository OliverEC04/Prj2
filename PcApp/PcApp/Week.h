#pragma once
#include "Week.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include "Day.h"

class Week
{
public:
	Week();

	string getConfig();

	Day days_[7];	
};

