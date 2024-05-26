//ds18b20 do->PB0

#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "DS18B20.h"
#include "sys.h"
#include "HL.h"
#include "Key.h"
#include "DHT11.h"

int main()
{
	
	/*定义数*/
    int KeyNum;	
	float temp1;
	uint8_t status;
    uint8_t temp2, hum;
	Delay_ms(100);
	
	/*初始化*/
	A_Init();		
	Key_Init();
	OLED_Init();
	DS18B20_Init();
	DHT11_Init();
	OLED_Clear();

	while(1)
	{	
		
		 OLED_ShowString(4, 1, "DHT11NO");
			
	/*按键控制A1、A2电平反转*/	
		KeyNum = Key_GetNum();		
		if (KeyNum == 2)
		{
			A1_Turn();
			A2_Turn();			
		}
	/*温度传感器读取显示*/
		temp1=DS18B20_GetTemperture();
		if(temp1 == 0)
		{
		OLED_ShowString(1,1,"           ");
       OLED_ShowString(1,1,"CLOSE");
       }else if(temp1 > 1) 
		{ 
		OLED_ShowString(1, 1, "Tem:");
        OLED_ShowString(1, 7, ".");
		//OLED_ShowString(1,5,"+");       
        OLED_ShowNum(1,5,temp1,2);  
		OLED_ShowNum(1,8,(unsigned long)(temp1*10)%10,1);  
		Delay_ms(10);
		}
	
		
	/*温湿度传感器读取显示*/
        status = DHT11_Read_Data(&temp2, &hum);
        
        if(status == 1) // ??????
        {
			
            OLED_ShowString(2, 1, "Tem: ");
            OLED_ShowNum(2, 5, temp2, 2);
            OLED_ShowString(3, 1, "Hum: ");
            OLED_ShowNum(3, 5, hum, 2);
            Delay_ms(10);

        }
        else
        {
            OLED_ShowString(4, 1, "DHT11NO");
        }

        Delay_ms(1000);
		Delay_ms(1000);
	
	}
}
