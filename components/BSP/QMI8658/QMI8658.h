#ifndef __QMI8658_H
#define __QMI8658_H

#include "driver/i2c.h"
#include "esp_log.h"
#include <stdio.h>
#include <string.h>

typedef unsigned char	u8;
typedef unsigned short	u16;
typedef unsigned int	u32;

typedef unsigned char	uint8_t;
typedef unsigned short	uint16_t;
typedef unsigned int	uint32_t;

#define I2C_MASTER_SCL_IO           10        // I2C SCL 引脚
#define I2C_MASTER_SDA_IO           11        // I2C SDA 引脚
#define I2C_MASTER_NUM              1 // I2C 端口号
#define I2C_MASTER_FREQ_HZ          100000    // I2C 频率
#define I2C_MASTER_TX_BUF_DISABLE   0         // 禁用 TX 缓冲区
#define I2C_MASTER_RX_BUF_DISABLE   0         // 禁用 RX 缓冲区



#define QMI8658C_I2C_Add			0x6B
/*---------------------General Purpose Registers------------------*/
#define QMI8658C_RegAdd_WHO_AM_I	0x00	//Device Identifier
#define QMI8658C_RegAdd_REVISION_ID	0x01	//Device Revision ID
/*---------------------Setup and Control Registers------------------*/
#define QMI8658C_RegAdd_CTRL1		0x02	//SPI Interface and Sensor Enable
#define QMI8658C_RegAdd_CTRL2		0x03	//Accelerometer: Output Data Rate, Full Scale, Self Test
#define QMI8658C_RegAdd_CTRL3		0x04	//Gyroscope: Output Data Rate, Full Scale, Self Test
#define QMI8658C_RegAdd_CTRL4		0x05	//Magnetometer Settings: Output Data Rate, and Device Selection
#define QMI8658C_RegAdd_CTRL5		0x06	//Low pass filter setting.
#define QMI8658C_RegAdd_CTRL6		0x07	//AttitudeEngine? Settings: Output Data Rate, Motion on Demand
#define QMI8658C_RegAdd_CTRL7		0x08	//Enable Sensors
#define QMI8658C_RegAdd_CTRL8		0x09	//Reserved: Not Used
#define QMI8658C_RegAdd_CTRL9		0x0A	//Host Commands
/*---------------------Host Controlled Calibration Registers------------------*/
#define QMI8658C_RegAdd_CAL1_L		0x0B	//Calibration Register CAL1_L – lower 8 bits. CAL1_H – upper 8 bits.
#define QMI8658C_RegAdd_CAL1_H		0x0C
#define QMI8658C_RegAdd_CAL2_L		0x0D	//Calibration Register CAL2_L – lower 8 bits. CAL2_H – upper 8 bits.
#define QMI8658C_RegAdd_CAL2_H		0x0E
#define QMI8658C_RegAdd_CAL3_L		0x0F	//Calibration Register CAL3_L – lower 8 bits. CAL3_H – upper 8 bits.
#define QMI8658C_RegAdd_CAL3_H 		0x10
#define QMI8658C_RegAdd_CAL4_L		0x11	//Calibration Register CAL4_L – lower 8 bits. CAL4_H – upper 8 bits.
#define QMI8658C_RegAdd_CAL4_H		0x12
/*---------------------FIFO Registers------------------*/
#define QMI8658C_RegAdd_FIFO_WTM_TH		0x13	//FIFO watermark level, in ODRs
#define QMI8658C_RegAdd_FIFO_CTRL		0x14	//FIFO Setup
#define QMI8658C_RegAdd_FIFO_SMPL_CNT	0x15	//FIFO sample count LSBs
#define QMI8658C_RegAdd_FIFO_STATUS		0x16	//FIFO Status
#define QMI8658C_RegAdd_FIFO_DATA		0x17	//FIFO Data
/*---------------------Status Registers------------------*/
#define QMI8658C_RegAdd_I2CM_STATUS		0x2C	//I2C Master Status.
#define QMI8658C_RegAdd_STATUSINT		0x2D	//Sensor Data Availability with the Locking mechanism.
#define QMI8658C_RegAdd_STATUS0			0x2E	//Output Data Over Run and Data Availability.
#define QMI8658C_RegAdd_STATUS1			0x2F	//Miscellaneous Status: Wake on Motion, CmdDone(CTRL9 protocol bit).
/*---------------------Timestamp Register------------------*/
#define QMI8658C_RegAdd_TIMESTAMP_LOW		0x30	//Sample Time Stamp TIMESTAMP_LOW – lower 8 bits.
#define QMI8658C_RegAdd_TIMESTAMP_MID		0x31	//TIMESTAMP_MID – middle 8 bits.
#define QMI8658C_RegAdd_TIMESTAMP_HIGH		0x32	//TIMESTAMP_HIGH – upper 8 bits.
/*---------------------Data Output Registers------------------*/
#define QMI8658C_RegAdd_TEMP_L		0x33	//Temperature Output Data TEMP_L – lower 8 bits. TEMP_H – upper 8 bits
#define QMI8658C_RegAdd_TEMP_H		0x34
#define QMI8658C_RegAdd_AX_L		0x35	//X-axis Acceleration AX_L – lower 8 bits. AX_H – upper 8 bits
#define QMI8658C_RegAdd_AX_H		0x36
#define QMI8658C_RegAdd_AY_L		0x37	//Y-axis Acceleration AY_L – lower 8 bits. AY_H – upper 8 bits
#define QMI8658C_RegAdd_AY_H		0x38
#define QMI8658C_RegAdd_AZ_L		0x39	//Z-axis Acceleration AZ_L – lower 8 bits. AZ_H – upper 8 bits
#define QMI8658C_RegAdd_AZ_H		0x3A
#define QMI8658C_RegAdd_GX_L		0x3B	//X-axis Angular Rate GX_L – lower 8 bits. GX_H – upper 8 bits
#define QMI8658C_RegAdd_GX_H		0x3C
#define QMI8658C_RegAdd_GY_L		0x3D	//Y-axis Angular Rate GY_L – lower 8 bits. GY_H – upper 8 bits
#define QMI8658C_RegAdd_GY_H		0x3E
#define QMI8658C_RegAdd_GZ_L		0x3F	//Z-axis Angular Rate GZ_L – lower 8 bits. GZ_H – upper 8 bits
#define QMI8658C_RegAdd_GZ_H		0x40
#define QMI8658C_RegAdd_MX_L		0x41	//X-axis Magnetic Field MX_L – lower 8 bits. MX_H – upper 8 bits
#define QMI8658C_RegAdd_MX_H		0x42
#define QMI8658C_RegAdd_MY_L		0x43	//Y-axis Magnetic Field MY_L – lower 8 bits. MY_H – upper 8 bits
#define QMI8658C_RegAdd_MY_H		0x44
#define QMI8658C_RegAdd_MZ_L		0x45	//Z-axis Magnetic Field MZ_L – lower 8 bits. MZ_H – upper 8 bits
#define QMI8658C_RegAdd_MZ_H		0x46
#define QMI8658C_RegAdd_dQW_L		0x49	//Quaternion Increment dQW dQW_L – lower 8 bits. dQW_H – upper 8 bits
#define QMI8658C_RegAdd_dQW_H		0x4A
#define QMI8658C_RegAdd_dQX_L		0x4B	//Quaternion Increment dQX dQX_L – lower 8 bits. dQX_H – upper 8 bits
#define QMI8658C_RegAdd_dQX_H		0x4C
#define QMI8658C_RegAdd_dQY_L		0x4D	//Quaternion Increment dQY dQY_L – lower 8 bits. dQY_H – upper 8 bits
#define QMI8658C_RegAdd_dQY_H		0x4E
#define QMI8658C_RegAdd_dQZ_L		0x4F	//Quaternion Increment dQZ dQZ_L – lower 8 bits. dQZ_H – upper 8 bits
#define QMI8658C_RegAdd_dQZ_H		0x50
#define QMI8658C_RegAdd_dVX_L		0x51	//Velocity Increment along X-axis dVX_L – lower 8 bits. dVX_H – upper 8 bits
#define QMI8658C_RegAdd_dVX_H		0x52
#define QMI8658C_RegAdd_dVY_L		0x53	//Velocity Increment along Y-axis dVY_L – lower 8 bits. dVY_H – upper 8 bits
#define QMI8658C_RegAdd_dVY_H		0x54
#define QMI8658C_RegAdd_dVZ_L		0x55	//Velocity Increment along Z-axis dVZ_L – lower 8 bits. dVZ_H – upper 8 bits
#define QMI8658C_RegAdd_dVZ_H		0x56
#define QMI8658C_RegAdd_AE_REG1		0x57	//AttitudeEngine Register 1
#define QMI8658C_RegAdd_AE_REG2		0x58	//AttitudeEngine Register 2
/*---------------------Reset Register------------------*/
#define QMI8658C_RegAdd_RESET		0x60	//Soft Reset Register

typedef struct
{
	short AX;//加速度数据
	short AY;
	short AZ;
	short GX;//陀螺仪数据
	short GY;
	short GZ;
	short MX;//磁力计数据
	short MY;
	short MZ;
}QMI8658C_Data;//QMI8658C数据

extern QMI8658C_Data QMI8658C_AGM;

void QMI8658C_WriteReg(u8 reg_add, u8 reg_dat);
uint8_t QMI8658C_ReadData(u8 reg_add);
uint8_t QMI8658C_Reg_Init(void);  // QMI8658C 寄存器初始化
uint8_t QMI8658C_ReadDev_Identifier(void);  // 读取设备标识符
uint8_t QMI8658C_ReadDev_RevisionID(void);  // 读取设备修订 ID
void QMI8658C_Set_CTRL1(void);  // 设置控制寄存器 1
void QMI8658C_Set_CTRL2(void);  // 设置控制寄存器 2
void QMI8658C_Set_CTRL3(void);  // 设置控制寄存器 3
void QMI8658C_Set_CTRL4(void);  // 设置控制寄存器 4
void QMI8658C_Set_CTRL5(void);  // 设置控制寄存器 5
void QMI8658C_Set_CTRL6(void);  // 设置控制寄存器 6
void QMI8658C_Set_CTRL7(void);  // 设置控制寄存器 7
void QMI8658C_Soft_Reset(void);  // 软件复位设备
uint8_t QMI8658C_Get_STATUS0(void);  // 获取状态寄存器 0 的值
uint8_t QMI8658C_MagnetometerData_Check(void);  // 磁力计数据检查
uint8_t QMI8658C_GyroscopeData_Check(void);  // 陀螺仪数据检查
uint8_t QMI8658C_AccelerometerData_Check(void);  // 加速度计数据检查
short QMI8658C_Get_AX(void);  // 获取 X 轴加速度值
short QMI8658C_Get_AY(void);  // 获取 Y 轴加速度值
short QMI8658C_Get_AZ(void);  // 获取 Z 轴加速度值
short QMI8658C_Get_GX(void);  // 获取 X 轴陀螺仪值
short QMI8658C_Get_GY(void);  // 获取 Y 轴陀螺仪值
short QMI8658C_Get_GZ(void);  // 获取 Z 轴陀螺仪值
short QMI8658C_Get_MX(void);  // 获取 X 轴磁力计值
short QMI8658C_Get_MY(void);  // 获取 Y 轴磁力计值
short QMI8658C_Get_MZ(void);  // 获取 Z 轴磁力计值
short QMI8658C_Get_Temperature(void);  // 获取温度值
uint8_t QMI8658C_Get_MagnetometerData(void);  // 获取磁力计数据
uint8_t QMI8658C_Get_GyroscopeData(void);  // 获取陀螺仪数据
uint8_t QMI8658C_Get_AccelerometerData(void);  // 获取加速度计数据


esp_err_t i2c_master_init(void);
#endif
