#include "led_display.h"

void display_7seg(int val1, int val2){
    // Lưu giá trị cũ để so sánh, tránh ghi đè GPIOB->ODR liên tục gây lag Proteus
    static int last_val1 = -1;
    static int last_val2 = -1;

    // Nếu cả 2 số không có gì thay đổi so với chu kỳ trước -> Thoát luôn!
    if (val1 == last_val1 && val2 == last_val2) return;

    last_val1 = val1;
    last_val2 = val2;

    uint8_t val1_tens = val1 / 10;
    uint8_t val1_units = val1 % 10;

    uint8_t val2_tens = val2 / 10;
    uint8_t val2_units = val2 % 10;

    // U2 (PB0-3): val1_tens | U3 (PB4-7): val1_units | U4 (PB8-11): val2_tens | U5 (PB12-15): val2_units
    uint16_t output_data = (val2_units << 12) | (val2_tens << 8) | (val1_units << 4) | val1_tens;

    GPIOB->ODR = output_data;
}

void turn_off_all_traffic_lights(void) {
    HAL_GPIO_WritePin(GPIOA, RED1_Pin|YELLOW1_Pin|GREEN1_Pin|RED2_Pin|YELLOW2_Pin|GREEN2_Pin, GPIO_PIN_RESET);
}


// Định nghĩa màu - đỏ 1 - vàng 2 - xanh 3
void set_traffic_light_1(int color) {
    HAL_GPIO_WritePin(GPIOA, RED1_Pin|YELLOW1_Pin|GREEN1_Pin, GPIO_PIN_RESET); // Tắt hết cột 1 trước
    if (color == 1) HAL_GPIO_WritePin(GPIOA, RED1_Pin, GPIO_PIN_SET);
    if (color == 2) HAL_GPIO_WritePin(GPIOA, YELLOW1_Pin, GPIO_PIN_SET);
    if (color == 3) HAL_GPIO_WritePin(GPIOA, GREEN1_Pin, GPIO_PIN_SET);
}

void set_traffic_light_2(int color) {
    HAL_GPIO_WritePin(GPIOA, RED2_Pin|YELLOW2_Pin|GREEN2_Pin, GPIO_PIN_RESET); // Tắt hết cột 2 trước
    if (color == 1) HAL_GPIO_WritePin(GPIOA, RED2_Pin, GPIO_PIN_SET);
    if (color == 2) HAL_GPIO_WritePin(GPIOA, YELLOW2_Pin, GPIO_PIN_SET);
    if (color == 3) HAL_GPIO_WritePin(GPIOA, GREEN2_Pin, GPIO_PIN_SET);
}
