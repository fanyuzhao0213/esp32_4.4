#pragma once

#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_vfs_fat.h"
#include "dirent.h"
#include "sdmmc_cmd.h"
#include "driver/sdmmc_host.h"
#include "esp_log.h"
#include <errno.h>
#include "esp_flash.h"

#define MAX_FILE_NAME_SIZE 256  // 定义文件名最大长度
#define MAX_PATH_SIZE 512      // 定义完整路径的最大长度

// 定义SD卡引脚配置
#define CONFIG_EXAMPLE_PIN_CLK  14  // SD卡时钟引脚
#define CONFIG_EXAMPLE_PIN_CMD  17  // SD卡命令引脚
#define CONFIG_EXAMPLE_PIN_D0   16  // SD卡数据线0引脚
#define CONFIG_EXAMPLE_PIN_D1   -1  // SD卡数据线1引脚（未使用）
#define CONFIG_EXAMPLE_PIN_D2   -1  // SD卡数据线2引脚（未使用）
#define CONFIG_EXAMPLE_PIN_D3   -1  // SD卡数据线3引脚（未使用）

#define CONFIG_SD_Card_D3       21  // SD卡D3引脚（用于某些特殊配置）

// 函数声明

/**
 * @brief 使能SD卡的片选信号
 * @return esp_err_t 返回操作结果（ESP_OK表示成功）
 */
esp_err_t SD_Card_CS_EN(void);

/**
 * @brief 禁用SD卡的片选信号
 * @return esp_err_t 返回操作结果（ESP_OK表示成功）
 */
esp_err_t SD_Card_CS_Dis(void);

/**
 * @brief 向指定路径的文件写入数据
 * @param path 文件路径
 * @param data 要写入的数据
 * @return esp_err_t 返回操作结果（ESP_OK表示成功）
 */
esp_err_t s_example_write_file(const char *path, char *data);

/**
 * @brief 从指定路径的文件读取数据
 * @param path 文件路径
 * @return esp_err_t 返回操作结果（ESP_OK表示成功）
 */
esp_err_t s_example_read_file(const char *path);

// 全局变量声明
extern uint32_t SDCard_Size;  // SD卡容量（单位：MB）
extern uint32_t Flash_Size;   // Flash容量（单位：MB）

/**
 * @brief 初始化SD卡
 */
void SD_Init(void);

/**
 * @brief 获取Flash大小并打印
 */
void Flash_Searching(void);

/**
 * @brief 打开指定路径的文件
 * @param file_path 文件路径
 * @return FILE* 返回文件指针，失败时返回NULL
 */
FILE* Open_File(const char *file_path);

/**
 * @brief 检索指定目录中特定扩展名的文件
 * @param directory 目录路径
 * @param fileExtension 文件扩展名（如".mp3"）
 * @param File_Name 存储文件名的二维数组
 * @param maxFiles 最大文件数量
 * @return uint16_t 返回找到的文件数量
 */
uint16_t Folder_retrieval(const char* directory, const char* fileExtension, char File_Name[][MAX_FILE_NAME_SIZE], uint16_t maxFiles);
void list_files_in_directory(const char *path);
void test_lvgl_fs();
void lv_fs_if_init(void);