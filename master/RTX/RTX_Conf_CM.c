/*----------------------------------------------------------------------------
 *      RL-ARM - RTX
 *----------------------------------------------------------------------------
 *      Name:    RTX_CONFIG.C
 *      Purpose: Configuration of RTX Kernel for Cortex-M
 *      Rev.:    V4.20
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2011 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <rtl.h>

#include "stm32l1xx.h"
#include "typedef.h"
#include "main.h"



/*----------------------------------------------------------------------------
 *      RTX User configuration part BEGIN
 *---------------------------------------------------------------------------*/

//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------
//
// <h>Task Configuration
// =====================
//
//   <o>Number of concurrent running tasks <0-250>
//   <i> Define max. number of tasks that will run at the same time.
//   <i> Default: 6
#ifndef OS_TASKCNT
 #define OS_TASKCNT     5
#endif

//   <o>Number of tasks with user-provided stack <0-250>
//   <i> Define the number of tasks that will use a bigger stack.
//   <i> The memory space for the stack is provided by the user.
//   <i> Default: 0
#ifndef OS_PRIVCNT
 #define OS_PRIVCNT     0
#endif

//   <o>Task stack size [bytes] <20-4096:8><#/4>
//   <i> Set the stack size for tasks which is assigned by the system.
//   <i> Default: 200
#ifndef OS_STKSIZE
 #define OS_STKSIZE     256
#endif

// <q>Check for the stack overflow
// ===============================
// <i> Include the stack checking code for a stack overflow.
// <i> Note that additional code reduces the Kernel performance.
#ifndef OS_STKCHECK
 #define OS_STKCHECK    1
#endif

// <q>Run in privileged mode
// =========================
// <i> Run all Tasks in privileged mode.
// <i> Default: Unprivileged
#ifndef OS_RUNPRIV
 #define OS_RUNPRIV     1
#endif

// </h>
// <h>SysTick Timer Configuration
// =============================
//   <o>Timer clock value [Hz] <1-1000000000>
//   <i> Set the timer clock value for selected timer.
//   <i> Default: 6000000  (6MHz)
#ifndef OS_CLOCK
 #define OS_CLOCK       32000000
#endif

//   <o>Timer tick value [us] <1-1000000>
//   <i> Set the timer tick value for selected timer.
//   <i> Default: 10000  (10ms)
#ifndef OS_TICK
 #define OS_TICK        1000
#endif

// </h>

// <h>System Configuration
// =======================
// <e>Round-Robin Task switching
// =============================
// <i> Enable Round-Robin Task switching.
#ifndef OS_ROBIN
 #define OS_ROBIN       0
#endif

//   <o>Round-Robin Timeout [ticks] <1-1000>
//   <i> Define how long a task will execute before a task switch.
//   <i> Default: 5
#ifndef OS_ROBINTOUT
 #define OS_ROBINTOUT   50
#endif

// </e>

//   <o>Number of user timers <0-250>
//   <i> Define max. number of user timers that will run at the same time.
//   <i> Default: 0  (User timers disabled)
#ifndef OS_TIMERCNT
 #define OS_TIMERCNT    0
#endif

//   <o>ISR FIFO Queue size<4=>   4 entries  <8=>   8 entries
//                         <12=> 12 entries  <16=> 16 entries
//                         <24=> 24 entries  <32=> 32 entries
//                         <48=> 48 entries  <64=> 64 entries
//                         <96=> 96 entries
//   <i> ISR functions store requests to this buffer,
//   <i> when they are called from the iterrupt handler.
//   <i> Default: 16 entries
#ifndef OS_FIFOSZ
 #define OS_FIFOSZ      32
#endif

// </h>

//------------- <<< end of configuration section >>> -----------------------

// Standard library system mutexes
// ===============================
//  Define max. number system mutexes that are used to protect 
//  the arm standard runtime library. For microlib they are not used.
#ifndef OS_MUTEXCNT
 #define OS_MUTEXCNT    8
#endif

/*----------------------------------------------------------------------------
 *      RTX User configuration part END
 *---------------------------------------------------------------------------*/

#define OS_TRV          ((U32)(((double)OS_CLOCK*(double)OS_TICK)/1E6)-1)

/*----------------------------------------------------------------------------
 *      Global Functions
 *---------------------------------------------------------------------------*/

/*--------------------------- os_idle_demon ---------------------------------*/

__task void os_idle_demon (void) {
	  /* The idle demon is a system task, running when no other task is ready */
	  /* to run. The 'os_xxx' function calls are not allowed from this task.  */

	#if 0
		for (;;) {
			/* HERE: include optional user code to be executed when no task runs.*/
		}
	#else
	
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

	for (;;) {
		/* HERE: include optional user code to be executed when no task runs.*/
		if(rtosRunMode == rtos_sleep){
			sleep = os_suspend();

			if(sleep != 0)
			{
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
				RTC_DateStructure.RTC_Year =0x11;
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

				//37kHZ / 16 = 18.5kHz   1 = 54uS
				
				count = sleep * 23125 / 10000; // 432.43  sleep*(OS_TICK/1000) * 23125 / 10000

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
				IWDG_ReloadCounter();
				
				if(PWR_GetFlagStatus(PWR_FLAG_WU) != RESET)
				{
				   PWR_ClearFlag(PWR_FLAG_WU);
				}
				else
				{
				   sleep = 0;
				}
			}

			/* 恢复延时时间 */
			os_resume (sleep);
		}
	}
	#endif
}


/*--------------------------- os_tmr_call -----------------------------------*/

void os_tmr_call (U16 info) {
  /* This function is called when the user timer has expired. Parameter   */
  /* 'info' holds the value, defined when the timer was created.          */

  /* HERE: include optional user code to be executed on timeout. */
}


/*--------------------------- os_error --------------------------------------*/

void os_error (U32 err_code) {
  /* This function is called when a runtime error is detected. Parameter */
  /* 'err_code' holds the runtime error code (defined in RTL.H).         */
	static U32 error_value;
  	error_value = err_code;
  /* HERE: include optional code to be executed on runtime error. */
  for (;;);
}


/*----------------------------------------------------------------------------
 *      RTX Configuration Functions
 *---------------------------------------------------------------------------*/

#include <RTX_lib.c>

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
