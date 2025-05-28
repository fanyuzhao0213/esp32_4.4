/* my_server.c */
#include "ble.h"

static const char *TAG = "BLE_SERVER";

// 在文件顶部添加定时器相关定义
#define CONN_TIMEOUT_MS 30000
static esp_timer_handle_t disconnect_timer;
static uint16_t active_conn_id = 0xFFFF;




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

void my_server_init(void)
{
    esp_err_t ret;
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
}

