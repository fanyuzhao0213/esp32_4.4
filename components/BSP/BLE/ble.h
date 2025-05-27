#ifndef BLE_H
#define BLE_H

#include <stdint.h>
#include "esp_log.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_log.h"

// 初始化BLE
void my_ble_init(void);


#endif // BLE_H

