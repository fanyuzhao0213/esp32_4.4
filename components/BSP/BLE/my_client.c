/* my_client.c - 仅实现BLE客户端 */
#include "ble.h"

static const char *TAG = "BLE_CLIENT";

// 处理扫描结果的回调函数
void esp_gap_cb(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    switch (event) {
        case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
            if (param->adv_start_cmpl.status == ESP_BT_STATUS_SUCCESS) {
                ESP_LOGI(TAG, "BLE广播已启动");
            } else {
                ESP_LOGE(TAG, "广播启动失败: %d", param->adv_start_cmpl.status);
            }
            break;

        case ESP_GAP_BLE_SCAN_RESULT_EVT: {
            uint8_t *adv_name = NULL;
            uint8_t adv_name_len = 0;
            uint8_t *raw_data = param->scan_rst.ble_adv;
            uint32_t raw_data_len = param->scan_rst.adv_data_len;

            switch (param->scan_rst.search_evt) {
                case ESP_GAP_SEARCH_INQ_RES_EVT: {
                    // 在设备地址打印后添加比对逻辑
                    if (memcmp(param->scan_rst.bda, TARGET_MAC, 6) == 0) {
                        ESP_LOGI(TAG, "发现目标设备，停止扫描");
                        esp_ble_gap_stop_scanning();
                        // 打印设备地址
                        ESP_LOGI(TAG, "设备地址: %02x:%02x:%02x:%02x:%02x:%02x",
                                param->scan_rst.bda[0], param->scan_rst.bda[1],
                                param->scan_rst.bda[2], param->scan_rst.bda[3],
                                param->scan_rst.bda[4], param->scan_rst.bda[5]);

                        // 打印RSSI
                        ESP_LOGI(TAG, "RSSI: %d", param->scan_rst.rssi);

                        // 解析并打印广播数据
                        if (raw_data_len > 0) {
                            ESP_LOGI(TAG, "原始数据(%d字节):", raw_data_len);
                            for (int i = 0; i < raw_data_len; i++) {
                                printf("%02x ", raw_data[i]);
                            }
                            printf("\n");
                        }

                        // 尝试获取设备名称
                        adv_name = esp_ble_resolve_adv_data(raw_data,
                                ESP_BLE_AD_TYPE_NAME_CMPL, &adv_name_len);
                        if (adv_name != NULL) {
                            ESP_LOGI(TAG, "设备名称: %.*s", adv_name_len, adv_name);
                        }
                            // 这里可以添加连接逻辑
                            break;
                        }

                    break;
                }
                default:
                    break;
            }
            break;
        }

        case ESP_GAP_BLE_SCAN_START_COMPLETE_EVT:
            if (param->scan_start_cmpl.status == ESP_BT_STATUS_SUCCESS) {
                ESP_LOGI(TAG, "扫描开始");
            }
            break;

        case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:
            if (param->adv_stop_cmpl.status == ESP_BT_STATUS_SUCCESS) {
                ESP_LOGI(TAG, "BLE广播已停止");
            }
            break;

        default:
            break;
    }
}






