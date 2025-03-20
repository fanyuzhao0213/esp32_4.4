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
#include "BSP/WIFI/wifi_smartconfig.h"
#include "BSP/WEATHER/weather.h"

// 定时器回调函数，用于更新时间
void screen_3_timer(lv_timer_t *timer)
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

void setup_scr_screen_3(lv_ui *ui){

	//Write codes screen_3
	ui->screen_3 = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui->screen_3, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_main_main_default
	static lv_style_t style_screen_3_main_main_default;
	if (style_screen_3_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_main_main_default);
	else
		lv_style_init(&style_screen_3_main_main_default);
	lv_style_set_bg_color(&style_screen_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_screen_3_main_main_default, 0);
	lv_obj_add_style(ui->screen_3, &style_screen_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_3_baitian
	ui->screen_3_baitian = lv_img_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_baitian, 0, 0);
	lv_obj_set_size(ui->screen_3_baitian, 320, 240);
	lv_obj_set_scrollbar_mode(ui->screen_3_baitian, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_baitian_main_main_default
	static lv_style_t style_screen_3_baitian_main_main_default;
	if (style_screen_3_baitian_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_baitian_main_main_default);
	else
		lv_style_init(&style_screen_3_baitian_main_main_default);
	lv_style_set_img_recolor(&style_screen_3_baitian_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_3_baitian_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_3_baitian_main_main_default, 255);
	lv_obj_add_style(ui->screen_3_baitian, &style_screen_3_baitian_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_3_baitian, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_3_baitian,&_bmp_Xian_BaiTian_320x240);
	lv_img_set_pivot(ui->screen_3_baitian, 0,0);
	lv_img_set_angle(ui->screen_3_baitian, 0);

	//Write codes screen_3_label_7
	ui->screen_3_label_7 = lv_label_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_label_7, 265, 170);
	lv_obj_set_size(ui->screen_3_label_7, 30, 12);
	lv_obj_set_scrollbar_mode(ui->screen_3_label_7, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_3_label_7, "后天");
	lv_label_set_long_mode(ui->screen_3_label_7, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_label_7_main_main_default
	static lv_style_t style_screen_3_label_7_main_main_default;
	if (style_screen_3_label_7_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_label_7_main_main_default);
	else
		lv_style_init(&style_screen_3_label_7_main_main_default);
	lv_style_set_radius(&style_screen_3_label_7_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_3_label_7_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_3_label_7_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_3_label_7_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_3_label_7_main_main_default, 0);
	lv_style_set_text_color(&style_screen_3_label_7_main_main_default, lv_color_make(0xf1, 0xef, 0xef));
	lv_style_set_text_font(&style_screen_3_label_7_main_main_default, &lv_customer_font_IBMPlexSansSC_SemiBold_12);
	lv_style_set_text_letter_space(&style_screen_3_label_7_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_3_label_7_main_main_default, 0);
	lv_style_set_text_align(&style_screen_3_label_7_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_3_label_7_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_3_label_7_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_3_label_7_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_3_label_7_main_main_default, 0);
	lv_obj_add_style(ui->screen_3_label_7, &style_screen_3_label_7_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_3_img_houtian
	ui->screen_3_img_houtian = lv_img_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_img_houtian, 230, 175);
	lv_obj_set_size(ui->screen_3_img_houtian, 35, 35);
	lv_obj_set_scrollbar_mode(ui->screen_3_img_houtian, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_img_houtian_main_main_default
	static lv_style_t style_screen_3_img_houtian_main_main_default;
	if (style_screen_3_img_houtian_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_img_houtian_main_main_default);
	else
		lv_style_init(&style_screen_3_img_houtian_main_main_default);
	lv_style_set_img_recolor(&style_screen_3_img_houtian_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_3_img_houtian_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_3_img_houtian_main_main_default, 255);
	lv_obj_add_style(ui->screen_3_img_houtian, &style_screen_3_img_houtian_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_3_img_houtian, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_3_img_houtian,&_11_35x35);
	lv_img_set_pivot(ui->screen_3_img_houtian, 0,0);
	lv_img_set_angle(ui->screen_3_img_houtian, 0);

	//Write codes screen_3_label_5
	ui->screen_3_label_5 = lv_label_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_label_5, 60, 170);
	lv_obj_set_size(ui->screen_3_label_5, 30, 12);
	lv_obj_set_scrollbar_mode(ui->screen_3_label_5, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_3_label_5, "今天");
	lv_label_set_long_mode(ui->screen_3_label_5, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_label_5_main_main_default
	static lv_style_t style_screen_3_label_5_main_main_default;
	if (style_screen_3_label_5_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_label_5_main_main_default);
	else
		lv_style_init(&style_screen_3_label_5_main_main_default);
	lv_style_set_radius(&style_screen_3_label_5_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_3_label_5_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_3_label_5_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_3_label_5_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_3_label_5_main_main_default, 0);
	lv_style_set_text_color(&style_screen_3_label_5_main_main_default, lv_color_make(0xef, 0xe6, 0xe6));
	lv_style_set_text_font(&style_screen_3_label_5_main_main_default, &lv_customer_font_IBMPlexSansSC_SemiBold_12);
	lv_style_set_text_letter_space(&style_screen_3_label_5_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_3_label_5_main_main_default, 0);
	lv_style_set_text_align(&style_screen_3_label_5_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_3_label_5_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_3_label_5_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_3_label_5_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_3_label_5_main_main_default, 0);
	lv_obj_add_style(ui->screen_3_label_5, &style_screen_3_label_5_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_3_label_6
	ui->screen_3_label_6 = lv_label_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_label_6, 160, 170);
	lv_obj_set_size(ui->screen_3_label_6, 30, 12);
	lv_obj_set_scrollbar_mode(ui->screen_3_label_6, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_3_label_6, "明天");
	lv_label_set_long_mode(ui->screen_3_label_6, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_label_6_main_main_default
	static lv_style_t style_screen_3_label_6_main_main_default;
	if (style_screen_3_label_6_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_label_6_main_main_default);
	else
		lv_style_init(&style_screen_3_label_6_main_main_default);
	lv_style_set_radius(&style_screen_3_label_6_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_3_label_6_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_3_label_6_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_3_label_6_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_3_label_6_main_main_default, 0);
	lv_style_set_text_color(&style_screen_3_label_6_main_main_default, lv_color_make(0xf0, 0xeb, 0xeb));
	lv_style_set_text_font(&style_screen_3_label_6_main_main_default, &lv_customer_font_IBMPlexSansSC_SemiBold_12);
	lv_style_set_text_letter_space(&style_screen_3_label_6_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_3_label_6_main_main_default, 0);
	lv_style_set_text_align(&style_screen_3_label_6_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_3_label_6_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_3_label_6_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_3_label_6_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_3_label_6_main_main_default, 0);
	lv_obj_add_style(ui->screen_3_label_6, &style_screen_3_label_6_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_3_label_jiangshui
	ui->screen_3_label_jiangshui = lv_label_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_label_jiangshui, 275, 130);
	lv_obj_set_size(ui->screen_3_label_jiangshui, 30, 10);
	lv_obj_set_scrollbar_mode(ui->screen_3_label_jiangshui, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_3_label_jiangshui, "10%");
	lv_label_set_long_mode(ui->screen_3_label_jiangshui, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_label_jiangshui_main_main_default
	static lv_style_t style_screen_3_label_jiangshui_main_main_default;
	if (style_screen_3_label_jiangshui_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_label_jiangshui_main_main_default);
	else
		lv_style_init(&style_screen_3_label_jiangshui_main_main_default);
	lv_style_set_radius(&style_screen_3_label_jiangshui_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_3_label_jiangshui_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_3_label_jiangshui_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_3_label_jiangshui_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_3_label_jiangshui_main_main_default, 0);
	lv_style_set_text_color(&style_screen_3_label_jiangshui_main_main_default, lv_color_make(0x38, 0x38, 0x3d));
	lv_style_set_text_font(&style_screen_3_label_jiangshui_main_main_default, &lv_font_arial_10);
	lv_style_set_text_letter_space(&style_screen_3_label_jiangshui_main_main_default, 1);
	lv_style_set_text_line_space(&style_screen_3_label_jiangshui_main_main_default, 0);
	lv_style_set_text_align(&style_screen_3_label_jiangshui_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_3_label_jiangshui_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_3_label_jiangshui_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_3_label_jiangshui_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_3_label_jiangshui_main_main_default, 0);
	lv_obj_add_style(ui->screen_3_label_jiangshui, &style_screen_3_label_jiangshui_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_3_label_fengsu
	ui->screen_3_label_fengsu = lv_label_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_label_fengsu, 275, 90);
	lv_obj_set_size(ui->screen_3_label_fengsu, 30, 10);
	lv_obj_set_scrollbar_mode(ui->screen_3_label_fengsu, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_3_label_fengsu, "9.66");
	lv_label_set_long_mode(ui->screen_3_label_fengsu, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_label_fengsu_main_main_default
	static lv_style_t style_screen_3_label_fengsu_main_main_default;
	if (style_screen_3_label_fengsu_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_label_fengsu_main_main_default);
	else
		lv_style_init(&style_screen_3_label_fengsu_main_main_default);
	lv_style_set_radius(&style_screen_3_label_fengsu_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_3_label_fengsu_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_3_label_fengsu_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_3_label_fengsu_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_3_label_fengsu_main_main_default, 0);
	lv_style_set_text_color(&style_screen_3_label_fengsu_main_main_default, lv_color_make(0x50, 0x49, 0x49));
	lv_style_set_text_font(&style_screen_3_label_fengsu_main_main_default, &lv_font_arial_10);
	lv_style_set_text_letter_space(&style_screen_3_label_fengsu_main_main_default, 1);
	lv_style_set_text_line_space(&style_screen_3_label_fengsu_main_main_default, 0);
	lv_style_set_text_align(&style_screen_3_label_fengsu_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_3_label_fengsu_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_3_label_fengsu_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_3_label_fengsu_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_3_label_fengsu_main_main_default, 0);
	lv_obj_add_style(ui->screen_3_label_fengsu, &style_screen_3_label_fengsu_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_3_label_fengxiang
	ui->screen_3_label_fengxiang = lv_label_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_label_fengxiang, 275, 110);
	lv_obj_set_size(ui->screen_3_label_fengxiang, 30, 10);
	lv_obj_set_scrollbar_mode(ui->screen_3_label_fengxiang, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_3_label_fengxiang, "东风");
	lv_label_set_long_mode(ui->screen_3_label_fengxiang, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_label_fengxiang_main_main_default
	static lv_style_t style_screen_3_label_fengxiang_main_main_default;
	if (style_screen_3_label_fengxiang_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_label_fengxiang_main_main_default);
	else
		lv_style_init(&style_screen_3_label_fengxiang_main_main_default);
	lv_style_set_radius(&style_screen_3_label_fengxiang_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_3_label_fengxiang_main_main_default, lv_color_make(0x35, 0x3e, 0x45));
	lv_style_set_bg_grad_color(&style_screen_3_label_fengxiang_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_3_label_fengxiang_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_3_label_fengxiang_main_main_default, 0);
	lv_style_set_text_color(&style_screen_3_label_fengxiang_main_main_default, lv_color_make(0x31, 0x2e, 0x33));
	lv_style_set_text_font(&style_screen_3_label_fengxiang_main_main_default, &lv_customer_font_IBMPlexSansSC_SemiBold_10);
	lv_style_set_text_letter_space(&style_screen_3_label_fengxiang_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_3_label_fengxiang_main_main_default, 0);
	lv_style_set_text_align(&style_screen_3_label_fengxiang_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_3_label_fengxiang_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_3_label_fengxiang_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_3_label_fengxiang_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_3_label_fengxiang_main_main_default, 0);
	lv_obj_add_style(ui->screen_3_label_fengxiang, &style_screen_3_label_fengxiang_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_3_label_4
	ui->screen_3_label_4 = lv_label_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_label_4, 240, 130);
	lv_obj_set_size(ui->screen_3_label_4, 30, 10);
	lv_obj_set_scrollbar_mode(ui->screen_3_label_4, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_3_label_4, "降水:");
	lv_label_set_long_mode(ui->screen_3_label_4, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_label_4_main_main_default
	static lv_style_t style_screen_3_label_4_main_main_default;
	if (style_screen_3_label_4_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_label_4_main_main_default);
	else
		lv_style_init(&style_screen_3_label_4_main_main_default);
	lv_style_set_radius(&style_screen_3_label_4_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_3_label_4_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_3_label_4_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_3_label_4_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_3_label_4_main_main_default, 0);
	lv_style_set_text_color(&style_screen_3_label_4_main_main_default, lv_color_make(0xfd, 0xfc, 0xfc));
	lv_style_set_text_font(&style_screen_3_label_4_main_main_default, &lv_customer_font_IBMPlexSansSC_SemiBold_10);
	lv_style_set_text_letter_space(&style_screen_3_label_4_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_3_label_4_main_main_default, 0);
	lv_style_set_text_align(&style_screen_3_label_4_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_3_label_4_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_3_label_4_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_3_label_4_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_3_label_4_main_main_default, 0);
	lv_obj_add_style(ui->screen_3_label_4, &style_screen_3_label_4_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_3_img_tianqi
	ui->screen_3_img_tianqi = lv_img_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_img_tianqi, 135, 85);
	lv_obj_set_size(ui->screen_3_img_tianqi, 60, 55);
	lv_obj_set_scrollbar_mode(ui->screen_3_img_tianqi, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_img_tianqi_main_main_default
	static lv_style_t style_screen_3_img_tianqi_main_main_default;
	if (style_screen_3_img_tianqi_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_img_tianqi_main_main_default);
	else
		lv_style_init(&style_screen_3_img_tianqi_main_main_default);
	lv_style_set_img_recolor(&style_screen_3_img_tianqi_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_3_img_tianqi_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_3_img_tianqi_main_main_default, 255);
	lv_obj_add_style(ui->screen_3_img_tianqi, &style_screen_3_img_tianqi_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_3_img_tianqi, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_3_img_tianqi,&_0_60x55);
	lv_img_set_pivot(ui->screen_3_img_tianqi, 0,0);
	lv_img_set_angle(ui->screen_3_img_tianqi, 0);

	//Write codes screen_3_label_1
	ui->screen_3_label_1 = lv_label_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_label_1, 64, 120);
	lv_obj_set_size(ui->screen_3_label_1, 15, 15);
	lv_obj_set_scrollbar_mode(ui->screen_3_label_1, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_3_label_1, "晴");
	lv_label_set_long_mode(ui->screen_3_label_1, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_label_1_main_main_default
	static lv_style_t style_screen_3_label_1_main_main_default;
	if (style_screen_3_label_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_label_1_main_main_default);
	else
		lv_style_init(&style_screen_3_label_1_main_main_default);
	lv_style_set_radius(&style_screen_3_label_1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_3_label_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_3_label_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_3_label_1_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_3_label_1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_3_label_1_main_main_default, lv_color_make(0xe9, 0xdd, 0xdd));
	lv_style_set_text_font(&style_screen_3_label_1_main_main_default, &lv_customer_font_IBMPlexSansSC_SemiBold_12);
	lv_style_set_text_letter_space(&style_screen_3_label_1_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_3_label_1_main_main_default, 0);
	lv_style_set_text_align(&style_screen_3_label_1_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_3_label_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_3_label_1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_3_label_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_3_label_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_3_label_1, &style_screen_3_label_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_3_label_2
	ui->screen_3_label_2 = lv_label_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_label_2, 240, 90);
	lv_obj_set_size(ui->screen_3_label_2, 30, 10);
	lv_obj_set_scrollbar_mode(ui->screen_3_label_2, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_3_label_2, "风速:");
	lv_label_set_long_mode(ui->screen_3_label_2, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_label_2_main_main_default
	static lv_style_t style_screen_3_label_2_main_main_default;
	if (style_screen_3_label_2_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_label_2_main_main_default);
	else
		lv_style_init(&style_screen_3_label_2_main_main_default);
	lv_style_set_radius(&style_screen_3_label_2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_3_label_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_3_label_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_3_label_2_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_3_label_2_main_main_default, 0);
	lv_style_set_text_color(&style_screen_3_label_2_main_main_default, lv_color_make(0xfa, 0xf9, 0xf9));
	lv_style_set_text_font(&style_screen_3_label_2_main_main_default, &lv_customer_font_IBMPlexSansSC_SemiBold_10);
	lv_style_set_text_letter_space(&style_screen_3_label_2_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_3_label_2_main_main_default, 0);
	lv_style_set_text_align(&style_screen_3_label_2_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_3_label_2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_3_label_2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_3_label_2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_3_label_2_main_main_default, 0);
	lv_obj_add_style(ui->screen_3_label_2, &style_screen_3_label_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_3_label_3
	ui->screen_3_label_3 = lv_label_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_label_3, 240, 110);
	lv_obj_set_size(ui->screen_3_label_3, 30, 10);
	lv_obj_set_scrollbar_mode(ui->screen_3_label_3, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_3_label_3, "风向:");
	lv_label_set_long_mode(ui->screen_3_label_3, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_label_3_main_main_default
	static lv_style_t style_screen_3_label_3_main_main_default;
	if (style_screen_3_label_3_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_label_3_main_main_default);
	else
		lv_style_init(&style_screen_3_label_3_main_main_default);
	lv_style_set_radius(&style_screen_3_label_3_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_3_label_3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_3_label_3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_3_label_3_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_3_label_3_main_main_default, 0);
	lv_style_set_text_color(&style_screen_3_label_3_main_main_default, lv_color_make(0xf9, 0xf6, 0xf6));
	lv_style_set_text_font(&style_screen_3_label_3_main_main_default, &lv_customer_font_IBMPlexSansSC_SemiBold_10);
	lv_style_set_text_letter_space(&style_screen_3_label_3_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_3_label_3_main_main_default, 0);
	lv_style_set_text_align(&style_screen_3_label_3_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_3_label_3_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_3_label_3_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_3_label_3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_3_label_3_main_main_default, 0);
	lv_obj_add_style(ui->screen_3_label_3, &style_screen_3_label_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_3_label_wenduriqi
	ui->screen_3_label_wenduriqi = lv_label_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_label_wenduriqi, 20, 120);
	lv_obj_set_size(ui->screen_3_label_wenduriqi, 40, 10);
	lv_obj_set_scrollbar_mode(ui->screen_3_label_wenduriqi, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_3_label_wenduriqi, "10-30");
	lv_label_set_long_mode(ui->screen_3_label_wenduriqi, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_label_wenduriqi_main_main_default
	static lv_style_t style_screen_3_label_wenduriqi_main_main_default;
	if (style_screen_3_label_wenduriqi_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_label_wenduriqi_main_main_default);
	else
		lv_style_init(&style_screen_3_label_wenduriqi_main_main_default);
	lv_style_set_radius(&style_screen_3_label_wenduriqi_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_3_label_wenduriqi_main_main_default, lv_color_make(0x8a, 0x8a, 0xc1));
	lv_style_set_bg_grad_color(&style_screen_3_label_wenduriqi_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_3_label_wenduriqi_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_3_label_wenduriqi_main_main_default, 0);
	lv_style_set_text_color(&style_screen_3_label_wenduriqi_main_main_default, lv_color_make(0xfa, 0xf4, 0xf4));
	lv_style_set_text_font(&style_screen_3_label_wenduriqi_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_3_label_wenduriqi_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_3_label_wenduriqi_main_main_default, 0);
	lv_style_set_text_align(&style_screen_3_label_wenduriqi_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_3_label_wenduriqi_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_3_label_wenduriqi_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_3_label_wenduriqi_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_3_label_wenduriqi_main_main_default, 0);
	lv_obj_add_style(ui->screen_3_label_wenduriqi, &style_screen_3_label_wenduriqi_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_3_label_jintianriqi
	ui->screen_3_label_jintianriqi = lv_label_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_label_jintianriqi, 60, 190);
	lv_obj_set_size(ui->screen_3_label_jintianriqi, 45, 12);
	lv_obj_set_scrollbar_mode(ui->screen_3_label_jintianriqi, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_3_label_jintianriqi, "10-30");
	lv_label_set_long_mode(ui->screen_3_label_jintianriqi, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_label_jintianriqi_main_main_default
	static lv_style_t style_screen_3_label_jintianriqi_main_main_default;
	if (style_screen_3_label_jintianriqi_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_label_jintianriqi_main_main_default);
	else
		lv_style_init(&style_screen_3_label_jintianriqi_main_main_default);
	lv_style_set_radius(&style_screen_3_label_jintianriqi_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_3_label_jintianriqi_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_3_label_jintianriqi_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_3_label_jintianriqi_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_3_label_jintianriqi_main_main_default, 0);
	lv_style_set_text_color(&style_screen_3_label_jintianriqi_main_main_default, lv_color_make(0xf7, 0xf3, 0xf3));
	lv_style_set_text_font(&style_screen_3_label_jintianriqi_main_main_default, &lv_font_arial_12);
	lv_style_set_text_letter_space(&style_screen_3_label_jintianriqi_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_3_label_jintianriqi_main_main_default, 0);
	lv_style_set_text_align(&style_screen_3_label_jintianriqi_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_3_label_jintianriqi_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_3_label_jintianriqi_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_3_label_jintianriqi_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_3_label_jintianriqi_main_main_default, 0);
	lv_obj_add_style(ui->screen_3_label_jintianriqi, &style_screen_3_label_jintianriqi_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_3_label_mingtianriqi
	ui->screen_3_label_mingtianriqi = lv_label_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_label_mingtianriqi, 160, 190);
	lv_obj_set_size(ui->screen_3_label_mingtianriqi, 45, 12);
	lv_obj_set_scrollbar_mode(ui->screen_3_label_mingtianriqi, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_3_label_mingtianriqi, "10-31");
	lv_label_set_long_mode(ui->screen_3_label_mingtianriqi, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_label_mingtianriqi_main_main_default
	static lv_style_t style_screen_3_label_mingtianriqi_main_main_default;
	if (style_screen_3_label_mingtianriqi_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_label_mingtianriqi_main_main_default);
	else
		lv_style_init(&style_screen_3_label_mingtianriqi_main_main_default);
	lv_style_set_radius(&style_screen_3_label_mingtianriqi_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_3_label_mingtianriqi_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_3_label_mingtianriqi_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_3_label_mingtianriqi_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_3_label_mingtianriqi_main_main_default, 0);
	lv_style_set_text_color(&style_screen_3_label_mingtianriqi_main_main_default, lv_color_make(0xf8, 0xf2, 0xf2));
	lv_style_set_text_font(&style_screen_3_label_mingtianriqi_main_main_default, &lv_font_arial_12);
	lv_style_set_text_letter_space(&style_screen_3_label_mingtianriqi_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_3_label_mingtianriqi_main_main_default, 0);
	lv_style_set_text_align(&style_screen_3_label_mingtianriqi_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_3_label_mingtianriqi_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_3_label_mingtianriqi_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_3_label_mingtianriqi_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_3_label_mingtianriqi_main_main_default, 0);
	lv_obj_add_style(ui->screen_3_label_mingtianriqi, &style_screen_3_label_mingtianriqi_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_3_label_houtianriqi
	ui->screen_3_label_houtianriqi = lv_label_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_label_houtianriqi, 265, 190);
	lv_obj_set_size(ui->screen_3_label_houtianriqi, 45, 12);
	lv_obj_set_scrollbar_mode(ui->screen_3_label_houtianriqi, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_3_label_houtianriqi, "11-01");
	lv_label_set_long_mode(ui->screen_3_label_houtianriqi, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_label_houtianriqi_main_main_default
	static lv_style_t style_screen_3_label_houtianriqi_main_main_default;
	if (style_screen_3_label_houtianriqi_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_label_houtianriqi_main_main_default);
	else
		lv_style_init(&style_screen_3_label_houtianriqi_main_main_default);
	lv_style_set_radius(&style_screen_3_label_houtianriqi_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_3_label_houtianriqi_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_3_label_houtianriqi_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_3_label_houtianriqi_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_3_label_houtianriqi_main_main_default, 0);
	lv_style_set_text_color(&style_screen_3_label_houtianriqi_main_main_default, lv_color_make(0xf9, 0xf0, 0xf0));
	lv_style_set_text_font(&style_screen_3_label_houtianriqi_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_3_label_houtianriqi_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_3_label_houtianriqi_main_main_default, 0);
	lv_style_set_text_align(&style_screen_3_label_houtianriqi_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_3_label_houtianriqi_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_3_label_houtianriqi_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_3_label_houtianriqi_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_3_label_houtianriqi_main_main_default, 0);
	lv_obj_add_style(ui->screen_3_label_houtianriqi, &style_screen_3_label_houtianriqi_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_3_label_wendu
	ui->screen_3_label_wendu = lv_label_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_label_wendu, 10, 80);
	lv_obj_set_size(ui->screen_3_label_wendu, 60, 40);
	lv_obj_set_scrollbar_mode(ui->screen_3_label_wendu, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_3_label_wendu, "25");
	lv_label_set_long_mode(ui->screen_3_label_wendu, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_label_wendu_main_main_default
	static lv_style_t style_screen_3_label_wendu_main_main_default;
	if (style_screen_3_label_wendu_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_label_wendu_main_main_default);
	else
		lv_style_init(&style_screen_3_label_wendu_main_main_default);
	lv_style_set_radius(&style_screen_3_label_wendu_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_3_label_wendu_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_3_label_wendu_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_3_label_wendu_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_3_label_wendu_main_main_default, 0);
	lv_style_set_text_color(&style_screen_3_label_wendu_main_main_default, lv_color_make(0xeb, 0xe5, 0xe5));
	lv_style_set_text_font(&style_screen_3_label_wendu_main_main_default, &lv_font_simsun_40);
	lv_style_set_text_letter_space(&style_screen_3_label_wendu_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_3_label_wendu_main_main_default, 0);
	lv_style_set_text_align(&style_screen_3_label_wendu_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_3_label_wendu_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_3_label_wendu_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_3_label_wendu_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_3_label_wendu_main_main_default, 0);
	lv_obj_add_style(ui->screen_3_label_wendu, &style_screen_3_label_wendu_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_3_img_2
	ui->screen_3_img_2 = lv_img_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_img_2, 64, 80);
	lv_obj_set_size(ui->screen_3_img_2, 16, 19);
	lv_obj_set_scrollbar_mode(ui->screen_3_img_2, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_img_2_main_main_default
	static lv_style_t style_screen_3_img_2_main_main_default;
	if (style_screen_3_img_2_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_img_2_main_main_default);
	else
		lv_style_init(&style_screen_3_img_2_main_main_default);
	lv_style_set_img_recolor(&style_screen_3_img_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_3_img_2_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_3_img_2_main_main_default, 255);
	lv_obj_add_style(ui->screen_3_img_2, &style_screen_3_img_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_3_img_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_3_img_2,&_bmp_Du_16x19);
	lv_img_set_pivot(ui->screen_3_img_2, 0,0);
	lv_img_set_angle(ui->screen_3_img_2, 0);

	//Write codes screen_3_label_riqi
	ui->screen_3_label_riqi = lv_label_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_label_riqi, 15, 42.5);
	lv_obj_set_size(ui->screen_3_label_riqi, 90, 15);
	lv_obj_set_scrollbar_mode(ui->screen_3_label_riqi, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_3_label_riqi, "2020/10/19");
	lv_label_set_long_mode(ui->screen_3_label_riqi, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_label_riqi_main_main_default
	static lv_style_t style_screen_3_label_riqi_main_main_default;
	if (style_screen_3_label_riqi_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_label_riqi_main_main_default);
	else
		lv_style_init(&style_screen_3_label_riqi_main_main_default);
	lv_style_set_radius(&style_screen_3_label_riqi_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_3_label_riqi_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_3_label_riqi_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_3_label_riqi_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_3_label_riqi_main_main_default, 0);
	lv_style_set_text_color(&style_screen_3_label_riqi_main_main_default, lv_color_make(0xf8, 0xf7, 0xf7));
	lv_style_set_text_font(&style_screen_3_label_riqi_main_main_default, &lv_font_arial_12);
	lv_style_set_text_letter_space(&style_screen_3_label_riqi_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_3_label_riqi_main_main_default, 0);
	lv_style_set_text_align(&style_screen_3_label_riqi_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_3_label_riqi_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_3_label_riqi_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_3_label_riqi_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_3_label_riqi_main_main_default, 0);
	lv_obj_add_style(ui->screen_3_label_riqi, &style_screen_3_label_riqi_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_3_label_xingqi
	ui->screen_3_label_xingqi = lv_label_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_label_xingqi, 140, 42.5);
	lv_obj_set_size(ui->screen_3_label_xingqi, 60, 15);
	lv_obj_set_scrollbar_mode(ui->screen_3_label_xingqi, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_3_label_xingqi, "星期一");
	lv_label_set_long_mode(ui->screen_3_label_xingqi, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_label_xingqi_main_main_default
	static lv_style_t style_screen_3_label_xingqi_main_main_default;
	if (style_screen_3_label_xingqi_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_label_xingqi_main_main_default);
	else
		lv_style_init(&style_screen_3_label_xingqi_main_main_default);
	lv_style_set_radius(&style_screen_3_label_xingqi_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_3_label_xingqi_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_3_label_xingqi_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_3_label_xingqi_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_3_label_xingqi_main_main_default, 0);
	lv_style_set_text_color(&style_screen_3_label_xingqi_main_main_default, lv_color_make(0xf7, 0xf7, 0xf7));
	lv_style_set_text_font(&style_screen_3_label_xingqi_main_main_default, &lv_customer_font_IBMPlexSansSC_SemiBold_12);
	lv_style_set_text_letter_space(&style_screen_3_label_xingqi_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_3_label_xingqi_main_main_default, 0);
	lv_style_set_text_align(&style_screen_3_label_xingqi_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_3_label_xingqi_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_3_label_xingqi_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_3_label_xingqi_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_3_label_xingqi_main_main_default, 0);
	lv_obj_add_style(ui->screen_3_label_xingqi, &style_screen_3_label_xingqi_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_3_label_time
	ui->screen_3_label_time = lv_label_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_label_time, 225, 35);
	lv_obj_set_size(ui->screen_3_label_time, 80, 30);
	lv_obj_set_scrollbar_mode(ui->screen_3_label_time, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_3_label_time, "18:51");
	lv_label_set_long_mode(ui->screen_3_label_time, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_label_time_main_main_default
	static lv_style_t style_screen_3_label_time_main_main_default;
	if (style_screen_3_label_time_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_label_time_main_main_default);
	else
		lv_style_init(&style_screen_3_label_time_main_main_default);
	lv_style_set_radius(&style_screen_3_label_time_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_3_label_time_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_3_label_time_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_3_label_time_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_3_label_time_main_main_default, 0);
	lv_style_set_text_color(&style_screen_3_label_time_main_main_default, lv_color_make(0xec, 0xe9, 0xf1));
	lv_style_set_text_font(&style_screen_3_label_time_main_main_default, &lv_font_arial_26);
	lv_style_set_text_letter_space(&style_screen_3_label_time_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_3_label_time_main_main_default, 0);
	lv_style_set_text_align(&style_screen_3_label_time_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_3_label_time_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_3_label_time_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_3_label_time_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_3_label_time_main_main_default, 0);
	lv_obj_add_style(ui->screen_3_label_time, &style_screen_3_label_time_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_3_img_1
	ui->screen_3_img_1 = lv_img_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_img_1, 135, 15);
	lv_obj_set_size(ui->screen_3_img_1, 15, 15);
	lv_obj_set_scrollbar_mode(ui->screen_3_img_1, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_img_1_main_main_default
	static lv_style_t style_screen_3_img_1_main_main_default;
	if (style_screen_3_img_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_img_1_main_main_default);
	else
		lv_style_init(&style_screen_3_img_1_main_main_default);
	lv_style_set_img_recolor(&style_screen_3_img_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_3_img_1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_3_img_1_main_main_default, 255);
	lv_obj_add_style(ui->screen_3_img_1, &style_screen_3_img_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_3_img_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_3_img_1,&_bmp_DingWei_15x15);
	lv_img_set_pivot(ui->screen_3_img_1, 0,0);
	lv_img_set_angle(ui->screen_3_img_1, 0);

	//Write codes screen_3_label_dingwei
	ui->screen_3_label_dingwei = lv_label_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_label_dingwei, 150, 12);
	lv_obj_set_size(ui->screen_3_label_dingwei, 60, 20);
	lv_obj_set_scrollbar_mode(ui->screen_3_label_dingwei, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_3_label_dingwei, "西安");
	lv_label_set_long_mode(ui->screen_3_label_dingwei, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_label_dingwei_main_main_default
	static lv_style_t style_screen_3_label_dingwei_main_main_default;
	if (style_screen_3_label_dingwei_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_label_dingwei_main_main_default);
	else
		lv_style_init(&style_screen_3_label_dingwei_main_main_default);
	lv_style_set_radius(&style_screen_3_label_dingwei_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_3_label_dingwei_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_3_label_dingwei_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_3_label_dingwei_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_3_label_dingwei_main_main_default, 0);
	lv_style_set_text_color(&style_screen_3_label_dingwei_main_main_default, lv_color_make(0xd5, 0xbe, 0xbe));
	lv_style_set_text_font(&style_screen_3_label_dingwei_main_main_default, &lv_customer_font_IBMPlexSansSC_SemiBold_20);
	lv_style_set_text_letter_space(&style_screen_3_label_dingwei_main_main_default, 3);
	lv_style_set_text_line_space(&style_screen_3_label_dingwei_main_main_default, 0);
	lv_style_set_text_align(&style_screen_3_label_dingwei_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_3_label_dingwei_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_3_label_dingwei_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_3_label_dingwei_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_3_label_dingwei_main_main_default, 0);
	lv_obj_add_style(ui->screen_3_label_dingwei, &style_screen_3_label_dingwei_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_3_label_riluo
	ui->screen_3_label_riluo = lv_label_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_label_riluo, 215, 225);
	lv_obj_set_size(ui->screen_3_label_riluo, 35, 8);
	lv_obj_set_scrollbar_mode(ui->screen_3_label_riluo, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_3_label_riluo, "20:00");
	lv_label_set_long_mode(ui->screen_3_label_riluo, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_label_riluo_main_main_default
	static lv_style_t style_screen_3_label_riluo_main_main_default;
	if (style_screen_3_label_riluo_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_label_riluo_main_main_default);
	else
		lv_style_init(&style_screen_3_label_riluo_main_main_default);
	lv_style_set_radius(&style_screen_3_label_riluo_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_3_label_riluo_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_3_label_riluo_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_3_label_riluo_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_3_label_riluo_main_main_default, 0);
	lv_style_set_text_color(&style_screen_3_label_riluo_main_main_default, lv_color_make(0xfa, 0xfa, 0xfa));
	lv_style_set_text_font(&style_screen_3_label_riluo_main_main_default, &lv_font_Acme_Regular_10);
	lv_style_set_text_letter_space(&style_screen_3_label_riluo_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_3_label_riluo_main_main_default, 0);
	lv_style_set_text_align(&style_screen_3_label_riluo_main_main_default, LV_TEXT_ALIGN_LEFT);
	lv_style_set_pad_left(&style_screen_3_label_riluo_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_3_label_riluo_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_3_label_riluo_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_3_label_riluo_main_main_default, 0);
	lv_obj_add_style(ui->screen_3_label_riluo, &style_screen_3_label_riluo_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_3_label_richu
	ui->screen_3_label_richu = lv_label_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_label_richu, 75, 225);
	lv_obj_set_size(ui->screen_3_label_richu, 35, 8);
	lv_obj_set_scrollbar_mode(ui->screen_3_label_richu, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_3_label_richu, "10:00");
	lv_label_set_long_mode(ui->screen_3_label_richu, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_label_richu_main_main_default
	static lv_style_t style_screen_3_label_richu_main_main_default;
	if (style_screen_3_label_richu_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_label_richu_main_main_default);
	else
		lv_style_init(&style_screen_3_label_richu_main_main_default);
	lv_style_set_radius(&style_screen_3_label_richu_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_3_label_richu_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_3_label_richu_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_3_label_richu_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_3_label_richu_main_main_default, 0);
	lv_style_set_text_color(&style_screen_3_label_richu_main_main_default, lv_color_make(0xeb, 0xe5, 0xe5));
	lv_style_set_text_font(&style_screen_3_label_richu_main_main_default, &lv_font_Acme_Regular_10);
	lv_style_set_text_letter_space(&style_screen_3_label_richu_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_3_label_richu_main_main_default, 0);
	lv_style_set_text_align(&style_screen_3_label_richu_main_main_default, LV_TEXT_ALIGN_LEFT);
	lv_style_set_pad_left(&style_screen_3_label_richu_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_3_label_richu_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_3_label_richu_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_3_label_richu_main_main_default, 0);
	lv_obj_add_style(ui->screen_3_label_richu, &style_screen_3_label_richu_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_3_richu_bai
	ui->screen_3_richu_bai = lv_img_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_richu_bai, 100, 220);
	lv_obj_set_size(ui->screen_3_richu_bai, 120, 20);
	lv_obj_set_scrollbar_mode(ui->screen_3_richu_bai, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_richu_bai_main_main_default
	static lv_style_t style_screen_3_richu_bai_main_main_default;
	if (style_screen_3_richu_bai_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_richu_bai_main_main_default);
	else
		lv_style_init(&style_screen_3_richu_bai_main_main_default);
	lv_style_set_img_recolor(&style_screen_3_richu_bai_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_3_richu_bai_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_3_richu_bai_main_main_default, 255);
	lv_obj_add_style(ui->screen_3_richu_bai, &style_screen_3_richu_bai_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_3_richu_bai, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_3_richu_bai,&_bmp_RiChuRiLuo_120x20);
	lv_img_set_pivot(ui->screen_3_richu_bai, 0,0);
	lv_img_set_angle(ui->screen_3_richu_bai, 0);

	//Write codes screen_3_backbtn
	ui->screen_3_backbtn = lv_btn_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_backbtn, 0, 0);
	lv_obj_set_size(ui->screen_3_backbtn, 30, 30);
	lv_obj_set_scrollbar_mode(ui->screen_3_backbtn, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_backbtn_main_main_default
	static lv_style_t style_screen_3_backbtn_main_main_default;
	if (style_screen_3_backbtn_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_backbtn_main_main_default);
	else
		lv_style_init(&style_screen_3_backbtn_main_main_default);
	lv_style_set_radius(&style_screen_3_backbtn_main_main_default, 5);
	lv_style_set_bg_color(&style_screen_3_backbtn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_3_backbtn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_3_backbtn_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_3_backbtn_main_main_default, 255);
	lv_style_set_border_color(&style_screen_3_backbtn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_3_backbtn_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_3_backbtn_main_main_default, 255);
	lv_style_set_text_color(&style_screen_3_backbtn_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_3_backbtn_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_align(&style_screen_3_backbtn_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_3_backbtn, &style_screen_3_backbtn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->screen_3_backbtn_label = lv_label_create(ui->screen_3_backbtn);
	lv_label_set_text(ui->screen_3_backbtn_label, "back");
	lv_obj_set_style_pad_all(ui->screen_3_backbtn, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_3_backbtn_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_3_img_jintian
	ui->screen_3_img_jintian = lv_img_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_img_jintian, 20, 170);
	lv_obj_set_size(ui->screen_3_img_jintian, 35, 35);
	lv_obj_set_scrollbar_mode(ui->screen_3_img_jintian, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_img_jintian_main_main_default
	static lv_style_t style_screen_3_img_jintian_main_main_default;
	if (style_screen_3_img_jintian_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_img_jintian_main_main_default);
	else
		lv_style_init(&style_screen_3_img_jintian_main_main_default);
	lv_style_set_img_recolor(&style_screen_3_img_jintian_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_3_img_jintian_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_3_img_jintian_main_main_default, 255);
	lv_obj_add_style(ui->screen_3_img_jintian, &style_screen_3_img_jintian_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_3_img_jintian, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_3_img_jintian,&_5_35x35);
	lv_img_set_pivot(ui->screen_3_img_jintian, 0,0);
	lv_img_set_angle(ui->screen_3_img_jintian, 0);

	//Write codes screen_3_img_mingtian
	ui->screen_3_img_mingtian = lv_img_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_img_mingtian, 130, 170);
	lv_obj_set_size(ui->screen_3_img_mingtian, 35, 35);
	lv_obj_set_scrollbar_mode(ui->screen_3_img_mingtian, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_img_mingtian_main_main_default
	static lv_style_t style_screen_3_img_mingtian_main_main_default;
	if (style_screen_3_img_mingtian_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_img_mingtian_main_main_default);
	else
		lv_style_init(&style_screen_3_img_mingtian_main_main_default);
	lv_style_set_img_recolor(&style_screen_3_img_mingtian_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_3_img_mingtian_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_3_img_mingtian_main_main_default, 255);
	lv_obj_add_style(ui->screen_3_img_mingtian, &style_screen_3_img_mingtian_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_3_img_mingtian, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_3_img_mingtian,&_1_35x35);
	lv_img_set_pivot(ui->screen_3_img_mingtian, 0,0);
	lv_img_set_angle(ui->screen_3_img_mingtian, 0);

	// // 创建定时器
	// static bool screen_3_timer_enabled = false;
	// if (!screen_3_timer_enabled) {
	// 	lv_timer_create(screen_3_timer, 1000, NULL);  // 每秒更新一次时间
	// 	screen_3_timer_enabled = true;
	// }
	//Init events for screen
	events_init_screen_3(ui);
}