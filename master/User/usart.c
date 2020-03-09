#include "usart.h"
#include "Drive.h"
/**
  ******************************************************************************
  * @file    usart.c
  * @author  控远智能科技有限公司
  * @version V1.0.0
  * @date    2017-8-1
  * @brief   按键初始化相关操作
  ******************************************************************************
  * @attention
  *
  *串口相关操作函数，完成串口的初始化操作，还定义了接收缓存，接收状态标志及接收长度信息
  *在做移植时，注意将相关变量移植到对应的文件中
  *
  ******************************************************************************
  */


//__IO uint8_t usart1_rcvd_flag;
__IO uint8_t usart2_rcvd_flag;
__IO uint8_t usart3_rcvd_flag;


//__IO uint8_t usart1_rcvd_len = 0;
__IO uint8_t usart2_rcvd_len = 0;
__IO uint8_t usart3_rcvd_len = 0;


//uint8_t usart1_rcvd_buf[USART1_RX_BUF_LEN];
char usart2_rcvd_buf[USART2_RX_BUF_LEN];
char usart3_rcvd_buf[USART3_RX_BUF_LEN];


void Init_USART(void)
{
	Init_USART2();
	Init_USART3();
}

/*
void Init_USART1(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	GPIO_PinAFConfig(GPIOA,GPIO_Pin_2,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA,GPIO_Pin_3,GPIO_AF_USART2);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;  
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	Stm32_Uartx_Init(USART1,USART1_BAUDRATE,FORMAT_8none);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
}
*/
void Init_USART2(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);
	/*
	*  USART2_TX -> PA2 , USART2_RX -> PA3
	*/				
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;  
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART2, ENABLE);
}

void USART2_Close(void){
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, DISABLE);
	USART_Cmd(USART2, DISABLE);
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&NVIC_InitStruct);

}

void Init_USART3(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3);
	/*
	*  USART3_TX -> PB10 , USART3_RX -> PB11
	*/				
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);		

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	Stm32_Uartx_Init(USART3,USART3_BAUDRATE,FORMAT_8none);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
}


void Stm32_Uartx_Init(USART_TypeDef* USARTx,uint32_t Baudrate,uint16_t Format)
{
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = Baudrate;
	switch(Format)
	{
		default:
		case FORMAT_8none:
		{ 
			USART_InitStruct.USART_WordLength = USART_WordLength_8b;
			USART_InitStruct.USART_Parity = USART_Parity_No;
			break;
		}
		case FORMAT_8even:
		{ 
			USART_InitStruct.USART_WordLength = USART_WordLength_9b;
			USART_InitStruct.USART_Parity = USART_Parity_Even;
			break;
		}
		case FORMAT_8odd:
		{ 
			USART_InitStruct.USART_WordLength = USART_WordLength_9b;
			USART_InitStruct.USART_Parity = USART_Parity_Odd;
			break;
		}
	}

	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
	USART_Init(USARTx, &USART_InitStruct);
	USART_Cmd(USARTx, ENABLE);
	//USART_ClearFlag(USARTx, USART_FLAG_TC);

}


void usart_send_str(USART_TypeDef* USARTx,char *str)
{

	USART_GetFlagStatus(USARTx, USART_FLAG_TC);
	while((*str)!='\0')
	{
	  USART_SendData(USARTx,*str);
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
		str++;
	}
//	USART_SendData(USARTx,'\n');
//	while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
}
/*
int fputc(int ch, FILE *f)
{
	USART_SendData(USART2, (uint8_t) ch);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);		
	return (ch);

}	

int fgetc(FILE *f)
{
	while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);
	return (char)USART_ReceiveData(USART2);
}*/

//整形转字符，stm32不支持标准的itoa,这里自己实现
char *myitoa(int value, char *string, int radix)
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;
    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;

} /* NCL_Itoa */

//字符串转整形，stm32不支持标准的atoi,这里自己实现
int myatoi(const char *str)
{
	int s=0;
	uint8_t falg=0;
	
	while(*str==' ')
	{
		str++;
	}

	if(*str=='-'||*str=='+')
	{
		if(*str=='-')
		falg=1;
		str++;
	}

	while(*str>='0'&&*str<='9')
	{
		s=s*10+*str-'0';
		str++;
		if(s<0)
		{
			s=2147483647;
			break;
		}
	}
	return s*(falg?-1:1);
}

//简单的printf实现，在例程中将printf重定向到了串口2上，使用该函数可以实现其他串口的printf功能，注意是部分实现。
void USARTx_printf(USART_TypeDef* USARTx,char *Data,...)
{
  const char *str;
  int d;   
  char buf[16];
  va_list ap;
  va_start(ap, Data);
  while ( *Data != 0)
  {	
			USART_GetFlagStatus(USARTx, USART_FLAG_TC);
      if ( *Data == 0x5c )  //'\'
      {									  
              switch ( *++Data )
              {
                      case 'r':
                              USART_SendData(USARTx,0x0d);
                              Data ++;
                              break;

                      case 'n':
                              USART_SendData(USARTx,0x0a);	
                              Data ++;
                              break;
                      
                      default:
                              Data ++;
                          break;
              }			 
      }
      else if ( *Data == '%')
      {
				switch ( *++Data )
				{				
				case 's':	
					str = va_arg(ap, const char *);
					for ( ; *str; str++) 
					{
						USART_SendData(USARTx,*str);
						while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
					}
					Data++;
					break;
				case 'd':	
					d = va_arg(ap, int);
					myitoa(d, buf, 10);
					for (str = buf; *str; str++) 
					{
						USART_SendData(USARTx,*str);
						while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
					}
					Data++;
					break;
				default:
					Data++;
					break;
			}		 
    } 
    else 
		{
			USART_SendData(USARTx,*Data++);
			while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
		}
  }
}

