
/*
 * X10.h
 *
 * Created: 09-05-2023 13:13:35
 *  Author: Karl-Emil
 */ 


#ifndef X10_H_
#define X10_H_
#include "clock.h"
#include "lyd.h"
#include <stdbool.h>
#include <stdint.h>

extern volatile bool burstEnabled;
extern volatile bool intTrigger;
extern volatile bool idle;
extern volatile uint8_t alarmStatus;
extern volatile int currentTime;
extern int coffeeTime;
extern int buzzerTime;

extern int slave1_buzzer_on[12];
extern int slave1_buzzer_off[12];
extern int slave1_lys_on[12];
extern int slave1_lys_off[12];
extern int slave1_gardin_on[12];
extern int slave1_gardin_off[12];
extern int slave2_kaffe_on[12];
extern int slave2_kaffe_off[12];

void setupX10();
void sendBurst();
void runCommand(int* command);
bool checkReset();
void chooseCommand(int);


#endif /* X10_H_ */