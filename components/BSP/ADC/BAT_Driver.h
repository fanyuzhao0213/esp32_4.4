#pragma once
#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"


/*---------------------------------------------------------------
        ADC General Macros
---------------------------------------------------------------*/
/* 硬件配置 */
#define ADC_UNIT            ADC_UNIT_1                  // 使用ADC1
#define ADC_CHANNEL         ADC1_CHANNEL_7              // 对应GPIO35(ESP32)或GPIO8(ESP32-S3)
#define ADC_ATTEN          ADC_ATTEN_DB_11             // 11dB衰减(0-3.1V量程)
#define VOLTAGE_DIV_RATIO  3.0f                        // 分压电阻比例
#define MEASUREMENT_OFFSET 0.99f                        // 测量补偿系数

/* 全局变量 */
static esp_adc_cal_characteristics_t adc_chars;

extern float BAT_analogVolts;

void BAT_Init(void);
float BAT_Get_Volts(void);

