#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"

#define TICK 10

extern int timer_flag[4];
extern int timer_counter[4];

void setTimer(int index, int duration);
void timerRun();

#endif /* INC_TIMER_H_ */
