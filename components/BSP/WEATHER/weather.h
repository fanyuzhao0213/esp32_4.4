#ifndef __WEATHER_H_
#define __WEATHER_H_

// 定义天气信息结构体
typedef struct {
    char date[16];              // 日期
    char text_day[32];          // 白天天气描述
    char text_night[32];        // 夜间天气描述
    char high[8];               // 最高温度
    char low[8];                // 最低温度
    char rainfall[8];           // 降雨量
    char humidity[8];           // 湿度
    char wind_speed[8];         // 风速
    char wind_direction[32];    // 风向
} WeatherInfo;

// 全局变量，用于保存每日天气信息
#define MAX_DAYS 7  // 假设最多保存 7 天的天气信息
WeatherInfo daily_weather[MAX_DAYS];
extern char *City_Name;  // 用于存储 CITY 的 name

//更改更新weather的时间   默认为10min
#define WEATHER_UPDATE_TIME                 60*1           //单位1S
extern void http_client_task(void *pvParameters);

#endif