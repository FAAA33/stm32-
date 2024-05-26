#ifndef _ds18b20_H
#define _ds18b20_H

#include "sys.h"



#define DS18B20_PORT 			GPIOB//设置引脚为gpiob口
#define DS18B20_PIN 			(GPIO_Pin_0)//设置具体哪个引脚
#define DS18B20_PORT_RCC		RCC_APB2Periph_GPIOG


										   
#define	DS18B20_DQ_OUT PBout(0) //上面改下面也需要改
#define	DS18B20_DQ_IN  PBin(0)  //上面改下面也需要改
   	
u8 DS18B20_Init(void);			
float DS18B20_GetTemperture(void);	
void DS18B20_Start(void);		
void DS18B20_Write_Byte(u8 dat);
u8 DS18B20_Read_Byte(void);		
u8 DS18B20_Read_Bit(void);		
void DS18B20_Reset(void);			   

#endif
