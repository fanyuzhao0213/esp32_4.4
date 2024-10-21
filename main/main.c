#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_chip_info.h"
#include "esp_timer.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_demos.h"
#include "wifi_ap.h"
#include "wifi_smartconfig.h"
#include "freertos/event_groups.h"
#include "weather.h"
#include "simple_wifi_sta.h"
#include  "mqtt.h"

/*********************
 *      DEFINES
 *********************/
#define LVGL_TASK_STACK_SIZE   (4 * 1024)   // 定义LVGL任务的堆栈大小（字节）
#define LVGL_TASK_PRIORITY     6            // 定义LVGL任务的优先级
#define LV_TICK_PERIOD_MS      1           // 心跳周期为1ms

EventGroupHandle_t g_event_group;        /* 定义事件组 */

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_tick_task(void *arg);
static void lvgl_task(void *arg);
static void print_chip_info(void);

/**********************
 *   STATIC FUNCTIONS
 **********************/

// 定时器任务，周期性增加LVGL的时钟计数
static void lv_tick_task(void *arg)
{
    (void)arg;
    lv_tick_inc(LV_TICK_PERIOD_MS);
}

// 打印板子信息和重启原因
static void print_chip_info(void)
{
    esp_chip_info_t chip_info;
    esp_err_t ret;
    uint32_t flash_size;

    ret = nvs_flash_init();                                         /* 初始化NVS */

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    esp_flash_get_size(NULL, &flash_size);                          /* 获取FLASH大小 */

    esp_chip_info(&chip_info);
    printf("内核:cup数量%d\n",chip_info.cores);                     /* 获取CPU内核数并显示 */
    printf("FLASH size: %u MB flash\n", flash_size / (1024 * 1024)); // 显示FLASH大小


    esp_chip_info(&chip_info);
    printf("芯片信息: %d CPU核, WiFi%s%s, 修订版 %d\n", chip_info.cores,
        (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
        (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "",
        chip_info.revision);

    printf("闪存: %dMB %s\n", spi_flash_get_chip_size() / (1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "嵌入式" : "外部");

    esp_reset_reason_t reset_reason = esp_reset_reason();
    printf("重启原因: %d\n", reset_reason);
}

//WIFI 任务
void wifi_init(void)
{
    //创建事件标志组
    g_event_group = xEventGroupCreate();
    wifi_sta_init();                         //wifi STA工作模式初始化
    //wifi_init_softap();                       //wifi softAP工作模式初始化
    // 启动任务来监控Wi-Fi连接和智能配网状态
    // wifi_smartconfig_sta();

    // 等待 WIFI_CONNECT_BIT 都被设置
    EventBits_t bits = xEventGroupWaitBits( g_event_group, WIFI_CONNECT_BIT, // 等待的标志
                                            pdTRUE,        // 等待之后自动清除标志
                                            pdTRUE,        // 等待所有标志
                                            portMAX_DELAY  // 永久等待
                                            );
    if(bits & WIFI_CONNECT_BIT)
    {
        //获取weather 任务启动
        //start http  task
        mqtt_start();
		xTaskCreate(http_client_task, "http_client", 5120, NULL, 3, NULL);
    }
}

// LVGL任务，处理GUI更新
static void lvgl_task(void *arg)
{
    printf("LVGL任务启动,核心: %d\n", xPortGetCoreID());

    lv_init();                             // 初始化LVGL
    lv_port_disp_init();                   // 初始化显示器
    lv_port_indev_init();                  // 初始化触摸屏

    // 创建周期性定时器以调用lv_tick_inc
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "periodic_gui"
    };
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));

    printf("LVGL与定时器初始化完成\n");

    // 加载LVGL widgets示例
    lv_demo_widgets();
    printf("LVGL Widgets demo加载完成\n");

    // LVGL任务循环
    while (1)
    {
        lv_task_handler();                 // 处理LVGL任务
        vTaskDelay(pdMS_TO_TICKS(5));     // 延时10ms
    }
}

/**********************
 *   APPLICATION MAIN
 **********************/

void app_main(void)
{
    // 打印芯片信息和重启原因
    print_chip_info();
    wifi_init();
    // 创建LVGL任务
    // xTaskCreatePinnedToCore(lvgl_task, "LVGL_Task", LVGL_TASK_STACK_SIZE, NULL, LVGL_TASK_PRIORITY, NULL, 0);
}
