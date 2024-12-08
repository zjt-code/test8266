/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"
//#include ""


void app_main()
{
    printf("Hello world!\n");


    gpio_config_t gp_t;

    gp_t.mode = GPIO_MODE_OUTPUT;
    gp_t.intr_type =GPIO_INTR_DISABLE;
    gp_t.pin_bit_mask = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;
    gp_t.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&gp_t);

    gpio_set_level(GPIO_NUM_12,0);
    gpio_set_level(GPIO_NUM_13,0);
    gpio_set_level(GPIO_NUM_14,0);

    gpio_set_level(GPIO_NUM_12,1);



    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is ESP8266 chip with %d CPU cores, WiFi, ",     chip_info.cores);

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

//    for (int i = 10; i >= 0; i--) {
//        printf("Restarting in %d seconds...\n", i);
//        vTaskDelay(1000 / portTICK_PERIOD_MS);
//    }

    int i =0;

    while(1)
    {

			printf("%d seconds...\n",i);
			vTaskDelay(1000 / portTICK_PERIOD_MS);
			i++;
			gpio_set_level(GPIO_NUM_12,1);
			gpio_set_level(GPIO_NUM_13,0);
			gpio_set_level(GPIO_NUM_14,0);
			vTaskDelay(1000 / portTICK_PERIOD_MS);
			i++;
			gpio_set_level(GPIO_NUM_12,0);
			gpio_set_level(GPIO_NUM_13,1);
			gpio_set_level(GPIO_NUM_14,0);
			vTaskDelay(1000 / portTICK_PERIOD_MS);
							i++;
			gpio_set_level(GPIO_NUM_12,0);
			gpio_set_level(GPIO_NUM_13,0);
			gpio_set_level(GPIO_NUM_14,1);


    }
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
}
