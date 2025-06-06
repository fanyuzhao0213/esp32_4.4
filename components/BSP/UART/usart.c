
#include "usart.h"
#include "ble.h"

Rev_uart_t Rev_uart;
static const char *TAG = "UART";
static QueueHandle_t uart_queue;
static uint8_t uart_tx_buf[100] = {0};

void LOG_HEXDUMP_PRINT(char*str, uint8_t *data, uint16_t len)
{
    printf("%s\n",str);
    for(uint16_t i = 0; i < len;i++)
    {
        printf("%02x ", data[i]);
    }
    printf("\n");
}

void uart_receive_task(void *arg)
{
    uint8_t data[BUF_SIZE];
    TickType_t last_receive_time = 0;  // 记录最后一次接收到数据的时间

    while (1)
    {
        // 等待 UART 队列中的事件
        uart_event_t event;
        if (xQueueReceive(uart_queue, (void *)&event, portMAX_DELAY))
        {
            ESP_LOGI(TAG, "Event received: %d", event.type);  // 打印接收到的事件类型

            switch (event.type)
            {
                case UART_DATA:  // 接收到数据
                    uart_read_bytes(UART_NUM, data, event.size, portMAX_DELAY);
                    memcpy(&Rev_uart.uart_revbuf[Rev_uart.pr_w], data, event.size);  // 复制数据
                    Rev_uart.pr_w = (Rev_uart.pr_w + event.size) % BUF_SIZE; // 确保索引不越界
                    // LOG_HEXDUMP_PRINT("REV DATA:",&Rev_uart.uart_revbuf[Rev_uart.pr_w],event.size);
                    LOG_HEXDUMP_PRINT("REV DATA:", data, event.size);
                    usart_rev_analysis(data, event.size);
                    break;

                // UART FIFO 缓冲区溢出事件
                case UART_FIFO_OVF:
                    ESP_LOGW(TAG, "Hardware FIFO Overflow");
                    uart_flush_input(UART_NUM);
                    xQueueReset(uart_queue);
                    break;

                // UART 缓冲区满事件
                case UART_BUFFER_FULL:
                    ESP_LOGW(TAG, "Ring Buffer Full");
                    uart_flush_input(UART_NUM);
                    xQueueReset(uart_queue);
                    break;

                // UART 帧错误事件
                case UART_FRAME_ERR:
                    ESP_LOGW(TAG, "UART Frame Error");
                    break;

                // UART 奇偶校验错误事件
                case UART_PARITY_ERR:
                    ESP_LOGW(TAG, "UART Parity Error");
                    break;

                default:
                    ESP_LOGW(TAG, "Unknown event type: %d", event.type);  // 打印未知事件类型
                    break;
            }
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);  // 稍微延时，避免占用过多 CPU
    }
}


void usart_init()
{
    // 配置 UART 参数
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    // 初始化 UART
    uart_param_config(UART_NUM, &uart_config);

    // 设置 UART 引脚 (根据实际硬件配置)
    uart_set_pin(UART_NUM, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    // 安装 UART 驱动程序
    uart_driver_install(UART_NUM, BUF_SIZE * 2, BUF_SIZE * 2, 20, &uart_queue, 0);

    ESP_LOGI(TAG, "UART init finished!");
    const uint8_t test_data1[] = {0x01, 0x02, 0x03, 0x04};
    usart_send_packet(test_data1, sizeof(test_data1));
    // 创建处理 UART 事件的任务
    xTaskCreate(uart_receive_task, "uart_receive_task", 4096, NULL, 5, NULL);
    ESP_LOGI(TAG, "uart_receive_task create finished!");
}

void usart_send_packet(const uint8_t *payload, uint16_t payload_len)
{
    // 检查有效载荷长度是否合法
    if (payload_len > MAX_PAYLOAD_LEN) {
        ESP_LOGE(TAG, "Payload too large: %d bytes (max %d)", payload_len, MAX_PAYLOAD_LEN);
        return;
    }

    // 计算整个数据包长度: 包头(2) + 长度字段(2) + 有效载荷 + CRC(2)
    uint16_t packet_len = 2 + 2 + payload_len + 2;
    uint8_t  packet[packet_len];

    // 填充包头
    packet[0] = PACKET_HEADER;
    packet[1] = PACKET_HEADER;

    // 填充长度字段
    packet[2] = (packet_len >> 8) & 0xFF;        // 高字节
    packet[3] = packet_len  & 0xFF; // 高字节

    // 复制有效载荷
    memcpy(&packet[4], payload, payload_len);

    // 计算CRC (从长度字段开始到有效载荷结束)
    uint16_t crc = CRC16_CCITT(&packet[4], payload_len);

    // 填充CRC
    packet[packet_len - 2] = crc & 0xFF;        // CRC低字节
    packet[packet_len - 1] = (crc >> 8) & 0xFF; // CRC高字节

    // 打印调试信息
    ESP_LOGI(TAG, "Sending packet: len=%d, payload_len=%d, CRC=0x%04X",
             packet_len, payload_len, crc);
    LOG_HEXDUMP_PRINT("Packet data:", packet, packet_len);

    // 发送数据包
    uart_write_bytes(UART_NUM, (const char*)packet, packet_len);
}


uint8_t usart_rev_analysis(uint8_t *data, uint16_t len)
{
    uint16_t command_id = 0;
    uint16_t crc_value = 0;
    // 检查长度是否合法
    if (len > MAX_PAYLOAD_LEN) {
        ESP_LOGE(TAG, "Payload too large: %d bytes (max %d)", len, MAX_PAYLOAD_LEN);
        return 1;
    }

    if (data[0] != 0xAA || data[1] != 0xAA) {
        ESP_LOGE(TAG, "command header is not correct!");
        return 2;
    }

    uint8_t error = CRC16_CCITT_CHECK(&data[4],len-4);
    if(error == 1)	//校验正确
    {
        command_id = (data[4]<<8) + data[5];
        ESP_LOGI(TAG, "rev 0xAA 0xAAcommand_id=%04x", command_id);
        switch(command_id)
        {
            case 0x0001:
                uart_tx_buf[0] = 0x00;
                uart_tx_buf[1] = 0x01;
                uart_tx_buf[2] = 0x01;
                usart_send_packet(uart_tx_buf, 3);
                esp_ble_gap_set_scan_params(&ble_scan_params);
                esp_ble_gap_start_scanning(30); // 扫描30秒
                break;
            case 0x0002:
                uart_tx_buf[0] = 0x00;
                uart_tx_buf[1] = 0x01;
                uart_tx_buf[2] = 0x02;
                usart_send_packet(uart_tx_buf, 3);
                break;
            case 0x0003:
                uart_tx_buf[0] = 0x00;
                uart_tx_buf[1] = 0x01;
                uart_tx_buf[2] = 0x03;
                usart_send_packet(uart_tx_buf, 3);
                break;
            case 0x0004:
                uart_tx_buf[0] = 0x00;
                uart_tx_buf[1] = 0x01;
                uart_tx_buf[2] = 0x04;
                usart_send_packet(uart_tx_buf, 3);
                break;
            case 0x0005:
                uart_tx_buf[0] = 0x00;
                uart_tx_buf[1] = 0x01;
                uart_tx_buf[2] = 0x05;
                usart_send_packet(uart_tx_buf, 3);
                break;
            default:
            break;
        }
    }
    else	//校验失败
    {
        ESP_LOGI(TAG, "check error!");
        return 3;
    }
    return 0;
}


/**
 * @name: CRC16_CCITT
 * @msg:  该函数可生成16位的CCITT类型CRC校验位，Polynomial: 0x1021，Initial Value: 0x0000
 * @param [in]
 *         uint8_t *puchMsg：待生成校验位的原始数据
 *         uint16_t usDataLen： puchMsg数据长度
 * @param [out]
 *         无
 * @return 返回值位生成的校验位
 * @note:  无
 */
uint16_t CRC16_CCITT(uint8_t *puchMsg, uint16_t usDataLen)
{
    uint16_t wCRCin = 0x0000;
    uint16_t wCPoly = 0x1021;
    uint8_t wChar = 0;
    uint8_t i = 0;

    while (usDataLen--)
    {
        wChar = *(puchMsg++);
        wCRCin ^= (wChar << 8);

        for (i = 0; i < 8; i++)
        {
            if (wCRCin & 0x8000)
            {
                wCRCin = (wCRCin << 1) ^ wCPoly;
            }
            else
            {
                wCRCin = wCRCin << 1;
            }
        }
    }
    // InvertUint16(&wCRCin, &wCRCin);
    return (wCRCin);
}

/**
 * @name: CRC16_CCITT_CHECK
 * @msg:  校验16位的CCITT是否正确
 * @param [in]
 *         uint8_t *puchMsg：待生成校验位的原始数据
 *         uint16_t usDataLen： puchMsg数据长度
 * @param [out]
 *         无
 * @return 0:校验失败；1：校验成功
 * @note:  此时包括数据中的校验位
 */
uint8_t CRC16_CCITT_CHECK(uint8_t *puchMsg, uint16_t usDataLen)
{
    uint16_t crc = 0;
    uint16_t crcvalue = 0;
    crc = CRC16_CCITT(puchMsg, usDataLen - 2);
    ESP_LOGI(TAG,"[CRC] crc value:%04x",crc);
    crcvalue = (puchMsg[usDataLen - 2] << 8) + puchMsg[usDataLen - 1];
    if(crc != crcvalue)
        return 0;
    else
        return 1;
}

