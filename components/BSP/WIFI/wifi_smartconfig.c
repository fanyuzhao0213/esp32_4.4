#include "wifi_smartconfig.h"
#include "PCF85063.h"

uint32_t g_my_lvgl_year = 0;
uint32_t g_my_lvgl_month = 0;
uint32_t g_my_lvgl_day = 0;
uint8_t g_my_lvgl_hours = 0;
uint8_t g_my_lvgl_minutes = 0;
uint8_t g_my_lvgl_seconds = 0;
char *weekday_str = NULL;       // 获取星期几的字符串

/* 定义事件 */
static EventGroupHandle_t s_wifi_event_group;
static const int CONNECTED_BIT = BIT0;
static const int ESPTOUCH_DONE_BIT = BIT1;
static const char *TAG = "smartconfig_example";

/**
 * @brief       WIFI链接糊掉函数
 * @param       arg:传入网卡控制块
 * @param       event_base:WIFI事件
 * @param       event_id:事件ID
 * @param       event_data:事件数据
 * @retval      无
 */
static void event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        xTaskCreate(smartconfig_task, "smartconfig_task", 4096, NULL, 3, NULL);
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        esp_wifi_connect();
        xEventGroupClearBits(s_wifi_event_group, CONNECTED_BIT);
    }
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        xEventGroupSetBits(s_wifi_event_group, CONNECTED_BIT);


        ESP_LOGI(TAG,"get ip address");
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data; // 获取事件数据

        // 创建一个 char 数组来存储 IP 地址字符串
        char ip_str[16]; // 适合 IPv4 地址的缓冲区
        char netmask_str[16];
        char gateway_str[16];

        // 使用 esp_ip4addr_ntoa 函数获取并格式化 IP 地址
        ESP_LOGI(TAG, "got ip:%s", esp_ip4addr_ntoa(&event->ip_info.ip, ip_str, sizeof(ip_str))); // 打印 IP 地址
        ESP_LOGI(TAG, "netmask:%s", esp_ip4addr_ntoa(&event->ip_info.netmask, netmask_str, sizeof(netmask_str))); // 打印子网掩码
        ESP_LOGI(TAG, "gateway:%s", esp_ip4addr_ntoa(&event->ip_info.gw, gateway_str, sizeof(gateway_str))); // 打印网关地址
        xEventGroupSetBits(g_event_group, WIFI_CONNECT_BIT);

    }
    else if (event_base == SC_EVENT && event_id == SC_EVENT_SCAN_DONE)
    {
        ESP_LOGI(TAG, "Scan done");
    }
    else if (event_base == SC_EVENT && event_id == SC_EVENT_FOUND_CHANNEL)
    {
        ESP_LOGI(TAG, "Found channel");
    }
    /* 已获取SSID和密码,表示配网成功 */
    else if (event_base == SC_EVENT && event_id == SC_EVENT_GOT_SSID_PSWD)
    {
        ESP_LOGI(TAG, "Got SSID and password");

        smartconfig_event_got_ssid_pswd_t *evt = (smartconfig_event_got_ssid_pswd_t *)event_data;
        wifi_config_t wifi_config;
        uint8_t ssid[33] = { 0 };
        uint8_t password[65] = { 0 };
        uint8_t rvd_data[33] = { 0 };

        bzero(&wifi_config, sizeof(wifi_config_t));
        memcpy(wifi_config.sta.ssid, evt->ssid, sizeof(wifi_config.sta.ssid));
        memcpy(wifi_config.sta.password, evt->password, sizeof(wifi_config.sta.password));
        wifi_config.sta.bssid_set = evt->bssid_set;

        if (wifi_config.sta.bssid_set == true)
        {
            memcpy(wifi_config.sta.bssid, evt->bssid, sizeof(wifi_config.sta.bssid));
        }

        memcpy(ssid, evt->ssid, sizeof(evt->ssid));
        memcpy(password, evt->password, sizeof(evt->password));
        ESP_LOGI(TAG, "SSID:%s", ssid);
        ESP_LOGI(TAG, "PASSWORD:%s", password);

        /* 手机APPEspTouch软件使用ESPTOUCH V2模式，会执行以下代码 */
        if (evt->type == SC_TYPE_ESPTOUCH_V2)
        {
            ESP_ERROR_CHECK( esp_smartconfig_get_rvd_data(rvd_data, sizeof(rvd_data)) );
            ESP_LOGI(TAG, "RVD_DATA:");

            for (int i = 0; i < 33; i++)
            {
                printf("%02x ", rvd_data[i]);
            }

            printf("\n");
        }

        ESP_ERROR_CHECK( esp_wifi_disconnect() );
        ESP_ERROR_CHECK( esp_wifi_set_config(WIFI_IF_STA, &wifi_config) );
        esp_wifi_connect();
    }
    else if (event_base == SC_EVENT && event_id == SC_EVENT_SEND_ACK_DONE)
    {
        xEventGroupSetBits(s_wifi_event_group, ESPTOUCH_DONE_BIT);
    }
}

/**
 * @brief       WiFi一键配网
 * @param       无
 * @retval      无
 */
void wifi_smartconfig_sta(void)
{
    /* 初始化网卡 */
    ESP_ERROR_CHECK(esp_netif_init());
    /* 创建事件 */
    s_wifi_event_group = xEventGroupCreate();
    /* 使用默认配置初始化包括netif的Wi-Fi */
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    /* 把WIFI网卡设置为STA模式 */
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    assert(sta_netif);
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    /* WIFI初始化 */
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );

    /* 注册WIFI事件 */
    ESP_ERROR_CHECK( esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL) );
    ESP_ERROR_CHECK( esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL) );
    ESP_ERROR_CHECK( esp_event_handler_register(SC_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL) );

    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK( esp_wifi_start() );
}


void smartconfig_task(void *param)
{
    EventBits_t uxBits;
    /* 设置配网协议 */
    ESP_ERROR_CHECK( esp_smartconfig_set_type(SC_TYPE_ESPTOUCH) );
    /* 设置配网参数 */
    smartconfig_start_config_t cfg = SMARTCONFIG_START_CONFIG_DEFAULT();
    /* 开始配网 */
    ESP_ERROR_CHECK( esp_smartconfig_start(&cfg) );

    while (1)
    {
        // 等待事件组的位被置位 (CONNECTED_BIT 或 ESPTOUCH_DONE_BIT)
        uxBits = xEventGroupWaitBits(s_wifi_event_group, CONNECTED_BIT | ESPTOUCH_DONE_BIT, true, false, portMAX_DELAY);

        // 检查是否Wi-Fi已经连接
        if (uxBits & CONNECTED_BIT)
        {
            ESP_LOGI(TAG, "WiFi Connected to AP");
        }

        // 检查智能配网是否完成
        if (uxBits & ESPTOUCH_DONE_BIT)
        {
            ESP_LOGI(TAG, "Smartconfig done");
            esp_smartconfig_stop();  // 停止智能配网
            break;                   // 跳出循环，结束任务
        }
    }

    vTaskDelete(NULL);  // 删除当前任务
}

// 设置时区为中国标准时间
void set_timezone()
{
    // 设置为北京时间，UTC+8
    setenv("TZ", "CST-8", 1);
    tzset();
}

// 时间同步通知回调
void time_sync_notification_cb(struct timeval *tv)
{
    ESP_LOGI("NTP TIME", "Time has been synchronized");
}

// 初始化 SNTP
void initialize_sntp(void)
{
    // 检查是否已经启动 SNTP，如果是，则先停止
    if (sntp_enabled()) {
        sntp_stop();  // 停止已经运行的 SNTP 客户端
    }

    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");      // 默认服务器
    sntp_setservername(1, "time.google.com");   // 谷歌全球服务器（响应快）
    sntp_setservername(2, "time.nist.gov");     // 美国国家标准局服务器
    sntp_setservername(3, "ntp.aliyun.com");    // 阿里云国内服务器
    sntp_set_sync_mode(SNTP_SYNC_MODE_IMMED);   // 主动同步模式
    sntp_init();
    set_timezone();
}

// 获取并打印当前时间
void obtain_time(void)
{
    time_t now;
    struct tm timeinfo;
    char strftime_buf[64];
    uint8_t timeout_count =0;
    esp_err_t err;

    initialize_sntp();
    // 等待时间同步
    // while (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET)
    // {
    //     ESP_LOGI(TAG, "Waiting for system time to be set...");
    //     vTaskDelay(1000 / portTICK_PERIOD_MS);
    //     timeout_count++;
    //     if(timeout_count >=10)
    //     {
    //         xSemaphoreGive(systerminit_semaphore);
    //         ESP_LOGI(TAG, "信号量释放成功");
    //         timeout_count=0;
    //         return;
    //     }
    // }
    xSemaphoreGive(systerminit_semaphore);
    ESP_LOGI(TAG, "信号量释放成功");
    // 获取当前时间
    time(&now);
    localtime_r(&now, &timeinfo);

    // 格式化并打印时间
    strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
    ESP_LOGI(TAG, "The current date/time is: %s", strftime_buf);

    // 提取时间信息并设置到RTC
    datetime.hour = timeinfo.tm_hour;
    datetime.minute = timeinfo.tm_min;
    datetime.second= timeinfo.tm_sec;
    datetime.day  = timeinfo.tm_mday;
    datetime.month  = timeinfo.tm_mon + 1; // tm_mon 从0开始（0表示一月），因此需要+1
    datetime.year  = timeinfo.tm_year + 1900; // tm_year 是从1900年起算的，因此我们取最后两位表示年份
    datetime.dotw = timeinfo.tm_wday;
    // 打印提取出的时间信息
    ESP_LOGI(TAG, "准备同步到RTC的时间信息:");
    ESP_LOGI(TAG, "小时: %02d, 分钟: %02d, 秒: %02d", datetime.hour, datetime.minute, datetime.second);
    ESP_LOGI(TAG, "日期: %02d, 月份: %02d, 年份: %04d", datetime.day, datetime.month, datetime.year);
    ESP_LOGI(TAG, "星期: %d", datetime.dotw);
    // 调用RTC设置时间的函数
    PCF85063_Set_All(datetime);
}

// 星期几的字符串数组
const char *weekdays[] = {"星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"};
void sync_systime_to_mytime(void)
{
    time_t now;
    struct tm timeinfo;
    // 获取当前时间
    time(&now);
    localtime_r(&now, &timeinfo);

    // 提取时间信息并设置到RTC
    // 解析当前时间信息
    g_my_lvgl_year = timeinfo.tm_year + 1900;  // 将 tm_year 转换为标准年份
    g_my_lvgl_month = timeinfo.tm_mon + 1;     // 将 tm_mon 转换为标准月份
    g_my_lvgl_day = timeinfo.tm_mday;          // tm_mday 是当前日期（1-31）
    g_my_lvgl_hours = timeinfo.tm_hour;
    g_my_lvgl_minutes = timeinfo.tm_min;
    g_my_lvgl_seconds = timeinfo.tm_sec;
        // 解析星期几
    int weekday = timeinfo.tm_wday;  // tm_wday 的范围是 0（星期日）到 6（星期六）
    weekday_str = weekdays[weekday];  // 获取星期几的字符串


	// printf("LOOP 年:%4d, 月:%2d, 日:%2d, 小时: %02d, 分钟: %02d, 秒: %02d, 星期: %s\r\n",
    //        g_my_lvgl_year, g_my_lvgl_month, g_my_lvgl_day,
    //        g_my_lvgl_hours, g_my_lvgl_minutes, g_my_lvgl_seconds, weekday_str);
}
