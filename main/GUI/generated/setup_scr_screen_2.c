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


void setup_scr_screen_2(lv_ui *ui){

	//Write codes screen_2
	ui->screen_2 = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui->screen_2, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_2_main_main_default
	static lv_style_t style_screen_2_main_main_default;
	if (style_screen_2_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_2_main_main_default);
	else
		lv_style_init(&style_screen_2_main_main_default);
	lv_style_set_bg_color(&style_screen_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_screen_2_main_main_default, 0);
	lv_obj_add_style(ui->screen_2, &style_screen_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_2_back
	ui->screen_2_back = lv_btn_create(ui->screen_2);
	lv_obj_set_pos(ui->screen_2_back, 0, 0);
	lv_obj_set_size(ui->screen_2_back, 50, 50);
	lv_obj_set_scrollbar_mode(ui->screen_2_back, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_2_back_main_main_default
	static lv_style_t style_screen_2_back_main_main_default;
	if (style_screen_2_back_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_2_back_main_main_default);
	else
		lv_style_init(&style_screen_2_back_main_main_default);
	lv_style_set_radius(&style_screen_2_back_main_main_default, 5);
	lv_style_set_bg_color(&style_screen_2_back_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_2_back_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_2_back_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_2_back_main_main_default, 255);
	lv_style_set_border_color(&style_screen_2_back_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_2_back_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_2_back_main_main_default, 255);
	lv_style_set_text_color(&style_screen_2_back_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_2_back_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_align(&style_screen_2_back_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_2_back, &style_screen_2_back_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->screen_2_back_label = lv_label_create(ui->screen_2_back);
	lv_label_set_text(ui->screen_2_back_label, "back");
	lv_obj_set_style_pad_all(ui->screen_2_back, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_2_back_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_2_sw_1
	ui->screen_2_sw_1 = lv_switch_create(ui->screen_2);
	lv_obj_set_pos(ui->screen_2_sw_1, 140, 110);
	lv_obj_set_size(ui->screen_2_sw_1, 40, 20);
	lv_obj_set_scrollbar_mode(ui->screen_2_sw_1, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_2_sw_1_main_main_default
	static lv_style_t style_screen_2_sw_1_main_main_default;
	if (style_screen_2_sw_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_2_sw_1_main_main_default);
	else
		lv_style_init(&style_screen_2_sw_1_main_main_default);
	lv_style_set_radius(&style_screen_2_sw_1_main_main_default, 100);
	lv_style_set_bg_color(&style_screen_2_sw_1_main_main_default, lv_color_make(0xe6, 0xe2, 0xe6));
	lv_style_set_bg_grad_color(&style_screen_2_sw_1_main_main_default, lv_color_make(0xe6, 0xe2, 0xe6));
	lv_style_set_bg_grad_dir(&style_screen_2_sw_1_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_2_sw_1_main_main_default, 255);
	lv_style_set_border_color(&style_screen_2_sw_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_2_sw_1_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_2_sw_1_main_main_default, 255);
	lv_obj_add_style(ui->screen_2_sw_1, &style_screen_2_sw_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_CHECKED for style_screen_2_sw_1_main_indicator_checked
	static lv_style_t style_screen_2_sw_1_main_indicator_checked;
	if (style_screen_2_sw_1_main_indicator_checked.prop_cnt > 1)
		lv_style_reset(&style_screen_2_sw_1_main_indicator_checked);
	else
		lv_style_init(&style_screen_2_sw_1_main_indicator_checked);
	lv_style_set_bg_color(&style_screen_2_sw_1_main_indicator_checked, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_2_sw_1_main_indicator_checked, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_2_sw_1_main_indicator_checked, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_2_sw_1_main_indicator_checked, 255);
	lv_style_set_border_color(&style_screen_2_sw_1_main_indicator_checked, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_2_sw_1_main_indicator_checked, 0);
	lv_style_set_border_opa(&style_screen_2_sw_1_main_indicator_checked, 255);
	lv_obj_add_style(ui->screen_2_sw_1, &style_screen_2_sw_1_main_indicator_checked, LV_PART_INDICATOR|LV_STATE_CHECKED);

	//Write style state: LV_STATE_DEFAULT for style_screen_2_sw_1_main_knob_default
	static lv_style_t style_screen_2_sw_1_main_knob_default;
	if (style_screen_2_sw_1_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_screen_2_sw_1_main_knob_default);
	else
		lv_style_init(&style_screen_2_sw_1_main_knob_default);
	lv_style_set_radius(&style_screen_2_sw_1_main_knob_default, 100);
	lv_style_set_bg_color(&style_screen_2_sw_1_main_knob_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_2_sw_1_main_knob_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_2_sw_1_main_knob_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_2_sw_1_main_knob_default, 255);
	lv_style_set_border_color(&style_screen_2_sw_1_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_2_sw_1_main_knob_default, 0);
	lv_style_set_border_opa(&style_screen_2_sw_1_main_knob_default, 255);
	lv_obj_add_style(ui->screen_2_sw_1, &style_screen_2_sw_1_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Init events for screen
	events_init_screen_2(ui);
}