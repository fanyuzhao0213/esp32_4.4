#include "QMI8658.h"
#include <string.h>

QMI8658C_Data QMI8658C_AGM = {0};
static const char *TAG = "QMI8658C"; // 定义日志标签
#include "QMI8658.h"

// I2C 初始化函数
esp_err_t i2c_master_init(void) {
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    // 配置 I2C 参数
    esp_err_t err = i2c_param_config(I2C_MASTER_NUM, &conf);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "I2C param config failed: %s", esp_err_to_name(err));
        return err;  // 返回错误
    }

    // 安装 I2C 驱动
    err = i2c_driver_install(I2C_MASTER_NUM, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "I2C driver installation failed: %s", esp_err_to_name(err));
        return err;  // 返回错误
    }

    ESP_LOGI(TAG, "I2C master initialized successfully");  // 成功初始化信息
    return ESP_OK;  // 返回成功
}



void QMI8658C_WriteReg(uint8_t reg_add, uint8_t reg_dat) {
    // 设置 I2C 设备地址和要写入的数据
    uint8_t data[2] = {reg_add, reg_dat};
    i2c_master_write_to_device(I2C_MASTER_NUM, QMI8658C_I2C_Add, data, sizeof(data), 1000 / portTICK_PERIOD_MS);
}

uint8_t QMI8658C_ReadData(uint8_t reg_add) {
    uint8_t data;
    // 写入寄存器地址以便读取数据
    i2c_master_write_to_device(I2C_MASTER_NUM, QMI8658C_I2C_Add, &reg_add, 1, 1000 / portTICK_PERIOD_MS);
    // 读取数据
    i2c_master_read_from_device(I2C_MASTER_NUM, QMI8658C_I2C_Add, &data, 1, 1000 / portTICK_PERIOD_MS);
    return data;
}


/**********************************************************************************************************
*	函 数 名: QMI8658C_Reg_Init
*	功能说明: QMI8658C初始化寄存器
*	形	  参: 无
*	返 回 值: 1:成功	0:失败
**********************************************************************************************************/
uint8_t QMI8658C_Reg_Init(void)
{
	if(QMI8658C_ReadDev_Identifier() == 1 && QMI8658C_ReadDev_RevisionID() == 1)
	{
		QMI8658C_Set_CTRL1();
		QMI8658C_Set_CTRL7();
		QMI8658C_Set_CTRL2();
		QMI8658C_Set_CTRL3();
		QMI8658C_Set_CTRL4();
		QMI8658C_Set_CTRL5();
		return 1;
	}
	return 0;
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_ReadDev_Identifier
*	功能说明: 读取Device identifier并判断是否正确
*	形	  参: 无
*	返 回 值: Device identifier是否正确
**********************************************************************************************************/

uint8_t QMI8658C_ReadDev_Identifier(void)
{
    uint8_t device_id = QMI8658C_ReadData(QMI8658C_RegAdd_WHO_AM_I); // 读取设备标识符
    ESP_LOGI(TAG, "Read Device Identifier: 0x%02X", device_id); // 打印读取到的设备标识符

    if (device_id == 0x05) { // 设备标识符 0x05 | 0xA0
        ESP_LOGI(TAG, "Device identifier matched: 0x05"); // 设备匹配成功的日志
        return 1;
    } else {
        ESP_LOGE(TAG, "Device identifier mismatch: expected 0x05, got 0x%02X", device_id); // 设备不匹配的日志
        return 0;
    }
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_ReadDev_RevisionID
*	功能说明: 读取Revision ID并判断是否正确
*	形	  参: 无
*	返 回 值: Revision ID是否正确
**********************************************************************************************************/
uint8_t QMI8658C_ReadDev_RevisionID(void)
{
    uint8_t revision_id = QMI8658C_ReadData(QMI8658C_RegAdd_REVISION_ID);  // 读取修订 ID
    ESP_LOGI(TAG, "读取的修订 ID: 0x%02X", revision_id);  // 打印读取的修订 ID

    if (revision_id == 0x7B || revision_id == 0x7C) {  // 如果设备修订 ID 为 0x7B
        ESP_LOGI(TAG, "设备修订 ID 正确: 0x7B");  // 打印成功信息
        return 1;  // 返回 1 表示修订 ID 正确
    } else {
        ESP_LOGE(TAG, "设备修订 ID 错误: 期望 0x7B, 实际 0x%02X", revision_id);  // 打印错误信息
        return 0;  // 返回 0 表示修订 ID 错误
    }
}
/**********************************************************************************************************
*	函 数 名: QMI8658C_Set_CTRL1
*	功能说明: 配置CTRL1寄存器，控制电源状态，配置SPI通信
*	形	  参: 无
*	返 回 值: 无
**********************************************************************************************************/
void QMI8658C_Set_CTRL1(void)
{
	QMI8658C_WriteReg(QMI8658C_RegAdd_CTRL1, 0x41);
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_Set_CTRL2
*	功能说明: 配置CTRL2寄存器，配置加速度计满量程和输出数据速率;使能自测
*	形	  参: 无
*	返 回 值: 无
**********************************************************************************************************/
void QMI8658C_Set_CTRL2(void)
{
	QMI8658C_WriteReg(QMI8658C_RegAdd_CTRL2, 0x34);//加速度计自检，±16g，500Hz采样
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_Set_CTRL3
*	功能说明: 配置CTRL3寄存器，配置陀螺仪满量程和输出数据速率;使能自测
*	形	  参: 无
*	返 回 值: 无
**********************************************************************************************************/
void QMI8658C_Set_CTRL3(void)
{
	QMI8658C_WriteReg(QMI8658C_RegAdd_CTRL3, 0xD4);//陀螺仪自检，±128dps，500Hz采样
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_Set_CTRL4
*	功能说明: 配置CTRL4寄存器，配置磁力仪输出数据速率和选择设备
*	形	  参: 无
*	返 回 值: 无
**********************************************************************************************************/
void QMI8658C_Set_CTRL4(void)
{
	QMI8658C_WriteReg(QMI8658C_RegAdd_CTRL4, 0x00);//无磁力仪
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_Set_CTRL5
*	功能说明: 配置CTRL5寄存器，配置启用/禁用低通滤波
*	形	  参: 无
*	返 回 值: 无
**********************************************************************************************************/
void QMI8658C_Set_CTRL5(void)
{
	QMI8658C_WriteReg(QMI8658C_RegAdd_CTRL5, 0x00);//不使能陀螺仪、加速度计的低通滤波
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_Set_CTRL6
*	功能说明: 配置CTRL6寄存器
*	形	  参: 无
*	返 回 值: 无
**********************************************************************************************************/
void QMI8658C_Set_CTRL6(void)
{
	QMI8658C_WriteReg(QMI8658C_RegAdd_CTRL6, 0x00);
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_Set_CTRL7
*	功能说明: 配置CTRL7寄存器，启用/禁用姿态引擎，加速度计，分别使用sEN、aEN、gEN和mENbits的陀螺仪和磁强计
*	形	  参: 无
*	返 回 值: 无
**********************************************************************************************************/
void QMI8658C_Set_CTRL7(void)
{
	QMI8658C_WriteReg(QMI8658C_RegAdd_CTRL7, 0x07);//使能陀螺仪、加速度计
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_Soft_Reset
*	功能说明: 传感器软件复位
*	形	  参: 无
*	返 回 值: 无
**********************************************************************************************************/
void QMI8658C_Soft_Reset(void)
{
	QMI8658C_WriteReg(QMI8658C_RegAdd_RESET, 0x00);
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_Get_STATUS0
*	功能说明: 输出数据可用性。
*	形	  参: 无
*	返 回 值: 数据可用性
**********************************************************************************************************/
uint8_t QMI8658C_Get_STATUS0(void)
{
	return QMI8658C_ReadData(QMI8658C_RegAdd_STATUS0);
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_MagnetometerData_Check
*	功能说明: 检查磁力计数据是否可用
*	形	  参: 无
*	返 回 值: 1：新数据可用	0：上次读取后没有更新
**********************************************************************************************************/
uint8_t QMI8658C_MagnetometerData_Check(void)
{
	uint8_t status = 0;

	status = QMI8658C_Get_STATUS0();
	if(status >> 2 & 1)
		return 1;
	else
		return 0;
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_GyroscopeData_Check
*	功能说明: 检查陀螺仪数据是否可用
*	形	  参: 无
*	返 回 值: 1：新数据可用	0：上次读取后没有更新
**********************************************************************************************************/
uint8_t QMI8658C_GyroscopeData_Check(void)
{
	uint8_t status = 0;

	status = QMI8658C_Get_STATUS0();
	if(status >> 1 & 1)
		return 1;
	else
		return 0;
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_AccelerometerData_Check
*	功能说明: 检查加速度计数据是否可用
*	形	  参: 无
*	返 回 值: 1：新数据可用	0：上次读取后没有更新
**********************************************************************************************************/
uint8_t QMI8658C_AccelerometerData_Check(void)
{
	uint8_t status = 0;

	status = QMI8658C_Get_STATUS0();
	if(status >> 0 & 1)
		return 1;
	else
		return 0;
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_Get_AX
*	功能说明: 输出AX数据
*	形	  参: 无
*	返 回 值: 16位AX数据
**********************************************************************************************************/
short QMI8658C_Get_AX(void)
{
	short AX = 0;
	char AX_H = 0, AX_L = 0;

	AX_H = QMI8658C_ReadData(QMI8658C_RegAdd_AX_H);
	AX_L = QMI8658C_ReadData(QMI8658C_RegAdd_AX_L);
	AX = (AX_H << 8) | AX_L;
	return AX;
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_Get_AY
*	功能说明: 输出AY数据
*	形	  参: 无
*	返 回 值: 16位AY数据
**********************************************************************************************************/
short QMI8658C_Get_AY(void)
{
	short AY = 0;
	char AY_H = 0, AY_L = 0;

	AY_H = QMI8658C_ReadData(QMI8658C_RegAdd_AY_H);
	AY_L = QMI8658C_ReadData(QMI8658C_RegAdd_AY_L);
	AY = (AY_H << 8) | AY_L;
	return AY;
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_Get_AZ
*	功能说明: 输出AZ数据
*	形	  参: 无
*	返 回 值: 16位AZ数据
**********************************************************************************************************/
short QMI8658C_Get_AZ(void)
{
	short AZ = 0;
	char AZ_H = 0, AZ_L = 0;

	AZ_H = QMI8658C_ReadData(QMI8658C_RegAdd_AZ_H);
	AZ_L = QMI8658C_ReadData(QMI8658C_RegAdd_AZ_L);
	AZ = (AZ_H << 8) | AZ_L;
	return AZ;
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_Get_GX
*	功能说明: 输出GX数据
*	形	  参: 无
*	返 回 值: 16位GX数据
**********************************************************************************************************/
short QMI8658C_Get_GX(void)
{
	short GX = 0;
	char GX_H = 0, GX_L = 0;

	GX_H = QMI8658C_ReadData(QMI8658C_RegAdd_GX_H);
	GX_L = QMI8658C_ReadData(QMI8658C_RegAdd_GX_L);
	GX = (GX_H << 8) | GX_L;
	return GX;
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_Get_GY
*	功能说明: 输出GY数据
*	形	  参: 无
*	返 回 值: 16位GY数据
**********************************************************************************************************/
short QMI8658C_Get_GY(void)
{
	short GY = 0;
	char GY_H = 0, GY_L = 0;

	GY_H = QMI8658C_ReadData(QMI8658C_RegAdd_GY_H);
	GY_L = QMI8658C_ReadData(QMI8658C_RegAdd_GY_L);
	GY = (GY_H << 8) | GY_L;
	return GY;
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_Get_GZ
*	功能说明: 输出GZ数据
*	形	  参: 无
*	返 回 值: 16位GZ数据
**********************************************************************************************************/
short QMI8658C_Get_GZ(void)
{
	short GZ = 0;
	char GZ_H = 0, GZ_L = 0;

	GZ_H = QMI8658C_ReadData(QMI8658C_RegAdd_GZ_H);
	GZ_L = QMI8658C_ReadData(QMI8658C_RegAdd_GZ_L);
	GZ = (GZ_H << 8) | GZ_L;
	return GZ;
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_Get_MX
*	功能说明: 输出MX数据
*	形	  参: 无
*	返 回 值: 16位MX数据
**********************************************************************************************************/
short QMI8658C_Get_MX(void)
{
	short MX = 0;
	char MX_H = 0, MX_L = 0;

	MX_H = QMI8658C_ReadData(QMI8658C_RegAdd_MX_H);
	MX_L = QMI8658C_ReadData(QMI8658C_RegAdd_MX_L);
	MX = (MX_H << 8) | MX_L;
	return MX;
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_Get_MY
*	功能说明: 输出MY数据
*	形	  参: 无
*	返 回 值: 16位MY数据
**********************************************************************************************************/
short QMI8658C_Get_MY(void)
{
	short MY = 0;
	char MY_H = 0, MY_L = 0;

	MY_H = QMI8658C_ReadData(QMI8658C_RegAdd_MY_H);
	MY_L = QMI8658C_ReadData(QMI8658C_RegAdd_MY_L);
	MY = (MY_H << 8) | MY_L;
	return MY;
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_Get_MZ
*	功能说明: 输出MZ数据
*	形	  参: 无
*	返 回 值: 16位MZ数据
**********************************************************************************************************/
short QMI8658C_Get_MZ(void)
{
	short MZ = 0;
	char MZ_H = 0, MZ_L = 0;

	MZ_H = QMI8658C_ReadData(QMI8658C_RegAdd_MZ_H);
	MZ_L = QMI8658C_ReadData(QMI8658C_RegAdd_MZ_L);
	MZ = (MZ_H << 8) | MZ_L;
	return MZ;
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_Get_Temperature
*	功能说明: 输出传感器温度
*	形	  参: 无
*	返 回 值: 16位传感器温度
**********************************************************************************************************/
short QMI8658C_Get_Temperature(void)
{
	short Temp = 0;
	char Temp_H = 0, Temp_L = 0;

	Temp_H = QMI8658C_ReadData(QMI8658C_RegAdd_TEMP_H);
	Temp_L = QMI8658C_ReadData(QMI8658C_RegAdd_TEMP_L);
	Temp = (Temp_H << 8) | Temp_L;
	return Temp;
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_Get_MagnetometerData
*	功能说明: 读取磁力计数据
*	形	  参: MagnetometerData:输出磁力计的X、Y、Z数据
*	返 回 值: 0：当前数据未更新 1：当前数据可用
**********************************************************************************************************/
uint8_t QMI8658C_Get_MagnetometerData(void)
{
	if(QMI8658C_MagnetometerData_Check() == 1)//判断磁力计数据是否可用
	{
		QMI8658C_AGM.MX = QMI8658C_Get_MX();
		QMI8658C_AGM.MY = QMI8658C_Get_MY();
		QMI8658C_AGM.MZ = QMI8658C_Get_MZ();
		return 1;
	}
	return 0;
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_Get_GyroscopeData
*	功能说明: 读取陀螺仪数据
*	形	  参: GyroscopeData:输出陀螺仪的X、Y、Z数据
*	返 回 值: 0：当前数据未更新 1：当前数据可用
**********************************************************************************************************/
uint8_t QMI8658C_Get_GyroscopeData(void)
{
	if(QMI8658C_GyroscopeData_Check() == 1)//判断陀螺仪数据是否可用
	{
		QMI8658C_AGM.GX = QMI8658C_Get_GX();
		QMI8658C_AGM.GY = QMI8658C_Get_GY();
		QMI8658C_AGM.GZ = QMI8658C_Get_GZ();
		return 1;
	}
	return 0;
}

/**********************************************************************************************************
*	函 数 名: QMI8658C_Get_AccelerometerData
*	功能说明: 读取加速度计数据
*	形	  参: AccelerometerData:输出加速度计的X、Y、Z数据
*	返 回 值: 0：当前数据未更新 1：当前数据可用
**********************************************************************************************************/
uint8_t QMI8658C_Get_AccelerometerData(void)
{
	if(QMI8658C_AccelerometerData_Check() == 1)//判断加速度计数据是否可用
	{
		QMI8658C_AGM.AX = QMI8658C_Get_AX();
		QMI8658C_AGM.AY = QMI8658C_Get_AY();
		QMI8658C_AGM.AZ = QMI8658C_Get_AZ();
		return 1;
	}
	return 0;
}

