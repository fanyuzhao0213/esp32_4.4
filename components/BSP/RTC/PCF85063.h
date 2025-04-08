#pragma once

#include "iic.h"
#include "esp_log.h"

extern uint8_t g_my_lvgl_hours;
extern uint8_t g_my_lvgl_minutes;
extern uint8_t g_my_lvgl_seconds;
extern uint32_t g_my_lvgl_year;
extern uint32_t g_my_lvgl_month;
extern uint32_t g_my_lvgl_day;
extern char *weekday_str;  // 获取星期几的字符串


/*********************** 设备地址定义 ************************/
#define PCF85063_ADDRESS   (0x51)  // PCF85063的I2C设备地址

/*********************** 时间基准定义 ***********************/
#define YEAR_OFFSET        (1970)  // 年份基准值（RTC存储的年份需要加上此偏移量）

/*********************** 寄存器地址定义 *********************/
/* 控制与状态寄存器 */
#define RTC_CTRL_1_ADDR    (0x00)  // 控制寄存器1
#define RTC_CTRL_2_ADDR    (0x01)  // 控制寄存器2
#define RTC_OFFSET_ADDR    (0x02)  // 偏移校准寄存器
#define RTC_RAM_by_ADDR    (0x03)  // RAM字节寄存器

/* 时间日期寄存器 */
#define RTC_SECOND_ADDR    (0x04)  // 秒寄存器
#define RTC_MINUTE_ADDR    (0x05)  // 分寄存器
#define RTC_HOUR_ADDR      (0x06)  // 时寄存器
#define RTC_DAY_ADDR       (0x07)  // 日寄存器
#define RTC_WDAY_ADDR      (0x08)  // 星期寄存器
#define RTC_MONTH_ADDR     (0x09)  // 月寄存器
#define RTC_YEAR_ADDR      (0x0A)  // 年寄存器（0-99，实际年份=YEAR_OFFSET+寄存器值）

/* 闹钟寄存器 */
#define RTC_SECOND_ALARM   (0x0B)  // 闹钟秒寄存器
#define RTC_MINUTE_ALARM   (0x0C)  // 闹钟分寄存器
#define RTC_HOUR_ALARM     (0x0D)  // 闹钟时寄存器
#define RTC_DAY_ALARM      (0x0E)  // 闹钟日寄存器
#define RTC_WDAY_ALARM     (0x0F)  // 闹钟星期寄存器

/* 定时器寄存器 */
#define RTC_TIMER_VAL      (0x10)  // 定时器值寄存器
#define RTC_TIMER_MODE     (0x11)  // 定时器模式寄存器

/*********************** 控制寄存器1位定义 ******************/
#define RTC_CTRL_1_EXT_TEST (0x80) // 外部时钟测试模式
#define RTC_CTRL_1_STOP     (0x20) // RTC停止位：0-运行 1-停止
#define RTC_CTRL_1_SR       (0x10) // 软件复位：0-正常 1-复位
#define RTC_CTRL_1_CIE      (0x04) // 校准中断使能
#define RTC_CTRL_1_12_24    (0x02) // 时间格式：0-24小时制 1-12小时制
#define RTC_CTRL_1_CAP_SEL  (0x01) // 负载电容选择：0-7pF 1-12.5pF

/*********************** 控制寄存器2位定义 ******************/
#define RTC_CTRL_2_AIE      (0x80) // 闹钟中断使能
#define RTC_CTRL_2_AF       (0x40) // 闹钟标志位
#define RTC_CTRL_2_MI       (0x20) // 分钟中断使能
#define RTC_CTRL_2_HMI      (0x10) // 半分钟中断使能
#define RTC_CTRL_2_TF       (0x08) // 定时器标志位

/*********************** 偏移校准寄存器位定义 ***************/
#define RTC_OFFSET_MODE     (0x80) // 偏移校准模式

/*********************** 定时器模式寄存器位定义 *************/
#define RTC_TIMER_MODE_TE   (0x04) // 定时器使能
#define RTC_TIMER_MODE_TIE  (0x02) // 定时器中断使能
#define RTC_TIMER_MODE_TI_TP (0x01) // 定时器中断模式：0-电平 1-脉冲

/*********************** 通用定义 **************************/
#define RTC_ALARM           (0x80) // 闹钟使能位（设置对应位禁用闹钟）
#define RTC_CTRL_1_DEFAULT  (0x00) // 控制寄存器1默认值
#define RTC_CTRL_2_DEFAULT  (0x00) // 控制寄存器2默认值
#define RTC_TIMER_FLAG      (0x08) // 定时器标志位掩码

/*********************** 数据类型定义 **********************/
/**
 * @brief 日期时间结构体
 * @note 星期(dotw)取值范围：0-6（周日-周六）
 */
typedef struct {
    uint16_t year;    // 年份（完整年份，如2024）
    uint8_t month;    // 月份（1-12）
    uint8_t day;      // 日（1-31）
    uint8_t dotw;     // 星期（0-6，周日=0）
    uint8_t hour;     // 时（0-23）
    uint8_t minute;   // 分（0-59）
    uint8_t second;   // 秒（0-59）
} datetime_t;

/*********************** 全局变量声明 **********************/
extern datetime_t datetime;  // 全局日期时间变量

/*********************** 函数声明 *************************/
/* 基础功能 */
void PCF85063_Init(void);      // RTC初始化
void PCF85063_Loop(void);      // RTC主循环
void PCF85063_Reset(void);     // RTC复位

/* 时间设置与读取 */
void PCF85063_Set_Time(datetime_t time);   // 设置时间（时分秒）
void PCF85063_Set_Date(datetime_t date);   // 设置日期（年月日星期）
void PCF85063_Set_All(datetime_t time);    // 设置完整日期时间
void PCF85063_Read_Time(datetime_t *time); // 读取完整日期时间

/* 闹钟功能 */
void PCF85063_Enable_Alarm(void);          // 使能闹钟功能
uint8_t PCF85063_Get_Alarm_Flag(void);     // 获取闹钟触发状态
void PCF85063_Set_Alarm(datetime_t time);  // 设置闹钟时间
void PCF85063_Read_Alarm(datetime_t *time);// 读取闹钟设置

/* 工具函数 */
void datetime_to_str(char *datetime_str, datetime_t time); // 日期时间转字符串

/*********************** 星期定义说明 **********************
 * 0 - Sunday    周日
 * 1 - Monday    周一
 * 2 - Tuesday   周二
 * 3 - Wednesday 周三
 * 4 - Thursday  周四
 * 5 - Friday    周五
 * 6 - Saturday  周六
 **********************************************************/


