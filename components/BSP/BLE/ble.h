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
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define DEVICE_NAME "FYZ_ESP_BLE"
// 在全局变量区添加目标MAC定义
extern uint8_t TARGET_MAC[6]; // 替换为实际目标MAC
extern char TARGET_NAME[];// 设置要连接的设备名称

#define CONNECT_USE_NAME_MAC                1           //1:mac2:name

#define PROFILE_NUM 1
#define PROFILE_APP_IDX 0
#define ESP_APP_ID 0x55
#define SERVICE_UUID 0x00FF
#define CHARACTERISTIC_UUID 0xFF01
#define GATTS_NUM_HANDLE 4




#define BLE_MTU_SEND_SIZE     20

extern esp_ble_scan_params_t ble_scan_params;

void esp_gap_cb(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);
// 初始化BLE
void my_ble_init(void);
void my_server_init(void);
void my_client_init(void);
void my_ble_c_send_data(uint8_t* data, uint16_t len);
#endif // BLE_H

