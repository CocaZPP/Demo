#include "Drive.h"
#include "main.h"
#include "math.h"
#include "TMP112.h"
extern Test_M5311 testM5311;//测试M5311

void delay_ms(unsigned int ms)
{                         
	volatile unsigned int a;
	while(ms)
	{
		a=3600;
		while(a--);
		ms--;
	}
	return;
}

//延时us           
void delay_us(unsigned int Nus)
{ 
	int i,j;
	for(i=0;i<Nus;i++){
		for(j=0;j<3;j++){
			;
		}
	}
}


void Set_LCD_Power(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = LCD_POWER_EN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(LCD_POWER_EN_GPIO, &GPIO_InitStructure);
	GPIO_SetBits(LCD_POWER_EN_GPIO,LCD_POWER_EN_PIN);
}

void Clr_LCD_Power(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = LCD_POWER_EN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(LCD_POWER_EN_GPIO, &GPIO_InitStructure);
	I2C_Set_Input();
}

void Clr_Buzzer_Power(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = BUZZER_EN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(BUZZER_EN_GPIO, &GPIO_InitStructure);
}

void Buzzer_50ms(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = BUZZER_EN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(BUZZER_EN_GPIO, &GPIO_InitStructure);

	GPIO_SetBits(BUZZER_EN_GPIO,BUZZER_EN_PIN);
	delay_ms(50);
	Clr_Buzzer_Power();	

}
void Beep50ms_Time(int times,int time )
{
		while(times--)
	{
		Buzzer_50ms();
		delay_ms(time);
	}
}

void Buzzer_1000ms(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = BUZZER_EN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(BUZZER_EN_GPIO, &GPIO_InitStructure);

	GPIO_SetBits(BUZZER_EN_GPIO,BUZZER_EN_PIN);
	os_dly_wait(1000);
	Clr_Buzzer_Power();	
}
void Set_BTDE_Power(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = BTDE_EN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(BTDE_EN_GPIO, &GPIO_InitStructure);
	GPIO_SetBits(BTDE_EN_GPIO,BTDE_EN_PIN);
}

void Clr_BTDE_Power(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = BTDE_EN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(BTDE_EN_GPIO, &GPIO_InitStructure);
}
void Set_HBZ_Power(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = HBZ_EN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(HBZ_EN_GPIO, &GPIO_InitStructure);
	GPIO_SetBits(HBZ_EN_GPIO,HBZ_EN_PIN);
}

void Clr_HBZ_Power(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = HBZ_EN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(HBZ_EN_GPIO, &GPIO_InitStructure);
}
void H_OUT_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = HOUT_EN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(HOUT_EN_GPIO, &GPIO_InitStructure);
}

void Init_HS1(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;
//	EXTI_InitTypeDef   EXTI_InitStructure;
//	NVIC_InitTypeDef   NVIC_InitStructure;

	//EXTI_ClearITPendingBit(EXTI_Line2);
	
	/* Configure PC2 pin as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Pin = HS1_PIN;
	GPIO_Init(HS1_GPIO, &GPIO_InitStructure);

	/* Connect EXTI2 Line to PC2 pin */
	//SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource2);

	/* Configure EXTI2 line */
	//EXTI_InitStructure.EXTI_Line = EXTI_Line2;
	//EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	//EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
	//EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	//EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI2 Interrupt to the lowest priority */
	//NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	//NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	//NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//NVIC_Init(&NVIC_InitStructure);
	
}

uint8  flag_ADC = 0;

/**
  * @brief  DMA1_Channel1中断服务函数
  * @param  无
  * @retval 无
  */
void DMA1_Channel1_IRQHandler()  
{  
	/*判断DMA传输完成中断*/ 
	if(DMA_GetITStatus(DMA1_IT_TC1) != RESET)                        
	{ 
		flag_ADC = 1;
	}	
	/*清除DMA中断标志位*/	
	DMA_ClearITPendingBit(DMA1_IT_TC1);                      
}  

#define ADC1_DR_ADDRESS    ((uint32_t)0x40012458)

__IO uint16_t ADC_ConvertedValue[30];

//Channel  0温度 1电量
void ADC1_Init(uint8 Channel){
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

#if 1
	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;

	/*------------------------ DMA1 configuration ------------------------------*/
	/* Enable DMA1 clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	/* DMA1 channel1 configuration */
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_ADDRESS;//
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConvertedValue;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 30;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);

	
	/*清除一次DMA中断标志*/
	DMA_ClearITPendingBit(DMA1_IT_TC1); 

	DMA_ITConfig(DMA1_Channel1, DMA1_IT_TC1, ENABLE); 

		/*选择DMA1通道中断*/
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;  

	/*中断使能*/ 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   
	
	/*优先级设为0 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0e;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0c;
	
	/*使能 DMA 中断*/ 
	NVIC_Init(&NVIC_InitStructure);  

	/* Enable DMA1 channel1 */
	DMA_Cmd(DMA1_Channel1, ENABLE);


	RCC_HSICmd(ENABLE);
	
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	/* Configure PB.12 (ADC Channel18) in analog mode */
	GPIO_InitStructure.GPIO_Pin = HOUT_EN_PIN|BATT_DE_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(AD_IN_GPIO, &GPIO_InitStructure);
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);


	/* Enable ADC1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	/* ADC1 configuration */
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 
	ADC_InitStructure.ADC_NbrOfConversion = 3;
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_Vrefint, 1, ADC_SampleTime_384Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 2, ADC_SampleTime_384Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 3, ADC_SampleTime_384Cycles);
	
	#if 0
	/* ADC1 regular channel18 configuration */ 
	if(Channel == 0){
		ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_96Cycles);
	}else if(Channel == 17){
		ADC_RegularChannelConfig(ADC1, ADC_Channel_Vrefint, 1, ADC_SampleTime_192Cycles);
	}else{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_192Cycles);
	}
	
	if(Channel == 17){
		ADC_TempSensorVrefintCmd(ENABLE);
	}

	#endif

	/* Enable the request after last transfer for DMA Circular mode */
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);
	
	ADC_TempSensorVrefintCmd(ENABLE);
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);

	/* Wait until the ADC1 is ready */
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET)
	{
		IWDG_ReloadCounter();
	}

	/* Start ADC1 Software Conversion */ 
	ADC_SoftwareStartConv(ADC1);
#else
	/*----------------- ADC1 configuration with DMA enabled --------------------*/
	/* Enable the HSI oscillator */
	RCC_HSICmd(ENABLE);

	GPIO_InitStructure.GPIO_Pin = NTC_DE_PIN|BATT_DE_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(AD_IN_GPIO, &GPIO_InitStructure);
	/* Check that HSI oscillator is ready */
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
  
	//ADC_DeInit(ADC1);
	/* Enable ADC1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	/* ADC1 configuration */
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	/* ADC1 regular channel18 configuration */ 

	/*
	if(Channel == 0){
		ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_192Cycles);
	}else if(Channel == 17){
		ADC_RegularChannelConfig(ADC1, ADC_Channel_Vrefint, 1, ADC_SampleTime_192Cycles);
	}else{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_192Cycles);
	}
	if(Channel == 17){
		ADC_TempSensorVrefintCmd(ENABLE);
	}
	*/

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);



	/* Wait until the ADC1 is ready */
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET)
	{
		IWDG_ReloadCounter();
	}

	/* Start ADC1 Software Conversion */ 
	//ADC_SoftwareStartConv(ADC1);



#endif
}



void Close_ADC1(void){
#if 0	
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET); //等待ADC1准备好
	ADC_Cmd(ADC1, DISABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, DISABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, DISABLE);
	DMA_Cmd(DMA1_Channel1, DISABLE);
	ADC_DMACmd(ADC1, DISABLE);
	ADC_Cmd(ADC1, DISABLE);
	RCC_HSICmd(DISABLE);
	//while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
	ADC_IO_Set_Input();
#else
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET); //等待ADC1准备好
	ADC_Cmd(ADC1, DISABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, DISABLE);
	ADC_Cmd(ADC1, DISABLE);
	RCC_HSICmd(DISABLE);
	//while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
	ADC_IO_Set_Input();
#endif
}



void Get_Vref(void)
{
    uint16 i;
    uint16 temp_AD_value;
    uint16 sum;
    uint16 average;
    uint16 max,min;
		uint32  cnt=0;
    const double voltage = 1.224;
	ADC1_Init(17);
	delay_ms(5);
	flag_ADC = 0;
	while((flag_ADC == 0)&&(cnt<100))
	{
		cnt++;
		delay_ms(100);
		IWDG_ReloadCounter();
	}

    sum = 0;
    for(i=0;i<10;i++){
        temp_AD_value = ADC_ConvertedValue[i*3+0];
		if(temp_AD_value >= 4096){
			temp_AD_value = temp_AD_value>>4;
		}
        sum += temp_AD_value;
        if(i==0){
            max = temp_AD_value;
            min = temp_AD_value;
        }else{
            if(max < temp_AD_value){
                max = temp_AD_value;
            }else if(min > temp_AD_value){
                min = temp_AD_value;
            }
        }
    }
    average = (sum-max-min)/(10-2);
    Vref = voltage/average*4096.0;


}


int8 Get_Temperature(void)
{
	uint8 i=0;
	Init_TMP112();
	for(i=0;i<2;i++)
	{
		delay_ms(1000);//第一次温度模块上电延时2S
	}
	temperature = ReadTmp112Value();
	return (int8)(temperature);
}

#define BATTER_VALUE_4		2.4		//电量最小电压
#define BATTER_VALUE_3		1.8		//电量最小电压
#define BATTER_VALUE_2		0.6		//电量最小电压
#define BATTER_VALUE_1		0.12		//电量最小电压
#define BATTER_VALUE4_BAND		0.01//
#define BATTER_VALUE3_BAND		0.01//
#define BATTER_VALUE2_BAND		0.01//
#define BATTER_VALUE1_BAND		0.01//

uint8 Get_Battery(void)
{
	uint8 i;
	uint16 max,min;
	uint16 sum;
	uint16 average;
	uint16 temp_AD_value;
	const double VREF = 3.3;
	static float last_value = 10;
	static uint8 runFlag = 0x10;
	double voltage;
	const double AD_MAX = 4096.0;
//	uint8 now_batteryValue;
	static uint8 batteryValue;

	sum = 0;
	for(i=0;i<10;i++){
        temp_AD_value = ADC_ConvertedValue[i*3+2];
		if(temp_AD_value >= 4096){
			temp_AD_value = temp_AD_value>>4;
		}
		sum += temp_AD_value;
		if(i==0){
			max = temp_AD_value;
			min = temp_AD_value;
		}else{
			if(max < temp_AD_value){
				max = temp_AD_value;
			}else if(min > temp_AD_value){
				min = temp_AD_value;
			}
		}
	}
	average = (sum-max-min)/(10-2);

	/*
	R18 = 0.1634+ss14;//系统
	if(back_light_count != 0){//背光
		R18 += 0.181245;
	}
	if(led1_switch == SWITCH_ON){//报警灯
		R18 += 0.303795;
	}
	if(sound_alarm_flag!=0 && Buzzer_flag==SWITCH_ON){//报警声音
		R18 += 0.418175;
	}
	ret = (float)(((double)average/ad_max)*VREF*(13.3/3.3))+R18;//最后加上电路上ss14管压降
	*/
	voltage = Vref/AD_MAX*average*2;
	if(runFlag){
        runFlag--;
        last_value = voltage;
    }else{
        voltage = last_value*0.9+voltage*0.1;
        last_value = voltage;
    }
	batteryValue = voltage*10*3/2;
//	
//	if(voltage > BATTER_VALUE_4){
//        now_batteryValue = 100;
//    }else if(voltage > BATTER_VALUE_3){
//        now_batteryValue = 75;
//    }else if(voltage > BATTER_VALUE_2){
//        now_batteryValue = 25;
//    }else if(voltage > BATTER_VALUE_1){
//        now_batteryValue = 5;
//    }else{
//        now_batteryValue = 0;
//    }
//	
//	if(now_batteryValue > batteryValue){
//        if(voltage > BATTER_VALUE_4+BATTER_VALUE4_BAND/2){
//            now_batteryValue = 100;
//        }else if(voltage > BATTER_VALUE_3+BATTER_VALUE3_BAND){
//            now_batteryValue = 75;
//        }else if(voltage > BATTER_VALUE_2+BATTER_VALUE2_BAND){
//            now_batteryValue = 25;
//        }else if(voltage > BATTER_VALUE_1+BATTER_VALUE1_BAND){
//            now_batteryValue = 5;
//        }else {
//            now_batteryValue = 0;
//        }
//    }
//    batteryValue = now_batteryValue;
	
	Close_ADC1();
	delay_ms(5);
	return batteryValue;
}


void ADC_IO_Set_Input(void){
	//7.8 7.2
	GPIO_InitTypeDef   GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = BATT_DE_PIN;
	GPIO_Init(AD_IN_GPIO,&GPIO_InitStructure);
}

void OLED_IO_Set_Input(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = OLED_RST_PINS|OLED_DC_PINS|OLED_CS_PINS|OLED_SCLK_PINS|OLED_SDIN_PINS;
		GPIO_Init(OLED_PORT, &GPIO_InitStruct);
}


void CC2500_GPIO_Set_Input(void){
	GPIO_InitTypeDef   GPIO_InitStructure;
    //SPI_2 Interface
    GPIO_InitStructure.GPIO_Pin = CC_MOSI;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(CC_GPIO,&GPIO_InitStructure);
    CC_MO_L;

    GPIO_InitStructure.GPIO_Pin = CC_SCLK;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(CC_GPIO,&GPIO_InitStructure);
    CC_SLK_L;

    GPIO_InitStructure.GPIO_Pin = CC_MISO;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(CC_GPIO,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = CC_CSn;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(CC_GPIO,&GPIO_InitStructure);
    CC_CSn_L;

    GPIO_InitStructure.GPIO_Pin = CC_CE;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(CC_GPIO,&GPIO_InitStructure);
    CC_CE_L;

    //GDO PINs
    GPIO_InitStructure.GPIO_Pin = CC_IRQ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(CC_GPIO,&GPIO_InitStructure);

}

void KEY_IO_Set_Input(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
}
void I2C_Set_Input(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;
		GPIO_InitStructure.GPIO_Pin = I2C_SDA|I2C_SCL;
		GPIO_Init(I2C_GPIO, &GPIO_InitStructure);

}



void Init_GPIO(void){
	Clr_M5311_Power();
	Ctr_M5311_RST();
	Clr_LCD_Power();
	Clr_Buzzer_Power();
	Clr_BTDE_Power();
	Clr_HBZ_Power();
	//
	ADC_IO_Set_Input();
	OLED_IO_Set_Input();
	CC2500_GPIO_Set_Input();
	I2C_Set_Input();
	Init_HS1();
}

void Init_Unused_GPIO(void){
	GPIO_InitTypeDef   GPIO_InitStructure;
	
	//初始化所有没有使用的IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 |GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_7|GPIO_Pin_10;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_0;
	GPIO_Init(GPIOH,&GPIO_InitStructure);
}





void PeriphClock_Initialize(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_SRAM | RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC | RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOH  ,ENABLE);  //Max clock == systerm clock(72Mhz)
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
#ifdef  VECT_TAB_RAM
	NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);/* Set the Vector Table base location at 0x20000000 */
#else  /* VECT_TAB_FLASH */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0000);/* Set the Vector Table base location at 0x08000000 */
#endif
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	//if (SysTick_Config(SystemCoreClock / 10000)){ /* Capture error */ 
		//while (1);
	//}
	
}

void RCC_Configuration(void){
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC | RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOH, ENABLE);
	RCC_HSEConfig(RCC_HSE_ON);
	if(RCC_WaitForHSEStartUp() != SUCCESS){
		//RCC_HSEConfig(RCC_HSE_ON);
		//RCC_WaitForHSEStartUp();
	}
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);

}

void NVIC_Initialize(void)
{


	
}


void StopRTCLSIMode_Close(void)
{

	NVIC_InitTypeDef  NVIC_InitStructure;

	/* Allow access to RTC */
	//PWR_RTCAccessCmd(DISABLE);

	/* Enable the RTC Clock */
	//RCC_RTCCLKCmd(DISABLE);


	/* Enable the RTC Wakeup Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = RTC_WKUP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&NVIC_InitStructure);


	/* Enable the Wakeup Interrupt */
	//RTC_ITConfig(RTC_IT_WUT, DISABLE);

	/* Enable Ultra low power mode */
	//PWR_UltraLowPowerCmd(DISABLE);

}

/* Private define ------------------------------------------------------------*/
#define EEPROM_BASE_ADDR     	   0x08080000
#define DATA_EEPROM_START_ADDR     0x08080000
#define DATA_EEPROM_END_ADDR       0x080801FF
#define DATA_EEPROM_PAGE_SIZE      0x8


void FLASH_Save_Para_Encode(uint8 * p, uint16 addr_offset, uint16 len)
{
	uint32 i;
	__disable_irq();
	DATA_EEPROM_Unlock();
	for(i=0;i<len;i++){
		DATA_EEPROM_ProgramByte(EEPROM_BASE_ADDR+addr_offset+i , *(p+i));
	}
	__enable_irq();
}

uint8 FLASH_Get_Para_Decode(uint8 * p, uint16 addr_offset, uint16 len)
{
	uint32 i;
	__disable_irq();
	for(i=0;i<len;i++){
		*(p+i) = *((uint8 *)(EEPROM_BASE_ADDR+addr_offset+i));
	}
	__enable_irq();
	return 0;
}

//通用定时器3中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//Tout= ((arr+1)*(psc+1))/Tclk；
//这里使用的是定时器3!
void TIM3_Int_Init(u16 arr,u16 psc,FunctionalState TimState)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, TimState); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,TimState); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = TimState; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	TIM_Cmd(TIM3, TimState);  //使能TIMx					 
}
//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
			//启动NB收发数据标志
			if(testM5311.communica_flag == 1){
				testM5311.communica_cnt++;
			}	
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
		}
}






