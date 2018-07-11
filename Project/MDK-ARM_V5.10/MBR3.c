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
#include "MBR3.h"
#include "configuration.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/*******************************************
Function: ????????
SlaverAddr:????
Registers_Addr:?????
*Readbuf:??????
ReadSize:????
********************************************/

uint8_t MBR3_Read(uint8_t SlaverAddr,uint8_t Registers_Addr,uint8_t *Readbuf,uint8_t ReadSize)
{
	uint32_t errStatus=1;
  uint8_t i; 
  uint8_t read_count;
  read_count=ReadSize;

	do{
			I2C_Start();													//Master发送起始信号
			errStatus = I2C_WriteStart(SlaverAddr<<1|0x00);
		} //0x00???
  while(errStatus!=I2C_SUCCESS);

	I2C_WriteStart(Registers_Addr);   //??????
	I2C_Stop();														//发送停止信号
		
	do{
			I2C_Start();													//Master发送起始信号
			errStatus = I2C_WriteStart(SlaverAddr<<1|0x01);
		} //0x00???
  while(errStatus!=I2C_SUCCESS);

  for (i = 0; i < read_count; ++i)
	{
		if(i<read_count-1)/* code */
		{
			Readbuf[i]=I2C_Read_Byte(0x01);  //0x00??????,????ACK
		}
		else
		{
			Readbuf[i]=I2C_Read_Byte(0x00);  //??????NACK
		}
	}

    I2C_Stop();  //?????

    return 1;   //????
}

/*******************************************
Function: ????????
SlaverAddr:????
Registers_Addr:?????
*Writebuf:??????
WriteSize:????
********************************************/
uint8_t MBR3_Write(uint8_t SlaverAddr,uint8_t Registers_Addr,uint8_t *Writebuf,uint8_t WriteSize)
{
	uint32_t errStatus;
  	uint8_t i; 
//    uint8_t read_count;
//    read_count=WriteSize;
    do{
				I2C_Start();													//Master发送起始信号
				errStatus = I2C_WriteStart(SlaverAddr<<1|0x00);
			} //0x00???
    while(errStatus!=I2C_SUCCESS);
		
    I2C_WriteStart(Registers_Addr);   //??????

    for (i = 0; i < WriteSize; ++i)
    {
    	errStatus=I2C_WriteStart(Writebuf[i]);/* code */
    	if (errStatus != I2C_SUCCESS)
    	{
				I2C_Stop();
    		return 0;
    	}
    }

		I2C_Stop();														//发送停止信号
    return 1;
}
/**************************************************
Function:?????????
***************************************************/
uint8_t MBR3_WriteRegister(uint8_t Registers_Addr,uint8_t Data)
{
    uint32_t errStatus;
	  
		do{
				I2C_Start();													//Master发送起始信号
				errStatus = I2C_WriteStart(SLAVE_ADDR<<1|0x00);
			} //0x00???
    while(errStatus!=I2C_SUCCESS);

    I2C_WriteStart(Registers_Addr);   //??????

    errStatus=I2C_WriteStart(Data);/* code */
    if(I2C_SUCCESS != errStatus)
    {
			I2C_Stop();
      return 0;
    }
    I2C_Stop();														//发送停止信号
    return 1;
}

/***********************************************
?MBR3????
************************************************/
uint8_t configurationMBR3(void)
{
    uint8_t MBR3State;
    uint8_t CRCState;
    do{
        MBR3State=MBR3_Write(SLAVE_ADDR,REGMAP_ORIGIN,configData,TOTAL_CONFIG_REG_COUNT);  //??128????
    }while(MBR3State!=1);

    MBR3_WriteRegister(CTRL_CMD,SAVE_CHECK_CRC);           //??????

    delay_ms(220);

    do{
        MBR3State=MBR3_Read(SLAVE_ADDR,CTRL_CMD_ERR,&CRCState,1);  //CRC??
    }while(MBR3State!=1);

    if (CRCState!=0x00)
    {
        return 0;
    }

    MBR3_WriteRegister(CTRL_CMD,SW_RESET);   //????
    
    delay_ms(220);

    return 1;
}
/***********************************************
????
************************************************/
void ReadButtonStatus(uint8_t*ButtonStatus)
{
    uint8_t MBR3State;
    do{ 
        MBR3State=MBR3_Read(SLAVE_ADDR,BUTTON_STATUS,ButtonStatus,2);
    }while(MBR3State!=1);
    
}

/***********************************************
????
************************************************/
void ReadSlider1Value(uint8_t* slider_value)
{
    uint8_t MBR3State;
    do{ 
        MBR3State=MBR3_Read(SLAVE_ADDR,0xb0,slider_value,1);
    }while(MBR3State!=1);
    
}

/***********************************************
????
************************************************/
void ReadSlider2Value(uint8_t* slider_value)
{
    uint8_t MBR3State;
    do{ 
        MBR3State=MBR3_Read(SLAVE_ADDR,0xb2,slider_value,1);
    }while(MBR3State!=1);
    
}

slider_t slider_state_ram[SLIDER_NUM];
slider_t *slider_state[SLIDER_NUM];
uint8_t slider_value[2];
void TouchPlatformInit(void)
{
    for(uint8_t i = 0; i < SLIDER_NUM; i++)
    {
        slider_state[i] = &slider_state_ram[i];
        memset(slider_state[i], 0, sizeof(slider_t));
    }
}

#define NO_TOUCHING         0
#define TOUCHING            1
#define SLIDING             2
#define RELEASE             3

#define DEBAUNCE_VALUE      5

#define NO_TOUCHING_VALUE   255
#define TOUCHING_VALUE_MAX  200

void CalSlideState(void)
{
    static uint8_t state[SLIDER_NUM] = {0};
    
    ReadSlider1Value(&slider_value[0]);
    ReadSlider2Value(&slider_value[1]);
    
    for(uint8_t i = 0; i < SLIDER_NUM; i++)
    {
        
//        if(slider_value[i] == NO_TOUCHING_VALUE)
//        {
//            state[i] = NO_TOUCHING;
//            slider_state[i]->is_touching = 0;
//        }
        
        switch(state[i])
        {
            case NO_TOUCHING:
                if(slider_value[i] < TOUCHING_VALUE_MAX)
                {
                    state[i] = TOUCHING;
                    slider_state[i]->start_time = os_get_time();
                    slider_state[i]->value_start = slider_value[i];
                    slider_state[i]->is_touching = 1;
                    printf("start value:%d\r\n",slider_state[i]->value_start);
                }
                break;
            case TOUCHING:
                if(slider_value[i] == NO_TOUCHING_VALUE)
                {
                    state[i] = NO_TOUCHING;
                    break;
                }
                if((abs(slider_value[i] - slider_state[i]->value_start) > DEBAUNCE_VALUE) /*&& (slider_value[i] != NO_TOUCHING_VALUE)*/)
                {
                    state[i] = SLIDING;
                    printf("value %d --- ",slider_value[i]);
                    
                    if(slider_value[i] > slider_state[i]->value_start)
                    {
                        slider_state[i]->direction = SLIDE_UP;  
                        printf("%d:up\r\n",i);
                    }
                    else if(slider_value[i] < slider_state[i]->value_start)
                    {
                        slider_state[i]->direction = SLIDE_DOWN;
                        printf("%d:down\r\n",i);
                    }
                }
                break;
            case SLIDING:
                if(slider_value[i] == NO_TOUCHING_VALUE)
                {
                    state[i] = RELEASE;
                    printf("release\r\n");
                }
                
                break;
            case RELEASE:
                slider_state[i]->cnt++;
                state[i] = NO_TOUCHING;
                break;
            default:
                break;
        }
            
    }
}


/* [] END OF FILE */
