/**
 ****************************************************************************************************
 * @file        led.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-08-26
 * @brief       LED驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 ESP32-S3 开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#ifndef __LED_H_
#define __LED_H_

#include "driver/gpio.h"


/* 引脚定义 */
#define LED_GPIO_PIN1        GPIO_NUM_10  /* LED连接的GPIO端口 */
#define LED_GPIO_PIN2       GPIO_NUM_11  /* LED连接的GPIO端口 */

/* 引脚的输出的电平状态 */
enum GPIO_OUTPUT_STATE
{
    PIN_RESET,
    PIN_SET
};

/* LED端口定义 */
#define LED1(x)          do { x ?                                      \
                             gpio_set_level(LED_GPIO_PIN1, PIN_SET) :  \
                             gpio_set_level(LED_GPIO_PIN1, PIN_RESET); \
                        } while(0)  /* LED翻转 */

/* LED端口定义 */
#define LED2(x)          do { x ?                                      \
                             gpio_set_level(LED_GPIO_PIN2, PIN_SET) :  \
                             gpio_set_level(LED_GPIO_PIN2, PIN_RESET); \
                        } while(0)  /* LED翻转 */

/* LED取反定义 */
#define LED1_TOGGLE()    do { gpio_set_level(LED_GPIO_PIN1, !gpio_get_level(LED_GPIO_PIN1)); } while(0)  /* LED翻转 */
#define LED2_TOGGLE()    do { gpio_set_level(LED_GPIO_PIN2, !gpio_get_level(LED_GPIO_PIN2)); } while(0)  /* LED翻转 */

/* 函数声明*/
void led1_init(void);    /* 初始化LED */
void led2_init(void);    /* 初始化LED */
#endif
