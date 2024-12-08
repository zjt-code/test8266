/* pwm example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "esp_log.h"
#include "esp_system.h"
#include "esp_err.h"

#include "esp8266/gpio_register.h"
#include "esp8266/pin_mux_register.h"

#include "driver/pwm.h"
#include "driver/gpio.h"


#define PWM_0_OUT_IO_NUM   12
#define PWM_1_OUT_IO_NUM   13
#define PWM_2_OUT_IO_NUM   14
#define PWM_3_OUT_IO_NUM   15

// PWM period 1000us(1Khz), same as depth
#define PWM_PERIOD    (1000)

static const char *TAG = "pwm_example";

// pwm pin number
const uint32_t pin_num[4] = {
    PWM_0_OUT_IO_NUM,
    PWM_1_OUT_IO_NUM,
    PWM_2_OUT_IO_NUM,
    PWM_3_OUT_IO_NUM
};

// duties table, real_duty = duties[x]/PERIOD
uint32_t duties[4] = {
    500, 500, 500, 500,
};

// phase table, delay = (phase[x]/360)*PERIOD
float phase[4] = {
    0, 0, 90.0, -90.0,
};

void app_main()
{

    gpio_config_t my_io;

    my_io.mode = GPIO_MODE_OUTPUT;
    my_io.pin_bit_mask = GPIO_Pin_13|GPIO_Pin_14;


    my_io.pull_down_en = GPIO_PULLDOWN_DISABLE;
    my_io.pull_up_en = GPIO_PULLUP_ENABLE;
    my_io.intr_type =GPIO_PULLDOWN_DISABLE;

    gpio_config(&my_io);

  //  gpio_set_level(GPIO_NUM_12,0);
    gpio_set_level(GPIO_NUM_13,0);
    gpio_set_level(GPIO_NUM_14,0);


    pwm_init(PWM_PERIOD, duties, 1, pin_num);
    pwm_set_phases(phase);
    pwm_start();
    int16_t count = 0;

    int16_t loop =1;

    while (1) {
        if (count == 5) {
            // channel0, 1 output hight level.
            // channel2, 3 output low level.
            pwm_stop(0x0);
            pwm_deinit();

            ESP_LOGI(TAG, "PWM stop\n");
        } else if (count == 10) {

        	if(loop >10)loop =1;

        	duties[0] =loop*100;
        	loop++;
        	pwm_init(PWM_PERIOD, duties, 1, pin_num);
        	pwm_set_phases(phase);
            pwm_start();
            ESP_LOGI(TAG, "PWM re-start\n");
            count = 0;
        }

        count++;
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

