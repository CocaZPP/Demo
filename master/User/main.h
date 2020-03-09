/**
  ******************************************************************************
  * @file    Project/STM32L1xx_StdPeriph_Templates/main.h 
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    16-May-2014
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h> 
#include <float.h>
#include <assert.h>
#include <ctype.h>

#include "rtl.h"
#include "stm32l1xx.h"
#include "typedef.h"
#include "Usart.h"
#include "Key.h"
#include "LED_Drive.h"
#include "Drive.h"
#include "display.h"
#include "Fonts_conf.h"
#include "data.h"
#include "FP_Menu.h"
#include "Menu.h"
#include "Flash_map.h"
#include "stm32l1xx_ulp_modes.h"
#include "SI24R1.h"
#include "M5311.h"
#include "TMP112.h"
#include "OPT3001.h"
/*********DEBUG 用完请关闭****************/
//#define DEBUG
/*********************************/
#define RTC_MODE




//#define KEY_NONE	0xff
#define KEY_UP		0x01
#define KEY_DOWN	0x02
#define KEY_LEFT	0x04
#define KEY_RIGHT	0x08
#define KEY_CANCEL	0x10
#define KEY_ENTER		0x20
#define KEY_TWO		(KEY_UP&KEY_DOWN)


//报警类型
#define ALARM_TYPE_SMOKE		0//烟感报警
#define ALARM_TYPE_TEMP		1//主机温度报警
#define ALARM_TYPE_WATER		2//水位报警
#define ALARM_TYPE_MOVE_MODULE		3//终端被非法移动
#define ALARM_TYPE_TEMP_MODULE		4//测温模块高温报警
#define ALARM_TYPE_GAS		5//气体报警
#define ALARM_TYPE_TEMP_IR		6//温度模块光电报警
#define ALARM_TYPE_IR		7//模块光电报警
#define ALARM_TYPE_SHAKE_LITTLE		8//终端模块连续小震动
#define ALARM_TYPE_SHAKE_BIG		9//终端模块大的震动
#define ALARM_TYPE_COM		10//电缆孔监控器无法通讯



#define DEVICE_TYPE				0xd0
#define DEVICE_TYPE_TEMP		0xd1
#define DEVICE_TYPE_MOVE		0xd2
#define DEVICE_TYPE_WATER		0xd3
#define DEVICE_TYPE_SMOKE		0xd4
#define DEVICE_TYPE_MOVE2		0xd6

#define COM_START		0xaa
#define COM_STOP		0x55


/* Exported types ------------------------------------------------------------*/
typedef enum{
	rtos_run = 0,
	rtos_sleep
}RtosMode;//运行状态

//FOR RTOS
#define EVT_ALARM_HAPPEN       	0x0001	//发生报警
#define EVT_EXT_WAKEUP       	0x0002	//外部磁体唤醒
#define EVT_KEY_READY       	0x0004	//按键事件
#define EVT_DIS_UPDATE      	0x0008	//显示刷新
#define EVT_USART_DATA_READY    0x0010	//串口数据接收
#define EVT_NET_READY    		0x0020	//NET发送数据




/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

extern OS_TID tsk_main, tsk_RfReadSensor, tsk_Net;
extern RtosMode rtosRunMode;

uint32_t GetLSIFrequency(void);

extern  void RTC_AlarmConfig(void);
extern void GotoUploadApp();



#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
