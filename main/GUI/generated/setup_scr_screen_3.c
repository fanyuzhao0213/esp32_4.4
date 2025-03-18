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

	//Write codes screen_3_back
	ui->screen_3_back = lv_btn_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_back, 4, 2);
	lv_obj_set_size(ui->screen_3_back, 30, 30);
	lv_obj_set_scrollbar_mode(ui->screen_3_back, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_back_main_main_default
	static lv_style_t style_screen_3_back_main_main_default;
	if (style_screen_3_back_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_back_main_main_default);
	else
		lv_style_init(&style_screen_3_back_main_main_default);
	lv_style_set_radius(&style_screen_3_back_main_main_default, 5);
	lv_style_set_bg_color(&style_screen_3_back_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_3_back_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_3_back_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_3_back_main_main_default, 255);
	lv_style_set_border_color(&style_screen_3_back_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_3_back_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_3_back_main_main_default, 255);
	lv_style_set_text_color(&style_screen_3_back_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_3_back_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_align(&style_screen_3_back_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_3_back, &style_screen_3_back_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->screen_3_back_label = lv_label_create(ui->screen_3_back);
	lv_label_set_text(ui->screen_3_back_label, "default");
	lv_obj_set_style_pad_all(ui->screen_3_back, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_3_back_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_3_tianqi
	ui->screen_3_tianqi = lv_img_create(ui->screen_3);
	lv_obj_set_pos(ui->screen_3_tianqi, 0, 0);
	lv_obj_set_size(ui->screen_3_tianqi, 320, 240);
	lv_obj_set_scrollbar_mode(ui->screen_3_tianqi, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_3_tianqi_main_main_default
	static lv_style_t style_screen_3_tianqi_main_main_default;
	if (style_screen_3_tianqi_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_3_tianqi_main_main_default);
	else
		lv_style_init(&style_screen_3_tianqi_main_main_default);
	lv_style_set_img_recolor(&style_screen_3_tianqi_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_3_tianqi_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_3_tianqi_main_main_default, 255);
	lv_obj_add_style(ui->screen_3_tianqi, &style_screen_3_tianqi_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_3_tianqi, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_3_tianqi,&_bmp_BeiJing1_320x240);
	lv_img_set_pivot(ui->screen_3_tianqi, 0,0);
	lv_img_set_angle(ui->screen_3_tianqi, 0);

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

	//Init events for screen
	events_init_screen_3(ui);
}