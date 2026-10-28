#include "main.h"
#include "fsm_traffic_light.h"
#include "input_processing.h"
#include "led_display.h"
#include "timer.h"

// Các trạng thái của ngã tư
enum TrafficState {INIT, RED_GREEN, RED_YELLOW, GREEN_RED, YELLOW_RED};
static enum TrafficState traffic_state = INIT;

// Biến đếm ngược
int countdown1 = 0;
int countdown2 = 0;

void fsm_traffic_light(void) {
    switch (systemMode) {
        // Chế độ hoạt động bình thường
        case MODE_1_NORMAL:
            switch (traffic_state) {
                case INIT:
                    // Khởi tạo ban đầu: đèn 1 đỏ, đèn 2 xanh
                    set_traffic_light_1(1);
                    set_traffic_light_2(3);
                    countdown1 = time_red;
                    countdown2 = time_green;
                    display_7seg(countdown1, countdown2); // Chỉ cập nhật LED 7 đoạn ngay lúc khởi tạo
                    traffic_state = RED_GREEN;
                    setTimer(0, 1000); // Cài timer đếm ngược 1 giây cho index = 0
                    break;

                case RED_GREEN:
                    if (timer_flag[0] == 1) {
                        countdown1--;
                        countdown2--;
                        if (countdown2 <= 0) { // Đường số 2 đếm xong --> chuyển sang vàng
                            countdown2 = time_yellow;
                            set_traffic_light_2(2);
                            traffic_state = RED_YELLOW;
                        }
                        display_7seg(countdown1, countdown2); // Chỉ cập nhật LED mỗi 1 giây
                        setTimer(0, 1000);
                    }
                    break;

                case RED_YELLOW:
                    if (timer_flag[0] == 1) {
                        countdown1--;
                        countdown2--;
                        if (countdown2 <= 0) { // Cả 2 đường đếm xong: đường 1 --> xanh, đường 2 --> đỏ
                            countdown1 = time_green;
                            countdown2 = time_red;
                            set_traffic_light_1(3);
                            set_traffic_light_2(1);
                            traffic_state = GREEN_RED;
                        }
                        display_7seg(countdown1, countdown2); // Chỉ cập nhật LED mỗi 1 giây
                        setTimer(0, 1000);
                    }
                    break;

                case GREEN_RED:
                    if (timer_flag[0] == 1) {
                        countdown1--;
                        countdown2--;
                        if (countdown1 <= 0) { // Đường số 1 đếm xong --> đường số 1 thành vàng
                            countdown1 = time_yellow;
                            set_traffic_light_1(2);
                            traffic_state = YELLOW_RED;
                        }
                        display_7seg(countdown1, countdown2); // Chỉ cập nhật LED mỗi 1 giây
                        setTimer(0, 1000);
                    }
                    break;

                case YELLOW_RED:
                    if (timer_flag[0] == 1) {
                        countdown1--;
                        countdown2--;
                        if (countdown1 <= 0) { // Cả 2 đường đếm xong: đường 1 --> đỏ, đường 2 --> xanh
                            countdown1 = time_red;
                            countdown2 = time_green;
                            set_traffic_light_1(1);
                            set_traffic_light_2(3);
                            traffic_state = RED_GREEN;
                        }
                        display_7seg(countdown1, countdown2); // Chỉ cập nhật LED mỗi 1 giây
                        setTimer(0, 1000);
                    }
                    break;
            }
            break;

        // Chế độ điều chỉnh thời gian cho RED
        case MODE_2_RED:
            traffic_state = INIT; // Đặt lại state để khi thoát về Mode 1 sẽ chạy từ đầu
            display_7seg(systemMode, temp_duration);

            if (timer_flag[1] == 1) {
                HAL_GPIO_TogglePin(GPIOA, RED1_Pin | RED2_Pin);
                setTimer(1, 250);
            }
            break;

        // Chế độ điều chỉnh thời gian cho YELLOW
        case MODE_3_YELLOW:
            traffic_state = INIT;
            display_7seg(systemMode, temp_duration);

            if (timer_flag[1] == 1) {
                HAL_GPIO_TogglePin(GPIOA, YELLOW1_Pin | YELLOW2_Pin);
                setTimer(1, 250);
            }
            break;

        // Chế độ điều chỉnh thời gian cho GREEN
        case MODE_4_GREEN:
            traffic_state = INIT;
            display_7seg(systemMode, temp_duration);

            if (timer_flag[1] == 1) {
                HAL_GPIO_TogglePin(GPIOA, GREEN1_Pin | GREEN2_Pin);
                setTimer(1, 250);
            }
            break;
    }
}
