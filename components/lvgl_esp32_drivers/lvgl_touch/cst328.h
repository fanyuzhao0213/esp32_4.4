#ifndef __CST328_H
#define __CST328_H

#include <stdint.h>
#include <stdbool.h>
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define CST328_I2C_SLAVE_ADDR                   0x1A
#define CST328_LCD_TOUCH_MAX_POINTS             (5)
/* CST328 registers */
#define ESP_LCD_TOUCH_CST328_READ_Number_REG    (0xD005)
#define ESP_LCD_TOUCH_CST328_READ_XY_REG        (0xD000)
#define ESP_LCD_TOUCH_CST328_READ_Checksum_REG  (0x80FF)
#define ESP_LCD_TOUCH_CST328_CONFIG_REG         (0x8047)

//debug info
/****************HYN_REG_MUT_DEBUG_INFO_MODE address start***********/
#define HYN_REG_MUT_DEBUG_INFO_IC_CHECKSUM      0xD208
#define HYN_REG_MUT_DEBUG_INFO_FW_VERSION       0xD204
#define HYN_REG_MUT_DEBUG_INFO_IC_TYPE			0xD202
#define HYN_REG_MUT_DEBUG_INFO_PROJECT_ID		0xD200
#define HYN_REG_MUT_DEBUG_INFO_BOOT_TIME        0xD1FC
#define HYN_REG_MUT_DEBUG_INFO_RES_Y            0xD1FA
#define HYN_REG_MUT_DEBUG_INFO_RES_X            0xD1F8
#define HYN_REG_MUT_DEBUG_INFO_KEY_NUM          0xD1F7
#define HYN_REG_MUT_DEBUG_INFO_TP_NRX           0xD1F6
#define HYN_REG_MUT_DEBUG_INFO_TP_NTX           0xD1F4
//workmode
#define HYN_REG_MUT_DEBUG_INFO_MODE             0xD101
#define HYN_REG_MUT_RESET_MODE            	    0xD102
#define HYN_REG_MUT_DEBUG_RECALIBRATION_MODE    0xD104
#define HYN_REG_MUT_DEEP_SLEEP_MODE    			0xD105
#define HYN_REG_MUT_DEBUG_POINT_MODE	    	0xD108
#define HYN_REG_MUT_NORMAL_MODE                 0xD109

#define HYN_REG_MUT_DEBUG_RAWDATA_MODE          0xD10A
#define HYN_REG_MUT_DEBUG_DIFF_MODE             0xD10D
#define HYN_REG_MUT_DEBUG_FACTORY_MODE          0xD119
#define HYN_REG_MUT_DEBUG_FACTORY_MODE_2        0xD120

//Interrupt Modes
#define RISING    0x01
#define FALLING   0x02
#define CHANGE    0x03
#define ONLOW     0x04
#define ONHIGH    0x05
#define ONLOW_WE  0x0C
#define ONHIGH_WE 0x0D

typedef struct {
    bool inited;
    uint16_t max_x_coord;
    uint16_t max_y_coord;
    uint8_t i2c_dev_addr;
} cst328_status_t;

void cst328_init(uint8_t dev_addr);
bool cst328_read(lv_indev_drv_t *drv, lv_indev_data_t *data);

#ifdef __cplusplus
}
#endif
#endif /* __CST328_H */
