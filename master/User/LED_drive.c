#include "main.h"
#include "LED_Drive.h"
#include "typedef.h"



//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   


#define OLED_SCLK_Clr() GPIO_ResetBits(OLED_SCLK_PORT, OLED_SCLK_PINS)
#define OLED_SCLK_Set() GPIO_SetBits(OLED_SCLK_PORT, OLED_SCLK_PINS)

#define OLED_SDIN_Clr() GPIO_ResetBits(OLED_SDIN_PORT, OLED_SDIN_PINS)
#define OLED_SDIN_Set() GPIO_SetBits(OLED_SDIN_PORT, OLED_SDIN_PINS)

#define OLED_RST_Clr() GPIO_ResetBits(OLED_RST_PORT, OLED_RST_PINS)
#define OLED_RST_Set() GPIO_SetBits(OLED_RST_PORT, OLED_RST_PINS)


#define OLED_DC_Clr() GPIO_ResetBits(OLED_DC_PORT, OLED_DC_PINS)
#define OLED_DC_Set() GPIO_SetBits(OLED_DC_PORT, OLED_DC_PINS)


#define OLED_CS_Clr()  GPIO_ResetBits(OLED_CS_PORT, OLED_CS_PINS)
#define OLED_CS_Set()  GPIO_SetBits(OLED_CS_PORT, OLED_CS_PINS)


#define __nop()  _nop_()

void SPI1_Init(void)
{
    SPI_InitTypeDef  SPI_InitStruct;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
    /* Enable SPI clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    /* Set the MOSI,MISO and SCK at high level */
	GPIO_PinAFConfig(OLED_PORT, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(OLED_PORT, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(OLED_PORT, GPIO_PinSource7, GPIO_AF_SPI1);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;

	/* SPI SCK pin configuration */
	GPIO_InitStructure.GPIO_Pin = OLED_SCLK_PINS;
	GPIO_Init(OLED_PORT, &GPIO_InitStructure);

	/* SPI  MOSI pin configuration */
	GPIO_InitStructure.GPIO_Pin =  OLED_SDIN_PINS;
	GPIO_Init(OLED_PORT, &GPIO_InitStructure);

	/* SPI MISO pin configuration */
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStruct.SPI_CRCPolynomial = 7;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
    
    SPI_Init(SPI1, &SPI_InitStruct);
	/* Enable the Rx buffer not empty interrupt */
	//SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);
	/* Enable the SPI Error interrupt */
	//SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_ERR, ENABLE);

	/* Configure the Priority Group to 1 bit */                
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	/* Configure the SPI interrupt priority */
	NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

    /* SPI enable */
    SPI_Cmd(SPI1, ENABLE);
        
}   

//SPIx 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
uint8_t SPI1_ReadWriteByte(uint8_t TxData)
{		
    /*!< Wait until the transmit buffer is empty */
    while (SPI_GetFlagStatus(SPI1, SPI_FLAG_TXE) == RESET)
    {}
    
    /*!< Send the byte */
    SPI_SendData(SPI1, TxData);
    
    /*!< Wait to receive a byte*/
    while (SPI_GetFlagStatus(SPI1, SPI_FLAG_RXNE) == RESET)
    {}
    
    /*!< Return the byte read from the SPI bus */
    return SPI_ReceiveData(SPI1); 				    
}




//向SSD1306写入一个字节。
//dat:要写入的数据/命令
//cmd:数据/命令标志 0,表示命令;1,表示数据;
void OLED_WR_Byte(uint8_t dat,uint8_t cmd)
{	
    if(cmd == OLED_DATA)
        OLED_DC_Set();
    else 
        OLED_DC_Clr();	
    
    OLED_CS_Clr();
#if 0
    for(i=0;i<8;i++)
    {			  
        OLED_SCLK_Clr();
        if(dat&0x80)
            OLED_SDIN_Set();
        else
            OLED_SDIN_Clr();
        OLED_SCLK_Set();
        dat<<=1;   
    }
#else
    SPI1_ReadWriteByte(dat);
#endif
    OLED_CS_Set();
    OLED_DC_Set();   	    
} 



void OLED_Set_Pos(uint8_t x, uint8_t y) 
{ 
    OLED_WR_Byte(0xb0+y,OLED_CMD);
    OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
    OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 
}   	  

//开启OLED显示    
void OLED_Display_On(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
    OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
    OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

//关闭OLED显示     
void OLED_Display_Off(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
    OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
    OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
    uint8_t i,n;		    
    for(i=0;i<8;i++)  
    {  
        OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
        OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
        OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
        for(n=0;n<128;n++)
            OLED_WR_Byte(0,OLED_DATA); 
    } //更新显示
}

#if 0

//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示				 
//size:选择字体 16/12 
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr)
{      	
    uint8_t c=0,i=0;	
    c=chr-' ';//得到偏移后的值			
    if(x>Max_Column-1){x=0;y=y+2;}
    if(SIZE ==16)
    {
        OLED_Set_Pos(x,y);	
        for(i=0;i<8;i++)
            OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
        
        OLED_Set_Pos(x,y+1);
        for(i=0;i<8;i++)
            OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
    }
    else 
    {   
        OLED_Set_Pos(x,y+1);
        for(i=0;i<6;i++)
            OLED_WR_Byte(F6x8[c][i],OLED_DATA);
        
    }
}
//m^n函数
u32 oled_pow(uint8_t m,uint8_t n)
{
    u32 result=1;	 
    while(n--)result*=m;    
    return result;
}				  
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void OLED_ShowNum(uint8_t x,uint8_t y,u32 num,uint8_t len,uint8_t size2)
{         	
    uint8_t t,temp;
    uint8_t enshow=0;						   
    for(t=0;t<len;t++)
    {
        temp=(num/oled_pow(10,len-t-1))%10;
        if(enshow==0&&t<(len-1))
        {
            if(temp==0)
            {
                OLED_ShowChar(x+(size2/2)*t,y,' ');
                continue;
            }else enshow=1; 
            
        }
        OLED_ShowChar(x+(size2/2)*t,y,temp+'0'); 
    }
} 
//显示一个字符号串
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr)
{
    uint8_t j=0;
    while (chr[j]!='\0')
    {		OLED_ShowChar(x,y,chr[j]);
        x+=8;
        if(x>120){x=0;y+=2;}
        j++;
    }
}
//显示汉字
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no)
{      			    
    uint8_t t,adder=0;
    OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
    {
        OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
        adder+=1;
    }	
    
    OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
    {	
        OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
        adder+=1;
    }					
}
#endif

//OLED_DrawBMP(0, 0, 16, 8, batt_bmp2[Bt_tap]);

/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void OLED_DrawBMP(uint8_t x0, uint8_t y0,uint8_t x1, uint8_t y1,const uint8_t BMP[])
{ 	
    
    unsigned int j=0;
    uint8_t x,y;
    
    
    for(y=y0;y<y1;y++)
    {
        OLED_Set_Pos(x0,y);
        for(x=x0;x<x1;x++)
        {      
            OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
        }
    }
    
} 

void LCD_Display_Pic(uint8_t x, uint8_t y, uint8_t col, uint8_t row, const uint8_t * dat)
{
    uint8_t i, j;
    const uint8_t * p;
    
    p = dat;
    
    for(i = 0; i < row; i++){
        OLED_Set_Pos(x, y);
        for(j = 0; j < col; j++){	
            OLED_WR_Byte(*p, OLED_DATA);           
            p++;
        }
        y++;
    }
}



//初始化SSD1306					    
void OLED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = OLED_RST_PINS|OLED_DC_PINS|OLED_CS_PINS;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(OLED_PORT, &GPIO_InitStruct);
    //GPIO_Init(OLED_RST_PORT, GPIO_InitStruct);
    //GPIO_Init(OLED_DC_PORT, GPIO_InitStruct);
    //GPIO_Init(OLED_CS_PORT, GPIO_InitStruct);
    
    SPI1_Init();
    
    
    OLED_RST_Set();
    os_dly_wait(200);
    OLED_RST_Clr();
    os_dly_wait(200);
    OLED_RST_Set(); 
    /*				  
OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
OLED_WR_Byte(0x00,OLED_CMD);//-not offset
OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
OLED_WR_Byte(0x12,OLED_CMD);
OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
OLED_WR_Byte(0x02,OLED_CMD);//
OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
*/
    
    OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
    OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
    OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
    OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
    OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
    OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
    OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
    OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
    OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
    OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
    OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
    OLED_WR_Byte(0x00,OLED_CMD);//-not offset
    OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
    OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
    OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
    OLED_WR_Byte(0x12,OLED_CMD);
    OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
    OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
    OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WR_Byte(0x02,OLED_CMD);//
    OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
    OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
    OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
    OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
    OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
    
    OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
    OLED_Clear();
    OLED_Set_Pos(0,0); 	
    
    
    
    //OLED_ShowString(30,0,"OLED TEST");
    //OLED_ShowString(8,2,"ZHONGJINGYUAN");  
    //OLED_ShowString(20,4,"2014/05/01");  
    //OLED_ShowString(0,6,"ASCII:");  
    //OLED_ShowString(63,6,"CODE:");  
    //OLED_ShowCHinese(0,0,0);
    //OLED_ShowCHinese(18,0,1);
    //OLED_ShowCHinese(36,0,2);
    //OLED_ShowCHinese(54,0,3);
    //OLED_ShowCHinese(72,0,4);
    //OLED_ShowCHinese(90,0,5);
    //OLED_ShowCHinese(108,0,6);
    
    
    
}  


void  OLED_Disable(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    NVIC_InitTypeDef NVIC_InitStructure;
	SPI_I2S_DeInit(SPI1);
	NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&NVIC_InitStructure);
    SPI_Cmd(SPI1, DISABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, DISABLE);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = OLED_RST_PINS|OLED_DC_PINS|OLED_CS_PINS;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(OLED_PORT, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = OLED_SCLK_PINS|OLED_SDIN_PINS;
	GPIO_Init(OLED_PORT, &GPIO_InitStruct);

}


//******************************************************************************************
//以下为显存模式
//******************************************************************************************


static uint8_t  dis_buff[1024] = {0x00};//显存 


//OLED 显示将显存的内容全部显示
void OLED_DisplayBuff(void)
{
    unsigned int j=0;
    uint8_t x,y;
    uint8_t x1= 128, y1 = 8;
    uint8_t x0 = 0,y0 = 0;
    
    if(y1%8==0) 
        y=y1/8;      
    else 
        y=y1/8+1;
    
    for(y=y0;y<y1;y++)
    {
        OLED_Set_Pos(x0,y);
        for(x=x0;x<x1;x++)
        {      
            OLED_WR_Byte(dis_buff[j++],OLED_DATA);	    	
        }
    }
    
}

#define setbit(x,y) x|=(1<<y) //将X的第Y位置1
#define clrbit(x,y) x&=~(1<<y) //将X的第Y位清0

static void set_pixel(uint16_t x, uint16_t y, uint8_t color) 
{
    uint16_t byte;
    
    if(x > 128 || y > 64) { return; }
    
    if(y/8 == 0) 
    { byte = x; }
    else 
    { byte = x+128*(y/8); }
    
    //OLED_Set_Pos(x,y);
    
    if(color)
        dis_buff[byte] |= (0x01<<(y-8*(y/8)));
    else
        dis_buff[byte] &= ~(0x01<<(y-8*(y/8)));
    
    
}

//垂直线
void  Display_VLine(uint8_t x0, uint8_t y0, uint8_t y1, uint8_t color) 
{
    uint8_t  bak;
    
    if(y0 > y1) 						// 对y0、y1大小进行排列，以便画图
    {  
        bak = y1;
        y1 = y0;
        y0 = bak;
    }
    
    do
    {  
        set_pixel(x0, y0,color);		// 逐点显示，描出垂直线
        y0++;
    }while(y1 >= y0);
}

//水平线
void  Display_HLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t color) 
{
    uint8_t  bak;
    
    if(x0 > x1) 						// 对x0、x1大小进行排列，以便画图
    {
        bak = x1;
        x1 = x0;
        x0 = bak;
    }
    
    do
    {		
        set_pixel(x0, y0, color);
        x0++;
    }while(x1 >= x0);
}

//空心矩形框
void  Display_Rectangle(uint8_t x0, uint8_t y0, uint8_t wight, uint8_t hight, uint8_t color) 
{
    Display_HLine(x0,y0,x0+wight,color);
	Display_HLine(x0,y0+hight,x0+wight,color);
	Display_VLine(x0,y0,y0+hight,color);
	Display_VLine(x0+wight,y0,y0+hight,color);
}

//实心矩形框
void Bar(uint8_t x0, uint8_t y0, uint8_t wight, uint8_t hight, uint8_t color) 
{
	uint8_t i;
	for(i=0;i<hight;i++){
    	Display_HLine(x0,y0+i,x0+wight,color);
	}
}


void Display_PIC(uint8_t x, uint8_t y, uint8_t col, uint8_t row, uint8_t const * dat)
{
    uint8_t i, j, index;
    uint8_t const * p;
    uint8_t d;
    
    p = dat;
    
    //取模方式:逐行式	
    for(i = 0; i < row; i++){
        d = *p++;
        index = 0;
        for(j = 0; j < col; j++){
            if(index == 8){
                d = *p++;
                index = 0;
            }			
            set_pixel(x + j, y + i, d&0x80);
            index++;
            d <<=1;
        }
    }	
}


void LCD_Clear(void)
{
	memset(dis_buff,0,1024);
}

void LCD_Update(void)
{
    unsigned int j=0;
    uint8_t x,y;
    uint8_t x1= 128, y1 = 8;
    uint8_t x0 = 0,y0 = 0;
    
    if(y1%8==0) 
        y=y1/8;      
    else 
        y=y1/8+1;
    
    for(y=y0;y<y1;y++)
    {
        OLED_Set_Pos(x0,y);
        for(x=x0;x<x1;x++)
        {      
            OLED_WR_Byte(dis_buff[j++],OLED_DATA);	    	
        }
    }
}






