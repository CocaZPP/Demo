#ifndef __DRIVE_H
#define __DRIVE_H

#include "stm32l1xx.h"
#include "typedef.h"

#define HS1_GPIO		GPIOC
#define HS1_PIN		GPIO_Pin_2

#define LCD_POWER_EN_GPIO		GPIOC
#define LCD_POWER_EN_PIN		GPIO_Pin_4


//M5311IO控制引脚
#define M5311_POWER_EN_GPIO		GPIOB
#define M5311_POWER_EN_PIN		GPIO_Pin_5

#define M5311_RST_GPIO				GPIOB
#define M5311_RST_PIN			GPIO_Pin_3

#define M5311_WAKE_GPIO				GPIOB
#define M5311_WAKE_PIN			GPIO_Pin_6

#define M5311_PMSIN_GPIO				GPIOB
#define M5311_PMSIN_PIN			GPIO_Pin_8
//器件电源控制
#define BUZZER_EN_GPIO		GPIOB
#define BUZZER_EN_PIN		GPIO_Pin_9

#define BTDE_EN_GPIO		GPIOC
#define BTDE_EN_PIN		GPIO_Pin_14

#define HBZ_EN_GPIO		GPIOC
#define HBZ_EN_PIN		GPIO_Pin_15

#define HOUT_EN_GPIO		GPIOA
#define HOUT_EN_PIN		GPIO_Pin_0

//adc检测电量
#define AD_IN_GPIO		GPIOA
#define BATT_DE_PIN		GPIO_Pin_1


void delay_ms(unsigned int ms);
void delay_us(unsigned int ms);

void Init_LCD_Power(void);
void Set_LCD_Power(void);
void Clr_LCD_Power(void);

void Buzzer_50ms(void);
void Beep50ms_Time(int times,int time );
void Buzzer_1000ms(void);

void Set_BTDE_Power(void);
void Clr_BTDE_Power(void);
void Set_HBZ_Power(void);
void Clr_HBZ_Power(void);
void H_OUT_Init(void);
void Init_HS1(void);
void I2C_Set_Input(void);
	
void ADC1_Init(uint8 Channel);
void Close_ADC1(void);
void Get_Vref(void);
int8 Get_Temperature(void);
uint8 Get_Battery(void);
void ADC_IO_Set_Input(void);
void OLED_IO_Set_Input(void);
void CC2500_GPIO_Set_Input(void);
void KEY_IO_Set_Input(void);
void Init_GPIO(void);
void Init_Unused_GPIO(void);

void FLASH_Save_Para_Encode(uint8 * p, uint16 addr_offset, uint16 len);
uint8 FLASH_Get_Para_Decode(uint8 * p, uint16 addr_offset, uint16 len);


void Init_T(void);
void T_Send_Signal(void);
void T_IO_Set_Input(void);

void PeriphClock_Initialize(void);
void RCC_Configuration(void);
void NVIC_Initialize(void);
void StopRTCLSIMode_Close(void);
void SysTickConfig(void);

void TIM3_Int_Init(u16 arr,u16 psc,FunctionalState TimState);

#endif


