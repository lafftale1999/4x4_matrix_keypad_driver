#ifndef _4X4_MATRIX_KEYPAD_DRIVER_H_
#define _4X4_MATRIX_KEYPAD_DRIVER_H_

#define _4X4_MATRIX_KEYPAD_COLUMNS          4
#define _4X4_MATRIX_KEYPAD_ROWS             4

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

void _4x4_matrix_scan_keys(char* buf, uint8_t buf_len);
uint8_t _4x4_matrix_init();
char _4x4_matrix_get_key_press();

#endif