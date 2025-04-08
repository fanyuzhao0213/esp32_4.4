#include "BAT_Driver.h"


/* 调试标签 */
const static char *ADC_TAG = "ADC";

/* 全局变量 */
float BAT_analogVolts = 0;  // 电池电压值（单位：V）

/*
**
 * @brief ADC校准初始化
 * @return true:校准可用 false:校准不可用
 */
static bool adc_calibration_init(void)
{
    esp_err_t ret = esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_VREF);

    if (ret == ESP_OK) {
        esp_adc_cal_characterize(ADC_UNIT, ADC_ATTEN,
                               ADC_WIDTH_BIT_12, 0, &adc_chars);
        ESP_LOGI(ADC_TAG, "ADC校准启用 Vref=%dmV", adc_chars.vref);
        return true;
    }

    ESP_LOGI(ADC_TAG, "eFuse校准数据未找到,使用原始值");
    return false;
}

/**
 * @brief ADC硬件初始化
 */
static void adc_hardware_init(void)
{
    // 配置ADC位宽(12位)
    adc1_config_width(ADC_WIDTH_BIT_12);

    // 配置通道衰减
    adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN);
}



/**
 * @brief 电池检测初始化
 */
void BAT_Init(void)
{
    adc_hardware_init();
    bool cali_enabled = adc_calibration_init();

    if (!cali_enabled) {
        ESP_LOGI(ADC_TAG, "注意：未启用校准，电压测量可能存在误差");
    }
}

/**
 * @brief 获取电池电压(V)
 * @return 当前电池电压(单位:V)
 */
float BAT_Get_Volts(void)
{
    int raw = adc1_get_raw(ADC_CHANNEL);

    if (adc_chars.vref != 0) {  // 校准可用
        uint32_t voltage_mv = esp_adc_cal_raw_to_voltage(raw, &adc_chars);
        BAT_analogVolts = (voltage_mv * VOLTAGE_DIV_RATIO) / 1000.0f / MEASUREMENT_OFFSET;
    } else {  // 无校准时的近似计算
        BAT_analogVolts = (raw * 3.3f * VOLTAGE_DIV_RATIO) / 4095.0f / MEASUREMENT_OFFSET;
    }

    // ESP_LOGI(ADC_TAG, "Raw:%d, Voltage:%.2fV", raw, BAT_analogVolts);
    return BAT_analogVolts;
}

