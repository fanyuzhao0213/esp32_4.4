#include "mqtt.h"

static const char* TAG = "MQTT";

#define MQTT_ADDRESS    "mqtt://broker-cn.emqx.io"      //MQTT连接地址
#define MQTT_PORT       1883                            //MQTT连接端口号
#define MQTT_CLIENT     "mqttx_esp32s3"                 //Client ID（设备唯一，大家最好自行改一下）
#define MQTT_USERNAME   "esp32s3"                       //MQTT用户名
#define MQTT_PASSWORD   "12345678"                      //MQTT密码

#define MQTT_PUBLIC_TOPIC       "/pub/topic"            //推送消息主题
#define MQTT_SUBSCRIBE_TOPIC    "/sub/topic"            //订阅的主题

static esp_mqtt_client_handle_t     s_mqtt_client = NULL;
static bool s_is_mqtt_connected = false;

/**
 * mqtt连接事件处理函数
 * @param event 事件参数
 * @return 无
 */
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;

    switch ((esp_mqtt_event_id_t)event_id) {
        case MQTT_EVENT_CONNECTED:  // 连接成功
            ESP_LOGI(TAG, "MQTT connected");
            s_is_mqtt_connected = true;
            // 订阅测试主题
            esp_mqtt_client_subscribe(s_mqtt_client, MQTT_SUBSCRIBE_TOPIC, 1);
            break;
        case MQTT_EVENT_DISCONNECTED:  // 断开连接
            ESP_LOGI(TAG, "MQTT disconnected");
            s_is_mqtt_connected = false;
            break;
        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG, "Subscribed to topic, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(TAG, "Message published, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            printf("Received topic: %.*s\r\n", event->topic_len, event->topic);
            printf("Received data: %.*s\r\n", event->data_len, event->data);
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
            break;
        default:
            ESP_LOGI(TAG, "Other event id:%d", event_id);
            break;
    }
}

/**
 * 启动 MQTT 连接
 */
void mqtt_start(void)
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .uri = MQTT_ADDRESS,        // 设置连接地址
        .port = MQTT_PORT,          // 设置端口号
        .client_id = MQTT_CLIENT,   // Client ID
        .username = MQTT_USERNAME,  // 用户名
        .password = MQTT_PASSWORD   // 密码
    };

    ESP_LOGI(TAG, "MQTT connecting: client_id=%s, username=%s, password=%s", mqtt_cfg.client_id, mqtt_cfg.username, mqtt_cfg.password);

    s_mqtt_client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(s_mqtt_client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(s_mqtt_client);
    xTaskCreate(mqtt_pub_task, "mqtt_pub_task", 2048, NULL, 3, NULL);
}

/**
 * 发布 MQTT 消息任务
 */
void mqtt_pub_task(void *pvParameters)
{
    int count = 0;
    static char mqtt_pub_buff[64];

    while (1) {
        if (s_is_mqtt_connected) {
            snprintf(mqtt_pub_buff, sizeof(mqtt_pub_buff), "{\"count\":\"%d\"}", count);
            esp_mqtt_client_publish(s_mqtt_client, MQTT_PUBLIC_TOPIC, mqtt_pub_buff, 0, 1, 0);
            count++;
        }
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}


