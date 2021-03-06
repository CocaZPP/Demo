/****************************************************************************************
* 文件名：FONT8x16.C
* 功能：8x16 ASCII码字体及显示函数。
* 作者：
* 日期：2009.04.17
* 备注：使用GUI_SetColor()函数设置前景颜色及背景色。
****************************************************************************************/
#include "main.h"
#include "fonts_conf.h"

#if FONT7x14_EN==1

extern void Display_PIC(uint8 x, uint8 y, uint8 col, uint8 row, uint8 const *dat);

#define ASCII_CHAR_NUM	90
#define FONT_UNIT_SIZE	31

static const uint8 ascii_char_code[ASCII_CHAR_NUM*FONT_UNIT_SIZE] = 
{
/* 0 */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : 0
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x38,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x38,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 1 */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : 1
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x10,0x30,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 2 */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : 2
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x38,0x44,0x44,0x04,0x08,0x10,0x20,0x40,0x7C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 3 */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : 3
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x38,0x44,0x04,0x18,0x04,0x04,0x04,0x44,0x38,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 4 */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : 4
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x08,0x18,0x28,0x48,0x48,0x88,0x78,0x08,0x1C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 5 */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : 5
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x7C,0x40,0x40,0x78,0x44,0x04,0x44,0x44,0x38,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 6 */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : 6
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x1C,0x24,0x40,0x58,0x64,0x44,0x44,0x44,0x38,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 7 */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : 7
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x7C,0x48,0x08,0x08,0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 8 */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : 8
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x38,0x44,0x44,0x28,0x38,0x44,0x44,0x44,0x38,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* 9 */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : 9
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x38,0x44,0x44,0x44,0x4C,0x34,0x04,0x48,0x70,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* . */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : .
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x03,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*------------------------------------------------------------------------------
;  源文件 / 文字 : ~
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x20,0x52,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*------------------------------------------------------------------------------
;  源文件 / 文字 : !
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x03,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x40,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* @ */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : @
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x38,0x44,0x9A,0xAA,0xAA,0xAA,0xB4,0x42,0x3C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* # */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : #
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x28,0x28,0xFC,0x28,0x48,0x50,0xFC,0x50,0x50,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* $ */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : $
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x06,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x20,0x78,0xA8,0xA0,0x60,0x30,0x28,0xA8,0xA8,0x70,0x20,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* % */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : %
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x44,0xA8,0xA8,0xB0,0x68,0x34,0x54,0x54,0x88,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* ^ */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : ^(用于表示三次方)
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/

0x04,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x60,0x90,0x10,0x60,0x10,0x90,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0x04,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
//0x00,0x40,0xA0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* & */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : &
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x20,0x50,0x50,0x60,0x58,0xA8,0xA8,0x90,0x6C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* * */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : *
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x06,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x20,0xA8,0x70,0x70,0xA8,0x20,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* ( */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : (
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x04,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x20,0x40,0x40,0x80,0x80,0x80,0x80,0x80,0x40,0x40,0x20,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* ) */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : )
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x04,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x80,0x40,0x40,0x20,0x20,0x20,0x20,0x20,0x40,0x40,0x80,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* _ */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : _
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* + */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : +
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x10,0x10,0x10,0xFE,0x10,0x10,0x10,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* - */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : -
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* = */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : =
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0xFC,0x00,0x00,0xFC,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* | */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : |
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x03,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* \ */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : \
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x06,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x80,0x80,0x40,0x40,0x20,0x20,0x20,0x10,0x10,0x08,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* / */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : /
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x04,0x08,0x08,0x10,0x10,0x20,0x20,0x40,0x40,0x80,0x80,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* ? */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : ?
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x06,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x70,0x88,0x88,0x08,0x10,0x20,0x20,0x00,0x20,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* : */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : :
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x04,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x00,0x00,0x60,0x60,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* ; */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : ;
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x04,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x00,0x60,0x60,0x20,0xC0,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* " */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : "
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x05,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x50,0xA0,0xA0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* ' */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : '
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x03,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0xC0,0x40,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* < */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : <
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x06,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x08,0x10,0x20,0x40,0x80,0x40,0x20,0x10,0x08,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* > */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : >
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x06,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x10,0x20,0x40,0x80,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* , */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : ,
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x04,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x20,0xC0,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* A */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : A
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x0A,0x0E,0x02,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x08,0x00,0x08,0x00,0x14,0x00,0x14,0x00,0x22,0x00,
0x3E,0x00,0x41,0x00,0x41,0x00,0xE3,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
/* B */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : B
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x08,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0xFC,0x42,0x42,0x42,0x7C,0x42,0x42,0x42,0xFC,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* C */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : C
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x08,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x3A,0x46,0x82,0x80,0x80,0x80,0x82,0x44,0x38,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* D */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : D
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x09,0x0E,0x02,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0xFC,0x00,0x42,0x00,0x41,0x00,0x41,0x00,0x41,0x00,
0x41,0x00,0x41,0x00,0x42,0x00,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* E */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : E
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0xFC,0x44,0x40,0x48,0x78,0x48,0x40,0x42,0xFC,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* F */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : F
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0xFC,0x44,0x40,0x48,0x78,0x48,0x40,0x40,0xE0,0x00,0x00,0x00,
0x48,0x00,0x40,0x00,0x40,0x00,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* G */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : G
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x08,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x3A,0x46,0x82,0x80,0x87,0x82,0x82,0x42,0x3C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* H */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : H
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x09,0x0E,0x02,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0xE7,0x00,0x42,0x00,0x42,0x00,0x42,0x00,0x7E,0x00,
0x42,0x00,0x42,0x00,0x42,0x00,0xE7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* I */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : I
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x04,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0xE0,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0xE0,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* J */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : J
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x05,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x70,0x20,0x20,0x20,0x20,0x20,0x20,0xA0,0xC0,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* K */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : K
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x09,0x0E,0x02,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0xE7,0x00,0x44,0x00,0x48,0x00,0x50,0x00,0x70,0x00,
0x48,0x00,0x44,0x00,0x42,0x00,0xE7,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
/* L */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : L
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0xE0,0x40,0x40,0x40,0x40,0x40,0x40,0x42,0xFC,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* M */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : M
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x0C,0x0E,0x02,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0xE0,0xE0,0x60,0xC0,0x51,0x40,0x51,0x40,0x51,0x40,
0x4A,0x40,0x4A,0x40,0x4A,0x40,0xE4,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,
/* N */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : N
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x09,0x0E,0x02,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0xC7,0x00,0x42,0x00,0x62,0x00,0x52,0x00,0x4A,0x00,
0x4A,0x00,0x46,0x00,0x42,0x00,0xE2,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* O */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : O
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x09,0x0E,0x02,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x3C,0x00,0x42,0x00,0x81,0x00,0x81,0x00,0x81,0x00,
0x81,0x00,0x81,0x00,0x42,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* P */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : P
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0xF8,0x44,0x44,0x44,0x78,0x40,0x40,0x40,0xE0,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* Q */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : Q
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x09,0x0E,0x02,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x3C,0x00,0x42,0x00,0x81,0x00,0x81,0x00,0x81,0x00,
0x81,0x00,0x81,0x00,0x42,0x00,0x3C,0x00,0x08,0x00,0x07,0x00,0x00,0x00,
/* R */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : R
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x08,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0xFC,0x42,0x42,0x42,0x7C,0x48,0x44,0x44,0xE3,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* S */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : S
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x74,0x8C,0x84,0x60,0x18,0x04,0x84,0xC4,0xB8,0x00,0x00,0x00,
0x04,0x00,0x84,0x00,0xC4,0x00,0xB8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* T */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : T
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x08,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0xFE,0x92,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* U */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : U
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x09,0x0E,0x02,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0xE7,0x00,0x42,0x00,0x42,0x00,0x42,0x00,0x42,0x00,
0x42,0x00,0x42,0x00,0x42,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* V */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : V
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x08,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0xEE,0x44,0x44,0x44,0x28,0x28,0x28,0x10,0x10,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* W */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : W
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x0D,0x0E,0x02,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0xEF,0x38,0x42,0x10,0x42,0x10,0x45,0x20,0x25,0x20,
0x29,0x40,0x29,0x40,0x10,0x80,0x10,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
/* X */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : X
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x09,0x0E,0x02,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0xE7,0x80,0x42,0x00,0x24,0x00,0x18,0x00,0x08,0x00,
0x18,0x00,0x24,0x00,0x42,0x00,0xE7,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
/* Y */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : Y
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x08,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0xE7,0x42,0x24,0x28,0x28,0x10,0x10,0x10,0x38,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* Z */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : Z
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x08,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x7E,0x42,0x04,0x08,0x10,0x20,0x40,0x82,0xFE,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* a */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : a
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x06,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0x30,0x48,0x38,0x48,0x48,0x3C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* b */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : b
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x40,0xC0,0x40,0x58,0x64,0x44,0x44,0x44,0x38,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* c */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : c
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x06,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0x38,0x48,0x40,0x40,0x48,0x30,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* d */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : d
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x04,0x0C,0x04,0x34,0x4C,0x44,0x44,0x4E,0x34,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* e */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : e
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x06,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0x30,0x48,0x78,0x40,0x48,0x30,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* f */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : f
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x04,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x30,0x40,0x40,0xF0,0x40,0x40,0x40,0x40,0xE0,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* g */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : g
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0x3E,0x44,0x44,0x38,0x40,0x7C,0x42,0x42,0x3C,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* h */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : h
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x40,0xC0,0x40,0x58,0x64,0x44,0x44,0x44,0xEE,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* i */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : i
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x03,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x40,0x00,0x00,0x40,0xC0,0x40,0x40,0x40,0xE0,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* j */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : j
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x03,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x40,0x00,0x00,0x40,0xC0,0x40,0x40,0x40,0x40,0x40,0x40,0x80,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* k */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : k
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x06,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x40,0xC0,0x40,0x4C,0x50,0x60,0x50,0x48,0xEC,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* l */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : l
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x03,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x40,0xC0,0x40,0x40,0x40,0x40,0x40,0x40,0xE0,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* m */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : m
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x09,0x0E,0x02,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5A,0x00,0xED,0x00,
0x49,0x00,0x49,0x00,0x49,0x00,0xED,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
/* n */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : n
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0x58,0xE4,0x44,0x44,0x44,0xEE,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* o */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : o
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0x38,0x44,0x44,0x44,0x44,0x38,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* p */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : p
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0x58,0xE4,0x44,0x44,0x64,0x58,0x40,0x40,0xE0,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* q */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : q
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0x34,0x4C,0x44,0x44,0x4C,0x34,0x04,0x04,0x0E,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* r */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : r
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x04,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0x50,0xE0,0x40,0x40,0x40,0xE0,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* s */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : s
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x06,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0x38,0x48,0x60,0x18,0x48,0x70,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* t */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : t
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x04,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x40,0x40,0xE0,0x40,0x40,0x40,0x50,0x60,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* u */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : u
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0xCC,0x44,0x44,0x44,0x4E,0x34,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* v */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : v
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0xEE,0x44,0x28,0x28,0x10,0x10,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* w */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : w
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x09,0x0E,0x02,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xDD,0x80,0x49,0x00,
0x4A,0x00,0x5A,0x00,0x24,0x00,0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* x */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : x
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x05,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0xD8,0x50,0x20,0x20,0x50,0xD8,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* y */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : y
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0xEE,0x44,0x48,0x28,0x28,0x10,0x10,0x20,0xE0,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* z */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : z
;  宽×高（像素）: 13×14
------------------------------------------------------------------------------*/
0x05,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0xF8,0x90,0x20,0x20,0x48,0xF8,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*   */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : 空格
;  宽×高（像素）: 7×14
------------------------------------------------------------------------------*/
0x07,0x0E,0x01,//宽的像素数,高的像素数，宽的字节数，参数设置可选
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

/* ASCII码字符字模检索表 */
static const int8 ascii_char_array[]="0123456789.~!@#$%^&*()_+-=|\\/?:;\"'<>,ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz "; 

/****************************************************************************
* 名称：GUI_PutChar()
* 功能：显示ASCII码，显示值为'0'-'9'、'.'、'+'、'-'及':'(若为其它值，则显示' ')。
* 入口参数： x		指定显示位置，x坐标
*           y		指定显示位置，y坐标
*           ch		要显示的ASCII码值。
* 出口参数：为0时表示操作失败，返回其他值为偏移量。
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
uint8  GUI_PutChar7x14(uint8 x, uint8 y, int8 ch)
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
uint8 GUI_PutString7x14(uint8 x, uint8 y, int8 * str)
{
	uint8 ret, add_len;

	add_len = 0;
	while(1){
		if( (*str)=='\0' ){
			break;
		}
		ret = GUI_PutChar7x14(x, y, *str++);
		x += ret;						
		add_len += ret;
	}

	return add_len;
}



uint8 GUI_PutStringConst7x14(uint8 x,uint8 y , uint8 const *str)
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
			ret =GUI_PutChar7x14(x, y, e);
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


