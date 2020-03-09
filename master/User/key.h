
#ifndef __KEY_H
#define __KEY_H

#include "stm32l1xx.h"
#include "typedef.h"


#define KEY_NONE    0xFF

extern __IO uint8 Key_flag;
extern __IO uint16 BS8116A_value;
extern __IO uint8 TCKey_value;

extern void Init_BS8116A_GPIO(void);
void BS8116A_GPIO_Set_Input(void);

extern void Init_BS8116A(void);

extern uint16 ReadBS8116A(void);
extern uint8 ReadKeyValue(void);
uint16 ReadBS8116A_S(void);


#endif

