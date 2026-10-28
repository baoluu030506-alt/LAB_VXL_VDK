#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_

// Khai báo các trạng thái của hệ thống
#define MODE_1_NORMAL 1
#define MODE_2_RED    2
#define MODE_3_YELLOW 3
#define MODE_4_GREEN  4

extern int time_red;
extern int time_yellow;
extern int time_green;

extern int systemMode;
extern int temp_duration;

void fsm_for_input_processing(void);

#endif /* INC_INPUT_PROCESSING_H_ */
