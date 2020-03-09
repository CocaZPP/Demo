/*
  ******************************************************************************
  * @file    common_typed.h
  * @author
  * @version
  * @date
  * @brief
  ******************************************************************************
  * @copy
  *
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TYPE_DEF_H_
#define _TYPE_DEF_H_
#include <string.h>
#include <stdarg.h>

#include "math.h"
#include "stdio.h"
#include "misc.h"


#include "stm32l1xx.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_spi.h"
#include "stm32l1xx_rcc.h"
#include "stm32l1xx_rtc.h"
#include "stm32l1xx_usart.h"
#include "stm32l1xx_dma.h"
#include "stm32l1xx_adc.h"
#include "stm32l1xx_exti.h"
#include "stm32l1xx_syscfg.h"
#include "stm32l1xx_flash.h"
#include "stm32l1xx_tim.h"
#include "stm32l1xx_iwdg.h"
#include "stm32l1xx_pwr.h"
#include "stm32l1xx_dbgmcu.h"

#ifdef __cplusplus
extern "C" {
#endif


/* These types must be 8-bit integer */
typedef char			int8;
typedef unsigned char	uint8;
typedef unsigned char	u8;

/* These types must be 16-bit integer */
typedef short			int16;
typedef unsigned short		uint16;
typedef unsigned short		u16;

/* These types must be 32-bit integer */
typedef long			int32;
typedef unsigned long	uint32;
typedef unsigned long	u32;

typedef unsigned long long	uint64;


#ifdef __cplusplus
}
#endif

/* Exported constants --------------------------------------------------------*/
/* Exported variable ---------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
#endif
/************************* *****END OF FILE************************************/

