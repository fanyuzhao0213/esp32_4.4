#ifndef __BILIBILI_H_
#define __BILIBILI_H_
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
#include "string.h"


// #define BILI_API_URL "https://api.bilibili.com/x/space/acc/info?mid=400000973" // 替换为实际BVID
#define BILI_API_URL "https://api.bilibili.com/x/relation/stat?vmid=400000973&jsonp=jsonp" // 替换为实际BVID
#define BILI_API1_URL "https://api.bilibili.com/x/space/upstat?mid=400000973"

// 用户数据结构体（全部改为字符串存储）
typedef struct {
    char mid[20];        // 用户ID（字符串形式）
    char following[10];  // 关注数
    char whisper[10];    // 悄悄关注
    char black[10];      // 黑名单数
    char follower[10];   // 粉丝数
} BiliUserInfo;

extern BiliUserInfo current_user; // 全局存储用户数据
void print_user_info();
extern int g_GetBiliBili_Info_Flag;

extern void bilibili_task(void *pvParameters);
extern void fetch_bilibili_info_task(void *pvParameters);
#endif