#include "ble.h"
#include "string.h"

#define DEVICE_NAME "FYZ_ESP_BLE"
static const char *TAG = "BLE_BLUEDROID";

// 在文件顶部添加定时器相关定义
#define CONN_TIMEOUT_MS 30000
static esp_timer_handle_t disconnect_timer;
static uint16_t active_conn_id = 0xFFFF;


// 在全局变量区添加目标MAC定义
static uint8_t TARGET_MAC[6] = {0xE5, 0xBA, 0xCC, 0xE8, 0x05, 0xCC}; // 替换为实际目标MAC

#define PROFILE_NUM 1
#define PROFILE_APP_IDX 0
#define ESP_APP_ID 0x55
#define SERVICE_UUID 0x00FF
#define CHARACTERISTIC_UUID 0xFF01
#define GATTS_NUM_HANDLE 4

// 定义服务UUID结构体
static esp_bt_uuid_t service_uuid = {
    .len = ESP_UUID_LEN_128,
    .uuid.uuid128 = {
        0xfb, 0x34, 0x9b, 0x5f, 0x80, 0x00, 0x00, 0x80,
        0x00, 0x10, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00
    }
};

// 定义特征UUID结构体
static esp_bt_uuid_t char_uuid = {
    .len = ESP_UUID_LEN_128,
    .uuid.uuid128 = {
        0xfb, 0x34, 0x9b, 0x5f, 0x80, 0x00, 0x00, 0x80,
        0x00, 0x10, 0x00, 0x00, 0x01, 0xFF, 0x00, 0x00
    }
};

// 自定义制造商数据（包含MAC地址和其他数据）
static uint8_t manufacturer_data[12] = {0}; // 预留10字节的制造商数据空间

// 配置广播数据
esp_ble_adv_data_t adv_data = {
    .set_scan_rsp = false,
    .include_name = true,
    .include_txpower = true,
    .min_interval = 0x20,
    .max_interval = 0x40,
    .appearance = 0,
    .manufacturer_len = sizeof(manufacturer_data),  // 设置制造商数据长度
    .p_manufacturer_data = manufacturer_data,       // 指向制造商数据
    .service_data_len = 0,
    .p_service_data = NULL,
    .service_uuid_len = 16,       // 设置服务UUID长度
    .p_service_uuid = service_uuid.uuid.uuid128,                 // 指向服务UUID
    .flag = (ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT),
};

// 配置广播参数
esp_ble_adv_params_t adv_params = {
    .adv_int_min = 0x20,
    .adv_int_max = 0x40,
    .adv_type = ADV_TYPE_IND,
    .own_addr_type = BLE_ADDR_TYPE_PUBLIC,
    .channel_map = ADV_CHNL_ALL,
    .adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};


static esp_gatt_char_prop_t property = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_NOTIFY;
static esp_attr_value_t gatts_demo_char_val = {
    .attr_max_len = 512,
    .attr_len     = 0,
    .attr_value   = NULL,
};

static uint16_t profile_handle_table[GATTS_NUM_HANDLE];
static esp_gatts_cb_t gatts_cb;
static esp_gatt_if_t gatts_if_for_notify = 0;

// 添加定时器回调函数
static void disconnect_timeout_callback(void* arg) {
    if (active_conn_id != 0xFFFF) {
        ESP_LOGI(TAG, "连接超时，主动断开");
        esp_ble_gatts_close(gatts_if_for_notify, active_conn_id);
        active_conn_id = 0xFFFF;
        // 清理定时器资源
        if (disconnect_timer) {
            esp_timer_stop(disconnect_timer);
            esp_timer_delete(disconnect_timer);
            disconnect_timer = NULL;
        }
    }
}

// 处理GATTS事件的回调函数
static void gatts_profile_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param) {
    switch (event) {
        case ESP_GATTS_REG_EVT:
            ESP_LOGI(TAG, "REGISTER_APP_EVT, status %d, app_id %d", param->reg.status, param->reg.app_id);
            esp_ble_gap_set_device_name(DEVICE_NAME);
            esp_ble_gap_config_local_privacy(true);

            // 创建服务ID结构体
            esp_gatt_srvc_id_t service_id = {
                .is_primary = true,
                .id = {
                    .uuid = service_uuid,
                    .inst_id = 0
                }
            };
            esp_ble_gatts_create_service(gatts_if, &service_id, GATTS_NUM_HANDLE);
            break;

        case ESP_GATTS_CREATE_EVT:
            ESP_LOGI(TAG, "CREATE_SERVICE_EVT, status %d,  service_handle %d\n", param->create.status, param->create.service_handle);
            profile_handle_table[0] = param->create.service_handle;
            esp_ble_gatts_start_service(profile_handle_table[0]);
            esp_ble_gatts_add_char(
                profile_handle_table[0],
                &char_uuid,  // 使用结构体指针
                ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
                property,
                &gatts_demo_char_val,
                NULL);
            break;

        case ESP_GATTS_CONNECT_EVT:
            ESP_LOGI(TAG, "ESP_GATTS_CONNECT_EVT, conn_id = %d", param->connect.conn_id);
            // 打印连接设备的MAC地址
            ESP_LOGI(TAG, "连接设备MAC地址: %02x:%02x:%02x:%02x:%02x:%02x",
                    param->connect.remote_bda[0], param->connect.remote_bda[1],
                    param->connect.remote_bda[2], param->connect.remote_bda[3],
                    param->connect.remote_bda[4], param->connect.remote_bda[5]);
            gatts_if_for_notify = gatts_if;
            esp_ble_gap_stop_advertising();

            // 记录当前连接ID
            active_conn_id = param->connect.conn_id;
            // 创建单次定时器
            esp_timer_create_args_t timer_args = {
                .callback = &disconnect_timeout_callback,
                .name = "disconnect_timer"
            };
            esp_timer_create(&timer_args, &disconnect_timer);
            esp_timer_start_once(disconnect_timer, CONN_TIMEOUT_MS * 1000);
            break;
            break;

        case ESP_GATTS_WRITE_EVT:
            if (!param->write.is_prep) {
                esp_ble_gatts_send_response(gatts_if, param->write.conn_id, param->write.trans_id, ESP_GATT_OK, NULL);
                ESP_LOGI(TAG, "GATT_WRITE_EVT, handle = %d, value len = %d, value :", param->write.handle, param->write.len);
                esp_log_buffer_hex(TAG, param->write.value, param->write.len);

                // 添加数据回复逻辑
                uint8_t response_data[] = {0x11, 0xAA, 0xFF}; // 自定义回复数据
                esp_err_t ret = esp_ble_gatts_send_indicate(
                    gatts_if_for_notify,
                    active_conn_id,
                    profile_handle_table[3], // 特征值句柄
                    sizeof(response_data),
                    response_data,
                    false // 使用通知而非指示
                );
                if (ret != ESP_OK) {
                    ESP_LOGE(TAG, "发送失败: %s", esp_err_to_name(ret));
                }else
                {
                    ESP_LOGI(TAG, "已发送回复数据");
                }
            }
            break;

        case ESP_GATTS_DISCONNECT_EVT:
            ESP_LOGI(TAG, "ESP_GATTS_DISCONNECT_EVT, disconnect reason 0x%x", param->disconnect.reason);
            esp_ble_gap_start_advertising(&adv_params);
            // 取消定时器
            if (disconnect_timer) {
                esp_timer_stop(disconnect_timer);
                esp_timer_delete(disconnect_timer);
                disconnect_timer = NULL;
            }
            active_conn_id = 0xFFFF;
            gatts_if_for_notify = 0;
            memset(profile_handle_table, 0, sizeof(profile_handle_table));
            break;
        // 修正重复的特征添加事件处理，合并为一个完整的处理分支
        case ESP_GATTS_ADD_CHAR_EVT:
            if (param->add_char.status == ESP_GATT_OK) {
                profile_handle_table[3] = param->add_char.attr_handle;
                ESP_LOGI(TAG, "特征添加成功，句柄: %d", param->add_char.attr_handle);

                // 添加客户端特征配置描述符
                esp_bt_uuid_t descr_uuid = {
                    .len = ESP_UUID_LEN_16,
                    .uuid.uuid16 = ESP_GATT_UUID_CHAR_CLIENT_CONFIG
                };
                esp_ble_gatts_add_char_descr(
                    profile_handle_table[0],
                    &descr_uuid,
                    ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
                    NULL,
                    NULL);
            }
            break;

        // 添加描述符事件处理
        case ESP_GATTS_ADD_CHAR_DESCR_EVT:
            if (param->add_char_descr.status == ESP_GATT_OK) {
                ESP_LOGI(TAG, "描述符添加成功，句柄: %d", param->add_char_descr.attr_handle);
                // 保存描述符句柄
                profile_handle_table[2] = param->add_char_descr.attr_handle;
            }
            break;
        default:
            break;
    }
}

// GATTS回调函数
static void gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param) {
    if (event == ESP_GATTS_REG_EVT) {
        if (param->reg.status == ESP_GATT_OK) {
            profile_handle_table[PROFILE_APP_IDX] = param->reg.app_id;
        } else {
            ESP_LOGI(TAG, "Reg app failed, app_id %04x, status %d\n",
                    param->reg.app_id,
                    param->reg.status);
            return;
        }
    }

    gatts_profile_event_handler(event, gatts_if, param);
}

// 处理扫描结果的回调函数
static void esp_gap_cb(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param) {
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

void my_ble_init(void) {
    esp_err_t ret;

    ESP_LOGI(TAG, "初始化蓝牙控制器");
    printf("Free heap before BT init: %d\n", heap_caps_get_free_size(MALLOC_CAP_DEFAULT));

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ret = esp_bt_controller_init(&bt_cfg);
    if (ret) {
        ESP_LOGE(TAG, "蓝牙控制器初始化失败: %s", esp_err_to_name(ret));
        return;
    }
    printf("Free heap after BT init: %d\n", heap_caps_get_free_size(MALLOC_CAP_DEFAULT));

    ret = esp_bt_controller_enable(ESP_BT_MODE_BLE);
    if (ret) {
        ESP_LOGE(TAG, "蓝牙控制器使能失败: %s", esp_err_to_name(ret));
        return;
    }

    ret = esp_bluedroid_init();
    if (ret) {
        ESP_LOGE(TAG, "Bluedroid初始化失败: %s", esp_err_to_name(ret));
        return;
    }

    ret = esp_bluedroid_enable();
    if (ret) {
        ESP_LOGE(TAG, "Bluedroid使能失败: %s", esp_err_to_name(ret));
        return;
    }

    // 注册GATTS和GAP回调
    ret = esp_ble_gatts_register_callback(gatts_event_handler);
    if (ret) {
        ESP_LOGE(TAG, "GATTS回调注册失败, error code = %x", ret);
        return;
    }

    ret = esp_ble_gatts_app_register(ESP_APP_ID);
    if (ret) {
        ESP_LOGE(TAG, "GATTS应用注册失败, error code = %x", ret);
        return;
    }

    // 注册GAP回调
    esp_ble_gap_register_callback(esp_gap_cb);
    esp_ble_gap_set_device_name(DEVICE_NAME);

    // 获取蓝牙MAC地址
    uint8_t mac[6];
    esp_read_mac(mac, ESP_MAC_BT);

    // 设置制造商数据
    // 修改数据填充方式：
    manufacturer_data[0] = 0xFF;
    manufacturer_data[1] = 0xFF;
    memcpy(&manufacturer_data[2], mac, 6);
    manufacturer_data[8] = 0x01;
    manufacturer_data[9] = 0x02;
    manufacturer_data[10] = 0x03; // 新增数据
    manufacturer_data[11] = 0x04; // 新增数据

    // 配置广播数据
    esp_ble_gap_config_adv_data(&adv_data);

    // 启动广播
    ret = esp_ble_gap_start_advertising(&adv_params);
    if (ret) {
        ESP_LOGE(TAG, "启动广播失败: %s", esp_err_to_name(ret));
        return;
    }

    // 启动扫描
    esp_ble_scan_params_t scan_params = {
        .scan_type = BLE_SCAN_TYPE_ACTIVE,
        .own_addr_type = BLE_ADDR_TYPE_PUBLIC,
        .scan_filter_policy = BLE_SCAN_FILTER_ALLOW_ALL,
        .scan_interval = 0x50,
        .scan_window = 0x30,
        .scan_duplicate = BLE_SCAN_DUPLICATE_DISABLE
    };
    esp_ble_gap_set_scan_params(&scan_params);
    #if 0
    //  添加设备到白名单          .scan_filter_policy = BLE_SCAN_FILTER_ALLOW_ONLY_WLST, // 关键参数  需要同步使用
    // 3. 白名单验证（在GAP回调中）
    case ESP_GAP_BLE_SCAN_RESULT_EVT:
    if(param->scan_rst.ble_adv_flag & ESP_BLE_ADV_FLAG_FILTERED_BY_WLST) {
        ESP_LOGI(TAG, "该设备通过白名单过滤");
    }
    #endif
    // esp_ble_gap_update_whitelist(true, TARGET_MAC,BLE_WL_ADDR_TYPE_PUBLIC);
    esp_ble_gap_start_scanning(0); // 0表示持续扫描
}

