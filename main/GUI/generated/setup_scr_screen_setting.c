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

static void screen_setting_calendardraw_part_begin_event_cb(lv_event_t * e)
{
	lv_obj_t * obj = lv_event_get_target(e);
	lv_obj_draw_part_dsc_t * dsc = lv_event_get_param(e);
	if(dsc->part == LV_PART_ITEMS) {
		if(dsc->id < 7) {
			dsc->label_dsc->color = lv_color_make(0x0D, 0x30, 0x55);
			dsc->label_dsc->font = &lv_font_simsun_12;
		}	else if (lv_btnmatrix_has_btn_ctrl(obj, dsc->id, LV_BTNMATRIX_CTRL_DISABLED)) {
			dsc->rect_dsc->bg_color = lv_color_make(0x01, 0xa2, 0xb1);
			dsc->rect_dsc->bg_grad.stops_count = 2;
			dsc->rect_dsc->bg_grad.dir = LV_GRAD_DIR_NONE;
			dsc->rect_dsc->bg_grad.stops[0].color = lv_color_make(0x01, 0xa2, 0xb1);
			dsc->rect_dsc->bg_grad.stops[1].color = lv_color_make(0x01, 0xa2, 0xb1);
			dsc->rect_dsc->bg_opa = 0;
			dsc->label_dsc->color = lv_color_make(0xA9, 0xA2, 0xA2);
			dsc->label_dsc->font = &lv_font_simsun_12;
		}		else if(lv_btnmatrix_has_btn_ctrl(obj, dsc->id, LV_BTNMATRIX_CTRL_CUSTOM_1)) {
			dsc->rect_dsc->bg_color = lv_color_make(0x01, 0xa2, 0xb1);
			dsc->rect_dsc->bg_grad.stops_count = 2;
			dsc->rect_dsc->bg_grad.dir = LV_GRAD_DIR_NONE;
			dsc->rect_dsc->bg_grad.stops[0].color = lv_color_make(0x01, 0xa2, 0xb1);
			dsc->rect_dsc->bg_grad.stops[1].color = lv_color_make(0x01, 0xa2, 0xb1);
			dsc->rect_dsc->bg_opa = 255;
			dsc->rect_dsc->border_color = lv_color_make(0xc0, 0xc0, 0xc0);
			dsc->rect_dsc->border_width = 1;
			dsc->rect_dsc->border_opa = 255;
			dsc->label_dsc->color = lv_color_make(0x0D, 0x30, 0x55);
			dsc->label_dsc->font = &lv_font_simsun_12;
		}
		else if(lv_btnmatrix_has_btn_ctrl(obj, dsc->id, LV_BTNMATRIX_CTRL_CUSTOM_2)) {
			dsc->rect_dsc->bg_color = lv_color_make(0x21, 0x95, 0xf6);
			dsc->rect_dsc->bg_grad.stops_count = 2;
			dsc->rect_dsc->bg_grad.dir = LV_GRAD_DIR_NONE;
			dsc->rect_dsc->bg_grad.stops[0].color = lv_color_make(0x21, 0x95, 0xf6);
			dsc->rect_dsc->bg_grad.stops[1].color = lv_color_make(0x21, 0x95, 0xf6);
			dsc->rect_dsc->bg_opa = 255;
			dsc->label_dsc->color = lv_color_make(0x0D, 0x30, 0x55);
			dsc->label_dsc->font = &lv_font_simsun_12;
		}	else {
			dsc->rect_dsc->bg_color = lv_color_make(0x01, 0xa2, 0xb1);
			dsc->rect_dsc->bg_grad.stops_count = 2;
			dsc->rect_dsc->bg_grad.dir = LV_GRAD_DIR_NONE;
			dsc->rect_dsc->bg_grad.stops[0].color = lv_color_make(0x01, 0xa2, 0xb1);
			dsc->rect_dsc->bg_grad.stops[1].color = lv_color_make(0x01, 0xa2, 0xb1);
			dsc->rect_dsc->bg_opa = 0;
			dsc->rect_dsc->border_color = lv_color_make(0xc0, 0xc0, 0xc0);
			dsc->rect_dsc->border_width = 1;
			dsc->rect_dsc->border_opa = 255;
			dsc->label_dsc->color = lv_color_make(0x0D, 0x30, 0x55);
			dsc->label_dsc->font = &lv_font_simsun_12;
		}
	}
}
static lv_obj_t * g_kb;
static void kb_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *kb = lv_event_get_target(e);
	if(code == LV_EVENT_READY || code == LV_EVENT_CANCEL){
		lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
	}
}
static void ta_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *ta = lv_event_get_target(e);
	lv_obj_t *kb = lv_event_get_user_data(e);
	if (code == LV_EVENT_FOCUSED)
	{
		lv_keyboard_set_textarea(kb, ta);
		lv_obj_move_foreground(kb);
		lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
	}
	if (code == LV_EVENT_DEFOCUSED)
	{
		lv_keyboard_set_textarea(kb, NULL);
		lv_obj_move_background(kb);
		lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
	}
}

void setup_scr_screen_setting(lv_ui *ui){

	static lv_style_t style_faint_blue;
	if (style_faint_blue.prop_cnt > 1)
		lv_style_reset(&style_faint_blue);
	else
		lv_style_init(&style_faint_blue);
	lv_style_init(&style_faint_blue);
	// 设置字体颜色为淡灰蓝
	lv_style_set_text_color(&style_faint_blue, lv_color_make(0x90, 0xA4, 0xC4));
	// 设置字体透明度（可选，更虚幻）
	lv_style_set_text_opa(&style_faint_blue, LV_OPA_80);

	// 应用到所有 TextArea

	//Write codes screen_setting
	ui->screen_setting = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui->screen_setting, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_setting_main_main_default
	static lv_style_t style_screen_setting_main_main_default;
	if (style_screen_setting_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_setting_main_main_default);
	else
		lv_style_init(&style_screen_setting_main_main_default);
	lv_style_set_bg_color(&style_screen_setting_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_screen_setting_main_main_default, 0);
	lv_obj_add_style(ui->screen_setting, &style_screen_setting_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_setting_tabview
	ui->screen_setting_tabview = lv_tabview_create(ui->screen_setting, LV_DIR_TOP, 50);
	lv_obj_set_pos(ui->screen_setting_tabview, 0, 0);
	lv_obj_set_size(ui->screen_setting_tabview, 320, 40);

	//BoardInfo
	ui->screen_setting_tabview_BoardInfo = lv_tabview_add_tab(ui->screen_setting_tabview,"BoardInfo");

	//MUSIC
	ui->screen_setting_tabview_MUSIC = lv_tabview_add_tab(ui->screen_setting_tabview,"MUSIC");
	lv_obj_t * screen_setting_tabview_MUSIC_label = lv_label_create(ui->screen_setting_tabview_MUSIC);
	lv_label_set_text(screen_setting_tabview_MUSIC_label, "con2");


	//Write style state: LV_STATE_DEFAULT for style_screen_setting_tabview_main_main_default
	static lv_style_t style_screen_setting_tabview_main_main_default;
	if (style_screen_setting_tabview_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_setting_tabview_main_main_default);
	else
		lv_style_init(&style_screen_setting_tabview_main_main_default);
	lv_style_set_radius(&style_screen_setting_tabview_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_setting_tabview_main_main_default, lv_color_make(0x10, 0x1d, 0x28));
	lv_style_set_bg_grad_color(&style_screen_setting_tabview_main_main_default, lv_color_make(0xea, 0xef, 0xf3));
	lv_style_set_bg_grad_dir(&style_screen_setting_tabview_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_setting_tabview_main_main_default, 170);
	lv_style_set_border_color(&style_screen_setting_tabview_main_main_default, lv_color_make(0xc0, 0xc0, 0xc0));
	lv_style_set_border_width(&style_screen_setting_tabview_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_setting_tabview_main_main_default, 100);
	lv_style_set_text_color(&style_screen_setting_tabview_main_main_default, lv_color_make(0x1d, 0x46, 0xa5));
	lv_style_set_text_font(&style_screen_setting_tabview_main_main_default, &lv_font_Acme_Regular_20);
	lv_style_set_text_letter_space(&style_screen_setting_tabview_main_main_default, 1);
	lv_style_set_text_line_space(&style_screen_setting_tabview_main_main_default, 16);
	lv_obj_add_style(ui->screen_setting_tabview, &style_screen_setting_tabview_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_setting_tabview_extra_btnm_main_default
	static lv_style_t style_screen_setting_tabview_extra_btnm_main_default;
	if (style_screen_setting_tabview_extra_btnm_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_setting_tabview_extra_btnm_main_default);
	else
		lv_style_init(&style_screen_setting_tabview_extra_btnm_main_default);
	lv_style_set_radius(&style_screen_setting_tabview_extra_btnm_main_default, 0);
	lv_style_set_bg_color(&style_screen_setting_tabview_extra_btnm_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_setting_tabview_extra_btnm_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_setting_tabview_extra_btnm_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_setting_tabview_extra_btnm_main_default, 255);
	lv_style_set_border_color(&style_screen_setting_tabview_extra_btnm_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_setting_tabview_extra_btnm_main_default, 0);
	lv_style_set_border_opa(&style_screen_setting_tabview_extra_btnm_main_default, 100);
	lv_style_set_pad_left(&style_screen_setting_tabview_extra_btnm_main_default, 0);
	lv_style_set_pad_right(&style_screen_setting_tabview_extra_btnm_main_default, 0);
	lv_style_set_pad_top(&style_screen_setting_tabview_extra_btnm_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_setting_tabview_extra_btnm_main_default, 0);
	lv_obj_add_style(lv_tabview_get_tab_btns(ui->screen_setting_tabview), &style_screen_setting_tabview_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_setting_tabview_extra_btnm_items_default
	static lv_style_t style_screen_setting_tabview_extra_btnm_items_default;
	if (style_screen_setting_tabview_extra_btnm_items_default.prop_cnt > 1)
		lv_style_reset(&style_screen_setting_tabview_extra_btnm_items_default);
	else
		lv_style_init(&style_screen_setting_tabview_extra_btnm_items_default);
	lv_style_set_text_color(&style_screen_setting_tabview_extra_btnm_items_default, lv_color_make(0x4d, 0x4d, 0x4d));
	lv_style_set_text_font(&style_screen_setting_tabview_extra_btnm_items_default, &lv_font_simsun_12);
	lv_obj_add_style(lv_tabview_get_tab_btns(ui->screen_setting_tabview), &style_screen_setting_tabview_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_CHECKED for style_screen_setting_tabview_extra_btnm_items_checked
	static lv_style_t style_screen_setting_tabview_extra_btnm_items_checked;
	if (style_screen_setting_tabview_extra_btnm_items_checked.prop_cnt > 1)
		lv_style_reset(&style_screen_setting_tabview_extra_btnm_items_checked);
	else
		lv_style_init(&style_screen_setting_tabview_extra_btnm_items_checked);
	lv_style_set_radius(&style_screen_setting_tabview_extra_btnm_items_checked, 0);
	lv_style_set_bg_color(&style_screen_setting_tabview_extra_btnm_items_checked, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_setting_tabview_extra_btnm_items_checked, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_setting_tabview_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_setting_tabview_extra_btnm_items_checked, 60);
	lv_style_set_border_color(&style_screen_setting_tabview_extra_btnm_items_checked, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_setting_tabview_extra_btnm_items_checked, 4);
	lv_style_set_border_opa(&style_screen_setting_tabview_extra_btnm_items_checked, 255);
	lv_style_set_border_side(&style_screen_setting_tabview_extra_btnm_items_checked, LV_BORDER_SIDE_BOTTOM);
	lv_style_set_text_color(&style_screen_setting_tabview_extra_btnm_items_checked, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_text_font(&style_screen_setting_tabview_extra_btnm_items_checked, &lv_font_simsun_12);
	lv_obj_add_style(lv_tabview_get_tab_btns(ui->screen_setting_tabview), &style_screen_setting_tabview_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

	//Write codes screen_setting_tileview
	ui->screen_setting_tileview = lv_tileview_create(ui->screen_setting);
	lv_obj_set_pos(ui->screen_setting_tileview, 0, 40);
	lv_obj_set_size(ui->screen_setting_tileview, 320, 200);
	lv_obj_set_scrollbar_mode(ui->screen_setting_tileview, LV_SCROLLBAR_MODE_ON);

	//Write style state: LV_STATE_DEFAULT for style_screen_setting_tileview_main_main_default
	static lv_style_t style_screen_setting_tileview_main_main_default;
	if (style_screen_setting_tileview_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_setting_tileview_main_main_default);
	else
		lv_style_init(&style_screen_setting_tileview_main_main_default);
	lv_style_set_radius(&style_screen_setting_tileview_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_setting_tileview_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_setting_tileview_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_setting_tileview_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_setting_tileview_main_main_default, 255);
	lv_obj_add_style(ui->screen_setting_tileview, &style_screen_setting_tileview_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_setting_tileview_main_scrollbar_default
	static lv_style_t style_screen_setting_tileview_main_scrollbar_default;
	if (style_screen_setting_tileview_main_scrollbar_default.prop_cnt > 1)
		lv_style_reset(&style_screen_setting_tileview_main_scrollbar_default);
	else
		lv_style_init(&style_screen_setting_tileview_main_scrollbar_default);
	lv_style_set_radius(&style_screen_setting_tileview_main_scrollbar_default, 0);
	lv_style_set_bg_color(&style_screen_setting_tileview_main_scrollbar_default, lv_color_make(0xea, 0xef, 0xf3));
	lv_style_set_bg_opa(&style_screen_setting_tileview_main_scrollbar_default, 255);
	lv_obj_add_style(ui->screen_setting_tileview, &style_screen_setting_tileview_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//add new tile tileview_BoardInfo
	ui->tileview_BoardInfo = lv_tileview_add_tile(ui->screen_setting_tileview, 0, 0, LV_DIR_RIGHT);

	//Write codes screen_setting_ta_angle
	ui->screen_setting_ta_angle = lv_textarea_create(ui->tileview_BoardInfo);
	lv_obj_set_pos(ui->screen_setting_ta_angle, 50, 120);
	lv_obj_set_size(ui->screen_setting_ta_angle, 230, 20);
	lv_obj_set_scrollbar_mode(ui->screen_setting_ta_angle, LV_SCROLLBAR_MODE_OFF);
	lv_textarea_set_text(ui->screen_setting_ta_angle,"NULL");
	lv_textarea_set_one_line(ui->screen_setting_ta_angle, true);  // Set to single-line mode
	lv_obj_add_style(ui->screen_setting_ta_angle, &style_faint_blue, LV_PART_MAIN);

	//Write codes screen_setting_ta_acceleration
	ui->screen_setting_ta_acceleration = lv_textarea_create(ui->tileview_BoardInfo);
	lv_obj_set_pos(ui->screen_setting_ta_acceleration, 50, 170);
	lv_obj_set_size(ui->screen_setting_ta_acceleration, 230, 20);
	lv_obj_set_scrollbar_mode(ui->screen_setting_ta_acceleration, LV_SCROLLBAR_MODE_OFF);
	lv_textarea_set_text(ui->screen_setting_ta_acceleration,"NULL");
	lv_textarea_set_one_line(ui->screen_setting_ta_acceleration, true);  // Set to single-line mode
	lv_obj_add_style(ui->screen_setting_ta_acceleration, &style_faint_blue, LV_PART_MAIN);

	//Write codes screen_setting_ta_acceleration
	ui->screen_setting_ta_Rtc = lv_textarea_create(ui->tileview_BoardInfo);
	lv_obj_set_pos(ui->screen_setting_ta_Rtc, 50, 220);
	lv_obj_set_size(ui->screen_setting_ta_Rtc, 230, 20);
	lv_obj_set_scrollbar_mode(ui->screen_setting_ta_Rtc, LV_SCROLLBAR_MODE_OFF);
	lv_textarea_set_text(ui->screen_setting_ta_Rtc,"NULL");
	lv_textarea_set_one_line(ui->screen_setting_ta_Rtc, true);  // Set to single-line mode
	lv_obj_add_style(ui->screen_setting_ta_Rtc, &style_faint_blue, LV_PART_MAIN);

	ui->screen_setting_ta_BoardInfo = lv_textarea_create(ui->tileview_BoardInfo);
	lv_obj_set_pos(ui->screen_setting_ta_BoardInfo, 50, 270);
	lv_obj_set_size(ui->screen_setting_ta_BoardInfo, 230, 20);
	lv_obj_set_scrollbar_mode(ui->screen_setting_ta_BoardInfo, LV_SCROLLBAR_MODE_OFF);
	lv_textarea_set_text(ui->screen_setting_ta_BoardInfo,"NULL");
	lv_textarea_set_one_line(ui->screen_setting_ta_BoardInfo, true);  // Set to single-line mode
	lv_obj_add_style(ui->screen_setting_ta_BoardInfo, &style_faint_blue, LV_PART_MAIN);

	ui->screen_setting_label_4 = lv_label_create(ui->tileview_BoardInfo);
	lv_obj_set_pos(ui->screen_setting_label_4, 50, 200);
	lv_obj_set_size(ui->screen_setting_label_4, 100, 15);
	lv_obj_set_scrollbar_mode(ui->screen_setting_label_4, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_setting_label_4, "rtc");
	lv_label_set_long_mode(ui->screen_setting_label_4, LV_LABEL_LONG_WRAP);

	ui->screen_setting_label_5 = lv_label_create(ui->tileview_BoardInfo);
	lv_obj_set_pos(ui->screen_setting_label_5, 50, 250);
	lv_obj_set_size(ui->screen_setting_label_5, 100, 15);
	lv_obj_set_scrollbar_mode(ui->screen_setting_label_5, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_setting_label_5, "BoardInfo");
	lv_label_set_long_mode(ui->screen_setting_label_5, LV_LABEL_LONG_WRAP);

	//Write codes screen_setting_label_3
	ui->screen_setting_label_3 = lv_label_create(ui->tileview_BoardInfo);
	lv_obj_set_pos(ui->screen_setting_label_3, 50, 150);
	lv_obj_set_size(ui->screen_setting_label_3, 100, 15);
	lv_obj_set_scrollbar_mode(ui->screen_setting_label_3, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_setting_label_3, "acceleration");
	lv_label_set_long_mode(ui->screen_setting_label_3, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_setting_label_3_main_main_default
	static lv_style_t style_screen_setting_label_3_main_main_default;
	if (style_screen_setting_label_3_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_setting_label_3_main_main_default);
	else
		lv_style_init(&style_screen_setting_label_3_main_main_default);
	lv_style_set_radius(&style_screen_setting_label_3_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_setting_label_3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_setting_label_3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_setting_label_3_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_setting_label_3_main_main_default, 0);
	lv_style_set_text_color(&style_screen_setting_label_3_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_setting_label_3_main_main_default, &lv_font_Acme_Regular_14);
	lv_style_set_text_letter_space(&style_screen_setting_label_3_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_setting_label_3_main_main_default, 0);
	lv_style_set_text_align(&style_screen_setting_label_3_main_main_default, LV_TEXT_ALIGN_LEFT);
	lv_style_set_pad_left(&style_screen_setting_label_3_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_setting_label_3_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_setting_label_3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_setting_label_3_main_main_default, 0);
	lv_obj_add_style(ui->screen_setting_label_3, &style_screen_setting_label_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_setting_label_angle
	ui->screen_setting_label_angle = lv_label_create(ui->tileview_BoardInfo);
	lv_obj_set_pos(ui->screen_setting_label_angle, 50, 100);
	lv_obj_set_size(ui->screen_setting_label_angle, 100, 15);
	lv_obj_set_scrollbar_mode(ui->screen_setting_label_angle, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_setting_label_angle, "angle");
	lv_label_set_long_mode(ui->screen_setting_label_angle, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_setting_label_angle_main_main_default
	static lv_style_t style_screen_setting_label_angle_main_main_default;
	if (style_screen_setting_label_angle_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_setting_label_angle_main_main_default);
	else
		lv_style_init(&style_screen_setting_label_angle_main_main_default);
	lv_style_set_radius(&style_screen_setting_label_angle_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_setting_label_angle_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_setting_label_angle_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_setting_label_angle_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_setting_label_angle_main_main_default, 0);
	lv_style_set_text_color(&style_screen_setting_label_angle_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_setting_label_angle_main_main_default, &lv_font_Acme_Regular_14);
	lv_style_set_text_letter_space(&style_screen_setting_label_angle_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_setting_label_angle_main_main_default, 0);
	lv_style_set_text_align(&style_screen_setting_label_angle_main_main_default, LV_TEXT_ALIGN_LEFT);
	lv_style_set_pad_left(&style_screen_setting_label_angle_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_setting_label_angle_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_setting_label_angle_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_setting_label_angle_main_main_default, 0);
	lv_obj_add_style(ui->screen_setting_label_angle, &style_screen_setting_label_angle_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_setting_ta_Voltage
	ui->screen_setting_ta_Voltage = lv_textarea_create(ui->tileview_BoardInfo);
	lv_obj_set_pos(ui->screen_setting_ta_Voltage, 50, 70);
	lv_obj_set_size(ui->screen_setting_ta_Voltage, 200, 20);
	lv_obj_set_scrollbar_mode(ui->screen_setting_ta_Voltage, LV_SCROLLBAR_MODE_OFF);
	lv_textarea_set_text(ui->screen_setting_ta_Voltage,"NULL");
	lv_textarea_set_one_line(ui->screen_setting_ta_Voltage, true);  // Set to single-line mode
	lv_obj_add_style(ui->screen_setting_ta_Voltage, &style_faint_blue, LV_PART_MAIN);

	//Write codes screen_setting_label_2
	ui->screen_setting_label_2 = lv_label_create(ui->tileview_BoardInfo);
	lv_obj_set_pos(ui->screen_setting_label_2, 50, 50);
	lv_obj_set_size(ui->screen_setting_label_2, 100, 15);
	lv_obj_set_scrollbar_mode(ui->screen_setting_label_2, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_setting_label_2, "voltage");
	lv_label_set_long_mode(ui->screen_setting_label_2, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_setting_label_2_main_main_default
	static lv_style_t style_screen_setting_label_2_main_main_default;
	if (style_screen_setting_label_2_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_setting_label_2_main_main_default);
	else
		lv_style_init(&style_screen_setting_label_2_main_main_default);
	lv_style_set_radius(&style_screen_setting_label_2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_setting_label_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_setting_label_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_setting_label_2_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_setting_label_2_main_main_default, 0);
	lv_style_set_text_color(&style_screen_setting_label_2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_setting_label_2_main_main_default, &lv_font_Acme_Regular_14);
	lv_style_set_text_letter_space(&style_screen_setting_label_2_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_setting_label_2_main_main_default, 0);
	lv_style_set_text_align(&style_screen_setting_label_2_main_main_default, LV_TEXT_ALIGN_LEFT);
	lv_style_set_pad_left(&style_screen_setting_label_2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_setting_label_2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_setting_label_2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_setting_label_2_main_main_default, 0);
	lv_obj_add_style(ui->screen_setting_label_2, &style_screen_setting_label_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_setting_slider_backlight
	ui->screen_setting_slider_backlight = lv_slider_create(ui->tileview_BoardInfo);
	lv_obj_set_pos(ui->screen_setting_slider_backlight, 50, 30);
	lv_obj_set_size(ui->screen_setting_slider_backlight, 200, 10);
	lv_obj_set_scrollbar_mode(ui->screen_setting_slider_backlight, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_setting_slider_backlight_main_main_default
	static lv_style_t style_screen_setting_slider_backlight_main_main_default;
	if (style_screen_setting_slider_backlight_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_setting_slider_backlight_main_main_default);
	else
		lv_style_init(&style_screen_setting_slider_backlight_main_main_default);
	lv_style_set_radius(&style_screen_setting_slider_backlight_main_main_default, 50);
	lv_style_set_bg_color(&style_screen_setting_slider_backlight_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_setting_slider_backlight_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_setting_slider_backlight_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_setting_slider_backlight_main_main_default, 60);
	lv_style_set_outline_color(&style_screen_setting_slider_backlight_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_outline_width(&style_screen_setting_slider_backlight_main_main_default, 0);
	lv_style_set_outline_opa(&style_screen_setting_slider_backlight_main_main_default, 0);
	lv_obj_add_style(ui->screen_setting_slider_backlight, &style_screen_setting_slider_backlight_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_setting_slider_backlight_main_indicator_default
	static lv_style_t style_screen_setting_slider_backlight_main_indicator_default;
	if (style_screen_setting_slider_backlight_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_screen_setting_slider_backlight_main_indicator_default);
	else
		lv_style_init(&style_screen_setting_slider_backlight_main_indicator_default);
	lv_style_set_radius(&style_screen_setting_slider_backlight_main_indicator_default, 50);
	lv_style_set_bg_color(&style_screen_setting_slider_backlight_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_setting_slider_backlight_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_setting_slider_backlight_main_indicator_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_setting_slider_backlight_main_indicator_default, 255);
	lv_obj_add_style(ui->screen_setting_slider_backlight, &style_screen_setting_slider_backlight_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_setting_slider_backlight_main_knob_default
	static lv_style_t style_screen_setting_slider_backlight_main_knob_default;
	if (style_screen_setting_slider_backlight_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_screen_setting_slider_backlight_main_knob_default);
	else
		lv_style_init(&style_screen_setting_slider_backlight_main_knob_default);
	lv_style_set_radius(&style_screen_setting_slider_backlight_main_knob_default, 50);
	lv_style_set_bg_color(&style_screen_setting_slider_backlight_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_setting_slider_backlight_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_setting_slider_backlight_main_knob_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_setting_slider_backlight_main_knob_default, 255);
	lv_obj_add_style(ui->screen_setting_slider_backlight, &style_screen_setting_slider_backlight_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_slider_set_range(ui->screen_setting_slider_backlight,0, 100);
	lv_slider_set_value(ui->screen_setting_slider_backlight,50,false);

	//Write codes screen_setting_label_1
	ui->screen_setting_label_1 = lv_label_create(ui->tileview_BoardInfo);
	lv_obj_set_pos(ui->screen_setting_label_1, 50, 10);
	lv_obj_set_size(ui->screen_setting_label_1, 100, 15);
	lv_obj_set_scrollbar_mode(ui->screen_setting_label_1, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_setting_label_1, "BackLight");
	lv_label_set_long_mode(ui->screen_setting_label_1, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_setting_label_1_main_main_default
	static lv_style_t style_screen_setting_label_1_main_main_default;
	if (style_screen_setting_label_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_setting_label_1_main_main_default);
	else
		lv_style_init(&style_screen_setting_label_1_main_main_default);
	lv_style_set_radius(&style_screen_setting_label_1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_setting_label_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_setting_label_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_setting_label_1_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_setting_label_1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_setting_label_1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_setting_label_1_main_main_default, &lv_font_Acme_Regular_14);
	lv_style_set_text_letter_space(&style_screen_setting_label_1_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_setting_label_1_main_main_default, 0);
	lv_style_set_text_align(&style_screen_setting_label_1_main_main_default, LV_TEXT_ALIGN_LEFT);
	lv_style_set_pad_left(&style_screen_setting_label_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_setting_label_1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_setting_label_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_setting_label_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_setting_label_1, &style_screen_setting_label_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	//add new tile tileview_Test
	ui->tileview_Test = lv_tileview_add_tile(ui->screen_setting_tileview, 1 , 0, LV_DIR_LEFT);

	//Write codes screen_setting_calendar
	ui->screen_setting_calendar = lv_calendar_create(ui->tileview_Test);
	lv_obj_set_pos(ui->screen_setting_calendar, 0, 0);
	lv_obj_set_size(ui->screen_setting_calendar, 320, 200);
	lv_obj_set_scrollbar_mode(ui->screen_setting_calendar, LV_SCROLLBAR_MODE_OFF);
	today.year = 2020;
	today.month = 5;
	today.day = 7;
	lv_calendar_set_today_date(ui->screen_setting_calendar, today.year, today.month, today.day);
	lv_calendar_set_showed_date(ui->screen_setting_calendar, today.year, today.month);
	highlihted_days[0].year = 2020;
	highlihted_days[0].month = 5;
	highlihted_days[0].day = 14;
	lv_calendar_set_highlighted_dates(ui->screen_setting_calendar, highlihted_days, 1);
	lv_obj_t *screen_setting_calendar_header = lv_calendar_header_arrow_create(ui->screen_setting_calendar);
	lv_calendar_t * screen_setting_calendar = (lv_calendar_t *)ui->screen_setting_calendar;
	lv_obj_add_event_cb(screen_setting_calendar->btnm, screen_setting_calendardraw_part_begin_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);

	//Write style state: LV_STATE_DEFAULT for style_screen_setting_calendar_main_main_default
	static lv_style_t style_screen_setting_calendar_main_main_default;
	if (style_screen_setting_calendar_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_setting_calendar_main_main_default);
	else
		lv_style_init(&style_screen_setting_calendar_main_main_default);
	lv_style_set_radius(&style_screen_setting_calendar_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_setting_calendar_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_setting_calendar_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_setting_calendar_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_setting_calendar_main_main_default, 255);
	lv_style_set_border_color(&style_screen_setting_calendar_main_main_default, lv_color_make(0xc0, 0xc0, 0xc0));
	lv_style_set_border_width(&style_screen_setting_calendar_main_main_default, 1);
	lv_style_set_border_opa(&style_screen_setting_calendar_main_main_default, 255);
	lv_obj_add_style(ui->screen_setting_calendar, &style_screen_setting_calendar_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_setting_calendar_extra_header_main_default
	static lv_style_t style_screen_setting_calendar_extra_header_main_default;
	if (style_screen_setting_calendar_extra_header_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_setting_calendar_extra_header_main_default);
	else
		lv_style_init(&style_screen_setting_calendar_extra_header_main_default);
	lv_style_set_bg_color(&style_screen_setting_calendar_extra_header_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_setting_calendar_extra_header_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_setting_calendar_extra_header_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_setting_calendar_extra_header_main_default, 255);
	lv_style_set_text_color(&style_screen_setting_calendar_extra_header_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_setting_calendar_extra_header_main_default, &lv_font_Acme_Regular_14);
	lv_obj_add_style(screen_setting_calendar_header, &style_screen_setting_calendar_extra_header_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_setting_btn_home
	ui->screen_setting_btn_home = lv_btn_create(ui->screen_setting);
	lv_obj_set_pos(ui->screen_setting_btn_home, 280, 200);
	lv_obj_set_size(ui->screen_setting_btn_home, 40, 40);
	lv_obj_set_scrollbar_mode(ui->screen_setting_btn_home, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_setting_btn_home_main_main_default
	static lv_style_t style_screen_setting_btn_home_main_main_default;
	if (style_screen_setting_btn_home_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_setting_btn_home_main_main_default);
	else
		lv_style_init(&style_screen_setting_btn_home_main_main_default);
	lv_style_set_radius(&style_screen_setting_btn_home_main_main_default, 5);
	lv_style_set_bg_color(&style_screen_setting_btn_home_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_setting_btn_home_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_setting_btn_home_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_setting_btn_home_main_main_default, 255);
	lv_style_set_border_color(&style_screen_setting_btn_home_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_setting_btn_home_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_setting_btn_home_main_main_default, 255);
	lv_style_set_text_color(&style_screen_setting_btn_home_main_main_default, lv_color_make(0x17, 0x4a, 0x63));
	lv_style_set_text_font(&style_screen_setting_btn_home_main_main_default, &lv_font_Acme_Regular_14);
	lv_style_set_text_align(&style_screen_setting_btn_home_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_setting_btn_home, &style_screen_setting_btn_home_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->screen_setting_btn_home_label = lv_label_create(ui->screen_setting_btn_home);
	lv_label_set_text(ui->screen_setting_btn_home_label, "home");
	lv_obj_set_style_pad_all(ui->screen_setting_btn_home, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_setting_btn_home_label, LV_ALIGN_CENTER, 0, 0);

	//Init events for screen
	events_init_screen_setting(ui);
}