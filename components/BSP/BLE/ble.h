#ifndef BLE_H
#define BLE_H

#include "string.h"
#include <stdint.h>
#include "esp_log.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_log.h"


#define DEVICE_NAME "FYZ_ESP_BLE"
// 在全局变量区添加目标MAC定义
static uint8_t TARGET_MAC[6] = {0xE5, 0xBA, 0xCC, 0xE8, 0x05, 0xCC}; // 替换为实际目标MAC

#define PROFILE_NUM 1
#define PROFILE_APP_IDX 0
#define ESP_APP_ID 0x55
#define SERVICE_UUID 0x00FF
#define CHARACTERISTIC_UUID 0xFF01
#define GATTS_NUM_HANDLE 4


void esp_gap_cb(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);
// 初始化BLE
void my_ble_init(void);
void my_server_init(void);

#endif // BLE_H

