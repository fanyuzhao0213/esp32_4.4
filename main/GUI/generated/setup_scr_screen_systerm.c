/*
 * Copyright 2025 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"
#include "BSP/RTC/rtc.h"
#include "BSP/WIFI/wifi_smartconfig.h"
#include "esp_task_wdt.h"

static char cached_paths[3][128]; // 缓存图片路径
static uint8_t img_index = 0;     // 当前加载的图片索引
// 获取图像路径
const char* get_image_path(char* weather_code)
{
	static char path[256]; // 静态分配，避免被释放
	snprintf(path, sizeof(path), "bmp_tianqi_40x40_%s", weather_code);
    return path;
}

// 创建一个图像路径对象
char *image_jinri_path; // 用于存储完整路径
char *image_mingri_path; // 用于存储完整路径
char *image_houri_path; // 用于存储完整路径
bool image_set = false;
// 静态变量，用于保存上一次设置的路径
static char last_image_path_tianqi[256] = {0};
static char last_image_path_jintian[256] = {0};
static char last_image_path_mingtian[256] = {0};
static char last_image_path_houtian[256] = {0};

lv_img_dsc_t* get_image_descriptor(char* weather_code) {
    // 将 weather_code 转换为对应的数值（如果是数字字符串）
    int num = atoi(weather_code);  // 转换字符串为整数
	// printf("weather_code:%s\n",weather_code);
	// printf("num:%d\n",num);
    // 判断数字是否在合法范围内（0-38 或 99）
    if ((num >= 0 && num <= 38) || num == 99) {
        // 使用数组来存储图像描述符
        static lv_img_dsc_t* image_desc[] = {
            &bmp_tianqi_40x40_0, &bmp_tianqi_40x40_1, &bmp_tianqi_40x40_2,
            &bmp_tianqi_40x40_3, &bmp_tianqi_40x40_4, &bmp_tianqi_40x40_5,
			&bmp_tianqi_40x40_6, &bmp_tianqi_40x40_7, &bmp_tianqi_40x40_8,
			&bmp_tianqi_40x40_9, &bmp_tianqi_40x40_10, &bmp_tianqi_40x40_11,
			&bmp_tianqi_40x40_12, &bmp_tianqi_40x40_13, &bmp_tianqi_40x40_14,
			&bmp_tianqi_40x40_15, &bmp_tianqi_40x40_16, &bmp_tianqi_40x40_17,
			&bmp_tianqi_40x40_18, &bmp_tianqi_40x40_19, &bmp_tianqi_40x40_20,
			&bmp_tianqi_40x40_21, &bmp_tianqi_40x40_22, &bmp_tianqi_40x40_23,
			&bmp_tianqi_40x40_24, &bmp_tianqi_40x40_25, &bmp_tianqi_40x40_26,
			&bmp_tianqi_40x40_27, &bmp_tianqi_40x40_28, &bmp_tianqi_40x40_29,
			&bmp_tianqi_40x40_30, &bmp_tianqi_40x40_31, &bmp_tianqi_40x40_32,
			&bmp_tianqi_40x40_33, &bmp_tianqi_40x40_34, &bmp_tianqi_40x40_35,
			&bmp_tianqi_40x40_36, &bmp_tianqi_40x40_37, &bmp_tianqi_40x40_38,
            &bmp_tianqi_40x40_99
        };
        // 判断 weather_code 是否在有效范围内并返回相应的图像描述符
        if (num <= 38 || num == 99) {
            return image_desc[num];  // 根据 weather_code 的值返回图像描述符
        }
    }
    return NULL;  // 如果 weather_code 不在有效范围内，返回 NULL
}


// 定时器回调函数，用于更新时间
void screen_systerm_timer(lv_timer_t *timer)
{
	printf("current_screen: %d\r\n",current_screen);
	if(current_screen == SCREEN_2)
	{
		uint8_t m_hours = 0;
		// 更新时间
		sync_systime_to_mytime();
		    // 打印时间信息
   		printf("SCREEN_2 SYNC TIME 年:%4d, 月:%2d, 日:%2d, 小时: %02d, 分钟: %02d, 秒: %02d, 星期: %s\r\n",
           g_my_lvgl_year, g_my_lvgl_month, g_my_lvgl_day,
           g_my_lvgl_hours, g_my_lvgl_minutes, g_my_lvgl_seconds, weekday_str);
		if(g_my_lvgl_hours >= 12)
		{
			m_hours = g_my_lvgl_hours - 12;
		}else
		{
			m_hours = g_my_lvgl_hours;
		}
		// 检查控件是否有效
		if (lv_obj_is_valid(meter))
		{
			// 设置时针、分针和秒针的位置
			// 时针每小时移动30度，每分钟移动0.5度
			lv_meter_set_indicator_value(meter, indic_hour, m_hours * 30 + g_my_lvgl_minutes / 2);
			// 分针每分钟移动6度
			lv_meter_set_indicator_value(meter, indic_min, g_my_lvgl_minutes * 6);
			// 秒针每秒移动6度
			lv_meter_set_indicator_value(meter, indic_sec, g_my_lvgl_seconds * 6);
		}
	}
	else if(current_screen == SCREEN_3)
	{
		sync_systime_to_mytime();
		printf("SCREEN_3 SYNC TIME 年:%4d, 月:%2d, 日:%2d, 小时: %02d, 分钟: %02d, 秒: %02d, 星期: %s\r\n",
           g_my_lvgl_year, g_my_lvgl_month, g_my_lvgl_day,
           g_my_lvgl_hours, g_my_lvgl_minutes, g_my_lvgl_seconds, weekday_str);
		/*明天和后天的日期显示*/
		static char temp_buf[50] = {0};
        strncpy(temp_buf, daily_weather[1].date + 5, 5);
        temp_buf[5] = '\0'; // 确保字符串以 '\0' 结尾
		lv_label_set_text(guider_ui.screen_3_label_mingtianriqi,temp_buf);
		memset(temp_buf,0,20);
        strncpy(temp_buf, daily_weather[2].date + 5, 5);
        temp_buf[5] = '\0'; // 确保字符串以 '\0' 结尾
		lv_label_set_text(guider_ui.screen_3_label_houtianriqi,temp_buf);

		/*今天日期和时间显示*/
		sprintf(temp_buf,"%4d-%02d-%02d",g_my_lvgl_year,g_my_lvgl_month,g_my_lvgl_day);
		lv_label_set_text(guider_ui.screen_3_label_riqi,temp_buf);
		memset(temp_buf,0,20);
		sprintf(temp_buf,"%02d-%02d",g_my_lvgl_month,g_my_lvgl_day);
		lv_label_set_text(guider_ui.screen_3_label_wenduriqi,temp_buf);
		lv_label_set_text(guider_ui.screen_3_label_jintianriqi,temp_buf);
		memset(temp_buf,0,20);
		sprintf(temp_buf,"%02d:%02d",g_my_lvgl_hours,g_my_lvgl_minutes);
		lv_label_set_text(guider_ui.screen_3_label_time,temp_buf);
		lv_label_set_text(guider_ui.screen_3_label_xingqi,weekday_str);
		lv_label_set_text(guider_ui.screen_3_label_dingwei,City_Name);

		/*天气相关显示*/
		/* 天气*/
		memset(temp_buf,0,20);
		sprintf(temp_buf,"%s",daily_weather[0].text_day);
		lv_label_set_text(guider_ui.screen_3_label_1,temp_buf);
		memset(temp_buf,0,20);
		sprintf(temp_buf,"%s°",daily_weather[0].high);
		lv_label_set_text(guider_ui.screen_3_label_gaowen,temp_buf);
		// lv_label_set_text(guider_ui.screen_3_label_wendu,temp_buf);
		memset(temp_buf,0,20);
		sprintf(temp_buf,"%s",daily_weather[0].high);
		lv_label_set_text(guider_ui.screen_3_label_wendu,temp_buf);
		memset(temp_buf,0,20);
		sprintf(temp_buf,"%s°",daily_weather[0].low);
		lv_label_set_text(guider_ui.screen_3_label_diwen,temp_buf);
		memset(temp_buf,0,20);
		sprintf(temp_buf,"%s%%",daily_weather[0].humidity);
		lv_label_set_text(guider_ui.screen_3_label_jiangshui,temp_buf);
		memset(temp_buf,0,20);
		sprintf(temp_buf,"%s",daily_weather[0].wind_speed);
		lv_label_set_text(guider_ui.screen_3_label_fengsu,temp_buf);
		/*风向*/
		// 使用 strstr 查找子字符串
		if (strstr(daily_weather[0].wind_direction, "无"))
		{
			memset(temp_buf,0,20);
			sprintf(temp_buf,"%s","无风");
			lv_label_set_text(guider_ui.screen_3_label_fengxiang,temp_buf);
		}
		else
		{
			memset(temp_buf,0,20);
			sprintf(temp_buf,"%s",daily_weather[0].wind_direction);
			lv_label_set_text(guider_ui.screen_3_label_fengxiang,temp_buf);
		}
		//test
		// memcpy(daily_weather[0].code_day,"1",2);
		// memcpy(daily_weather[1].code_day,"7",2);
		// memcpy(daily_weather[2].code_day,"11",3);
		// 缓存上次的路径
		lv_img_set_src(guider_ui.screen_3_img_tianqi, get_image_descriptor(daily_weather[0].code_day));
		lv_img_set_src(guider_ui.screen_3_img_jintian, get_image_descriptor(daily_weather[0].code_day));
		lv_img_set_src(guider_ui.screen_3_img_mingtian, get_image_descriptor(daily_weather[1].code_day));
		lv_img_set_src(guider_ui.screen_3_img_houtian, get_image_descriptor(daily_weather[2].code_day));
	}
}


void setup_scr_screen_systerm(lv_ui *ui){

	//Write codes screen_systerm
	ui->screen_systerm = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui->screen_systerm, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_systerm_main_main_default
	static lv_style_t style_screen_systerm_main_main_default;
	if (style_screen_systerm_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_main_main_default);
	else
		lv_style_init(&style_screen_systerm_main_main_default);
	lv_style_set_bg_color(&style_screen_systerm_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_screen_systerm_main_main_default, 0);
	lv_obj_add_style(ui->screen_systerm, &style_screen_systerm_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_systerm_imgbtn_weather
	ui->screen_systerm_imgbtn_weather = lv_imgbtn_create(ui->screen_systerm);
	lv_obj_set_pos(ui->screen_systerm_imgbtn_weather, 0, 10);
	lv_obj_set_size(ui->screen_systerm_imgbtn_weather, 80, 50);
	lv_obj_set_scrollbar_mode(ui->screen_systerm_imgbtn_weather, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_systerm_imgbtn_weather_main_main_default
	static lv_style_t style_screen_systerm_imgbtn_weather_main_main_default;
	if (style_screen_systerm_imgbtn_weather_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_imgbtn_weather_main_main_default);
	else
		lv_style_init(&style_screen_systerm_imgbtn_weather_main_main_default);
	lv_style_set_text_color(&style_screen_systerm_imgbtn_weather_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_align(&style_screen_systerm_imgbtn_weather_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_systerm_imgbtn_weather_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_systerm_imgbtn_weather_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_systerm_imgbtn_weather_main_main_default, 255);
	lv_obj_add_style(ui->screen_systerm_imgbtn_weather, &style_screen_systerm_imgbtn_weather_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_systerm_imgbtn_weather_main_main_pressed
	static lv_style_t style_screen_systerm_imgbtn_weather_main_main_pressed;
	if (style_screen_systerm_imgbtn_weather_main_main_pressed.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_imgbtn_weather_main_main_pressed);
	else
		lv_style_init(&style_screen_systerm_imgbtn_weather_main_main_pressed);
	lv_style_set_text_color(&style_screen_systerm_imgbtn_weather_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_text_align(&style_screen_systerm_imgbtn_weather_main_main_pressed, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_systerm_imgbtn_weather_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_systerm_imgbtn_weather_main_main_pressed, 0);
	lv_style_set_img_opa(&style_screen_systerm_imgbtn_weather_main_main_pressed, 255);
	lv_obj_add_style(ui->screen_systerm_imgbtn_weather, &style_screen_systerm_imgbtn_weather_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_systerm_imgbtn_weather_main_main_checked
	static lv_style_t style_screen_systerm_imgbtn_weather_main_main_checked;
	if (style_screen_systerm_imgbtn_weather_main_main_checked.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_imgbtn_weather_main_main_checked);
	else
		lv_style_init(&style_screen_systerm_imgbtn_weather_main_main_checked);
	lv_style_set_text_color(&style_screen_systerm_imgbtn_weather_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_text_align(&style_screen_systerm_imgbtn_weather_main_main_checked, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_systerm_imgbtn_weather_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_systerm_imgbtn_weather_main_main_checked, 0);
	lv_style_set_img_opa(&style_screen_systerm_imgbtn_weather_main_main_checked, 255);
	lv_obj_add_style(ui->screen_systerm_imgbtn_weather, &style_screen_systerm_imgbtn_weather_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_systerm_imgbtn_weather, LV_IMGBTN_STATE_RELEASED, NULL, &_app_weather_old_alpha_80x50, NULL);
	lv_obj_add_flag(ui->screen_systerm_imgbtn_weather, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_systerm_imgbtn_2048
	ui->screen_systerm_imgbtn_2048 = lv_imgbtn_create(ui->screen_systerm);
	lv_obj_set_pos(ui->screen_systerm_imgbtn_2048, 110, 10);
	lv_obj_set_size(ui->screen_systerm_imgbtn_2048, 80, 50);
	lv_obj_set_scrollbar_mode(ui->screen_systerm_imgbtn_2048, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_systerm_imgbtn_2048_main_main_default
	static lv_style_t style_screen_systerm_imgbtn_2048_main_main_default;
	if (style_screen_systerm_imgbtn_2048_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_imgbtn_2048_main_main_default);
	else
		lv_style_init(&style_screen_systerm_imgbtn_2048_main_main_default);
	lv_style_set_text_color(&style_screen_systerm_imgbtn_2048_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_align(&style_screen_systerm_imgbtn_2048_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_systerm_imgbtn_2048_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_systerm_imgbtn_2048_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_systerm_imgbtn_2048_main_main_default, 255);
	lv_obj_add_style(ui->screen_systerm_imgbtn_2048, &style_screen_systerm_imgbtn_2048_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_systerm_imgbtn_2048_main_main_pressed
	static lv_style_t style_screen_systerm_imgbtn_2048_main_main_pressed;
	if (style_screen_systerm_imgbtn_2048_main_main_pressed.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_imgbtn_2048_main_main_pressed);
	else
		lv_style_init(&style_screen_systerm_imgbtn_2048_main_main_pressed);
	lv_style_set_text_color(&style_screen_systerm_imgbtn_2048_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_text_align(&style_screen_systerm_imgbtn_2048_main_main_pressed, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_systerm_imgbtn_2048_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_systerm_imgbtn_2048_main_main_pressed, 0);
	lv_style_set_img_opa(&style_screen_systerm_imgbtn_2048_main_main_pressed, 255);
	lv_obj_add_style(ui->screen_systerm_imgbtn_2048, &style_screen_systerm_imgbtn_2048_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_systerm_imgbtn_2048_main_main_checked
	static lv_style_t style_screen_systerm_imgbtn_2048_main_main_checked;
	if (style_screen_systerm_imgbtn_2048_main_main_checked.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_imgbtn_2048_main_main_checked);
	else
		lv_style_init(&style_screen_systerm_imgbtn_2048_main_main_checked);
	lv_style_set_text_color(&style_screen_systerm_imgbtn_2048_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_text_align(&style_screen_systerm_imgbtn_2048_main_main_checked, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_systerm_imgbtn_2048_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_systerm_imgbtn_2048_main_main_checked, 0);
	lv_style_set_img_opa(&style_screen_systerm_imgbtn_2048_main_main_checked, 255);
	lv_obj_add_style(ui->screen_systerm_imgbtn_2048, &style_screen_systerm_imgbtn_2048_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_systerm_imgbtn_2048, LV_IMGBTN_STATE_RELEASED, NULL, &_app_2048_alpha_80x50, NULL);
	lv_obj_add_flag(ui->screen_systerm_imgbtn_2048, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_systerm_imgbtn_bili
	ui->screen_systerm_imgbtn_bili = lv_imgbtn_create(ui->screen_systerm);
	lv_obj_set_pos(ui->screen_systerm_imgbtn_bili, 220, 10);
	lv_obj_set_size(ui->screen_systerm_imgbtn_bili, 80, 50);
	lv_obj_set_scrollbar_mode(ui->screen_systerm_imgbtn_bili, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_systerm_imgbtn_bili_main_main_default
	static lv_style_t style_screen_systerm_imgbtn_bili_main_main_default;
	if (style_screen_systerm_imgbtn_bili_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_imgbtn_bili_main_main_default);
	else
		lv_style_init(&style_screen_systerm_imgbtn_bili_main_main_default);
	lv_style_set_text_color(&style_screen_systerm_imgbtn_bili_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_align(&style_screen_systerm_imgbtn_bili_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_systerm_imgbtn_bili_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_systerm_imgbtn_bili_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_systerm_imgbtn_bili_main_main_default, 255);
	lv_obj_add_style(ui->screen_systerm_imgbtn_bili, &style_screen_systerm_imgbtn_bili_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_systerm_imgbtn_bili_main_main_pressed
	static lv_style_t style_screen_systerm_imgbtn_bili_main_main_pressed;
	if (style_screen_systerm_imgbtn_bili_main_main_pressed.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_imgbtn_bili_main_main_pressed);
	else
		lv_style_init(&style_screen_systerm_imgbtn_bili_main_main_pressed);
	lv_style_set_text_color(&style_screen_systerm_imgbtn_bili_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_text_align(&style_screen_systerm_imgbtn_bili_main_main_pressed, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_systerm_imgbtn_bili_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_systerm_imgbtn_bili_main_main_pressed, 0);
	lv_style_set_img_opa(&style_screen_systerm_imgbtn_bili_main_main_pressed, 255);
	lv_obj_add_style(ui->screen_systerm_imgbtn_bili, &style_screen_systerm_imgbtn_bili_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_systerm_imgbtn_bili_main_main_checked
	static lv_style_t style_screen_systerm_imgbtn_bili_main_main_checked;
	if (style_screen_systerm_imgbtn_bili_main_main_checked.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_imgbtn_bili_main_main_checked);
	else
		lv_style_init(&style_screen_systerm_imgbtn_bili_main_main_checked);
	lv_style_set_text_color(&style_screen_systerm_imgbtn_bili_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_text_align(&style_screen_systerm_imgbtn_bili_main_main_checked, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_systerm_imgbtn_bili_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_systerm_imgbtn_bili_main_main_checked, 0);
	lv_style_set_img_opa(&style_screen_systerm_imgbtn_bili_main_main_checked, 255);
	lv_obj_add_style(ui->screen_systerm_imgbtn_bili, &style_screen_systerm_imgbtn_bili_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_systerm_imgbtn_bili, LV_IMGBTN_STATE_RELEASED, NULL, &_app_bilibili_alpha_80x50, NULL);
	lv_obj_add_flag(ui->screen_systerm_imgbtn_bili, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_systerm_imgbtn_sd
	ui->screen_systerm_imgbtn_sd = lv_imgbtn_create(ui->screen_systerm);
	lv_obj_set_pos(ui->screen_systerm_imgbtn_sd, 0, 90);
	lv_obj_set_size(ui->screen_systerm_imgbtn_sd, 80, 50);
	lv_obj_set_scrollbar_mode(ui->screen_systerm_imgbtn_sd, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_systerm_imgbtn_sd_main_main_default
	static lv_style_t style_screen_systerm_imgbtn_sd_main_main_default;
	if (style_screen_systerm_imgbtn_sd_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_imgbtn_sd_main_main_default);
	else
		lv_style_init(&style_screen_systerm_imgbtn_sd_main_main_default);
	lv_style_set_text_color(&style_screen_systerm_imgbtn_sd_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_align(&style_screen_systerm_imgbtn_sd_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_systerm_imgbtn_sd_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_systerm_imgbtn_sd_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_systerm_imgbtn_sd_main_main_default, 255);
	lv_obj_add_style(ui->screen_systerm_imgbtn_sd, &style_screen_systerm_imgbtn_sd_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_systerm_imgbtn_sd_main_main_pressed
	static lv_style_t style_screen_systerm_imgbtn_sd_main_main_pressed;
	if (style_screen_systerm_imgbtn_sd_main_main_pressed.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_imgbtn_sd_main_main_pressed);
	else
		lv_style_init(&style_screen_systerm_imgbtn_sd_main_main_pressed);
	lv_style_set_text_color(&style_screen_systerm_imgbtn_sd_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_text_align(&style_screen_systerm_imgbtn_sd_main_main_pressed, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_systerm_imgbtn_sd_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_systerm_imgbtn_sd_main_main_pressed, 0);
	lv_style_set_img_opa(&style_screen_systerm_imgbtn_sd_main_main_pressed, 255);
	lv_obj_add_style(ui->screen_systerm_imgbtn_sd, &style_screen_systerm_imgbtn_sd_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_systerm_imgbtn_sd_main_main_checked
	static lv_style_t style_screen_systerm_imgbtn_sd_main_main_checked;
	if (style_screen_systerm_imgbtn_sd_main_main_checked.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_imgbtn_sd_main_main_checked);
	else
		lv_style_init(&style_screen_systerm_imgbtn_sd_main_main_checked);
	lv_style_set_text_color(&style_screen_systerm_imgbtn_sd_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_text_align(&style_screen_systerm_imgbtn_sd_main_main_checked, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_systerm_imgbtn_sd_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_systerm_imgbtn_sd_main_main_checked, 0);
	lv_style_set_img_opa(&style_screen_systerm_imgbtn_sd_main_main_checked, 255);
	lv_obj_add_style(ui->screen_systerm_imgbtn_sd, &style_screen_systerm_imgbtn_sd_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_systerm_imgbtn_sd, LV_IMGBTN_STATE_RELEASED, NULL, &_app_file_manager_alpha_80x50, NULL);
	lv_obj_add_flag(ui->screen_systerm_imgbtn_sd, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_systerm_label_4
	ui->screen_systerm_label_4 = lv_label_create(ui->screen_systerm);
	lv_obj_set_pos(ui->screen_systerm_label_4, 15, 145);
	lv_obj_set_size(ui->screen_systerm_label_4, 50, 20);
	lv_obj_set_scrollbar_mode(ui->screen_systerm_label_4, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_systerm_label_4, "SD");
	lv_label_set_long_mode(ui->screen_systerm_label_4, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_systerm_label_4_main_main_default
	static lv_style_t style_screen_systerm_label_4_main_main_default;
	if (style_screen_systerm_label_4_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_label_4_main_main_default);
	else
		lv_style_init(&style_screen_systerm_label_4_main_main_default);
	lv_style_set_radius(&style_screen_systerm_label_4_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_systerm_label_4_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_systerm_label_4_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_systerm_label_4_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_systerm_label_4_main_main_default, 0);
	lv_style_set_text_color(&style_screen_systerm_label_4_main_main_default, lv_color_make(0x41, 0xb2, 0xb4));
	lv_style_set_text_font(&style_screen_systerm_label_4_main_main_default, &lv_font_Acme_Regular_20);
	lv_style_set_text_letter_space(&style_screen_systerm_label_4_main_main_default, 1);
	lv_style_set_text_line_space(&style_screen_systerm_label_4_main_main_default, 0);
	lv_style_set_text_align(&style_screen_systerm_label_4_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_systerm_label_4_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_systerm_label_4_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_systerm_label_4_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_systerm_label_4_main_main_default, 0);
	lv_obj_add_style(ui->screen_systerm_label_4, &style_screen_systerm_label_4_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_systerm_imgbtn_moive
	ui->screen_systerm_imgbtn_moive = lv_imgbtn_create(ui->screen_systerm);
	lv_obj_set_pos(ui->screen_systerm_imgbtn_moive, 110, 90);
	lv_obj_set_size(ui->screen_systerm_imgbtn_moive, 80, 50);
	lv_obj_set_scrollbar_mode(ui->screen_systerm_imgbtn_moive, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_systerm_imgbtn_moive_main_main_default
	static lv_style_t style_screen_systerm_imgbtn_moive_main_main_default;
	if (style_screen_systerm_imgbtn_moive_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_imgbtn_moive_main_main_default);
	else
		lv_style_init(&style_screen_systerm_imgbtn_moive_main_main_default);
	lv_style_set_text_color(&style_screen_systerm_imgbtn_moive_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_align(&style_screen_systerm_imgbtn_moive_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_systerm_imgbtn_moive_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_systerm_imgbtn_moive_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_systerm_imgbtn_moive_main_main_default, 255);
	lv_obj_add_style(ui->screen_systerm_imgbtn_moive, &style_screen_systerm_imgbtn_moive_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_systerm_imgbtn_moive_main_main_pressed
	static lv_style_t style_screen_systerm_imgbtn_moive_main_main_pressed;
	if (style_screen_systerm_imgbtn_moive_main_main_pressed.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_imgbtn_moive_main_main_pressed);
	else
		lv_style_init(&style_screen_systerm_imgbtn_moive_main_main_pressed);
	lv_style_set_text_color(&style_screen_systerm_imgbtn_moive_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_text_align(&style_screen_systerm_imgbtn_moive_main_main_pressed, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_systerm_imgbtn_moive_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_systerm_imgbtn_moive_main_main_pressed, 0);
	lv_style_set_img_opa(&style_screen_systerm_imgbtn_moive_main_main_pressed, 255);
	lv_obj_add_style(ui->screen_systerm_imgbtn_moive, &style_screen_systerm_imgbtn_moive_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_systerm_imgbtn_moive_main_main_checked
	static lv_style_t style_screen_systerm_imgbtn_moive_main_main_checked;
	if (style_screen_systerm_imgbtn_moive_main_main_checked.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_imgbtn_moive_main_main_checked);
	else
		lv_style_init(&style_screen_systerm_imgbtn_moive_main_main_checked);
	lv_style_set_text_color(&style_screen_systerm_imgbtn_moive_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_text_align(&style_screen_systerm_imgbtn_moive_main_main_checked, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_systerm_imgbtn_moive_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_systerm_imgbtn_moive_main_main_checked, 0);
	lv_style_set_img_opa(&style_screen_systerm_imgbtn_moive_main_main_checked, 255);
	lv_obj_add_style(ui->screen_systerm_imgbtn_moive, &style_screen_systerm_imgbtn_moive_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_systerm_imgbtn_moive, LV_IMGBTN_STATE_RELEASED, NULL, &_app_movie_alpha_80x50, NULL);
	lv_obj_add_flag(ui->screen_systerm_imgbtn_moive, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_systerm_imgbtn_server
	ui->screen_systerm_imgbtn_server = lv_imgbtn_create(ui->screen_systerm);
	lv_obj_set_pos(ui->screen_systerm_imgbtn_server, 220, 90);
	lv_obj_set_size(ui->screen_systerm_imgbtn_server, 80, 50);
	lv_obj_set_scrollbar_mode(ui->screen_systerm_imgbtn_server, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_systerm_imgbtn_server_main_main_default
	static lv_style_t style_screen_systerm_imgbtn_server_main_main_default;
	if (style_screen_systerm_imgbtn_server_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_imgbtn_server_main_main_default);
	else
		lv_style_init(&style_screen_systerm_imgbtn_server_main_main_default);
	lv_style_set_text_color(&style_screen_systerm_imgbtn_server_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_align(&style_screen_systerm_imgbtn_server_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_systerm_imgbtn_server_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_systerm_imgbtn_server_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_systerm_imgbtn_server_main_main_default, 255);
	lv_obj_add_style(ui->screen_systerm_imgbtn_server, &style_screen_systerm_imgbtn_server_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_systerm_imgbtn_server_main_main_pressed
	static lv_style_t style_screen_systerm_imgbtn_server_main_main_pressed;
	if (style_screen_systerm_imgbtn_server_main_main_pressed.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_imgbtn_server_main_main_pressed);
	else
		lv_style_init(&style_screen_systerm_imgbtn_server_main_main_pressed);
	lv_style_set_text_color(&style_screen_systerm_imgbtn_server_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_text_align(&style_screen_systerm_imgbtn_server_main_main_pressed, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_systerm_imgbtn_server_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_systerm_imgbtn_server_main_main_pressed, 0);
	lv_style_set_img_opa(&style_screen_systerm_imgbtn_server_main_main_pressed, 255);
	lv_obj_add_style(ui->screen_systerm_imgbtn_server, &style_screen_systerm_imgbtn_server_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_systerm_imgbtn_server_main_main_checked
	static lv_style_t style_screen_systerm_imgbtn_server_main_main_checked;
	if (style_screen_systerm_imgbtn_server_main_main_checked.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_imgbtn_server_main_main_checked);
	else
		lv_style_init(&style_screen_systerm_imgbtn_server_main_main_checked);
	lv_style_set_text_color(&style_screen_systerm_imgbtn_server_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_text_align(&style_screen_systerm_imgbtn_server_main_main_checked, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_systerm_imgbtn_server_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_systerm_imgbtn_server_main_main_checked, 0);
	lv_style_set_img_opa(&style_screen_systerm_imgbtn_server_main_main_checked, 255);
	lv_obj_add_style(ui->screen_systerm_imgbtn_server, &style_screen_systerm_imgbtn_server_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_systerm_imgbtn_server, LV_IMGBTN_STATE_RELEASED, NULL, &_app_server_alpha_80x50, NULL);
	lv_obj_add_flag(ui->screen_systerm_imgbtn_server, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_systerm_imgbtn_resolve
	ui->screen_systerm_imgbtn_resolve = lv_imgbtn_create(ui->screen_systerm);
	lv_obj_set_pos(ui->screen_systerm_imgbtn_resolve, 5, 165);
	lv_obj_set_size(ui->screen_systerm_imgbtn_resolve, 80, 50);
	lv_obj_set_scrollbar_mode(ui->screen_systerm_imgbtn_resolve, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_systerm_imgbtn_resolve_main_main_default
	static lv_style_t style_screen_systerm_imgbtn_resolve_main_main_default;
	if (style_screen_systerm_imgbtn_resolve_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_imgbtn_resolve_main_main_default);
	else
		lv_style_init(&style_screen_systerm_imgbtn_resolve_main_main_default);
	lv_style_set_text_color(&style_screen_systerm_imgbtn_resolve_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_align(&style_screen_systerm_imgbtn_resolve_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_systerm_imgbtn_resolve_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_systerm_imgbtn_resolve_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_systerm_imgbtn_resolve_main_main_default, 255);
	lv_obj_add_style(ui->screen_systerm_imgbtn_resolve, &style_screen_systerm_imgbtn_resolve_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_systerm_imgbtn_resolve_main_main_pressed
	static lv_style_t style_screen_systerm_imgbtn_resolve_main_main_pressed;
	if (style_screen_systerm_imgbtn_resolve_main_main_pressed.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_imgbtn_resolve_main_main_pressed);
	else
		lv_style_init(&style_screen_systerm_imgbtn_resolve_main_main_pressed);
	lv_style_set_text_color(&style_screen_systerm_imgbtn_resolve_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_text_align(&style_screen_systerm_imgbtn_resolve_main_main_pressed, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_systerm_imgbtn_resolve_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_systerm_imgbtn_resolve_main_main_pressed, 0);
	lv_style_set_img_opa(&style_screen_systerm_imgbtn_resolve_main_main_pressed, 255);
	lv_obj_add_style(ui->screen_systerm_imgbtn_resolve, &style_screen_systerm_imgbtn_resolve_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_systerm_imgbtn_resolve_main_main_checked
	static lv_style_t style_screen_systerm_imgbtn_resolve_main_main_checked;
	if (style_screen_systerm_imgbtn_resolve_main_main_checked.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_imgbtn_resolve_main_main_checked);
	else
		lv_style_init(&style_screen_systerm_imgbtn_resolve_main_main_checked);
	lv_style_set_text_color(&style_screen_systerm_imgbtn_resolve_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_text_align(&style_screen_systerm_imgbtn_resolve_main_main_checked, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_systerm_imgbtn_resolve_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_systerm_imgbtn_resolve_main_main_checked, 0);
	lv_style_set_img_opa(&style_screen_systerm_imgbtn_resolve_main_main_checked, 255);
	lv_obj_add_style(ui->screen_systerm_imgbtn_resolve, &style_screen_systerm_imgbtn_resolve_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_systerm_imgbtn_resolve, LV_IMGBTN_STATE_RELEASED, NULL, &_app_thought_alpha_80x50, NULL);
	lv_obj_add_flag(ui->screen_systerm_imgbtn_resolve, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_systerm_label_7
	ui->screen_systerm_label_7 = lv_label_create(ui->screen_systerm);
	lv_obj_set_pos(ui->screen_systerm_label_7, 0, 220);
	lv_obj_set_size(ui->screen_systerm_label_7, 100, 20);
	lv_obj_set_scrollbar_mode(ui->screen_systerm_label_7, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_systerm_label_7, "Thought");
	lv_label_set_long_mode(ui->screen_systerm_label_7, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_systerm_label_7_main_main_default
	static lv_style_t style_screen_systerm_label_7_main_main_default;
	if (style_screen_systerm_label_7_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_label_7_main_main_default);
	else
		lv_style_init(&style_screen_systerm_label_7_main_main_default);
	lv_style_set_radius(&style_screen_systerm_label_7_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_systerm_label_7_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_systerm_label_7_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_systerm_label_7_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_systerm_label_7_main_main_default, 0);
	lv_style_set_text_color(&style_screen_systerm_label_7_main_main_default, lv_color_make(0x3b, 0x88, 0x9b));
	lv_style_set_text_font(&style_screen_systerm_label_7_main_main_default, &lv_font_Acme_Regular_20);
	lv_style_set_text_letter_space(&style_screen_systerm_label_7_main_main_default, 1);
	lv_style_set_text_line_space(&style_screen_systerm_label_7_main_main_default, 0);
	lv_style_set_text_align(&style_screen_systerm_label_7_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_systerm_label_7_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_systerm_label_7_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_systerm_label_7_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_systerm_label_7_main_main_default, 0);
	lv_obj_add_style(ui->screen_systerm_label_7, &style_screen_systerm_label_7_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_systerm_label_1
	ui->screen_systerm_label_1 = lv_label_create(ui->screen_systerm);
	lv_obj_set_pos(ui->screen_systerm_label_1, 0, 70);
	lv_obj_set_size(ui->screen_systerm_label_1, 100, 20);
	lv_obj_set_scrollbar_mode(ui->screen_systerm_label_1, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_systerm_label_1, "Weather");
	lv_label_set_long_mode(ui->screen_systerm_label_1, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_systerm_label_1_main_main_default
	static lv_style_t style_screen_systerm_label_1_main_main_default;
	if (style_screen_systerm_label_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_label_1_main_main_default);
	else
		lv_style_init(&style_screen_systerm_label_1_main_main_default);
	lv_style_set_radius(&style_screen_systerm_label_1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_systerm_label_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_systerm_label_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_systerm_label_1_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_systerm_label_1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_systerm_label_1_main_main_default, lv_color_make(0x4b, 0xa9, 0xaa));
	lv_style_set_text_font(&style_screen_systerm_label_1_main_main_default, &lv_font_Acme_Regular_20);
	lv_style_set_text_letter_space(&style_screen_systerm_label_1_main_main_default, 1);
	lv_style_set_text_line_space(&style_screen_systerm_label_1_main_main_default, 0);
	lv_style_set_text_align(&style_screen_systerm_label_1_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_systerm_label_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_systerm_label_1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_systerm_label_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_systerm_label_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_systerm_label_1, &style_screen_systerm_label_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_systerm_imgbtn_2050
	ui->screen_systerm_imgbtn_2050 = lv_imgbtn_create(ui->screen_systerm);
	lv_obj_set_pos(ui->screen_systerm_imgbtn_2050, 110, 165);
	lv_obj_set_size(ui->screen_systerm_imgbtn_2050, 80, 50);
	lv_obj_set_scrollbar_mode(ui->screen_systerm_imgbtn_2050, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_systerm_imgbtn_2050_main_main_default
	static lv_style_t style_screen_systerm_imgbtn_2050_main_main_default;
	if (style_screen_systerm_imgbtn_2050_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_imgbtn_2050_main_main_default);
	else
		lv_style_init(&style_screen_systerm_imgbtn_2050_main_main_default);
	lv_style_set_text_color(&style_screen_systerm_imgbtn_2050_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_align(&style_screen_systerm_imgbtn_2050_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_systerm_imgbtn_2050_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_systerm_imgbtn_2050_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_systerm_imgbtn_2050_main_main_default, 255);
	lv_obj_add_style(ui->screen_systerm_imgbtn_2050, &style_screen_systerm_imgbtn_2050_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_systerm_imgbtn_2050_main_main_pressed
	static lv_style_t style_screen_systerm_imgbtn_2050_main_main_pressed;
	if (style_screen_systerm_imgbtn_2050_main_main_pressed.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_imgbtn_2050_main_main_pressed);
	else
		lv_style_init(&style_screen_systerm_imgbtn_2050_main_main_pressed);
	lv_style_set_text_color(&style_screen_systerm_imgbtn_2050_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_text_align(&style_screen_systerm_imgbtn_2050_main_main_pressed, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_systerm_imgbtn_2050_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_systerm_imgbtn_2050_main_main_pressed, 0);
	lv_style_set_img_opa(&style_screen_systerm_imgbtn_2050_main_main_pressed, 255);
	lv_obj_add_style(ui->screen_systerm_imgbtn_2050, &style_screen_systerm_imgbtn_2050_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_systerm_imgbtn_2050_main_main_checked
	static lv_style_t style_screen_systerm_imgbtn_2050_main_main_checked;
	if (style_screen_systerm_imgbtn_2050_main_main_checked.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_imgbtn_2050_main_main_checked);
	else
		lv_style_init(&style_screen_systerm_imgbtn_2050_main_main_checked);
	lv_style_set_text_color(&style_screen_systerm_imgbtn_2050_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_text_align(&style_screen_systerm_imgbtn_2050_main_main_checked, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_systerm_imgbtn_2050_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_systerm_imgbtn_2050_main_main_checked, 0);
	lv_style_set_img_opa(&style_screen_systerm_imgbtn_2050_main_main_checked, 255);
	lv_obj_add_style(ui->screen_systerm_imgbtn_2050, &style_screen_systerm_imgbtn_2050_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_systerm_imgbtn_2050, LV_IMGBTN_STATE_RELEASED, NULL, &_app_picture_alpha_80x50, NULL);
	lv_obj_add_flag(ui->screen_systerm_imgbtn_2050, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_systerm_label_2
	ui->screen_systerm_label_2 = lv_label_create(ui->screen_systerm);
	lv_obj_set_pos(ui->screen_systerm_label_2, 120, 70);
	lv_obj_set_size(ui->screen_systerm_label_2, 60, 20);
	lv_obj_set_scrollbar_mode(ui->screen_systerm_label_2, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_systerm_label_2, "2048");
	lv_label_set_long_mode(ui->screen_systerm_label_2, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_systerm_label_2_main_main_default
	static lv_style_t style_screen_systerm_label_2_main_main_default;
	if (style_screen_systerm_label_2_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_label_2_main_main_default);
	else
		lv_style_init(&style_screen_systerm_label_2_main_main_default);
	lv_style_set_radius(&style_screen_systerm_label_2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_systerm_label_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_systerm_label_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_systerm_label_2_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_systerm_label_2_main_main_default, 0);
	lv_style_set_text_color(&style_screen_systerm_label_2_main_main_default, lv_color_make(0x3a, 0xb6, 0xb4));
	lv_style_set_text_font(&style_screen_systerm_label_2_main_main_default, &lv_font_Acme_Regular_20);
	lv_style_set_text_letter_space(&style_screen_systerm_label_2_main_main_default, 1);
	lv_style_set_text_line_space(&style_screen_systerm_label_2_main_main_default, 0);
	lv_style_set_text_align(&style_screen_systerm_label_2_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_systerm_label_2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_systerm_label_2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_systerm_label_2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_systerm_label_2_main_main_default, 0);
	lv_obj_add_style(ui->screen_systerm_label_2, &style_screen_systerm_label_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_systerm_label_3
	ui->screen_systerm_label_3 = lv_label_create(ui->screen_systerm);
	lv_obj_set_pos(ui->screen_systerm_label_3, 220, 70);
	lv_obj_set_size(ui->screen_systerm_label_3, 80, 20);
	lv_obj_set_scrollbar_mode(ui->screen_systerm_label_3, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_systerm_label_3, "Bilibili");
	lv_label_set_long_mode(ui->screen_systerm_label_3, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_systerm_label_3_main_main_default
	static lv_style_t style_screen_systerm_label_3_main_main_default;
	if (style_screen_systerm_label_3_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_label_3_main_main_default);
	else
		lv_style_init(&style_screen_systerm_label_3_main_main_default);
	lv_style_set_radius(&style_screen_systerm_label_3_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_systerm_label_3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_systerm_label_3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_systerm_label_3_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_systerm_label_3_main_main_default, 0);
	lv_style_set_text_color(&style_screen_systerm_label_3_main_main_default, lv_color_make(0x2f, 0x95, 0xa2));
	lv_style_set_text_font(&style_screen_systerm_label_3_main_main_default, &lv_font_Acme_Regular_20);
	lv_style_set_text_letter_space(&style_screen_systerm_label_3_main_main_default, 1);
	lv_style_set_text_line_space(&style_screen_systerm_label_3_main_main_default, 0);
	lv_style_set_text_align(&style_screen_systerm_label_3_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_systerm_label_3_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_systerm_label_3_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_systerm_label_3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_systerm_label_3_main_main_default, 0);
	lv_obj_add_style(ui->screen_systerm_label_3, &style_screen_systerm_label_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_systerm_label_5
	ui->screen_systerm_label_5 = lv_label_create(ui->screen_systerm);
	lv_obj_set_pos(ui->screen_systerm_label_5, 115, 145);
	lv_obj_set_size(ui->screen_systerm_label_5, 70, 20);
	lv_obj_set_scrollbar_mode(ui->screen_systerm_label_5, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_systerm_label_5, "Movie");
	lv_label_set_long_mode(ui->screen_systerm_label_5, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_systerm_label_5_main_main_default
	static lv_style_t style_screen_systerm_label_5_main_main_default;
	if (style_screen_systerm_label_5_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_label_5_main_main_default);
	else
		lv_style_init(&style_screen_systerm_label_5_main_main_default);
	lv_style_set_radius(&style_screen_systerm_label_5_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_systerm_label_5_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_systerm_label_5_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_systerm_label_5_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_systerm_label_5_main_main_default, 0);
	lv_style_set_text_color(&style_screen_systerm_label_5_main_main_default, lv_color_make(0x34, 0xa8, 0xb7));
	lv_style_set_text_font(&style_screen_systerm_label_5_main_main_default, &lv_font_Acme_Regular_20);
	lv_style_set_text_letter_space(&style_screen_systerm_label_5_main_main_default, 1);
	lv_style_set_text_line_space(&style_screen_systerm_label_5_main_main_default, 0);
	lv_style_set_text_align(&style_screen_systerm_label_5_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_systerm_label_5_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_systerm_label_5_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_systerm_label_5_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_systerm_label_5_main_main_default, 0);
	lv_obj_add_style(ui->screen_systerm_label_5, &style_screen_systerm_label_5_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_systerm_label_6
	ui->screen_systerm_label_6 = lv_label_create(ui->screen_systerm);
	lv_obj_set_pos(ui->screen_systerm_label_6, 210, 145);
	lv_obj_set_size(ui->screen_systerm_label_6, 100, 20);
	lv_obj_set_scrollbar_mode(ui->screen_systerm_label_6, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_systerm_label_6, "SERVER");
	lv_label_set_long_mode(ui->screen_systerm_label_6, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_systerm_label_6_main_main_default
	static lv_style_t style_screen_systerm_label_6_main_main_default;
	if (style_screen_systerm_label_6_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_label_6_main_main_default);
	else
		lv_style_init(&style_screen_systerm_label_6_main_main_default);
	lv_style_set_radius(&style_screen_systerm_label_6_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_systerm_label_6_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_systerm_label_6_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_systerm_label_6_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_systerm_label_6_main_main_default, 0);
	lv_style_set_text_color(&style_screen_systerm_label_6_main_main_default, lv_color_make(0x2f, 0xa2, 0x9a));
	lv_style_set_text_font(&style_screen_systerm_label_6_main_main_default, &lv_font_Acme_Regular_20);
	lv_style_set_text_letter_space(&style_screen_systerm_label_6_main_main_default, 1);
	lv_style_set_text_line_space(&style_screen_systerm_label_6_main_main_default, 0);
	lv_style_set_text_align(&style_screen_systerm_label_6_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_systerm_label_6_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_systerm_label_6_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_systerm_label_6_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_systerm_label_6_main_main_default, 0);
	lv_obj_add_style(ui->screen_systerm_label_6, &style_screen_systerm_label_6_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_systerm_label_8
	ui->screen_systerm_label_8 = lv_label_create(ui->screen_systerm);
	lv_obj_set_pos(ui->screen_systerm_label_8, 100, 220);
	lv_obj_set_size(ui->screen_systerm_label_8, 100, 20);
	lv_obj_set_scrollbar_mode(ui->screen_systerm_label_8, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_systerm_label_8, "Picture");
	lv_label_set_long_mode(ui->screen_systerm_label_8, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_systerm_label_8_main_main_default
	static lv_style_t style_screen_systerm_label_8_main_main_default;
	if (style_screen_systerm_label_8_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_systerm_label_8_main_main_default);
	else
		lv_style_init(&style_screen_systerm_label_8_main_main_default);
	lv_style_set_radius(&style_screen_systerm_label_8_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_systerm_label_8_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_systerm_label_8_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_systerm_label_8_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_systerm_label_8_main_main_default, 0);
	lv_style_set_text_color(&style_screen_systerm_label_8_main_main_default, lv_color_make(0x31, 0x86, 0x87));
	lv_style_set_text_font(&style_screen_systerm_label_8_main_main_default, &lv_font_Acme_Regular_20);
	lv_style_set_text_letter_space(&style_screen_systerm_label_8_main_main_default, 1);
	lv_style_set_text_line_space(&style_screen_systerm_label_8_main_main_default, 0);
	lv_style_set_text_align(&style_screen_systerm_label_8_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_systerm_label_8_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_systerm_label_8_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_systerm_label_8_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_systerm_label_8_main_main_default, 0);
	lv_obj_add_style(ui->screen_systerm_label_8, &style_screen_systerm_label_8_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    // 创建定时器
    static bool screen_systerm_timer_enabled = false;
    if (!screen_systerm_timer_enabled) {
        lv_timer_create(screen_systerm_timer, 1000, NULL);  // 每秒更新一次时间
        screen_systerm_timer_enabled = true;
    }
	//Init events for screen
	events_init_screen_systerm(ui);
}