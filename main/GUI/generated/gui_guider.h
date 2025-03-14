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
	lv_obj_t *screen_2_sw_1;
}lv_ui;

void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_screen_home(lv_ui *ui);
void setup_scr_screen_2(lv_ui *ui);

#ifdef __cplusplus
}
#endif
#endif