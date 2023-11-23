#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "client_task.h"
#include "led.h"

#include "config.h"
#include "address.h"
#include "bacdef.h"
#include "handlers.h"
#include "client.h"
#include "dlenv.h"
#include "bacdcode.h"
#include "npdu.h"
#include "apdu.h"
#include "iam.h"
#include "tsm.h"
#include "datalink.h"
#include "dcc.h"
#include "getevent.h"
#include "net.h"
#include "txbuf.h"
#include "version.h"
#include "device.h"
#include "bactext.h"


#define CLIENT_DEVICE_ID CONFIG_CLIENT_DEVICE_ID

static const char *TAG = "client";

unsigned timeout = 100; /* milliseconds */
time_t last_seconds = 0;
bool found = false;
static BACNET_ADDRESS Target_Address;
static uint8_t request_id = 0;
time_t elapsed_seconds = 0;
unsigned max_apdu = 0;
time_t timeout_seconds = 0;
time_t current_seconds = 0;
uint16_t pdu_len = 0;
BACNET_ADDRESS src = { 0 };


void client_task(void *arg)
{
    gpio_config_t input_config;
    input_config.intr_type = GPIO_INTR_DISABLE;
    input_config.mode = GPIO_MODE_INPUT;
    input_config.pin_bit_mask = (1ULL << GPIO_NUM_0);
    input_config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    input_config.pull_up_en = GPIO_PULLUP_ONLY;
    gpio_config(&input_config);

    last_seconds = time(NULL);
    timeout_seconds = (apdu_timeout() / 1000) * apdu_retries();
    /* try to bind with the device */
    found = address_bind_request(
        CLIENT_DEVICE_ID, &max_apdu, &Target_Address);
    if (!found) {
        Send_WhoIs(CLIENT_DEVICE_ID, CLIENT_DEVICE_ID);
    }

    while(true)
    {
        current_seconds = time(NULL);

        /* at least one second has passed */
        if (current_seconds != last_seconds) {
            tsm_timer_milliseconds((uint16_t)((current_seconds - last_seconds) * 1000));
        }

        /* wait until the device is bound, or timeout and quit */
        if (!found) {
            found = address_bind_request(
                CLIENT_DEVICE_ID, &max_apdu, &Target_Address);
        };


        if (found) {
            // send out a write property request
            int button_pressed = !gpio_get_level(CONFIG_BUTTON_GPIO);

            BACNET_APPLICATION_DATA_VALUE application_data = {
                .tag = BACNET_APPLICATION_TAG_REAL,
                .type.Real = button_pressed,
                .context_specific = false,
                .next = NULL
            };  

            ESP_LOGI(TAG, "Sending write property request");

            request_id = Send_Write_Property_Request(
                CLIENT_DEVICE_ID, // destination device id
                OBJECT_ANALOG_VALUE, // object type
                0, // object instance
                PROP_PRESENT_VALUE, // object property
                &application_data, // object value
                0, // priority
                BACNET_ARRAY_ALL // array index
            );

            if (request_id == 0) {
                ESP_LOGE(TAG, "Failed to send write property request");
            } else {
                ESP_LOGI(TAG, "Sent write property request with request id %d", request_id);
            }
        }
        else {
            elapsed_seconds += (current_seconds - last_seconds);
            if (elapsed_seconds > timeout_seconds) {
                ESP_LOGE(TAG, "APDU Timeout!");
            }
        }


        /* keep track of time for next check */
        last_seconds = current_seconds;

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}