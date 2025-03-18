/*
 * Copyright 2025 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"


void init_scr_del_flag(lv_ui *ui){
	ui->screen_home_del = true;
	ui->screen_2_del = true;
	ui->screen_3_del = true;
}

void setup_ui(lv_ui *ui){
	init_scr_del_flag(ui);
	setup_scr_screen_home(ui);
	lv_scr_load(ui->screen_home);
}

void clock_count(int *hour, int *min, int *sec)
{
    (*sec)++;
    if(*sec == 60)
    {
        *sec = 0;
        (*min)++;
    }
    if(*min == 60)
    {
        *min = 0;
        if(*hour < 12)
        {
            (*hour)++;
        } else {
            (*hour)++;
            *hour = *hour %12;
        }
    }
}