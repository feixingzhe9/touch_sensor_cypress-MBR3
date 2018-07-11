
#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "oled.h"
#include "exti.h"
#include "adc.h"
#include "joystick.h"
#include "timer.h"
#include "rtc.h"
#include "standby.h"
#include "dma.h"
#include "beep.h"
#include "stm32_eeprom.h"
#include "spi.h"
#include "nrf24l01.h"
#include "i2c.h"
#include "mpu6050.h"
#include "can_protocol.h"
#include "can.h"

/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
//#include <project.h>
#include "configuration.h"
#include "MBR3.h"

//CY_ISR_PROTO(MBR3_ISR_Handler);
void LogTouchInfo(void);
uint8_t MBR3Flag=0;
uint8_t Button[2];

int main()
{
//    CyGlobalIntEnable;      /* Enable global interrupts */
        SysTickInit();
		COM_Init(COM1,115200);
		I2C_Init();
//    I2C_Start();

//    isr_HostIntPin_StartEx(MBR3_ISR_Handler);
    
    configurationMBR3();
    TouchPlatformInit();
    CanInit();

    while(1)
    {

		//LogTouchInfo();		
        ReadButtonStatus(Button);
				
//				printf("button[0]=%d,button[1]=%d\r\n",Button[0],Button[1]);
        can_protocol_period();
        CalSlideState();
        delay_ms(50);
    }
}


#define LOG_PERIOD          100/SYSTICK_PERIOD
static uint32_t log_start_time = 0;
extern uint8_t slider_value[2];
void LogTouchInfo(void)
{
    if(os_get_time() - log_start_time >= LOG_PERIOD)
    {
        log_start_time = os_get_time();
        printf("SLIDER_1=%d,SLIDER_2=%d,button[0]=%d,button[1]=%d\r\n",slider_value[0],slider_value[1],Button[0],Button[1]);
    }
}

///**
//  * @brief  Main program.
//  * @param  None
//  * @retval None
//  */
//int main(void)
//{
//	uint32_t t=0;
//	uint8_t data = 0;
//	uint8_t key = 0;
//	uint16_t speed = 100;

//	LED_Init();				//LED IO初始化
//	Delay_Init();			//延时初始化
//	COM_Init(COM1, 115200);//串口1初始化
//	OLED_Init();			//初始化OLED
//	ADC_Initialize();	//ADC初始化
//	JoyStick_Init();	//摇杆按键(JoyStick)初始化
//	BEEP_Init();			//蜂鸣器初始化
//  EE_Init();				//FLASH 模拟EEPROM初始化
//	I2C_Init();				//初始化I2C接口
//	
//	//显示提示信息
//	OLED_ShowString(0,0,"WWW.UCORTEX.COM");	
//	OLED_ShowString(0,16,"SPEED: 100 Kbps");
//	OLED_ShowString(0,32,"DATA = 0x  ");
//	OLED_ShowString(0,48,"RESULT: ");
//	OLED_Refresh_Gram();
// 	
//	while(1)
//	{
//		key = JoyStick_Scan(0);
//		if(key == KEY_CENTER)//进行一次I2C读写
//		{
//			data = MPU6050_getDeviceID();
//			OLED_ShowxNum(72,32,data,2,16,0x13);
//			if(data == 0x68)
//				OLED_ShowString(64,48,"SUCCESS");
//			else
//				OLED_ShowString(64,48,"ERROR  ");
//		}
//		else if(key == KEY_UP)//I2C访问速度增加10Kbps
//		{
//			speed+=10;//速度加10Kbps
//			if(speed > 400) speed = 400;//I2C最高访问速度是400Kbps
//			I2C_SetSpeed(speed); //设置I2C速度
//			OLED_ShowNum(56,16,speed,3,16);//显示当前设置的I2C速度
//		}
//		else if(key == KEY_DOWN)//I2C访问速度减少10Kbps
//		{
//			if(speed > 10) speed -= 10;//速度减10Kbps
//			else speed = 10;
//			I2C_SetSpeed(speed); //设置I2C速度
//			OLED_ShowNum(56,16,speed,3,16);//显示当前设置的I2C速度
//		}
//		
//		OLED_Refresh_Gram();
//		delay_ms(50);
//		if(t++>5)
//		{
//			t=0;
//			LED=!LED;//工作状态指示
//		}
//	}
//}

