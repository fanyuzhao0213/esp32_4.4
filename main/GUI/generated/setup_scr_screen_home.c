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


void setup_scr_screen_home(lv_ui *ui){

	//Write codes screen_home
	ui->screen_home = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui->screen_home, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_home_main_main_default
	static lv_style_t style_screen_home_main_main_default;
	if (style_screen_home_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_home_main_main_default);
	else
		lv_style_init(&style_screen_home_main_main_default);
	lv_style_set_bg_color(&style_screen_home_main_main_default, lv_color_make(0x41, 0x91, 0xe6));
	lv_style_set_bg_opa(&style_screen_home_main_main_default, 29);
	lv_obj_add_style(ui->screen_home, &style_screen_home_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_home_jiasu
	ui->screen_home_jiasu = lv_btn_create(ui->screen_home);
	lv_obj_set_pos(ui->screen_home_jiasu, 20, 20);
	lv_obj_set_size(ui->screen_home_jiasu, 50, 50);
	lv_obj_set_scrollbar_mode(ui->screen_home_jiasu, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_home_jiasu_main_main_default
	static lv_style_t style_screen_home_jiasu_main_main_default;
	if (style_screen_home_jiasu_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_home_jiasu_main_main_default);
	else
		lv_style_init(&style_screen_home_jiasu_main_main_default);
	lv_style_set_radius(&style_screen_home_jiasu_main_main_default, 5);
	lv_style_set_bg_color(&style_screen_home_jiasu_main_main_default, lv_color_make(0x28, 0x91, 0xe6));
	lv_style_set_bg_grad_color(&style_screen_home_jiasu_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_home_jiasu_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_home_jiasu_main_main_default, 255);
	lv_style_set_border_color(&style_screen_home_jiasu_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_home_jiasu_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_home_jiasu_main_main_default, 255);
	lv_style_set_text_color(&style_screen_home_jiasu_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_home_jiasu_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_align(&style_screen_home_jiasu_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_home_jiasu, &style_screen_home_jiasu_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->screen_home_jiasu_label = lv_label_create(ui->screen_home_jiasu);
	lv_label_set_text(ui->screen_home_jiasu_label, "加速");
	lv_obj_set_style_pad_all(ui->screen_home_jiasu, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_home_jiasu_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_home_jiansu
	ui->screen_home_jiansu = lv_btn_create(ui->screen_home);
	lv_obj_set_pos(ui->screen_home_jiansu, 20, 100);
	lv_obj_set_size(ui->screen_home_jiansu, 50, 50);
	lv_obj_set_scrollbar_mode(ui->screen_home_jiansu, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_home_jiansu_main_main_default
	static lv_style_t style_screen_home_jiansu_main_main_default;
	if (style_screen_home_jiansu_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_home_jiansu_main_main_default);
	else
		lv_style_init(&style_screen_home_jiansu_main_main_default);
	lv_style_set_radius(&style_screen_home_jiansu_main_main_default, 5);
	lv_style_set_bg_color(&style_screen_home_jiansu_main_main_default, lv_color_make(0x3c, 0xcd, 0x8e));
	lv_style_set_bg_grad_color(&style_screen_home_jiansu_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_home_jiansu_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_home_jiansu_main_main_default, 255);
	lv_style_set_border_color(&style_screen_home_jiansu_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_home_jiansu_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_home_jiansu_main_main_default, 255);
	lv_style_set_text_color(&style_screen_home_jiansu_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_home_jiansu_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_align(&style_screen_home_jiansu_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_home_jiansu, &style_screen_home_jiansu_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->screen_home_jiansu_label = lv_label_create(ui->screen_home_jiansu);
	lv_label_set_text(ui->screen_home_jiansu_label, "减速");
	lv_obj_set_style_pad_all(ui->screen_home_jiansu, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_home_jiansu_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_home_slider
	ui->screen_home_slider = lv_slider_create(ui->screen_home);
	lv_obj_set_pos(ui->screen_home_slider, 120, 120);
	lv_obj_set_size(ui->screen_home_slider, 160, 10);
	lv_obj_set_scrollbar_mode(ui->screen_home_slider, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_home_slider_main_main_default
	static lv_style_t style_screen_home_slider_main_main_default;
	if (style_screen_home_slider_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_home_slider_main_main_default);
	else
		lv_style_init(&style_screen_home_slider_main_main_default);
	lv_style_set_radius(&style_screen_home_slider_main_main_default, 50);
	lv_style_set_bg_color(&style_screen_home_slider_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_home_slider_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_home_slider_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_home_slider_main_main_default, 60);
	lv_style_set_outline_color(&style_screen_home_slider_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_outline_width(&style_screen_home_slider_main_main_default, 0);
	lv_style_set_outline_opa(&style_screen_home_slider_main_main_default, 0);
	lv_obj_add_style(ui->screen_home_slider, &style_screen_home_slider_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_home_slider_main_indicator_default
	static lv_style_t style_screen_home_slider_main_indicator_default;
	if (style_screen_home_slider_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_screen_home_slider_main_indicator_default);
	else
		lv_style_init(&style_screen_home_slider_main_indicator_default);
	lv_style_set_radius(&style_screen_home_slider_main_indicator_default, 50);
	lv_style_set_bg_color(&style_screen_home_slider_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_home_slider_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_home_slider_main_indicator_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_home_slider_main_indicator_default, 255);
	lv_obj_add_style(ui->screen_home_slider, &style_screen_home_slider_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_home_slider_main_knob_default
	static lv_style_t style_screen_home_slider_main_knob_default;
	if (style_screen_home_slider_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_screen_home_slider_main_knob_default);
	else
		lv_style_init(&style_screen_home_slider_main_knob_default);
	lv_style_set_radius(&style_screen_home_slider_main_knob_default, 50);
	lv_style_set_bg_color(&style_screen_home_slider_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_home_slider_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_home_slider_main_knob_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_home_slider_main_knob_default, 255);
	lv_obj_add_style(ui->screen_home_slider, &style_screen_home_slider_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_slider_set_range(ui->screen_home_slider,0, 100);
	lv_slider_set_value(ui->screen_home_slider,50,false);

	//Write codes screen_home_sliderText
	ui->screen_home_sliderText = lv_label_create(ui->screen_home);
	lv_obj_set_pos(ui->screen_home_sliderText, 180, 100);
	lv_obj_set_size(ui->screen_home_sliderText, 25, 10);
	lv_obj_set_scrollbar_mode(ui->screen_home_sliderText, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_home_sliderText, "50");
	lv_label_set_long_mode(ui->screen_home_sliderText, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_home_slidertext_main_main_default
	static lv_style_t style_screen_home_slidertext_main_main_default;
	if (style_screen_home_slidertext_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_home_slidertext_main_main_default);
	else
		lv_style_init(&style_screen_home_slidertext_main_main_default);
	lv_style_set_radius(&style_screen_home_slidertext_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_home_slidertext_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_home_slidertext_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_home_slidertext_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_home_slidertext_main_main_default, 0);
	lv_style_set_text_color(&style_screen_home_slidertext_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_home_slidertext_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_home_slidertext_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_home_slidertext_main_main_default, 0);
	lv_style_set_text_align(&style_screen_home_slidertext_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_home_slidertext_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_home_slidertext_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_home_slidertext_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_home_slidertext_main_main_default, 0);
	lv_obj_add_style(ui->screen_home_sliderText, &style_screen_home_slidertext_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_home_jiting
	ui->screen_home_jiting = lv_btn_create(ui->screen_home);
	lv_obj_set_pos(ui->screen_home_jiting, 20, 180);
	lv_obj_set_size(ui->screen_home_jiting, 50, 50);
	lv_obj_set_scrollbar_mode(ui->screen_home_jiting, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_home_jiting_main_main_default
	static lv_style_t style_screen_home_jiting_main_main_default;
	if (style_screen_home_jiting_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_home_jiting_main_main_default);
	else
		lv_style_init(&style_screen_home_jiting_main_main_default);
	lv_style_set_radius(&style_screen_home_jiting_main_main_default, 5);
	lv_style_set_bg_color(&style_screen_home_jiting_main_main_default, lv_color_make(0xdb, 0x0a, 0x3f));
	lv_style_set_bg_grad_color(&style_screen_home_jiting_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_home_jiting_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_home_jiting_main_main_default, 255);
	lv_style_set_border_color(&style_screen_home_jiting_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_home_jiting_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_home_jiting_main_main_default, 255);
	lv_style_set_text_color(&style_screen_home_jiting_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_home_jiting_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_align(&style_screen_home_jiting_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_home_jiting, &style_screen_home_jiting_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->screen_home_jiting_label = lv_label_create(ui->screen_home_jiting);
	lv_label_set_text(ui->screen_home_jiting_label, "急停");
	lv_obj_set_style_pad_all(ui->screen_home_jiting, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_home_jiting_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_home_led
	ui->screen_home_led = lv_led_create(ui->screen_home);
	lv_obj_set_pos(ui->screen_home_led, 180, 47);
	lv_obj_set_size(ui->screen_home_led, 40, 40);
	lv_obj_set_scrollbar_mode(ui->screen_home_led, LV_SCROLLBAR_MODE_OFF);
	lv_led_set_brightness(ui->screen_home_led, 255);
	lv_led_set_color(ui->screen_home_led, lv_color_make(0x00, 0xa1, 0xb5));

	//Write codes screen_home_Next
	ui->screen_home_Next = lv_btn_create(ui->screen_home);
	lv_obj_set_pos(ui->screen_home_Next, 242, 180);
	lv_obj_set_size(ui->screen_home_Next, 50, 50);
	lv_obj_set_scrollbar_mode(ui->screen_home_Next, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_home_next_main_main_default
	static lv_style_t style_screen_home_next_main_main_default;
	if (style_screen_home_next_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_home_next_main_main_default);
	else
		lv_style_init(&style_screen_home_next_main_main_default);
	lv_style_set_radius(&style_screen_home_next_main_main_default, 5);
	lv_style_set_bg_color(&style_screen_home_next_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_home_next_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_home_next_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_home_next_main_main_default, 255);
	lv_style_set_border_color(&style_screen_home_next_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_home_next_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_home_next_main_main_default, 255);
	lv_style_set_text_color(&style_screen_home_next_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_home_next_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_align(&style_screen_home_next_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_home_Next, &style_screen_home_next_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->screen_home_Next_label = lv_label_create(ui->screen_home_Next);
	lv_label_set_text(ui->screen_home_Next_label, "下一页");
	lv_obj_set_style_pad_all(ui->screen_home_Next, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_home_Next_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_home_sw_led
	ui->screen_home_sw_led = lv_switch_create(ui->screen_home);
	lv_obj_set_pos(ui->screen_home_sw_led, 140, 195);
	lv_obj_set_size(ui->screen_home_sw_led, 40, 20);
	lv_obj_set_scrollbar_mode(ui->screen_home_sw_led, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_home_sw_led_main_main_default
	static lv_style_t style_screen_home_sw_led_main_main_default;
	if (style_screen_home_sw_led_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_home_sw_led_main_main_default);
	else
		lv_style_init(&style_screen_home_sw_led_main_main_default);
	lv_style_set_radius(&style_screen_home_sw_led_main_main_default, 100);
	lv_style_set_bg_color(&style_screen_home_sw_led_main_main_default, lv_color_make(0x32, 0xc3, 0xb9));
	lv_style_set_bg_grad_color(&style_screen_home_sw_led_main_main_default, lv_color_make(0xe6, 0xe2, 0xe6));
	lv_style_set_bg_grad_dir(&style_screen_home_sw_led_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_home_sw_led_main_main_default, 255);
	lv_style_set_border_color(&style_screen_home_sw_led_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_home_sw_led_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_home_sw_led_main_main_default, 255);
	lv_obj_add_style(ui->screen_home_sw_led, &style_screen_home_sw_led_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_CHECKED for style_screen_home_sw_led_main_indicator_checked
	static lv_style_t style_screen_home_sw_led_main_indicator_checked;
	if (style_screen_home_sw_led_main_indicator_checked.prop_cnt > 1)
		lv_style_reset(&style_screen_home_sw_led_main_indicator_checked);
	else
		lv_style_init(&style_screen_home_sw_led_main_indicator_checked);
	lv_style_set_bg_color(&style_screen_home_sw_led_main_indicator_checked, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_home_sw_led_main_indicator_checked, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_home_sw_led_main_indicator_checked, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_home_sw_led_main_indicator_checked, 255);
	lv_style_set_border_color(&style_screen_home_sw_led_main_indicator_checked, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_home_sw_led_main_indicator_checked, 0);
	lv_style_set_border_opa(&style_screen_home_sw_led_main_indicator_checked, 255);
	lv_obj_add_style(ui->screen_home_sw_led, &style_screen_home_sw_led_main_indicator_checked, LV_PART_INDICATOR|LV_STATE_CHECKED);

	//Write style state: LV_STATE_DEFAULT for style_screen_home_sw_led_main_knob_default
	static lv_style_t style_screen_home_sw_led_main_knob_default;
	if (style_screen_home_sw_led_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_screen_home_sw_led_main_knob_default);
	else
		lv_style_init(&style_screen_home_sw_led_main_knob_default);
	lv_style_set_radius(&style_screen_home_sw_led_main_knob_default, 100);
	lv_style_set_bg_color(&style_screen_home_sw_led_main_knob_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_home_sw_led_main_knob_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_home_sw_led_main_knob_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_home_sw_led_main_knob_default, 255);
	lv_style_set_border_color(&style_screen_home_sw_led_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_home_sw_led_main_knob_default, 0);
	lv_style_set_border_opa(&style_screen_home_sw_led_main_knob_default, 255);
	lv_obj_add_style(ui->screen_home_sw_led, &style_screen_home_sw_led_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_home_label_led
	ui->screen_home_label_led = lv_label_create(ui->screen_home);
	lv_obj_set_pos(ui->screen_home_label_led, 135, 180);
	lv_obj_set_size(ui->screen_home_label_led, 50, 10);
	lv_obj_set_scrollbar_mode(ui->screen_home_label_led, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_home_label_led, "LED");
	lv_label_set_long_mode(ui->screen_home_label_led, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_home_label_led_main_main_default
	static lv_style_t style_screen_home_label_led_main_main_default;
	if (style_screen_home_label_led_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_home_label_led_main_main_default);
	else
		lv_style_init(&style_screen_home_label_led_main_main_default);
	lv_style_set_radius(&style_screen_home_label_led_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_home_label_led_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_home_label_led_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_home_label_led_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_home_label_led_main_main_default, 0);
	lv_style_set_text_color(&style_screen_home_label_led_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_home_label_led_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_home_label_led_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_home_label_led_main_main_default, 0);
	lv_style_set_text_align(&style_screen_home_label_led_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_home_label_led_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_home_label_led_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_home_label_led_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_home_label_led_main_main_default, 0);
	lv_obj_add_style(ui->screen_home_label_led, &style_screen_home_label_led_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Init events for screen
	events_init_screen_home(ui);
}