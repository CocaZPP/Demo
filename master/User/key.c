#include "Key.h"


__IO uint8 Key_flag = 0;
__IO uint16 BS8116A_value = 0;
__IO uint8 TCKey_value = 0;




#define BS8116_INT_GPIO		GPIOC
#define BS8116_INT_Pin		GPIO_Pin_6


#define I2C2_SLAVE_ADDRESS		0xA0

// IO Config
#define I2C2_GPIO					GPIOC
#define I2C2_SCL					GPIO_Pin_8
#define I2C2_SDA					GPIO_Pin_7

/* Private define ------------------------------------------------------------*/
#define SCL2_H        GPIO_SetBits(I2C2_GPIO,I2C2_SCL)
#define SCL2_L         GPIO_ResetBits(I2C2_GPIO,I2C2_SCL)
 
#define SDA2_H         GPIO_SetBits(I2C2_GPIO,I2C2_SDA)
#define SDA2_L         GPIO_ResetBits(I2C2_GPIO,I2C2_SDA)

#define SDA2_read     GPIO_ReadInputDataBit(I2C2_GPIO, I2C2_SDA)

static void I2C2_delay(void)
{	
	volatile uint16 i = 12; //这里可以优化速度	，经测试最低到5还能写入
   
	while(i){
		i--; 
	} 
}
void Init_BS8116A_GPIO(void)
{ 

	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;

			
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Pin = I2C2_SDA|I2C2_SCL;
	GPIO_Init(I2C2_GPIO, &GPIO_InitStructure);
	SCL2_H;SDA2_H;

	//中断
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = BS8116_INT_Pin;
	GPIO_Init(BS8116_INT_GPIO,&GPIO_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource6);

	EXTI_InitStruct.EXTI_Line = EXTI_Line6;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;

	NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

	EXTI_Init(&EXTI_InitStruct);

	NVIC_Init(&NVIC_InitStruct);

}

void BS8116A_GPIO_Set_Input(void){

	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	EXTI_InitStruct.EXTI_Line = EXTI_Line6;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStruct.EXTI_LineCmd = DISABLE;

	NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x0d;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;

	EXTI_Init(&EXTI_InitStruct);

	NVIC_Init(&NVIC_InitStruct);

	GPIO_InitStructure.GPIO_Pin = I2C2_SDA;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(I2C2_GPIO,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = I2C2_SCL;
	GPIO_Init(I2C2_GPIO,&GPIO_InitStructure);

	//中断
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Pin = BS8116_INT_Pin;
	GPIO_Init(BS8116_INT_GPIO,&GPIO_InitStructure);


}
static void I2C2_Set_SDA_Output(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; 

	GPIO_InitStructure.GPIO_Pin = I2C2_SDA;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(I2C2_GPIO,&GPIO_InitStructure);
}

static void I2C2_Set_SDA_Input(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; 

	GPIO_InitStructure.GPIO_Pin = I2C2_SDA;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(I2C2_GPIO,&GPIO_InitStructure);
}

static void I2C2_Start(void)
{
	//SCL_L;
	//I2C_delay();
	I2C2_Set_SDA_Output();
	SDA2_H;
	I2C2_delay();
	SCL2_H;
	I2C2_delay();
	SDA2_L;
	I2C2_delay();
	
	//SCL_L;
	//I2C_delay();
}

static void I2C2_Stop(void)
{
	SCL2_L;
	I2C2_delay();
	SDA2_L;
	I2C2_delay();
	SCL2_H;
	I2C2_delay();
	SDA2_H;
	I2C2_delay();
}

static ErrorStatus I2C2_WaitAck(void) 	 //返回为:=1有ACK,=0无ACK
{
	uint8 errtime = 255;    
	ErrorStatus ret;

	ret = SUCCESS;
	
	SCL2_L;
	I2C2_delay();
	I2C2_Set_SDA_Input();
	SCL2_H;
	I2C2_delay();
 	while(SDA2_read == SET)
 	{
		//Delay(8);// 1US
  		errtime--;
  		if(errtime==0){  			
			ret = ERROR;
			break;
  		}
		I2C2_delay();
 	}
	SCL2_L;
	I2C2_delay();
	I2C2_Set_SDA_Output();
	
	return ret;
}

static ErrorStatus I2C2_SendByte(uint8 SendByte) //数据从高位到低位//
{
	ErrorStatus ret;
	uint8 i = 8;

	while(i--){
		SCL2_L;
		I2C2_delay();
		if(SendByte&0x80){
			SDA2_H;  
		}else{
			SDA2_L;   
		}
		SendByte<<=1;
		I2C2_delay();
		SCL2_H;
		I2C2_delay();
	}
	//SCL_L;
	//I2C_delay();
	ret = I2C2_WaitAck();
	I2C2_delay();

	return ret;
}


static uint8 I2C2_ReceiveByte(uint8 need_ack)  //数据从高位到低位//
{ 
	uint8 i = 8;
	uint8 ReceiveByte = 0;
        volatile uint8 k;

       //I2C2_Set_SDA_Input();
	while(i--){
		ReceiveByte <<= 1;
		SCL2_L;
		I2C2_Set_SDA_Input();
		I2C2_delay();
		SCL2_H;
		I2C2_delay();
                k = SDA2_read;
		if(k){//SDA2_read == SET
			ReceiveByte |= 0x01;
		}
	}
	
	if(need_ack){
		SCL2_L;
		I2C2_delay();
		I2C2_Set_SDA_Output();
		SDA2_L;
		I2C2_delay();
		SCL2_H;
		I2C2_delay();
	}else{
		SCL2_L;
		I2C2_delay();
		I2C2_Set_SDA_Output();
		SDA2_H;
		I2C2_delay();
		SCL2_H;
		I2C2_delay();
	}
	
	return ReceiveByte;
}




uint16 ReadBS8116A(void)
{
    uint8 key1 = 0;
    uint8 key2 = 0;
    uint16 key = 0;
    
    I2C2_Start();
    I2C2_SendByte(I2C2_SLAVE_ADDRESS);

    I2C2_SendByte(0x08);
    I2C2_Start();
    
    I2C2_SendByte(I2C2_SLAVE_ADDRESS|0x01);

    key1 = I2C2_ReceiveByte(1);
    key2 = I2C2_ReceiveByte(0);

    I2C2_Stop();

    key = (uint16)(key2<<8) + key1;

    return key;

}


uint16 ReadBS8116A_S(void)
{
    uint16 key = 0;
    
    I2C2_Start();
    I2C2_SendByte(I2C2_SLAVE_ADDRESS);

    I2C2_SendByte(0xB2);
    I2C2_Start();
    
    I2C2_SendByte(I2C2_SLAVE_ADDRESS|0x01);

    key = I2C2_ReceiveByte(0);

    I2C2_Stop();
	if(key != 0){
		//key_type = 1;
	}

    return key;

}







void Init_BS8116A(void)
{
    uint8 check_sum = 0;
    uint8 data;
    uint8 add;
	uint8 ack = 0;
    uint8 i;
	
	Init_BS8116A_GPIO();
	
    I2C2_Start();
    ack = I2C2_SendByte(I2C2_SLAVE_ADDRESS);
    //22个数据

    add = 0xb0;
    ack = I2C2_SendByte(add);
    //Option1   bit0: IRQ_OMS  0:Level hole ( 默认 )   1:One-shot
    data = 0x01;
    ack = I2C2_SendByte(data);
    check_sum += data;

    //Reserve
    data = 0x00;
    ack = I2C2_SendByte(data);
    check_sum += data;

    //Reserve
    data = 0x83;
    ack = I2C2_SendByte(data);
    check_sum += data;

    //Reserve
    data = 0xf3;
    ack = I2C2_SendByte(data);
    check_sum += data;

    //Option2  bit6  LSC  0:一般省电模式   1:更省电模式 ( 唤醒时间增加至 0.5~1 秒 )
    data = 0x98;//0xD8   0x98
    ack = I2C2_SendByte(data);
    check_sum += data;


    //K1   bit7  K1WU  0开启按键唤醒功能 ( 默认 )  1关闭按键唤醒功能
    data = 0x10;
    ack = I2C2_SendByte(data);
    check_sum += data;

    //K - TH    bit7  K1WU  0开启按键唤醒功能 ( 默认 )  1关闭按键唤醒功能
    for(i = 0; i < 14; i++){
        data = 0x10;
        ack = I2C2_SendByte(data);
        check_sum += data;
    }

    //K16   bit6 : Mode   0: Key16  1: IRQ ( 默认 )
    data = 0xd0;  //0xD0  0x90
    ack = I2C2_SendByte(data);
    check_sum += data;

    //CHECK SUM
    data = check_sum;
    ack = I2C2_SendByte(data);

    I2C2_Stop();


	//ReadBS8116A_S();//识别按键类型


}


//=========KEY=============
uint8 ReadKeyValue(void)
{

    uint16 temp;
    uint8 KEY_SCAN = KEY_NONE;


    temp = BS8116A_value & 0xfffe;
    switch(temp){
        case 0x0004://r
			KEY_SCAN = 'r';//right
            break;
        case 0x0008://d
			KEY_SCAN = 'd';//down
            break;
        case 0x0010://l
			KEY_SCAN = 'l';//left
            break;
        case 0x0020://m
			KEY_SCAN = 'm';//menu
            break;
		case 0x0040://u
			KEY_SCAN = 'u';//up
			break;
		case 0x0080://o
			KEY_SCAN = 'o';//ok
            break;
        default:
            KEY_SCAN = KEY_NONE;
    }



    return KEY_SCAN;//KEY

}







