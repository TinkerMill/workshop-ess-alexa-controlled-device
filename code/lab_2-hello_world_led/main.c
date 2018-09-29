/* Blinky!!!!

    This code verifies that the LED is properly connected,
    and that PlatformIO is properly setup to compile, flash,
    and monitor the status of the MCU.

*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"

#define LED_GPIO    13


void app_main()
{
    printf("Hello world!\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    /* Set GPIO for use */
    gpio_pad_select_gpio(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    gpio_set_level(LED_GPIO, 1);
    /* Toggle the LED on and off during the countdown */

    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        if (( i % 2) == 0) {
            printf("Turning OFF LED\n");
            gpio_set_level(LED_GPIO, 0);
        }
        else {
            printf("Turning ON LED\n");
            gpio_set_level(LED_GPIO, 1);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    /* Finish by turning off the LED */
    gpio_set_level(LED_GPIO, 0);
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
}