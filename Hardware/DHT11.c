#include "DHT11.h"
#include "delay.h"

// DHT11 ?????
void DHT11_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  // ??GPIOB??

    GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       // ????
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DHT11_PORT, &GPIO_InitStructure);

    GPIO_SetBits(DHT11_PORT, DHT11_PIN);                   // ???????
}

// ??????????????
static void DHT11_Start(void)
{
    // ????18????????
    GPIO_ResetBits(DHT11_PORT, DHT11_PIN);
    Delay_ms(20);
    // ??20-40??
    GPIO_SetBits(DHT11_PORT, DHT11_PIN);
    Delay_us(30);
}

// ??DHT11??
static uint8_t DHT11_Check_Response(void)
{
    int Response = 0;
    Delay_us(40);
    if(!GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN))
    {
        Delay_us(80);
        if(GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN)) Response = 1;
        else Response = -1; // 55us???????????
    }
    while(GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN)); // ??DHT11??

    return Response;
}

// ?DHT11?????
static uint8_t DHT11_Read_Bit(void)
{
    uint8_t i = 0;
    while(GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN) == 0); // ???????
    Delay_us(40);
    if(GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN) == 0) i = 0;
    else i = 1;
    while(GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN)); // ???????

    return i;
}

// ?DHT11??????
static uint8_t DHT11_Read_Byte(void)
{
    uint8_t j;
	int dat = 0;
    for(j = 0; j < 8; j++)
    {
        dat <<= 1;
        dat |= DHT11_Read_Bit();
    }
    return dat;
}

// ???????
uint8_t DHT11_Read_Data(uint8_t *temperature, uint8_t *humidity)
{
    uint8_t RH_byte1, RH_byte2, T_byte1, T_byte2;
    uint8_t checksum;
    
    DHT11_Start();
    if(DHT11_Check_Response())
    {
        RH_byte1 = DHT11_Read_Byte();
        RH_byte2 = DHT11_Read_Byte();
        T_byte1 = DHT11_Read_Byte();
        T_byte2 = DHT11_Read_Byte();
        checksum = DHT11_Read_Byte();

        if(checksum == ((RH_byte1 + RH_byte2 + T_byte1 + T_byte2) & 0xFF))
        {
            *humidity = RH_byte1;
            *temperature = T_byte1;
            return 1; // ??????
        }
    }
    return 0; // ??????
}
