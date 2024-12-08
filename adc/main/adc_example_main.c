/* adc example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_log.h"
#include "driver/gpio.h"

static const char *TAG = "adc example";

static void adc_task()
{
    int x;
    uint16_t adc_data[100];

    float voltage=0.0f;

    while (1)
    {
        if (ESP_OK == adc_read(&adc_data[0]))
        {
        	voltage = ((float)adc_data[0])/1023.0f;

//        	uint16_t  i_vol = voltage*1000)

        	ESP_LOGI(TAG,"voltage =%d mV",(uint16_t)(voltage *1000));

            ESP_LOGI(TAG, "adc read: %d\r\n", adc_data[0]);
        }

//        ESP_LOGI(TAG, "adc read fast:\r\n");
//
//        if (ESP_OK == adc_read_fast(adc_data, 100)) {
//            for (x = 0; x < 100; x++) {
//                printf("%d--", adc_data[x]);
//            }

            printf("\r\n");
//        }

        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

void app_main()
{
    // 1. init adc
    adc_config_t adc_config;

    // Depend on menuconfig->Component config->PHY->vdd33_const value
    // When measuring system voltage(ADC_READ_VDD_MODE), vdd33_const must be set to 255.
//    adc_config.mode = ADC_READ_TOUT_MODE;
    adc_config.mode = ADC_READ_TOUT_MODE;
    adc_config.clk_div = 32; // ADC sample collection clock = 80MHz/clk_div = 10MHz
    ESP_ERROR_CHECK(adc_init(&adc_config));


    gpio_config_t my_io;

    my_io.mode = GPIO_MODE_OUTPUT;
    my_io.pin_bit_mask = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;


    my_io.pull_down_en = GPIO_PULLDOWN_DISABLE;
    my_io.pull_up_en = GPIO_PULLUP_ENABLE;
    my_io.intr_type =GPIO_PULLDOWN_DISABLE;

    gpio_config(&my_io);

    gpio_set_level(GPIO_NUM_12,0);
    gpio_set_level(GPIO_NUM_13,0);
    gpio_set_level(GPIO_NUM_14,0);

    // 2. Create a adc task to read adc value
    xTaskCreate(adc_task, "adc_task", 1024, NULL, 5, NULL);
}
