#ifndef __DHT11_H
#define __DHT11_H

#include "stm32f10x.h"

// ??DHT11??????GPIO?????
#define DHT11_PORT GPIOB
#define DHT11_PIN GPIO_Pin_1

void DHT11_Init(void);             // ???DHT11??
uint8_t DHT11_Read_Data(uint8_t *temperature, uint8_t *humidity); // ?????????

#endif
