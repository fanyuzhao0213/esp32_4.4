#include "ble.h"

static const char *TAG = "BLE_BLUEDROID";
uint8_t TARGET_MAC[6] = {0xEC, 0x43, 0x77, 0xE8, 0xA3, 0x1B}; // 设置要连接的实际目标MAC
char TARGET_NAME[] = "Washer-Aqua-Mu";// 设置要连接的设备名称



void my_ble_init(void)
{
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

    my_server_init();       //服务端初始化 类似于从机，广播被手机连
    my_client_init();       //客户端初始化 类似于主机，主动扫描
    #if 0
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
    #endif
}

