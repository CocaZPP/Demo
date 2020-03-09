#include "main.h"
#include "fonts_conf.h"

#if  FONT14x14_EN==1

#define FONT14X14_NUM	99
#define FONT14X14_SIZE	28
/*宋体 ，自动大小，14x14，常规，五号
取模软件(字模3,取码方式)  横向取模，字节正序
*/
// 取模软件(PCtoLCD2002) 阴码,逐行,顺向(宋体,等比14x14)
uint8 const FONT14x14_TAB[FONT14X14_NUM*FONT14X14_SIZE]=
{

	/*--  文字:  ℃  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x60,0x00,0x90,0x00,0x97,0xE8,0x68,0x18,0x10,0x08,0x10,0x08,0x10,0x00,0x10,0x00,
	0x10,0x00,0x10,0x00,0x10,0x08,0x08,0x10,0x07,0xE0,0x00,0x00,
	
	/*--  文字:  电  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x02,0x00,0x02,0x00,0x02,0x00,0x7F,0xF0,0x42,0x10,0x42,0x10,0x7F,0xF0,0x42,0x10,
	0x42,0x10,0x7F,0xF0,0x42,0x00,0x02,0x08,0x02,0x08,0x01,0xF8,
	
	/*--  文字:  力  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0xFF,0xF0,0x04,0x10,0x08,0x10,0x08,0x10,
	0x08,0x10,0x10,0x10,0x10,0x10,0x20,0x10,0x40,0x20,0x80,0xC0,
	
	/*--  文字:  通  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x47,0xF0,0x21,0x20,0x20,0xC0,0x07,0xF0,0x04,0x90,0xE4,0x90,0x27,0xF0,0x24,0x90,
	0x24,0x90,0x27,0xF0,0x24,0x90,0x24,0xB0,0x50,0x00,0x8F,0xF8,
	
	/*--  文字:  道  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x04,0x10,0x42,0x20,0x20,0x00,0x2F,0xF8,0x02,0x00,0x07,0xF0,0xE4,0x10,0x27,0xF0,
	0x24,0x10,0x27,0xF0,0x24,0x10,0x27,0xF0,0x50,0x00,0x8F,0xF8,
	
	/*--  文字:  监  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x08,0x80,0x48,0x80,0x48,0xF8,0x49,0x00,0x4A,0x40,0x48,0x20,0x08,0x20,0x00,0x00,
	0x3F,0xE0,0x25,0x20,0x25,0x20,0x25,0x20,0x25,0x20,0xFF,0xF8,
	
	/*--  文字:  控  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x21,0x00,0x20,0x80,0x27,0xF8,0xF4,0x08,0x21,0x20,0x22,0x10,0x24,0x08,0x30,0x00,
	0xE3,0xF0,0x20,0x80,0x20,0x80,0x20,0x80,0x20,0x80,0xE7,0xF8,
	
	/*--  文字:  编  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x20,0x80,0x20,0x40,0x4B,0xF8,0x4A,0x08,0xF2,0x08,0x13,0xF8,0x22,0x00,0x43,0xF8,
	0xFA,0xA8,0x06,0xA8,0x03,0xF8,0x1A,0xA8,0xE2,0xA8,0x02,0x18,
	
	/*--  文字:  号  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x3F,0xE0,0x20,0x20,0x20,0x20,0x3F,0xE0,0x00,0x00,0x00,0x00,0xFF,0xF8,0x08,0x00,
	0x10,0x00,0x3F,0xE0,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0xC0,
	
	/*--  文字:  水  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x10,0x7B,0x20,0x0B,0x40,0x0A,0x80,0x12,0x80,
	0x12,0x40,0x22,0x20,0x42,0x10,0x82,0x08,0x02,0x00,0x0E,0x00,
	
	/*--  文字:  位  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x11,0x00,0x10,0x80,0x10,0x80,0x27,0xF0,0x20,0x00,0x60,0x20,0xA4,0x20,0x24,0x20,
	0x22,0x20,0x22,0x40,0x22,0x40,0x20,0x40,0x20,0x80,0x2F,0xF8,
	
	/*--  文字:  报  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x20,0x00,0x23,0xF0,0x22,0x10,0xFA,0x10,0x22,0x70,0x22,0x00,0x2B,0xF0,0x32,0x90,
	0xE2,0x90,0x22,0xA0,0x22,0x40,0x22,0xA0,0x23,0x10,0xE2,0x08,
	
	/*--  文字:  警  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x24,0x40,0x7E,0xF8,0x25,0x10,0x7E,0x90,0xAA,0x60,0x3A,0x98,0x06,0x00,0xFF,0xF8,
	0x00,0x00,0x3F,0xE0,0x00,0x00,0x3F,0xE0,0x20,0x20,0x3F,0xE0,
	
	/*--  文字:  正  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x00,0x00,0x7F,0xF0,0x02,0x00,0x02,0x00,0x02,0x00,0x22,0x00,0x22,0x00,0x23,0xE0,
	0x22,0x00,0x22,0x00,0x22,0x00,0x22,0x00,0x22,0x00,0xFF,0xF8,
	
	/*--  文字:  常  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x02,0x00,0x22,0x20,0x12,0x40,0xFF,0xF8,0x80,0x08,0x1F,0xC0,0x10,0x40,0x1F,0xC0,
	0x02,0x00,0x7F,0xF0,0x42,0x10,0x42,0x10,0x42,0x70,0x02,0x00,
	
	/*--  文字:  温  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x07,0xE0,0x44,0x20,0x24,0x20,0x07,0xE0,0x84,0x20,0x44,0x20,0x07,0xE0,0x20,0x00,
	0x2F,0xF0,0x4A,0x50,0x4A,0x50,0x8A,0x50,0x8A,0x50,0x1F,0xF8,
	
	/*--  文字:  度  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x02,0x00,0x01,0x00,0x3F,0xF8,0x24,0x20,0x3F,0xF8,0x24,0x20,0x27,0xE0,0x20,0x00,
	0x2F,0xF0,0x24,0x20,0x22,0x40,0x41,0x80,0x46,0x60,0x98,0x18,
	
	/*--  文字:  设  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x40,0x00,0x23,0xE0,0x22,0x20,0x02,0x20,0x02,0x20,0xE4,0x18,0x28,0x00,0x27,0xF0,
	0x22,0x10,0x22,0x20,0x29,0x40,0x30,0x80,0x23,0x60,0x0C,0x18,
	
	/*--  文字:  置  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x7F,0xF0,0x48,0x90,0x48,0x90,0x7F,0xF0,0x02,0x00,0x7F,0xF0,0x02,0x00,0x3F,0xE0,
	0x20,0x20,0x20,0x20,0x22,0x20,0x22,0x20,0x22,0x20,0xFF,0xF8,
	
	/*--  文字:  查  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x02,0x00,0x02,0x00,0xFF,0xF8,0x0A,0x80,0x12,0x40,0x22,0x20,0xC0,0x18,0x3F,0xE0,
	0x20,0x20,0x3F,0xE0,0x20,0x20,0x3F,0xE0,0x00,0x00,0xFF,0xF8,
	
	/*--  文字:  看  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x00,0xF0,0x7F,0x00,0x02,0x00,0x3F,0xE0,0x04,0x00,0xFF,0xF8,0x08,0x00,0x1F,0xE0,
	0x30,0x20,0x5F,0xE0,0x90,0x20,0x1F,0xE0,0x10,0x20,0x1F,0xE0,
	
	/*--  文字:  服  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x00,0x00,0x7B,0xF0,0x4A,0x10,0x4A,0x10,0x4A,0x70,0x7A,0x00,0x4B,0xF0,0x4A,0x90,
	0x7A,0x90,0x4A,0xA0,0x4A,0x40,0x4A,0xA0,0x4B,0x10,0x9A,0x08,
	
	/*--  文字:  务  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x08,0x00,0x1F,0xE0,0x30,0x40,0x48,0x80,0x07,0x00,0x18,0xC0,0xE0,0x38,0x04,0x00,
	0x7F,0xE0,0x04,0x20,0x08,0x20,0x10,0x20,0x20,0x20,0x40,0xC0,
	
	/*--  文字:  器  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x7D,0xF0,0x45,0x10,0x45,0x10,0x7D,0xF0,0x00,0x40,0x02,0x20,0xFF,0xF8,0x08,0x80,
	0x30,0x60,0xC0,0x18,0x7D,0xF0,0x45,0x10,0x45,0x10,0x7D,0xF0,
	
	/*--  文字:  模  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x22,0x20,0x22,0x20,0x27,0xF8,0xF2,0x20,0x27,0xF0,0x24,0x10,0x77,0xF0,0x6C,0x10,
	0xA7,0xF0,0x20,0x80,0x2F,0xF8,0x21,0x40,0x22,0x20,0x2C,0x18,
	
	/*--  文字:  块  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x21,0x00,0x21,0x00,0x27,0xF0,0x21,0x10,0xF9,0x10,0x21,0x10,0x21,0x10,0x2F,0xF8,
	0x21,0x40,0x39,0x40,0xE2,0x20,0x02,0x20,0x04,0x10,0x08,0x08,
	
	/*--  文字:  清  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x00,0x80,0x47,0xF0,0x20,0x80,0x17,0xF0,0x00,0x80,0x8F,0xF8,0x40,0x00,0x17,0xF0,
	0x14,0x10,0x27,0xF0,0x24,0x10,0x47,0xF0,0x44,0x10,0x04,0x70,
	
	/*--  文字:  除  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x00,0x80,0xF0,0x80,0x91,0x40,0x92,0x20,0xA4,0x10,0xAB,0xE8,0x90,0x80,0x90,0x80,
	0x97,0xF0,0x90,0x80,0xE4,0x90,0x84,0x88,0x88,0x88,0x83,0x80,
	
	/*--  文字:  备  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x08,0x00,0x1F,0xE0,0x30,0x40,0x48,0x80,0x07,0x00,0x18,0xC0,0xE0,0x38,0x3F,0xE0,
	0x22,0x20,0x22,0x20,0x3F,0xE0,0x22,0x20,0x22,0x20,0x3F,0xE0,
	
	/*--  文字:  信  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x11,0x00,0x10,0x80,0x2F,0xF8,0x20,0x00,0x67,0xF0,0xA0,0x00,0x27,0xF0,0x20,0x00,
	0x27,0xF0,0x24,0x10,0x24,0x10,0x24,0x10,0x27,0xF0,0x24,0x10,
	
	/*--  文字:  息  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x04,0x00,0x08,0x00,0x3F,0xE0,0x20,0x20,0x3F,0xE0,0x20,0x20,0x3F,0xE0,0x20,0x20,
	0x3F,0xE0,0x02,0x00,0x11,0x10,0x51,0x08,0x50,0x48,0x8F,0xC0,

	/*--  文字:  菜  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x10,0x40,0xFF,0xF8,0x10,0x40,0x00,0xF0,0x7F,0x20,0x24,0x20,0x12,0x40,0x02,0x00,
	0xFF,0xF8,0x07,0x00,0x0A,0x80,0x32,0x60,0xC2,0x18,0x02,0x00,
	
	/*--  文字:  单  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x10,0x40,0x08,0x80,0x3F,0xE0,0x22,0x20,0x22,0x20,0x3F,0xE0,0x22,0x20,0x22,0x20,
	0x3F,0xE0,0x02,0x00,0x02,0x00,0xFF,0xF8,0x02,0x00,0x02,0x00,
	
	/*--  文字:  厂  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x00,0x00,0x3F,0xF8,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,
	0x20,0x00,0x20,0x00,0x20,0x00,0x40,0x00,0x40,0x00,0x80,0x00,
	
	/*--  文字:  家  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x02,0x00,0xFF,0xF8,0x80,0x08,0x00,0x00,0x7F,0xF0,0x0C,0x00,0x12,0x20,0x65,0x40,
	0x09,0x80,0x33,0x40,0xC5,0x40,0x19,0x20,0xE1,0x18,0x06,0x00,
	
	/*--  文字:  后  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x00,0x70,0x3F,0x80,0x20,0x00,0x20,0x00,0x3F,0xF8,0x20,0x00,0x20,0x00,0x2F,0xF0,
	0x28,0x10,0x28,0x10,0x48,0x10,0x48,0x10,0x8F,0xF0,0x08,0x10,
	
	/*--  文字:  台  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x04,0x00,0x04,0x00,0x08,0x40,0x10,0x20,0x20,0x10,0x7F,0xF8,0x00,0x08,0x00,0x00,
	0x3F,0xF0,0x20,0x10,0x20,0x10,0x20,0x10,0x3F,0xF0,0x20,0x10,
	
	/*--  文字:  是  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x3F,0xE0,0x20,0x20,0x3F,0xE0,0x20,0x20,0x3F,0xE0,0x00,0x00,0xFF,0xF8,0x02,0x00,
	0x22,0x00,0x23,0xE0,0x22,0x00,0x22,0x00,0x52,0x00,0x8F,0xF8,
	
	/*--  文字:  否  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x00,0x00,0x7F,0xF0,0x02,0x00,0x06,0x00,0x0A,0xC0,0x32,0x30,0xC2,0x08,0x02,0x00,
	0x3F,0xE0,0x20,0x20,0x20,0x20,0x20,0x20,0x3F,0xE0,0x20,0x20,
	
    
	/*--  文字:  确  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x01,0x00,0x01,0xF0,0xFA,0x10,0x24,0x20,0x23,0xF8,0x42,0x48,0x7A,0x48,0xCB,0xF8,
	0x4A,0x48,0x4A,0x48,0x4B,0xF8,0x7A,0x48,0x42,0x48,0x04,0x18,
	
	/*--  文字:  认  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x40,0x80,0x20,0x80,0x20,0x80,0x00,0x80,0xE0,0x80,0x20,0x80,0x20,0x80,0x21,0x40,
	0x21,0x40,0x29,0x40,0x32,0x20,0x22,0x20,0x04,0x10,0x08,0x08,
	
	/*--  文字:  取  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x00,0x00,0xFC,0x00,0x4B,0xF0,0x49,0x10,0x79,0x10,0x49,0x10,0x49,0x10,0x78,0xA0,
	0x48,0xA0,0x4E,0x40,0xF8,0x40,0x08,0xA0,0x09,0x10,0x0A,0x08,
	
	/*--  文字:  消  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x00,0x80,0x44,0x90,0x22,0xA0,0x10,0x80,0x07,0xF0,0x84,0x10,0x44,0x10,0x17,0xF0,
	0x14,0x10,0x24,0x10,0x27,0xF0,0x44,0x10,0x44,0x10,0x04,0x70,

	
	/*--  文字:  时  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x00,0x20,0x00,0x20,0xF0,0x20,0x97,0xF8,0x90,0x20,0x90,0x20,0xF2,0x20,0x91,0x20,
	0x91,0x20,0x90,0x20,0xF0,0x20,0x90,0x20,0x00,0x20,0x00,0xE0,
	
	/*--  文字:  间  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x20,0x00,0x17,0xF8,0x10,0x08,0x40,0x08,0x4F,0xC8,0x48,0x48,0x48,0x48,0x4F,0xC8,
	0x48,0x48,0x48,0x48,0x4F,0xC8,0x40,0x08,0x40,0x08,0x40,0x38,
	
	/*--  文字:  隔  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x00,0x00,0x7B,0xF8,0x48,0x00,0x49,0xF0,0x51,0x10,0x51,0xF0,0x48,0x00,0x4B,0xF8,
	0x4A,0xA8,0x4A,0x48,0x73,0xF8,0x42,0x48,0x42,0x48,0x42,0x18,
	
	/*--  文字:  上  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x03,0xF0,0x02,0x00,0x02,0x00,
	0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0xFF,0xF8,
	
	/*--  文字:  传  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x10,0x80,0x10,0x80,0x17,0xF0,0x20,0x80,0x21,0x00,0x6F,0xF8,0xA1,0x00,0x22,0x00,
	0x27,0xF0,0x20,0x10,0x20,0x20,0x21,0x40,0x20,0x80,0x20,0x40,
	
	/*--  文字:  启  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x04,0x00,0x02,0x00,0x3F,0xF0,0x20,0x10,0x20,0x10,0x3F,0xF0,0x20,0x00,0x20,0x00,
	0x2F,0xF0,0x28,0x10,0x48,0x10,0x48,0x10,0x8F,0xF0,0x08,0x10,
	
	/*--  文字:  动  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x00,0x80,0x78,0x80,0x00,0x80,0x03,0xF8,0x00,0x88,0xFC,0x88,0x20,0x88,0x20,0x88,
	0x48,0x88,0x44,0x88,0xFD,0x08,0x05,0x08,0x02,0x08,0x04,0x30,
	
	/*--  文字:  停  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x10,0x80,0x1F,0xF8,0x10,0x00,0x27,0xF0,0x24,0x10,0x67,0xF0,0xA0,0x00,0x2F,0xF8,
	0x28,0x08,0x27,0xF0,0x20,0x40,0x20,0x40,0x20,0x40,0x21,0xC0,
	
	/*--  文字:  止  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x01,0x00,0x01,0x00,0x01,0x00,0x11,0x00,0x11,0x00,0x11,0xF0,0x11,0x00,0x11,0x00,
	0x11,0x00,0x11,0x00,0x11,0x00,0x11,0x00,0x11,0x00,0xFF,0xF8,

	/*--  文字:  采  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x00,0xF0,0x7F,0x00,0x04,0x20,0x22,0x20,0x10,0x40,0x02,0x00,0x02,0x00,0xFF,0xF8,
	0x07,0x00,0x0A,0x80,0x12,0x40,0x22,0x20,0xC2,0x18,0x02,0x00,
	
	/*--  文字:  样  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x24,0x10,0x22,0x20,0x20,0x00,0xF7,0xF0,0x20,0x80,0x20,0x80,0x77,0xF0,0x68,0x80,
	0xA0,0x80,0x2F,0xF8,0x20,0x80,0x20,0x80,0x20,0x80,0x20,0x80,

	/*--  文字:  光  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x02,0x00,0x42,0x10,0x22,0x20,0x12,0x40,0x02,0x00,0xFF,0xF8,0x08,0x80,0x08,0x80,
	0x08,0x80,0x08,0x80,0x10,0x80,0x10,0x88,0x20,0x88,0x40,0x78,
	
	/*--  文字:  纤  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x20,0x38,0x23,0xC0,0x48,0x40,0x48,0x40,0xF0,0x40,0x10,0x40,0x23,0xF8,0x40,0x40,
	0xF8,0x40,0x00,0x40,0x00,0x40,0x18,0x40,0xE0,0x40,0x00,0x40,

	/*--  文字:  功  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x01,0x00,0x01,0x00,0xF9,0x00,0x23,0xF0,0x21,0x10,0x21,0x10,0x21,0x10,0x21,0x10,
	0x21,0x10,0x39,0x10,0xC2,0x10,0x02,0x10,0x04,0x10,0x08,0x60,
	
	/*--  文字:  能  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x10,0x80,0x20,0x98,0x44,0xE0,0xFE,0x88,0x02,0x88,0x00,0x78,0x7C,0x00,0x44,0x88,
	0x7C,0x90,0x44,0xE0,0x7C,0x80,0x44,0x88,0x44,0x88,0x4C,0x78,
	
	/*--  文字:  使  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x10,0x80,0x10,0x80,0x2F,0xF8,0x20,0x80,0x6F,0xF8,0xA8,0x88,0x28,0x88,0x2F,0xF8,
	0x24,0x80,0x22,0x80,0x21,0x00,0x22,0x80,0x24,0x60,0x28,0x18,
	
	/*--  文字:  开  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x7F,0xF0,0x10,0x40,0x10,0x40,0x10,0x40,0x10,0x40,0x10,0x40,0xFF,0xF8,0x10,0x40,
	0x10,0x40,0x10,0x40,0x20,0x40,0x20,0x40,0x40,0x40,0x80,0x40,
	
	/*--  文字:  关  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x10,0x40,0x08,0x40,0x08,0x80,0x7F,0xF0,0x02,0x00,0x02,0x00,0x02,0x00,0xFF,0xF8,
	0x05,0x00,0x05,0x00,0x08,0x80,0x10,0x40,0x20,0x20,0xC0,0x18,
	
	/*--  文字:  闭  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x40,0x00,0x2F,0xF8,0x00,0x08,0x40,0x88,0x40,0x88,0x5F,0xE8,0x41,0x88,0x42,0x88,
	0x44,0x88,0x48,0x88,0x50,0x88,0x43,0x88,0x40,0x08,0x40,0x38,
	
	/*--  文字:  绑  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x22,0x00,0x22,0x78,0x4F,0x48,0x52,0x48,0xF2,0x48,0x27,0x50,0x42,0x50,0xF2,0x48,
	0x0F,0x48,0x02,0x48,0x32,0x48,0xC2,0x70,0x04,0x40,0x08,0x40,
	
	/*--  文字:  定  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x04,0x00,0x02,0x00,0xFF,0xF8,0x80,0x08,0x00,0x00,0x3F,0xE0,0x02,0x00,0x02,0x00,
	0x22,0x00,0x23,0xE0,0x22,0x00,0x22,0x00,0x52,0x00,0x8F,0xF8,
	
	/*--  文字:  系  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x01,0xE0,0x7E,0x00,0x04,0x00,0x08,0x40,0x10,0x80,0x3F,0x00,0x04,0x40,0x18,0x20,
	0x7F,0xF0,0x02,0x10,0x12,0x40,0x22,0x20,0x42,0x10,0x0E,0x00,
	
	/*--  文字:  统  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x21,0x00,0x20,0x80,0x40,0x00,0x97,0xF8,0xF1,0x00,0x21,0x20,0x42,0x10,0x87,0xF0,
	0xF1,0x50,0x01,0x40,0x02,0x40,0x32,0x48,0xC4,0x48,0x08,0x38,
	
	/*--  文字:  测  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x00,0x08,0x4F,0x88,0x28,0x88,0x0A,0xA8,0x8A,0xA8,0x4A,0xA8,0x0A,0xA8,0x2A,0xA8,
	0x2A,0xA8,0x42,0x28,0x45,0x08,0x84,0x88,0x88,0x88,0x10,0x38,
	
	/*--  文字:  移  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x00,0x80,0x18,0x80,0xE1,0xE0,0x22,0x20,0x25,0x40,0xF8,0x80,0x21,0x20,0x36,0x40,
	0x68,0xF8,0x61,0x10,0xA6,0xA0,0x20,0x40,0x21,0x80,0x26,0x00,
	
	/*--  文字:  检  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x20,0x80,0x20,0x80,0x21,0x40,0xF2,0x20,0x24,0x10,0x2B,0xE8,0x70,0x00,0x69,0x10,
	0xA0,0x90,0x24,0x90,0x22,0x20,0x22,0x20,0x20,0x40,0x2F,0xF8,
	
	/*--  文字:  录  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x00,0x00,0x7F,0xE0,0x00,0x20,0x3F,0xE0,0x00,0x20,0xFF,0xF8,0x02,0x00,0x22,0x20,
	0x13,0x40,0x0A,0x80,0x12,0x40,0x22,0x20,0xC2,0x18,0x0E,0x00,
	
	/*--  文字:  入  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x08,0x00,0x04,0x00,0x04,0x00,0x02,0x00,0x02,0x00,0x05,0x00,0x05,0x00,0x08,0x80,
	0x08,0x80,0x10,0x40,0x10,0x40,0x20,0x20,0x40,0x10,0x80,0x08,
	
	/*--  文字:  删  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x00,0x08,0x3B,0x88,0x2A,0x88,0x2A,0xA8,0x2A,0xA8,0x2A,0xA8,0x7F,0xE8,0x2A,0xA8,
	0x2A,0xA8,0x2A,0xA8,0x2A,0x88,0x2A,0x88,0x5A,0x88,0x85,0xB8,
	
	/*--  文字:  列  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x00,0x08,0x7E,0x08,0x10,0x08,0x10,0x48,0x1E,0x48,0x22,0x48,0x22,0x48,0x52,0x48,
	0x8C,0x48,0x04,0x48,0x08,0x08,0x10,0x08,0x20,0x08,0x40,0x38,
	
	/*--  文字:  表  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x02,0x00,0x02,0x00,0x7F,0xF0,0x02,0x00,0x3F,0xE0,0x02,0x00,0xFF,0xF8,0x05,0x00,
	0x09,0x10,0x18,0xA0,0x28,0x40,0xCA,0x20,0x0C,0x18,0x08,0x00,
	
	/*--  文字:  询  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x42,0x00,0x22,0x00,0x27,0xF8,0x08,0x08,0x07,0xE8,0xE4,0x28,0x24,0x28,0x27,0xE8,
	0x24,0x28,0x24,0x28,0x2F,0xE8,0x34,0x08,0x20,0x08,0x00,0x30,
	
	/*--  文字:  在  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x04,0x00,0x04,0x00,0xFF,0xF8,0x08,0x00,0x10,0x80,0x10,0x80,0x30,0x80,0x57,0xF0,
	0x90,0x80,0x10,0x80,0x10,0x80,0x10,0x80,0x1F,0xF8,0x10,0x00,
	
	/*--  文字:  线  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x20,0xA0,0x20,0x90,0x48,0x80,0x48,0xF0,0xF3,0x80,0x10,0x80,0x20,0xB8,0x43,0xC0,
	0xF8,0x90,0x00,0xA0,0x00,0x48,0x18,0xA8,0xE3,0x18,0x00,0x08,
	
	/*--  文字:  始  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x20,0x80,0x20,0x80,0x21,0x00,0xF9,0x20,0x4A,0x10,0x4F,0xF8,0x48,0x08,0x88,0x00,
	0x4B,0xF0,0x32,0x10,0x12,0x10,0x2A,0x10,0x4B,0xF0,0x82,0x10,
	
	/*--  文字:  按  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x20,0x80,0x20,0x40,0x27,0xF8,0xF4,0x08,0x24,0x88,0x20,0x80,0x27,0xF8,0x31,0x10,
	0xE1,0x10,0x23,0x20,0x20,0xC0,0x20,0xA0,0x21,0x10,0xE6,0x08,
	
	/*--  文字:  键  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x20,0x40,0x20,0x40,0x36,0xF0,0x42,0x50,0x83,0xF8,0x74,0x50,0x26,0xF0,0x22,0x40,
	0xF2,0xF0,0x22,0x40,0x2A,0xF8,0x34,0x40,0x2B,0x40,0x10,0xF8,
	
	/*--  文字:  试  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x40,0x50,0x20,0x48,0x20,0x40,0x0F,0xF8,0x00,0x40,0xE0,0x40,0x27,0x40,0x22,0x40,
	0x22,0x40,0x22,0x20,0x2A,0x28,0x33,0xA8,0x2E,0x18,0x00,0x08,
	
	/*--  文字:  失  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x02,0x00,0x12,0x00,0x12,0x00,0x1F,0xE0,0x22,0x00,0x42,0x00,0x02,0x00,0xFF,0xF8,
	0x05,0x00,0x05,0x00,0x08,0x80,0x10,0x40,0x20,0x20,0xC0,0x18,
	
	/*--  文字:  败  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x01,0x00,0xF9,0x00,0x89,0x00,0xA9,0xF8,0xAA,0x10,0xAD,0x10,0xA9,0x10,0xA9,0x10,
	0xA8,0xA0,0xA8,0xA0,0x20,0x40,0x50,0xA0,0x49,0x10,0x86,0x08,
	
	/*--  文字:  成  --*/
	/*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
	/*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x00,0xA0,0x00,0x90,0x00,0x80,0x7F,0xF8,0x40,0x80,0x40,0x90,0x7C,0x90,0x44,0x90,
	0x44,0xA0,0x44,0xA0,0x44,0x48,0x58,0xA8,0x41,0x18,0x82,0x08,

    
    /*--  文字:  灵  --*/
    /*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
    0x7F,0xE0,0x00,0x20,0x00,0x20,0x3F,0xE0,0x00,0x20,0x00,0x20,0x7F,0xE0,0x02,0x00,
    0x22,0x20,0x22,0x40,0x45,0x00,0x08,0x80,0x30,0x60,0xC0,0x18,
    
    /*--  文字:  敏  --*/
    /*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
    0x20,0x40,0x3E,0x40,0x40,0x40,0xBC,0x78,0x24,0x90,0x34,0x90,0x2D,0x50,0xFE,0x50,
    0x44,0x50,0x54,0x50,0x7E,0x20,0x04,0x20,0x04,0x50,0x18,0x88,
	
    /*--  文字:  版--*/
    /*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x08,0x00,0x48,0x18,0x49,0xE0,0x49,0x00,0x7D,0x00,0x41,0xF0,0x41,0x50,0x79,0x50,
	0x49,0x50,0x49,0x50,0x49,0x20,0x49,0x20,0x4A,0x50,0x8C,0x88,
	
    /*--  文字:  本--*/
    /*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x02,0x00,0x02,0x00,0x02,0x00,0xFF,0xF8,0x07,0x00,0x0A,0x80,0x0A,0x80,0x12,0x40,
	0x22,0x20,0x42,0x10,0x9F,0xC8,0x02,0x00,0x02,0x00,0x02,0x00,

	/*--  文字:  终--*/
    /*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x21,0x00,0x21,0x00,0x41,0xE0,0x92,0x20,0xF5,0x40,0x20,0x80,0x41,0x40,0x82,0x20,
	0xF4,0x18,0x01,0x80,0x00,0x60,0x33,0x00,0xC0,0xC0,0x00,0x20,

	/*--  文字:  端--*/
    /*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/	
	0x20,0x40,0x12,0x48,0x12,0x48,0xFA,0x48,0x03,0xF8,0x08,0x00,0x8B,0xF8,0x48,0x80,
	0x53,0xF8,0x52,0xA8,0x02,0xA8,0x1A,0xA8,0xE2,0xA8,0x02,0x18,

	/*--  文字:  参--*/
    /*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x08,0x00,0x10,0x40,0x3F,0xE0,0x04,0x20,0xFF,0xF8,0x10,0x40,0x21,0x20,0xC6,0x18,
	0x38,0x80,0x01,0x00,0x0E,0x20,0x70,0xC0,0x07,0x00,0xF8,0x00,

	/*--  文字:  数--*/
    /*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x10,0x40,0x92,0x40,0x54,0x40,0xFE,0x78,0x38,0x90,0x54,0x90,0x93,0x50,0x20,0x50,
	0xFC,0x50,0x24,0x50,0x64,0x20,0x18,0x20,0x34,0x50,0xC2,0x88,

	/*--  文字:  烟--*/
    /*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x20,0x00,0x27,0xF0,0x2C,0x10,0xB4,0x90,0xA4,0x90,0xA7,0xF0,0xA4,0x90,0x24,0x90,
	0x25,0x50,0x26,0x30,0x54,0x10,0x54,0x10,0x47,0xF0,0x84,0x10,

	/*--  文字:  感--*/
    /*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x00,0x90,0x7F,0xF8,0x40,0x80,0x5E,0x90,0x40,0x90,0x5E,0xA0,0x52,0x40,0x5E,0xA8,
	0x41,0x18,0x82,0x08,0x04,0x00,0x52,0x10,0x50,0x48,0x8F,0xC8,
	
	/*--  文字:  网--*/
    /*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x00,0x00,0x7F,0xF8,0x40,0x08,0x42,0x28,0x53,0x28,0x4A,0xA8,0x44,0x48,0x44,0x48,
	0x4A,0xA8,0x4A,0xA8,0x51,0x08,0x62,0x08,0x40,0x08,0x40,0x38,

	/*--  文字:  络--*/
    /*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x21,0x00,0x21,0x00,0x41,0xE0,0x92,0x20,0xF5,0x40,0x20,0x80,0x41,0x40,0x82,0x20,
	0xF4,0x18,0x03,0xE0,0x02,0x20,0x32,0x20,0xC3,0xE0,0x02,0x20,
	
	/*--  文字:  热--*/
    /*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x10,0x80,0x10,0x80,0x7B,0xE0,0x10,0xA0,0x18,0xA0,0x72,0xA0,0x11,0x28,0x11,0xA8,
	0x12,0x98,0x74,0x08,0x00,0x00,0x49,0x10,0x44,0x88,0x84,0x88,
    
	/*--  文字:  释--*/
    /*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x0C,0x00,0x73,0xF0,0x11,0x10,0x94,0xA0,0x58,0x40,0x10,0xA0,0xFD,0x18,0x10,0x40,
	0x39,0xF0,0x34,0x40,0x50,0x40,0x53,0xF8,0x90,0x40,0x10,0x40,

	/*--  文字:  限--*/
    /*--  宋体11;  此字体下对应的点阵为：宽x高=14x14   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x14  --*/
	0x00,0x00,0x7B,0xF0,0x4A,0x10,0x4A,0x10,0x53,0xF0,0x52,0x10,0x4A,0x10,0x4B,0xF0,
	0x4A,0x48,0x4A,0x50,0x72,0x20,0x42,0xA0,0x43,0x10,0x42,0x08,
};


uint8 const FONT14X14_INDEX[FONT14X14_NUM][3]=
{  
    "℃","电","力","通","道","监","控","编","号","水",
	"位","报","警","正","常","温","度","设","置","查",
	"看","服","务","器","模","块","清","除","备","信",
	"息","菜","单","厂","家","后","台","是","否","确",
	"认","取","消","时","间","隔","上","传","启","动",
	"停","止","采","样","光","纤","功","能","使","开",
	"关","闭","绑","定","系","统","测","移","检","录",
	"入","删","列","表","询","在","线","始","按","键",
	"试","失","败","成","灵","敏","版","本","终","端",
	"参","数","烟","感","网","络","热","释","限",
};



uint8  GUI_PutHZ14x14(uint8 x, uint8 y, uint16 hz_code)
{
	const uint8 *  font_dat;
	const uint16 * p16;
	uint8 i;
	uint16 t;

	p16 = (uint16 *)FONT14X14_INDEX;
		
	for(i = 0; i < FONT14X14_NUM; i++){
		t = *p16;
		if(t == hz_code){
			break;
		}
		p16 = (uint16 *)(((uint8 *)p16)+3);
	}

	if (i == FONT14X14_NUM){
		return (0);
	}
	
	font_dat = FONT14x14_TAB+i*FONT14X14_SIZE;

	Display_PIC(x, y, 14, 14, font_dat);

	return(14);
}

uint8 GUI_PutStringConst14x14(uint8 x, uint8 y, uint8 const *buf)
{  
	uint8 e;
	uint16 hz;
	const uint8 *p;
	uint8 ret;
	uint8 add_len;

	p = buf;
	add_len = 0;
	while(*p){
		if(*p <= 0x7f){
			e = *p++;
			ret = GUI_PutChar7x14(x, y, e);
		}else{
			hz = *((uint16 *)(p));
			p+=2;
			ret = GUI_PutHZ14x14(x, y, hz);
		}
		
		x += ret;
		add_len += ret;
		
		if(x >= GUI_LCM_XMAX){
			break;
		}
	}
	return add_len;
}

uint8 Get_TxtLength14x14(uint8 const *buf)
{
    uint8 e;
	uint16 hz;
	const uint8 *p;
	uint8 ret;
	uint8 add_len;

	p = buf;
	add_len = 0;
	while(*p){
		if(*p <= 0x7f){
			e = *p++;
			ret =7;
		}else{
			hz = *((uint16 *)(p));
			p+=2;
			ret = 14;
		}
		
		add_len += ret;

	}
	return add_len;
    
}

uint8 GUI_PutString14x14(uint8 x, uint8 y, uint8 *buf)
{
	uint8 e;
	uint16 hz;
	uint8 *p;
	uint8 ret;
	uint8 add_len;

	p = buf;
	add_len = 0;
	
	while(*p){
		if(*p <= 0x7f){
			e = *p++;
			ret = GUI_PutChar7x14(x, y, e);
		}else{
			hz = *((uint16 *)(p));
			p+=2;
			ret = GUI_PutHZ14x14(x, y, hz);
		}
		
		x += ret;
		add_len += ret;
		
		if(x >= GUI_LCM_XMAX){
			break;
		}
	}
	return add_len;
}


uint8 GUI_PutStringConst14x14_7x14(uint8 x, uint8 y, uint8 const *buf)
{  
	uint8 e;
	uint16 hz;
	const uint8 *p;
	uint8 ret;
	uint8 add_len;

	p = buf;
	add_len = 0;
	while(*p){
		if(*p <= 0x7f){
			e = *p++;
			ret = GUI_PutChar7x14(x, y, e);
		}else{
			hz = *((uint16 *)(p));
			p+=2;
			ret = GUI_PutHZ14x14(x, y, hz);
		}
		
		x += ret;
		add_len += ret;
		
		if(x >= GUI_LCM_XMAX){
			break;
		}
	}
	return add_len;
}

#endif
