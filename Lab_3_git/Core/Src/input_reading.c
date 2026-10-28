#include "main.h"
#include "timer.h"         // Thêm để lấy hằng số TICK
#include "input_reading.h" // Thêm để đồng bộ prototype

#define NO_OF_BUTTONS 3

// Tính số chu kỳ tự động dựa theo TICK (1000ms = 1s, 250ms = 0.25s)
#define DURATION_FOR_AUTO_INCREASING (1000 / TICK)


#define BUTTON_IS_PRESSED  GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET

// Mảng ánh xạ các chân GPIO tương ứng với 3 button (PA8, PA9, PA10)
static uint16_t button_pins[NO_OF_BUTTONS] = {GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10};
static GPIO_TypeDef* button_ports[NO_OF_BUTTONS] = {GPIOA, GPIOA, GPIOA};

// Bộ đệm lưu trạng thái cuối cùng sau khi debouncing
static GPIO_PinState buttonBuffer[NO_OF_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};

// Định nghĩa 2 bộ đệm để debouncing
static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};

// Cờ ghi nhận sự kiện nhấn nút > 1s
static uint8_t flagForButtonPress1s[NO_OF_BUTTONS] = {0, 0, 0};

// Bộ đếm cho sự kiện nhấn giữ > 1s
static uint16_t counterForButtonPress1s[NO_OF_BUTTONS] = {0, 0, 0};

void button_reading(void) {
    for (int i = 0; i < NO_OF_BUTTONS; i++) {
        debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
        debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(button_ports[i], button_pins[i]);

        if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i]) {
            if (buttonBuffer[i] != debounceButtonBuffer1[i]) {
                buttonBuffer[i] = debounceButtonBuffer1[i];

                if (buttonBuffer[i] == BUTTON_IS_PRESSED) {
                    counterForButtonPress1s[i] = 0;
                }
            }

            if (buttonBuffer[i] == BUTTON_IS_PRESSED) {
                if (counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING) {
                    counterForButtonPress1s[i]++;
                } else {
                    flagForButtonPress1s[i] = 1;
                }
            } else {
                counterForButtonPress1s[i] = 0;
                flagForButtonPress1s[i] = 0;
            }
        }
    }
}

// Hàm kiểm tra trạng thái vật lý của nút nhấn (đã qua chống rung)
unsigned char is_button_pressed(uint8_t index) {
    if (index >= NO_OF_BUTTONS) return 0;

    if (buttonBuffer[index] == BUTTON_IS_PRESSED) {
        return 1;
    }
    return 0;
}

// Hàm kiểm tra xem 1 nút cụ thể đã được nhấn giữ >= 1s hay chưa
unsigned char is_button_pressed_1s(uint8_t index) {
    if (index >= NO_OF_BUTTONS) return 0; // Đổi từ 0xff sang 0 để an toàn
    if (flagForButtonPress1s[index] == 1) {
        flagForButtonPress1s[index] = 0;  // Xóa cờ sau khi xử lý vòng lặp tự động tăng
        return 1;
    }
    return 0;
}
