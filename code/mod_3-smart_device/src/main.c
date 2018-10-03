#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event_loop.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_log.h"
#include "mqtt_client.h"
#include "driver/gpio.h"

static const char *TAG = "SMART_DEVICE";

static EventGroupHandle_t wifi_event_group;
const static int CONNECTED_BIT = BIT0;


// **************** Set parameters here ******************
// GPIO Pin where LED resides
#define LED_GPIO                13

// Set WiFi credentials - CASE is important!
#define CONFIG_WIFI_SSID        "SSID Name Here"
#define CONFIG_WIFI_PASSWORD    "pre-Shared key here"

// Enter your CloudMQTT endpoint and credentials
#define MQTT_HOST               "FQDN"
#define MQTT_WEBSOCKET_PORT     "00000"
#define MQTT_USERNAME           "paste_here"
#define MQTT_PASSWORD           "paste_here"

// Build URI for websocket connection
#define MQTT_URI "wss://" MQTT_HOST ":" MQTT_WEBSOCKET_PORT "/ws"

// **************** Do NOT modify below ******************


static esp_err_t wifi_event_handler(void *ctx, system_event_t *event)
{
    switch (event->event_id) {
        case SYSTEM_EVENT_STA_START:
            esp_wifi_connect();
            break;
        case SYSTEM_EVENT_STA_GOT_IP:
            xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);

            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            esp_wifi_connect();
            xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
            break;
        default:
            break;
    }
    return ESP_OK;
}

static void wifi_init(void)
{
    tcpip_adapter_init();
    wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK(esp_event_loop_init(wifi_event_handler, NULL));
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = CONFIG_WIFI_SSID,
            .password = CONFIG_WIFI_PASSWORD,
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    ESP_LOGI(TAG, "start the WIFI SSID:[%s] password:[%s]", CONFIG_WIFI_SSID, "******");
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_LOGI(TAG, "Waiting for wifi");
    xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT, false, true, portMAX_DELAY);
}

extern const uint8_t mqtt_ca_pem_start[] asm("_binary_data_cloudmqtt_pem_start");
extern const uint8_t mqtt_ca_pem_end[]   asm("_binary_data_cloudmqtt_pem_end");

static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    const char s[2] = "=";
    char *token;
    char mqtt_topic[30];
    char mqtt_data[30];

    // your_context_t *context = event->context;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");

            // Setup subscription to "command" channel
            msg_id = esp_mqtt_client_subscribe(client, "command", 0);
            ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
            break;
        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            // example to publish up to MQTT broker - not used in this example
            // msg_id = esp_mqtt_client_publish(client, "tm", "data", 0, 0, 0);
            // ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            // process incoming data
            // first display topic and data received
            ESP_LOGI(TAG, "MQTT_EVENT_DATA");
            printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
            printf("DATA=%.*s\r\n", event->data_len, event->data);

            // look for topic command/sensor with data of 'on' or 'off',
            // then act on that sensor (turn it on or off)

            // copy and compare topic - looking for "command"
            strncpy(mqtt_topic, event->topic, event->topic_len);
            mqtt_topic[event->topic_len] = 0;
            if( strcmp(mqtt_topic, "command") == 0) {
                // parse data
                if( event->data_len < 10 ) {
                    strncpy(mqtt_data, event->data, event->data_len);
                    mqtt_data[event->data_len] = 0;
                }
                else {
                    printf("data too long for valid command. bypassing\r\n");
                    break;
                }
                // parse "key" of key value pair: sensor=off or sensor=on
                token = strtok(mqtt_data, s);
                if (token != NULL) {
                    // token points to sensor to act on
                    if (strcmp (token, "led") == 0) {
                        token = strtok(NULL, s);
                        printf("sensor: led, command: %s\r\n", token);
                        if (strcmp(token, "on") == 0) {
                            //turn on LED
                            printf("Turning LED ON\r\n");
                            gpio_set_level(LED_GPIO, 1);
                        }
                        else if (strcmp(token, "off") == 0) {
                            //turn off LED
                            printf("Turning LED OFF\r\n");
                            gpio_set_level(LED_GPIO, 0);
                        }
                    }
                    else {
                        printf("no sensor named %s found\r\n", token);
                    }
                }
            }
            else {
                // should not get here as only subscribed to monitored topic(s)
                printf("topic %s not expected\r\n", mqtt_topic);
            }

            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
            break;
    }
    return ESP_OK;
}

static void mqtt_app_start(void)
{
    const esp_mqtt_client_config_t mqtt_cfg = {
        .uri = MQTT_URI,
        .event_handle = mqtt_event_handler,
        .cert_pem = (const char *)mqtt_ca_pem_start,
        .username = MQTT_USERNAME,
        .password = MQTT_PASSWORD,
        .client_id = "smart_device",
    };

    ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);
}

void app_main()
{
    ESP_LOGI(TAG, "[APP] Startup..");
    ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());

    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("MQTT_CLIENT", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT_TCP", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT_SSL", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT", ESP_LOG_VERBOSE);
    esp_log_level_set("OUTBOX", ESP_LOG_VERBOSE);

    // Set the GPIO for the LED
    gpio_pad_select_gpio(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    nvs_flash_init();
    wifi_init();
    mqtt_app_start();
}