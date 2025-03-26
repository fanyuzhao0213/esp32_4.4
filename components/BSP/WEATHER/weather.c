#include <string.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "esp_http_client.h"
#include "cJSON.h"
#include "weather.h"
#include "wifi_smartconfig.h"

static const char *HTTP_TAG = "Weather";
#define MAX_HTTP_OUTPUT_BUFFER 1300
#define HOST "api.seniverse.com"
#define UserKey "SNJN8m1O95pkg2cEA"
#define Location "Xian"
#define Language "zh-Hans"
#define Strat "-1"
#define Days "5"

// 定义全局变量
char *City_Name = NULL;  // 用于存储 CITY 的 name
int daily_weather_count = 0;  // 实际获取到的天气信息数量
WeatherInfo daily_weather[MAX_DAYS];

static void freeBuffer(char* buf, int bufSize)
{
	for( int i = 0; i < bufSize; i ++ )
		buf[i] = NULL;
}

// 获取每日天气预报并保存到全局变量
void parse_weather_data(const char *json_data)
{
    if (json_data == NULL) {
        ESP_LOGE(HTTP_TAG, "Invalid JSON data");
        return;
    }

    // 解析 JSON 数据
    cJSON *root = cJSON_Parse(json_data);
    if (root == NULL) {
        ESP_LOGE(HTTP_TAG, "Failed to parse JSON data");
        return;
    }

    // 获取 "results" 数组
    cJSON *results = cJSON_GetObjectItem(root, "results");
    if (!cJSON_IsArray(results)) {
        ESP_LOGE(HTTP_TAG, "Invalid 'results' field in JSON");
        cJSON_Delete(root);
        return;
    }

    // 获取第一个结果（假设只有一个结果）
    cJSON *result = cJSON_GetArrayItem(results, 0);
    if (result == NULL) {
        ESP_LOGE(HTTP_TAG, "No result found in 'results' array");
        cJSON_Delete(root);
        return;
    }

// 获取 "location" 对象
    cJSON *location = cJSON_GetObjectItem(result, "location");
    if (location == NULL) {
        printf("Invalid 'location' field in JSON\n");
        cJSON_Delete(root);
        return;
    }

    // 获取 "name" 字段
    cJSON *name = cJSON_GetObjectItem(location, "name");
    if (cJSON_IsString(name)) {
        // 释放旧的全局变量内存（如果已分配）
        if (City_Name != NULL) {
            free(City_Name);
            City_Name = NULL;
        }

        // 分配内存并复制 name 的值
        City_Name = strdup(name->valuestring);
        if (City_Name == NULL) {
            printf("Failed to allocate memory for location name\n");
            cJSON_Delete(root);
            return;
        }

        printf("Location Name: %s\n", City_Name);
    } else {
        printf("Invalid 'name' field in JSON\n");
    }

    // 获取 "daily" 数组
    cJSON *daily = cJSON_GetObjectItem(result, "daily");
    if (!cJSON_IsArray(daily)) {
        ESP_LOGE(HTTP_TAG, "Invalid 'daily' field in JSON");
        cJSON_Delete(root);
        return;
    }

    // 遍历每日天气信息
    int daily_size = cJSON_GetArraySize(daily);
    daily_weather_count = (daily_size > MAX_DAYS) ? MAX_DAYS : daily_size;  // 限制保存的天数

    for (int j = 0; j < daily_weather_count; j++) {
        cJSON *day = cJSON_GetArrayItem(daily, j);
        if (day == NULL) {
            ESP_LOGE(HTTP_TAG, "Failed to get day %d from 'daily' array", j);
            continue;
        }

        // 解析并保存天气信息
        cJSON *item = NULL;

        // 解析日期
        item = cJSON_GetObjectItem(day, "date");
        if (cJSON_IsString(item)) {
            snprintf(daily_weather[j].date, sizeof(daily_weather[j].date), "%s", item->valuestring);
        } else {
            snprintf(daily_weather[j].date, sizeof(daily_weather[j].date), "N/A");
        }

        // 解析白天天气描述
        item = cJSON_GetObjectItem(day, "text_day");
        if (cJSON_IsString(item)) {
            snprintf(daily_weather[j].text_day, sizeof(daily_weather[j].text_day), "%s", item->valuestring);
        } else {
            snprintf(daily_weather[j].text_day, sizeof(daily_weather[j].text_day), "N/A");
        }

        // 解析夜间天气描述
        item = cJSON_GetObjectItem(day, "text_night");
        if (cJSON_IsString(item)) {
            snprintf(daily_weather[j].text_night, sizeof(daily_weather[j].text_night), "%s", item->valuestring);
        } else {
            snprintf(daily_weather[j].text_night, sizeof(daily_weather[j].text_night), "N/A");
        }

        // 解析白天气温
        item = cJSON_GetObjectItem(day, "high");
        if (cJSON_IsString(item)) {
            snprintf(daily_weather[j].high, sizeof(daily_weather[j].high), "%s", item->valuestring);
        } else {
            snprintf(daily_weather[j].high, sizeof(daily_weather[j].high), "N/A");
        }

        // 解析夜间气温
        item = cJSON_GetObjectItem(day, "low");
        if (cJSON_IsString(item)) {
            snprintf(daily_weather[j].low, sizeof(daily_weather[j].low), "%s", item->valuestring);
        } else {
            snprintf(daily_weather[j].low, sizeof(daily_weather[j].low), "N/A");
        }

        // 解析降水量
        item = cJSON_GetObjectItem(day, "rainfall");
        if (cJSON_IsString(item)) {
            snprintf(daily_weather[j].rainfall, sizeof(daily_weather[j].rainfall), "%s", item->valuestring);
        } else {
            snprintf(daily_weather[j].rainfall, sizeof(daily_weather[j].rainfall), "N/A");
        }

        // 解析湿度
        item = cJSON_GetObjectItem(day, "humidity");
        if (cJSON_IsString(item)) {
            snprintf(daily_weather[j].humidity, sizeof(daily_weather[j].humidity), "%s", item->valuestring);
        } else {
            snprintf(daily_weather[j].humidity, sizeof(daily_weather[j].humidity), "N/A");
        }

        // 解析风速
        item = cJSON_GetObjectItem(day, "wind_speed");
        if (cJSON_IsString(item)) {
            snprintf(daily_weather[j].wind_speed, sizeof(daily_weather[j].wind_speed), "%s", item->valuestring);
        } else {
            snprintf(daily_weather[j].wind_speed, sizeof(daily_weather[j].wind_speed), "N/A");
        }

        // 解析风向
        item = cJSON_GetObjectItem(day, "wind_direction");
        if (cJSON_IsString(item)) {
            snprintf(daily_weather[j].wind_direction, sizeof(daily_weather[j].wind_direction), "%s", item->valuestring);
        } else {
            snprintf(daily_weather[j].wind_direction, sizeof(daily_weather[j].wind_direction), "N/A");
        }

        // 解析降水概率 (precip)
        item = cJSON_GetObjectItem(day, "precip");
        if (cJSON_IsString(item)) {
            snprintf(daily_weather[j].precip, sizeof(daily_weather[j].precip), "%s", item->valuestring);
        } else {
            snprintf(daily_weather[j].precip, sizeof(daily_weather[j].precip), "N/A");
        }

        // 解析风力等级 (wind_scale)
        item = cJSON_GetObjectItem(day, "wind_scale");
        if (cJSON_IsString(item)) {
            snprintf(daily_weather[j].wind_scale, sizeof(daily_weather[j].wind_scale), "%s", item->valuestring);
        } else {
            snprintf(daily_weather[j].wind_scale, sizeof(daily_weather[j].wind_scale), "N/A");
        }

        // 解析白天天气code (code_day)
        item = cJSON_GetObjectItem(day, "code_day");
        if (cJSON_IsString(item)) {
            snprintf(daily_weather[j].code_day, sizeof(daily_weather[j].code_day), "%s", item->valuestring);
        } else {
            snprintf(daily_weather[j].code_day, sizeof(daily_weather[j].code_day), "N/A");
        }

        // 解析夜晚天气code (code_night)
        item = cJSON_GetObjectItem(day, "code_night");
        if (cJSON_IsString(item)) {
            snprintf(daily_weather[j].code_night, sizeof(daily_weather[j].code_night), "%s", item->valuestring);
        } else {
            snprintf(daily_weather[j].code_night, sizeof(daily_weather[j].code_night), "N/A");
        }

        // 打印解析的天气信息
        ESP_LOGI(HTTP_TAG,
            "Date: %s, Text Day: %s, Text Night: %s, High: %s, Low: %s, Rainfall: %s, Humidity: %s, "
            "Wind Speed: %s, Wind Direction: %s, Precip: %s, Wind Scale: %s, Code Day: %s, Code Night: %s",
            daily_weather[j].date,
            daily_weather[j].text_day,
            daily_weather[j].text_night,
            daily_weather[j].high,
            daily_weather[j].low,
            daily_weather[j].rainfall,
            daily_weather[j].humidity,
            daily_weather[j].wind_speed,
            daily_weather[j].wind_direction,
            daily_weather[j].precip,
            daily_weather[j].wind_scale,
            daily_weather[j].code_day,
            daily_weather[j].code_night
            );
        }
    // 释放 JSON 对象
    cJSON_Delete(root);
}

/** HTTP functions **/
void http_client_task(void *pvParameters)
{
    static uint16_t timecount =0;
    static uint16_t weather_update_flag = 1;
    int retry_count = 0;
    esp_err_t err;

    while(1)
    {
        if(weather_update_flag == 1)
        {
            weather_update_flag = 0;
            char output_buffer[MAX_HTTP_OUTPUT_BUFFER] = {0};   // Buffer to store response of http request
            int content_length = 0;
            static const char *URL = "http://"HOST"/v3/weather/daily.json?"	\
                                    "key="UserKey"&location="Location		\
                                    "&language="Language					\
                                    "&unit=c&start="Strat"&days="Days;
            esp_http_client_config_t config = {
                .url = URL,
            };
            esp_http_client_handle_t client = esp_http_client_init(&config);

            // GET Request
            esp_http_client_set_method(client, HTTP_METHOD_GET);

            //增加重试机制
            while (retry_count < 3) {
                err = esp_http_client_open(client, 0);
                if (err == ESP_OK)
                {
                    break;  // 请求成功，跳出重试循环
                }
                else
                {
                    retry_count++;
                    ESP_LOGE(HTTP_TAG, "Retrying... attempt %d", retry_count);
                    vTaskDelay(1000 / portTICK_PERIOD_MS);  // 等待 1 秒后重试
                }
            }

            if (err != ESP_OK) {
                ESP_LOGE(HTTP_TAG, "Failed to open HTTP connection: %s", esp_err_to_name(err));
            } else {
                content_length = esp_http_client_fetch_headers(client);
                if (content_length < 0) {
                    ESP_LOGE(HTTP_TAG, "HTTP client fetch headers failed");
                } else {
                    int data_read = esp_http_client_read_response(client, output_buffer, MAX_HTTP_OUTPUT_BUFFER);
                    if (data_read >= 0) {
                        ESP_LOGI(HTTP_TAG, "HTTP GET Status = %d, content_length = %d",
                        esp_http_client_get_status_code(client),
                        esp_http_client_get_content_length(client));
                        printf("data:%s", output_buffer);
                        parse_weather_data(output_buffer);
                        while(!lvgl_systerm_ready_flag)
                        {
                            vTaskDelay(1000);       //1S
                        }
                    } else {
                        ESP_LOGE(HTTP_TAG, "Failed to read response");
                    }
                }
            }
            esp_http_client_close(client);
            esp_http_client_cleanup(client);  // 释放 HTTP 客户端资源
        }
        timecount++;
        if(timecount >= WEATHER_UPDATE_TIME)
        {
            timecount = 0;
            weather_update_flag = 1;
            size_t free_heap = esp_get_free_heap_size();
            ESP_LOGI(HTTP_TAG,"Free heap size: %d bytes\n", free_heap);
        }
        vTaskDelay(1000);       //1S
    }
	vTaskDelete(NULL);
}
