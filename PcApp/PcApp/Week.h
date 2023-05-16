#pragma once
#include "Serial.h"
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

	void sendConfig(CSerial& serial);

	Day days_[7];	
};

