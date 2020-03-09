#include "SI24R1.h"

const u8 TX_ADDRESS[TX_ADR_WIDTH] = {0x0A,0x01,0x07,0x0E,0x01};  // 定义一个静态发送地址
const u8 RF_CHANNEL[CH_NUM] = {2, 10, 20, 30, 40, 50, 60, 70, 80, 90, 120};//定义RF的通讯通道，一共定义 0 -9 共计 10个



static u8 SPI_RW(u8 byte)
{
	u8 bit_ctr;
	for(bit_ctr=0; bit_ctr<8; bit_ctr++)
	{
		if(byte & 0x80)
			CC_MO_H;//MOSI = 1;
		else
			CC_MO_L;//MOSI = 0;																 
		byte = (byte << 1);                      
		CC_SLK_H;//SCK = 1;                                   
		byte |= CC2500_MI;//MISO;     
		//SPIWait();
		CC_SLK_L;//SCK = 0;                                
	}
	return(byte);                              
}


/********************************************************
函数功能：SI24R1引脚初始化                
入口参数：无
返回  值：无
*********************************************************/
void SI24R1_Init(void)
{
	//SCK = 0; 													//SPI时钟线拉低
	//CSN = 1;				
	//CE 	= 0;				
	//IRQ = 1;

	GPIO_InitTypeDef GPIO_InitStru;

    //SPI_2 Interface
    GPIO_InitStru.GPIO_Pin = CC_SCLK + CC_MOSI;
    GPIO_InitStru.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStru.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStru.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStru.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(CC_GPIO,&GPIO_InitStru);
	GPIO_ResetBits(CC_GPIO,CC_SCLK);


    GPIO_InitStru.GPIO_Pin = CC_MISO;
    GPIO_InitStru.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStru.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStru.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStru.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(CC_GPIO,&GPIO_InitStru);
    
    GPIO_InitStru.GPIO_Pin = CC_CSn;
    GPIO_InitStru.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStru.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStru.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStru.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(CC_GPIO,&GPIO_InitStru);
	GPIO_SetBits(CC_GPIO,CC_CSn);

	GPIO_InitStru.GPIO_Pin = CC_CE;
    GPIO_InitStru.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStru.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStru.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStru.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(CC_GPIO,&GPIO_InitStru);
	GPIO_ResetBits(CC_GPIO,CC_CE);

    //GDO PINs
    GPIO_InitStru.GPIO_Pin = CC_IRQ;
    GPIO_InitStru.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStru.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStru.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(CC_GPIO,&GPIO_InitStru);
	
}


/********************************************************
函数功能：写寄存器的值（单字节）                
入口参数：reg:寄存器映射地址（格式：WRITE_REG｜reg）
					value:寄存器的值
返回  值：状态寄存器的值
*********************************************************/
u8 SI24R1_Write_Reg(u8 reg, u8 value)
{
	u8 status;

	CC_CSn_L;//CSN = 0;                 
	status = SPI_RW(reg);				
	SPI_RW(value);
	CC_CSn_H;//CSN = 1;  
	
	return(status);
}


/********************************************************
函数功能：写寄存器的值（多字节）                  
入口参数：reg:寄存器映射地址（格式：WRITE_REG｜reg）
					pBuf:写数据首地址
					bytes:写数据字节数
返回  值：状态寄存器的值
*********************************************************/
u8 SI24R1_Write_Buf(u8 reg, const u8 *pBuf, u8 bytes)
{
	u8 status,byte_ctr;

  CC_CSn_L;//CSN = 0;                                  			
  status = SPI_RW(reg);                          
  for(byte_ctr=0; byte_ctr<bytes; byte_ctr++)     
    SPI_RW(*pBuf++);
  CC_CSn_H;//CSN = 1;                                      	

  return(status);       
}							  					   


/********************************************************
函数功能：读取寄存器的值（单字节）                  
入口参数：reg:寄存器映射地址（格式：READ_REG｜reg）
返回  值：寄存器值
*********************************************************/
u8 SI24R1_Read_Reg(u8 reg)
{
 	u8 value;

	CC_CSn_L;//CSN = 0;    
	SPI_RW(reg);			
	value = SPI_RW(0);
	CC_CSn_H;//CSN = 1;              

	return(value);
}


/********************************************************
函数功能：读取寄存器的值（多字节）                  
入口参数：reg:寄存器映射地址（READ_REG｜reg）
					pBuf:接收缓冲区的首地址
					bytes:读取字节数
返回  值：状态寄存器的值
*********************************************************/
u8 SI24R1_Read_Buf(u8 reg, u8 *pBuf, u8 bytes)
{
	u8 status,byte_ctr;

  CC_CSn_L;//CSN = 0;                                        
  status = SPI_RW(reg);                           
  for(byte_ctr=0;byte_ctr<bytes;byte_ctr++)
    pBuf[byte_ctr] = SPI_RW(0);                   //读取数据，低字节在前
  CC_CSn_H;//CSN = 1;                                        

  return(status);    
}

void SI24R1_Standby_Mode(void)
{
	CC_CE_L;//CE=0;	
	//SI24R1_Write_Reg(WRITE_REG1 + CONFIG, 0x00);
}

/********************************************************
函数功能：SI24R1接收模式初始化                      
入口参数：无
返回  值：无
*********************************************************/
void SI24R1_RX_Mode(uint8 ch)
{
	CC_CE_L;//CE=0;	
	SI24R1_Write_Buf(WRITE_REG1 + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);	// 接收设备接收通道0使用和发送设备相同的发送地址
	SI24R1_Write_Reg(WRITE_REG1 + EN_AA, 0x01);               						// 使能接收通道0自动应答
	SI24R1_Write_Reg(WRITE_REG1 + EN_RXADDR, 0x01);           						// 使能接收通道0
	SI24R1_Write_Reg(WRITE_REG1 + RF_CH, RF_CHANNEL[ch]);                 						// 选择射频通道0x40
	SI24R1_Write_Reg(WRITE_REG1 + RX_PW_P0, TX_PLOAD_WIDTH);  						// 接收通道0选择和发送通道相同有效数据宽度
	SI24R1_Write_Reg(WRITE_REG1 + RF_SETUP, 0x0f);            						// 数据传输率2Mbps，发射功率7dBm
	SI24R1_Write_Reg(WRITE_REG1 + CONFIG, 0x0f);              						// CRC使能，16位CRC校验，上电，接收模式
	SI24R1_Write_Reg(WRITE_REG1 + STATUS, 0xff);  												//清除所有的中断标志位
	CC_CE_H;//CE=1;	                                          									// 拉高CE启动接收设备
}						


/********************************************************
函数功能：SI24R1发送模式初始化                      
入口参数：无
返回  值：无
*********************************************************/
void SI24R1_TX_Mode(uint8 ch)
{
	CC_CE_L;//CE=0;	
	SI24R1_Write_Buf(WRITE_REG1 + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);     // 写入发送地址
	SI24R1_Write_Buf(WRITE_REG1 + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);  // 为了应答接收设备，接收通道0地址和发送地址相同

	SI24R1_Write_Reg(WRITE_REG1 + EN_AA, 0x01);       											// 使能接收通道0自动应答
	SI24R1_Write_Reg(WRITE_REG1 + EN_RXADDR, 0x01);   											// 使能接收通道0
	SI24R1_Write_Reg(WRITE_REG1 + SETUP_RETR, 0x0a);  											// 自动重发延时等待250us+86us，自动重发10次
	SI24R1_Write_Reg(WRITE_REG1 + RF_CH, RF_CHANNEL[ch]);         											// 选择射频通道0x40
	SI24R1_Write_Reg(WRITE_REG1 + RF_SETUP, 0x0f);    											// 数据传输率2Mbps，发射功率7dBm
	SI24R1_Write_Reg(WRITE_REG1 + CONFIG, 0x0e);      											// CRC使能，16位CRC校验，上电
	//CE = 1;
}


/********************************************************
函数功能：读取接收数据                       
入口参数：rxbuf:接收数据存放首地址
返回  值：0:接收到数据
          1:没有接收到数据
*********************************************************/
u8 SI24R1_RxPacket(u8 *rxbuf)
{
	u8 state;
	state = SI24R1_Read_Reg(STATUS);  			                 //读取状态寄存器的值    	  
	SI24R1_Write_Reg(WRITE_REG1+STATUS,state);               //清除RX_DS中断标志

	if(state & RX_DR)								                           //接收到数据
	{
		SI24R1_Read_Buf(RD_RX_PLOAD,rxbuf,TX_PLOAD_WIDTH);     //读取数据
		SI24R1_Write_Reg(FLUSH_RX,0xff);					              //清除RX FIFO寄存器
		return 0; 
	}
	return 1;//没收到任何数据
}


/********************************************************
函数功能：发送一个数据包                      
入口参数：txbuf:要发送的数据
返回  值：0x10:达到最大重发次数，发送失败 
          0x20:发送成功            
          0xff:发送失败                  
*********************************************************/
u8 SI24R1_TxPacket(u8 *txbuf)
{
	u8 state;
	u32 count = 0;
	CC_CE_L;//CE=0;																										  //CE拉低，使能SI24R1配置
	SI24R1_Write_Buf(WR_TX_PLOAD, txbuf, TX_PLOAD_WIDTH);	    //写数据到TX FIFO,32个字节
 	CC_CE_H;//CE=1;																										  //CE置高，使能发送	   
	
	while((IRQ_IN != 0) && (count<100000)){count++;}																				  //等待发送完成
	state = SI24R1_Read_Reg(STATUS);  											  //读取状态寄存器的值	   
	SI24R1_Write_Reg(WRITE_REG1+STATUS, state); 								//清除TX_DS或MAX_RT中断标志
	if(state&MAX_RT)																			    //达到最大重发次数
	{
		SI24R1_Write_Reg(FLUSH_TX,0xff);										    //清除TX FIFO寄存器 
		return MAX_RT; 
	}
	if(state&TX_DS)																			      //发送完成
	{
		return TX_DS;
	}
	return 0XFF;																						  //发送失败
}

