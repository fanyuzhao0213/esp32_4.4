/*****************************************************************************
* | File       :   PCF85063.c
* | Author     :   Waveshare team
* | Function   :   PCF85063 RTC Driver
* | Info       :
*----------------
* | This version: V2.0
* | Date       :   2024-03-20
* | Info       :   Enhanced version with detailed comments
*
******************************************************************************/
#include "PCF85063.h"

/* 全局变量 */
datetime_t datetime = {0};  // 当前日期时间结构体

/* 月份字符串映射表 */
const char MonthStr[12][4] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

/* 私有函数声明 */
static uint8_t decToBcd(int val);
static int bcdToDec(uint8_t val);

/******************************************************************************
 * @brief  PCF85063初始化
 * @note   配置为正常模式，RTC运行，不重置，不校正，24小时制，内部负载电容12.5pF
 ******************************************************************************/
void PCF85063_Init()
{
    uint8_t Value = RTC_CTRL_1_DEFAULT | RTC_CTRL_1_CAP_SEL;
    ESP_ERROR_CHECK(I2C_Write(PCF85063_ADDRESS, RTC_CTRL_1_ADDR, &Value, 1));

    // 示例：初始化时设置默认时间（开发时使用）
    /*
    datetime_t default_time = {
        .year = 2024,
        .month = 3,
        .day = 20,
        .dotw = 3,  // 周三
        .hour = 12,
        .minute = 0,
        .second = 0
    };
    PCF85063_Set_All(default_time);
    */
}

/******************************************************************************
 * @brief  RTC主循环
 * @note   需要定期调用以更新时间数据
 ******************************************************************************/
void PCF85063_Loop(void)
{
    PCF85063_Read_Time(&datetime);
}

/******************************************************************************
 * @brief  硬件复位RTC
 * @note   会触发RTC的软复位，保持配置但重置内部状态
 ******************************************************************************/
void PCF85063_Reset()
{
    uint8_t Value = RTC_CTRL_1_DEFAULT | RTC_CTRL_1_CAP_SEL | RTC_CTRL_1_SR;
    ESP_ERROR_CHECK(I2C_Write(PCF85063_ADDRESS, RTC_CTRL_1_ADDR, &Value, 1));
}

/******************************************************************************
 * @brief  设置时间（时、分、秒）
 * @param  time : 包含时分秒的datetime_t结构体
 ******************************************************************************/
void PCF85063_Set_Time(datetime_t time)
{
    uint8_t buf[3] = {
        decToBcd(time.second),
        decToBcd(time.minute),
        decToBcd(time.hour)
    };
    ESP_ERROR_CHECK(I2C_Write(PCF85063_ADDRESS, RTC_SECOND_ADDR, buf, 3));
}

/******************************************************************************
 * @brief  设置日期（日、星期、月、年）
 * @param  date : 包含日期的datetime_t结构体
 * @note   年份会自动减去YEAR_OFFSET（通常为2000）
 ******************************************************************************/
void PCF85063_Set_Date(datetime_t date)
{
    uint8_t buf[4] = {
        decToBcd(date.day),
        decToBcd(date.dotw),
        decToBcd(date.month),
        decToBcd(date.year - YEAR_OFFSET)
    };
    ESP_ERROR_CHECK(I2C_Write(PCF85063_ADDRESS, RTC_DAY_ADDR, buf, 4));
}

/******************************************************************************
 * @brief  设置完整日期时间
 * @param  time : 完整的datetime_t结构体
 * @note   一次性设置所有时间寄存器，减少I2C通信次数
 ******************************************************************************/
void PCF85063_Set_All(datetime_t time)
{
    uint8_t buf[7] = {
        decToBcd(time.second),
        decToBcd(time.minute),
        decToBcd(time.hour),
        decToBcd(time.day),
        decToBcd(time.dotw),
        decToBcd(time.month),
        decToBcd(time.year - YEAR_OFFSET)
    };
    ESP_ERROR_CHECK(I2C_Write(PCF85063_ADDRESS, RTC_SECOND_ADDR, buf, 7));
}

/******************************************************************************
 * @brief  读取当前日期时间
 * @param  time : 用于存储时间的datetime_t指针
 * @note   会自动处理BCD到十进制的转换
 ******************************************************************************/
void PCF85063_Read_Time(datetime_t *time)
{
    uint8_t buf[7] = {0};
    ESP_ERROR_CHECK(I2C_Read(PCF85063_ADDRESS, RTC_SECOND_ADDR, buf, 7));

    time->second = bcdToDec(buf[0] & 0x7F);  // 去掉无效位
    time->minute = bcdToDec(buf[1] & 0x7F);
    time->hour   = bcdToDec(buf[2] & 0x3F);  // 24小时制
    time->day    = bcdToDec(buf[3] & 0x3F);
    time->dotw   = bcdToDec(buf[4] & 0x07);  // 星期几(0-6)
    time->month  = bcdToDec(buf[5] & 0x1F);
    time->year   = bcdToDec(buf[6]) + YEAR_OFFSET;
}

/******************************************************************************
 * @brief  启用闹钟功能并清除闹钟标志
 * @note   需要先设置闹钟时间再调用此函数
 ******************************************************************************/
void PCF85063_Enable_Alarm()
{
    uint8_t Value = RTC_CTRL_2_DEFAULT | RTC_CTRL_2_AIE;  // 使能闹钟中断
    Value &= ~RTC_CTRL_2_AF;  // 清除闹钟标志
    ESP_ERROR_CHECK(I2C_Write(PCF85063_ADDRESS, RTC_CTRL_2_ADDR, &Value, 1));
}

/******************************************************************************
 * @brief  获取闹钟触发状态
 * @return 闹钟状态标志位组合：
 *         - RTC_CTRL_2_AF: 闹钟已触发
 *         - RTC_CTRL_2_AIE: 闹钟中断使能
 ******************************************************************************/
uint8_t PCF85063_Get_Alarm_Flag()
{
    uint8_t Value = 0;
    ESP_ERROR_CHECK(I2C_Read(PCF85063_ADDRESS, RTC_CTRL_2_ADDR, &Value, 1));
    return Value & (RTC_CTRL_2_AF | RTC_CTRL_2_AIE);
}

/******************************************************************************
 * @brief  设置闹钟时间
 * @param  time : 包含闹钟时间的datetime_t结构体
 * @note   当前实现只设置时分秒，日和星期禁用（设置为RTC_ALARM）
 ******************************************************************************/
void PCF85063_Set_Alarm(datetime_t time)
{
    uint8_t buf[5] = {
        decToBcd(time.second) & (~RTC_ALARM),  // 秒报警使能
        decToBcd(time.minute) & (~RTC_ALARM),  // 分报警使能
        decToBcd(time.hour) & (~RTC_ALARM),    // 时报警使能
        RTC_ALARM,  // 日报警禁用
        RTC_ALARM   // 星期报警禁用
    };
    ESP_ERROR_CHECK(I2C_Write(PCF85063_ADDRESS, RTC_SECOND_ALARM, buf, 5));
}

/******************************************************************************
 * @brief  读取闹钟设置时间
 * @param  time : 存储闹钟时间的datetime_t指针
 ******************************************************************************/
void PCF85063_Read_Alarm(datetime_t *time)
{
    uint8_t buf[5] = {0};
    ESP_ERROR_CHECK(I2C_Read(PCF85063_ADDRESS, RTC_SECOND_ALARM, buf, 5));

    time->second = bcdToDec(buf[0] & 0x7F);
    time->minute = bcdToDec(buf[1] & 0x7F);
    time->hour   = bcdToDec(buf[2] & 0x3F);
    // 注：日和星期报警被禁用，读取值无意义
}

/******************************************************************************
 * @brief  十进制转BCD码
 * @param  val : 十进制数值(0-99)
 * @return 对应的BCD码
 ******************************************************************************/
static uint8_t decToBcd(int val)
{
    return (uint8_t)((val / 10 * 16) + (val % 10));
}

/******************************************************************************
 * @brief  BCD码转十进制
 * @param  val : BCD码
 * @return 对应的十进制数值
 ******************************************************************************/
static int bcdToDec(uint8_t val)
{
    return (int)((val / 16 * 10) + (val % 16));
}

/******************************************************************************
 * @brief  日期时间转字符串
 * @param  datetime_str : 输出缓冲区
 * @param  time : 日期时间结构体
 * @note   格式: "YYYY.MM.DD D HH:MM:SS"
 ******************************************************************************/
void datetime_to_str(char *datetime_str, datetime_t time)
{
    sprintf(datetime_str, " %d.%d.%d %d %d:%d:%d ",
            time.year, time.month, time.day,
            time.dotw, time.hour, time.minute, time.second);
}
