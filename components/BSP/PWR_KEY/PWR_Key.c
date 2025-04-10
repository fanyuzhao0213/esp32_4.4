#include "PWR_Key.h"

// 电池供电状态（0: 未上电，1: 按键按下准备上电，2: 上电状态）
static uint8_t BAT_State = 0;

// 设备状态（1: 睡眠，2: 重启）
static uint8_t Device_State = 0;

// 长按时间计数
static uint16_t Long_Press = 0;

// 主循环，检测按键状态
void PWR_Loop(void)
{
  if(BAT_State)  // 如果 BAT 已经处于激活过程或上电状态
  {
    if(!gpio_get_level(PWR_KEY_Input_PIN))  // 按键被按下（低电平）
    {
      if(BAT_State == 2)  // 已经处于上电状态
      {
        Long_Press++;  // 按键持续按下，计时加一

        // 根据按键持续时间判断操作
        if(Long_Press >= Device_Sleep_Time)
        {
          if(Long_Press >= Device_Sleep_Time && Long_Press < Device_Restart_Time)
            Device_State = 1;   // 睡眠请求

          else if(Long_Press >= Device_Restart_Time && Long_Press < Device_Shutdown_Time)
            Device_State = 2;   // 重启请求

          else if(Long_Press >= Device_Shutdown_Time)
            Shutdown();        // 超过关机时间，执行关机
        }
      }
    }
    else  // 按键松开
    {
      if(BAT_State == 1)   // 如果此时是刚上电阶段
        BAT_State = 2;     // 状态变为稳定上电状态

      Long_Press = 0;      // 清除按下时间
    }
  }
}

// 睡眠（未实现）
void Fall_Asleep(void)
{

}

// 重启（未实现）
void Restart(void)
{

}

// 关机
void Shutdown(void)
{
  gpio_set_level(PWR_Control_PIN, false); // 关闭电池输出 MOS 管
  pwm_set_duty(0);                      // 关闭背光
}

// GPIO 配置函数
void configure_GPIO(int pin, gpio_mode_t Mode)
{
  gpio_reset_pin(pin);            // 复位该 GPIO
  gpio_set_direction(pin, Mode);  // 设置输入或输出模式
}

// 电源初始化函数
void PWR_Init(void)
{
  // 设置按键为输入
  configure_GPIO(PWR_KEY_Input_PIN, GPIO_MODE_INPUT);

  // 设置控制 MOS 管的输出引脚
  configure_GPIO(PWR_Control_PIN, GPIO_MODE_OUTPUT);

  // 初始关闭电池供电
  gpio_set_level(PWR_Control_PIN, false);

  vTaskDelay(100);  // 延时防抖或等待稳定

  // 如果按键被按下，说明用户希望上电
  if(!gpio_get_level(PWR_KEY_Input_PIN))
  {
    BAT_State = 1;                // 设置状态为准备上电
    gpio_set_level(PWR_Control_PIN, true);  // 打开电池输出
  }
}


