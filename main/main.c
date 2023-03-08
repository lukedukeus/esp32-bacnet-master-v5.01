
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "server.h"
void task_server(void *pvParam);
void app_main(void);
esp_err_t event_handler(void *ctx, system_event_t *event);

static const char *TAG = "ringlight";
/* FreeRTOS event group to signal when we are connected*/
static int flag = -1;

esp_err_t event_handler(void *ctx, system_event_t *event);
esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id) {
        case SYSTEM_EVENT_STA_START:
            esp_wifi_connect();
			
            break;
        case SYSTEM_EVENT_STA_GOT_IP:
            ESP_LOGI(TAG, "got ip:%s",
                     ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
            flag = 0;
            break;

        case SYSTEM_EVENT_STA_DISCONNECTED:
            esp_wifi_connect();
			ESP_LOGI(TAG,"wifi disconnect");
            break;
        default:
            break;
    }
    return ESP_OK;
}

void app_main(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
	
    tcpip_adapter_init();
    ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    wifi_config_t sta_config = {
        .sta = {
            .ssid = "SSID",
            .password = "PASSWORD",
            .bssid_set = false
        }
    };
    ESP_ERROR_CHECK( esp_wifi_set_config(WIFI_IF_STA, &sta_config) );
    ESP_ERROR_CHECK( esp_wifi_start() );
    ESP_LOGI(TAG, "wifi_init_sta finished.");
	
	xTaskCreate(task_server,"bacnet_server", 6000, NULL, 1, NULL);
	
}

void task_server(void *pvParam)
{
	 	while(flag != 0)
	{
		vTaskDelay(1000 / portTICK_PERIOD_MS);
		ESP_LOGI(TAG, "server wait");
	}
	server(200004);
}
