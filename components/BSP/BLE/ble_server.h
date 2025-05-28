#ifndef BLE_SERVER_H
#define BLE_SERVER_H

#include "ble_common.h"

// 添加在文件头部
#define GATTS_DEMO_CHAR_VAL_LEN 20
static const uint16_t primary_service_uuid = ESP_GATT_UUID_PRI_SERVICE;
static const uint16_t characteristic_uuid = ESP_GATT_UUID_CHAR_DECLARE;
static const uint16_t descr_uuid = ESP_GATT_UUID_CHAR_CLIENT_CONFIG;
static uint8_t descr_value[2] = {0};


// 初始化GATT服务
esp_err_t ble_gatt_server_init(void);
// 发送数据
esp_err_t ble_gatt_server_send_data(uint16_t conn_id, uint8_t *data, uint16_t len);
// 断开连接
void ble_gatt_server_disconnect(uint16_t conn_id);
// 获取连接信息
ble_conn_info_t *ble_gatt_server_get_conn_info(void);
void ble_start_advertising(void);
#endif