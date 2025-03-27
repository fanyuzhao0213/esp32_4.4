#ifndef __WEATHER_H_
#define __WEATHER_H_
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
#include "wifi_smartconfig.h"

extern void http_client_task(void *pvParameters);
extern uint8_t lvgl_systerm_ready_flag;
// 定义天气信息结构体
typedef struct {
    char date[16];              // 日期 (例如: "2025-03-21")
    char text_day[32];          // 白天天气描述 (例如: "多云")
    char code_day[8];           // 白天天气代码 (例如: "4")
    char text_night[32];        // 夜间天气描述 (例如: "阴")
    char code_night[8];         // 夜间天气代码 (例如: "9")
    char high[8];               // 白天气温最高值 (例如: "21")
    char low[8];                // 夜间气温最低值 (例如: "6")
    char rainfall[8];           // 降水量 (例如: "0.00")
    char precip[8];             // 降水概率 (例如: "0.00")
    char wind_direction[32];    // 风向 (例如: "无持续风向")
    char wind_direction_degree[8]; // 风向角度 (例如: "" — 可选字段)
    char wind_speed[8];         // 风速 (例如: "8.4")
    char wind_scale[8];         // 风力等级 (例如: "2")
    char humidity[8];           // 湿度 (例如: "26")
} WeatherInfo;


// 全局变量，用于保存每日天气信息
#define MAX_DAYS 7  // 假设最多保存 7 天的天气信息
WeatherInfo daily_weather[MAX_DAYS];
extern char *City_Name;  // 用于存储 CITY 的 name

//更改更新weather的时间   默认为10min
#define WEATHER_UPDATE_TIME                 60*1           //单位1S
extern void http_client_task(void *pvParameters);
#endif