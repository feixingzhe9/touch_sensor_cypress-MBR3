#if !defined(MBR3_H) 
#define MBR3_H 

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

#include "stm32f10x.h"
#include "i2c.h"
#include "delay.h"

#define SLIDER_NUM          1
typedef enum
{
    SLIDE_NONE = 0,
    SLIDE_UP,
    SLIDE_DOWN,   
} slider_directon_e;

typedef struct
{
    uint8_t     direction;
    uint8_t     value_start;
    uint8_t     value_end;
    uint8_t     value_previous;
    uint8_t     cnt;
    uint8_t     is_touching;
    uint32_t    start_time;
} slider_t;

uint8_t MBR3_Read(uint8_t SlaverAddr,uint8_t Registers_Addr,uint8_t *Readbuf,uint8_t ReadSize);

uint8_t MBR3_Write(uint8_t SlaverAddr,uint8_t Registers_Addr,uint8_t *Writebuf,uint8_t WriteSize);

uint8_t MBR3_WriteRegister(uint8_t Registers_Addr,uint8_t Data);

uint8_t MBR3_ReadRegister(uint8_t Registers_Addr);

uint8_t configurationMBR3(void);

void ReadButtonStatus(uint8_t *ButtonStatus);

void ReadSlider1Value(uint8_t* slider_value);

void ReadSlider2Value(uint8_t* slider_value);

void TouchPlatformInit(void);
void CalSlideState(void);

/* [] END OF FILE */

#endif
