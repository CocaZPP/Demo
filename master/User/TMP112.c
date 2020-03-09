#include "TMP112.h"
#include <math.h>

static void I2C_delay(void)
{	
	volatile uint16 i = 5; //这里可以优化速度	，经测试最低到5还能写入
   
	while(i){
		i--; 
	} 
}

//初始化GPIO
void Init_TMP112_GPIO(void)
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
void TMP112_INIT(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		EXTI_InitTypeDef   EXTI_InitStructure;
		NVIC_InitTypeDef   NVIC_InitStructure;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Pin = TMP112_INT_Pin;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_Init(TMP112_INT_GPIO,&GPIO_InitStructure);

		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource0);

		EXTI_InitStructure.EXTI_Line = EXTI_Line0;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);

		NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
}
//将GPIO 配置位输入模式
void TMP112_GPIO_Set_Input(void)
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
	I2C_Set_SDA_Output();
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
	uint8 errtime = 50;    
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
void I2C_SendAck(uint8 status)
{
	SCL_L;
	I2C_delay();
	I2C_Set_SDA_Output();
	if(status == 0){
		SDA_L;
	}
	else{
		SDA_H;
	}
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
}
static ErrorStatus I2C_SendByte(uint8 SendByte) //数据从高位到低位//
{
	ErrorStatus ret;
	uint8 i = 8;
	I2C_Set_SDA_Output();
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
//I2C_SendAck(need_ack);
	if(need_ack){
		SCL_L;
		I2C_delay();
		I2C_Set_SDA_Output();
		SDA_L;
		I2C_delay();
		SCL_H;
		I2C_delay();
		SCL_L;
	}else{
		SCL_L;
		I2C_delay();
		I2C_Set_SDA_Output();
		SDA_H;
		I2C_delay();
		SCL_H;
		I2C_delay();
		SCL_L;
	}

	return ReceiveByte;
}


uint16 ReadTmp112Value(void)
{
	uint8 TempH ,TempL;
	int16 data = 0;

	I2C_Start();
	I2C_SendByte(TMP112_ADDRESS);//设备地址--写操作
	I2C_SendByte(0x00);//数据
	I2C_Stop();
	I2C_Start();
	I2C_SendByte((TMP112_ADDRESS | 0x01));//设备地址--读操作
	TempH=I2C_ReadByte(1);
	TempL=I2C_ReadByte(1);
	I2C_Stop();

	data |= TempH;
	data <<= 8;
	data |= TempL;
	data >>= 4;

	if(data > 2047)
	{
		data -= 4096;
	}
	
	data = (int16)((float)data * 0.0625);

	return data;
}

uint8 Tmp112_WriteConfig(void)
{
	I2C_Start();
	I2C_SendByte(TMP112_ADDRESS);//设备地址--写操作
	I2C_SendByte(TMP_REG_CONFIG);

	//配置寄存器的值 OS(0) R1(1) R0(1) F1(1) F0(0) POL(0) TM(1) SD(0)
	I2C_SendByte(0x72);
	//中断模式，通过读取温度寄存器，清空报警中断
	//比较器模式，当前温度达到预定范围，清空报警，否则一直保持中断
	//中断模式四次达预警值报警0.25Hz
	I2C_SendByte(0xa0);     // CR1(1) CR0(0) AL(1) EM(0)  0  0  0  0

	I2C_Stop();

	return 1;
}

//读取寄存器
uint16 Tmp211_ReadReg(uint8 reg)
{
	uint8 config_reg_h = 0;
	uint8 config_reg_l = 0;
	uint16 data = 0;

	I2C_Start();
	I2C_SendByte(TMP112_ADDRESS);//设备地址--写操作

	I2C_SendByte(reg);//数据
	I2C_Stop();

	I2C_Start();
	I2C_SendByte((TMP112_ADDRESS | 0x01));//设备地址--读操作

	config_reg_h = I2C_ReadByte(1);
	I2C_delay();
	config_reg_l = I2C_ReadByte(1);

	I2C_Stop();

	data |= config_reg_h;
	data <<= 8;
	data |= config_reg_l;
	data >>= 4;
	return data;
}

//写入寄存器
void Tmp211_WriteLimReg(uint8 reg,int16 dat16)
{
	static uint8 data = 0;
	static uint16 dat = 0;
	I2C_Start();
	I2C_SendByte(TMP112_ADDRESS);//设备地址--写操作

	I2C_SendByte(reg);//数据

	if(dat16 >= 0){
		dat = (int16)((float)dat16/0.0625);
	}
	else{
		dat16 = -dat16;
		dat = (int16)((float)dat16/0.0625);
	}

	data = (dat>>4)&0xff;
	I2C_SendByte(data);

	data = (dat<<4)&0xf0;
	I2C_SendByte(data);

	I2C_Stop();
}


void Init_TMP112(void)
{
	Init_TMP112_GPIO();
	TMP112_INIT();
	Tmp112_WriteConfig();
}





