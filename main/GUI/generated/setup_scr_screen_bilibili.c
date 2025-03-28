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

static const lv_img_dsc_t* screen_bilibili_animimg_1_imgs[3] = {
	&screen_bilibili_animimg_1bilibili_01,
	&screen_bilibili_animimg_1bilibili_02,
	&screen_bilibili_animimg_1bilibili_03
};

void setup_scr_screen_bilibili(lv_ui *ui){

	//Write codes screen_bilibili
	ui->screen_bilibili = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui->screen_bilibili, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_bilibili_main_main_default
	static lv_style_t style_screen_bilibili_main_main_default;
	if (style_screen_bilibili_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_bilibili_main_main_default);
	else
		lv_style_init(&style_screen_bilibili_main_main_default);
	lv_style_set_bg_color(&style_screen_bilibili_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_screen_bilibili_main_main_default, 0);
	lv_obj_add_style(ui->screen_bilibili, &style_screen_bilibili_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_bilibili_img_beijing
	ui->screen_bilibili_img_beijing = lv_img_create(ui->screen_bilibili);
	lv_obj_set_pos(ui->screen_bilibili_img_beijing, 0, 0);
	lv_obj_set_size(ui->screen_bilibili_img_beijing, 320, 240);
	lv_obj_set_scrollbar_mode(ui->screen_bilibili_img_beijing, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_bilibili_img_beijing_main_main_default
	static lv_style_t style_screen_bilibili_img_beijing_main_main_default;
	if (style_screen_bilibili_img_beijing_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_bilibili_img_beijing_main_main_default);
	else
		lv_style_init(&style_screen_bilibili_img_beijing_main_main_default);
	lv_style_set_img_recolor(&style_screen_bilibili_img_beijing_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_bilibili_img_beijing_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_bilibili_img_beijing_main_main_default, 255);
	lv_obj_add_style(ui->screen_bilibili_img_beijing, &style_screen_bilibili_img_beijing_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_bilibili_img_beijing, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_bilibili_img_beijing,&_bilibili_beijing_320x240);
	lv_img_set_pivot(ui->screen_bilibili_img_beijing, 0,0);
	lv_img_set_angle(ui->screen_bilibili_img_beijing, 0);

	//Write codes screen_bilibili_btn_home
	ui->screen_bilibili_btn_home = lv_btn_create(ui->screen_bilibili);
	lv_obj_set_pos(ui->screen_bilibili_btn_home, 280, 200);
	lv_obj_set_size(ui->screen_bilibili_btn_home, 40, 40);
	lv_obj_set_scrollbar_mode(ui->screen_bilibili_btn_home, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_bilibili_btn_home_main_main_default
	static lv_style_t style_screen_bilibili_btn_home_main_main_default;
	if (style_screen_bilibili_btn_home_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_bilibili_btn_home_main_main_default);
	else
		lv_style_init(&style_screen_bilibili_btn_home_main_main_default);
	lv_style_set_radius(&style_screen_bilibili_btn_home_main_main_default, 5);
	lv_style_set_bg_color(&style_screen_bilibili_btn_home_main_main_default, lv_color_make(0x9d, 0xcd, 0xa5));
	lv_style_set_bg_grad_color(&style_screen_bilibili_btn_home_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_bilibili_btn_home_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_bilibili_btn_home_main_main_default, 255);
	lv_style_set_border_color(&style_screen_bilibili_btn_home_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_bilibili_btn_home_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_bilibili_btn_home_main_main_default, 255);
	lv_style_set_text_color(&style_screen_bilibili_btn_home_main_main_default, lv_color_make(0x38, 0x56, 0x1a));
	lv_style_set_text_font(&style_screen_bilibili_btn_home_main_main_default, &lv_font_Acme_Regular_14);
	lv_style_set_text_align(&style_screen_bilibili_btn_home_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_bilibili_btn_home, &style_screen_bilibili_btn_home_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->screen_bilibili_btn_home_label = lv_label_create(ui->screen_bilibili_btn_home);
	lv_label_set_text(ui->screen_bilibili_btn_home_label, "Home");
	lv_obj_set_style_pad_all(ui->screen_bilibili_btn_home, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_bilibili_btn_home_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_bilibili_animimg_1
	ui->screen_bilibili_animimg_1 = lv_animimg_create(ui->screen_bilibili);
	lv_obj_set_pos(ui->screen_bilibili_animimg_1, 100, 100);
	lv_obj_set_size(ui->screen_bilibili_animimg_1, 110, 125);
	lv_obj_set_scrollbar_mode(ui->screen_bilibili_animimg_1, LV_SCROLLBAR_MODE_OFF);
	lv_animimg_set_src(ui->screen_bilibili_animimg_1, (lv_img_dsc_t**) screen_bilibili_animimg_1_imgs, 3);
	lv_animimg_set_duration(ui->screen_bilibili_animimg_1, 900);
	lv_animimg_set_repeat_count(ui->screen_bilibili_animimg_1, 3000);
	lv_animimg_start(ui->screen_bilibili_animimg_1);

	//Write codes screen_bilibili_label_Flowers
	ui->screen_bilibili_label_Flowers = lv_label_create(ui->screen_bilibili);
	lv_obj_set_pos(ui->screen_bilibili_label_Flowers, 160, 50);
	lv_obj_set_size(ui->screen_bilibili_label_Flowers, 80, 15);
	lv_obj_set_scrollbar_mode(ui->screen_bilibili_label_Flowers, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_bilibili_label_Flowers, "88");
	lv_label_set_long_mode(ui->screen_bilibili_label_Flowers, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_bilibili_label_flowers_main_main_default
	static lv_style_t style_screen_bilibili_label_flowers_main_main_default;
	if (style_screen_bilibili_label_flowers_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_bilibili_label_flowers_main_main_default);
	else
		lv_style_init(&style_screen_bilibili_label_flowers_main_main_default);
	lv_style_set_radius(&style_screen_bilibili_label_flowers_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_bilibili_label_flowers_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_bilibili_label_flowers_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_bilibili_label_flowers_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_bilibili_label_flowers_main_main_default, 0);
	lv_style_set_text_color(&style_screen_bilibili_label_flowers_main_main_default, lv_color_make(0xaf, 0xea, 0x9a));
	lv_style_set_text_font(&style_screen_bilibili_label_flowers_main_main_default, &lv_font_Acme_Regular_14);
	lv_style_set_text_letter_space(&style_screen_bilibili_label_flowers_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_bilibili_label_flowers_main_main_default, 0);
	lv_style_set_text_align(&style_screen_bilibili_label_flowers_main_main_default, LV_TEXT_ALIGN_LEFT);
	lv_style_set_pad_left(&style_screen_bilibili_label_flowers_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_bilibili_label_flowers_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_bilibili_label_flowers_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_bilibili_label_flowers_main_main_default, 0);
	lv_obj_add_style(ui->screen_bilibili_label_Flowers, &style_screen_bilibili_label_flowers_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_bilibili_label_Fans
	ui->screen_bilibili_label_Fans = lv_label_create(ui->screen_bilibili);
	lv_obj_set_pos(ui->screen_bilibili_label_Fans, 120, 25);
	lv_obj_set_size(ui->screen_bilibili_label_Fans, 50, 15);
	lv_obj_set_scrollbar_mode(ui->screen_bilibili_label_Fans, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_bilibili_label_Fans, "88");
	lv_label_set_long_mode(ui->screen_bilibili_label_Fans, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_bilibili_label_fans_main_main_default
	static lv_style_t style_screen_bilibili_label_fans_main_main_default;
	if (style_screen_bilibili_label_fans_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_bilibili_label_fans_main_main_default);
	else
		lv_style_init(&style_screen_bilibili_label_fans_main_main_default);
	lv_style_set_radius(&style_screen_bilibili_label_fans_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_bilibili_label_fans_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_bilibili_label_fans_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_bilibili_label_fans_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_bilibili_label_fans_main_main_default, 0);
	lv_style_set_text_color(&style_screen_bilibili_label_fans_main_main_default, lv_color_make(0xad, 0xe7, 0x92));
	lv_style_set_text_font(&style_screen_bilibili_label_fans_main_main_default, &lv_font_Acme_Regular_14);
	lv_style_set_text_letter_space(&style_screen_bilibili_label_fans_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_bilibili_label_fans_main_main_default, 0);
	lv_style_set_text_align(&style_screen_bilibili_label_fans_main_main_default, LV_TEXT_ALIGN_LEFT);
	lv_style_set_pad_left(&style_screen_bilibili_label_fans_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_bilibili_label_fans_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_bilibili_label_fans_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_bilibili_label_fans_main_main_default, 0);
	lv_obj_add_style(ui->screen_bilibili_label_Fans, &style_screen_bilibili_label_fans_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_bilibili_label_BlackList
	ui->screen_bilibili_label_BlackList = lv_label_create(ui->screen_bilibili);
	lv_obj_set_pos(ui->screen_bilibili_label_BlackList, 260, 5);
	lv_obj_set_size(ui->screen_bilibili_label_BlackList, 50, 15);
	lv_obj_set_scrollbar_mode(ui->screen_bilibili_label_BlackList, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_bilibili_label_BlackList, "88");
	lv_label_set_long_mode(ui->screen_bilibili_label_BlackList, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_bilibili_label_blacklist_main_main_default
	static lv_style_t style_screen_bilibili_label_blacklist_main_main_default;
	if (style_screen_bilibili_label_blacklist_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_bilibili_label_blacklist_main_main_default);
	else
		lv_style_init(&style_screen_bilibili_label_blacklist_main_main_default);
	lv_style_set_radius(&style_screen_bilibili_label_blacklist_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_bilibili_label_blacklist_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_bilibili_label_blacklist_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_bilibili_label_blacklist_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_bilibili_label_blacklist_main_main_default, 0);
	lv_style_set_text_color(&style_screen_bilibili_label_blacklist_main_main_default, lv_color_make(0xb6, 0xed, 0xc9));
	lv_style_set_text_font(&style_screen_bilibili_label_blacklist_main_main_default, &lv_font_Acme_Regular_14);
	lv_style_set_text_letter_space(&style_screen_bilibili_label_blacklist_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_bilibili_label_blacklist_main_main_default, 0);
	lv_style_set_text_align(&style_screen_bilibili_label_blacklist_main_main_default, LV_TEXT_ALIGN_LEFT);
	lv_style_set_pad_left(&style_screen_bilibili_label_blacklist_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_bilibili_label_blacklist_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_bilibili_label_blacklist_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_bilibili_label_blacklist_main_main_default, 0);
	lv_obj_add_style(ui->screen_bilibili_label_BlackList, &style_screen_bilibili_label_blacklist_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_bilibili_label_UserID
	ui->screen_bilibili_label_UserID = lv_label_create(ui->screen_bilibili);
	lv_obj_set_pos(ui->screen_bilibili_label_UserID, 75, 5);
	lv_obj_set_size(ui->screen_bilibili_label_UserID, 80, 15);
	lv_obj_set_scrollbar_mode(ui->screen_bilibili_label_UserID, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_bilibili_label_UserID, "88888888");
	lv_label_set_long_mode(ui->screen_bilibili_label_UserID, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_bilibili_label_userid_main_main_default
	static lv_style_t style_screen_bilibili_label_userid_main_main_default;
	if (style_screen_bilibili_label_userid_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_bilibili_label_userid_main_main_default);
	else
		lv_style_init(&style_screen_bilibili_label_userid_main_main_default);
	lv_style_set_radius(&style_screen_bilibili_label_userid_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_bilibili_label_userid_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_bilibili_label_userid_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_bilibili_label_userid_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_bilibili_label_userid_main_main_default, 0);
	lv_style_set_text_color(&style_screen_bilibili_label_userid_main_main_default, lv_color_make(0xbc, 0xd9, 0xb4));
	lv_style_set_text_font(&style_screen_bilibili_label_userid_main_main_default, &lv_font_Acme_Regular_14);
	lv_style_set_text_letter_space(&style_screen_bilibili_label_userid_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_bilibili_label_userid_main_main_default, 0);
	lv_style_set_text_align(&style_screen_bilibili_label_userid_main_main_default, LV_TEXT_ALIGN_LEFT);
	lv_style_set_pad_left(&style_screen_bilibili_label_userid_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_bilibili_label_userid_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_bilibili_label_userid_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_bilibili_label_userid_main_main_default, 0);
	lv_obj_add_style(ui->screen_bilibili_label_UserID, &style_screen_bilibili_label_userid_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_bilibili_label_3
	ui->screen_bilibili_label_3 = lv_label_create(ui->screen_bilibili);
	lv_obj_set_pos(ui->screen_bilibili_label_3, 184, 5);
	lv_obj_set_size(ui->screen_bilibili_label_3, 75, 15);
	lv_obj_set_scrollbar_mode(ui->screen_bilibili_label_3, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_bilibili_label_3, "Blacklist:");
	lv_label_set_long_mode(ui->screen_bilibili_label_3, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_bilibili_label_3_main_main_default
	static lv_style_t style_screen_bilibili_label_3_main_main_default;
	if (style_screen_bilibili_label_3_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_bilibili_label_3_main_main_default);
	else
		lv_style_init(&style_screen_bilibili_label_3_main_main_default);
	lv_style_set_radius(&style_screen_bilibili_label_3_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_bilibili_label_3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_bilibili_label_3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_bilibili_label_3_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_bilibili_label_3_main_main_default, 0);
	lv_style_set_text_color(&style_screen_bilibili_label_3_main_main_default, lv_color_make(0x93, 0xec, 0x8d));
	lv_style_set_text_font(&style_screen_bilibili_label_3_main_main_default, &lv_font_Acme_Regular_14);
	lv_style_set_text_letter_space(&style_screen_bilibili_label_3_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_bilibili_label_3_main_main_default, 0);
	lv_style_set_text_align(&style_screen_bilibili_label_3_main_main_default, LV_TEXT_ALIGN_LEFT);
	lv_style_set_pad_left(&style_screen_bilibili_label_3_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_bilibili_label_3_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_bilibili_label_3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_bilibili_label_3_main_main_default, 0);
	lv_obj_add_style(ui->screen_bilibili_label_3, &style_screen_bilibili_label_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_bilibili_label_2
	ui->screen_bilibili_label_2 = lv_label_create(ui->screen_bilibili);
	lv_obj_set_pos(ui->screen_bilibili_label_2, 5, 50);
	lv_obj_set_size(ui->screen_bilibili_label_2, 150, 15);
	lv_obj_set_scrollbar_mode(ui->screen_bilibili_label_2, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_bilibili_label_2, "Numberoffollowers:");
	lv_label_set_long_mode(ui->screen_bilibili_label_2, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_bilibili_label_2_main_main_default
	static lv_style_t style_screen_bilibili_label_2_main_main_default;
	if (style_screen_bilibili_label_2_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_bilibili_label_2_main_main_default);
	else
		lv_style_init(&style_screen_bilibili_label_2_main_main_default);
	lv_style_set_radius(&style_screen_bilibili_label_2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_bilibili_label_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_bilibili_label_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_bilibili_label_2_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_bilibili_label_2_main_main_default, 0);
	lv_style_set_text_color(&style_screen_bilibili_label_2_main_main_default, lv_color_make(0xca, 0xd6, 0x8f));
	lv_style_set_text_font(&style_screen_bilibili_label_2_main_main_default, &lv_font_Acme_Regular_14);
	lv_style_set_text_letter_space(&style_screen_bilibili_label_2_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_bilibili_label_2_main_main_default, 0);
	lv_style_set_text_align(&style_screen_bilibili_label_2_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_bilibili_label_2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_bilibili_label_2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_bilibili_label_2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_bilibili_label_2_main_main_default, 0);
	lv_obj_add_style(ui->screen_bilibili_label_2, &style_screen_bilibili_label_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_bilibili_label_4
	ui->screen_bilibili_label_4 = lv_label_create(ui->screen_bilibili);
	lv_obj_set_pos(ui->screen_bilibili_label_4, 5, 25);
	lv_obj_set_size(ui->screen_bilibili_label_4, 110, 15);
	lv_obj_set_scrollbar_mode(ui->screen_bilibili_label_4, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_bilibili_label_4, "Numberoffans:");
	lv_label_set_long_mode(ui->screen_bilibili_label_4, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_bilibili_label_4_main_main_default
	static lv_style_t style_screen_bilibili_label_4_main_main_default;
	if (style_screen_bilibili_label_4_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_bilibili_label_4_main_main_default);
	else
		lv_style_init(&style_screen_bilibili_label_4_main_main_default);
	lv_style_set_radius(&style_screen_bilibili_label_4_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_bilibili_label_4_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_bilibili_label_4_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_bilibili_label_4_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_bilibili_label_4_main_main_default, 0);
	lv_style_set_text_color(&style_screen_bilibili_label_4_main_main_default, lv_color_make(0xa6, 0xf2, 0xb5));
	lv_style_set_text_font(&style_screen_bilibili_label_4_main_main_default, &lv_font_Acme_Regular_14);
	lv_style_set_text_letter_space(&style_screen_bilibili_label_4_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_bilibili_label_4_main_main_default, 0);
	lv_style_set_text_align(&style_screen_bilibili_label_4_main_main_default, LV_TEXT_ALIGN_LEFT);
	lv_style_set_pad_left(&style_screen_bilibili_label_4_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_bilibili_label_4_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_bilibili_label_4_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_bilibili_label_4_main_main_default, 0);
	lv_obj_add_style(ui->screen_bilibili_label_4, &style_screen_bilibili_label_4_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_bilibili_label_1
	ui->screen_bilibili_label_1 = lv_label_create(ui->screen_bilibili);
	lv_obj_set_pos(ui->screen_bilibili_label_1, 5, 5);
	lv_obj_set_size(ui->screen_bilibili_label_1, 70, 15);
	lv_obj_set_scrollbar_mode(ui->screen_bilibili_label_1, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_bilibili_label_1, "User_ID:");
	lv_label_set_long_mode(ui->screen_bilibili_label_1, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_bilibili_label_1_main_main_default
	static lv_style_t style_screen_bilibili_label_1_main_main_default;
	if (style_screen_bilibili_label_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_bilibili_label_1_main_main_default);
	else
		lv_style_init(&style_screen_bilibili_label_1_main_main_default);
	lv_style_set_radius(&style_screen_bilibili_label_1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_bilibili_label_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_bilibili_label_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_bilibili_label_1_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_bilibili_label_1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_bilibili_label_1_main_main_default, lv_color_make(0xcd, 0xe7, 0xb1));
	lv_style_set_text_font(&style_screen_bilibili_label_1_main_main_default, &lv_font_Acme_Regular_14);
	lv_style_set_text_letter_space(&style_screen_bilibili_label_1_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_bilibili_label_1_main_main_default, 0);
	lv_style_set_text_align(&style_screen_bilibili_label_1_main_main_default, LV_TEXT_ALIGN_LEFT);
	lv_style_set_pad_left(&style_screen_bilibili_label_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_bilibili_label_1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_bilibili_label_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_bilibili_label_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_bilibili_label_1, &style_screen_bilibili_label_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Init events for screen
	events_init_screen_bilibili(ui);
}