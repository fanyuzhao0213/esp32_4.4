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
    SCREEN_HOME,
    SCREEN_2,
    SCREEN_3
} screen_state_t;

void events_init(lv_ui *ui);
void events_init_screen_home(lv_ui *ui);
void events_init_screen_2(lv_ui *ui);
void events_init_screen_3(lv_ui *ui);
extern screen_state_t current_screen;  // 当前屏幕状态

#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */