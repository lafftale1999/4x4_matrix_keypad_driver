#include "4x4_matrix_keypad.h"

static char _4x4_matrix_layout[4][4] =
{
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

static uint8_t row_pins[] = {6, 7, 8, 9};
static uint8_t col_pins[] = {10, 11, 12, 13};

static char _4x4_matrix_wait_for_keypress() {
    while (1) {
        for (uint8_t row = 0; row < _4X4_MATRIX_KEYPAD_ROWS; row++) {
            gpio_put(row_pins[row], 1);
            sleep_ms(5);

            for (uint8_t col = 0; col < _4X4_MATRIX_KEYPAD_COLUMNS; col++) {
                if (gpio_get(col_pins[col]) != 0) {

                    while (gpio_get(col_pins[col]) != 0) {
                        sleep_ms(10);
                    }

                    gpio_put(row_pins[row], 0);

                    return _4x4_matrix_layout[row][col];
                }
            }

            gpio_put(row_pins[row], 0);
        }

        sleep_ms(5);
    }
}

void _4x4_matrix_scan_keys(char* buf, uint8_t buf_len) {
    uint8_t char_len = 0;

    while (char_len < buf_len - 1) {
        char key = _4x4_matrix_wait_for_keypress();
        printf("*");
        buf[char_len++] = key;
    }
    
    printf("\n");
    buf[char_len] = '\0';
}

char _4x4_matrix_get_key_press() {
    return _4x4_matrix_wait_for_keypress();
}

uint8_t _4x4_matrix_init() {
    
    for (uint8_t row = 0; row < _4X4_MATRIX_KEYPAD_ROWS; row++) {
        gpio_init(row_pins[row]);
        gpio_set_dir(row_pins[row], GPIO_OUT);
        gpio_put(row_pins[row], 0);
    }

    for (uint8_t col = 0; col < _4X4_MATRIX_KEYPAD_COLUMNS; col++) {
        gpio_init(col_pins[col]);
        gpio_set_dir(col_pins[col], GPIO_IN);
    }

    return 0;
}