/**
  ******************************************************************************
  * @file    PWR/CurrentConsumption/stm32l1xx_ulp_modes.h
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    20-April-2015
  * @brief   Header for stm32l1xx_ulp_modes.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32L1xx_ULP_MODES_H
#define __STM32L1xx_ULP_MODES_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx.h"


#define BOR_LEVEL OB_BOR_OFF  /*!< BOR is disabled at power down, the reset is asserted when the VDD power supply reachs the PDR(Power Down Reset) threshold (1.5V) */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void LowPowerRunMode_Measure(void);
void LowPowerRunModeSRAM_Measure(void);
void SleepMode_Measure(void);
void LowPowerSleepMode_Measure(void);
void StopMode_Measure(void);
void StopRTCLSEMode_Measure(void);
void StopRTCLSIMode_Measure(void);
void StandbyMode_Measure(void);
void StandbyRTCLSEMode_Measure(void);
void StandbyRTCLSIMode_Measure(void);

#endif /* __STM32L1xx_ULP_MODES_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
