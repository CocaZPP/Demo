#ifndef _FONTS_CONF_H_
#define _FONTS_CONF_H_

#include "main.h"

#define FONT6x7_EN		1
#define FONT7x14_EN		1
#define FONT8x14_EN		0
#define FONT10x16_EN	0
#define FONT12x24_EN	0
#define FONT14x28_EN	0
#define PIC_DATA_EN		1
#define FONT14x14_EN	1
#define FONT16x24_EN	0

#if FONT6x7_EN==1
#include "font6x7.h"	
#endif

#if FONT7x14_EN==1
#include "font7x14.h"
#endif

#if FONT8x14_EN==1
#include "font8x14.h"
#endif

#if FONT10x16_EN==1
#include "font10x16.h"
#endif

#if FONT12x24_EN==1
#include "font12x24.h"
#endif

#if FONT14x28_EN==1
#include "font14x28.h"
#endif

#if PIC_DATA_EN==1
#include "pic.h"
#endif

#if FONT14x14_EN ==1
#include "font14x14.h"
#endif

#if FONT16x24_EN ==1
#include "font16x24.h"
#endif

#endif

