#include <stdio.h>
#include "4x4_matrix.h"
#include "esp_log.h"
#include "esp_err.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

const char* TAG = "MAIN";

char buf[5];

void app_main(void)
{
    vTaskDelay(pdMS_TO_TICKS(5000));

    _4x4_matrix_init();

    while(true) {
        ESP_LOGI(TAG, "ENTER CODE:");

        _4x4_matrix_scan_keys(buf, 5);

        ESP_LOGI(TAG, "%s", buf);

        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}