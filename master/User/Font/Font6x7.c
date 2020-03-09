/****************************************************************************************
* 文件名：FONT8x16.C
* 功能：8x16 ASCII码字体及显示函数。
* 作者：
* 日期：2009.04.17
* 备注：使用GUI_SetColor()函数设置前景颜色及背景色。
****************************************************************************************/
#include "main.h"
#include "fonts_conf.h"

#if FONT6x7_EN==1


extern void Display_PIC(uint8 x, uint8 y, uint8 col, uint8 row, uint8 const *dat);

#define ASCII_CHAR_NUM	13
#define FONT_UNIT_SIZE	11

static const uint8 ascii_char_code[ASCII_CHAR_NUM*FONT_UNIT_SIZE] = 
{
0x06,0x08,0x01,0x70,0x88,0x88,0x88,0x88,0x88,0x88,0x70,/*"0",0*/
0x06,0x08,0x01,0x20,0x60,0x20,0x20,0x20,0x20,0x20,0x70,/*"1",1*/
0x06,0x08,0x01,0x70,0x88,0x88,0x10,0x20,0x40,0x80,0xF8,/*"2",2*/
0x06,0x08,0x01,0x70,0x88,0x08,0x30,0x08,0x08,0x88,0x70,/*"3",3*/
0x06,0x08,0x01,0x10,0x30,0x50,0x50,0x90,0x78,0x10,0x18,/*"4",4*/
0x06,0x08,0x01,0xF8,0x80,0x80,0xF0,0x08,0x08,0x88,0x70,/*"5",5*/
0x06,0x08,0x01,0x70,0x90,0x80,0xF0,0x88,0x88,0x88,0x70,/*"6",6*/
0x06,0x08,0x01,0xF8,0x90,0x10,0x20,0x20,0x20,0x20,0x20,/*"7",7*/
0x06,0x08,0x01,0x70,0x88,0x88,0x70,0x88,0x88,0x88,0x70,/*"8",8*/
0x06,0x08,0x01,0x70,0x88,0x88,0x88,0x78,0x08,0x48,0x70,/*"9",9*/
0x06,0x08,0x01,0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,/*"-",10*/
0x03,0x08,0x01,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,/*":",11*/
0x03,0x08,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*" ",12*/
};

/* ASCII码字符字模检索表 */
static const int8 ascii_char_array[ASCII_CHAR_NUM]="0123456789-: "; 

/****************************************************************************
* 名称：GUI_PutChar()
* 功能：显示ASCII码，显示值为'0'-'9'、'.'、'+'、'-'及':'(若为其它值，则显示' ')。
* 入口参数： x		指定显示位置，x坐标
*           y		指定显示位置，y坐标
*           ch		要显示的ASCII码值。
* 出口参数：为0时表示操作失败，返回其他值为偏移量。
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
static uint8  GUI_PutChar6x7(uint8 x, uint8 y, int8 ch)
{  
	uint8 const *p;
	uint16 i;
	uint8 col, row;
   
	for(i=0; i<ASCII_CHAR_NUM; i++)
	{  
		if(ascii_char_array[i]==ch){
			break;
		}
	}
	
	if(i >= ASCII_CHAR_NUM){
		i = ASCII_CHAR_NUM-1;
	}
	
	p = ascii_char_code+i*FONT_UNIT_SIZE;
	col = *p;
	row = *(p+1);
	p += 3;
	
    	Display_PIC(x, y, col, row, p);
   
	return col;
}


/****************************************************************************
* 名称：GUI_PutString7x14()
* 功能：显示ASCII码(16x32字体)，显示值为'0'-'9'、'.'、'+'、'-'及':'(若为其它值，则显示' ')。
* 入口参数： x		指定显示位置，x坐标
*           y		指定显示位置，y坐标
*           ch		要显示的ASCII码值。
* 出口参数：返回值为1时表示操作成功，为0时表示操作失败。
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
uint8 GUI_PutString6x7(uint8 x, uint8 y, int8 * str)
{
	uint8 ret, add_len;

	add_len = 0;
	while(1){
		if( (*str)=='\0' ){
			break;
		}
		ret = GUI_PutChar6x7(x, y, *str++);
		x += ret;						
		add_len += ret;
	}

	return add_len;
}


#if 0
uint8 GUI_PutStringConst6x7(uint8 x,uint8 y , int8 const *str)
{
	uint8 e;
	const uint8 *p;
	uint8 ret;
	uint8 add_len;
	
	p = str;
	add_len = 0;
	
	while(*p){
		if(*p <= 0x7f){
			e = *p++;
			ret =GUI_PutChar6x7(x, y, e);
			x += ret;	
			add_len += ret;
			if(x >= GUI_LCM_XMAX){
				break;
			}
		}else {
			break;
		}
	}
		
	return add_len;
}
#endif

#if 0
void Font7x14_Test(void)
{
	uint8 i, j;
	uint8 x, y;


	x = 0, y = 0;
	j = 0;
	while(1){
		for(i = 0; i < 16; i++){
			x += GUI_PutChar7x14(x, y, ascii_char_array[j]);
			j++;
			if(j == ASCII_CHAR_NUM){
				j = 0;
			}
		}
		x = 0;
		y+=16;
		if(y == 64){
			y = 0;
			LCD_Update();
			Delay(5000);
			LCD_Clear();
		}
	}
}
#endif

#endif



