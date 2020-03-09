#include "OPT3001.h"
#include <math.h>
static void I2C_delay(void)
{	
	volatile uint16 i = 5; //这里可以优化速度	，经测试最低到5还能写入
   
	while(i){
		i--; 
	} 
}

//初始化GPIO
void Init_OPT_GPIO(void)
{ 
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_InitStructure.GPIO_Pin = I2C_SDA|I2C_SCL;
		GPIO_Init(I2C_GPIO, &GPIO_InitStructure);
		SCL_H;SDA_H;
}
void OPT3001_INIT(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		EXTI_InitTypeDef   EXTI_InitStructure;
		NVIC_InitTypeDef   NVIC_InitStructure;
			//中断
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Pin = OPT_INT_Pin;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_Init(OPT_INT_GPIO,&GPIO_InitStructure);

		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource1);

		EXTI_InitStructure.EXTI_Line = EXTI_Line1;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);

		NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
}

//将GPIO 配置位输入模式
void OPT_GPIO_Set_Input(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_InitStructure.GPIO_Pin = I2C_SDA|I2C_SCL;
		GPIO_Init(I2C_GPIO, &GPIO_InitStructure);
}

static void I2C_Set_SDA_Output(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_InitStructure.GPIO_Pin = I2C_SDA;
		GPIO_Init(I2C_GPIO, &GPIO_InitStructure);
}

static void I2C_Set_SDA_Input(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_InitStructure.GPIO_Pin = I2C_SDA;
		GPIO_Init(I2C_GPIO, &GPIO_InitStructure);
}

static int SDA_read(void)
{
	if(GPIO_ReadInputDataBit(I2C_GPIO,I2C_SDA) == Bit_SET){
        return 1;
    }else{
        return 0;
    }
}

static void I2C_Start(void)
{
	//SCL_L;
	//I2C_delay();
	I2C_Set_SDA_Output();
	SDA_H;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SDA_L;
	I2C_delay();

	//SCL_L;
	//I2C_delay();
}

static void I2C_Stop(void)
{
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SDA_H;
	I2C_delay();
}

static ErrorStatus I2C_WaitAck(void) 	 //返回为:=1有ACK,=0无ACK
{
	uint8 errtime = 20;    
	ErrorStatus ret;

	ret = SUCCESS;
	SCL_L;
	I2C_delay();
	I2C_Set_SDA_Input();
	SCL_H;
	I2C_delay();
 	while(SDA_read() == SET)
 	{
		//Delay(8);// 1US
  		errtime--;
  		if(errtime==0){  			
			ret = ERROR;
			break;
  		}
		I2C_delay();
 	}
	SCL_L;
	I2C_delay();
	I2C_Set_SDA_Output();
	
	return ret;
}

static ErrorStatus I2C_SendByte(uint8 SendByte) //数据从高位到低位//
{
	ErrorStatus ret;
	uint8 i = 8;

	while(i--){
		SCL_L;
		I2C_delay();
		if(SendByte&0x80){
			SDA_H;  
		}else{
			SDA_L;   
		}
		SendByte<<=1;
		I2C_delay();
		SCL_H;
		I2C_delay();
	}
	//SCL_L;
	//I2C_delay();
	ret = I2C_WaitAck();
	I2C_delay();

	return ret;
}


static uint8 I2C_ReadByte(uint8 need_ack)
{
	uint8 i = 8;
	uint8 ReceiveByte = 0;
    volatile uint8 k;

       //I2C2_Set_SDA_Input();
	while(i--){
		ReceiveByte <<= 1;
		SCL_L;
		I2C_Set_SDA_Input();
		I2C_delay();
		SCL_H;
		I2C_delay();
        k = SDA_read();
		if(k){//SDA2_read == SET
			ReceiveByte |= 0x01;
		}
	}

	if(need_ack){
		SCL_L;
		I2C_delay();
		I2C_Set_SDA_Output();
		SDA_L;
		I2C_delay();
		SCL_H;
		I2C_delay();
	}else{
		SCL_L;
		I2C_delay();
		I2C_Set_SDA_Output();
		SDA_H;
		I2C_delay();
		SCL_H;
		I2C_delay();
	}

	return ReceiveByte;
}


//写入寄存器
void OPT3001_WriteReg(uint8 reg,int16 dat16)
{
	static uint8 data;
	I2C_Start();
	I2C_SendByte(OPT_ADDRESS);//设备地址--写操作

	I2C_SendByte(reg);//数据

	//data = dat16&0x00ff;
	data = (dat16&0xff00)>>8;
	I2C_SendByte(data);

	//data = (dat16&0x00ff)>>8;
	data = dat16&0x00ff;
	I2C_SendByte(data);
	
	I2C_Stop();
}

uint16 OPT3001_read(uint8 reg)
{
    uint8 reg_h;
	uint8 reg_l;
	uint16 data;

	I2C_Start();
	I2C_SendByte(OPT_ADDRESS);//设备地址--写操作

	I2C_SendByte(reg);
	I2C_Stop();

	I2C_Start();
	I2C_SendByte(OPT_ADDRESS | 0x01);//设备地址--读操作

	reg_h = I2C_ReadByte(1);
	reg_l = I2C_ReadByte(0);

	I2C_Stop();
	data = ((uint16)reg_h)*256 + reg_l;
	return data;
}
/*
功能：写上下限寄存器
输入：无
输出：无
*/
void Opt3001_WriteLimReg(uint8 reg,float dat16)
{
	uint16 VDatE = 0;
	uint16 VDatR = 0;
	uint16 dat = 0;
	dat = dat16*100;
	VDatE = (dat<<1)>>4;
	dat = (dat16*100)/VDatE;
	VDatR = log(dat)/log(2);
	dat16 = ((VDatR<<12)&0xf000)|(VDatE&0x0fff);
	OPT3001_WriteReg(reg, dat16);	
}

/*
功能：读取厂商ID
输入：无
输出：无
*/
uint16 opt3001_manufacturer_id(void)
{
    uint16 id = 0;
	id = OPT3001_read(OPT_REG_MFID);
    return id;
}
 
/*
功能：读取设备ID
输入：无
输出：无
*/
uint16 opt3001_device_id(void)
{
    uint16 id = 0;
	id = OPT3001_read(OPT_REG_ID);
    return id;
}
/*
功能：读取光照度上限
输入：无
输出：无
*/
uint16 opt3001_limUp(void)
{
    uint16 limUp = 0;
		limUp = OPT3001_read(OPT_REG_LIMUP);
		limUp =  (1<<((limUp & 0xF000)>>12))*(limUp & 0x0FFF);
    return limUp;
}
/*
功能：读取光照度上限
输入：无
输出：无
*/
uint16 opt3001_limDown(void)
{
    uint16 limDown = 0;
		limDown = OPT3001_read(OPT_REG_LIMDOWN);
		limDown =  (1<<((limDown & 0xF000)>>12))*(limDown & 0x0FFF);
    return limDown;
}
/*
功能：读取配置寄存器
输入：无
输出：无
备注：产生报警中断，读取配置寄存器，清空中断标志位
*/
uint16 opt3001_REG(void)
{
    uint16 reg = 0;
		reg = OPT3001_read(OPT_REG_CONFIG);
    return reg;
}
void Init_OPT3001(void)
{
	static uint16_t vCfg = 0;
	//12:15 RN  	- 配置测量光照的范围 见手册20页表9  当配置位1100传感器测量范围自动选择
	//11    CT  	- 测量时间配置 0- 100Ms  1-800Ms
	//10:9  M[1:0]	- 转换模式 00-关闭模式  01 - 单次转换  10、11 - 连续多次转换
	//8     OVF     - 测量光照超出设定的范围或最大测量值 溢出标志
	//7     CRF		- 转换就绪字段 1-转换完成
	//6     FH		- 转换的光照值 大于上限值 置位
	//5     FL		- 转换的光照值 小于下限值 置位
	//4     L		- 中断输出的两种模式  1-窗口模式 这种模式下高限置位和低限置位INT输出  0-滞后模式 高限置位INT输出 具体看手册
	//3     POL		- INT 中断被触发输出极性 0-拉低  1-拉高
	//2     ME 		- 掩码字段
	//0:1   FC		- 超出上限范围故障计数  如果超出次数 大于等于计数设定次数  INT输出中断
	vCfg = 0xC410;
	Init_OPT_GPIO();
	OPT3001_INIT();
	OPT3001_WriteReg(OPT_REG_CONFIG, vCfg);
}

/*
功能：读取传感器数据
输入：无
输出：无
*/
#define ARRY_SIZE 10
uint32_t opt3001_data[ARRY_SIZE];
uint8_t arry_wpr=0;
 
uint32 OPT3001_GetLuxValue(void)
{
    uint32 Result = 0;
	
		Result = OPT3001_read(OPT_REG_VALUE);
		Result =  (1<<((Result & 0xF000)>>12))*(Result & 0x0FFF);//获取的光照强度扩大一百倍
		
		return Result;
}




