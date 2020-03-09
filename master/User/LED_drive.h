//移植说明：采用硬件SPI模式读写SD卡，SPI1
//SD_DT3--SD_CS------------PB4
//SD_CMD--SPI1_MOSI--------PB6
//SD_SCK--SPI1_SCK---------PB5
//SD_DT0--SPI1_MISO--------PB7
//
//
//
//
#ifndef _OLED_H_
#define _OLED_H_		 

#include "stm32l1xx.h"
#include "typedef.h"



#define GUI_LCM_XMAX    128


#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED端口定义----------------  					   



/****************时钟*********************/
#define OLED_PORT  (GPIOA)

#define OLED_SCLK_PORT  (GPIOA)
#define OLED_SCLK_PINS  (GPIO_Pin_5)

/****************数据*********************/
#define OLED_SDIN_PORT  (GPIOA)
#define OLED_SDIN_PINS  (GPIO_Pin_7)

/****************复位*********************/
#define OLED_RST_PORT  (GPIOA)
#define OLED_RST_PINS  (GPIO_Pin_8)

/****************数据/命令*********************/
#define OLED_DC_PORT  (GPIOA)
#define OLED_DC_PINS  (GPIO_Pin_9)

/****************片选*********************/
#define OLED_CS_PORT  (GPIOA)
#define OLED_CS_PINS  (GPIO_Pin_4)




										  
void SPI1_Init(void);			 //初始化SPI口
uint8_t SPI1_ReadWriteByte(uint8_t dt);//SPI总线读写一个字节

		     

//OLED控制用函数
extern void OLED_WR_Byte(uint8_t dat,uint8_t cmd);	    
extern void OLED_Display_On(void);
extern void OLED_Display_Off(void);	   							   		    
extern void OLED_Init(void);
extern void OLED_Clear(void);
extern void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
extern void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot);
extern void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr);
extern void OLED_ShowNum(uint8_t x,uint8_t y,uint32 num,uint8_t len,uint8_t size2);
extern void OLED_ShowString(uint8_t x,uint8_t y, uint8_t *p);	 
extern void OLED_Set_Pos(uint8_t x, uint8_t y);
extern void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);
extern void OLED_DrawBMP(uint8_t x0, uint8_t y0,uint8_t x1, uint8_t y1,const uint8_t BMP[]);


extern void OLED_DisplayBuff(void);

extern void Display_PIC(uint8_t x, uint8_t y, uint8_t col, uint8_t row, uint8_t const * dat);

extern void OLED_DisplayPic(uint8_t x0, uint8_t y0,uint8_t w, uint8_t h,const uint8_t BMP[]);

extern void  Display_VLine(uint8_t x0, uint8_t y0, uint8_t y1, uint8_t color);
extern void  Display_HLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t color) ;
void  Display_Rectangle(uint8_t x0, uint8_t y0, uint8_t wight, uint8_t hight, uint8_t color);
void Bar(uint8_t x0, uint8_t y0, uint8_t wight, uint8_t hight, uint8_t color);

extern void LCD_Clear(void);

extern void LCD_Update(void);

extern void  OLED_Disable(void);

extern void LCD_Display_Pic(uint8_t x, uint8_t y, uint8_t col, uint8_t row, const uint8_t * dat);
 
#endif




