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


// 创建一个表盘对象
lv_obj_t *meter;

// 声明时针、分针和秒针的指针变量
static lv_meter_indicator_t *indic_hour = NULL;
static lv_meter_indicator_t *indic_min = NULL;
static lv_meter_indicator_t *indic_sec = NULL;

// 初始时间：3点20分50秒
int screen_2_analog_clock_hour_value = 0;
int screen_2_analog_clock_min_value = 0;
int screen_2_analog_clock_sec_value = 0;

// 定时器回调函数，用于更新时间
void screen_2_analog_clock_timer(lv_timer_t *timer)
{
	if(current_screen == SCREEN_2)
	{
		uint8_t m_hours = 0;
		// 更新时间
		sync_systime_to_mytime();
		// printf("mytime : 小时: %02d, 分钟: %02d, 秒: %02d", g_my_lvgl_hours, g_my_lvgl_minutes, g_my_lvgl_seconds);
		if(g_my_lvgl_hours >= 12)
		{
			m_hours = g_my_lvgl_hours - 12;
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
		char temp_buf[20] = {0};
		sprintf(temp_buf,"%4d-%02d-%02d",g_my_lvgl_year,g_my_lvgl_month,g_my_lvgl_day);
		lv_label_set_text(guider_ui.screen_3_label_riqi,temp_buf);
		memset(temp_buf,0,20);
		sprintf(temp_buf,"%02d-%02d",g_my_lvgl_month,g_my_lvgl_day);
		lv_label_set_text(guider_ui.screen_3_label_wenduriqi,temp_buf);
		memset(temp_buf,0,20);
		sprintf(temp_buf,"%02d:%02d",g_my_lvgl_hours,g_my_lvgl_minutes);
		lv_label_set_text(guider_ui.screen_3_label_time,temp_buf);
		lv_label_set_text(guider_ui.screen_3_label_xingqi,weekday_str);
		lv_label_set_text(guider_ui.screen_3_label_dingwei,City_Name);
	}
}

#include "lvgl/lvgl.h"

void create_analog_clock(lv_obj_t *parent) {
    // 创建一个表盘对象
    meter = lv_meter_create(parent);
    lv_obj_set_size(meter, 200, 200); // 设置表盘大小
    lv_obj_center(meter); // 居中显示

    // 设置表盘背景颜色
    lv_obj_set_style_bg_color(meter, lv_color_hex(0x333333), 0);
    lv_obj_set_style_bg_opa(meter, LV_OPA_COVER, 0);

    // 添加刻度线
    lv_meter_scale_t *scale = lv_meter_add_scale(meter); // 创建一个刻度系统

    // 设置刻度范围和角度
    lv_meter_set_scale_range(meter, scale, 0, 360, 360, 270); // 范围 0-360 度，起始角度 270 度（12 点方向）

    // 设置主要刻度（每小时一个大刻度）并添加标签
    lv_meter_set_scale_ticks(meter, scale, 12, 2, 20, lv_color_white()); // 12 个主要刻度，宽度为 2，长度为 10，颜色为白色
	// 设置次要刻度（每分钟一个小刻度）
    lv_meter_set_scale_ticks(meter, scale, 60, 1, 5, lv_color_white()); // 60 个次要刻度，宽度为 1，长度为 5，颜色为白色
    static const char *labels[] = {"12", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};
    for (int i = 0; i < 12; i++) {
        lv_obj_t *label = lv_label_create(meter); // 创建标签
        lv_label_set_text(label, labels[i]); // 设置标签文本
        lv_obj_set_style_text_color(label, lv_color_white(), 0); // 设置文本颜色为白色

        // 计算标签位置
        int angle = i * 30; // 每个标签间隔 30 度
        if (angle >= 360) angle -= 360; // 确保角度在 0-360 范围内
        int radius = 70; // 标签距离表盘中心的半径
        int x = radius * lv_trigo_sin(angle) / LV_TRIGO_SIN_MAX; // 计算 x 坐标
        int y = -radius * lv_trigo_cos(angle) / LV_TRIGO_SIN_MAX; // 计算 y 坐标

        // 设置标签位置
        lv_obj_align(label, LV_ALIGN_CENTER, x, y);
    }

    // 添加时针
	//最后一个参数越大，不算符号，越短
    indic_hour = lv_meter_add_needle_line(meter, scale, 4, lv_color_hex(0xFFA500), -50);
    // 添加分针
    indic_min = lv_meter_add_needle_line(meter, scale, 3, lv_color_hex(0x00FF00), -30);
    // 添加秒针
    indic_sec = lv_meter_add_needle_line(meter, scale, 2, lv_color_hex(0xFF0000), -20);


    // 设置指针的初始值（示例时间：3:45:30）
    lv_meter_set_indicator_value(meter, indic_hour, 3 * 30 + 45 / 2); // 时针
    lv_meter_set_indicator_value(meter, indic_min, 20 * 6);          // 分针
    lv_meter_set_indicator_value(meter, indic_sec, 30 * 6);          // 秒针

    // 添加中心点装饰
	/*
		lv_obj_create：创建一个 LVGL 对象。
		lv_obj_set_size：设置对象的大小。
		lv_obj_set_style_bg_color：设置对象的背景颜色。
		lv_obj_set_style_bg_opa：设置对象的背景透明度。
		lv_obj_set_style_radius：设置对象的圆角半径。
		lv_obj_align：将对象对齐到指定位置。
	*/
    lv_obj_t *center = lv_obj_create(meter);
    lv_obj_set_size(center, 10, 10);
    lv_obj_set_style_bg_color(center, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_bg_opa(center, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(center, LV_RADIUS_CIRCLE, 0);
    lv_obj_align(center, LV_ALIGN_CENTER, 0, 0);
}

void setup_scr_screen_2(lv_ui *ui)
{
    // 创建屏幕
    ui->screen_2 = lv_obj_create(NULL);
    lv_obj_set_scrollbar_mode(ui->screen_2, LV_SCROLLBAR_MODE_OFF);

    // 设置屏幕背景颜色
    static lv_style_t style_screen_2_main_main_default;
    lv_style_init(&style_screen_2_main_main_default);
    lv_style_set_bg_color(&style_screen_2_main_main_default, lv_color_make(0x05, 0x0d, 0x48));  // 深蓝色背景
    lv_style_set_bg_opa(&style_screen_2_main_main_default, 158);  // 背景透明度
    lv_obj_add_style(ui->screen_2, &style_screen_2_main_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    // 创建返回按钮
    ui->screen_2_back = lv_btn_create(ui->screen_2);
    lv_obj_set_pos(ui->screen_2_back, 0, 0);  // 设置按钮位置
    lv_obj_set_size(ui->screen_2_back, 50, 30);  // 设置按钮大小

    // 设置返回按钮样式
    static lv_style_t style_screen_2_back_main_main_default;
    lv_style_init(&style_screen_2_back_main_main_default);
    lv_style_set_radius(&style_screen_2_back_main_main_default, 5);  // 圆角半径
    lv_style_set_bg_color(&style_screen_2_back_main_main_default, lv_color_make(0x21, 0x95, 0xf6));  // 按钮背景颜色
    lv_style_set_bg_opa(&style_screen_2_back_main_main_default, 255);  // 背景透明度
    lv_obj_add_style(ui->screen_2_back, &style_screen_2_back_main_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    // 添加返回按钮的标签
    ui->screen_2_back_label = lv_label_create(ui->screen_2_back);
    lv_label_set_text(ui->screen_2_back_label, "back");  // 设置标签文本
    lv_obj_align(ui->screen_2_back_label, LV_ALIGN_CENTER, 0, 0);  // 居中对齐

    // 创建下一步按钮
    ui->screen_2_next = lv_btn_create(ui->screen_2);
    lv_obj_set_pos(ui->screen_2_next, 270, 0);  // 设置按钮位置
    lv_obj_set_size(ui->screen_2_next, 50, 30);  // 设置按钮大小

    // 设置下一步按钮样式
    static lv_style_t style_screen_2_next_main_main_default;
    lv_style_init(&style_screen_2_next_main_main_default);
    lv_style_set_radius(&style_screen_2_next_main_main_default, 5);  // 圆角半径
    lv_style_set_bg_color(&style_screen_2_next_main_main_default, lv_color_make(0x21, 0x95, 0xf6));  // 按钮背景颜色
    lv_style_set_bg_opa(&style_screen_2_next_main_main_default, 255);  // 背景透明度
    lv_obj_add_style(ui->screen_2_next, &style_screen_2_next_main_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    // 添加下一步按钮的标签
    ui->screen_2_next_label = lv_label_create(ui->screen_2_next);
    lv_label_set_text(ui->screen_2_next_label, "next");  // 设置标签文本
    lv_obj_align(ui->screen_2_next_label, LV_ALIGN_CENTER, 0, 0);  // 居中对齐

    // 创建模拟时钟
	create_analog_clock(ui->screen_2);
	/**
	 * meter : 指向仪表对象的指针
	 * scale : 指向刻度对象
	 * cnt	 : 小刻度的数量
	 * width : 小刻度的宽度
	 * len   : 小刻度的长度
	 * color : 小刻度的颜色
	 * void lv_meter_set_scale_ticks(lv_obj_t *obj, lv_meter_scale_t *scale,
								 uint16_t cnt, uint16_t width,
								uint16_t len, lv_color_t color);
	 * meter     : 指向仪表对象的指针
	 * scale     : 指向刻度对象
	 * nth       : 绘画主刻度的步长
	 * width     : 主刻度的宽度
	 * len       : 主刻度的长度
	 * color     : 主刻度的颜色
	 * label_gap : 刻度与标签之间的间隙
	 * void lv_meter_set_scale_major_ticks(lv_obj_t *obj, lv_meter_scale_t *scale,
										uint16_t nth, uint16_t width, uint16_t len,
										lv_color_t color, int16_t label_gap);
	*/
	/**
	 * obj   : 指向仪表对象的指针
	 * scale : 指向刻度对象
	 * width : 指针宽度
	 * color : 指针颜色
	 * r_mod : 修改半径长度(0：默认值；-10：默认长度-10)
	 * lv_meter_indicator_t *lv_meter_add_needle_line(lv_obj_t *obj, lv_meter_scale_t *scale,
												 uint16_t width, lv_color_t color, int16_t r_mod);
	 * obj   : 指向仪表对象的指针
	 * indic : 指向指针对象
	 * value : 指向的数值
	 *
	 * void lv_meter_set_indicator_value( lv_obj_t * obj, lv_meter_indicator_t * indic,
									 int32_t value);
	*/
	/**
	 * obj   	   : 指向仪表对象的指针
	 * scale	   : 指向指针对象
	 * min  	   : 最小值
	 * max   	   : 最大值
	 * angle_range : 最大的角度(默认是270°，可设置0~360°)
	 * rotation    : 旋转的角度(默认是0°，可设置0~360°)
	 * void lv_meter_set_scale_range(lv_obj_t * obj,
								 lv_meter_scale_t * scale,
								int32_t min, int32_t max,
								uint32_t angle_range, uint32_t rotation);
	*/

    // 创建定时器
    static bool screen_2_analog_clock_timer_enabled = false;
    if (!screen_2_analog_clock_timer_enabled) {
        lv_timer_create(screen_2_analog_clock_timer, 1000, NULL);  // 每秒更新一次时间
        screen_2_analog_clock_timer_enabled = true;
    }
    // 初始化事件
    events_init_screen_2(ui);
}