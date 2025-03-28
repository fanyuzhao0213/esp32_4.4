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
#include "bilibili.h"
#include "simple_wifi_sta.h"
#include  "mqtt.h"
#include "iic.h"
#include "QMI8658.h"
#include "rtc.h"
#include "SD_MMC.h"
#include "esp_spiffs.h"
#include "esp_vfs.h"
#include "nvs_flash.h"
#include "my_gui.h"
#include "lv_fs_if/lv_fs_if.h"


// 创建信号量
SemaphoreHandle_t systerminit_semaphore;

uint8_t lvgl_systerm_ready_flag = 0;

#define DEFAULT_FD_NUM          5
#define DEFAULT_MOUNT_POINT     "/spiffs"
#define WRITE_DATA              "I have a daughter, and her name is Fan Hexi.\r\n"
static const char               *TAG = "spiffs";
/*********************
 *      DEFINES
 *********************/
#define LVGL_TASK_STACK_SIZE   (4 * 1024)   // 定义LVGL任务的堆栈大小（字节）
#define LVGL_TASK_PRIORITY     3            // 定义LVGL任务的优先级
#define LV_TICK_PERIOD_MS      1           // 心跳周期为1ms

EventGroupHandle_t g_event_group;        /* 定义事件组 */

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_tick_task(void *arg);
static void lvgl_task(void *arg);
static void print_chip_info(void);

/**
 * @brief       SPIFFS 初始化
 * @param       partition_label: 分区表的分区名称
 * @param       mount_point: 文件系统关联的文件路径前缀
 * @param       max_files: 可以同时打开的最大文件数
 * @retval      返回 ESP_OK 表示成功，否则返回错误码
 */
esp_err_t spiffs_init(char *partition_label, char *mount_point, size_t max_files)
{
    /* 配置 SPIFFS 文件系统的各个参数 */
    esp_vfs_spiffs_conf_t conf = {
        .base_path = mount_point,              // 挂载点路径
        .partition_label = partition_label,    // 分区标签
        .max_files = max_files,                // 最大打开文件数
        .format_if_mount_failed = true,        // 如果挂载失败，是否格式化分区
    };

    /* 使用上面定义的设置来初始化和挂载 SPIFFS 文件系统 */
    esp_err_t ret_val = esp_vfs_spiffs_register(&conf);

    /* 判断 SPIFFS 挂载及初始化是否成功 */
    if (ret_val != ESP_OK)
    {
        if (ret_val == ESP_FAIL)
        {
            printf("Failed to mount or format filesystem\n");  // 挂载或格式化失败
        }
        else if (ret_val == ESP_ERR_NOT_FOUND)
        {
            printf("Failed to find SPIFFS partition\n");       // 未找到 SPIFFS 分区
        }
        else
        {
            printf("Failed to initialize SPIFFS (%s)\n", esp_err_to_name(ret_val));  // 其他错误
        }

        return ESP_FAIL;  // 返回失败状态
    }

    /* 打印 SPIFFS 存储信息 */
    size_t total = 0, used = 0;
    ret_val = esp_spiffs_info(conf.partition_label, &total, &used);

    if (ret_val != ESP_OK)
    {
        ESP_LOGI(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret_val));  // 获取分区信息失败
    }
    else
    {
        ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);  // 打印分区总大小和已用大小
    }

    return ret_val;  // 返回初始化结果
}

/**
 * @brief       注销 SPIFFS 初始化
 * @param       partition_label：分区表标识
 * @retval      返回 ESP_OK 表示成功，否则返回错误码
 */
esp_err_t spiffs_deinit(char *partition_label)
{
    /* 注销并卸载 SPIFFS 文件系统 */
    return esp_vfs_spiffs_unregister(partition_label);
}

void list_spiffs_directory(const char *path)
{
    DIR *dir = opendir(path);  // 打开目录
    if (dir == NULL) {
        ESP_LOGE(TAG, "Failed to open directory: %s", path);
        return;
    }

    ESP_LOGI(TAG, "Listing directory: %s", path);

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {  // 遍历目录项
        char full_path[512];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(full_path, &st) == 0) {  // 获取文件/目录信息
            if (S_ISDIR(st.st_mode)) {
                ESP_LOGI(TAG, "DIR: %s", entry->d_name);  // 如果是目录
            } else {
                ESP_LOGI(TAG, "FILE: %s (size: %ld)", entry->d_name, st.st_size);  // 如果是文件
            }
        } else {
            ESP_LOGE(TAG, "Failed to stat: %s", entry->d_name);
        }
    }

    closedir(dir);  // 关闭目录
}

/**
 * @brief       测试 SPIFFS 文件系统
 * @param       无
 * @retval      无
 */
void spiffs_test(void)
{
    ESP_LOGI(TAG, "Opening file");

    /* 尝试以只读模式打开文件，检查文件是否存在 */
    FILE* f = fopen("/spiffs/hello.txt", "r");
    if (f == NULL)
    {
        /* 文件不存在，尝试创建并写入数据 */
        ESP_LOGI(TAG, "File does not exist, creating a new file...");
        f = fopen("/spiffs/hello.txt", "w");  // 以只写模式创建文件
        if (f == NULL)
        {
            ESP_LOGE(TAG, "Failed to create file for writing");  // 文件创建失败
            return;
        }

        /* 向新创建的文件中写入数据 */
        fprintf(f, WRITE_DATA);
        fclose(f);  // 关闭文件
        ESP_LOGI(TAG, "File created and data written");  // 文件创建并写入完成
    }
    else
    {
        /* 文件已存在，直接关闭文件 */
        fclose(f);
        ESP_LOGI(TAG, "File already exists");  // 文件已存在
    }

    /* 重命名之前检查目标文件是否存在 */
    struct stat st;
    if (stat("/spiffs/foo.txt", &st) == 0)  // 获取文件信息，成功返回 0
    {
        /* 如果目标文件存在，则删除它 */
        unlink("/spiffs/foo.txt");  // 删除文件
        ESP_LOGI(TAG, "Existing target file deleted");  // 目标文件已删除
    }

    /* 重命名创建的文件 */
    ESP_LOGI(TAG, "Renaming file");
    if (rename("/spiffs/hello.txt", "/spiffs/foo.txt") != 0)  // 重命名文件
    {
        ESP_LOGE(TAG, "Rename failed");  // 重命名失败
        return;
    }

    /* 打开重命名的文件并读取内容 */
    ESP_LOGI(TAG, "Reading file");
    f = fopen("/spiffs/foo.txt", "r");  // 以只读模式打开文件
    if (f == NULL)
    {
        ESP_LOGE(TAG, "Failed to open file for reading");  // 文件打开失败
        return;
    }

    char line[64];
    fgets(line, sizeof(line), f);  // 读取文件内容到 line 缓冲区
    fclose(f);  // 关闭文件

    char* pos = strchr(line, '\n');  // 查找换行符 '\n' 的位置
    if (pos)
    {
        *pos = '\0';  // 将换行符替换为字符串结束符 '\0'
    }

    ESP_LOGI(TAG, "Read from file: '%s'", line);  // 打印读取的文件内容
}

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
    printf("-------------esp32-s3----------------\r\n");
	printf("编译时间:%s %s\r\n", __DATE__, __TIME__);
	printf("esp32 sdk version :%s\r\n", esp_get_idf_version());
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
{    // 创建二进制信号量（推荐静态分配）
    systerminit_semaphore = xSemaphoreCreateBinary();
    if (systerminit_semaphore == NULL) {
        ESP_LOGE(TAG, "信号量创建失败");
    }else{
        ESP_LOGE(TAG, "信号量创建成功");
    }
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
        obtain_time();
        mqtt_start();
        // 创建LVGL任务
        xTaskCreatePinnedToCore(lvgl_task, "LVGL_Task", LVGL_TASK_STACK_SIZE, NULL, LVGL_TASK_PRIORITY, NULL, 0);
    }
}

// LVGL任务，处理GUI更新
static void lvgl_task(void *arg)
{
    printf("LVGL任务启动,核心: %d\n", xPortGetCoreID());
    /* 初始化SD卡 */
    SD_Init();
    lv_init();                             // 初始化LVGL
    lv_fs_if_init();
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
    printf("scr_act_height() %d\n",scr_act_height());
    printf("scr_act_width() %d\n",scr_act_width());
    printf("LVGL与定时器初始化完成\n");

    //实际lvgl调用这个函数
    lv_mainstart();
    printf("LVGL Widgets demo加载完成\n");
    // LVGL任务循环
    while (1)
    {
        lv_task_handler();                 // 处理LVGL任务
        vTaskDelay(pdMS_TO_TICKS(5));     // 延时10ms
    }
}

void my_spiffs_init(void)
{
    spiffs_init("storage", DEFAULT_MOUNT_POINT, DEFAULT_FD_NUM);    /* SPIFFS初始化 */
    spiffs_test();
    list_spiffs_directory("/spiffs");
    spiffs_deinit("storage");
}
/**********************
 *   APPLICATION MAIN
 **********************/

static const char *MAINTAG = "MAIN"; // 定义日志标签
i2c_obj_t i2c1_master;

void app_main(void)
{
    print_chip_info();                  // 打印芯片信息和重启原因
    my_spiffs_init();
    ESP_ERROR_CHECK(bsp_i2c_init());  // 初始化I2C总线
    ESP_LOGI(MAINTAG, "I2C initialized successfully"); // 输出I2C初始化成功的信息
    qmi8658_init(); // 初始化qmi8658芯片
    wifi_init();
    // xTaskCreatePinnedToCore(QMI8658_Task, "QMI8658_Task", 4096, NULL, 3, NULL, 0);
}


