/*
 * Copyright 2025 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

// 更新 Slider 值到 Label 的函数
void update_slider_label(lv_obj_t *slider, lv_obj_t *label) {
    int16_t current_value = lv_slider_get_value(slider);
	printf("current_value:%d",current_value);
    char buffer[16];  // 16 字节的缓冲区
    snprintf(buffer, sizeof(buffer), "%d", current_value);  // 使用 snprintf 防止溢出
	printf("buffer:%s",buffer);
    lv_label_set_text(label, buffer);
}

void events_init(lv_ui *ui)
{
}

static void screen_home_jiasu_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		int16_t current_value = lv_slider_get_value(guider_ui.screen_home_slider);
		printf("lv_slider_get_value : %d!",current_value);
        int16_t new_value = current_value + 10;
		printf("new_value : %d!",new_value);
        if (new_value > lv_slider_get_max_value(guider_ui.screen_home_slider)) {
            new_value = lv_slider_get_max_value(guider_ui.screen_home_slider);
        }
        lv_slider_set_value(guider_ui.screen_home_slider, new_value, LV_ANIM_ON);
        lv_obj_invalidate(guider_ui.screen_home_slider);
		update_slider_label(guider_ui.screen_home_slider, guider_ui.screen_home_sliderText);
	}
		break;
	default:
		break;
	}
}

static void screen_home_jiansu_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		int16_t current_value = lv_slider_get_value(guider_ui.screen_home_slider);
		printf("lv_slider_get_value : %d!",current_value);
        int16_t new_value = current_value - 10;
		printf("new_value : %d!",new_value);
        if (new_value < lv_slider_get_min_value(guider_ui.screen_home_slider)) {
            new_value = lv_slider_get_max_value(guider_ui.screen_home_slider);
        }
        lv_slider_set_value(guider_ui.screen_home_slider, new_value, LV_ANIM_ON);
        lv_obj_invalidate(guider_ui.screen_home_slider);
		update_slider_label(guider_ui.screen_home_slider, guider_ui.screen_home_sliderText);
	}
		break;
	default:
		break;
	}
}

static void screen_home_slider_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_VALUE_CHANGED:
	{
		printf("sidler is changed!");
		update_slider_label(guider_ui.screen_home_slider, guider_ui.screen_home_sliderText);
	}
		break;
	default:
		break;
	}
}

static void screen_home_jiting_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
        int16_t current_value = 0;
        lv_slider_set_value(guider_ui.screen_home_slider, current_value, LV_ANIM_ON);
        lv_obj_invalidate(guider_ui.screen_home_slider);
		update_slider_label(guider_ui.screen_home_slider, guider_ui.screen_home_sliderText);
	}
		break;
	default:
		break;
	}
}

static void screen_home_Next_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		lv_disp_t * d = lv_obj_get_disp(lv_scr_act());
		if (d->prev_scr == NULL && d->scr_to_load == NULL)
		{
			if (guider_ui.screen_2_del == true)
				setup_scr_screen_2(&guider_ui);
			lv_scr_load_anim(guider_ui.screen_2, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
		}
		guider_ui.screen_home_del = true;
	}
		break;
	default:
		break;
	}
}

static void screen_home_sw_led_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_VALUE_CHANGED:
	{
		// 获取 Switch 的状态
        bool sw_state = lv_obj_has_state(guider_ui.screen_home_sw_led, LV_STATE_CHECKED);

        // 控制 LED 的状态
        if (sw_state) {
            lv_led_on(guider_ui.screen_home_led);  // 打开 LED
			lv_label_set_text(guider_ui.screen_home_label_led, "ON");
        } else {
            lv_led_off(guider_ui.screen_home_led); // 关闭 LED
			lv_label_set_text(guider_ui.screen_home_label_led, "OFF");
        }
	}
		break;
	default:
		break;
	}
}

void events_init_screen_home(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_home_jiasu, screen_home_jiasu_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_home_jiansu, screen_home_jiansu_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_home_slider, screen_home_slider_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_home_jiting, screen_home_jiting_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_home_Next, screen_home_Next_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_home_sw_led, screen_home_sw_led_event_handler, LV_EVENT_ALL, NULL);
}

static void screen_2_back_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		lv_disp_t * d = lv_obj_get_disp(lv_scr_act());
		if (d->prev_scr == NULL && d->scr_to_load == NULL)
		{
			if (guider_ui.screen_home_del == true)
				setup_scr_screen_home(&guider_ui);
			lv_scr_load_anim(guider_ui.screen_home, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
		}
		guider_ui.screen_2_del = true;
	}
		break;
	default:
		break;
	}
}

static void screen_2_next_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		lv_disp_t * d = lv_obj_get_disp(lv_scr_act());
		if (d->prev_scr == NULL && d->scr_to_load == NULL)
		{
			if (guider_ui.screen_3_del == true)
				setup_scr_screen_3(&guider_ui);
			lv_scr_load_anim(guider_ui.screen_3, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
		}
		guider_ui.screen_2_del = true;
	}
		break;
	default:
		break;
	}
}

void events_init_screen_2(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_2_back, screen_2_back_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_2_next, screen_2_next_event_handler, LV_EVENT_ALL, NULL);
}

static void screen_3_back_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		lv_disp_t * d = lv_obj_get_disp(lv_scr_act());
		if (d->prev_scr == NULL && d->scr_to_load == NULL)
		{
			if (guider_ui.screen_2_del == true)
				setup_scr_screen_2(&guider_ui);
			lv_scr_load_anim(guider_ui.screen_2, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
		}
		guider_ui.screen_3_del = true;
	}
		break;
	default:
		break;
	}
}

static void screen_3_backbtn_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		lv_disp_t * d = lv_obj_get_disp(lv_scr_act());
		if (d->prev_scr == NULL && d->scr_to_load == NULL)
		{
			if (guider_ui.screen_2_del == true)
				setup_scr_screen_2(&guider_ui);
			lv_scr_load_anim(guider_ui.screen_2, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
		}
		guider_ui.screen_3_del = true;
	}
		break;
	default:
		break;
	}
}

void events_init_screen_3(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_3_back, screen_3_back_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_3_backbtn, screen_3_backbtn_event_handler, LV_EVENT_ALL, NULL);
}
