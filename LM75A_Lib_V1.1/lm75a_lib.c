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
#include "stm32f10x.h"                  // Device header.
#include "stm32f10x_i2c.h"
#include <stdio.h>
#include "lm75a_lib.h"  

uint32_t counterr=0,lm75_Address;
int dataBuffer[5];
float tempControl,lmvalue,temperature;

GPIO_InitTypeDef GPIOInitStructure;
I2C_InitTypeDef I2C_InitStructure;
		
		


void Lm75a_Config(uint8_t a0,uint8_t a1,uint8_t a2){
		if(a0==0&&a1==0&&a2==0){
	lm75_Address=0x90;
	}
	else if(a0==0&&a1==0&&a2==1){
	lm75_Address=0x98;
	}
	else if(a0==0&&a1==1&&a2==0){
	lm75_Address=0x94;
	}
	else if(a0==1&&a1==0&&a2==0){
	lm75_Address=0x92;
	}
	else if(a0==1&&a1==1&&a2==1){
	lm75_Address=0x9e;
	}
	else if(a0==1&&a1==1&&a2==0){
	lm75_Address=0x96;
	}
	else if(a0==0&&a1==1&&a2==1){
	lm75_Address=0x9c;
	}
	else if(a0==1&&a1==0&&a2==1){
	lm75_Address=0x9a;
	}
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIOInitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOInitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB, &GPIOInitStructure);

	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 100000;
	I2C_Init(I2C1, &I2C_InitStructure);
	I2C_Cmd(I2C1, ENABLE);

}


void i2c_readData(void){
		// Wait if busy
		while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
		// Generate START condition
		I2C_GenerateSTART(I2C1, ENABLE);
		while (!I2C_GetFlagStatus(I2C1, I2C_FLAG_SB));
		// Send device address for read
		I2C_Send7bitAddress(I2C1, lm75_Address, I2C_Direction_Receiver);
		while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
		// Read the first data
		while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
		dataBuffer[0] = I2C_ReceiveData(I2C1);
		// Disable ACK and generate stop condition
		I2C_AcknowledgeConfig(I2C1, DISABLE);
		I2C_GenerateSTOP(I2C1, ENABLE);
		// Read the second data
		while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
		dataBuffer[1] = I2C_ReceiveData(I2C1);
}


extern float get_temperature_c(void){
i2c_readData();
temperature = 0.5*((dataBuffer[0]<<8|dataBuffer[1])>>7);
return temperature;
}

extern float get_temperature_f(void){
i2c_readData();
lmvalue = get_temperature_c();
	
return ((lmvalue/5) *9) +32;

}



void systemClockEnable(void){
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock/1000);
}

void SysTick_Handler(void){

    if(counterr>0){
        counterr--;
    }
}

void Lm75a_Delay(uint64_t time){
        systemClockEnable();
    counterr=time;
    while(counterr);
}

