
#ifndef __OPT3001_H
#define __OPT3001_H
#include "stm32l1xx.h"
#include "typedef.h"

#define I2C_GPIO    GPIOC
#define I2C_SCL     GPIO_Pin_7
#define I2C_SDA	    GPIO_Pin_8

/* Private define ------------------------------------------------------------*/
#define SCL_H         GPIO_SetBits(I2C_GPIO,I2C_SCL)
#define SCL_L         GPIO_ResetBits(I2C_GPIO,I2C_SCL) 

#define SDA_H      		GPIO_SetBits(I2C_GPIO,I2C_SDA)
#define SDA_L         GPIO_ResetBits(I2C_GPIO,I2C_SDA) 
// IO Config
#define OPT_INT_GPIO    GPIOC
#define OPT_INT_Pin     GPIO_Pin_1

#define OPT_ADDRESS		0x88

//TMP112 Reg
#define OPT_REG_VALUE      0x00
#define OPT_REG_CONFIG      0x01
#define OPT_REG_LIMDOWN     0x02
#define OPT_REG_LIMUP       0x03

#define OPT_REG_MFID    0x7e    //0x5449
#define OPT_REG_ID      0x7f    //0x3001

void Init_OPT_GPIO(void);
void OPT_GPIO_Set_Input(void);
void Opt3001_WriteLimReg(uint8 reg,float dat16);
uint16 opt3001_manufacturer_id(void);
uint16 opt3001_device_id(void);
uint16 opt3001_limUp(void);
uint16 opt3001_limDown(void);
uint16 opt3001_REG(void);
void Init_OPT3001(void);
void OPT3001_INIT(void);
uint32 OPT3001_GetLuxValue(void);
#endif

