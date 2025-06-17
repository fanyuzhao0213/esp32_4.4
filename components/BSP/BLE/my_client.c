/*
 * 简化版 BLE GATT 客户端示例
 * 基于 ESP-IDF 4.4.8 官方示例
 */

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "nvs.h"
#include "nvs_flash.h"

#include "esp_bt.h"
#include "esp_gap_ble_api.h"
#include "esp_gattc_api.h"
#include "esp_gatt_defs.h"
#include "esp_bt_main.h"
#include "esp_gatt_common_api.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "ble.h"

#define TAG "BLE_CLIENT"

// 自定义服务和特征UUID，需要与服务端匹配
// #define TARGET_SERVICE_UUID        0x00FF
// #define TARGET_CHARACTERISTIC_UUID 0xFF01
static const uint8_t TARGET_SERVICE_UUID_128[16] = {0x9E, 0xCA, 0xDC, 0x24, 0x0E, 0xE5, 0xA9, 0xE0, 0x93, 0xF3, 0xA3, 0xB5, 0x01, 0x00, 0x40, 0x6E};
// Nordic UART Service: 6E400001-B5A3-F393-E0A9-E50E24DCCA9E
//static const uint8_t TARGET_CHARACTERISTIC_UUID_128[16] = {0x9E, 0xCA, 0xDC, 0x24, 0x0E, 0xE5, 0xA9, 0xE0, 0x93, 0xF3, 0xA3, 0xB5, 0x02, 0x00, 0x40, 0x6E};

static bool connect = false;
// 全局状态标志
static bool write_pending = false;

// 存储服务和特征信息
static uint16_t service_start_handle = 0;
static uint16_t service_end_handle = 0;
static uint16_t char_handle = 0;
static esp_bd_addr_t remote_bda = {0};
static uint16_t conn_id = 0;
static esp_gatt_if_t gattc_if_value = 0;

// 扫描参数
esp_ble_scan_params_t ble_scan_params = {
    .scan_type              = BLE_SCAN_TYPE_ACTIVE,
    .own_addr_type          = BLE_ADDR_TYPE_PUBLIC,
    .scan_filter_policy     = BLE_SCAN_FILTER_ALLOW_ALL,
    .scan_interval          = 0x50,
    .scan_window            = 0x30,
    .scan_duplicate         = BLE_SCAN_DUPLICATE_DISABLE
};

// GAP 回调函数
void esp_gap_cb(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param) {
    switch (event) {
    case ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT:
        // 扫描参数设置完成，开始扫描
        //esp_ble_gap_start_scanning(30); // 扫描30秒
        break;

    case ESP_GAP_BLE_SCAN_START_COMPLETE_EVT:
        if (param->scan_start_cmpl.status != ESP_BT_STATUS_SUCCESS) {
            ESP_LOGE(TAG, "扫描启动失败, 错误状态 = %x", param->scan_start_cmpl.status);
            break;
        }
        ESP_LOGI(TAG, "扫描启动成功");
        break;

    case ESP_GAP_BLE_SCAN_RESULT_EVT: {
        esp_ble_gap_cb_param_t *scan_result = (esp_ble_gap_cb_param_t *)param;
        // 解析广播数据中的设备名称
        uint8_t adv_name_len = 0;
        uint8_t *adv_name = esp_ble_resolve_adv_data(scan_result->scan_rst.ble_adv,
                                                ESP_BLE_AD_TYPE_NAME_CMPL, &adv_name_len);
        if(CONNECT_USE_NAME_MAC == 1)
        {
            // 判断 MAC 地址
            if (memcmp(scan_result->scan_rst.bda, TARGET_MAC, 6) == 0) {
                ESP_LOGI(TAG, "找到目标设备（MAC 匹配）: %02x:%02x:%02x:%02x:%02x:%02x",
                            TARGET_MAC[0], TARGET_MAC[1], TARGET_MAC[2],
                            TARGET_MAC[3], TARGET_MAC[4], TARGET_MAC[5]);
                if (connect == false) {
                    connect = true;
                    ESP_LOGI(TAG, "连接到远程设备（MAC 匹配）");
                    esp_ble_gap_stop_scanning();
                    esp_ble_gattc_open(gattc_if_value, scan_result->scan_rst.bda,
                                    scan_result->scan_rst.ble_addr_type, true);
                }
            }
        }else
        {
            if (adv_name != NULL) {
                if (strlen(TARGET_NAME) == adv_name_len &&
                    strncmp((char *)adv_name, TARGET_NAME, adv_name_len) == 0) {

                    ESP_LOGI(TAG, "找到目标设备: %s", TARGET_NAME);
                    if (connect == false) {
                        connect = true;
                        ESP_LOGI(TAG, "连接到远程设备");
                        esp_ble_gap_stop_scanning();
                        esp_ble_gattc_open(gattc_if_value, scan_result->scan_rst.bda,
                                        scan_result->scan_rst.ble_addr_type, true);
                    }
                }
            }
        }
        break;
    }

    case ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT:
        if (param->scan_stop_cmpl.status != ESP_BT_STATUS_SUCCESS) {
            ESP_LOGE(TAG, "扫描停止失败, 错误状态 = %x", param->scan_stop_cmpl.status);
            break;
        }
        ESP_LOGI(TAG, "扫描停止成功");
        break;

    default:
        break;
    }
}

// GATTC 回调函数
static void esp_gattc_cb(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param) {
    ESP_LOGD(TAG, "GATTC事件: %d", event);

    switch (event) {
    case ESP_GATTC_REG_EVT:
        if (param->reg.status == ESP_GATT_OK) {
            gattc_if_value = gattc_if;
            ESP_LOGI(TAG, "注册成功，设置扫描参数");
            esp_ble_gap_set_scan_params(&ble_scan_params);
        } else {
            ESP_LOGE(TAG, "注册应用失败, 状态 %d", param->reg.status);
        }
        break;

    case ESP_GATTC_CONNECT_EVT:
        ESP_LOGI(TAG, "ESP_GATTC_CONNECT_EVT, 连接ID: %d", param->connect.conn_id);
        conn_id = param->connect.conn_id;
        memcpy(remote_bda, param->connect.remote_bda, sizeof(esp_bd_addr_t));

        // 连接后配置MTU
        esp_ble_gattc_send_mtu_req(gattc_if, param->connect.conn_id);
        break;

    case ESP_GATTC_OPEN_EVT:
        if (param->open.status != ESP_GATT_OK) {
            ESP_LOGE(TAG, "连接打开失败, 状态 %d", param->open.status);
            break;
        }
        ESP_LOGI(TAG, "连接打开成功");
        break;

    case ESP_GATTC_CFG_MTU_EVT:
        if (param->cfg_mtu.status != ESP_GATT_OK) {
            ESP_LOGE(TAG, "配置MTU失败, 状态 %d", param->cfg_mtu.status);
            break;
        }
        ESP_LOGI(TAG, "MTU配置成功, MTU = %d", param->cfg_mtu.mtu);

        // 开始搜索服务
        esp_ble_gattc_search_service(gattc_if, conn_id, NULL);
        break;

    case ESP_GATTC_SEARCH_RES_EVT:
        // 搜索到服务
        if (param->search_res.srvc_id.uuid.len == ESP_UUID_LEN_128 &&
            memcmp(param->search_res.srvc_id.uuid.uuid.uuid128, TARGET_SERVICE_UUID_128, 16) == 0) {

            ESP_LOGI(TAG, "找到目标服务 UUID=6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
            service_start_handle = param->search_res.start_handle;
            service_end_handle = param->search_res.end_handle;
        }
        break;

    case ESP_GATTC_SEARCH_CMPL_EVT:
        if (param->search_cmpl.status != ESP_GATT_OK) {
            ESP_LOGE(TAG, "服务搜索失败, 状态 %d", param->search_cmpl.status);
            break;
        }

        if (service_start_handle != 0 && service_end_handle != 0) {
            ESP_LOGI(TAG, "开始查找特征");
            // 获取特征数量
            uint16_t count = 0;
            esp_gatt_status_t status = esp_ble_gattc_get_attr_count(gattc_if, conn_id,
                                                                  ESP_GATT_DB_CHARACTERISTIC,
                                                                  service_start_handle,
                                                                  service_end_handle,
                                                                  0, &count);
            if (status != ESP_GATT_OK) {
                ESP_LOGE(TAG, "获取特征数量失败, 状态 %d", status);
                break;
            }
            if (count > 0) {
                // 分配内存存储特征
                esp_gattc_char_elem_t *char_elem_result = (esp_gattc_char_elem_t *)malloc(
                                                        sizeof(esp_gattc_char_elem_t) * count);
                if (!char_elem_result) {
                    ESP_LOGE(TAG, "内存分配失败");
                    break;
                }
                // 查找目标特征
                esp_bt_uuid_t char_uuid = {
                    .len = ESP_UUID_LEN_128,
                    .uuid = {
                        .uuid128 = {0x9E, 0xCA, 0xDC, 0x24, 0x0E, 0xE5, 0xA9, 0xE0, 0x93, 0xF3, 0xA3, 0xB5, 0x02, 0x00, 0x40, 0x6E},
                    },
                };
                status = esp_ble_gattc_get_char_by_uuid(gattc_if, conn_id,
                                                      service_start_handle, service_end_handle,
                                                      char_uuid, char_elem_result, &count);
                if (status != ESP_GATT_OK) {
                    ESP_LOGE(TAG, "获取特征失败, 状态 %d", status);
                    free(char_elem_result);
                    break;
                }
                if (count > 0) {
                    // 找到目标特征
                    char_handle = char_elem_result[0].char_handle;
                    ESP_LOGI(TAG, "找到目标特征, handle = %d", char_handle);

                    // 添加CCCD配置
                    uint16_t ccc_handle = char_handle + 1; // 假设描述符紧接特征
                    uint16_t enable_notify = 0x0001;
                    esp_err_t err = esp_ble_gattc_write_char_descr(
                        gattc_if,
                        conn_id,
                        ccc_handle,
                        sizeof(enable_notify),
                        (uint8_t*)&enable_notify,
                        ESP_GATT_WRITE_TYPE_RSP,
                        ESP_GATT_AUTH_REQ_NONE
                    );
                    if (err != ESP_OK) {
                        ESP_LOGE(TAG, "CCCD配置失败: %s", esp_err_to_name(err));
                    }
                    #if 1
                    uint8_t write_data[] = {
                        0xAA, 0xAA, 0x25, 0xB1, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46,
                        0x44, 0x45, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x31, 0x38,
                        0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x31, 0x32,
                        0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x50
                    };
                    my_ble_c_send_data(write_data,sizeof(write_data));
                    #endif
                } else {
                    ESP_LOGE(TAG, "未找到目标特征");
                }
                free(char_elem_result);
            } else {
                ESP_LOGE(TAG, "服务中没有特征");
            }
        } else {
            ESP_LOGE(TAG, "未找到目标服务");
        }
        break;

    case ESP_GATTC_REG_FOR_NOTIFY_EVT:
        if (param->reg_for_notify.status != ESP_GATT_OK) {
            ESP_LOGE(TAG, "注册通知失败, 状态 %d", param->reg_for_notify.status);
            break;
        }
        // 启用通知
        uint8_t ccc_value[2] = {0x01, 0x00}; // 小端格式: 0x0001
        esp_ble_gattc_write_char_descr(
            gattc_if,
            conn_id,
            param->reg_for_notify.handle + 1, // CCCD 描述符
            sizeof(ccc_value),
            ccc_value,
            ESP_GATT_WRITE_TYPE_RSP,
            ESP_GATT_AUTH_REQ_NONE
        );
        // 获取描述符数量
        uint16_t desc_count = 0;
        esp_gatt_status_t ret_status = esp_ble_gattc_get_attr_count(gattc_if, conn_id,
                                                                 ESP_GATT_DB_DESCRIPTOR,
                                                                 service_start_handle,
                                                                 service_end_handle,
                                                                 char_handle, &desc_count);

        if (ret_status != ESP_GATT_OK) {
            ESP_LOGE(TAG, "获取描述符数量失败, 状态 %d", ret_status);
            break;
        }
        if (desc_count > 0) {
            // 分配内存存储描述符
            esp_gattc_descr_elem_t *descr_elem_result = (esp_gattc_descr_elem_t *)malloc(
                                                      sizeof(esp_gattc_descr_elem_t) * desc_count);

            if (!descr_elem_result) {
                ESP_LOGE(TAG, "内存分配失败");
                break;
            }
            // 查找客户端特征配置描述符
            esp_bt_uuid_t notify_descr_uuid = {
                .len = ESP_UUID_LEN_16,
                .uuid = {
                    .uuid16 = ESP_GATT_UUID_CHAR_CLIENT_CONFIG,
                },
            };
            ret_status = esp_ble_gattc_get_descr_by_char_handle(gattc_if, conn_id,
                                                              char_handle,
                                                              notify_descr_uuid,
                                                              descr_elem_result, &desc_count);

            if (ret_status != ESP_GATT_OK) {
                ESP_LOGE(TAG, "获取描述符失败, 状态 %d", ret_status);
                free(descr_elem_result);
                break;
            }
            if (desc_count > 0) {
                // 使能通知
                uint16_t notify_en = 1;
                ret_status = esp_ble_gattc_write_char_descr(gattc_if, conn_id,
                                                         descr_elem_result[0].handle,
                                                         sizeof(notify_en),
                                                         (uint8_t *)&notify_en,
                                                         ESP_GATT_WRITE_TYPE_RSP,
                                                         ESP_GATT_AUTH_REQ_NONE);

                if (ret_status != ESP_GATT_OK) {
                    ESP_LOGE(TAG, "写入描述符失败, 状态 %d", ret_status);
                }
            }
            free(descr_elem_result);
        }
        break;

    case ESP_GATTC_NOTIFY_EVT:
        // 接收到通知数据
        ESP_LOGI(TAG, "收到数据 (长度 %d):", param->notify.value_len);
        // 打印HEX格式
        for (int i = 0; i < param->notify.value_len; i++) {
            printf("%02X ", param->notify.value[i]);
            if ((i+1) % 16 == 0) printf("\n");
        }
        printf("\n");
        // 打印ASCII格式
        ESP_LOG_BUFFER_HEX_LEVEL(TAG, param->notify.value, param->notify.value_len, ESP_LOG_INFO);
        break;

    case ESP_GATTC_WRITE_DESCR_EVT:
        if (param->write.status != ESP_GATT_OK) {
            ESP_LOGE(TAG, "写入描述符失败, 状态 %d", param->write.status);
            break;
        }

        ESP_LOGI(TAG, "写入描述符成功，现在发送数据到特征");

        // // 写入数据到特征
        // uint8_t write_data[4] = {0x11, 0x22, 0x33, 0x44};
        // esp_ble_gattc_write_char(gattc_if, conn_id, char_handle,
        //                         sizeof(write_data), write_data,
        //                         ESP_GATT_WRITE_TYPE_RSP,
        //                         ESP_GATT_AUTH_REQ_NONE);
        break;

    case ESP_GATTC_WRITE_CHAR_EVT:
            if (param->write.handle == char_handle) {
                // 检查写入结果
                if (param->write.status == ESP_GATT_OK) {
                    ESP_LOGI(TAG, "写入成功!");
                } else {
                    ESP_LOGE(TAG, "写入失败! 状态码: 0x%02X", param->write.status);

                    // 错误代码解析
                    switch (param->write.status) {
                        case ESP_GATT_INVALID_HANDLE:
                            ESP_LOGE(TAG, "原因: 无效的特征句柄");
                            break;
                        case ESP_GATT_WRITE_NOT_PERMIT:
                            ESP_LOGE(TAG, "原因: 写操作不被允许");
                            break;
                        case ESP_GATT_INSUF_AUTHENTICATION:
                            ESP_LOGE(TAG, "原因: 认证不足");
                            break;
                        default:
                            ESP_LOGE(TAG, "未知错误");
                    }
                }
                // 重置写入状态标志
                write_pending = false;
            }
            break;
        ESP_LOGI(TAG, "写入特征成功");
        break;
    case ESP_GATTC_DISCONNECT_EVT:
        connect = false;
        ESP_LOGI(TAG, "断开连接, 原因 = %d", param->disconnect.reason);

        // 重置服务和特征句柄
        service_start_handle = 0;
        service_end_handle = 0;
        char_handle = 0;

        // 重新开始扫描
        esp_ble_gap_set_scan_params(&ble_scan_params);
        break;

    default:
        break;
    }
}

void my_client_init(void)
{
    esp_err_t ret;
    // 注册 GAP 回调函数
    ret = esp_ble_gap_register_callback(esp_gap_cb);
    if (ret) {
        ESP_LOGE(TAG, "注册 GAP 回调失败: %s", esp_err_to_name(ret));
        return;
    }
    // 注册 GATTC 回调函数
    ret = esp_ble_gattc_register_callback(esp_gattc_cb);
    if (ret) {
        ESP_LOGE(TAG, "注册 GATTC 回调失败: %s", esp_err_to_name(ret));
        return;
    }
    // 注册 GATTC 应用
    ret = esp_ble_gattc_app_register(0);
    if (ret) {
        ESP_LOGE(TAG, "注册 GATTC 应用失败: %s", esp_err_to_name(ret));
        return;
    }
    // 设置本地 MTU
    ret = esp_ble_gatt_set_local_mtu(500);
    if (ret) {
        ESP_LOGE(TAG, "设置本地 MTU 失败: %s", esp_err_to_name(ret));
    }
    ESP_LOGI(TAG, "BLE 客户端初始化完成");
}

/*封装主机发送数据打包函数*/
void my_ble_c_send_data(uint8_t* data, uint16_t len)
{
    const int total_length = len;
    const int chunk_size = BLE_MTU_SEND_SIZE; // 根据当前 MTU 调整

    for (int offset = 0; offset < total_length; offset += chunk_size) {
        int current_chunk = (total_length - offset) < chunk_size ?
                            (total_length - offset) : chunk_size;

        // 最后一块使用响应写入，其他块使用无响应写入
        esp_gatt_write_type_t write_type = (offset + current_chunk >= total_length) ?
                                        ESP_GATT_WRITE_TYPE_RSP :
                                        ESP_GATT_WRITE_TYPE_NO_RSP;

        esp_err_t ret = esp_ble_gattc_write_char(
            gattc_if_value,
            conn_id,
            char_handle,
            current_chunk,
            data + offset,
            write_type,
            ESP_GATT_AUTH_REQ_NONE
        );

        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "分块写入失败 [偏移:%d]: %s",
                    offset, esp_err_to_name(ret));
            break;
        }
        // 添加延迟以避免堵塞
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}