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
#include "wifi_smartconfig.h"

// 定时器回调函数，用于切换屏幕
void screen_init_timer(lv_timer_t *timer)
{
    // 阻塞等待，最多等待2秒
    if (xSemaphoreTake(systerminit_semaphore, pdMS_TO_TICKS(500)))
	{
        printf("获取信号量成功，继续执行\n");
		switch_screen(SCREEN_SYSTERM);  // 切换到主屏幕
		// 1. 删除当前定时器（安全检查）
        if (timer)
		{
            lv_timer_del(timer); // 删除定时器
            timer = NULL;        // 避免野指针
        }
    } else
	{
        printf("等待超时，信号量未就绪\n");
    }
}
static const lv_img_dsc_t* screen_init_animimg_1_imgs[3] = {
	&screen_init_animimg_1bmp_bilibili_01_01,
	&screen_init_animimg_1bmp_bilibili_01_02,
	&screen_init_animimg_1bmp_bilibili_01_03
};
static const lv_img_dsc_t* screen_init_animimg_2_imgs[6] = {
	&screen_init_animimg_2pig_00,
	&screen_init_animimg_2pig_01,
	&screen_init_animimg_2pig_02,
	&screen_init_animimg_2pig_03,
	&screen_init_animimg_2pig_04,
	&screen_init_animimg_2pig_05
};

void setup_scr_screen_init(lv_ui *ui){

	//Write codes screen_init
	ui->screen_init = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui->screen_init, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_init_main_main_default
	static lv_style_t style_screen_init_main_main_default;
	if (style_screen_init_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_init_main_main_default);
	else
		lv_style_init(&style_screen_init_main_main_default);
	lv_style_set_bg_color(&style_screen_init_main_main_default, lv_color_make(0x62, 0x97, 0xc6));
	lv_style_set_bg_opa(&style_screen_init_main_main_default, 0);
	lv_obj_add_style(ui->screen_init, &style_screen_init_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_init_animimg_1
	ui->screen_init_animimg_1 = lv_animimg_create(ui->screen_init);
	lv_obj_set_pos(ui->screen_init_animimg_1, 0, 190);
	lv_obj_set_size(ui->screen_init_animimg_1, 320, 50);
	lv_obj_set_scrollbar_mode(ui->screen_init_animimg_1, LV_SCROLLBAR_MODE_OFF);
	lv_animimg_set_src(ui->screen_init_animimg_1, (lv_img_dsc_t**) screen_init_animimg_1_imgs, 3);
	lv_animimg_set_duration(ui->screen_init_animimg_1, 1500);
	lv_animimg_t* screen_init_animimg_1_ext = (lv_animimg_t *)ui->screen_init_animimg_1;
	lv_anim_set_start_cb(&screen_init_animimg_1_ext->anim, 0);
	lv_animimg_set_repeat_count(ui->screen_init_animimg_1, 300000);
	lv_animimg_start(ui->screen_init_animimg_1);

	//Write codes screen_init_animimg_2
	ui->screen_init_animimg_2 = lv_animimg_create(ui->screen_init);
	lv_obj_set_pos(ui->screen_init_animimg_2, 110, 55);
	lv_obj_set_size(ui->screen_init_animimg_2, 100, 80);
	lv_obj_set_scrollbar_mode(ui->screen_init_animimg_2, LV_SCROLLBAR_MODE_OFF);
	lv_animimg_set_src(ui->screen_init_animimg_2, (lv_img_dsc_t**) screen_init_animimg_2_imgs, 6);
	lv_animimg_set_duration(ui->screen_init_animimg_2, 3000);
	lv_animimg_set_repeat_count(ui->screen_init_animimg_2, 3000);
	lv_animimg_start(ui->screen_init_animimg_2);

	//Write codes screen_init_label_1
	ui->screen_init_label_1 = lv_label_create(ui->screen_init);
	lv_obj_set_pos(ui->screen_init_label_1, 70, 160);
	lv_obj_set_size(ui->screen_init_label_1, 200, 20);
	lv_obj_set_scrollbar_mode(ui->screen_init_label_1, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_init_label_1, "系统正在初始化...");
	lv_label_set_long_mode(ui->screen_init_label_1, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_init_label_1_main_main_default
	static lv_style_t style_screen_init_label_1_main_main_default;
	if (style_screen_init_label_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_init_label_1_main_main_default);
	else
		lv_style_init(&style_screen_init_label_1_main_main_default);
	lv_style_set_radius(&style_screen_init_label_1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_init_label_1_main_main_default, lv_color_make(0xe7, 0xeb, 0xee));
	lv_style_set_bg_grad_color(&style_screen_init_label_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_init_label_1_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_init_label_1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_init_label_1_main_main_default, lv_color_make(0x3d, 0xae, 0x73));
	lv_style_set_text_font(&style_screen_init_label_1_main_main_default, &lv_customer_font_IBMPlexSansSC_SemiBold_20);
	lv_style_set_text_letter_space(&style_screen_init_label_1_main_main_default, 1);
	lv_style_set_text_line_space(&style_screen_init_label_1_main_main_default, 0);
	lv_style_set_text_align(&style_screen_init_label_1_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_init_label_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_init_label_1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_init_label_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_init_label_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_init_label_1, &style_screen_init_label_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_init_label_tittle
	ui->screen_init_label_tittle = lv_label_create(ui->screen_init);
	lv_obj_set_pos(ui->screen_init_label_tittle, 0, 0);
	lv_obj_set_size(ui->screen_init_label_tittle, 150, 20);
	lv_obj_set_scrollbar_mode(ui->screen_init_label_tittle, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_init_label_tittle, "Esp32S3_LVGL");
	lv_label_set_long_mode(ui->screen_init_label_tittle, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_init_label_tittle_main_main_default
	static lv_style_t style_screen_init_label_tittle_main_main_default;
	if (style_screen_init_label_tittle_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_init_label_tittle_main_main_default);
	else
		lv_style_init(&style_screen_init_label_tittle_main_main_default);
	lv_style_set_radius(&style_screen_init_label_tittle_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_init_label_tittle_main_main_default, lv_color_make(0x2f, 0x82, 0xc6));
	lv_style_set_bg_grad_color(&style_screen_init_label_tittle_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_init_label_tittle_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_init_label_tittle_main_main_default, 0);
	lv_style_set_text_color(&style_screen_init_label_tittle_main_main_default, lv_color_make(0x91, 0x2b, 0x2b));
	lv_style_set_text_font(&style_screen_init_label_tittle_main_main_default, &lv_font_Acme_Regular_20);
	lv_style_set_text_letter_space(&style_screen_init_label_tittle_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_init_label_tittle_main_main_default, 0);
	lv_style_set_text_align(&style_screen_init_label_tittle_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_init_label_tittle_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_init_label_tittle_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_init_label_tittle_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_init_label_tittle_main_main_default, 0);
	lv_obj_add_style(ui->screen_init_label_tittle, &style_screen_init_label_tittle_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	// 创建定时器
    static bool screen_init_timer_enabled = false;
    if (!screen_init_timer_enabled) {
        lv_timer_create(screen_init_timer, 1000, NULL);  // 每秒更新一次时间
        screen_init_timer_enabled = true;
    }
}