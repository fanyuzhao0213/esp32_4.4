/*
 * Copyright 2025 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "guider_fonts.h"

typedef struct
{
	lv_obj_t *screen_home;
	bool screen_home_del;
	lv_obj_t *screen_home_jiasu;
	lv_obj_t *screen_home_jiasu_label;
	lv_obj_t *screen_home_jiansu;
	lv_obj_t *screen_home_jiansu_label;
	lv_obj_t *screen_home_slider;
	lv_obj_t *screen_home_sliderText;
	lv_obj_t *screen_home_jiting;
	lv_obj_t *screen_home_jiting_label;
	lv_obj_t *screen_home_led;
	lv_obj_t *screen_home_Next;
	lv_obj_t *screen_home_Next_label;
	lv_obj_t *screen_home_sw_led;
	lv_obj_t *screen_home_label_led;
	lv_obj_t *screen_2;
	bool screen_2_del;
	lv_obj_t *screen_2_back;
	lv_obj_t *screen_2_back_label;
	lv_obj_t *screen_2_next;
	lv_obj_t *screen_2_next_label;
	lv_obj_t *screen_2_analog_clock;
	lv_obj_t *screen_3;
	bool screen_3_del;
	lv_obj_t *screen_3_baitian;
	lv_obj_t *screen_3_label_7;
	lv_obj_t *screen_3_img_houtian;
	lv_obj_t *screen_3_label_5;
	lv_obj_t *screen_3_label_6;
	lv_obj_t *screen_3_label_jiangshui;
	lv_obj_t *screen_3_label_fengsu;
	lv_obj_t *screen_3_label_fengxiang;
	lv_obj_t *screen_3_label_4;
	lv_obj_t *screen_3_img_tianqi;
	lv_obj_t *screen_3_label_1;
	lv_obj_t *screen_3_label_2;
	lv_obj_t *screen_3_label_3;
	lv_obj_t *screen_3_label_wenduriqi;
	lv_obj_t *screen_3_label_jintianriqi;
	lv_obj_t *screen_3_label_mingtianriqi;
	lv_obj_t *screen_3_label_houtianriqi;
	lv_obj_t *screen_3_label_wendu;
	lv_obj_t *screen_3_img_2;
	lv_obj_t *screen_3_label_riqi;
	lv_obj_t *screen_3_label_xingqi;
	lv_obj_t *screen_3_label_time;
	lv_obj_t *screen_3_img_1;
	lv_obj_t *screen_3_label_dingwei;
	lv_obj_t *screen_3_label_riluo;
	lv_obj_t *screen_3_label_richu;
	lv_obj_t *screen_3_richu_bai;
	lv_obj_t *screen_3_backbtn;
	lv_obj_t *screen_3_backbtn_label;
	lv_obj_t *screen_3_img_jintian;
	lv_obj_t *screen_3_img_mingtian;
}lv_ui;

void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_screen_home(lv_ui *ui);
void setup_scr_screen_2(lv_ui *ui);
void clock_count(int *hour, int *min, int *sec);
void setup_scr_screen_3(lv_ui *ui);
LV_IMG_DECLARE(_bmp_DingWei_15x15);
LV_IMG_DECLARE(_5_35x35);
LV_IMG_DECLARE(_bmp_Xian_BaiTian_320x240);
LV_IMG_DECLARE(_0_60x55);
LV_IMG_DECLARE(_11_35x35);
LV_IMG_DECLARE(_bmp_RiChuRiLuo_120x20);
LV_IMG_DECLARE(_1_35x35);
LV_IMG_DECLARE(_bmp_Du_16x19);

#ifdef __cplusplus
}
#endif
#endif