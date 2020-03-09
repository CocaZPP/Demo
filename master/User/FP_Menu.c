#include <stdio.h>
#include "main.h"
#include "Menu.h"
#include "FP_Menu.h"

#define MENU_MAX_LAYER			8

#define MENU_ENABLE_NUMBER		7

typedef enum{
	MENU_ALWAYS_ENABLE_INDEX = 0,
}enumMenuEnableIndex;

typedef struct{
	uint8 item_num;
	uint8 current_item;
	const uint8 *menu_title;
	const strMenuItemInfo* item_array;	
}strMenuList;


static const uint8 main_menu_title[MENU_STRING_MAX_LEN] = {"菜单"};
static const uint8 factory_menu_title[MENU_STRING_MAX_LEN] = {"厂家设置"};

extern const strMenuItemInfo main_menu_items[];
extern const strMenuItemInfo background_menu_items[];


void ItemNum2Str(uint8 num, uint8* buff)
{
    uint16 value;
    uint8 cnt = 0;

    value = num;
    
    cnt = 0;

    buff[cnt++] = (value/10)%10 + '0';
    buff[cnt++] = (value)%10 + '0';
    buff[cnt++] = '.';
    buff[cnt++] = 0;
}


// 得到第index+1项有效的item的index, 没有找到返回item_num
static uint8 Get_Item_Enable_Index(const strMenuItemInfo * item, uint8 item_num, uint8 index)
{
	//uint8 enable_switch_index;
	uint8 i, j;
	
	for(i = 0,	j = 0; i < item_num; i++){
		if(*item[i].enable == ENABLE){
			j++;
			if(j == index+1){
				break;
			}
		}
		/*
		enable_switch_index = item[i].enable_switch_index;
		
		if(enable_switch_array[enable_switch_index] != 0){
			j++;
			if(j == index+1){
				break;
			}
		}
		*/
	}
	return i;	
}
// 得到有效菜单项的数量
static uint8 Get_Item_Enable_Number(const strMenuItemInfo * item, uint8 item_num)
{
	//uint8 enable_switch_index = 0;
	uint8 i, j;
	
	for(i = 0, j = 0; i < item_num; i++){
		if(*item[i].enable == ENABLE){
			j++;
		}
	}
	return j;	
}



//返回:0正常退出, 1指向下一项, 2退至上一级并指下一项,3退至上一级,255退出至主界面
static uint8 Show_Menu_List(strMenuList* list, uint8 list_index, strMenuList* current_list)
{
	uint8 menu_state = 1;

	const strMenuItemInfo * item;
	const strMenuItemInfo *current_item;
	uint8 display_item_index[3];
	uint8 ret;
	uint8 item_num_total;	  // 菜单项总数
	uint8 enable_num;
	const uint8 *menu_string_p;
	uint8 menu_num_perpage ; // 一页显示的菜单项数量
	uint8 x,y;
	uint8 start_p = 0; // 页数
	uint8 p = 1; // 当前手指	
	
	uint8 update = 1;
	uint8 i,key;
	uint8 display_index;
	uint8 buff[10];

	uint32 event_flag;

	if(list_index >= MENU_MAX_LAYER){
		return 0;
	}

	list[list_index] = *current_list;
	
	
	item = list[list_index].item_array;
	item_num_total = list[list_index].item_num;
	enable_num = Get_Item_Enable_Number(item, item_num_total);
	if(enable_num == 0){
		return 0;
	}
	if(enable_num < 3){
		menu_num_perpage = enable_num;
	}else{
		menu_num_perpage = 3;
	}	

	//初始化手指指向
	if(current_list->current_item < enable_num){
		if(current_list->current_item == 0){
			start_p = 0;
			p = 1;
		}else if(current_list->current_item == enable_num-1){
			if(current_list->current_item == 1){
				start_p = 0;
				p = 2;
			}else{
				start_p = enable_num-3;
				p = 3;
			}
		}else{
			start_p = current_list->current_item-1;
			p = 2;
		}
	}else{
		start_p = 0;
		p = 1;
	}
	
	menu_state = 1;
	update = 1;
	while(menu_state){
		  if(update){
			update = 0;
			LCD_Clear();
			for(i = 0; i < menu_num_perpage; i++){
				display_item_index[i] = Get_Item_Enable_Index(item, item_num_total, i+start_p);				
			}
			//list[list_index].current_item = display_item_index[p-1];

			GUI_PutStringConst14x14_7x14(0, 0, list[list_index].menu_title);
			
			for(i = 0; i < menu_num_perpage; i++){
				x = 16;
				y = 16+i*16;
				display_index = i+start_p+1;
				//sprintf(buff, "%2d.", display_index);
				ItemNum2Str(display_index,buff);
				//itoa(display_index, buff, 10);
				x += GUI_PutString14x14(x, y, buff);
				
				menu_string_p = item[display_item_index[i]].item_string;
				GUI_PutStringConst14x14_7x14(x, y, menu_string_p);
			}
			//Display_PIC(0, 7-p*2, 32, 16, hand_bmp);
			Display_PIC(0, p*16, 16, 12, hand_bmp);
			LCD_Update();
		}

		while(1){
			IWDG_ReloadCounter();
			//os_evt_wait_or(EVT_KEY_READY, 0xffff);

			os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        	event_flag = os_evt_get();
			
			if(event_flag == EVT_KEY_READY && Key_flag == 1 && key_value!= KEY_NONE){	
				Key_flag = 0;
				//BEEP_Short();
				Buzzer_50ms();
				key = key_value;
				key_value = KEY_NONE;
				switch(key){
					case KEY_CANCEL:
						menu_state = 0;
						ret = 0;
						break;
			
					case KEY_ENTER:
						current_item = &item[display_item_index[p-1]];
						list[list_index].current_item =start_p+p-1;

						//ret = Menu_Functions(current_item, list, list_index, &current_list->current_item);

						if(current_item->next_list_item_num != 0){
							current_list->item_num = current_item->next_list_item_num;
							current_list->item_array =  current_item->next_items_array;
							current_list->menu_title = current_item->item_string;
							if(current_item->func == NULL){
								current_list->current_item = 0;
							}else{
								current_list->current_item = current_item->func();
							}
							ret = Show_Menu_List(list, list_index+1, current_list);
						}else{
							if(current_item->func != NULL){
								ret = current_item->func();
								if(ret == QUIT_CURRENT_LIST){
									menu_state = 0;
									ret = 0;
								}
							}
						}

						update = 1;
						break;
						
					case KEY_UP:
						if(p == 3){
							p = 2;						
						}
						else if(p == 2){
							if(start_p == 0){
								p = 1;
							}else{
								start_p--;
							}
						}
						else{
							if(enable_num > 3){							
								p = 3;
								start_p = enable_num-3;
							}else{
								p = enable_num;
								start_p = 0;
							}
						}
						update = 1;
						break;
						
					case KEY_DOWN:
						if(p == 1){
							if(enable_num > 1){
								p = 2;
							}
						}
						else if(p == 2){
							if(start_p+3 == enable_num){
								p = 3;
							}else if(start_p+3 < enable_num){
								start_p++;
							}else{
								p = 1;
							}
						}
						else{
							p = 1;
							start_p = 0;
						}
						update = 1;
						break;
					
					default:
						break;
				}

				update = 1;
				break;				
			}
		}
	}

	list[list_index].current_item =start_p+p-1;
	
	return ret;
}


void Enter_Main_Menu(void)
{		
	strMenuList menu_list_array[MENU_MAX_LAYER];
	strMenuList main_menu_list;
	static uint8 hand_index = 0;
	main_menu_list.item_num = MAIN_MENU_ITEM_NUM;
	main_menu_list.current_item = hand_index;
	main_menu_list.item_array = main_menu_items;
	main_menu_list.menu_title = main_menu_title;
	
	Show_Menu_List(menu_list_array, 0, &main_menu_list);
	hand_index = menu_list_array[0].current_item;
}


void Enter_factory_Menu(void)
{
	strMenuList menu_list_array[MENU_MAX_LAYER];
	strMenuList main_menu_list;
	static uint8 hand_index = 0;

	main_menu_list.item_num = FACTORY_MENU_ITEM_NUM;
	main_menu_list.current_item = hand_index;
	main_menu_list.item_array = background_menu_items;
	main_menu_list.menu_title = factory_menu_title;
	
	Show_Menu_List(menu_list_array, 0, &main_menu_list);
	hand_index = menu_list_array[0].current_item;
}

