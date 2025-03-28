/*
 * Copyright 2025 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */


#ifndef EVENTS_INIT_H_
#define EVENTS_INIT_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"



// 定义屏幕状态枚举
typedef enum {
    SCREEN_INIT,
    SCREEN_SYSTERM,
    SCREEN_BILIBILI,
    SCREEN_HOME,
    SCREEN_2,
    SCREEN_3
} screen_state_t;

extern screen_state_t current_screen;  // 当前屏幕状态


void events_init(lv_ui *ui);
void events_init_screen_systerm(lv_ui *ui);
void events_init_screen_home(lv_ui *ui);
void events_init_screen_2(lv_ui *ui);
void events_init_screen_3(lv_ui *ui);
void events_init_screen_bilibili(lv_ui *ui);

extern const char* get_image_path(char* weather_code);
extern char *image_jinri_path; // 用于存储完整路径
extern char *image_mingri_path; // 用于存储完整路径
extern char *image_houri_path; // 用于存储完整路径

// 声明时针、分针和秒针的指针变量
extern lv_meter_indicator_t *indic_hour;
extern lv_meter_indicator_t *indic_min;
extern lv_meter_indicator_t *indic_sec;
extern lv_obj_t *meter;
void switch_screen(screen_state_t new_screen);
#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */