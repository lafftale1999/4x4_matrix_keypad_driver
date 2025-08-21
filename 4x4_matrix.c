#include "include/4x4_matrix.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_err.h"
#include "esp_log.h"

static char _4x4_matrix_layout[4][4] =
{
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

static uint8_t row_pins[4] = {0};
static uint8_t col_pins[4] = {0};

static char _4x4_matrix_wait_for_keypress() {
    while (1) {
        for (uint8_t row = 0; row < _4X4_MATRIX_KEYPAD_ROWS; row++) {
            gpio_set_level(row_pins[row], 1);
            vTaskDelay(pdMS_TO_TICKS(10));

            for (uint8_t col = 0; col < _4X4_MATRIX_KEYPAD_COLUMNS; col++) {
                vTaskDelay(pdMS_TO_TICKS(10));
                if (gpio_get_level(col_pins[col]) != 0) {
                    while (gpio_get_level(col_pins[col]) != 0) {
                        vTaskDelay(pdMS_TO_TICKS(10));
                    }

                    gpio_set_level(row_pins[row], 0);

                    return _4x4_matrix_layout[row][col];
                }
            }

            gpio_set_level(row_pins[row], 0);
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void _4x4_matrix_scan_keys(char* buf, uint8_t buf_len) {
    uint8_t char_len = 0;

    while (char_len < buf_len - 1) {
        char key = _4x4_matrix_wait_for_keypress();
        buf[char_len++] = key;
    }
    
    buf[char_len] = '\0';
}

char _4x4_matrix_get_key_press() {
    return _4x4_matrix_wait_for_keypress();
}

/**
 * @param row_p array of ESP32 pins connected to rows
 * @param col_p array of ESP32 pins connected to columns
 * @return 0 for success.
 */
uint8_t _4x4_matrix_init(const uint8_t row_p[4], const uint8_t col_p[4]) {
    for (uint8_t row = 0; row < _4X4_MATRIX_KEYPAD_ROWS; row++) {
        row_pins[row] = row_p[row];

        const gpio_config_t pin = {
            .mode = GPIO_MODE_OUTPUT,
            .pin_bit_mask = (1ULL << row_pins[row]),
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .intr_type = GPIO_INTR_DISABLE
        };

        ESP_ERROR_CHECK(gpio_config(&pin));
        ESP_ERROR_CHECK(gpio_set_level(row_pins[row], 0));
    }


    for (uint8_t col = 0; col < _4X4_MATRIX_KEYPAD_COLUMNS; col++) {
        col_pins[col] = col_p[col];
        
        const gpio_config_t pin = {
            .mode = GPIO_MODE_INPUT,
            .pin_bit_mask = (1ULL << col_pins[col]),
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_ENABLE,
            .intr_type = GPIO_INTR_DISABLE
        };

        ESP_ERROR_CHECK(gpio_config(&pin));
    }

    return 0;
}