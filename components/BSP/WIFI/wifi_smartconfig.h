#ifndef _wifi_smartconfig_H_
#define _wifi_smartconfig_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_smartconfig.h"
#include "esp_log.h"
#include "weather.h"
#include <time.h>
#include <sys/time.h>
#include "esp_sntp.h"

extern SemaphoreHandle_t systerminit_semaphore;

#define WIFI_CONNECT_BIT            BIT0
#define Timeout_GetWeather_BIT      BIT1
#define MQTT_CONNECT_BIT            BIT2

extern uint8_t g_my_lvgl_hours;
extern uint8_t g_my_lvgl_minutes;
extern uint8_t g_my_lvgl_seconds;
extern uint32_t g_my_lvgl_year;
extern uint32_t g_my_lvgl_month;
extern uint32_t g_my_lvgl_day;
extern char *weekday_str;  // 获取星期几的字符串
extern EventGroupHandle_t g_event_group;        /* 定义事件组 */

extern void wifi_smartconfig_sta(void);
extern void smartconfig_task(void *param);
extern void initialize_sntp(void);
extern void obtain_time(void);
extern void sync_systime_to_mytime(void);
#endif
