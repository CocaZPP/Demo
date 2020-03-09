#ifndef _FP_MENU_H_
#define _FP_MENU_H_

#include "typedef.h"


#define MENU_STRING_MAX_LEN		30


#define ENTER_BACKGROUND			0xfe
#define QUIT_CURRENT_LIST			0xff

typedef  struct{
	uint8 item_string[MENU_STRING_MAX_LEN];
	//enumMenuEnableIndex enable_switch_index;
	FunctionalState * enable; 
	const void* next_items_array;	
	uint8 next_list_item_num;
	uint8 (*func) (void);
	//enumMenuFunctionIndex item_function_index;
}strMenuItemInfo;


extern void Enter_Main_Menu(void);


#endif
