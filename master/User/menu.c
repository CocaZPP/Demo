
/**********************************************
**********************************************/
#include "main.h"
#include "Menu.h"
#include "SI24R1.h"
#include <string.h>

static FunctionalState always_enable = ENABLE;
static FunctionalState always_disable = DISABLE;
#define NO_FUNCTION_INDEX   NULL
extern M5311_INF m5311Inf;//模块信息
extern Test_M5311 testM5311;//测试M5311
uint32 event_flag;

uint8 ShowVersion(void)
{
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 key;
	uint8 string[20];
	uint8 ret;
	
	LCD_Clear();
	
	GUI_PutStringConst14x14_7x14(0,10,"VersionNumber:");
	sprintf((char*)string, "  %s  ", VSRSIONNUMBER);
	GUI_PutStringConst14x14_7x14(0,25,string);
	while(menu_state){
		if(update == 1){
            update = 0;
            LCD_Update();
        }
		IWDG_ReloadCounter();
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
			
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_UP:
					
					break;
					
				case KEY_DOWN:

					break;
				
				case KEY_LEFT:

					break;

				case KEY_RIGHT:

					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}

uint8 UpLoadApp(void)
{
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 key;
	uint8 string[20];
	uint8 ret;
	
	LCD_Clear();
	
	GUI_PutStringConst14x14_7x14(0,10,"UpLoadApp:");
	sprintf((char*)string, "  %s  ", VSRSIONNUMBER);
	GUI_PutStringConst14x14_7x14(0,25,"Enter Into UpLoad");
	while(menu_state){
		if(update == 1){
            update = 0;
            LCD_Update();
        }
		IWDG_ReloadCounter();
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
			
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:

					GotoUploadApp();
					
					menu_state = 0;
					ret = 0;
					break;

				case KEY_UP:
					
					break;
					
				case KEY_DOWN:

					break;
				
				case KEY_LEFT:

					break;

				case KEY_RIGHT:

					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}



uint8 Set_Number(void)
{
	uint32 temp=0;
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 index;
	uint8 key;
	uint8 string[20];
	uint8 i;
	uint8 ret;
	uint8 x,y,w;
	const uint8 time_index[9] = {0,1,2,3,4,5,6,7,8};

	LCD_Clear();
	GUI_PutStringConst14x14_7x14(0,7,main_menu_items[0].item_string);
	index=0;
	
	sprintf((char*)string, "%09d", number);

	while(menu_state){
		if(update == 1){
	            update = 0;
	            w = Get_TxtLength14x14(string);
	            x = (GUI_LCM_XMAX - w)/2;
	            y = 25;
		    GUI_PutString7x14(x, y, (char*)string);
				
	            w = time_index[index]*7;
	            Display_HLine(x + w, y+13, x+w+5, 1);
	            w = time_index[(index+6 - 1)%6]*7;
	            Display_HLine(x + w, y+13, x+w+5, 0);
				w = time_index[(index+6 + 1)%6]*7;
	            Display_HLine(x + w, y+13, x+w+5, 0);
	            
	            LCD_Update();
	        }
		IWDG_ReloadCounter();
		
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					temp=0;
					for(i = 0; i < 9; i++){
						temp*=10;
						temp += (string[i] - '0');
					}
					number = temp;
					FLASH_Save_Para_Encode((uint8 *)&number , NUMBER_ADDR , sizeof(number));
					Rf_channel_num = number % 10;
					FLASH_Save_Para_Encode((uint8 *)&Rf_channel_num , RF_CHANNEL_NUM_ADDR, sizeof(Rf_channel_num));
					os_dly_wait(100);//设置模块编号最后一位为通信信道
					menu_state = 0;
					ret = 1;
					break;

				case KEY_UP:
					if(string[index] < '9'){
						string[index]++;
					}else{
						string[index] = '0';
					}					
					update = 1;
					break;
					
				case KEY_DOWN:
					if(string[index] > '0'){
						string[index]--;
					}else{
						string[index] = '9';
					}
					update = 1;
					break;
				
				case KEY_LEFT:
					if(index==0){
						index=8;
					}else{
						index--;
					}					
					update = 1;
					break;

				case KEY_RIGHT:
					if(index >= 8){
						index = 0;
					}else{
						index++;
					}					
					update = 1;
					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}

uint8 Server_Inf_Show(void)
{
	uint8 menu_state = 1;
	uint8 update = 1;
	//uint8 index;
	uint8 key;
	uint8 string1[20];
	uint8 string2[20];
	uint8 ret;
	uint8 x1,y1;
	uint8 x2,y2;

	LCD_Clear();
	GUI_PutStringConst14x14_7x14(0,7,Server_Inf[0].item_string);
	//index=0;
	
	while(menu_state){
		if(update == 1){
            update = 0;
			sprintf((char*)string1, "IP:%03d.%03d.%03d.%03d",destinationIP[0],destinationIP[1],destinationIP[2],destinationIP[3]);
			sprintf((char*)string2, "PORT:%04d",destinationPort);
			
			x1 = 10;
			y1 = 25;
			GUI_PutString7x14(x1, y1, (char*)string1);
			x2 = 10;
			y2 = 40;
			GUI_PutString7x14(x2, y2, (char*)string2);

            LCD_Update();
			
        }
		IWDG_ReloadCounter();

		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					
					menu_state = 0;
					ret = 1;
					break;

				case KEY_UP:
				case KEY_DOWN:
				case KEY_LEFT:
				case KEY_RIGHT:
				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}


uint8 Server_Inf_Set(void)
{
	//uint32 temp=0;
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 update_all = 1;
	uint8 index;
	uint8 key;
	uint8 string1[20];
	uint8 string2[20];
	uint8 i;
	uint8 ret;
	uint8 x1,y1,w1;
	uint8 x2,y2,w2;
	//const uint8 time_index[] = {0,1,0,1,2,3,4,5,6,7,8,9};
	uint8 input_index;
	uint8 width = 3;

	
	index=0;

	w1 = 16;
	w2 = 37;

	while(menu_state){
		if(update_all == 1){
			update_all = 0;
			update = 1;
			sprintf((char*)string1, "IP:%03d.%03d.%03d.%03d",destinationIP[0],destinationIP[1],destinationIP[2],destinationIP[3]);
			sprintf((char*)string2, "PORT:%04d",destinationPort);
		}
	
		if(update == 1){
			LCD_Clear();
			GUI_PutStringConst14x14_7x14(0,7,Server_Inf[1].item_string);
			update = 0;
			x1 = 10;
			y1 = 25;
			GUI_PutString7x14(x1, y1, (char*)string1);
			x2 = 10;
			y2 = 40;
			GUI_PutString7x14(x2, y2, (char*)string2);

			if(index < 12){
				for(i=0;i<12;i++){
					if(index == i){
						Display_HLine(x1 +w1 + i*7+(index/3)*width, y1+13, x1+w1+i*7+(index/3)*width+5, 1);
					}
				}
			}else{
				for(i=0;i<4;i++){
					if((index-12) == i){
						Display_HLine(x2+w2 + i*7, y2+13, x2+w2+i*7+5, 1);
					}
				}
			}
			
			LCD_Update();
		}
		IWDG_ReloadCounter();

		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					input_index = 3;
					destinationIP[0] = (string1[input_index+0]-'0')*100+(string1[input_index+1]-'0')*10+(string1[input_index+2]-'0');
					input_index = 7;
					destinationIP[1] = (string1[input_index+0]-'0')*100+(string1[input_index+1]-'0')*10+(string1[input_index+2]-'0');
					input_index = 11;
					destinationIP[2] = (string1[input_index+0]-'0')*100+(string1[input_index+1]-'0')*10+(string1[input_index+2]-'0');
					input_index = 15;
					destinationIP[3] = (string1[input_index+0]-'0')*100+(string1[input_index+1]-'0')*10+(string1[input_index+2]-'0');

					destinationPort = (string2[5]-'0')*1000+(string2[6]-'0')*100+(string2[7]-'0')*10+(string2[8]-'0');
					
					FLASH_Save_Para_Encode((uint8 *)&destinationIP, DESTINATIONIP_ADDR, sizeof(destinationIP));
					FLASH_Save_Para_Encode((uint8 *)&destinationPort, DESTINATIONPORT_ADDR, sizeof(destinationPort));
					menu_state = 0;
					ret = 0;
					
					break;

				case KEY_UP:
					if(index < 12){
						if(index < 3){
							if(string1[index+3] < '9'){
								string1[index+3]++;
							}else{
								string1[index+3] = '0';
							}
						}else if(index < 6){
							if(string1[index+4] < '9'){
								string1[index+4]++;
							}else{
								string1[index+4] = '0';
							}
						}else if(index < 9){
							if(string1[index+5] < '9'){
								string1[index+5]++;
							}else{
								string1[index+5] = '0';
							}
						}else if(index < 12){
							if(string1[index+6] < '9'){
								string1[index+6]++;
							}else{
								string1[index+6] = '0';
							}
						}
						
					}else{
						if(string2[index+5-12] < '9'){
							string2[index+5-12]++;
						}else{
							string2[index+5-12] = '0';
						}
					}		
					update = 1;
					break;
					
				case KEY_DOWN:
					if(index < 12){
						if(index < 3){
							if(string1[index+3] > '0'){
								string1[index+3]--;
							}else{
								string1[index+3] = '9';
							}
						}else if(index < 6){
							if(string1[index+4] > '0'){
								string1[index+4]--;
							}else{
								string1[index+4] = '9';
							}
						}else if(index < 9){
							if(string1[index+5] > '0'){
								string1[index+5]--;
							}else{
								string1[index+5] = '9';
							}
						}else if(index < 12){
							if(string1[index+6] > '0'){
								string1[index+6]--;
							}else{
								string1[index+6] = '9';
							}
						}
						
					}else{
						if(string2[index+5-12] > '0'){
							string2[index+5-12]--;
						}else{
							string2[index+5-12] = '9';
						}
					}	
					
					update = 1;
					break;
				
				case KEY_LEFT:
					if(index==0){
						index=15;
					}else{
						index--;
					}					
					update = 1;
					break;

				case KEY_RIGHT:
					if(index >= 15){
						index = 0;
					}else{
						index++;
					}					
					update = 1;
					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}



const uint8 Clear_alarm_str[20] = {"是否清除报警信息"};
const uint8 Clear_alarm_Enter_str[20] = {"确认"};
const uint8 Clear_alarm_Cancel_str[20] = {"取消"};


uint8 Clear_Alarm_Inf(void)
{
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 key;
	uint8 ret;
	uint8 x,y,w;

	LCD_Clear();
	GUI_PutStringConst14x14_7x14(0,7,main_menu_items[2].item_string);
	
	while(menu_state){
		if((update == 1)){
            update = 0;
			w = Get_TxtLength14x14(Clear_alarm_str);
            x = (GUI_LCM_XMAX - w)/2;
            y = 25;
			GUI_PutStringConst14x14(x, y, Clear_alarm_str);
			x = 25;
			y = 48;
			GUI_PutStringConst14x14(x, y, Clear_alarm_Cancel_str);
			x = 75;
			y = 48;
			GUI_PutStringConst14x14(x, y, Clear_alarm_Enter_str);
            LCD_Update();
        }
		IWDG_ReloadCounter();
		
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					alarm_inf_upload_flag = 0;
					menu_state = 0;
					ret = 1;
					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}

uint8 Set_Interval(void)
{
	uint32 temp=0;
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 index;
	uint8 key;
	uint8 string[20];
	uint8 i;
	uint8 ret;
	uint8 x,y,w;
	const uint8 time_index[6] = {0,1,2,3,4,5};

	LCD_Clear();
	GUI_PutStringConst14x14_7x14(0,7,main_menu_items[3].item_string);
	index=0;
	
	sprintf((char*)string, "%03d (10min)", upload_interval);

	while(menu_state){
		if((update == 1)){
            update = 0;
            w = Get_TxtLength14x14(string);
            x = (GUI_LCM_XMAX - w)/2;
            y = 25;
			GUI_PutString7x14(x, y, (char*)string);
			
            w = time_index[index]*7;
            Display_HLine(x + w, y+13, x+w+5, 1);
			
            w = time_index[(index + 1)%4]*7;
            Display_HLine(x + w, y+13, x+w+5, 0);
			w = time_index[(index + 2)%4]*7;
            Display_HLine(x + w, y+13, x+w+5, 0);
			w = time_index[(index + 3)%4]*7;
            Display_HLine(x + w, y+13, x+w+5, 0);
            
            LCD_Update();
        }
		IWDG_ReloadCounter();
		
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					temp=0;
					for(i = 0; i < 3; i++){
						temp*=10;
						temp += (string[i] - '0');
					}
					upload_interval = temp;
					FLASH_Save_Para_Encode((uint8 *)&upload_interval , UPLOAD_INTERVAL_ADDR, sizeof(upload_interval));
					
					menu_state = 0;
					ret = 1;
					break;

				case KEY_UP:
					if(string[index] < '9'){
						string[index]++;
					}else{
						string[index] = '0';
					}					
					update = 1;
					break;
					
				case KEY_DOWN:
					if(string[index] > '0'){
						string[index]--;
					}else{
						string[index] = '9';
					}
					update = 1;
					break;
				
				case KEY_LEFT:
					if(index==0){
						index=2;
					}else{
						index--;
					}					
					update = 1;
					break;

				case KEY_RIGHT:
					if(index >= 2){
						index = 0;
					}else{
						index++;
					}					
					update = 1;
					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}

uint8 Set_Sample_Interval(void)
{
	uint32 temp=0;
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 index;
	uint8 key;
	uint8 string[20];
	uint8 i;
	uint8 ret;
	uint8 x,y,w;
	const uint8 time_index[6] = {0,1,2,3,4,5};

	LCD_Clear();
	GUI_PutStringConst14x14_7x14(0,7,main_menu_items[4].item_string);
	index=0;
	
	sprintf((char*)string, "%04d min", sample_interval);

	while(menu_state){
		if((update == 1)){
            update = 0;
            w = Get_TxtLength14x14(string);
            x = (GUI_LCM_XMAX - w)/2;
            y = 25;
			GUI_PutString7x14(x, y, (char*)string);
			
            w = time_index[index]*7;
            Display_HLine(x + w, y+13, x+w+5, 1);
            w = time_index[(index + 1)%4]*7;
            Display_HLine(x + w, y+13, x+w+5, 0);
			w = time_index[(index + 2)%4]*7;
            Display_HLine(x + w, y+13, x+w+5, 0);
			w = time_index[(index + 3)%4]*7;
            Display_HLine(x + w, y+13, x+w+5, 0);
            
            LCD_Update();
        }
		IWDG_ReloadCounter();
		
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					temp=0;
					for(i = 0; i < 4; i++){
						temp*=10;
						temp += (string[i] - '0');
					}
					sample_interval = temp;
					FLASH_Save_Para_Encode((uint8 *)&sample_interval , SAMPLE_INTERVAL_ADDR, sizeof(sample_interval));
					
					menu_state = 0;
					ret = 1;
					break;

				case KEY_UP:
					if(string[index] < '9'){
						string[index]++;
					}else{
						string[index] = '0';
					}					
					update = 1;
					break;
					
				case KEY_DOWN:
					if(string[index] > '0'){
						string[index]--;
					}else{
						string[index] = '9';
					}
					update = 1;
					break;
				
				case KEY_LEFT:
					if(index==0){
						index=3;
					}else{
						index--;
					}					
					update = 1;
					break;

				case KEY_RIGHT:
					if(index >= 3){
						index = 0;
					}else{
						index++;
					}					
					update = 1;
					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}

uint8 Set_T_Interval(void)
{
	uint32 temp=0;
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 index;
	uint8 key;
	uint8 string[20];
	uint8 i;
	uint8 ret;
	uint8 x,y,w;
	const uint8 time_index[6] = {0,1,2,3,4,5};

	LCD_Clear();
	GUI_PutStringConst14x14_7x14(0,7,main_menu_items[5].item_string);
	index=0;
	
	sprintf((char*)string, "%04d min", fibre_optical_interval);

	while(menu_state){
		if((update == 1)){
			update = 0;
			w = Get_TxtLength14x14(string);
			x = (GUI_LCM_XMAX - w)/2;
			y = 25;
			GUI_PutString7x14(x, y, (char*)string);
			
			w = time_index[index]*7;
			Display_HLine(x + w, y+13, x+w+5, 1);
			w = time_index[(index + 1)%4]*7;
			Display_HLine(x + w, y+13, x+w+5, 0);
			w = time_index[(index + 2)%4]*7;
			Display_HLine(x + w, y+13, x+w+5, 0);
			w = time_index[(index + 3)%4]*7;
			Display_HLine(x + w, y+13, x+w+5, 0);
			
			LCD_Update();
		}
		IWDG_ReloadCounter();
		
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					temp=0;
					for(i = 0; i < 4; i++){
						temp*=10;
						temp += (string[i] - '0');
					}
					fibre_optical_interval = temp;
					FLASH_Save_Para_Encode((uint8 *)&fibre_optical_interval , FIBRE_OPTICAL_INTERVAL_ADDR, sizeof(fibre_optical_interval));
					
					menu_state = 0;
					ret = 1;
					break;

				case KEY_UP:
					if(string[index] < '9'){
						string[index]++;
					}else{
						string[index] = '0';
					}					
					update = 1;
					break;
					
				case KEY_DOWN:
					if(string[index] > '0'){
						string[index]--;
					}else{
						string[index] = '9';
					}
					update = 1;
					break;
				
				case KEY_LEFT:
					if(index==0){
						index=3;
					}else{
						index--;
					}					
					update = 1;
					break;

				case KEY_RIGHT:
					if(index >= 3){
						index = 0;
					}else{
						index++;
					}					
					update = 1;
					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}


uint8 Open_Upload_Start(void){
	upload_start = 1;
	FLASH_Save_Para_Encode((uint8 *)&upload_start, UPLOAD_START_ADDR, sizeof(upload_start));
	return QUIT_CURRENT_LIST;
}

uint8 Close_Upload_Start(void){
	upload_start = 0;
	FLASH_Save_Para_Encode((uint8 *)&upload_start, UPLOAD_START_ADDR, sizeof(upload_start));
	return QUIT_CURRENT_LIST;
}

uint8 Set_TestNum(void)
{
	uint32 temp=0;
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 index;
	uint8 key;
	uint8 string[20];
	uint8 i;
	uint8 ret;
	uint8 x,y,w;
	const uint8 time_index[6] = {0,1,2,3,4,5};

	LCD_Clear();
	GUI_PutStringConst14x14_7x14(40,0,"SetTestNum");
	index=0;
	
	sprintf((char*)string, "%03d ", testM5311.test_cnt);

	while(menu_state){
		if((update == 1)){
            update = 0;
            w = Get_TxtLength14x14(string);
            x = (GUI_LCM_XMAX - w)/2;
            y = 25;
			GUI_PutString7x14(x, y, (char*)string);
			
            w = time_index[index]*7;
            Display_HLine(x + w, y+13, x+w+5, 1);
			
            w = time_index[(index + 1)%4]*7;
            Display_HLine(x + w, y+13, x+w+5, 0);
			w = time_index[(index + 2)%4]*7;
            Display_HLine(x + w, y+13, x+w+5, 0);
			w = time_index[(index + 3)%4]*7;
            Display_HLine(x + w, y+13, x+w+5, 0);
            
            LCD_Update();
        }
		IWDG_ReloadCounter();
		
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					temp=0;
					for(i = 0; i < 3; i++){
						temp*=10;
						temp += (string[i] - '0');
					}
					testM5311.test_cnt = temp;
					if(testM5311.test_cnt>100)
					{
						testM5311.test_cnt = 100;
					}
					menu_state = 0;
					ret = 1;
					break;

				case KEY_UP:
					if(string[index] < '9'){
						string[index]++;
					}else{
						string[index] = '0';
					}					
					update = 1;
					break;
					
				case KEY_DOWN:
					if(string[index] > '0'){
						string[index]--;
					}else{
						string[index] = '9';
					}
					update = 1;
					break;
				
				case KEY_LEFT:
					if(index==0){
						index=2;
					}else{
						index--;
					}					
					update = 1;
					break;

				case KEY_RIGHT:
					if(index >= 2){
						index = 0;
					}else{
						index++;
					}					
					update = 1;
					break;

				default:
						break;
			}
			
		}
	}
	return ret;
	
	 
}
//冒泡排序
void buddleSort(uint16 num[],uint16 count)
{
	uint16 temp,isSorted;
	uint16 i,j;
    for (i = 0; i < count - 1; i++){
		isSorted = 1;
        for (j = 0; j < count - i - 1; j++){
            if (num[j] > num[j + 1]){
								temp = num[j];
                num[j] = num[j+1];
                num[j+1] = temp;
                isSorted = 0;
				} 
			}
		if(isSorted) break;
    }
}
uint8 Test_Status(void)
{
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 key;
	uint8 string[50];
	uint8 ret;
	uint8 i;
	uint8  NBStatus = 0;
	uint16  link_Maxtime = 0;
	uint16  link_Mintime = 0;
	uint16  Comm_Maxtime = 0;
	uint16  Comm_Mintime = 0;
	m5311Inf.connect_time = 1;
	m5311Inf.communica_time = 1;
	testM5311.test_Mode = 1;
	testM5311.test_ok = 0;
	testM5311.test_error = 0;
	testM5311.cach=0;
	memset(testM5311.linkTime,0,100);
	memset(testM5311.CommTime,0,100);
	LCD_Clear();
	
	GUI_PutStringConst14x14_7x14(40,0,"Teststatus");
	GUI_PutStringConst14x14_7x14(0,20,"Wait....");
	LCD_Update();
	for(i = 0;i<testM5311.test_cnt;i++){
		M5311_Send_Inf();
	}
	//获取的时间排序
	buddleSort(testM5311.linkTime,testM5311.test_cnt);
	buddleSort(testM5311.CommTime,testM5311.test_cnt);
	link_Maxtime = testM5311.linkTime[testM5311.test_cnt-1];
	link_Mintime = testM5311.linkTime[0];
	Comm_Maxtime = testM5311.CommTime[testM5311.test_cnt-1];
	Comm_Maxtime = testM5311.CommTime[0];
	LCD_Clear();
	memset(string,0,50);
	sprintf((char*)string, "T:%dOK:%dErr:%d",testM5311.test_cnt,testM5311.test_ok,testM5311.test_error);
	GUI_PutStringConst14x14_7x14(0,0,string);
	memset(string,0,50);
	sprintf((char*)string, "LInk:");
	GUI_PutStringConst14x14_7x14(0,11,string);
	memset(string,0,50);
	sprintf((char*)string, "max:%dsmin:%ds",link_Maxtime,link_Mintime);
	GUI_PutStringConst14x14_7x14(0,22,string);
	memset(string,0,50);
	sprintf((char*)string, "Comm:");
	GUI_PutStringConst14x14_7x14(0,33,string);
	memset(string,0,50);
	sprintf((char*)string, "max:%dsmin:%ds",Comm_Maxtime,Comm_Mintime);
	GUI_PutStringConst14x14_7x14(0,44,string);

	while(menu_state){
		if(update == 1){
            update = 0;
            LCD_Update();
        }
		IWDG_ReloadCounter();
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
			
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
				  testM5311.test_Mode = 0;
					break;

				case KEY_ENTER:
					menu_state = 0;
					ret = 0;
					testM5311.test_Mode = 0;
					break;

				case KEY_UP:
					
					break;
					
				case KEY_DOWN:

					break;
				
				case KEY_LEFT:

					break;

				case KEY_RIGHT:

					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}

uint8 NB_Status(void)
{
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 key;
	uint8 string[50];
	uint8 ret;
	uint8  NBStatus = 0;
	testM5311.test_cnt = 0;
	testM5311.test_Mode = 1;
	LCD_Clear();
	
	GUI_PutStringConst14x14_7x14(40,0,"NBstatus");
	GUI_PutStringConst14x14_7x14(0,20,"Wait....");
	LCD_Update();
	NBStatus = Get_M5311Inf();
	M5311_Send_Inf();
	if(NBStatus == ERROR){
		LCD_Clear();
		GUI_PutStringConst14x14_7x14(0,20,"NB-ERROR");
	}
	else{
		LCD_Clear();
		memset(string,0,50);
		sprintf((char*)string, "%s",m5311Inf.imsi);
		if(strlen(string) != 0){
			GUI_PutStringConst14x14_7x14(0,8,string);
		}
		else{
			GUI_PutStringConst14x14_7x14(0,0,"NOCard");
		}
		if(m5311Inf.rssi ==99){
			GUI_PutStringConst14x14_7x14(0,16,"NOSignal");
		}
		else{
			memset(string,0,50);
			sprintf((char*)string, "rssi: %d",m5311Inf.rssi);
			GUI_PutStringConst14x14_7x14(0,20,string);
		}
		if(m5311Inf.linkNet == 1 ){
			GUI_PutStringConst14x14_7x14(0,32,"linkNet: OK");
			memset(string,0,50);
			sprintf((char*)string, "link:%ds",m5311Inf.connect_time);
			GUI_PutStringConst14x14_7x14(0,44,string);
			memset(string,0,50);
			sprintf((char*)string, "com:%ds",m5311Inf.communica_time);
			GUI_PutStringConst14x14_7x14(55,44,string);
		}
		else{
			GUI_PutStringConst14x14_7x14(0,32,"linkNet: ERROR");
		}
	}
	while(menu_state){
		if(update == 1){
            update = 0;
            LCD_Update();
        }
		IWDG_ReloadCounter();
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
			
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					testM5311.test_Mode = 0;
					break;

				case KEY_ENTER:
					menu_state = 0;
					ret = 0;
					testM5311.test_Mode = 0;
					break;

				case KEY_UP:
					
					break;
					
				case KEY_DOWN:

					break;
				
				case KEY_LEFT:

					break;

				case KEY_RIGHT:

					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}

uint8 Set_Temp_Mode_Number(void)
{
	uint32 temp=0;
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 update_all = 1;
	uint8 index;
	uint8 key;
	uint8 string1[20];
	uint8 string2[20];
	uint8 i;
	uint8 ret;
	uint8 x1,y1,w1;
	uint8 x2,y2,w2;
	const uint8 time_index[] = {0,1,0,1,2,3,4,5,6,7,8,9};
	uint8 input_index;


	LCD_Clear();
	GUI_PutStringConst14x14_7x14(0,7,binding_temp_module_number[0].item_string);
	
	index=10;
	input_index = 0;

	w1 = 34;
	w2 = 35;

	while(menu_state){
		if(update_all == 1){
			update_all = 0;
			update = 1;
			sprintf((char*)string1, "Index:%02d", input_index);
			if(temp_number[input_index] < 200000000 || temp_number[input_index]>=300000000){
				temp_number[input_index] = (temp_number[input_index]%100000000)+200000000;
			}
			sprintf((char*)string2, "NUM:%09d", temp_number[input_index]);
		}
	
		if(update == 1){
			update = 0;
			x1 = 20;
			y1 = 25;
			GUI_PutString7x14(x1, y1, (char*)string1);
			x2 = 20;
			y2 = 40;
			GUI_PutString7x14(x2, y2, (char*)string2);

			if(index < 2){
				if(index == 0){
					Display_HLine(x1 +w1 + 0, y1+13, x1+w1+0+5, 1);
					Display_HLine(x1 +w1 + 7, y1+13, x1+w1+7+5, 0);
				}else{
					Display_HLine(x1+w1 + 0, y1+13, x1+w1+0+5, 0);
					Display_HLine(x1+w1 + 7, y1+13, x1+w1+7+5, 1);
				}
				for(i=0;i<9;i++){
					Display_HLine(x2+w2 + i*7, y2+13, x2+w2+i*7+5, 0);
				}
			}else{
				Display_HLine(x1+w1 + 0, y1+13, x1+w1+0+5, 0);
				Display_HLine(x1+w1 + 7, y1+13, x1+w1+7+5, 0);
				for(i=0;i<9;i++){
					Display_HLine(x2+w2 + i*7, y2+13, x2+w2+i*7+5, 0);
				}
				Display_HLine(x2+w2 + time_index[index]*7, y2+13, x2+w2+time_index[index]*7+5, 1);
			}
			
			LCD_Update();
		}
		IWDG_ReloadCounter();
		
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					
					temp=0;
					for(i = 0; i < 2; i++){
						temp*=10;
						temp += (string1[6+i] - '0');
					}
					input_index = temp;
					if(input_index < mode_number_lenth){
						now_temp_number_lenth = input_index+1;
						temp=0;
						for(i = 0; i < 9; i++){
							temp*=10;
							temp += (string2[i+4] - '0');
						}
						temp_number[input_index] = temp;

						FLASH_Save_Para_Encode((uint8 *)&temp_number, TEMP_NUMBER_ADDR, sizeof(temp_number));
						FLASH_Save_Para_Encode((uint8 *)&now_temp_number_lenth, NOW_TEMP_NUMBER_LENTH_ADDR, sizeof(now_temp_number_lenth));
						
						index=10;
						input_index++;
						if(input_index >= mode_number_lenth){
							menu_state = 0;
							ret = 1;
						}
						update_all = 1;
					}
					break;

				case KEY_UP:
					if(index < 2){
						if(string1[index+6] < '9'){
							string1[index+6]++;
						}else{
							string1[index+6] = '0';
						}
					}else{
						if(string2[index+4-2] < '9'){
							string2[index+4-2]++;
						}else{
							string2[index+4-2] = '0';
						}
					}		
					update = 1;
					break;
					
				case KEY_DOWN:
					if(index < 2){
						if(string1[index+6] > '0'){
							string1[index+6]--;
						}else{
							string1[index+6] = '9';
						}
					}else{
						if(string2[index+4-2] > '0'){
							string2[index+4-2]--;
						}else{
							string2[index+4-2] = '9';
						}
					}
					update = 1;
					break;
				
				case KEY_LEFT:
					if(index==0){
						index=10;
					}else{
						index--;
						if(index == 2){
							index=1;
						}
					}					
					update = 1;
					break;

				case KEY_RIGHT:
					if(index >= 10){
						index = 0;
					}else{
						index++;
						if(index == 2){
							index=3;
						}
					}					
					update = 1;
					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
}

const uint8 Clear_number_str[20] = {"是否清除模块编号"};
const uint8 Clear_number_Enter_str[20] = {"确认"};
const uint8 Clear_number_Cancel_str[20] = {"取消"};

uint8 Del_Temp_Mode_Number(void)
{
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 key;
	uint8 ret;
	uint8 x,y,w;

	LCD_Clear();
	GUI_PutStringConst14x14_7x14(0,7,binding_temp_module_number[1].item_string);
	
	while(menu_state){
		if(update == 1){
            update = 0;
            w = Get_TxtLength14x14(Clear_alarm_str);
            x = (GUI_LCM_XMAX - w)/2;
            y = 25;
            GUI_PutStringConst14x14(x, y, Clear_number_str);
            x = 25;
            y = 48;
            GUI_PutStringConst14x14(x, y, Clear_number_Cancel_str);
            x = 75;
            y = 48;
            GUI_PutStringConst14x14(x, y, Clear_number_Enter_str);
            LCD_Update();
        }
		IWDG_ReloadCounter();
		
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					memset(temp_number,0,mode_number_lenth);
					now_temp_number_lenth = 0;
					FLASH_Save_Para_Encode((uint8 *)&temp_number, TEMP_NUMBER_ADDR, sizeof(temp_number));
					FLASH_Save_Para_Encode((uint8 *)&now_temp_number_lenth, NOW_TEMP_NUMBER_LENTH_ADDR, sizeof(now_temp_number_lenth));
					menu_state = 0;
					ret = 0;
					break;

				case KEY_UP:
					break;
					
				case KEY_DOWN:
					break;
				
				case KEY_LEFT:
					break;

				case KEY_RIGHT:
					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}


uint8 Read_Temp_Mode_Number(void)
{
	//uint32 temp=0;
	uint8 menu_state = 1;
	uint8 update = 1;
	//uint8 update_all = 1;
	//uint8 index;
	uint8 key;
	uint8 string1[20];
	uint8 string2[20];
	uint8 string3[20];
	//uint8 i;
	uint8 ret;
	uint8 x1,y1;
	uint8 x2,y2;
	//const uint8 time_index[] = {0,1,0,1,2,3,4,5,6,7,8,9};
	//uint8 input_index;
	uint8 start_p = 0; // 页数
	uint8 p = 1; // 当前手指	
	
	//index=10;
	//input_index = 0;

	//w1 = 34;
	//w2 = 35;

	while(menu_state){
		if(update == 1){
			update = 0;
			LCD_Clear();
			GUI_PutStringConst14x14_7x14(0,7,binding_temp_module_number[2].item_string);
			if(now_temp_number_lenth >= 3){
				sprintf((char*)string1, "%02d:%d", start_p+1,temp_number[start_p]);
				sprintf((char*)string2, "%02d:%d", start_p+2,temp_number[start_p+1]);
				sprintf((char*)string3, "%02d:%d", start_p+3,temp_number[start_p+2]);
			}else if(now_temp_number_lenth == 2){
				sprintf((char*)string1, "%02d:%d", 1,temp_number[0]);
				sprintf((char*)string2, "%02d:%d", 2,temp_number[1]);
			}else if(now_temp_number_lenth == 1){
				sprintf((char*)string1, "%02d:%d", 1,temp_number[0]);
			}else{
				sprintf((char*)string1, "NULL", 0);
			}
			x1 = 20;
			y1 = 20;
			GUI_PutString7x14(x1, y1, (char*)string1);
			x2 = 20;
			y2 = 34;
			GUI_PutString7x14(x2, y2, (char*)string2);
			x2 = 20;
			y2 = 48;
			GUI_PutString7x14(x2, y2, (char*)string3);
			Display_PIC(0, p*14+6, 16, 12, hand_bmp);
			LCD_Update();
		}

		IWDG_ReloadCounter();
		
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					
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
						if(now_temp_number_lenth > 3){ 						
							p = 3;
							start_p = now_temp_number_lenth-3;
						}else{
							p = now_temp_number_lenth;
							start_p = 0;
						}
					}
					update = 1;
					break;
					
				case KEY_DOWN:
					if(p == 1){
						if(now_temp_number_lenth > 1){
							p = 2;
						}
					}
					else if(p == 2){
						if(start_p+3 == now_temp_number_lenth){
							p = 3;
						}else if(start_p+3 < now_temp_number_lenth){
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
				
				case KEY_LEFT:
					update = 1;
					break;

				case KEY_RIGHT:
					update = 1;
					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}


uint8 Set_Move_Mode_Number(void)
{
	uint32 temp=0;
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 update_all = 1;
	uint8 index;
	uint8 key;
	uint8 string1[20];
	uint8 string2[20];
	uint8 i;
	uint8 ret;
	uint8 x1,y1,w1;
	uint8 x2,y2,w2;
	const uint8 time_index[] = {0,1,0,1,2,3,4,5,6,7,8,9};
	uint8 input_index;


	LCD_Clear();
	GUI_PutStringConst14x14_7x14(0,7,binding_temp_module_number[0].item_string);
	
	index=10;
	input_index = 0;

	w1 = 34;
	w2 = 35;

	while(menu_state){
		if(update_all == 1){
			update_all = 0;
			update = 1;
			sprintf((char*)string1, "Index:%02d", input_index);
			if(move_number[input_index] < 300000000 || move_number[input_index]>=400000000){
				move_number[input_index] = (move_number[input_index]%100000000)+300000000;
			}
			sprintf((char*)string2, "NUM:%09d", move_number[input_index]);
		}
	
		if(update == 1){
			update = 0;
			x1 = 20;
			y1 = 25;
			GUI_PutString7x14(x1, y1, (char*)string1);
			x2 = 20;
			y2 = 40;
			GUI_PutString7x14(x2, y2, (char*)string2);

			if(index < 2){
				if(index == 0){
					Display_HLine(x1 +w1 + 0, y1+13, x1+w1+0+5, 1);
					Display_HLine(x1 +w1 + 7, y1+13, x1+w1+7+5, 0);
				}else{
					Display_HLine(x1+w1 + 0, y1+13, x1+w1+0+5, 0);
					Display_HLine(x1+w1 + 7, y1+13, x1+w1+7+5, 1);
				}
				for(i=0;i<9;i++){
					Display_HLine(x2+w2 + i*7, y2+13, x2+w2+i*7+5, 0);
				}
			}else{
				Display_HLine(x1+w1 + 0, y1+13, x1+w1+0+5, 0);
				Display_HLine(x1+w1 + 7, y1+13, x1+w1+7+5, 0);
				for(i=0;i<9;i++){
					Display_HLine(x2+w2 + i*7, y2+13, x2+w2+i*7+5, 0);
				}
				Display_HLine(x2+w2 + time_index[index]*7, y2+13, x2+w2+time_index[index]*7+5, 1);
			}
			
			LCD_Update();
		}

		IWDG_ReloadCounter();
		
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					
					temp=0;
					for(i = 0; i < 2; i++){
						temp*=10;
						temp += (string1[6+i] - '0');
					}
					input_index = temp;
					if(input_index < mode_number_lenth){
						now_move_number_lenth = input_index+1;
						temp=0;
						for(i = 0; i < 9; i++){
							temp*=10;
							temp += (string2[i+4] - '0');
						}
						move_number[input_index] = temp;
						FLASH_Save_Para_Encode((uint8 *)&move_number, MOVE_NUMBER_ADDR, sizeof(move_number));
						FLASH_Save_Para_Encode((uint8 *)&now_move_number_lenth, NOW_MOVE_NUMBER_LENTH_ADDR, sizeof(now_move_number_lenth));
						
						index=10;
						input_index++;
						if(input_index >= mode_number_lenth){
							menu_state = 0;
							ret = 1;
						}
						update_all = 1;
					}
					
					break;

				case KEY_UP:
					if(index < 2){
						if(string1[index+6] < '9'){
							string1[index+6]++;
						}else{
							string1[index+6] = '0';
						}
					}else{
						if(string2[index+4-2] < '9'){
							string2[index+4-2]++;
						}else{
							string2[index+4-2] = '0';
						}
					}		
					update = 1;
					break;
					
				case KEY_DOWN:
					if(index < 2){
						if(string1[index+6] > '0'){
							string1[index+6]--;
						}else{
							string1[index+6] = '9';
						}
					}else{
						if(string2[index+4-2] > '0'){
							string2[index+4-2]--;
						}else{
							string2[index+4-2] = '9';
						}
					}
					update = 1;
					break;
				
				case KEY_LEFT:
					if(index==0){
						index=10;
					}else{
						index--;
						if(index == 2){
							index=1;
						}
					}					
					update = 1;
					break;

				case KEY_RIGHT:
					if(index >= 10){
						index = 0;
					}else{
						index++;
						if(index == 2){
							index=3;
						}
					}					
					update = 1;
					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}


uint8 Del_Move_Mode_Number(void)
{
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 key;
	uint8 ret;
	uint8 x,y,w;

	LCD_Clear();
	GUI_PutStringConst14x14_7x14(0,7,binding_move_module_number[1].item_string);
	
	while(menu_state){
		if((update == 1)){
			update = 0;
			w = Get_TxtLength14x14(Clear_alarm_str);
			x = (GUI_LCM_XMAX - w)/2;
			y = 25;
			GUI_PutStringConst14x14(x, y, Clear_number_str);
			x = 25;
			y = 48;
			GUI_PutStringConst14x14(x, y, Clear_number_Cancel_str);
			x = 75;
			y = 48;
			GUI_PutStringConst14x14(x, y, Clear_number_Enter_str);
			LCD_Update();
		}

		IWDG_ReloadCounter();
		
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					memset(move_number,0,mode_number_lenth);
					now_move_number_lenth = 0;
					FLASH_Save_Para_Encode((uint8 *)&move_number, MOVE_NUMBER_ADDR, sizeof(move_number));
					FLASH_Save_Para_Encode((uint8 *)&now_move_number_lenth, NOW_MOVE_NUMBER_LENTH_ADDR, sizeof(now_move_number_lenth));
					menu_state = 0;
					ret = 0;
					break;

				case KEY_UP:
					break;
					
				case KEY_DOWN:
					break;
				
				case KEY_LEFT:
					break;

				case KEY_RIGHT:
					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}


uint8 Read_Move_Mode_Number(void)
{
	//uint32 temp=0;
	uint8 menu_state = 1;
	uint8 update = 1;
	//uint8 update_all = 1;
	//uint8 index;
	uint8 key;
	uint8 string1[20];
	uint8 string2[20];
	uint8 string3[20];
	uint8 ret;
	uint8 x1,y1;
	uint8 x2,y2;
	//const uint8 time_index[] = {0,1,0,1,2,3,4,5,6,7,8,9};
	//uint8 input_index;
	uint8 start_p = 0; // 页数
	uint8 p = 1; // 当前手指	
	
	//index=10;
	//input_index = 0;

	//w1 = 34;
	//w2 = 35;

	while(menu_state){
		if(update == 1){
			update = 0;
			LCD_Clear();
			GUI_PutStringConst14x14_7x14(0,7,binding_temp_module_number[2].item_string);
			if(now_move_number_lenth >= 3){
				sprintf((char*)string1, "%02d:%d", start_p+1,move_number[start_p]);
				sprintf((char*)string2, "%02d:%d", start_p+2,move_number[start_p+1]);
				sprintf((char*)string3, "%02d:%d", start_p+3,move_number[start_p+2]);
			}else if(now_move_number_lenth == 2){
				sprintf((char*)string1, "%02d:%d", 1,move_number[0]);
				sprintf((char*)string2, "%02d:%d", 2,move_number[1]);
			}else if(now_move_number_lenth == 1){
				sprintf((char*)string1, "%02d:%d", 1,move_number[0]);
			}else{
				sprintf((char*)string1, "NULL", 0);
			}
			x1 = 20;
			y1 = 20;
			GUI_PutString7x14(x1, y1, (char*)string1);
			x2 = 20;
			y2 = 34;
			GUI_PutString7x14(x2, y2, (char*)string2);
			x2 = 20;
			y2 = 48;
			GUI_PutString7x14(x2, y2, (char*)string3);
			Display_PIC(0, p*14+6, 16, 12, hand_bmp);
			LCD_Update();
		}

		IWDG_ReloadCounter();
		
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					
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
						if(now_move_number_lenth > 3){						
							p = 3;
							start_p = now_move_number_lenth-3;
						}else{
							p = now_move_number_lenth;
							start_p = 0;
						}
					}
					update = 1;
					break;
					
				case KEY_DOWN:
					if(p == 1){
						if(now_move_number_lenth > 1){
							p = 2;
						}
					}
					else if(p == 2){
						if(start_p+3 == now_move_number_lenth){
							p = 3;
						}else if(start_p+3 < now_move_number_lenth){
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
				
				case KEY_LEFT:
					update = 1;
					break;

				case KEY_RIGHT:
					update = 1;
					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}
uint8 Set_Water_Mode_Number(void)
{
	uint32 temp=0;
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 update_all = 1;
	uint8 index;
	uint8 key;
	uint8 string1[20];
	uint8 string2[20];
	uint8 i;
	uint8 ret;
	uint8 x1,y1,w1;
	uint8 x2,y2,w2;
	const uint8 time_index[] = {0,1,0,1,2,3,4,5,6,7,8,9};
	uint8 input_index;


	LCD_Clear();
	GUI_PutStringConst14x14_7x14(0,7,binding_temp_module_number[0].item_string);
	
	index=10;
	input_index = 0;

	w1 = 34;
	w2 = 35;

	while(menu_state){
		if(update_all == 1){
			update_all = 0;
			update = 1;
			sprintf((char*)string1, "Index:%02d", input_index);
			if(water_number[input_index] < 400000000 || water_number[input_index]>=500000000){
				water_number[input_index] = (water_number[input_index]%100000000)+400000000;
			}
			sprintf((char*)string2, "NUM:%09d", water_number[input_index]);
		}
	
		if(update == 1){
			update = 0;
			x1 = 20;
			y1 = 25;
			GUI_PutString7x14(x1, y1, (char*)string1);
			x2 = 20;
			y2 = 40;
			GUI_PutString7x14(x2, y2, (char*)string2);

			if(index < 2){
				if(index == 0){
					Display_HLine(x1 +w1 + 0, y1+13, x1+w1+0+5, 1);
					Display_HLine(x1 +w1 + 7, y1+13, x1+w1+7+5, 0);
				}else{
					Display_HLine(x1+w1 + 0, y1+13, x1+w1+0+5, 0);
					Display_HLine(x1+w1 + 7, y1+13, x1+w1+7+5, 1);
				}
				for(i=0;i<9;i++){
					Display_HLine(x2+w2 + i*7, y2+13, x2+w2+i*7+5, 0);
				}
			}else{
				Display_HLine(x1+w1 + 0, y1+13, x1+w1+0+5, 0);
				Display_HLine(x1+w1 + 7, y1+13, x1+w1+7+5, 0);
				for(i=0;i<9;i++){
					Display_HLine(x2+w2 + i*7, y2+13, x2+w2+i*7+5, 0);
				}
				Display_HLine(x2+w2 + time_index[index]*7, y2+13, x2+w2+time_index[index]*7+5, 1);
			}
			
			LCD_Update();
		}

		IWDG_ReloadCounter();
		
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					
					temp=0;
					for(i = 0; i < 2; i++){
						temp*=10;
						temp += (string1[6+i] - '0');
					}
					input_index = temp;
					if(input_index < mode_number_lenth){
						now_water_number_lenth = input_index+1;
						temp=0;
						for(i = 0; i < 9; i++){
							temp*=10;
							temp += (string2[i+4] - '0');
						}
						water_number[input_index] = temp;

						 FLASH_Save_Para_Encode((uint8 *)&water_number, WATER_NUMBER_ADDR, sizeof(water_number));
						FLASH_Save_Para_Encode((uint8 *)&now_water_number_lenth, NOW_WATER_NUMBER_LENTH_ADDR, sizeof(now_water_number_lenth));
						 
						index=10;
						input_index++;
						if(input_index >= mode_number_lenth){
							menu_state = 0;
							ret = 1;
						}
						update_all = 1;
					}
					
					break;

				case KEY_UP:
					if(index < 2){
						if(string1[index+6] < '9'){
							string1[index+6]++;
						}else{
							string1[index+6] = '0';
						}
					}else{
						if(string2[index+4-2] < '9'){
							string2[index+4-2]++;
						}else{
							string2[index+4-2] = '0';
						}
					}		
					update = 1;
					break;
					
				case KEY_DOWN:
					if(index < 2){
						if(string1[index+6] > '0'){
							string1[index+6]--;
						}else{
							string1[index+6] = '9';
						}
					}else{
						if(string2[index+4-2] > '0'){
							string2[index+4-2]--;
						}else{
							string2[index+4-2] = '9';
						}
					}
					update = 1;
					break;
				
				case KEY_LEFT:
					if(index==0){
						index=10;
					}else{
						index--;
						if(index == 2){
							index=1;
						}
					}					
					update = 1;
					break;

				case KEY_RIGHT:
					if(index >= 10){
						index = 0;
					}else{
						index++;
						if(index == 2){
							index=3;
						}
					}					
					update = 1;
					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}


uint8 Del_Water_Mode_Number(void)
{
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 key;
	uint8 ret;
	uint8 x,y,w;

	LCD_Clear();
	GUI_PutStringConst14x14_7x14(0,7,binding_move_module_number[1].item_string);
	
	while(menu_state){
		if((update == 1)){
			update = 0;
			w = Get_TxtLength14x14(Clear_alarm_str);
			x = (GUI_LCM_XMAX - w)/2;
			y = 25;
			GUI_PutStringConst14x14(x, y, Clear_number_str);
			x = 25;
			y = 48;
			GUI_PutStringConst14x14(x, y, Clear_number_Cancel_str);
			x = 75;
			y = 48;
			GUI_PutStringConst14x14(x, y, Clear_number_Enter_str);
			LCD_Update();
		}

		IWDG_ReloadCounter();
		
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					memset(water_number,0,mode_number_lenth);
					now_water_number_lenth = 0;
					FLASH_Save_Para_Encode((uint8 *)&water_number, WATER_NUMBER_ADDR, sizeof(water_number));
					FLASH_Save_Para_Encode((uint8 *)&now_water_number_lenth, NOW_WATER_NUMBER_LENTH_ADDR, sizeof(now_water_number_lenth));
					menu_state = 0;
					ret = 0;
					break;

				case KEY_UP:
					break;
					
				case KEY_DOWN:
					break;
				
				case KEY_LEFT:
					break;

				case KEY_RIGHT:
					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}


uint8 Read_Water_Mode_Number(void)
{
	//uint32 temp=0;
	uint8 menu_state = 1;
	uint8 update = 1;
	//uint8 update_all = 1;
	//uint8 index;
	uint8 key;
	uint8 string1[20];
	uint8 string2[20];
	uint8 string3[20];
	uint8 ret;
	uint8 x1,y1;
	uint8 x2,y2;
	//const uint8 time_index[] = {0,1,0,1,2,3,4,5,6,7,8,9};
	//uint8 input_index;
	uint8 start_p = 0; // 页数
	uint8 p = 1; // 当前手指	
	
	//index=10;
	//input_index = 0;

	//w1 = 34;
	//w2 = 35;

	while(menu_state){
		if(update == 1){
			update = 0;
			LCD_Clear();
			GUI_PutStringConst14x14_7x14(0,7,binding_temp_module_number[2].item_string);
			if(now_water_number_lenth >= 3){
				sprintf((char*)string1, "%02d:%d", start_p+1,water_number[start_p]);
				sprintf((char*)string2, "%02d:%d", start_p+2,water_number[start_p+1]);
				sprintf((char*)string3, "%02d:%d", start_p+3,water_number[start_p+2]);
			}else if(now_water_number_lenth == 2){
				sprintf((char*)string1, "%02d:%d", 1,water_number[0]);
				sprintf((char*)string2, "%02d:%d", 2,water_number[1]);
			}else if(now_water_number_lenth == 1){
				sprintf((char*)string1, "%02d:%d", 1,water_number[0]);
			}else{
				sprintf((char*)string1, "NULL", 0);
			}
			x1 = 20;
			y1 = 20;
			GUI_PutString7x14(x1, y1, (char*)string1);
			x2 = 20;
			y2 = 34;
			GUI_PutString7x14(x2, y2, (char*)string2);
			x2 = 20;
			y2 = 48;
			GUI_PutString7x14(x2, y2, (char*)string3);
			Display_PIC(0, p*14+6, 16, 12, hand_bmp);
			LCD_Update();
		}

		IWDG_ReloadCounter();
		
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					
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
						if(now_water_number_lenth > 3){						
							p = 3;
							start_p = now_water_number_lenth-3;
						}else{
							p = now_water_number_lenth;
							start_p = 0;
						}
					}
					update = 1;
					break;
					
				case KEY_DOWN:
					if(p == 1){
						if(now_water_number_lenth > 1){
							p = 2;
						}
					}
					else if(p == 2){
						if(start_p+3 == now_water_number_lenth){
							p = 3;
						}else if(start_p+3 < now_water_number_lenth){
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
				
				case KEY_LEFT:
					update = 1;
					break;

				case KEY_RIGHT:
					update = 1;
					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}
uint8 Set_Smoke_Mode_Number(void)
{
	uint32 temp=0;
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 update_all = 1;
	uint8 index;
	uint8 key;
	uint8 string1[20];
	uint8 string2[20];
	uint8 i;
	uint8 ret;
	uint8 x1,y1,w1;
	uint8 x2,y2,w2;
	const uint8 time_index[] = {0,1,0,1,2,3,4,5,6,7,8,9};
	uint8 input_index;


	LCD_Clear();
	GUI_PutStringConst14x14_7x14(0,7,binding_temp_module_number[0].item_string);
	
	index=10;
	input_index = 0;

	w1 = 34;
	w2 = 35;

	while(menu_state){
		if(update_all == 1){
			update_all = 0;
			update = 1;
			sprintf((char*)string1, "Index:%02d", input_index);
			if(smoke_number[input_index] < 500000000 || smoke_number[input_index]>=600000000){
				smoke_number[input_index] = (smoke_number[input_index]%100000000)+500000000;
			}
			sprintf((char*)string2, "NUM:%09d", smoke_number[input_index]);
		}
	
		if(update == 1){
			update = 0;
			x1 = 20;
			y1 = 25;
			GUI_PutString7x14(x1, y1, (char*)string1);
			x2 = 20;
			y2 = 40;
			GUI_PutString7x14(x2, y2, (char*)string2);

			if(index < 2){
				if(index == 0){
					Display_HLine(x1 +w1 + 0, y1+13, x1+w1+0+5, 1);
					Display_HLine(x1 +w1 + 7, y1+13, x1+w1+7+5, 0);
				}else{
					Display_HLine(x1+w1 + 0, y1+13, x1+w1+0+5, 0);
					Display_HLine(x1+w1 + 7, y1+13, x1+w1+7+5, 1);
				}
				for(i=0;i<9;i++){
					Display_HLine(x2+w2 + i*7, y2+13, x2+w2+i*7+5, 0);
				}
			}else{
				Display_HLine(x1+w1 + 0, y1+13, x1+w1+0+5, 0);
				Display_HLine(x1+w1 + 7, y1+13, x1+w1+7+5, 0);
				for(i=0;i<9;i++){
					Display_HLine(x2+w2 + i*7, y2+13, x2+w2+i*7+5, 0);
				}
				Display_HLine(x2+w2 + time_index[index]*7, y2+13, x2+w2+time_index[index]*7+5, 1);
			}
			
			LCD_Update();
		}

		IWDG_ReloadCounter();
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					
					temp=0;
					for(i = 0; i < 2; i++){
						temp*=10;
						temp += (string1[6+i] - '0');
					}
					input_index = temp;
					if(input_index < mode_number_lenth){
						now_smoke_number_lenth = input_index+1;
						temp=0;
						for(i = 0; i < 9; i++){
							temp*=10;
							temp += (string2[i+4] - '0');
						}
						smoke_number[input_index] = temp;
						FLASH_Save_Para_Encode((uint8 *)&smoke_number, SMOKE_NUMBER_ADDR, sizeof(smoke_number));
						FLASH_Save_Para_Encode((uint8 *)&now_smoke_number_lenth, NOW_SMOKE_NUMBER_LENTH_ADDR,sizeof(now_smoke_number_lenth));
						
						index=10;
						input_index++;
						if(input_index >= mode_number_lenth){
							menu_state = 0;
							ret = 1;
						}
						update_all = 1;
					}
					
					break;

				case KEY_UP:
					if(index < 2){
						if(string1[index+6] < '9'){
							string1[index+6]++;
						}else{
							string1[index+6] = '0';
						}
					}else{
						if(string2[index+4-2] < '9'){
							string2[index+4-2]++;
						}else{
							string2[index+4-2] = '0';
						}
					}		
					update = 1;
					break;
					
				case KEY_DOWN:
					if(index < 2){
						if(string1[index+6] > '0'){
							string1[index+6]--;
						}else{
							string1[index+6] = '9';
						}
					}else{
						if(string2[index+4-2] > '0'){
							string2[index+4-2]--;
						}else{
							string2[index+4-2] = '9';
						}
					}
					update = 1;
					break;
				
				case KEY_LEFT:
					if(index==0){
						index=10;
					}else{
						index--;
						if(index == 2){
							index=1;
						}
					}					
					update = 1;
					break;

				case KEY_RIGHT:
					if(index >= 10){
						index = 0;
					}else{
						index++;
						if(index == 2){
							index=3;
						}
					}					
					update = 1;
					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}


uint8 Del_Smoke_Mode_Number(void)
{
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 key;
	uint8 ret;
	uint8 x,y,w;

	LCD_Clear();
	GUI_PutStringConst14x14_7x14(0,7,binding_move_module_number[1].item_string);
	
	while(menu_state){
		if((update == 1)){
			update = 0;
			w = Get_TxtLength14x14(Clear_alarm_str);
			x = (GUI_LCM_XMAX - w)/2;
			y = 25;
			GUI_PutStringConst14x14(x, y, Clear_number_str);
			x = 25;
			y = 48;
			GUI_PutStringConst14x14(x, y, Clear_number_Cancel_str);
			x = 75;
			y = 48;
			GUI_PutStringConst14x14(x, y, Clear_number_Enter_str);
			LCD_Update();
		}

		IWDG_ReloadCounter();
		
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					memset(smoke_number,0,mode_number_lenth);
					now_smoke_number_lenth = 0;
					FLASH_Save_Para_Encode((uint8 *)&smoke_number, SMOKE_NUMBER_ADDR, sizeof(smoke_number));
					FLASH_Save_Para_Encode((uint8 *)&now_smoke_number_lenth, NOW_SMOKE_NUMBER_LENTH_ADDR, sizeof(now_smoke_number_lenth));
					menu_state = 0;
					ret = 0;
					break;

				case KEY_UP:
					break;
					
				case KEY_DOWN:
					break;
				
				case KEY_LEFT:
					break;

				case KEY_RIGHT:
					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}


uint8 Read_Smoke_Mode_Number(void)
{
	//uint32 temp=0;
	uint8 menu_state = 1;
	uint8 update = 1;
	//uint8 update_all = 1;
	//uint8 index;
	uint8 key;
	uint8 string1[20];
	uint8 string2[20];
	uint8 string3[20];
	uint8 ret;
	uint8 x1,y1;
	uint8 x2,y2;
	//const uint8 time_index[] = {0,1,0,1,2,3,4,5,6,7,8,9};
	//uint8 input_index;
	uint8 start_p = 0; // 页数
	uint8 p = 1; // 当前手指	
	
	//index=10;
	//input_index = 0;

	//w1 = 34;
	//w2 = 35;

	while(menu_state){
		if(update == 1){
			update = 0;
			LCD_Clear();
			GUI_PutStringConst14x14_7x14(0,7,binding_temp_module_number[2].item_string);
			if(now_smoke_number_lenth >= 3){
				sprintf((char*)string1, "%02d:%d", start_p+1,smoke_number[start_p]);
				sprintf((char*)string2, "%02d:%d", start_p+2,smoke_number[start_p+1]);
				sprintf((char*)string3, "%02d:%d", start_p+3,smoke_number[start_p+2]);
			}else if(now_smoke_number_lenth == 2){
				sprintf((char*)string1, "%02d:%d", 1,smoke_number[0]);
				sprintf((char*)string2, "%02d:%d", 2,smoke_number[1]);
			}else if(now_smoke_number_lenth == 1){
				sprintf((char*)string1, "%02d:%d", 1,smoke_number[0]);
			}else{
				sprintf((char*)string1, "NULL", 0);
			}
			x1 = 20;
			y1 = 20;
			GUI_PutString7x14(x1, y1, (char*)string1);
			x2 = 20;
			y2 = 34;
			GUI_PutString7x14(x2, y2, (char*)string2);
			x2 = 20;
			y2 = 48;
			GUI_PutString7x14(x2, y2, (char*)string3);
			Display_PIC(0, p*14+6, 16, 12, hand_bmp);
			LCD_Update();
		}

		IWDG_ReloadCounter();
		
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					
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
						if(now_smoke_number_lenth > 3){						
							p = 3;
							start_p = now_smoke_number_lenth-3;
						}else{
							p = now_smoke_number_lenth;
							start_p = 0;
						}
					}
					update = 1;
					break;
					
				case KEY_DOWN:
					if(p == 1){
						if(now_smoke_number_lenth > 1){
							p = 2;
						}
					}
					else if(p == 2){
						if(start_p+3 == now_smoke_number_lenth){
							p = 3;
						}else if(start_p+3 < now_smoke_number_lenth){
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
				
				case KEY_LEFT:
					update = 1;
					break;

				case KEY_RIGHT:
					update = 1;
					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}


uint8 Open_T_Start(void){
	fibre_optical_enable = 1;
	FLASH_Save_Para_Encode((uint8 *)&fibre_optical_enable, FIBRE_OPTICAL_ENABLE_ADDR, sizeof(fibre_optical_enable));
	return QUIT_CURRENT_LIST;
}

uint8 Close_T_Start(void){
	fibre_optical_enable = 0;
	FLASH_Save_Para_Encode((uint8 *)&fibre_optical_enable, FIBRE_OPTICAL_ENABLE_ADDR, sizeof(fibre_optical_enable));
	return QUIT_CURRENT_LIST;
}

uint8 Open_Water_Level_Start(void){
	water_level_enable = 1;
	FLASH_Save_Para_Encode((uint8 *)&water_level_enable, WATER_LEVEL_ENABLE_ADDR, sizeof(water_level_enable));
	return QUIT_CURRENT_LIST;
}

uint8 Close_Water_Level_Start(void){
	water_level_enable = 0;
	FLASH_Save_Para_Encode((uint8 *)&water_level_enable, WATER_LEVEL_ENABLE_ADDR, sizeof(water_level_enable));
	return QUIT_CURRENT_LIST;
}


uint8 System_Inf_State(void)
{
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 key;
	uint8 string1[20];
	int8 string2[20];
	uint8 ret;
	uint8 x1,y1;
	uint16 count = 0;
	uint32 temp_id=0;
	uint32 last_temp_id=0;
	uint8 temper=0,v=0;
	uint8 i;

	LCD_Clear();
	GUI_PutStringConst14x14_7x14(0,7,"在线查看");
	memset(gCC2500RxBuf,0,32);
	while(menu_state){

		if(update == 1){
			update = 0;
			if(last_temp_id != temp_id){
				count=1;
				last_temp_id = temp_id;
			}else{
				count++;
			}
			sprintf((char*)string1, "NUM:%09d", temp_id);
			x1 = 20;
			y1 = 25;
			GUI_PutString7x14(x1, y1, (char*)string1);
			if(gCC2500RxBuf[1] == DEVICE_TYPE_MOVE && gCC2500RxBuf[9]==1){
				sprintf((char*)string2, "error:%d", count);
			}else{
				//sprintf((char*)string2, "ok:%d	 ", count);
				sprintf((char*)string2, "ok:%d  t=%d v=%d ", count , temper,v );
			}
			GUI_PutString7x14(20, 40, string2);
			
			LCD_Update();
			os_dly_wait(100);
		}
		menu_flag = 1;
		update = Read_Si24r1_Data(Rf_channel_num , 0);
		if(update == 1){
			temper = gCC2500RxBuf[8+0];
			v = gCC2500RxBuf[8+5];

			//设备编号
			temp_id = ((uint32)gCC2500RxBuf[4]<<24);
			temp_id |= ((uint32)gCC2500RxBuf[5]<<16);
			temp_id |= ((uint32)gCC2500RxBuf[6]<<8);
			temp_id |= ((uint32)gCC2500RxBuf[7]<<0);
			
			//此处需要接收温度值，否则会出线上传0的情况发生
			for(i=0;i<mode_number_lenth;i++){
				if(temp_number[i]==temp_id)
				{
					temp_alarm_com_count[i] = 0;
					temp_com_value[i][0] = gCC2500RxBuf[8+0];//温度1
					temp_com_value[i][1] = gCC2500RxBuf[8+1];//温度2
					temp_com_value[i][2] = gCC2500RxBuf[8+2];//温度3
					temp_com_value[i][3] = gCC2500RxBuf[8+3];//温度4
					temp_com_value[i][4] = gCC2500RxBuf[8+4];//温度5
					temp_com_value[i][5] = gCC2500RxBuf[8+5];//电压
				}
			}
		}
		IWDG_ReloadCounter();
		
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 300);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					menu_state = 0;
					ret = 1;
					break;

				case KEY_UP:
					break;
					
				case KEY_DOWN:
					break;
				
				case KEY_LEFT:
					break;

				case KEY_RIGHT:
					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}

uint8 Query_online_device(void)
{
	//uint32 temp=0;
	uint8 menu_state = 1;
	uint8 update = 1;
	//uint8 update_all = 1;
	//uint8 index;
	uint8 key;
	uint8 string1[20];
	uint8 string2[20];
	uint8 string3[20];
	uint8 i;
	uint8 ret;
	uint8 x1,y1;
	uint8 x2,y2;
	//const uint8 time_index[] = {0,1,0,1,2,3,4,5,6,7,8,9};
	//uint8 input_index;
	uint8 start_p = 0; // 页数
	uint8 p = 1; // 当前手指	
	uint32 number_buff[50];
	uint8 number_buff_lenth;

	number_buff_lenth = 0;
	for(i=0;i<mode_number_lenth;i++){
		if(online_number[i]&0x01){
			number_buff[number_buff_lenth++] = temp_number[i];
		}
	}
	for(i=0;i<mode_number_lenth;i++){
		if(online_number[i]&0x02){
			number_buff[number_buff_lenth++] = move_number[i];
		}
	}

	memset(string1,0,20);
	memset(string2,0,20);
	memset(string3,0,20);

	
	//index=10;
	//input_index = 0;

	//w1 = 34;
	//w2 = 35;

	while(menu_state){
		if(update == 1){
			update = 0;
			LCD_Clear();
			GUI_PutStringConst14x14_7x14(0,7,"Link设备");
			if(number_buff_lenth >= 3){
				sprintf((char*)string1, "%02d:%d", start_p+1,number_buff[start_p]);
				sprintf((char*)string2, "%02d:%d", start_p+2,number_buff[start_p+1]);
				sprintf((char*)string3, "%02d:%d", start_p+3,number_buff[start_p+2]);
			}else if(number_buff_lenth == 2){
				sprintf((char*)string1, "%02d:%d", 1,number_buff[0]);
				sprintf((char*)string2, "%02d:%d", 2,number_buff[1]);
			}else if(number_buff_lenth == 1){
				sprintf((char*)string1, "%02d:%d", 1,number_buff[0]);
			}else{
				sprintf((char*)string1, "NULL", 0);
			}
			x1 = 20;
			y1 = 20;
			GUI_PutString7x14(x1, y1, (char*)string1);
			x2 = 20;
			y2 = 34;
			GUI_PutString7x14(x2, y2, (char*)string2);
			x2 = 20;
			y2 = 48;
			GUI_PutString7x14(x2, y2, (char*)string3);
			Display_PIC(0, p*14+6, 16, 12, hand_bmp);
			LCD_Update();
		}

		IWDG_ReloadCounter();
		
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					
					break;

				case KEY_UP:
					if(number_buff_lenth == 0){
						update = 1;
						break;
					}
					
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
						if(number_buff_lenth > 3){						
							p = 3;
							start_p = number_buff_lenth-3;
						}else{
							p = number_buff_lenth;
							start_p = 0;
						}
					}
					update = 1;
					break;
					
				case KEY_DOWN:
					if(number_buff_lenth == 0){
						update = 1;
						break;
					}
					
					if(p == 1){
						if(number_buff_lenth > 1){
							p = 2;
						}
					}
					else if(p == 2){
						if(start_p+3 == number_buff_lenth){
							p = 3;
						}else if(start_p+3 < number_buff_lenth){
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
				
				case KEY_LEFT:
					update = 1;
					break;

				case KEY_RIGHT:
					update = 1;
					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}

uint8 Send_BC95_Data(void)
{
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 key;
	uint8 string1[20];
	int8 string2[20];
	uint8 ret;
	uint8 x1,y1;
	uint16 count = 0;
	uint32 temp_id=0;
	uint32 last_temp_id=0;


	LCD_Clear();
	GUI_PutStringConst14x14_7x14(0,7,main_menu_items[11].item_string);

	while(menu_state){

		if(update == 1){
			update = 0;
			temp_id = ((uint32)gCC2500RxBuf[4]<<24);
			temp_id |= ((uint32)gCC2500RxBuf[5]<<16);
			temp_id |= ((uint32)gCC2500RxBuf[6]<<8);
			temp_id |= ((uint32)gCC2500RxBuf[7]<<0);
			if(last_temp_id != temp_id){
				count=1;
				last_temp_id = temp_id;
			}else{
				count++;
			}
			sprintf((char*)string1, "NUM:%09d", temp_id);
			x1 = 20;
			y1 = 25;
			GUI_PutString7x14(x1, y1, (char*)string1);
			if(gCC2500RxBuf[1] == DEVICE_TYPE_MOVE && gCC2500RxBuf[9]==1){
				sprintf((char*)string2, "error:%d", count);
			}else{
				sprintf((char*)string2, "ok:%d	 ", count);
			}
			GUI_PutString7x14(20, 40, string2);
			
			LCD_Update();
			os_dly_wait(100);
		}

		IWDG_ReloadCounter();
		
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					menu_state = 0;
					ret = 1;
					break;

				case KEY_UP:
					break;
					
				case KEY_DOWN:
					break;
				
				case KEY_LEFT:
					break;

				case KEY_RIGHT:
					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}


uint8 Set_RFchannelNum(void)
{
	uint32 temp=0;
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 index;
	uint8 key;
	uint8 string[20];
	//uint8 i;
	uint8 ret;
	uint8 x,y,w;
	const uint8 time_index[6] = {0,1,2,3,4,5};

	LCD_Clear();
	GUI_PutStringConst14x14_7x14(0,7,"设置RFCH");
	index=0;
	
	sprintf((char*)string, "%d ", Rf_channel_num);

	while(menu_state){
		if((update == 1)){
            update = 0;
            w = Get_TxtLength14x14(string);
            x = (GUI_LCM_XMAX - w)/2;
            y = 25;
			GUI_PutString7x14(x, y, (char*)string);
			
            w = time_index[index]*7;
            Display_HLine(x + w, y+13, x+w+5, 1);
            w = time_index[(index + 1)%4]*7;
            Display_HLine(x + w, y+13, x+w+5, 0);
			w = time_index[(index + 2)%4]*7;
            Display_HLine(x + w, y+13, x+w+5, 0);
			w = time_index[(index + 3)%4]*7;
            Display_HLine(x + w, y+13, x+w+5, 0);
            
            LCD_Update();
        }
		IWDG_ReloadCounter();
		
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					temp = (string[0] - '0');
					Rf_channel_num = temp;
					FLASH_Save_Para_Encode((uint8 *)&Rf_channel_num , RF_CHANNEL_NUM_ADDR, sizeof(Rf_channel_num));
					
					menu_state = 0;
					ret = 1;
					break;

				case KEY_UP:
					if(string[0] < '9'){
						string[0]++;
					}else{
						string[0] = '0';
					}					
					update = 1;
					break;
					
				case KEY_DOWN:
					if(string[0] > '0'){
						string[0]--;
					}else{
						string[0] = '9';
					}
					update = 1;
					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}



uint8 Set_RFChannelForLinkTemp(void)
{
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 key;
	uint8 string1[20];
	int8 string2[20];
	uint8 ret;
	uint8 x1,y1;
	uint16 count = 0;
	uint32 temp_id=0;
	uint32 last_temp_id=0;
	uint8 now_index = 0;
	uint8 temper=0,v=0;

	LCD_Clear();
	GUI_PutStringConst14x14_7x14(0,7,"Link");
	memset(gCC2500RxBuf,0,32);
	while(menu_state){

		if(update == 1){
			update = 0;
			temp_id = temp_number[now_index];
			if(last_temp_id != temp_id){
				count=1;
				last_temp_id = temp_id;
			}else{
				count++;
			}
			sprintf((char*)string1, "NUM:%09d", temp_id);
			x1 = 20;
			y1 = 25;
			GUI_PutString7x14(x1, y1, (char*)string1);
			#if 0
			sprintf((char*)string2, "ok:%d	 ", count);
			#else
			sprintf((char*)string2, "ok:%d	t=%d v=%d ", count , temper,v );
			#endif
			GUI_PutString7x14(20, 40, string2);
			
			LCD_Update();
			os_dly_wait(100);
		}
		menu_flag = 1;
		Set_Rf_channel_flag = 1;
		update = Read_Si24r1_Data(DEFAULT_CH,temp_id);
		if(update == 1){
			temper = gCC2500RxBuf[8+0];
			v = gCC2500RxBuf[8+5];
		}
		if(update == 1){
			//if(now_temp_number_lenth > 1){
				//if(now_index >= now_temp_number_lenth-1){
					//now_index = 0;
				//}else{
					//now_index++;
				//}
			//}
		}

		IWDG_ReloadCounter();
		
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 150);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					if(now_temp_number_lenth > 1){
						if(now_index >= now_temp_number_lenth-1){
							now_index = 0;
						}else{
							now_index++;
						}
					}
					update = 1;
					break;

				case KEY_UP:
					if(now_temp_number_lenth > 1){
						if(now_index != 0){
							now_index--;
						}else{
							now_index = now_temp_number_lenth-1;
						}
					}
					update = 1;
					break;
					
				case KEY_DOWN:
					if(now_temp_number_lenth > 1){
						if(now_index >= now_temp_number_lenth-1){
							now_index = 0;
						}else{
							now_index++;
						}
					}
					update = 1;
					break;
				
				case KEY_LEFT:
					break;

				case KEY_RIGHT:
					break;

				default:
						break;
			}
			
		}
	}

	Set_Rf_channel_flag = 0;
	return ret;
	 
}

uint8 Set_RFChannelForLinkMove(void)
{
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 key;
	uint8 string1[20];
	int8 string2[20];
	uint8 ret;
	uint8 x1,y1;
	uint16 count = 0;
	uint32 temp_id=0;
	uint32 last_temp_id=0;
	uint8 now_index = 0;


	LCD_Clear();
	GUI_PutStringConst14x14_7x14(0,7,"Link");
	memset(gCC2500RxBuf,0,32);
	while(menu_state){

		if(update == 1){
			update = 0;
			temp_id = move_number[now_index];
			if(last_temp_id != temp_id){
				count=1;
				last_temp_id = temp_id;
			}else{
				count++;
			}
			sprintf((char*)string1, "NUM:%09d", temp_id);
			x1 = 20;
			y1 = 25;
			GUI_PutString7x14(x1, y1, (char*)string1);
			if(gCC2500RxBuf[1] == DEVICE_TYPE_MOVE && gCC2500RxBuf[9]==1){
				sprintf((char*)string2, "error:%d", count);
			}else{
				sprintf((char*)string2, "ok:%d	 ", count);
				//if(now_move_number_lenth > 1){
					//if(now_index >= now_move_number_lenth-1){
						//now_index = 0;
					//}else{
						//now_index++;
					//}
				//}
			}
			GUI_PutString7x14(20, 40, string2);
			
			LCD_Update();
			os_dly_wait(100);
		}
		menu_flag = 1;
		Set_Rf_channel_flag = 1;
		update = Read_Si24r1_Data(DEFAULT_CH,temp_id);

		IWDG_ReloadCounter();
		
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 150);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					if(now_move_number_lenth > 1){
						if(now_index >= now_move_number_lenth-1){
							now_index = 0;
						}else{
							now_index++;
						}
					}
					update = 1;
					break;

				case KEY_UP:
					if(now_move_number_lenth > 1){
						if(now_index != 0){
							now_index--;
						}else{
							now_index = now_move_number_lenth-1;
						}
					}
					update = 1;
					break;
					
				case KEY_DOWN:
					if(now_move_number_lenth > 1){
						if(now_index >= now_move_number_lenth-1){
							now_index = 0;
						}else{
							now_index++;
						}
					}
					update = 1;
					break;
				
				case KEY_LEFT:
					break;

				case KEY_RIGHT:
					break;

				default:
						break;
			}
			
		}
	}

	Set_Rf_channel_flag = 0;
	return ret;
	 
}

uint8 Set_Sensitivity(void)
{
	uint32 temp=0;
	uint8 menu_state = 1;
	uint8 update = 1;
	uint8 index;
	uint8 key;
	uint8 string[20];
	uint8 ret;
	uint8 x,y,w;
	const uint8 time_index[6] = {0,1,2,3,4,5};

	LCD_Clear();
	GUI_PutStringConst14x14_7x14(0,7,main_menu_items[12].item_string);
	index=0;
	
	sprintf((char*)string, "%d ", move_sensitivity);

	while(menu_state){
		if((update == 1)){
            update = 0;
            w = Get_TxtLength14x14(string);
            x = (GUI_LCM_XMAX - w)/2;
            y = 25;
			GUI_PutString7x14(x, y, (char*)string);
			
            w = time_index[0]*7;
            Display_HLine(x + w, y+13, x+w+5, 1);
            
            LCD_Update();
        }
		IWDG_ReloadCounter();
		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 0xffff);
        event_flag = os_evt_get();
		if(event_flag == EVT_KEY_READY && key_value != KEY_NONE){
			Buzzer_50ms();
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					menu_state = 0;
					ret = 0;
					break;

				case KEY_ENTER:
					temp=0;
					temp = (string[0] - '0');
					move_sensitivity = temp;
					FLASH_Save_Para_Encode((uint8 *)&move_sensitivity , MOVE_SENSITIVITY_ADDR, sizeof(move_sensitivity));
					
					menu_state = 0;
					ret = 1;
					break;

				case KEY_UP:
					if(string[index] < '9'){
						string[index]++;
					}else{
						string[index] = '0';
					}					
					update = 1;
					break;
					
				case KEY_DOWN:
					if(string[0] > '0'){
						string[0]--;
					}else{
						string[0] = '9';
					}
					update = 1;
					break;
				
				case KEY_LEFT:		
					update = 1;
					break;

				case KEY_RIGHT:				
					update = 1;
					break;

				default:
						break;
			}
			
		}
	}
	
	return ret;
	 
}

const strMenuItemInfo NB_test[2] = {
    {{"SetNumTimes"}, &always_enable, 0, 0, Set_TestNum},
    {{"TestStatus"}, &always_enable, 0, 0, Test_Status},
};

const strMenuItemInfo set_uploading[4] = {
    // 1启动
    {{"启动"}, &always_enable, 0, 0, Open_Upload_Start},
    // 2停止
    {{"停止"}, &always_enable, 0, 0, Close_Upload_Start},
	// 3测试上传
	{{"测试"}, &always_enable, NB_test, 2, NO_FUNCTION_INDEX},
	// 4状态界面
	{{"NBStatus"}, &always_enable, 0, 0, NB_Status},
};

const strMenuItemInfo binding_temp_module_number[3] = {
    {{"录入模块编号"}, &always_enable, 0, 0, Set_Temp_Mode_Number},
    {{"删除模块编号"}, &always_enable, 0, 0, Del_Temp_Mode_Number},
	{{"录入编号列表"}, &always_enable, 0, 0, Read_Temp_Mode_Number},
};
const strMenuItemInfo binding_move_module_number[3] = {
    {{"录入模块编号"}, &always_enable, 0, 0, Set_Move_Mode_Number},
    {{"删除模块编号"}, &always_enable, 0, 0, Del_Move_Mode_Number},
	{{"录入编号列表"}, &always_enable, 0, 0, Read_Move_Mode_Number},
};
const strMenuItemInfo binding_water_module_number[3] = {
    {{"录入模块编号"}, &always_enable, 0, 0, Set_Water_Mode_Number},
    {{"删除模块编号"}, &always_enable, 0, 0, Del_Water_Mode_Number},
	{{"录入编号列表"}, &always_enable, 0, 0, Read_Water_Mode_Number},
};
const strMenuItemInfo binding_smoke_module_number[3] = {
    {{"录入模块编号"}, &always_enable, 0, 0, Set_Smoke_Mode_Number},
    {{"删除模块编号"}, &always_enable, 0, 0, Del_Smoke_Mode_Number},
	{{"录入编号列表"}, &always_enable, 0, 0, Read_Smoke_Mode_Number},
};
const strMenuItemInfo binding_module_number[4] = {
    {{"测温模块"}, &always_enable, binding_temp_module_number, 3, NO_FUNCTION_INDEX},
    {{"移动检测模块"}, &always_enable, binding_move_module_number, 3, NO_FUNCTION_INDEX},
	{{"水位模块"}, &always_enable, binding_water_module_number, 3, NO_FUNCTION_INDEX},
    {{"烟感模块"}, &always_enable, binding_smoke_module_number, 3, NO_FUNCTION_INDEX},
};

const strMenuItemInfo set_t_switch[2] = {
    {{"开启"}, &always_enable, 0, 0, Open_T_Start},
    {{"关闭"}, &always_enable, 0, 0, Close_T_Start},
};
const strMenuItemInfo t_module_set[2] = {
    {{"功能使能"}, &always_enable, set_t_switch, 2, NO_FUNCTION_INDEX},
    {{"时间间隔"}, &always_enable, 0, 0, Set_T_Interval},
};

const strMenuItemInfo set_water_level_switch[2] = {
    {{"开启"}, &always_enable, 0, 0, Open_Water_Level_Start},
    {{"关闭"}, &always_enable, 0, 0, Close_Water_Level_Start},
};

const strMenuItemInfo Server_Inf[2] = {
    {{"查看服务器"}, &always_enable, 0, 0, Server_Inf_Show},
    {{"设置服务器"}, &always_enable, 0, 0, Server_Inf_Set},
};

const strMenuItemInfo RFchannel_set[2] = {
//    {{"设置"}, &always_enable, 0, 0, Set_RFchannelNum},
	{{"Link温度"}, &always_enable, 0, 0, Set_RFChannelForLinkTemp},
	{{"Link移动"}, &always_enable, 0, 0, Set_RFChannelForLinkMove},
};



//设置
const strMenuItemInfo main_menu_items[MAIN_MENU_ITEM_NUM] = {
    // 1设置编号
    {{"设置编号"}, &always_enable, 0, 0, Set_Number},
    
    // 2查看服务器
    {{"服务器"}, &always_enable, Server_Inf, 2, NO_FUNCTION_INDEX},

	// 3清除报警信息
    {{"清除报警信息"}, &always_enable, 0, 0, Clear_Alarm_Inf},

	// 4上传时间间隔
    {{"上传时间间隔"}, &always_enable, 0, 0, Set_Interval},
    
	// 5采样时间间隔
    {{"采样时间间隔"}, &always_enable, 0, 0, Set_Sample_Interval},

	// 6设置光纤
	{{"设置光纤"}, &always_disable, t_module_set, 2, NO_FUNCTION_INDEX},

	// 7上传启动
    {{"设置上传"}, &always_enable, set_uploading, 4, NO_FUNCTION_INDEX},

	// 8上传启动
    {{"设置水位"}, &always_enable, set_water_level_switch, 2, NO_FUNCTION_INDEX},

	// 9设置温度检测模块id
    {{"设置模块编号"}, &always_enable, binding_module_number, 4, NO_FUNCTION_INDEX},

	// 10系统设备信息状态查看界面
    {{"在线查看"}, &always_enable, 0, 0, System_Inf_State},

	// 11查询在线设备
    {{"设备信息"}, &always_enable, 0, 0, Query_online_device},

	// 12发送数据
    {{"设置RFCH"}, &always_enable, RFchannel_set, 2, NO_FUNCTION_INDEX},

    // 13设置移动报警灵敏度
    {{"设置灵敏度"}, &always_enable, 0, 0, Set_Sensitivity},
	
	// 14版本号查看
    {{"VersionNumber"}, &always_enable, 0, 0, ShowVersion},

	// 15升级版本
    {{"UpLoadApp"}, &always_enable, 0, 0, UpLoadApp},
};


//后台菜单
const strMenuItemInfo background_menu_items[FACTORY_MENU_ITEM_NUM] = {
	{{"后台菜单"}, &always_enable, 0, 0, NO_FUNCTION_INDEX},

};





