#include "bilibili.h"

static const char *BILI_TAG = "BiliBili";
BiliUserInfo current_user; // 全局存储用户数据
int g_GetBiliBili_Info_Flag = 0;

static const char bilibili_cert_pem[] =
"-----BEGIN CERTIFICATE-----\n"
"MIIETjCCAzagAwIBAgINAe5fIh38YjvUMzqFVzANBgkqhkiG9w0BAQsFADBMMSAw\n"
"HgYDVQQLExdHbG9iYWxTaWduIFJvb3QgQ0EgLSBSMzETMBEGA1UEChMKR2xvYmFs\n"
"U2lnbjETMBEGA1UEAxMKR2xvYmFsU2lnbjAeFw0xODExMjEwMDAwMDBaFw0yODEx\n"
"MjEwMDAwMDBaMFAxCzAJBgNVBAYTAkJFMRkwFwYDVQQKExBHbG9iYWxTaWduIG52\n"
"LXNhMSYwJAYDVQQDEx1HbG9iYWxTaWduIFJTQSBPViBTU0wgQ0EgMjAxODCCASIw\n"
"DQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKdaydUMGCEAI9WXD+uu3Vxoa2uP\n"
"UGATeoHLl+6OimGUSyZ59gSnKvuk2la77qCk8HuKf1UfR5NhDW5xUTolJAgvjOH3\n"
"idaSz6+zpz8w7bXfIa7+9UQX/dhj2S/TgVprX9NHsKzyqzskeU8fxy7quRU6fBhM\n"
"abO1IFkJXinDY+YuRluqlJBJDrnw9UqhCS98NE3QvADFBlV5Bs6i0BDxSEPouVq1\n"
"lVW9MdIbPYa+oewNEtssmSStR8JvA+Z6cLVwzM0nLKWMjsIYPJLJLnNvBhBWk0Cq\n"
"o8VS++XFBdZpaFwGue5RieGKDkFNm5KQConpFmvv73W+eka440eKHRwup08CAwEA\n"
"AaOCASkwggElMA4GA1UdDwEB/wQEAwIBhjASBgNVHRMBAf8ECDAGAQH/AgEAMB0G\n"
"A1UdDgQWBBT473/yzXhnqN5vjySNiPGHAwKz6zAfBgNVHSMEGDAWgBSP8Et/qC5F\n"
"JK5NUPpjmove4t0bvDA+BggrBgEFBQcBAQQyMDAwLgYIKwYBBQUHMAGGImh0dHA6\n"
"Ly9vY3NwMi5nbG9iYWxzaWduLmNvbS9yb290cjMwNgYDVR0fBC8wLTAroCmgJ4Yl\n"
"aHR0cDovL2NybC5nbG9iYWxzaWduLmNvbS9yb290LXIzLmNybDBHBgNVHSAEQDA+\n"
"MDwGBFUdIAAwNDAyBggrBgEFBQcCARYmaHR0cHM6Ly93d3cuZ2xvYmFsc2lnbi5j\n"
"b20vcmVwb3NpdG9yeS8wDQYJKoZIhvcNAQELBQADggEBAJmQyC1fQorUC2bbmANz\n"
"EdSIhlIoU4r7rd/9c446ZwTbw1MUcBQJfMPg+NccmBqixD7b6QDjynCy8SIwIVbb\n"
"0615XoFYC20UgDX1b10d65pHBf9ZjQCxQNqQmJYaumxtf4z1s4DfjGRzNpZ5eWl0\n"
"6r/4ngGPoJVpjemEuunl1Ig423g7mNA2eymw0lIYkN5SQwCuaifIFJ6GlazhgDEw\n"
"fpolu4usBCOmmQDo8dIm7A9+O4orkjgTHY+GzYZSR+Y0fFukAj6KYXwidlNalFMz\n"
"hriSqHKvoflShx8xpfywgVcvzfTO3PYkz6fiNJBonf6q8amaEsybwMbDqKWwIX7e\n"
"SPY=\n"
"-----END CERTIFICATE-----\n";


// 安全拷贝函数（防止溢出）
static void safe_strcpy(char *dest, const char *src, size_t max_len) {
    strncpy(dest, src, max_len - 1);
    dest[max_len - 1] = '\0';
}

// 安全获取JSON字符串字段
static void get_json_str_safe(cJSON *parent, const char *key,
                            char *output, size_t output_size,
                            const char *default_val) {
    cJSON *item = cJSON_GetObjectItemCaseSensitive(parent, key);
    if (item && cJSON_IsString(item)) {
        safe_strcpy(output, item->valuestring, output_size);
    } else if (item && cJSON_IsNumber(item)) {
        snprintf(output, output_size, "%d", item->valueint); // 数字转字符串
    } else {
        safe_strcpy(output, default_val, output_size);
    }
}

void parse_user_data(const char *json_str) {
    cJSON *root = cJSON_Parse(json_str);
    if (!root) return;

    cJSON *data = cJSON_GetObjectItemCaseSensitive(root, "data");
    if (data) {
        // 安全获取所有字段（数字自动转为字符串）
        get_json_str_safe(data, "mid", current_user.mid,
                         sizeof(current_user.mid), "0");
        get_json_str_safe(data, "following", current_user.following,
                         sizeof(current_user.following), "0");
        get_json_str_safe(data, "whisper", current_user.whisper,
                         sizeof(current_user.whisper), "0");
        get_json_str_safe(data, "black", current_user.black,
                         sizeof(current_user.black), "0");
        get_json_str_safe(data, "follower", current_user.follower,
                         sizeof(current_user.follower), "0");
    }
    print_user_info();
    g_GetBiliBili_Info_Flag = 1;
    cJSON_Delete(root);
}

// 打印用户信息
void print_user_info()
{
    printf("\n====== 用户数据 ======\n");
    printf("用户ID: %s\n", current_user.mid);
    printf("关注数: %s\n", current_user.following);
    printf("粉丝数: %s\n", current_user.follower);
    printf("黑名单: %s\n", current_user.black);
    printf("悄悄关注: %s\n", current_user.whisper);
}


static void http_event_handler(esp_http_client_event_t *evt)
{
    switch (evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGI(BILI_TAG,"HTTP_EVENT_ERROR\n");
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGI(BILI_TAG,"HTTP Response: %.*s\n", evt->data_len, (char *)evt->data);
            if (evt->data_len <= 0) break;

            char* buf = malloc(evt->data_len + 1);
            if (!buf) {
                ESP_LOGE(BILI_TAG, "Malloc failed");
                break;
            }

            memcpy(buf, evt->data, evt->data_len);
            buf[evt->data_len] = '\0';
            parse_user_data(buf);
            free(buf);
            break;
         case HTTP_EVENT_ON_FINISH:
            ESP_LOGI(BILI_TAG, "Request completed");
            break;
        default:
            break;
    }
}

// 通用API请求函数
static esp_err_t fetch_api(const char* url, int max_retries)
{
    int retry_count = 0;
    esp_err_t err = ESP_FAIL;

    esp_http_client_config_t config = {
        .url = url,
        .event_handler = http_event_handler,
        .cert_pem = bilibili_cert_pem,  // 设置 CA 证书
        .timeout_ms = 10000,  // 10秒超时
        .buffer_size = 2048,   // 适当缓冲区大小
        // .user_agent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36", // 伪装浏览器
    };

    for (int retry = 0; retry < max_retries; retry++)
    {
        ESP_LOGI(BILI_TAG, "Requesting %s (attempt %d/%d)", url, retry+1, max_retries);
        esp_http_client_handle_t client = esp_http_client_init(&config);

        err = esp_http_client_perform(client);

        int status_code = esp_http_client_get_status_code(client);
        ESP_LOGI(BILI_TAG, "HTTP Status: %d", status_code);

        esp_http_client_cleanup(client);

        if (err == ESP_OK && status_code == 200) {
            return ESP_OK;  // 成功则退出重试循环
        }

        ESP_LOGW(BILI_TAG, "Request failed: %s, status_code: %d",
                esp_err_to_name(err), status_code);

        esp_http_client_cleanup(client);

        // 指数退避
        int delay_ms = 1000 * (1 << retry);
        vTaskDelay(delay_ms / portTICK_PERIOD_MS);
    }
    return ESP_FAIL;
}


void fetch_bilibili_info_task(void *pvParameters)
{
    // 请求第一个API
    if (fetch_api(BILI_API_URL, 3) != ESP_OK) {
        ESP_LOGE(BILI_TAG, "Failed to fetch primary API");
    }
    else
    {
        ESP_LOGI(BILI_TAG, "Success to fetch primary API");
    }
    while (1)
    {
        vTaskDelay(1000);       //1S
    }




    /*B站功能未实现*/
    // 添加请求间隔（避免频率限制）
    // vTaskDelay(3000 / portTICK_PERIOD_MS);

    // // 请求第二个API
    // if (fetch_api(BILI_API1_URL, 3) != ESP_OK) {
    //     ESP_LOGE(BILI_TAG, "Failed to fetch secondary API");
    // }
}
//xTaskCreate(fetch_bilibili_info_task, "fetch_bilibili_info_task", 5120, NULL, 6, &xHttpTask);

