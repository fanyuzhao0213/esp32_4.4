#include "rtc.h"
#include "QMI8658.h"

static const char *TAG = "RTC";

// 读取RTC寄存器的函数
esp_err_t rtc_read_reg(uint8_t reg_addr, uint8_t *data, size_t len) 
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();  // 创建I2C命令句柄
    i2c_master_start(cmd);  // 开始I2C传输
    i2c_master_write_byte(cmd, (PCF85063_ADDR << 1) | I2C_MASTER_WRITE, true);  // 发送设备地址和写标志
    i2c_master_write_byte(cmd, reg_addr, true);  // 发送寄存器地址
    i2c_master_start(cmd);  // 重启I2C以准备读取
    i2c_master_write_byte(cmd, (PCF85063_ADDR << 1) | I2C_MASTER_READ, true);  // 发送设备地址和读标志
    i2c_master_read(cmd, data, len, I2C_MASTER_LAST_NACK);  // 读取数据
    i2c_master_stop(cmd);  // 停止I2C传输
    esp_err_t ret = i2c_master_cmd_begin(BSP_I2C_NUM, cmd, I2C_TIMEOUT_MS / portTICK_PERIOD_MS);  // 执行I2C命令
    i2c_cmd_link_delete(cmd);  // 删除I2C命令句柄
    return ret;  // 返回I2C操作结果
}

// 写入RTC寄存器的函数
esp_err_t rtc_write_reg(uint8_t reg_addr, uint8_t *data, size_t len) 
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (PCF85063_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg_addr, true);
    i2c_master_write(cmd, data, len, true);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(BSP_I2C_NUM, cmd, I2C_TIMEOUT_MS / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

// BCD编码转十进制
uint8_t bcd_to_dec(uint8_t val) 
{
    return (val >> 4) * 10 + (val & 0x0F);
}

// 十进制转BCD编码
uint8_t dec_to_bcd(uint8_t val) 
{
    return ((val / 10) << 4) | (val % 10);
}

// 获取RTC当前时间
esp_err_t sys_rtc_get_time(void) 
{
    uint8_t data[7];
    esp_err_t ret = rtc_read_reg(0x04, data, 7);  // 读取从0x04开始的PCF85063时间寄存器
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "读取时间寄存器失败");
        return ret;
    }

    // 解码BCD数据并处理
    uint8_t seconds = bcd_to_dec(data[0] & 0x7F);  // 忽略停止位
    uint8_t minutes = bcd_to_dec(data[1]);
    uint8_t hours = bcd_to_dec(data[2]);
    uint8_t day = bcd_to_dec(data[3]);
    uint8_t weekday = bcd_to_dec(data[4]);
    uint8_t month = bcd_to_dec(data[5] & 0x1F);  // 忽略世纪位
    uint8_t year = bcd_to_dec(data[6]);

    ESP_LOGI(TAG, "当前时间: %02d:%02d:%02d %02d/%02d/%04d", hours, minutes, seconds, day, month, 2000 + year);
    return ESP_OK;
}

// 设置RTC时间
esp_err_t rtc_set_time(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t day, uint8_t month, uint8_t year) 
{
    uint8_t data[7] = {
        dec_to_bcd(seconds),
        dec_to_bcd(minutes),
        dec_to_bcd(hours),
        dec_to_bcd(day),
        dec_to_bcd(0),  // 设置星期几（可选）
        dec_to_bcd(month),
        dec_to_bcd(year)
    };
    return rtc_write_reg(0x04, data, 7);
}

