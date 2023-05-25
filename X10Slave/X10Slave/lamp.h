/*
 * lamp.h
 *
 * Created: 24-05-2023 10:39:01
 *  Author: anton
 */ 
#pragma once

#ifndef LAMP_H_
#define LAMP_H_

#include <avr/io.h>

void initLamp();
void fadeLampOn(double);
void lampOff();



#endif /* LAMP_H_ */