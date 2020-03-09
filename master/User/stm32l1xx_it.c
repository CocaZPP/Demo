/**
  ******************************************************************************
  * @file    Project/STM32L1xx_StdPeriph_Templates/stm32l1xx_it.c 
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    16-May-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
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
#include "stm32l1xx_it.h"
#include "main.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
//void SVC_Handler(void)
//{
//}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
//void PendSV_Handler(void)
//{
//}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
//void SysTick_Handler(void)
//{
//}

/******************************************************************************/
/*                 STM32L1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l1xx_xx.s).                                            */
/******************************************************************************/

void EXTI9_5_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line6) != RESET){
		Key_flag = 1;
		BS8116A_value = ReadBS8116A();
		TCKey_value = ReadKeyValue();
		switch(TCKey_value){
		case 'd':
			key_value = KEY_DOWN;
			break;
		case 'l':
			key_value = KEY_LEFT;
			break;
		case 'm':
			key_value = KEY_CANCEL;
			break;
		case 'o':
			key_value = KEY_ENTER;
			break;
		case 'r':
			key_value = KEY_RIGHT;
			break;
		case 'u':
			key_value = KEY_UP;
			break;
		default :
			key_value = KEY_NONE;
			break;
		}

		if(key_value != KEY_NONE){
			isr_evt_set(EVT_KEY_READY, tsk_main);
		}

		EXTI_ClearITPendingBit(EXTI_Line6);
	}
}

/**
  * @brief  This function handles USART2 interrupt request.
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE))
	{
		usart2_rcvd_buf[usart2_rcvd_len++] = USART_ReceiveData(USART2);
		usart2_rcvd_flag = 1 ;
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	}
}

/**
  * @brief  This function handles USART2 interrupt request.
  * @param  None
  * @retval None
  */
void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE))
	{
		usart3_rcvd_buf[usart3_rcvd_len++] = USART_ReceiveData(USART3);
		usart3_rcvd_flag = 1 ;
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
	}
}


void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
    	TMP112_Alarm = 1;
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

//
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		OPT3001_Alarm = 1;
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

//
void EXTI2_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line2) != RESET)
  {
    set_state = 1;
    upload_delay_count = 0;
    sample_delay_count = 0;
    detection_delay_count = 0;
	
    /* Clear the EXTI line 2 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line2);
  }
}

/**
  * @brief  This function handles TIM2 global interrupt request.
  * @param  None
  * @retval None
  */
uint16_t capture = 0;
extern __IO uint16_t CCR1_Val;

void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
  }

}


void RTC_WKUP_IRQHandler(void)
{
  if(RTC_GetITStatus(RTC_IT_WUT) != RESET)
  {
    RTC_ClearITPendingBit(RTC_IT_WUT);
    EXTI_ClearITPendingBit(EXTI_Line20);
  } 
}

void RTC_Alarm_IRQHandler(void)
{
  
  /* Check on the AlarmA falg and on the number of interrupts per Second (60*8) */
  if(RTC_GetITStatus(RTC_IT_ALRA) != RESET) 
  { 
    /* Clear RTC AlarmA Flags */
    RTC_ClearITPendingBit(RTC_IT_ALRA);
	RTC_AlarmCmd(RTC_Alarm_A, DISABLE);
	//RtcAlarmTime_Set_1s();
  }
  /* Clear the EXTIL line 17 */
  EXTI_ClearITPendingBit(EXTI_Line17);
}

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
