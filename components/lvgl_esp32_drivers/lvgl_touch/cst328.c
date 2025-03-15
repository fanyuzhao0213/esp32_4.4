#include <esp_log.h>
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include <lvgl.h>
#else
#include <lvgl/lvgl.h>
#endif
#include "cst328.h"
#include "lvgl_i2c/i2c_manager.h"

#include "lvgl_helpers.h"

#define CST328_RST_PIN GPIO_NUM_2
#define CST328_INT_PIN GPIO_NUM_4

#define TAG "CST328"

cst328_status_t cst328_status;

esp_err_t cst328_i2c_read(uint8_t slave_addr, uint16_t register_addr, uint8_t *data_buf, uint8_t len) {
    return lvgl_i2c_read(CONFIG_LV_I2C_TOUCH_PORT, slave_addr, register_addr | I2C_REG_16, data_buf, len);
}

esp_err_t cst328_i2c_write(uint8_t slave_addr, uint16_t register_addr, uint8_t *data_buf, uint8_t len) {
    if (len == 0)
    {
        uint8_t register_buf[2] = {(uint8_t)(register_addr >> 8), (uint8_t)(register_addr)};
        return lvgl_i2c_write(CONFIG_LV_I2C_TOUCH_PORT, slave_addr, register_addr | I2C_NO_REG, register_buf, 2);
    }
    else
        return lvgl_i2c_write(CONFIG_LV_I2C_TOUCH_PORT, slave_addr, register_addr | I2C_REG_16, data_buf, len);
}

static void cst328_rst() {
    vTaskDelay(pdMS_TO_TICKS(50));
    gpio_set_direction(CST328_INT_PIN, (GPIO_MODE_INPUT)| (GPIO_MODE_DEF_OD));
    gpio_set_direction(CST328_RST_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(CST328_INT_PIN, 1);
    gpio_set_level(CST328_RST_PIN, 1);
    vTaskDelay(pdMS_TO_TICKS(50));
    gpio_set_level(CST328_RST_PIN, 0);
    vTaskDelay(pdMS_TO_TICKS(5));
    gpio_set_level(CST328_RST_PIN, 1);
    vTaskDelay(pdMS_TO_TICKS(200));
    gpio_set_level(CST328_INT_PIN, 0);
}

/**
  * @brief  Initialize for CS328 communication via I2C
  * @param  dev_addr: Device address on communication Bus (I2C slave address of GT911).
  * @retval None
  */
void cst328_init(uint8_t dev_addr) {
    cst328_rst();
    if (!cst328_status.inited) {

        cst328_status.i2c_dev_addr = dev_addr;
        cst328_status.max_x_coord = LV_HOR_RES_MAX;
        cst328_status.max_y_coord = LV_VER_RES_MAX;

        uint8_t data_buf[4];
        esp_err_t ret;

        ESP_LOGI(TAG, "Checking for CST328 Touch Controller");
        if ((ret = cst328_i2c_write(dev_addr, HYN_REG_MUT_DEBUG_INFO_MODE, data_buf, 0) != ESP_OK)) {
            ESP_LOGE(TAG, "Error reading from device: %s",
                 esp_err_to_name(ret));    // Only show error the first time
            return;
        }
        cst328_i2c_read(dev_addr, HYN_REG_MUT_DEBUG_INFO_BOOT_TIME, data_buf, 4);
        cst328_i2c_write(dev_addr, HYN_REG_MUT_NORMAL_MODE, data_buf, 0);

        uint16_t Verification = (uint16_t)(data_buf[3] << 8) | data_buf[2];

        if(!((Verification==0xCACA)?true:false)){
            ESP_LOGE(TAG, "Touch initialization failed!\r\n");
            cst328_status.inited = false;
        }
        else
        {
            ESP_LOGI(TAG, "Touch initialization success!\r\n");
            cst328_status.inited = true;
        }
    }
}

/**
  * @brief  Get the touch screen X and Y positions values. Ignores multi touch
  * @param  drv:
  * @param  data: Store data here
  * @retval Always false
  */
bool cst328_read(lv_indev_drv_t *drv, lv_indev_data_t *data) {
    uint8_t touch_pnt_cnt = 0;        // Number of detected touch points
    const uint8_t clear = 0;
    static int16_t last_x = 0;  // 12bit pixel value
    static int16_t last_y = 0;  // 12bit pixel value
    uint8_t data_buf[3];

    cst328_i2c_read(cst328_status.i2c_dev_addr, ESP_LCD_TOUCH_CST328_READ_Number_REG, data_buf, 1); // 读取触控数量
    touch_pnt_cnt = data_buf[0] & 0x0F;
    // ESP_LOGI(TAG, "touchnum:%d", touch_pnt_cnt);
    if (touch_pnt_cnt != 1){ // ignore no touch & multi touch
        data->point.x = last_x;
        data->point.y = last_y;
        data->state = LV_INDEV_STATE_REL;
        cst328_i2c_write(cst328_status.i2c_dev_addr, ESP_LCD_TOUCH_CST328_READ_Number_REG, (uint8_t *)&clear, 1);
        return false;
    }

    cst328_i2c_read(cst328_status.i2c_dev_addr, ESP_LCD_TOUCH_CST328_READ_XY_REG + 1, &data_buf[0], 3); // 只取第一个通道的坐标
    cst328_i2c_write(cst328_status.i2c_dev_addr, ESP_LCD_TOUCH_CST328_READ_Number_REG, (uint8_t *)&clear, 1);

    last_x = (uint16_t)(((uint16_t)data_buf[0] << 4) + ((data_buf[2] & 0xF0)>> 4));
    last_y = (uint16_t)(((uint16_t)data_buf[1] << 4) + (data_buf[2] & 0x0F));

#ifdef CONFIG_LV_CST328_SWAPXY
    int16_t swap_buf = last_x;
    last_x = last_y;
    last_y = swap_buf;
#endif
#ifdef CONFIG_LV_CST328_INVERT_X
    last_x = cst328_status.max_x_coord - last_x;
#endif
#ifdef CONFIG_LV_CST328_INVERT_Y
    last_y = cst328_status.max_y_coord - last_y;
#endif

    data->point.x = last_x;
    data->point.y = last_y;
    data->state = LV_INDEV_STATE_PR;
    // ESP_LOGI(TAG, "X=%u Y=%u", data->point.x, data->point.y);
    // ESP_LOGV(TAG, "X=%u Y=%u", data->point.x, data->point.y);
    return false;
}
