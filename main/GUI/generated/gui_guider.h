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
{	lv_obj_t *screen_init;
	bool screen_init_del;
	lv_obj_t *screen_init_animimg_1;
	lv_obj_t *screen_init_animimg_2;
	lv_obj_t *screen_init_label_1;
	lv_obj_t *screen_init_label_tittle;
	lv_obj_t *screen_systerm;
	bool screen_systerm_del;
	lv_obj_t *screen_systerm_imgbtn_weather;
	lv_obj_t *screen_systerm_imgbtn_weather_label;
	lv_obj_t *screen_systerm_imgbtn_2048;
	lv_obj_t *screen_systerm_imgbtn_2048_label;
	lv_obj_t *screen_systerm_imgbtn_bili;
	lv_obj_t *screen_systerm_imgbtn_bili_label;
	lv_obj_t *screen_systerm_imgbtn_sd;
	lv_obj_t *screen_systerm_imgbtn_sd_label;
	lv_obj_t *screen_systerm_label_4;
	lv_obj_t *screen_systerm_imgbtn_moive;
	lv_obj_t *screen_systerm_imgbtn_moive_label;
	lv_obj_t *screen_systerm_imgbtn_server;
	lv_obj_t *screen_systerm_imgbtn_server_label;
	lv_obj_t *screen_systerm_imgbtn_resolve;
	lv_obj_t *screen_systerm_imgbtn_resolve_label;
	lv_obj_t *screen_systerm_label_7;
	lv_obj_t *screen_systerm_label_1;
	lv_obj_t *screen_systerm_imgbtn_2050;
	lv_obj_t *screen_systerm_imgbtn_2050_label;
	lv_obj_t *screen_systerm_imgbtn_2051;
	lv_obj_t *screen_systerm_imgbtn_2051_label;
	lv_obj_t *screen_systerm_label_2;
	lv_obj_t *screen_systerm_label_3;
	lv_obj_t *screen_systerm_label_5;
	lv_obj_t *screen_systerm_label_6;
	lv_obj_t *screen_systerm_label_8;
	lv_obj_t *screen_systerm_label_9;
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
	lv_obj_t *screen_2_btn_Home;
	lv_obj_t *screen_2_btn_Home_label;
	lv_obj_t *screen_3;
	bool screen_3_del;
	lv_obj_t *screen_3_baitian;
	lv_obj_t *screen_3_label_fengli;
	lv_obj_t *screen_3_label_9;
	lv_obj_t *screen_3_label_10;
	lv_obj_t *screen_3_label_7;
	lv_obj_t *screen_3_img_houtian;
	lv_obj_t *screen_3_label_5;
	lv_obj_t *screen_3_label_6;
	lv_obj_t *screen_3_label_jiangshui;
	lv_obj_t *screen_3_label_gaowen;
	lv_obj_t *screen_3_label_diwen;
	lv_obj_t *screen_3_label_fengsu;
	lv_obj_t *screen_3_label_fengxiang;
	lv_obj_t *screen_3_label_4;
	lv_obj_t *screen_3_img_tianqi;
	lv_obj_t *screen_3_label_1;
	lv_obj_t *screen_3_label_2;
	lv_obj_t *screen_3_label_8;
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
	lv_obj_t *screen_3_btn_Home;
	lv_obj_t *screen_3_btn_Home_label;
}lv_ui;

void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_screen_init(lv_ui *ui);
void setup_scr_screen_systerm(lv_ui *ui);
void setup_scr_screen_home(lv_ui *ui);
void setup_scr_screen_2(lv_ui *ui);
void clock_count(int *hour, int *min, int *sec);
void setup_scr_screen_3(lv_ui *ui);

LV_IMG_DECLARE(_app_file_manager_alpha_80x50);
LV_IMG_DECLARE(_app_2048_alpha_80x50);
LV_IMG_DECLARE(_app_picture_alpha_80x50);
LV_IMG_DECLARE(_app_bilibili_alpha_80x50);
LV_IMG_DECLARE(_app_movie_alpha_80x50);
LV_IMG_DECLARE(_app_weather_old_alpha_80x50);
LV_IMG_DECLARE(_app_thought_alpha_80x50);
LV_IMG_DECLARE(_app_server_alpha_80x50);
LV_IMG_DECLARE(_clock_alpha_80x50);

LV_IMG_DECLARE(_bmp_DingWei_15x15);
LV_IMG_DECLARE(_5_35x35);
LV_IMG_DECLARE(_bmp_Xian_BaiTian_320x240);
LV_IMG_DECLARE(_0_60x55);
LV_IMG_DECLARE(_11_35x35);
LV_IMG_DECLARE(_bmp_RiChuRiLuo_120x20);
LV_IMG_DECLARE(_1_35x35);
LV_IMG_DECLARE(_bmp_Du_16x19);
LV_IMG_DECLARE(bmp_tianqi_40x40_0);
LV_IMG_DECLARE(bmp_tianqi_40x40_1);
LV_IMG_DECLARE(bmp_tianqi_40x40_2);
LV_IMG_DECLARE(bmp_tianqi_40x40_3);
LV_IMG_DECLARE(bmp_tianqi_40x40_4);
LV_IMG_DECLARE(bmp_tianqi_40x40_5);
LV_IMG_DECLARE(bmp_tianqi_40x40_6);
LV_IMG_DECLARE(bmp_tianqi_40x40_7);
LV_IMG_DECLARE(bmp_tianqi_40x40_8);
LV_IMG_DECLARE(bmp_tianqi_40x40_9);
LV_IMG_DECLARE(bmp_tianqi_40x40_10);
LV_IMG_DECLARE(bmp_tianqi_40x40_11);
LV_IMG_DECLARE(bmp_tianqi_40x40_12);
LV_IMG_DECLARE(bmp_tianqi_40x40_13);
LV_IMG_DECLARE(bmp_tianqi_40x40_14);
LV_IMG_DECLARE(bmp_tianqi_40x40_15);
LV_IMG_DECLARE(bmp_tianqi_40x40_16);
LV_IMG_DECLARE(bmp_tianqi_40x40_17);
LV_IMG_DECLARE(bmp_tianqi_40x40_18);
LV_IMG_DECLARE(bmp_tianqi_40x40_19);
LV_IMG_DECLARE(bmp_tianqi_40x40_20);
LV_IMG_DECLARE(bmp_tianqi_40x40_21);
LV_IMG_DECLARE(bmp_tianqi_40x40_22);
LV_IMG_DECLARE(bmp_tianqi_40x40_23);
LV_IMG_DECLARE(bmp_tianqi_40x40_24);
LV_IMG_DECLARE(bmp_tianqi_40x40_25);
LV_IMG_DECLARE(bmp_tianqi_40x40_26);
LV_IMG_DECLARE(bmp_tianqi_40x40_27);
LV_IMG_DECLARE(bmp_tianqi_40x40_28);
LV_IMG_DECLARE(bmp_tianqi_40x40_29);
LV_IMG_DECLARE(bmp_tianqi_40x40_30);
LV_IMG_DECLARE(bmp_tianqi_40x40_31);
LV_IMG_DECLARE(bmp_tianqi_40x40_32);
LV_IMG_DECLARE(bmp_tianqi_40x40_33);
LV_IMG_DECLARE(bmp_tianqi_40x40_34);
LV_IMG_DECLARE(bmp_tianqi_40x40_35);
LV_IMG_DECLARE(bmp_tianqi_40x40_36);
LV_IMG_DECLARE(bmp_tianqi_40x40_37);
LV_IMG_DECLARE(bmp_tianqi_40x40_38);
LV_IMG_DECLARE(bmp_tianqi_40x40_99);



#include "extra/widgets/animimg/lv_animimg.h"
LV_IMG_DECLARE(screen_init_animimg_1bmp_bilibili_01_01)
LV_IMG_DECLARE(screen_init_animimg_1bmp_bilibili_01_02)
LV_IMG_DECLARE(screen_init_animimg_1bmp_bilibili_01_03)

#include "extra/widgets/animimg/lv_animimg.h"
LV_IMG_DECLARE(screen_init_animimg_2pig_00)
LV_IMG_DECLARE(screen_init_animimg_2pig_01)
LV_IMG_DECLARE(screen_init_animimg_2pig_02)
LV_IMG_DECLARE(screen_init_animimg_2pig_03)
LV_IMG_DECLARE(screen_init_animimg_2pig_04)
LV_IMG_DECLARE(screen_init_animimg_2pig_05)

#ifdef __cplusplus
}
#endif
#endif