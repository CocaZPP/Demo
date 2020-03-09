
#ifndef __TMP112_H
#define __TMP112_H

#include "stm32l1xx.h"
#include "typedef.h"


#define I2C_GPIO    GPIOC
#define I2C_SCL     GPIO_Pin_7
#define I2C_SDA	    GPIO_Pin_8

#define TMP112_INT_GPIO    GPIOC
#define TMP112_INT_Pin     GPIO_Pin_0

/* Private define ------------------------------------------------------------*/
#define SCL_H         GPIO_SetBits(I2C_GPIO,I2C_SCL)
#define SCL_L         GPIO_ResetBits(I2C_GPIO,I2C_SCL) 

#define SDA_H      		GPIO_SetBits(I2C_GPIO,I2C_SDA)
#define SDA_L         GPIO_ResetBits(I2C_GPIO,I2C_SDA) 

//#define SDA2_read      I2C2_GPIO->IDR  & I2C2_SDA

#define TMP112_ADDRESS		0x90

//TMP112 Reg
#define TMP_REG_VALUE      0x00
#define TMP_REG_CONFIG      0x01
#define TMP_REG_LIMDOWN     0x02
#define TMP_REG_LIMUP       0x03
void Init_TMP112(void);
void TMP112_INIT(void);
uint16 ReadTmp112Value(void);
uint16 Tmp211_ReadReg(uint8 reg);
void Tmp211_WriteLimReg(uint8 reg,int16 dat16);
#endif

