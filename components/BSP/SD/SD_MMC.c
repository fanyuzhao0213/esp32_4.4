#include "SD_MMC.h"

#define EXAMPLE_MAX_CHAR_SIZE    64
#define MOUNT_POINT "/sdcard"

static const char *SD_TAG = "SD";

uint32_t Flash_Size = 0;
uint32_t SDCard_Size = 0;

// 写入文件
esp_err_t s_example_write_file(const char *path, char *data)
{
    ESP_LOGI(SD_TAG, "打开文件 %s", path);
    FILE *f = fopen(path, "w");
    if (f == NULL) {
        ESP_LOGE(SD_TAG, "打开文件失败");
        return ESP_FAIL;
    }
    fprintf(f, data);
    fclose(f);
    ESP_LOGI(SD_TAG, "文件写入成功");

    return ESP_OK;
}

// 读取文件
esp_err_t s_example_read_file(const char *path)
{
    ESP_LOGI(SD_TAG, "读取文件 %s", path);
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        ESP_LOGE(SD_TAG, "打开文件失败");
        return ESP_FAIL;
    }
    char line[EXAMPLE_MAX_CHAR_SIZE];
    fgets(line, sizeof(line), f);
    fclose(f);

    // 去除换行符
    char *pos = strchr(line, '\n');
    if (pos) {
        *pos = '\0';
    }
    ESP_LOGI(SD_TAG, "读取文件内容: '%s'", line);

    return ESP_OK;
}

bool is_mounted(const char* mount_point) {
    struct stat buffer;
    return (stat(mount_point, &buffer) == 0); // 如果挂载点存在，stat 返回 0
}

void check_sd_card_mount() {
    const char* mount_point = "/sdcard";
    if (is_mounted(mount_point)) {
        printf("SD 卡已正确挂载到 %s\n", mount_point);
    } else {
        printf("SD 卡未挂载到 %s\n", mount_point);
    }
}
// 初始化SD卡
void SD_Init(void)
{
    esp_err_t ret;

    // 挂载文件系统的配置
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = true,          // 挂载失败时格式化SD卡
        .max_files = 5,                          // 最大文件数
        .allocation_unit_size = 16 * 1024        // 分配单元大小
    };
    sdmmc_card_t *card;
    const char mount_point[] = MOUNT_POINT;
    ESP_LOGI(SD_TAG, "初始化SD卡");

    // 使用SPI外设
    sdmmc_host_t host = SDMMC_HOST_DEFAULT();

    // 配置SD卡槽
    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
    slot_config.width = 1;  // 1线模式

    slot_config.clk = CONFIG_EXAMPLE_PIN_CLK;
    slot_config.cmd = CONFIG_EXAMPLE_PIN_CMD;
    slot_config.d0 = CONFIG_EXAMPLE_PIN_D0;
    slot_config.d1 = CONFIG_EXAMPLE_PIN_D1;
    slot_config.d2 = CONFIG_EXAMPLE_PIN_D2;
    slot_config.d3 = CONFIG_EXAMPLE_PIN_D3;

    // 启用内部上拉电阻
    slot_config.flags |= SDMMC_SLOT_FLAG_INTERNAL_PULLUP;

    // 挂载文件系统
    ESP_LOGI(SD_TAG, "挂载文件系统");
    ret = esp_vfs_fat_sdmmc_mount(mount_point, &host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(SD_TAG, "挂载文件系统失败。如果需要格式化SD卡,请设置CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED选项。");
        } else {
            ESP_LOGE(SD_TAG, "初始化SD卡失败 (%s)。请确保SD卡线路已连接上拉电阻。", esp_err_to_name(ret));
        }
        return;
    }
    ESP_LOGI(SD_TAG, "文件系统挂载成功");

    // 打印SD卡信息
    sdmmc_card_print_info(stdout, card);
    SDCard_Size = ((uint64_t) card->csd.capacity) * card->csd.sector_size / (1024 * 1024);

    const char my_listpath[] =  "/sdcard/MY_IMAGE/WHITE";
    list_files_in_directory(MOUNT_POINT);
    list_files_in_directory(my_listpath);
}

// 列出 SD 卡中指定目录下的所有文件
void list_files_in_directory(const char *path)
{
    DIR *dir;
    struct dirent *entry;

    // 打开目录
    dir = opendir(path);
    if (dir == NULL) {
        ESP_LOGE(SD_TAG, "无法打开目录: %s", path);
        return;
    }

    ESP_LOGI(SD_TAG, "列出目录: %s", path);

    // 遍历目录中的每个条目
    while ((entry = readdir(dir)) != NULL) {
        // 打印文件或目录的名称
        if (entry->d_type == DT_REG) {  // 普通文件
            ESP_LOGI(SD_TAG, "文件: %s", entry->d_name);
        } else if (entry->d_type == DT_DIR) {  // 目录
            ESP_LOGI(SD_TAG, "目录: %s", entry->d_name);
        }
    }

    // 关闭目录
    closedir(dir);
}

// 获取Flash大小
void Flash_Searching(void)
{
    if(esp_flash_get_physical_size(NULL, &Flash_Size) == ESP_OK)
    {
        Flash_Size = Flash_Size / (uint32_t)(1024 * 1024);
        printf("Flash大小: %ld MB\n", Flash_Size);
    }
    else{
        printf("获取Flash大小失败\n");
    }
}

// 打开文件
FILE* Open_File(const char *file_path) {
    ESP_LOGI(SD_TAG, "尝试打开文件: %s", file_path);
    FILE *fp = fopen(file_path, "rb"); // 以二进制模式打开文件
    if (fp == NULL) {
        ESP_LOGE(SD_TAG, "打开文件 %s 失败。错误: %s", file_path, strerror(errno));
    }
    else
        printf("文件 %s 打开成功。 \r\n", file_path);
    return fp;
}

// 检索目录中指定扩展名的文件
uint16_t Folder_retrieval(const char* directory, const char* fileExtension, char File_Name[][MAX_FILE_NAME_SIZE], uint16_t maxFiles)
{
    DIR *dir = opendir(directory);  // 打开指定目录s
    if (dir == NULL) {
        ESP_LOGE(SD_TAG, "路径: <%s> 不存在", directory);
        return 0;
    }

    uint16_t fileCount = 0;  // 文件计数器
    struct dirent *entry;    // 目录条目指针

    // 遍历目录中的所有条目
    while ((entry = readdir(dir)) != NULL && fileCount < maxFiles) {
        // 跳过 "." 和 ".." 目录
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // 检查 entry->d_name 是否为空
        if (entry->d_name == NULL) {
            continue;
        }

        const char *dot = strrchr(entry->d_name, '.');
        if (dot != NULL && dot != entry->d_name) {
            if (strcasecmp(dot, fileExtension) == 0) {
                snprintf(File_Name[fileCount], MAX_FILE_NAME_SIZE, "%s", entry->d_name);

                // 拼接完整路径
                char filePath[MAX_PATH_SIZE];
                int path_len = snprintf(filePath, MAX_PATH_SIZE, "%s/%s", directory, entry->d_name);
                if (path_len >= MAX_PATH_SIZE) {
                    ESP_LOGW(SD_TAG, "路径过长，已截断: %s", filePath);
                }

                printf("找到文件: %s\r\n", filePath);
                fileCount++;
            }
        }
    }

    closedir(dir);  // 关闭目录

    if (fileCount > 0) {
        ESP_LOGI(SD_TAG, "检索到 %d 个扩展名为 '%s' 的文件", fileCount, fileExtension);
    } else {
        ESP_LOGW(SD_TAG, "目录 %s 中未找到扩展名为 '%s' 的文件", directory, fileExtension);
    }

    return fileCount;
}

