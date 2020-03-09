/**
  ******************************************************************************
  * @file    Project/STM32L1xx_StdPeriph_Templates/main.c 
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    16-May-2014
  * @brief   Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup Template_Project
  * @{
  */
  
//***************************************************************************************
//Task for RTOS
//***************************************************************************************
OS_TID tsk_main, tsk_RfReadSensor, tsk_Net;

static U64 stk_for_main_tsk[4096/8];

RtosMode rtosRunMode = rtos_run;





/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/


void RTC_Config(void)
{

  RTC_InitTypeDef RTC_InitStructure;
  RTC_TimeTypeDef  RTC_TimeStruct;
  uint32 count = 0;
  
  /* Enable the PWR clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Allow access to RTC */
  PWR_RTCAccessCmd(ENABLE);

#if 0
  /* Reset RTC Domain */
  RCC_RTCResetCmd(ENABLE);
  RCC_RTCResetCmd(DISABLE);

  /* Enable the LSE OSC */
  RCC_LSEConfig(RCC_LSE_ON);

  /* Wait till LSE is ready */  
  while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {
  }

  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
#else
  RCC_LSICmd(ENABLE);

  /* Wait till LSI is ready */
  while((RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)  && (count<10000000)){count++;}
  
  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

#endif

  /* Configure the RTC data register and RTC prescaler */
  RTC_InitStructure.RTC_AsynchPrediv = 0x4D;
  RTC_InitStructure.RTC_SynchPrediv  = 0xFF;
  RTC_InitStructure.RTC_HourFormat   = RTC_HourFormat_24;
  RTC_Init(&RTC_InitStructure);
  
  /* Set the time to 00h 00mn 00s AM */
  RTC_TimeStruct.RTC_H12     = RTC_H12_AM;
  RTC_TimeStruct.RTC_Hours   = 0x00;
  RTC_TimeStruct.RTC_Minutes = 0x00;
  RTC_TimeStruct.RTC_Seconds = 0x00;  
  //RTC_SetTime(RTC_Format_BIN, &RTC_TimeStruct);

  if(RTC_SetTime(RTC_Format_BIN, &RTC_TimeStruct) == ERROR)
  {
    //printf("\n\r>> !! RTC Set Time failed. !! <<\n\r");
  }
  else
  {
    RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);
  }
  
    /* Enable the RTC Clock */
  RCC_RTCCLKCmd(ENABLE);
  
  /* Wait for RTC APB registers synchronisation */
  RTC_WaitForSynchro();
}



//
void RtcAlarmTime_Set_1s(void)
{
    RTC_AlarmTypeDef RTC_AlarmStructure;
//	RTC_TimeTypeDef  RTC_TimeStruct;
//#if 0
//	RTC_TimeStruct.RTC_H12	   = RTC_H12_AM;
//	RTC_TimeStruct.RTC_Hours   = 0x00;
//	RTC_TimeStruct.RTC_Minutes = 0x00;
//	RTC_TimeStruct.RTC_Seconds = 0x00;	
//	if(RTC_SetTime(RTC_Format_BIN, &RTC_TimeStruct) == ERROR)
//	{
//		//printf("\n\r>> !! RTC Set Time failed. !! <<\n\r");
//	}
//	else
//	{
//		//RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);
//	}
//#endif
    // xw
    RTC_GetTime(RTC_Format_BIN, &(RTC_AlarmStructure.RTC_AlarmTime));
    //        printf("rtc %d, %d, %d", RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours, RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes, RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds);

	RTC_AlarmCmd(RTC_Alarm_A, DISABLE);
	RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = (RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds+5)%60;//rtc设置0.5S一次中断，+2为1S
	RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = (RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes);
	RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours = (RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours);

	RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
	RTC_AlarmStructure.RTC_AlarmDateWeekDay = 0x31;
    /* Set the alarmA Masks */
    RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay|RTC_AlarmMask_Hours|RTC_AlarmMask_Minutes;
    RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_A, &RTC_AlarmStructure);
    RTC_AlarmCmd(RTC_Alarm_A, ENABLE);
}


//RTC ALARM 
void RTC_AlarmConfig(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;
//  RTC_AlarmTypeDef RTC_AlarmStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* EXTI configuration */
  EXTI_ClearITPendingBit(EXTI_Line17);
  EXTI_InitStructure.EXTI_Line = EXTI_Line17;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  /* Enable the RTC Alarm Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_Alarm_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  RtcAlarmTime_Set_1s();
  /* Set the alarmA Masks */
  //RTC_AlarmStructure.RTC_AlarmTime.RTC_H12 = RTC_H12_AM;
  //RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours = 0;
  //RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = 0;
  //RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = 5;
  //RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_All;
  //RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_A, &RTC_AlarmStructure);

  
  /* Set AlarmA subseconds and enable SubSec Alarm : generate 8 interripts per Second */
  RTC_AlarmSubSecondConfig(RTC_Alarm_A, 0xff, RTC_AlarmSubSecondMask_SS14_5);

  /* Enable AlarmA interrupt */
  RTC_ITConfig(RTC_IT_ALRA, ENABLE);
  
  /* Enable the alarmA */
  RTC_AlarmCmd(RTC_Alarm_A, ENABLE);
  
}


void RTC_Disable(void){
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_RTCCLKCmd(DISABLE);
	RTC_AlarmCmd(RTC_Alarm_A, DISABLE);
	/* EXTI configuration */
	EXTI_ClearITPendingBit(EXTI_Line17);
	EXTI_InitStructure.EXTI_Line = EXTI_Line17;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/* Enable the RTC Alarm Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = RTC_Alarm_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&NVIC_InitStructure);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, DISABLE);
}



//************************************************
//看门狗初始化
void IWDG_init(void)
{
	/* Enable write access to IWDG_PR and IWDG_RLR registers */
        IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
        /* IWDG counter clock: 37KHz(LSI) / 256 = 0.14453 KHz */
    	IWDG_SetPrescaler(IWDG_Prescaler_256);
        /* Set counter reload value to 1562 */
        IWDG_SetReload(4000);// 20s
        /* Reload IWDG counter */
        IWDG_ReloadCounter();
        /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
        IWDG_Enable();
}

void dev_iwdg_feed(void)
{
        IWDG_ReloadCounter();
}

//**************************************************************************
//time 休眠时间 单位ms
//采用 RTC_WKUP 唤醒功能
void SysIntoSleep(uint16 time)
{
	//RTC_Config();
	RTC_InitTypeDef RTC_InitStructure;
	RTC_TimeTypeDef  RTC_TimeStruct;
	
	EXTI_InitTypeDef EXTI_InitStructure;
	//	RTC_AlarmTypeDef RTC_AlarmStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RTC_AlarmTypeDef RTC_AlarmStructure;

	RTC_TimeTypeDef  RTC_Time;
	RTC_DateTypeDef  RTC_DateStructure;
	
	uint32 sleep = 0;
	uint32 count = 0;
	uint16 time_num = 0;

	/* Enable the PWR clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Allow access to RTC */
  PWR_RTCAccessCmd(ENABLE);

  RCC_LSICmd(ENABLE);
  
	/* Wait till LSI is ready */
	while((RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)  && (count<10000000)){count++;}

	/* Select the RTC Clock Source */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

  /* Configure the RTC data register and RTC prescaler */
  RTC_InitStructure.RTC_AsynchPrediv = 0x4D;
  RTC_InitStructure.RTC_SynchPrediv  = 0xFF;
  RTC_InitStructure.RTC_HourFormat   = RTC_HourFormat_24;
  RTC_Init(&RTC_InitStructure);
  
  /* Set the time to 00h 00mn 00s AM */
  RTC_TimeStruct.RTC_H12     = RTC_H12_AM;
  RTC_TimeStruct.RTC_Hours   = 0x00;
  RTC_TimeStruct.RTC_Minutes = 0x00;
  RTC_TimeStruct.RTC_Seconds = 0x00;  
  //RTC_SetTime(RTC_Format_BIN, &RTC_TimeStruct);

  if(RTC_SetTime(RTC_Format_BIN, &RTC_TimeStruct) == ERROR)
  {
    //printf("\n\r>> !! RTC Set Time failed. !! <<\n\r");
  }
  else
  {
    RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);
  }
  
    /* Enable the RTC Clock */
  RCC_RTCCLKCmd(ENABLE);
  
  /* Wait for RTC APB registers synchronisation */
  RTC_WaitForSynchro();
	
	/* Enable the PWR clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	/* Allow access to RTC */
	PWR_RTCAccessCmd(ENABLE);

	/* Clear WakeUp flag */
	PWR_ClearFlag(PWR_FLAG_WU);

	RCC_LSICmd(ENABLE);
	/* Wait till LSI is ready */
	while((RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)  && (count<10000000)){count++;}
	/* Select the RTC Clock Source */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

	/* Enable the RTC Clock */
	RCC_RTCCLKCmd(ENABLE);

	/* Wait for RTC APB registers synchronisation */
	RTC_WaitForSynchro();

	/* Calendar Configuration这里时假设RTC时钟是32.768，如果不是，需要在system设置中更改 */
	RTC_InitStructure.RTC_AsynchPrediv = 126; // 126  0x7F
	RTC_InitStructure.RTC_SynchPrediv =  295; /* (37KHz / 128) - 1 = 0x120*/   //295  0x120
	RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
	RTC_Init(&RTC_InitStructure); 

	/* Set the date: Wednesday January 17th 2017 */
	RTC_DateStructure.RTC_Year =0x14;
	RTC_DateStructure.RTC_Month = RTC_Month_January;
	RTC_DateStructure.RTC_Date =0x13;
	RTC_DateStructure.RTC_WeekDay = RTC_Weekday_Tuesday;
	RTC_SetDate(RTC_Format_BIN, &RTC_DateStructure);//注意设置格式

	/* Set the time to 01h 00mn 00s AM */
	RTC_TimeStruct.RTC_H12     = RTC_H12_PM;
	RTC_TimeStruct.RTC_Hours   = 0x0a;
	RTC_TimeStruct.RTC_Minutes = 0x15;
	RTC_TimeStruct.RTC_Seconds = 0x03; 
	RTC_SetTime(RTC_Format_BIN, &RTC_TimeStruct); //注意设置格式

	/* EXTI configuration *******************************************************/
	EXTI_ClearITPendingBit(EXTI_Line20);
	EXTI_InitStructure.EXTI_Line = EXTI_Line20;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* Enable the RTC Wakeup Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = RTC_WKUP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//time_num = sleep*(OS_TICK/1000)*2;
	//if(time_num == 0)  time_num = 1;
	
	/* Clear WakeUp flag */
	PWR_ClearFlag(PWR_FLAG_WU);

	/* Enable the Wakeup Interrupt */
	RTC_ITConfig(RTC_IT_WUT, ENABLE);  

	/* RTC Wakeup Interrupt Generation: Clock Source: RTCDiv_16, Wakeup Time Base: 4s */
	RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div16);

	//37kHZ / 16 = 23125Hz   1 = 0.43243uS
	count = time * 23125 / 10000; // 432.43  sleep*(OS_TICK/1000) * 23125 / 10000

	if( count > 0xffff )
		time_num = 0xffff;
	else
		time_num = count;
	
	RTC_SetWakeUpCounter(time_num);
	
	/* Enable Wakeup Counter */
	RTC_WakeUpCmd(ENABLE);

	PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);

	RTC_WakeUpCmd(DISABLE);
	SystemInit();

	if(PWR_GetFlagStatus(PWR_FLAG_WU) != RESET)
	{
	   PWR_ClearFlag(PWR_FLAG_WU);
	}
}

//进入休眠初始化GPIO和电源控制
void SleepInit_GPIO(RtosMode mode)
{
	if(mode == rtos_sleep){
		Clr_M5311_Power();
		Ctr_M5311_RST();
		Clr_LCD_Power();
		Clr_BTDE_Power();
		Clr_HBZ_Power();
		OLED_IO_Set_Input();
		I2C_Set_Input();
	}
	Clr_Buzzer_Power();
	ADC_IO_Set_Input();
	CC2500_GPIO_Set_Input();
}


//***************************************************************************************
//2.4G通讯 传感器读取任务
__task void task_RfReadSensor(void)
{
	uint16 i = 0;
	uint8 j = 0;
	uint8 SI24_ret = 0;
  	uint32 temp_id = 0;

	int16 nowTemp = 0;
	uint8 cnt = 0; 
  	uint8 alarm_count = 0;
	uint8 temper = 0;
	uint32 TempMax = 0;

	uint8 IsAlarmTemp = 0;
	uint32 tempAlarm_id = 0;
	uint8 time_count = 0;

	static uint32 conut = 0;

	//间歇休眠模式
	rtosRunMode = rtos_run;

	while(1){
		IWDG_ReloadCounter();
		SleepInit_GPIO(rtosRunMode);
		
		if(rtosRunMode == rtos_sleep){
			//SysIntoSleep(20080);
			os_dly_wait(1800);
			Buzzer_50ms();
		
		}else{
			os_dly_wait(1800);
			Buzzer_50ms();
		}

		//读取是否唤醒		
		if(GPIO_ReadInputDataBit(HS1_GPIO, HS1_PIN) == 0){
			set_state = 0;
			//延时500ms再次判断是否有磁体唤醒
			os_dly_wait(500);
			if(GPIO_ReadInputDataBit(HS1_GPIO, HS1_PIN) == 0){
				rtosRunMode = rtos_run;
				os_evt_set(EVT_EXT_WAKEUP, tsk_main);
			}
		}

		SI24_ret = Read_Si24r1_Data(Rf_channel_num , 0);
		if(SI24_ret == 1){
			IWDG_ReloadCounter();
			temp_id = ((uint32)gCC2500RxBuf[4]<<24);
			temp_id |= ((uint32)gCC2500RxBuf[5]<<16);
			temp_id |= ((uint32)gCC2500RxBuf[6]<<8);
			temp_id |= ((uint32)gCC2500RxBuf[7]<<0);
			for(i=0;i<mode_number_lenth;i++){
				if(temp_number[i]==temp_id){
					temp_alarm_com_count[i] = 0;
					temp_com_value[i][0] = gCC2500RxBuf[8+0];//温度1
					temp_com_value[i][1] = gCC2500RxBuf[8+1];//温度2
					temp_com_value[i][2] = gCC2500RxBuf[8+2];//温度3
					temp_com_value[i][3] = gCC2500RxBuf[8+3];//温度4
					temp_com_value[i][4] = gCC2500RxBuf[8+4];//温度5
					temp_com_value[i][5] = gCC2500RxBuf[8+5];//电压

					if(gCC2500RxBuf[1] == DEVICE_TYPE_TEMP){
						//检查是否是高温报警
						IsAlarmTemp = 0;
						for(j=0;j<5;j++){
							if(gCC2500RxBuf[8+j] >= (temp_temperature_alarm)){
								if(TempMax+10 < gCC2500RxBuf[8+j]){
									temp_move_alarm = 1;
									alarm_value = gCC2500RxBuf[8+j];
									alarm_number = temp_id;
									TempMax = alarm_value;
								}
								IsAlarmTemp = 1;
							}
						}

						if(IsAlarmTemp == 0){
							TempMax = 0;
						}
						
					}
				}
				else if(gCC2500RxBuf[1] == DEVICE_TYPE_MOVE){
						move_alarm_com_count[i] = 0;
						//检查是否是移动报警
						if(gCC2500RxBuf[10] == 1){
							temp_move_alarm = 2;
							alarm_value = 0;
							alarm_number = temp_id;
						}
				}else if(gCC2500RxBuf[1] == DEVICE_TYPE_MOVE2){
						//检查是否是移动报警
						if(gCC2500RxBuf[10] == 2){
                            #if ALARM_TYPE_SHAKE
								temp_move_alarm = 9;
                            #else
								temp_move_alarm = 2;
                            #endif
							
							alarm_value = 0;
							alarm_number = temp_id;
							alarm_count = 0;
							time_count = 0;
						}else if(gCC2500RxBuf[10] == 1){
							//记录报警次数，每分钟清理一次
							alarm_count++;
							tempAlarm_id = temp_id;
						}
				}else if(water_number[i]==temp_id){
						if(gCC2500RxBuf[10] == 1){
							//水位报警标志位
							water_level = 1;
						}
				}else if(smoke_number[i]==temp_id){
						if(gCC2500RxBuf[10] == 1){
						//烟感标志位
							Smoke_Alarm = 1;
						}
				}
			}
		}

		upload_delay_count += 1;
		sample_delay_count += 1;
		detection_delay_count += 1;
		com_delay_count1 += 1;
		com_delay_count2 += 1;
		
		//温度/光强/电池电压采样
		if(sample_delay_count >= sample_interval*60){
			IWDG_ReloadCounter();
			Set_BTDE_Power();
			delay_ms(50);
			sample_delay_count = 0;

			//环境光强采样
			LightValue = OPT3001_GetLuxValue();
			
			//环境温度采样			
			nowTemp=0;
			for(cnt=0; cnt<5;cnt++){
				IWDG_ReloadCounter();
				delay_ms(10);
				nowTemp += ReadTmp112Value();
			}
			nowTemp = nowTemp/5;
			temperature = nowTemp;
			
			temperature_buff[3] = temperature_buff[2];
			temperature_buff[2] = temperature_buff[1];
			temperature_buff[1] = temperature_buff[0];
			temperature_buff[0] = temperature;
			
			if(temperature <= temperature_alarm_value){
				alarm_inf_upload_flag &= (~(1<<ALARM_TYPE_TEMP));
			}

			//电池电压
			Get_Vref();//
			battery_voltage = Get_Battery();


			//判断M5311是否处于PSM模式
			
			
			//关闭采样电源
			Clr_BTDE_Power();
			I2C_Set_Input();
		}

		//上传数据时间判断
		if(upload_interval > 0)
		{
			if(upload_delay_count >= upload_interval*60*10){//upload_interval*60*10
				upload_delay_count = 0;
				if(upload_start == 1){
					if(set_state == 0){
						//M5311_Send_Inf();
						os_evt_set (EVT_NET_READY, tsk_Net);
					}
				}
			}
		}
		else
		{
			if(upload_delay_count >= 60){//upload_interval*60*10
				upload_delay_count = 0;
				if(upload_start == 1){
					if(set_state == 0){
						//M5311_Send_Inf();
						os_evt_set (EVT_NET_READY, tsk_Net);
					}
				}
			}
		}
		
	}
}


//***************************************************************************************
//
__task void task_Net(void)
{
	uint32 event_flag;

	os_dly_wait(2000);

	//工作模式初始化模块
	rtosRunMode = rtos_run;
	M5311_InitPowerOn();
	//间歇休眠模式
//	rtosRunMode = rtos_sleep;

	while (1) {

		os_evt_wait_or(EVT_NET_READY | EVT_ALARM_HAPPEN, 0xffff);
        event_flag = os_evt_get();

		if(event_flag == EVT_NET_READY){
			//达到设定的上传时间
			if(upload_start == 1)
				M5311_Send_Inf();
		}
		else if(event_flag == EVT_ALARM_HAPPEN){
			//有报警信息上传数据
			if(upload_start == 1){
				if(Smoke_Alarm==1){
					//主机烟感报警
					M5311_Send_alarm(ALARM_TYPE_SMOKE);
					Smoke_Alarm = 0;
				}else if((temperature>=temperature_alarm_value) && ((alarm_inf_upload_flag&(1<<ALARM_TYPE_TEMP)) == 0)){
					alarm_inf_upload_flag |= (1<<ALARM_TYPE_TEMP);
					//主机温度报警
					M5311_Send_alarm(ALARM_TYPE_TEMP);
				}else if(water_level==1){
					//主机水位报警
					M5311_Send_alarm(ALARM_TYPE_WATER);
					water_level = 0;
				}else if(IR_alarm != 0){
					//主机光电报警
					IR_alarm = 1;
					M5311_Send_alarm(ALARM_TYPE_IR);
				}else if(temp_move_alarm == 2){
					//移动模块报警
					M5311_Send_alarm(ALARM_TYPE_MOVE_MODULE);
					temp_move_alarm = 0;
				}else if(temp_move_alarm == 8){
					//移动模块报警
					M5311_Send_alarm(ALARM_TYPE_SHAKE_LITTLE);
					temp_move_alarm = 0;
				}else if(temp_move_alarm == 9){
					//移动模块报警
					M5311_Send_alarm(ALARM_TYPE_SHAKE_BIG);
					temp_move_alarm = 0;
				}else if(temp_move_alarm == 1){
					//测温模块报警
					M5311_Send_alarm(ALARM_TYPE_TEMP_MODULE);
					temp_move_alarm = 0;
				}else if(Temp_IR_alarm != 0){
					//测温模块光电报警
				}else if(com_error != 0){
					//设备无法通讯报警
					com_error = 0;
				}
			}
		}

		//发送数据完毕，切换模式
		if(rtosRunMode == rtos_run){
//			rtosRunMode = rtos_sleep;
		}
	}
	
}



//***************************************************************************************
//
__task void task_main(void)
{
	uint32 event_flag;
	//******************************************************
	while(1)
	{
		os_evt_wait_or(EVT_EXT_WAKEUP, 0xffff); 
        event_flag = os_evt_get();
		
		if(event_flag == EVT_EXT_WAKEUP && rtosRunMode == rtos_run){
			Beep50ms_Time(3,100);
			//达到设定的上传时间
			Set_LCD_Power();
			OLED_Init();
			Init_BS8116A();
			Display_Main_View();
			LCD_Clear();
			LCD_Update();
			delay_ms(5);
			BS8116A_GPIO_Set_Input();
			OLED_Disable();
			Clr_LCD_Power();
		}

		//发送数据完毕，切换模式
		if(rtosRunMode == rtos_run){
//			rtosRunMode = rtos_sleep;
		}
		
	}
	
}


//***************************************************************************************
__task void task_initial (void){

    tsk_RfReadSensor = os_tsk_create(task_RfReadSensor, 1);

    tsk_Net= os_tsk_create(task_Net, 2);

    tsk_main =os_tsk_create_user (task_main, 5, &stk_for_main_tsk, sizeof(stk_for_main_tsk));   
    
    os_tsk_delete_self();
    
    while(1){
    }
}

//***************************************************************************************
//*************************************************
int main(void)
{ 
	SystemInit();//
	PeriphClock_Initialize();
	
	// 低功耗模式 调试使能
	DBGMCU_Config(DBGMCU_STOP,ENABLE);
	
	Variable_Flash(0);
	
	Init_Unused_GPIO();
	Init_GPIO();

	//***********************************
	//初始化OPT3001
	Init_OPT3001();
	OPT3001_M_ID = opt3001_manufacturer_id();//0x5449
	OPT3001_D_ID = opt3001_device_id();//0x3001 
	OPT3001Config_Reg = opt3001_REG();//0XC410
	Opt3001_WriteLimReg(OPT_REG_LIMUP,200);
	OPT3001_LimUp = opt3001_limUp();
	OPT3001_LimDown = opt3001_limDown();
	LightValue = OPT3001_GetLuxValue();
	delay_ms(100);

	Set_BTDE_Power();
	delay_ms(100);
	Get_Vref();//采样时间30ms
	delay_ms(100);
	battery_voltage = Get_Battery();

	//***********************************
	//初始化TMP112
	Init_TMP112();
	Tmp211_WriteLimReg(TMP_REG_LIMDOWN,0);
	Tmp211_WriteLimReg(TMP_REG_LIMUP,60);
	Tmp112_LimUp = Tmp211_ReadReg(TMP_REG_LIMUP);
	Tmp112_LimDown = Tmp211_ReadReg(TMP_REG_LIMDOWN);
	delay_ms(2000);//温度模块第一次上电延时2s
	temperature = ReadTmp112Value();
	temperature_buff[0] = temperature;
	temperature_buff[1] = temperature;
	temperature_buff[2] = temperature;
	temperature_buff[3] = temperature;
	Clr_BTDE_Power();
	I2C_Set_Input();

	#ifndef DEBUG
		//IWDG_init();
	#endif
	
	os_sys_init(task_initial);

	while(1){
	}
}

#define APPLICATION_ADDRESS   (uint32_t)0x08016000  //40k
typedef  void (*pFunction)(void);
pFunction Jump_To_Application;
uint32 JumpAddress;

void GotoUploadApp()
{
	/* Jump to user application */
	JumpAddress = *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);
	Jump_To_Application = (pFunction) JumpAddress;
	/* Initialize user application's Stack Pointer */
	__set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
	Jump_To_Application();
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
