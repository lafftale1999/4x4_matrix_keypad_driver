#include <stdio.h>
#include "pico/stdlib.h"

#include "4x4_matrix_keypad.h"

bool compare_authority(char* buf) {
    const char* code = "8321";
    uint8_t p_code = 0;

    uint8_t correct = 0;

    while(*buf != '\0' && (p_code < 4)) {
        if(*buf == code[p_code]) {
            correct++;
        }
        buf++;
        p_code++;
    }

    if(correct == 4) return true;
    
    return false;
    
}

int main()
{
    stdio_init_all();

    sleep_ms(5000);

    _4x4_matrix_init();

    while (true) {
        printf("Enter code: ");

        char string[5];
        _4x4_matrix_scan_keys(string, 5);

        printf("%s", (compare_authority(string) ? "WELCOME" : "Access denied..."));
        printf("\n");

        
        sleep_ms(1000);
    }
}
