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


void setup_scr_screen_Picture(lv_ui *ui){

	//Write codes screen_Picture
	ui->screen_Picture = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui->screen_Picture, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_picture_main_main_default
	static lv_style_t style_screen_picture_main_main_default;
	if (style_screen_picture_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_picture_main_main_default);
	else
		lv_style_init(&style_screen_picture_main_main_default);
	lv_style_set_bg_color(&style_screen_picture_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_screen_picture_main_main_default, 0);
	lv_obj_add_style(ui->screen_Picture, &style_screen_picture_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Picture_img_SD
	ui->screen_Picture_img_SD = lv_img_create(ui->screen_Picture);
	lv_obj_set_pos(ui->screen_Picture_img_SD, 0, 0);
	lv_obj_set_size(ui->screen_Picture_img_SD, 320, 240);
	lv_obj_set_scrollbar_mode(ui->screen_Picture_img_SD, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_picture_img_sd_main_main_default
	static lv_style_t style_screen_picture_img_sd_main_main_default;
	if (style_screen_picture_img_sd_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_picture_img_sd_main_main_default);
	else
		lv_style_init(&style_screen_picture_img_sd_main_main_default);
	lv_style_set_img_recolor(&style_screen_picture_img_sd_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_picture_img_sd_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_picture_img_sd_main_main_default, 255);
	lv_obj_add_style(ui->screen_Picture_img_SD, &style_screen_picture_img_sd_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Picture_img_SD, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Picture_img_SD,&_app_picture_320x240);
	lv_img_set_pivot(ui->screen_Picture_img_SD, 0,0);
	lv_img_set_angle(ui->screen_Picture_img_SD, 0);

	//Write codes screen_Picture_btn_Home
	ui->screen_Picture_btn_Home = lv_btn_create(ui->screen_Picture);
	lv_obj_set_pos(ui->screen_Picture_btn_Home, 290, 210);
	lv_obj_set_size(ui->screen_Picture_btn_Home, 30, 30);
	lv_obj_set_scrollbar_mode(ui->screen_Picture_btn_Home, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_picture_btn_home_main_main_default
	static lv_style_t style_screen_picture_btn_home_main_main_default;
	if (style_screen_picture_btn_home_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_picture_btn_home_main_main_default);
	else
		lv_style_init(&style_screen_picture_btn_home_main_main_default);
	lv_style_set_radius(&style_screen_picture_btn_home_main_main_default, 5);
	lv_style_set_bg_color(&style_screen_picture_btn_home_main_main_default, lv_color_make(0x17, 0xcf, 0x9b));
	lv_style_set_bg_grad_color(&style_screen_picture_btn_home_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_picture_btn_home_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_picture_btn_home_main_main_default, 255);
	lv_style_set_border_color(&style_screen_picture_btn_home_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_picture_btn_home_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_picture_btn_home_main_main_default, 255);
	lv_style_set_text_color(&style_screen_picture_btn_home_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_picture_btn_home_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_align(&style_screen_picture_btn_home_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_Picture_btn_Home, &style_screen_picture_btn_home_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->screen_Picture_btn_Home_label = lv_label_create(ui->screen_Picture_btn_Home);
	lv_label_set_text(ui->screen_Picture_btn_Home_label, "home");
	lv_obj_set_style_pad_all(ui->screen_Picture_btn_Home, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_Picture_btn_Home_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_Picture_btn_Switch
	ui->screen_Picture_btn_Switch = lv_btn_create(ui->screen_Picture);
	lv_obj_set_pos(ui->screen_Picture_btn_Switch, 0, 210);
	lv_obj_set_size(ui->screen_Picture_btn_Switch, 50, 30);
	lv_obj_set_scrollbar_mode(ui->screen_Picture_btn_Switch, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_picture_btn_switch_main_main_default
	static lv_style_t style_screen_picture_btn_switch_main_main_default;
	if (style_screen_picture_btn_switch_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_picture_btn_switch_main_main_default);
	else
		lv_style_init(&style_screen_picture_btn_switch_main_main_default);
	lv_style_set_radius(&style_screen_picture_btn_switch_main_main_default, 5);
	lv_style_set_bg_color(&style_screen_picture_btn_switch_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_picture_btn_switch_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_picture_btn_switch_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_picture_btn_switch_main_main_default, 255);
	lv_style_set_border_color(&style_screen_picture_btn_switch_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_picture_btn_switch_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_picture_btn_switch_main_main_default, 255);
	lv_style_set_text_color(&style_screen_picture_btn_switch_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_picture_btn_switch_main_main_default, &lv_font_Acme_Regular_14);
	lv_style_set_text_align(&style_screen_picture_btn_switch_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_Picture_btn_Switch, &style_screen_picture_btn_switch_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->screen_Picture_btn_Switch_label = lv_label_create(ui->screen_Picture_btn_Switch);
	lv_label_set_text(ui->screen_Picture_btn_Switch_label, "switch");
	lv_obj_set_style_pad_all(ui->screen_Picture_btn_Switch, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_Picture_btn_Switch_label, LV_ALIGN_CENTER, 0, 0);

	//Init events for screen
	events_init_screen_Picture(ui);
}