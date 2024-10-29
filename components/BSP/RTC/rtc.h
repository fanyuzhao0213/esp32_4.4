#ifndef __RTC_H_
#define __RTC_H_

#include <stdio.h>
#include "driver/i2c.h"
#include "esp_log.h"
#include "esp_err.h"

#define PCF85063_ADDR        0x51      // PCF85063 I2C address
#define I2C_TIMEOUT_MS       1000

esp_err_t rtc_set_time(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t day, uint8_t month, uint8_t year);
esp_err_t sys_rtc_get_time(void);


#endif


