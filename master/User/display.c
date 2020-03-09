
/* Includes ------------------------------------------------------------------*/
#include "main.h"  
#include "data.h"
#include "Display.h"
#include "M5311.h"
const uint8 title_str[20] = {"电力通道监控"};

const uint8 number_str[10] = {"编号"};

const uint8 temperature_str[10] = {"温度"};

const uint8 water_str[10] = {"水位"};
const uint8 fibre_optical_str[10] = {"光纤"};
const uint8 alarm_str[10] = {"报警"};
const uint8 normal_str[10] = {"正常"};

const uint8 battryValue_str[10] = {"电压"};


//入口参数
//value:电量0-100
void Display_Battery(uint8 value){
	const uint8 x=100,y=2;
	const uint8 wight=22,hight=11;
	static uint8 last_value = 100;
	uint8 num;
	Display_Rectangle(x,y,wight,hight,1);
	Bar(x+wight,y+3,3,6,1);

	if(value>100){
		value = 100;
	}
	num = ((uint8)(value*0.2+last_value*0.8))*(wight/100.0);
	Bar(x,y,num,hight,1);
	if((int)wight-num > 2){
		Bar(x+num+1,y+1,wight-num-2,hight-1,0);
	}
	last_value = value;
}

//入口参数
//value:
/************************************
0 -113dBm or less
1 -111dBm
2...30 -109dBm... -53dBm
31 -51dBm or greater
99 Not known or not detectable
*************************************/
void Display_Signal(uint8 value){
	const uint8 x=102,y=18;
	const uint8 wight=5,hight=12;
	static uint8 last_value = 31;
	uint8 num;
	num = (value*0.3+last_value*0.7);
	if(num>=20 && num<=31){
		Bar(x,y+8,wight,4,1);
		Bar(x+8,y+4,wight,8,1);
		Bar(x+16,y,wight,hight,1);
	}else if(num>=10 && num<20){
		Bar(x,y+8,wight,4,1);
		Bar(x+8,y+4,wight,8,1);
		Bar(x+16,y,wight,hight,0);
	}else if(num>=2 && num<10){
		Bar(x,y+8,wight,4,1);
		Bar(x+8,y+4,wight,8,0);
		Bar(x+16,y,wight,hight,0);
	}else{
		Bar(x,y+8,wight,4,0);
		Bar(x+8,y+4,wight,8,0);
		Bar(x+16,y,wight,hight,0);
	}
	last_value = value;
}

void Display_Main_View(void){
	uint8 x,y;
	uint8 buff[30];
	uint8 key;

	uint32 event_flag;
	uint8 timeout = 0;
	uint8 back_ret = 1;

	while(back_ret){
		LCD_Clear();
		IWDG_ReloadCounter();

		Get_Vref();
		battery = Get_Battery();
		//logo
		GUI_PutStringConst14x14(2,0, title_str);
		//电池电量
		Display_Battery(100);
		//信号强度
		Display_Signal(signal);
		//编号
		x = 2;
		y = 16;
		sprintf((char*)buff,":%09d",number);
		x += GUI_PutStringConst14x14(x,y, number_str);
		GUI_PutStringConst7x14(x,y, buff);
		//温度
		x = 2;
		y = 32;
		sprintf((char*)buff,":%02d",temperature);//(uint8)(battery_voltage*10)
		x += GUI_PutStringConst14x14(x,y, temperature_str);
		x += GUI_PutStringConst7x14(x,y, buff);
		x += GUI_PutStringConst14x14(x,y, "℃");
		GUI_PutStringConst7x14(x,y, "  ");

		x = 80;
		y = 32;
		sprintf((char*)buff,"%.1f   ",battery_voltage/10.0);//(uint8)(battery_voltage*10)
		//x += GUI_PutStringConst7x14(x,y, buff);
		
		//水位
		x = 2;
		y = 48;
		x += GUI_PutStringConst14x14(x,y, water_str);
		x += GUI_PutStringConst7x14(x,y, ":");
		GUI_PutStringConst14x14(x,y, normal_str);
		/*
		if(water_level == 0){
			x += GUI_PutStringConst14x14(x,y, normal_str);
		}else{
			x += GUI_PutStringConst14x14(x,y, alarm_str);
		}
		*/

		//电压
		x = 64;
		y = 48;
		x += GUI_PutStringConst14x14(x,y, " BT:");
		sprintf((char*)buff,"%02dV",battery_voltage);//(uint8)(battery_voltage*10)
		x += GUI_PutStringConst14x14(x,y, buff);
		LCD_Update();

		os_evt_wait_or(EVT_KEY_READY | EVT_DIS_UPDATE, 1000);
        event_flag = os_evt_get();

		if(event_flag == EVT_KEY_READY){
			key = key_value;
			key_value = KEY_NONE;
			switch(key){
				case KEY_CANCEL:
					Buzzer_50ms();
					Enter_Main_Menu();
					timeout = 0;
					break;
				case KEY_ENTER:
					break;
				case KEY_UP:
					break;
				case KEY_DOWN:
					break;
				case KEY_LEFT:
					break;
				case KEY_RIGHT:
					break;
			}
		}

		//10S没有进入设置，推出显示
		timeout++;
		if(timeout >= 10){
			back_ret = 0;
		}
	}

}



