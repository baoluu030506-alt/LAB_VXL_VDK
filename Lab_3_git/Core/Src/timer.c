#include "main.h"
#include "input_reading.h"
#include "timer.h"

int timer_flag[4] = {0, 0, 0, 0};
int timer_counter[4] = {0, 0, 0, 0};

//Index 0: đếm theo chu kì 1s cho đèn giao thông
//Index 1: tạo hiệu ứng nhấp nháy 2Hz
//Index 2: dùng cho việc tăng giá trị

void setTimer(int index, int duration){
	timer_counter[index] = duration / TICK;
	timer_flag[index] = 0;
}

void timerRun(){
	for(int i = 0; i < 4; i++){
		if(timer_counter[i] > 0){
			timer_counter[i]--;
			if(timer_counter[i] <= 0) timer_flag[i] = 1;
		}
	}
}

