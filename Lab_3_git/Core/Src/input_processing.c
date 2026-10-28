#include "main.h"
#include "input_reading.h"
#include "input_processing.h"
#include "led_display.h" // Thêm để gọi hàm tắt đèn khi chuyển Mode
#include "timer.h"

// Biến lưu mode hiện tại
int systemMode = MODE_1_NORMAL;

// Biến lưu thời gian của các đèn
int time_red = 5;
int time_yellow = 2;
int time_green = 3;

// Biến lưu thời gian tạm khi đang ở chế độ chỉnh sửa
int temp_duration = 0;

enum ButtonState {
    BUTTON_RELEASED,
    BUTTON_PRESSED,
    BUTTON_PRESSED_MORE_THAN_1_SECOND
};

// 3 nút: 0 - mode, 1 - tăng tgian, 2 - lưu
enum ButtonState button0State = BUTTON_RELEASED;
enum ButtonState button1State = BUTTON_RELEASED;
enum ButtonState button2State = BUTTON_RELEASED;

void fsm_for_input_processing(void) {

    // Xét trạng thái của button 0 --> Nếu nhấn thì chuyển mode
    switch (button0State) {
        case BUTTON_RELEASED:
            if (is_button_pressed(0)) {
                button0State = BUTTON_PRESSED;

                // Chuyển MODE
                switch (systemMode) {
                    case MODE_1_NORMAL:
                        systemMode = MODE_2_RED;
                        temp_duration = time_red;
                        turn_off_all_traffic_lights();
                        setTimer(1, 250); // Kích hoạt timer nhấp nháy 2Hz (250ms)
                        break;
                    case MODE_2_RED:
                        systemMode = MODE_3_YELLOW;
                        temp_duration = time_yellow;
                        turn_off_all_traffic_lights();
                        setTimer(1, 250);
                        break;
                    case MODE_3_YELLOW:
                        systemMode = MODE_4_GREEN;
                        temp_duration = time_green;
                        turn_off_all_traffic_lights();
                        setTimer(1, 250);
                        break;
                    case MODE_4_GREEN:
                        systemMode = MODE_1_NORMAL;
                        turn_off_all_traffic_lights();
                        break;
                }
            }
            break;

        case BUTTON_PRESSED:
            if (!is_button_pressed(0)) {
                button0State = BUTTON_RELEASED;
            }
            break;
        default: break;
    }

    // Xét trạng thái của button 1 (Tăng thời gian)
    switch (button1State) {
        case BUTTON_RELEASED:
            if (is_button_pressed(1)) {
                button1State = BUTTON_PRESSED;

                // Tăng giá trị temp lên 1 khi nhấn 1 lần
                if (systemMode != MODE_1_NORMAL) {
                    temp_duration++;
                    if (temp_duration > 99) temp_duration = 1;
                }
            }
            break;
        case BUTTON_PRESSED:
            if (!is_button_pressed(1)) {
                button1State = BUTTON_RELEASED;
            } else {
                if (is_button_pressed_1s(1)) {
                    button1State = BUTTON_PRESSED_MORE_THAN_1_SECOND;
                    // Tăng ngay 1 đơn vị khi giữ tròn 1s
                    if (systemMode != MODE_1_NORMAL) {
                        temp_duration++;
                        if (temp_duration > 99) temp_duration = 1;
                    }
                    // Bật Timer index 2 chạy 500ms cho các lần tăng tự động tiếp theo
                    setTimer(2, 500);
                }
            }
            break;
        case BUTTON_PRESSED_MORE_THAN_1_SECOND:
            if (!is_button_pressed(1)) {
                button1State = BUTTON_RELEASED;
            } else {
                // Tăng tự động mỗi 500ms khi vẫn còn giữ nút
                if (timer_flag[2] == 1) {
                    if (systemMode != MODE_1_NORMAL) {
                        temp_duration++;
                        if (temp_duration > 99) temp_duration = 1;
                    }
                    setTimer(2, 500);
                }
            }
            break;
        default: break;
    }

    // Xét trạng thái button 2 (Lưu giá trị)
    switch (button2State) {
        case BUTTON_RELEASED:
            if (is_button_pressed(2)) {
                button2State = BUTTON_PRESSED;

                // Lưu giá trị và tự động cân bằng Red = Green + Yellow
                switch (systemMode) {
                    case MODE_2_RED:
                        if (temp_duration <= time_yellow) {
                            temp_duration = time_yellow + 1;
                        }
                        time_red = temp_duration;
                        time_green = time_red - time_yellow;
                        break;
                    case MODE_3_YELLOW:
                        time_yellow = temp_duration;
                        time_red = time_green + time_yellow;
                        if (time_red > 99) { // Chống tràn quá 99s trên LED 7 đoạn
                            time_red = 99;
                            time_green = time_red - time_yellow;
                        }
                        break;
                    case MODE_4_GREEN:
                        time_green = temp_duration;
                        time_red = time_green + time_yellow;
                        if (time_red > 99) { // Chống tràn quá 99s trên LED 7 đoạn
                            time_red = 99;
                            time_yellow = time_red - time_green;
                        }
                        break;
                    default: break;
                }
            }
            break;
        case BUTTON_PRESSED:
            if (!is_button_pressed(2)) {
                button2State = BUTTON_RELEASED;
            }
            break;
        default: break;
    }
}
