#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "BSP/WEATHER/weather.h"
#include "BSP/WEATHER/bilibili.h"
#include "pwm.h"

//保存协议栈
TaskHandle_t xHttpTask = NULL;
TaskHandle_t xBiliBiliTask = NULL;

// 全局变量
screen_state_t current_screen = SCREEN_HOME;  // 当前屏幕状态

// 更新 Slider 值到 Label 的函数
void update_slider_label(lv_obj_t *slider, lv_obj_t *label) {
    int16_t current_value = lv_slider_get_value(slider);
    printf("current_value:%d", current_value);
    char buffer[16];  // 16 字节的缓冲区
    snprintf(buffer, sizeof(buffer), "%d", current_value);  // 使用 snprintf 防止溢出
    printf("buffer:%s", buffer);
    lv_label_set_text(label, buffer);
}

// 切换屏幕的函数
void switch_screen(screen_state_t new_screen)
{
    switch (new_screen) {
        case SCREEN_INIT:
            if (guider_ui.screen_init_del == true)
                setup_scr_screen_init(&guider_ui);
            lv_scr_load_anim(guider_ui.screen_init, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
            break;
        case SCREEN_SYSTERM:
            if (guider_ui.screen_systerm_del == true)
                setup_scr_screen_systerm(&guider_ui);
            lv_scr_load_anim(guider_ui.screen_systerm, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
            break;
        case SCREEN_BILIBILI:
            xTaskCreate(fetch_bilibili_info_task, "fetch_bilibili_info_task", 5120, NULL, 6, &xBiliBiliTask);
            if (guider_ui.screen_bilibili_del == true)
                setup_scr_screen_bilibili(&guider_ui);
            lv_scr_load_anim(guider_ui.screen_bilibili, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
            break;
        case SCREEN_SETTING:
            if (guider_ui.screen_setting_del == true)
                setup_scr_screen_setting(&guider_ui);
            lv_scr_load_anim(guider_ui.screen_setting, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
            break;
        case SCREEN_PICTURE:
            if (guider_ui.screen_Picture_del == true)
                setup_scr_screen_Picture(&guider_ui);
            lv_scr_load_anim(guider_ui.screen_Picture, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
            break;
        case SCREEN_HOME:
            if (guider_ui.screen_home_del == true)
                setup_scr_screen_home(&guider_ui);
            lv_scr_load_anim(guider_ui.screen_home, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
            break;
        case SCREEN_2:
            if (guider_ui.screen_2_del == true)
                setup_scr_screen_2(&guider_ui);
            lv_scr_load_anim(guider_ui.screen_2, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
            break;
        case SCREEN_3:
            xTaskCreate(http_client_task, "http_client", 5120, NULL, 6, &xHttpTask);
            if (guider_ui.screen_3_del == true)
                setup_scr_screen_3(&guider_ui);
            lv_scr_load_anim(guider_ui.screen_3, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
            break;
    }
    current_screen = new_screen;  // 更新当前屏幕状态
}

static void screen_systerm_imgbtn_weather_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_RELEASED:
	{
		lv_disp_t * d = lv_obj_get_disp(lv_scr_act());
		if (d->prev_scr == NULL && d->scr_to_load == NULL)
		{
            switch_screen(SCREEN_3);  // 切换到屏幕 3
			// if (guider_ui.screen_3_del == true)
			// 	setup_scr_screen_3(&guider_ui);
			// lv_scr_load_anim(guider_ui.screen_3, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
		}
		guider_ui.screen_systerm_del = true;
	}
		break;
	default:
		break;
	}
}

static void screen_systerm_imgbtn_bili_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_RELEASED:
	{
		lv_disp_t * d = lv_obj_get_disp(lv_scr_act());
		if (d->prev_scr == NULL && d->scr_to_load == NULL)
		{
            switch_screen(SCREEN_BILIBILI);
			// if (guider_ui.screen_bilibili_del == true)
			// 	setup_scr_screen_bilibili(&guider_ui);
			// lv_scr_load_anim(guider_ui.screen_bilibili, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
		}
		guider_ui.screen_systerm_del = true;
	}
		break;
	default:
		break;
	}
}

static void screen_systerm_imgbtn_2051_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_RELEASED:
	{
		lv_disp_t * d = lv_obj_get_disp(lv_scr_act());
		if (d->prev_scr == NULL && d->scr_to_load == NULL)
		{
            switch_screen(SCREEN_2);  // 切换到屏幕 2
			// if (guider_ui.screen_2_del == true)
			// 	setup_scr_screen_2(&guider_ui);
			// lv_scr_load_anim(guider_ui.screen_2, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
		}
		guider_ui.screen_systerm_del = true;
	}
		break;
	default:
		break;
	}
}
static void screen_systerm_imgbtn_setting_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_RELEASED:
	{
		lv_disp_t * d = lv_obj_get_disp(lv_scr_act());
		if (d->prev_scr == NULL && d->scr_to_load == NULL)
		{
            switch_screen(SCREEN_SETTING);
			// if (guider_ui.screen_setting_del == true)
			// 	setup_scr_screen_setting(&guider_ui);
			// lv_scr_load_anim(guider_ui.screen_setting, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
		}
		guider_ui.screen_systerm_del = true;
	}
		break;
	default:
		break;
	}
}

static void screen_systerm_imgbtn_Pic_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_RELEASED:
	{
		lv_disp_t * d = lv_obj_get_disp(lv_scr_act());
		if (d->prev_scr == NULL && d->scr_to_load == NULL)
		{
            switch_screen(SCREEN_PICTURE);
			// if (guider_ui.screen_Picture_del == true)
			// 	setup_scr_screen_Picture(&guider_ui);
			// lv_scr_load_anim(guider_ui.screen_Picture, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
		}
		guider_ui.screen_systerm_del = true;
	}
		break;
	default:
		break;
	}
}

void events_init_screen_systerm(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_systerm_imgbtn_weather, screen_systerm_imgbtn_weather_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_systerm_imgbtn_bili, screen_systerm_imgbtn_bili_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_systerm_imgbtn_setting, screen_systerm_imgbtn_setting_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_systerm_imgbtn_Pic, screen_systerm_imgbtn_Pic_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_systerm_imgbtn_2051, screen_systerm_imgbtn_2051_event_handler, LV_EVENT_ALL, NULL);
}

static void screen_setting_slider_backlight_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_VALUE_CHANGED:
	{
        int16_t current_value = lv_slider_get_value(guider_ui.screen_setting_slider_backlight);
        printf("backlight current_value:%d\n", current_value);
        if(current_value <= 10)
            current_value = 10;
        current_value = current_value*10;
        printf("pwm_set_duty backlight :%d\n", current_value);
        pwm_set_duty(current_value*10);
	}
		break;
	default:
		break;
	}
}

static void screen_setting_btn_home_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		lv_disp_t * d = lv_obj_get_disp(lv_scr_act());
		if (d->prev_scr == NULL && d->scr_to_load == NULL)
		{
            switch_screen(SCREEN_SYSTERM);
			// if (guider_ui.screen_systerm_del == true)
			// 	setup_scr_screen_systerm(&guider_ui);
			// lv_scr_load_anim(guider_ui.screen_systerm, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
		}
		guider_ui.screen_setting_del = true;
	}
		break;
	default:
		break;
	}
}

void events_init_screen_setting(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_setting_slider_backlight, screen_setting_slider_backlight_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_setting_btn_home, screen_setting_btn_home_event_handler, LV_EVENT_ALL, NULL);
}

static void screen_bilibili_btn_home_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		lv_disp_t * d = lv_obj_get_disp(lv_scr_act());
		if (d->prev_scr == NULL && d->scr_to_load == NULL)
		{
            // 需要销毁时
            if (xBiliBiliTask != NULL) {
                vTaskDelete(xBiliBiliTask);
                xBiliBiliTask = NULL; // 避免野指针
            }
            switch_screen(SCREEN_SYSTERM);
			// if (guider_ui.screen_systerm_del == true)
			// 	setup_scr_screen_systerm(&guider_ui);
			// lv_scr_load_anim(guider_ui.screen_systerm, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
		}
		guider_ui.screen_bilibili_del = true;
	}
		break;
	default:
		break;
	}
}

void events_init_screen_bilibili(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_bilibili_btn_home, screen_bilibili_btn_home_event_handler, LV_EVENT_ALL, NULL);
}

static void screen_Picture_btn_Home_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		lv_disp_t * d = lv_obj_get_disp(lv_scr_act());
		if (d->prev_scr == NULL && d->scr_to_load == NULL)
		{
			if (guider_ui.screen_systerm_del == true)
				setup_scr_screen_systerm(&guider_ui);
			lv_scr_load_anim(guider_ui.screen_systerm, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
		}
		guider_ui.screen_Picture_del = true;
	}
		break;
	default:
		break;
	}
}

static void screen_Picture_btn_Switch_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{

	}
		break;
	default:
		break;
	}
}

void events_init_screen_Picture(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_Picture_btn_Home, screen_Picture_btn_Home_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_Picture_btn_Switch, screen_Picture_btn_Switch_event_handler, LV_EVENT_ALL, NULL);
}


// 屏幕 1 的事件处理函数
static void screen_home_jiasu_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
        int16_t current_value = lv_slider_get_value(guider_ui.screen_home_slider);
        int16_t new_value = current_value + 10;
        if (new_value > lv_slider_get_max_value(guider_ui.screen_home_slider)) {
            new_value = lv_slider_get_max_value(guider_ui.screen_home_slider);
        }
        lv_slider_set_value(guider_ui.screen_home_slider, new_value, LV_ANIM_ON);
        update_slider_label(guider_ui.screen_home_slider, guider_ui.screen_home_sliderText);
    }
}

static void screen_home_jiansu_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
        int16_t current_value = lv_slider_get_value(guider_ui.screen_home_slider);
        int16_t new_value = current_value - 10;
        if (new_value < lv_slider_get_min_value(guider_ui.screen_home_slider)) {
            new_value = lv_slider_get_min_value(guider_ui.screen_home_slider);
        }
        lv_slider_set_value(guider_ui.screen_home_slider, new_value, LV_ANIM_ON);
        update_slider_label(guider_ui.screen_home_slider, guider_ui.screen_home_sliderText);
    }
}

static void screen_home_slider_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_VALUE_CHANGED) {
        update_slider_label(guider_ui.screen_home_slider, guider_ui.screen_home_sliderText);
    }
}

static void screen_home_jiting_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
        lv_slider_set_value(guider_ui.screen_home_slider, 0, LV_ANIM_ON);
        update_slider_label(guider_ui.screen_home_slider, guider_ui.screen_home_sliderText);
    }
}

static void screen_home_Next_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
        switch_screen(SCREEN_2);  // 切换到屏幕 2
    }
}

static void screen_home_sw_led_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_VALUE_CHANGED) {
        bool sw_state = lv_obj_has_state(guider_ui.screen_home_sw_led, LV_STATE_CHECKED);
        if (sw_state) {
            lv_led_on(guider_ui.screen_home_led);
            lv_label_set_text(guider_ui.screen_home_label_led, "ON");
        } else {
            lv_led_off(guider_ui.screen_home_led);
            lv_label_set_text(guider_ui.screen_home_label_led, "OFF");
        }
    }
}

void events_init_screen_home(lv_ui *ui) {
    lv_obj_add_event_cb(ui->screen_home_jiasu, screen_home_jiasu_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_home_jiansu, screen_home_jiansu_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_home_slider, screen_home_slider_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_home_jiting, screen_home_jiting_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_home_Next, screen_home_Next_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_home_sw_led, screen_home_sw_led_event_handler, LV_EVENT_ALL, NULL);
}

// 屏幕 2 的事件处理函数
static void screen_2_back_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
        switch_screen(SCREEN_HOME);  // 切换到主屏幕
    }
}

static void screen_2_next_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
        switch_screen(SCREEN_3);  // 切换到屏幕 3
    }
}

static void screen_2_btn_Home_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		lv_disp_t * d = lv_obj_get_disp(lv_scr_act());
		if (d->prev_scr == NULL && d->scr_to_load == NULL)
		{
            switch_screen(SCREEN_SYSTERM);  // 切换到屏幕 3
			// if (guider_ui.screen_systerm_del == true)
			// 	setup_scr_screen_systerm(&guider_ui);
			// lv_scr_load_anim(guider_ui.screen_systerm, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
		}
		guider_ui.screen_2_del = true;
	}
		break;
	default:
		break;
	}
}


void events_init_screen_2(lv_ui *ui) {
    lv_obj_add_event_cb(ui->screen_2_back, screen_2_back_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_2_next, screen_2_next_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_2_btn_Home, screen_2_btn_Home_event_handler, LV_EVENT_ALL, NULL);
}

static void screen_3_btn_Home_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		lv_disp_t * d = lv_obj_get_disp(lv_scr_act());
		if (d->prev_scr == NULL && d->scr_to_load == NULL)
		{
            // 需要销毁时
            if (xHttpTask != NULL) {
                vTaskDelete(xHttpTask);
                xHttpTask = NULL; // 避免野指针
            }
            switch_screen(SCREEN_SYSTERM);
			// if (guider_ui.screen_systerm_del == true)
			// 	setup_scr_screen_systerm(&guider_ui);
			// lv_scr_load_anim(guider_ui.screen_systerm, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
		}
		guider_ui.screen_3_del = true;
	}
		break;
	default:
		break;
	}
}

// 屏幕 3 的事件处理函数
static void screen_3_backbtn_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
        // 需要销毁时
        if (xHttpTask != NULL) {
            vTaskDelete(xHttpTask);
            xHttpTask = NULL; // 避免野指针
        }
        switch_screen(SCREEN_2);  // 切换到屏幕 2
    }
}

void events_init_screen_3(lv_ui *ui) {
    lv_obj_add_event_cb(ui->screen_3_backbtn, screen_3_backbtn_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_3_btn_Home, screen_3_btn_Home_event_handler, LV_EVENT_ALL, NULL);
}

