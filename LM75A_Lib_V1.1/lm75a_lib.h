/*******************************************************************************
|==============================================================================|
|   @author LIEK SOFTWARE TEAM                                                 |
|           Gorkem Aktas                                                       |
|           Fatih Yilmaz                                                       |
|           Emir Danisman                                                      |
|           Ozgur Karaaslan                                                    |
|   @date 9 January 2021            	                                       |
|   @documentedDate 28 March 2021                                              |
|   @version 1.1                                                               |
|   @brief  lm75a library                                                      |
|==============================================================================|
*******************************************************************************/
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_i2c.h"
#include <stdio.h>


void Lm75a_Config(uint8_t a0,uint8_t a1,uint8_t a2);
float get_temperature_c(void);
float get_temperature_f(void);
void i2c_readData(void);
void Lm75a_Delay(uint64_t time);


