/*******************************************************************************
 * @name    : ��ʱ����ͷ�ļ�
 * @author  : ������
 * @web     : WWW.UCORTEX.COM
 * @version : V1.0
 * @date    : 2014-04-03
 * @MDK     : KEIL MDK4.72a & KEL MDK 5.10
 * @brief   : �����΢�����ʱ���������ʵ�����̵���
 * ---------------------------------------------------------------------------- 
 * @copyright
 *
 * UCORTEX��Ȩ���У�Υ�߱ؾ�������Դ�������Ҳο���ּ�ڽ���ѧϰ�ͽ�ʡ����ʱ�䣬
 * ������Ϊ�ο����ļ����ݣ��������Ĳ�Ʒֱ�ӻ����ܵ��ƻ������漰���������⣬��
 * �߲��е��κ����Ρ�����ʹ�ù����з��ֵ����⣬���������WWW.UCORTEX.COM��վ��
 * �������ǣ����ǻ�ǳ���л�����������⼰ʱ�о����������ơ����̵İ汾���£�����
 * ���ر�֪ͨ���������е�WWW.UCORTEX.COM�������°汾��лл��
 * ��������������UCORTEX������һ�����͵�Ȩ����
 * ----------------------------------------------------------------------------
 * @description
 * LED -> PB12
 * KEY -> PA0
 *
 *-----------------------------------------------------------------------------
 * @history
 * ----------------------------------------------------------------------------
 * ����ʱ�䣺2014-04-03    �����ˣ�������
 * �汾��¼��V1.0
 * �������ݣ��½�
 * ----------------------------------------------------------------------------
 *
 ******************************************************************************/

#ifndef __DELAY_H
#define __DELAY_H
#include "stm32f10x.h"

#define SYSTICK_PERIOD                1      //1ms

void Delay_Init(void);	//SysTick��ʱ��ʼ��
void delay_ms(uint16_t xms);//������ʱ����
//void delay_us(uint32_t xus);//΢����ʱ����
extern void SysTickInit(void);
extern uint32_t os_get_time(void);

#define asm            __asm
#define delay_300ns()     do {asm("nop");asm("nop");asm("nop");asm("nop");\
                              asm("nop");asm("nop");asm("nop");asm("nop");\
                              asm("nop");asm("nop");asm("nop");asm("nop");\
                              asm("nop");asm("nop");asm("nop");asm("nop");\
                              asm("nop");asm("nop");asm("nop");asm("nop");\
                              asm("nop");asm("nop");} while(1==0)
                                
#define delay_600ns()     do { asm("nop");asm("nop");asm("nop");asm("nop");\
                               asm("nop");asm("nop");asm("nop");asm("nop");\
                               asm("nop");asm("nop");asm("nop");asm("nop");\
                               asm("nop");asm("nop");asm("nop");asm("nop");\
                               asm("nop");asm("nop");asm("nop");asm("nop");\
                               asm("nop");asm("nop");asm("nop");asm("nop");\
                               asm("nop");asm("nop");asm("nop");asm("nop");\
                               asm("nop");asm("nop");asm("nop");asm("nop");\
                               asm("nop");asm("nop");asm("nop");asm("nop");\
                               asm("nop");asm("nop");asm("nop");asm("nop");\
                               asm("nop");asm("nop");asm("nop");asm("nop");\
                               asm("nop");asm("nop");} while(1==0)
                                
#define delay_us(n)       do { for(uint32_t i=0;i<n;i++){delay_300ns();delay_600ns();}\
                                } while(0==1)

#endif

/********************* (C) COPYRIGHT 2014 WWW.UCORTEX.COM **********END OF FILE**********/
