#ifndef __USART_H_
#define __USART_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_log.h"
#include <string.h>
#include "driver/gpio.h"

#define UART_NUM            UART_NUM_2             // 使用 UART2
#define TXD_PIN             (GPIO_NUM_43)           // UART2 TX 引脚
#define RXD_PIN             (GPIO_NUM_44)           // UART2 RX 引脚
#define BUF_SIZE            1024                   // 接收缓冲区大小
#define TIMEOUT_MS          100

#define PACKET_HEADER      0xAA            // 包头标识
#define MAX_PAYLOAD_LEN    1024            // 最大有效载荷长度


typedef struct
{
    uint8_t uart_revbuf[BUF_SIZE];
    uint16_t pr_w;
    uint16_t pr_r;
}Rev_uart_t;

extern Rev_uart_t Rev_uart;

extern void usart_init(void);
extern void usart_send_payload(const uint8_t *payload, uint16_t payload_len);
extern uint8_t usart_rev_analysis(uint8_t *data, uint16_t len);
extern uint8_t CRC16_CCITT_CHECK(uint8_t *puchMsg, uint16_t usDataLen);
extern uint16_t CRC16_CCITT(uint8_t *puchMsg, uint16_t usDataLen);
#endif