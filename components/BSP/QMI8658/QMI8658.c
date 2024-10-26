#include "QMI8658.h"
#include <string.h>

static const char *TAG = "QMI8658C"; // 定义日志标签
t_sQMI8658 QMI8658; // 定义QMI8658结构体变量


// 创建步数结构体实例
t_step_counter step_counter = {
    .current_step_count = 0,
    .previous_step_count = 0,
    .total_step_count = 0,
    .timestamp = 0,
    .step_detected = false
};

/******************************************************************************/
/***************************  I2C ↓ *******************************************/
esp_err_t bsp_i2c_init(void)
{
    i2c_config_t i2c_conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = BSP_I2C_SDA,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = BSP_I2C_SCL,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = BSP_I2C_FREQ_HZ
    };
    i2c_param_config(BSP_I2C_NUM, &i2c_conf);

    return i2c_driver_install(BSP_I2C_NUM, i2c_conf.mode, 0, 0, 0);
}
/***************************  I2C ↑  *******************************************/
/*******************************************************************************/


/*******************************************************************************/
/***************************  姿态传感器 QMI8658 ↓   ****************************/

// 读取QMI8658寄存器的值
esp_err_t qmi8658_register_read(uint8_t reg_addr, uint8_t *data, size_t len)
{
    return i2c_master_write_read_device(BSP_I2C_NUM, QMI8658_SENSOR_ADDR,  &reg_addr, 1, data, len, 1000 / portTICK_PERIOD_MS);
}

// 给QMI8658的寄存器写值
esp_err_t qmi8658_register_write_byte(uint8_t reg_addr, uint8_t data)
{
    uint8_t write_buf[2] = {reg_addr, data};

    return i2c_master_write_to_device(BSP_I2C_NUM, QMI8658_SENSOR_ADDR, write_buf, sizeof(write_buf), 1000 / portTICK_PERIOD_MS);
}

// 初始化qmi8658
void qmi8658_init(void)
{
    uint8_t id = 0; // 芯片的ID号

    qmi8658_register_read(QMI8658_WHO_AM_I, &id ,1); // 读芯片的ID号
    while (id != 0x05)  // 判断读到的ID号是否是0x05
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // 延时1秒
        qmi8658_register_read(QMI8658_WHO_AM_I, &id ,1); // 读取ID号
    }
    ESP_LOGI(TAG, "QMI8658 OK!");  // 打印信息

    qmi8658_register_write_byte(QMI8658_RESET, 0xb0);  // 复位  
    vTaskDelay(10 / portTICK_PERIOD_MS);  // 延时10ms
    qmi8658_register_write_byte(QMI8658_CTRL1, 0x40); // CTRL1 设置地址自动增加
    qmi8658_register_write_byte(QMI8658_CTRL7, 0x03); // CTRL7 允许加速度和陀螺仪
    qmi8658_register_write_byte(QMI8658_CTRL2, 0x95); // CTRL2 设置ACC 4g 250Hz
    qmi8658_register_write_byte(QMI8658_CTRL3, 0xd5); // CTRL3 设置GRY 512dps 250Hz 
}

// 假设我们在读取步数后
void update_step_counter(uint32_t step_count) 
{
    step_counter.previous_step_count = step_counter.current_step_count; // 更新上次计数
    step_counter.current_step_count = step_count; // 更新当前步数
    step_counter.total_step_count += step_counter.current_step_count - step_counter.previous_step_count; // 累加总步数
    step_counter.timestamp = (uint32_t)esp_timer_get_time() / 1000; // 获取当前时间戳（毫秒）
    
    // 检测步数变化
    step_counter.step_detected = (step_counter.current_step_count != step_counter.previous_step_count);
}

//读取步数
void qmi_Read_StepCount(void)
{
	// 读取步数计数
	uint8_t step_count_low, step_count_mid, step_count_high;

	// 读取步数计数低位、中位和高位
	qmi8658_register_read(QMI8658_STEP_CNT_LOW, &step_count_low, 1);
	qmi8658_register_read(QMI8658_STEP_CNT_MIDL, &step_count_mid, 1);
	qmi8658_register_read(QMI8658_STEP_CNT_HIGH, &step_count_high, 1);

	// 计算总步数
	uint32_t step_count = (step_count_high << 16) | (step_count_mid << 8) | step_count_low;
    update_step_counter(step_count);
    // 打印步数信息
    ESP_LOGI(TAG, "Current Steps: %u, Total Steps: %u", step_counter.current_step_count, step_counter.total_step_count);

}



// 读取加速度和陀螺仪寄存器值
void qmi8658_Read_AccAndGry(t_sQMI8658 *p) 
{
    uint8_t status;
    int16_t buf[6] = {0};  // 存储传感器的原始数据

    // 读取状态寄存器以检查数据是否准备就绪
    qmi8658_register_read(QMI8658_STATUS0, &status, 1);
    if (status & 0x03) { // 检查加速度和陀螺仪数据是否可读
        // 读取加速度和陀螺仪数据
        qmi8658_register_read(QMI8658_AX_L, (uint8_t *)buf, 12);

        // 去除加速度的偏置
        p->acc_x = buf[0] - p->acc_offset[0];
        p->acc_y = buf[1] - p->acc_offset[1];
        p->acc_z = buf[2] - p->acc_offset[2];

        // 去除陀螺仪的偏置
        p->gyr_x = buf[3] - p->gyr_offset[0];
        p->gyr_y = buf[4] - p->gyr_offset[1];
        p->gyr_z = buf[5] - p->gyr_offset[2];

        // 使用 ESP-IDF 日志打印校准后的数据
        ESP_LOGI("QMI8658", "Acc - X: %d, Y: %d, Z: %d", p->acc_x, p->acc_y, p->acc_z);
        ESP_LOGI("QMI8658", "Gyr - X: %d, Y: %d, Z: %d", p->gyr_x, p->gyr_y, p->gyr_z);
    }
}

// 获取XYZ轴的倾角值
void qmi8658_fetch_angleFromAcc(t_sQMI8658 *p)
{
    float temp;

    qmi8658_Read_AccAndGry(p); // 读取加速度和陀螺仪的寄存器值

	// 使用 ESP-IDF 日志打印加速度数据
    ESP_LOGI(TAG, "Acceleration - X: %d, Y: %d, Z: %d", p->acc_x, p->acc_y, p->acc_z);

    // 根据寄存器值 计算倾角值 并把弧度转换成角度
    temp = (float)p->acc_x / sqrt( ((float)p->acc_y * (float)p->acc_y + (float)p->acc_z * (float)p->acc_z) );
    p->AngleX = atan(temp)*57.29578f; // 180/π=57.29578
    temp = (float)p->acc_y / sqrt( ((float)p->acc_x * (float)p->acc_x + (float)p->acc_z * (float)p->acc_z) );
    p->AngleY = atan(temp)*57.29578f; // 180/π=57.29578
    temp = sqrt( ((float)p->acc_x * (float)p->acc_x + (float)p->acc_y * (float)p->acc_y) ) / (float)p->acc_z;
    p->AngleZ = atan(temp)*57.29578f; // 180/π=57.29578
}

// 初始化传感器，采集100次数据，计算偏置
void qmi8658_calibrate(t_sQMI8658 *p) 
{
    int32_t acc_sum[3] = {0, 0, 0}; // 用于累加加速度
    int32_t gyr_sum[3] = {0, 0, 0}; // 用于累加陀螺仪
	ESP_LOGI(TAG, "QMI8658 SelfTest Start!");  // 打印信息
    // 采集100次数据
    for (int i = 0; i < 101; i++) {
		ESP_LOGI(TAG, "i:%d",i);  // 打印信息
        qmi8658_Read_AccAndGry(p);
		if(i != 0)
		{
			acc_sum[0] += p->acc_x;
			acc_sum[1] += p->acc_y;
			acc_sum[2] += p->acc_z;

			gyr_sum[0] += p->gyr_x;
			gyr_sum[1] += p->gyr_y;
			gyr_sum[2] += p->gyr_z;
		}
        vTaskDelay(10 / portTICK_PERIOD_MS); // 延迟10ms，避免过快采样
    }
	ESP_LOGI(TAG, "QMI8658 SelfTest End!");  // 打印信息
    // 计算平均值
    p->acc_offset[0] = acc_sum[0] / 100.0f;
    p->acc_offset[1] = acc_sum[1] / 100.0f;
    p->acc_offset[2] = acc_sum[2] / 100.0f;

    p->gyr_offset[0] = gyr_sum[0] / 100.0f;
    p->gyr_offset[1] = gyr_sum[1] / 100.0f;
    p->gyr_offset[2] = gyr_sum[2] / 100.0f;

    // 打印偏置值，确保初始化完成
    ESP_LOGI("QMI8658", "Acc offset - X: %.2f, Y: %.2f, Z: %.2f", p->acc_offset[0], p->acc_offset[1], p->acc_offset[2]);
    ESP_LOGI("QMI8658", "Gyr offset - X: %.2f, Y: %.2f, Z: %.2f", p->gyr_offset[0], p->gyr_offset[1], p->gyr_offset[2]);
}


// QMI8658_Task  采集六轴数据
void QMI8658_Task(void *arg)
{
	while(1)
	{
		qmi8658_fetch_angleFromAcc(&QMI8658);   // 获取XYZ轴的倾角
		// 输出XYZ轴的倾角
		ESP_LOGI(TAG, "angle_x = %.1f  angle_y = %.1f angle_z = %.1f",QMI8658.AngleX, QMI8658.AngleY, QMI8658.AngleZ);
		qmi_Read_StepCount();
		vTaskDelay(1000 / portTICK_PERIOD_MS);  // 延时1000ms
	}


}
/***************************  姿态传感器 QMI8658 ↑  ****************************/
/*******************************************************************************/
