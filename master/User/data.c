/* Includes ------------------------------------------------------------------*/
#include "Data.h"
#include "Flash_Map.h"
#include "main.h"
#include <string.h>


//**********************************
u8 gCC2500RxBuf[32];
u8 gCC2500TxBuf[32];
__IO uint8_t led_need_blink = 0;//附网标志
__IO uint8_t key_value;
__IO uint8_t set_state;//启动状态，是否手动启动显示
__IO uint8_t TMP112_Alarm = 0;//环境温度报警标志位 1有效
__IO uint8_t OPT3001_Alarm = 0;//光强报警标志位 1有效


uint8 menu_flag;

float Vref;
uint8 SI24_Receive_Enable=0;//2.4G模块使能
int8 temperature = 25;//温度
int8 temperature_buff[4];//温度
uint8 signal = 31;//信号强度
uint8 battery = 100;//电池电量
uint8 battery_voltage = 36;//电池电压
uint8 water_level = 0;// 1 有水，0 无水
uint8 Smoke_Alarm = 0;//0烟感正常，1烟雾报警

uint8 UDP_Buff[1000];
uint32 upload_delay_count;//BC95启动时间计数器
uint32 sample_delay_count;//温度采样时间
uint32 detection_delay_count;//光纤检测时间
uint32 com_delay_count1;//通讯检测时间
uint32 com_delay_count2;//通讯检测时间


uint16 alarm_inf_upload_flag = 0;//已经上传的报警信息标志位  bit0位烟感报警上传 bit1位水位报警上传
uint8 com_error;//通讯错误

uint8 temp_move_alarm;//温度或者移动报警标志  1 温度报警 2 移动报警
uint8 alarm_value;//2.4通讯的报警值
uint32 alarm_number;//2.4通讯的报警编号
uint8 temp_alarm_com_count[20];
uint8 move_alarm_com_count[20];

uint8 Temp_IR_alarm = 0;//光电报警  0没有光电报警   1开始报警，2报警结束
uint8 IR_alarm_Enable=0;//光电报警使能
uint8 IR_alarm;//光电报警  0没有光电报警   1开始报警，2报警结束
uint8 IR_alarm_start;//1开始报警  2结束报警
uint8 IR_alarm_end;//1开始报警  2结束报警
uint8 IR_alarm_time;//
uint8 IR_alarm_flag;

/*******************************************************************************************************/

//EEPROM   START
uint32 number = 100001234;//1+8位唯一编码  1 0000 1234（十进制）
uint8 destinationIP[4] = {118,24,84,211};//101,132,127,130  //{118,24,84,211}
uint16 destinationPort = 1012;//1012  4567

uint32 upload_interval = 6;//0-9999 min  以十分钟为一个单位
uint8 upload_start=1;//0停止上传  1启动上传
uint32 sample_interval = 60;//采样间隔时间0-9999 min
uint8 water_level_enable = 0;//水位检测功能使能
uint32 fibre_optical_interval = 60;//光纤检测时间0-9999 min
uint8 fibre_optical_enable = 0;//光纤检测功能使能
const uint8 mode_number_lenth = 20;
uint8 now_temp_number_lenth = 20;
uint8 now_move_number_lenth = 20;
uint8 now_water_number_lenth = 20;
uint8 now_smoke_number_lenth = 20;
uint32 temp_number[20];//温度监测    2+8位唯一编码  2 0000 1234（十进制）
uint32 move_number[20];//移动监测    3+8位唯一编码  3 0000 1234（十进制）
uint32 water_number[20];//水位监测    4+8位唯一编码  4 0000 1234（十进制）
uint32 smoke_number[20];//烟感监测    5+8位唯一编码  5 0000 1234（十进制）
uint8 online_number[20];//在线编号	bit0表示温度   bit1表示移动     0不在线，1在线

uint8 temperature_alarm_value = 60;//温度上限值，超过则报警
uint8 temperature_alarm_bound = 5;//温度上限值，超过则报警

uint8 temp_com_value[20][6];//报警温度5个和最后一个电压值

//测温模块报警参数
uint8 temp_sample_time = 15;//采样时间
uint8 temp_upload_time = 60;//上传时间
uint8 temp_temperature_alarm = 50;//报警温度
uint8 temp_temperature_bound = 3;//温度上限值，超过则报警

//报警模块参数设置
uint8 Module_upload_time  = 120;//模块上传时间
//移动报警模块参数
uint8 move_detection_time = 5;//检测时间
uint8 move_sensitivity = 5;//灵敏度(次数)


uint8 Test_NB_flag = 0;

uint8 Rf_channel_num = 1;//RF通讯信道 
uint8 Set_Rf_channel_flag = 0;// 设置通讯通道标志  0 通讯模式   1 信道设置模式

//EEPROM   END
/*******************************************************************************************************/
//温度光照模块
uint16 Tmp112Config_Reg = 0;
uint16 Tmp112_LimUp = 0;
uint16 Tmp112_LimDown = 0;


uint16 OPT3001_M_ID = 0;
uint16 OPT3001_D_ID = 0;
uint16 OPT3001Config_Reg = 0;
uint16 OPT3001_LimUp = 0;
uint16 OPT3001_LimDown = 0;
uint32 LightValue = 0;
/*******************************************************************************************************/

//模块报警信息
void Com_Send_Alarm(uint8 alarm_type)
{
	uint8 i;
	uint8 check = 0;
	UDP_Buff[0] = COM_START;
	UDP_Buff[1] = DEVICE_TYPE;
	UDP_Buff[2] = 0x30;//send
	UDP_Buff[3] = 10;//data lenth
	UDP_Buff[4] = (uint8)((number>>24)&0xff);//num  0x100 00 00
	UDP_Buff[5] = (uint8)((number>>16)&0xff);//num  0x100 00
	UDP_Buff[6] = (uint8)((number>>8)&0xff);//num   0x100
	UDP_Buff[7] = (uint8)(number&0xff);//num				0x01
	switch(alarm_type){
	case ALARM_TYPE_SMOKE:
		UDP_Buff[8] = alarm_type;//
		UDP_Buff[9] = 0;
		UDP_Buff[10] = (uint8)((number>>24)&0xff);//num  0x100 00 00
		UDP_Buff[11] = (uint8)((number>>16)&0xff);//num  0x100 00
		UDP_Buff[12] = (uint8)((number>>8)&0xff);//num   0x100
		UDP_Buff[13] = (uint8)(number&0xff);//num				0x01
		break;
	case ALARM_TYPE_TEMP:
		UDP_Buff[8] = alarm_type;//
		UDP_Buff[9] = temperature;
		UDP_Buff[10] = (uint8)((number>>24)&0xff);//num  0x100 00 00
		UDP_Buff[11] = (uint8)((number>>16)&0xff);//num  0x100 00
		UDP_Buff[12] = (uint8)((number>>8)&0xff);//num   0x100
		UDP_Buff[13] = (uint8)(number&0xff);//num				0x01
		break;
	case ALARM_TYPE_WATER:
		UDP_Buff[8] = alarm_type;//
		UDP_Buff[9] = 0;
		UDP_Buff[10] = (uint8)((number>>24)&0xff);//num  0x100 00 00
		UDP_Buff[11] = (uint8)((number>>16)&0xff);//num  0x100 00
		UDP_Buff[12] = (uint8)((number>>8)&0xff);//num   0x100
		UDP_Buff[13] = (uint8)(number&0xff);//num				0x01
		break;
	case ALARM_TYPE_MOVE_MODULE:
		UDP_Buff[8] = alarm_type;//
		UDP_Buff[9] = 0;
		UDP_Buff[10] = (uint8)((alarm_number>>24)&0xff);//num  0x100 00 00
		UDP_Buff[11] = (uint8)((alarm_number>>16)&0xff);//num  0x100 00
		UDP_Buff[12] = (uint8)((alarm_number>>8)&0xff);//num   0x100
		UDP_Buff[13] = (uint8)(alarm_number&0xff);//num				0x01
		break;
	case ALARM_TYPE_TEMP_MODULE:
		UDP_Buff[8] = alarm_type;//
		UDP_Buff[9] = alarm_value;
		UDP_Buff[10] = (uint8)((alarm_number>>24)&0xff);//num  0x100 00 00
		UDP_Buff[11] = (uint8)((alarm_number>>16)&0xff);//num  0x100 00
		UDP_Buff[12] = (uint8)((alarm_number>>8)&0xff);//num   0x100
		UDP_Buff[13] = (uint8)(alarm_number&0xff);//num				0x01
		break;
	case ALARM_TYPE_COM:
		UDP_Buff[8] = alarm_type;//
		UDP_Buff[9] = 0;
		UDP_Buff[10] = (uint8)((alarm_number>>24)&0xff);//num  0x100 00 00
		UDP_Buff[11] = (uint8)((alarm_number>>16)&0xff);//num  0x100 00
		UDP_Buff[12] = (uint8)((alarm_number>>8)&0xff);//num   0x100
		UDP_Buff[13] = (uint8)(alarm_number&0xff);//num				0x01
		break;
    case ALARM_TYPE_TEMP_IR:
		UDP_Buff[8] = alarm_type;//
		UDP_Buff[9] = Temp_IR_alarm;
		UDP_Buff[10] = (uint8)((alarm_number>>24)&0xff);//num  0x100 00 00
		UDP_Buff[11] = (uint8)((alarm_number>>16)&0xff);//num  0x100 00
		UDP_Buff[12] = (uint8)((alarm_number>>8)&0xff);//num   0x100
		UDP_Buff[13] = (uint8)(alarm_number&0xff);//num				0x01
		break;
    case ALARM_TYPE_IR:
		UDP_Buff[8] = alarm_type;//
		UDP_Buff[9] = IR_alarm;
		UDP_Buff[10] = (uint8)((number>>24)&0xff);//num  0x100 00 00
		UDP_Buff[11] = (uint8)((number>>16)&0xff);//num  0x100 00
		UDP_Buff[12] = (uint8)((number>>8)&0xff);//num   0x100
		UDP_Buff[13] = (uint8)(number&0xff);//num				0x01
        break;
    case ALARM_TYPE_SHAKE_LITTLE:
		UDP_Buff[8] = alarm_type;//
		UDP_Buff[9] = alarm_value;
		UDP_Buff[10] = (uint8)((alarm_number>>24)&0xff);//num  0x100 00 00
		UDP_Buff[11] = (uint8)((alarm_number>>16)&0xff);//num  0x100 00
		UDP_Buff[12] = (uint8)((alarm_number>>8)&0xff);//num   0x100
		UDP_Buff[13] = (uint8)(alarm_number&0xff);//num				0x01
        break;
    case ALARM_TYPE_SHAKE_BIG:
		UDP_Buff[8] = alarm_type;//
		UDP_Buff[9] = 0;
		UDP_Buff[10] = (uint8)((alarm_number>>24)&0xff);//num  0x100 00 00
		UDP_Buff[11] = (uint8)((alarm_number>>16)&0xff);//num  0x100 00
		UDP_Buff[12] = (uint8)((alarm_number>>8)&0xff);//num   0x100
		UDP_Buff[13] = (uint8)(alarm_number&0xff);//num				0x01
        break;
	}
	for(i=0;i<14;i++){
		check += UDP_Buff[i];
	}
	UDP_Buff[14] = check;
	UDP_Buff[15] = COM_STOP;//
	
}

//设备状态
void Com_Send_State(void)
{
	uint16 i;
	uint8 check = 0;
	
	uint8 temp_num = 0;//在线的温度模块数量
	uint8 temp_index[20];
	uint8 value = 0;
	
	for(i = 0; i<20; i++){
		if(online_number[i] & 0x01){
			temp_index[temp_num] = i;
			temp_num++;
		}
	}
	
	UDP_Buff[0] = COM_START;
	UDP_Buff[1] = DEVICE_TYPE;
	UDP_Buff[2] = 0x20;//send
	UDP_Buff[3] = 13+temp_num*10;//data lenth   now_temp_number_lenth*10;
	UDP_Buff[4] = (uint8)((number>>24)&0xff);//num
	UDP_Buff[5] = (uint8)((number>>16)&0xff);//num
	UDP_Buff[6] = (uint8)((number>>8)&0xff);//num
	UDP_Buff[7] = (uint8)(number&0xff);//num
	UDP_Buff[8] = (uint8)(temperature_buff[0]);//温度
	UDP_Buff[9] = (uint8)(temperature_buff[1]);//温度
	UDP_Buff[10] = (uint8)(temperature_buff[2]);//温度
	UDP_Buff[11] = (uint8)(temperature_buff[3]);//温度
	UDP_Buff[12] = (Smoke_Alarm<<7)|(water_level<<0);//烟感报警和水位报警
	UDP_Buff[13] = battery_voltage;//电池电量
	UDP_Buff[14] = (uint8)(upload_interval&0xff);//时间间隔
	UDP_Buff[15] = signal;//信号强度
	UDP_Buff[16] = temp_num;//now_temp_number_lenth;//温度报警模块个数
	
	for(i=0;i<temp_num;i++){
		value = temp_index[i];
		UDP_Buff[16+i*10+1] = (uint8)((temp_number[value]>>24)&0xff);//num
		UDP_Buff[16+i*10+2] = (uint8)((temp_number[value]>>16)&0xff);//num
		UDP_Buff[16+i*10+3] = (uint8)((temp_number[value]>>8)&0xff);//num
		UDP_Buff[16+i*10+4] = (uint8)((temp_number[value]>>0)&0xff);//num
		UDP_Buff[16+i*10+5] = temp_com_value[value][0];//temp1
		UDP_Buff[16+i*10+6] = temp_com_value[value][1];//temp2
		UDP_Buff[16+i*10+7] = temp_com_value[value][2];//temp3
		UDP_Buff[16+i*10+8] = temp_com_value[value][3];//temp4
		UDP_Buff[16+i*10+9] = temp_com_value[value][4];//temp5
		UDP_Buff[16+i*10+10] = temp_com_value[value][5];//电压
	}
	
	for(i=0;i<17+temp_num*10;i++){
		check += UDP_Buff[i];
	}
	
	UDP_Buff[i++] = check;//check
	UDP_Buff[i++] = COM_STOP;//data2
	
}



//2.4G通讯回应温度监测板子
void Com_Respond_Temp(void)
{
    uint8 i;
    uint8 check = 0;
    gCC2500TxBuf[0] = COM_START;
    gCC2500TxBuf[1] = DEVICE_TYPE_TEMP;
    gCC2500TxBuf[2] = gCC2500RxBuf[2];//控制码
    gCC2500TxBuf[3] = 10;//data lenth
    gCC2500TxBuf[4] = gCC2500RxBuf[4];//num
    gCC2500TxBuf[5] = gCC2500RxBuf[5];//num
    gCC2500TxBuf[6] = gCC2500RxBuf[6];//num
    gCC2500TxBuf[7] = gCC2500RxBuf[7];//num
    gCC2500TxBuf[8] = temp_sample_time;//采样时间(min)
    gCC2500TxBuf[9] = temp_upload_time;//上传时间(min)
    gCC2500TxBuf[10] = temp_temperature_alarm;//报警温度
    gCC2500TxBuf[11] = temp_temperature_bound;//报警温度带宽
    gCC2500TxBuf[12] = 0;//IR_alarm
    gCC2500TxBuf[13] = 0;//NC
    for(i=0;i<14;i++){
        check += gCC2500TxBuf[i];
    }
    gCC2500TxBuf[14] = check;//check
    gCC2500TxBuf[15] = COM_STOP;//data2
    
}


//2.4G通讯回应移动监测板子
void Com_Respond_Move(void)
{
    uint8 i;
    uint8 check = 0;
    gCC2500TxBuf[0] = COM_START;
    gCC2500TxBuf[1] = DEVICE_TYPE_MOVE;
    gCC2500TxBuf[2] = gCC2500RxBuf[2];//send
    gCC2500TxBuf[3] = 10;//data lenth
    gCC2500TxBuf[4] = gCC2500RxBuf[4];//num
    gCC2500TxBuf[5] = gCC2500RxBuf[5];//num
    gCC2500TxBuf[6] = gCC2500RxBuf[6];//num
    gCC2500TxBuf[7] = gCC2500RxBuf[7];//num
    if(gCC2500RxBuf[9] == 0){
    	gCC2500TxBuf[8] = 0x80;//应答
    }else{
    	gCC2500TxBuf[8] = 0xee;//应答
    }
    gCC2500TxBuf[9] = move_detection_time;//检测时间
    gCC2500TxBuf[10] = move_sensitivity;//灵敏度(次数)
    gCC2500TxBuf[11] = 0;//NC
    gCC2500TxBuf[12] = 0;//NC
    gCC2500TxBuf[13] = 0;//NC
    for(i=0;i<14;i++){
        check += gCC2500TxBuf[i];
    }
    gCC2500TxBuf[14] = check;//check
    gCC2500TxBuf[15] = COM_STOP;//data2
}
//2.4G通讯回应水位监测板子
void Com_Respond_Water(void)
{
    uint8 i;
    uint8 check = 0;
    gCC2500TxBuf[0] = COM_START;
    gCC2500TxBuf[1] = DEVICE_TYPE_WATER;
    gCC2500TxBuf[2] = gCC2500RxBuf[2];//send
    gCC2500TxBuf[3] = 10;//data lenth
    gCC2500TxBuf[4] = gCC2500RxBuf[4];//num
    gCC2500TxBuf[5] = gCC2500RxBuf[5];//num
    gCC2500TxBuf[6] = gCC2500RxBuf[6];//num
    gCC2500TxBuf[7] = gCC2500RxBuf[7];//num
    gCC2500TxBuf[8] = Module_upload_time;//上传时间间隔
    gCC2500TxBuf[9] = 0;//NC
    gCC2500TxBuf[10] = 0;//NC
    gCC2500TxBuf[11] = 0;//NC
    gCC2500TxBuf[12] = 0;//NC
    gCC2500TxBuf[13] = 0;//NC
    for(i=0;i<14;i++){
        check += gCC2500TxBuf[i];
    }
    gCC2500TxBuf[14] = check;//check
    gCC2500TxBuf[15] = COM_STOP;//data
}
//2.4G通讯回应烟感监测板子
void Com_Respond_Smoke(void)
{
    uint8 i;
    uint8 check = 0;
    gCC2500TxBuf[0] = COM_START;
    gCC2500TxBuf[1] = DEVICE_TYPE_SMOKE;
    gCC2500TxBuf[2] = gCC2500RxBuf[2];//send
    gCC2500TxBuf[3] = 10;//data lenth
    gCC2500TxBuf[4] = gCC2500RxBuf[4];//num
    gCC2500TxBuf[5] = gCC2500RxBuf[5];//num
    gCC2500TxBuf[6] = gCC2500RxBuf[6];//num
    gCC2500TxBuf[7] = gCC2500RxBuf[7];//num
    gCC2500TxBuf[8] = Module_upload_time;//上传时间间隔
    gCC2500TxBuf[9] = 0;//NC
    gCC2500TxBuf[10] = 0;//NC
    gCC2500TxBuf[11] = 0;//NC
    gCC2500TxBuf[12] = 0;//NC
    gCC2500TxBuf[13] = 0;//NC
    for(i=0;i<14;i++){
        check += gCC2500TxBuf[i];
    }
    gCC2500TxBuf[14] = check;//check
    gCC2500TxBuf[15] = COM_STOP;//data
}


//2.4G通讯回应移动监测板子
void Com_ForLink_Temp(uint8 ch)
{
    uint8 i;
    uint8 check = 0;
	
    gCC2500TxBuf[0] = COM_START;
    gCC2500TxBuf[1] = DEVICE_TYPE_TEMP;
    gCC2500TxBuf[2] = gCC2500RxBuf[2];//控制码
    gCC2500TxBuf[3] = 10;//data lenth
    gCC2500TxBuf[4] = gCC2500RxBuf[4];//num
    gCC2500TxBuf[5] = gCC2500RxBuf[5];//num
    gCC2500TxBuf[6] = gCC2500RxBuf[6];//num
    gCC2500TxBuf[7] = gCC2500RxBuf[7];//num
    gCC2500TxBuf[8] = temp_sample_time;//采样时间(min)
    gCC2500TxBuf[9] = temp_upload_time;//上传时间(min)
    gCC2500TxBuf[10] = temp_temperature_alarm;//报警温度
    gCC2500TxBuf[11] = temp_temperature_bound;//报警温度带宽
    gCC2500TxBuf[12] = 0xaa;//NC
    gCC2500TxBuf[13] = ch;//NC
    for(i=0;i<14;i++){
        check += gCC2500TxBuf[i];
    }
    gCC2500TxBuf[14] = check;//check
    gCC2500TxBuf[15] = COM_STOP;//data2
}

//2.4G通讯回应移动监测板子
void Com_ForLink_Move(uint8 ch)
{
    uint8 i;
    uint8 check = 0;
	
    gCC2500TxBuf[0] = COM_START;
    gCC2500TxBuf[1] = DEVICE_TYPE_TEMP;
    gCC2500TxBuf[2] = gCC2500RxBuf[2];//控制码
    gCC2500TxBuf[3] = 10;//data lenth
    gCC2500TxBuf[4] = gCC2500RxBuf[4];//num
    gCC2500TxBuf[5] = gCC2500RxBuf[5];//num
    gCC2500TxBuf[6] = gCC2500RxBuf[6];//num
    gCC2500TxBuf[7] = gCC2500RxBuf[7];//num
    gCC2500TxBuf[8] = 0;//采样时间(min)
    gCC2500TxBuf[9] = move_detection_time;//上传时间(min)
    gCC2500TxBuf[10] = move_sensitivity;//报警温度
    gCC2500TxBuf[11] = 0;//报警温度带宽
    gCC2500TxBuf[12] = 0xaa;//NC
    gCC2500TxBuf[13] = ch;//NC
    for(i=0;i<14;i++){
        check += gCC2500TxBuf[i];
    }
    gCC2500TxBuf[14] = check;//check
    gCC2500TxBuf[15] = COM_STOP;//data2
}



uint8 Read_Si24r1_Data(uint8 ch , uint32 num)
{
	uint8 i;
	uint16 count;
	uint8 check;
	uint32 temp_id;
	uint8 send_flag = 0;// 1回复温度2回复位移3回复水位4回复烟感
	uint8 ret = 0;
    uint8 check_index;
    uint32 flag = 0;

	uint8 sendOk = 0;
	uint8 sendCnt = 0;
	
	SI24R1_Init();
	SI24R1_RX_Mode(ch);
	count=0;

	IWDG_ReloadCounter();
	while(count<5000){//8000 20ms   count<8000
		count++;
		if(IRQ_IN == 0)
		{
			IWDG_ReloadCounter();
			if(!SI24R1_RxPacket(gCC2500RxBuf)){
				if((gCC2500RxBuf[0]==COM_START && gCC2500RxBuf[15]==COM_STOP && ((gCC2500RxBuf[1]==DEVICE_TYPE_MOVE) || (gCC2500RxBuf[1]==DEVICE_TYPE_MOVE2)))
                    ||(gCC2500RxBuf[0]==COM_START && gCC2500RxBuf[16]==COM_STOP && gCC2500RxBuf[1]==DEVICE_TYPE_TEMP)
					||(gCC2500RxBuf[0]==COM_START && gCC2500RxBuf[15]==COM_STOP && gCC2500RxBuf[1]==DEVICE_TYPE_WATER)
					||(gCC2500RxBuf[0]==COM_START && gCC2500RxBuf[15]==COM_STOP && gCC2500RxBuf[1]==DEVICE_TYPE_SMOKE)){
						
                    if(gCC2500RxBuf[1] == DEVICE_TYPE_TEMP){
                        check_index = 15;
                    }else{
                        check_index = 14;
                    }			
					SI24R1_TX_Mode(ch);
					check = 0;
					for(i=0;i<check_index;i++){
						check += gCC2500RxBuf[i];
					}
					
					if(check == gCC2500RxBuf[check_index]){
						//LED_Open();
						if(Set_Rf_channel_flag == 0){
							IWDG_ReloadCounter();
							temp_id = ((uint32)gCC2500RxBuf[4]<<24);
							temp_id |= ((uint32)gCC2500RxBuf[5]<<16);
							temp_id |= ((uint32)gCC2500RxBuf[6]<<8);
							temp_id |= ((uint32)gCC2500RxBuf[7]<<0);
							send_flag = 0;
							for(i=0;i<mode_number_lenth;i++){
								IWDG_ReloadCounter();
								if(temp_id == temp_number[i] 
								|| temp_id == move_number[i]
								|| temp_id == water_number[i]
								|| temp_id == smoke_number[i]){
									if(temp_id == temp_number[i]){
										online_number[i] |= 0x01;
										send_flag = 1;
									}else if(temp_id == move_number[i]){
										online_number[i] |= 0x02;
										send_flag = 2;
									}else if(temp_id == water_number[i]){
										send_flag = 3;
									}else if(temp_id == smoke_number[i]){
										send_flag = 4;
									}
									break;
								}
							}
                 
							//回应指令
							if(send_flag != 0){
								if(send_flag==1){
									Com_Respond_Temp();
								}else if(send_flag==2){
									Com_Respond_Move();
								}else if(send_flag==3){
									Com_Respond_Water();
								}else if(send_flag==4){
									Com_Respond_Smoke();
								}else{
									Com_Respond_Temp();
								}

								if(menu_flag==0 && gCC2500RxBuf[8]==0 && send_flag==2){
									//在前台，不处理移动报警模块的待机安装指令，只有在后台菜单界面下接收处理
									if(gCC2500RxBuf[1] == DEVICE_TYPE_MOVE){
									    memset(gCC2500TxBuf,0,32);
                                    }
								}
							}
						}
						else{
							gCC2500RxBuf[4] = (num>>24)&0xff;
							gCC2500RxBuf[5] = (num>>16)&0xff;
							gCC2500RxBuf[6] = (num>>8)&0xff;
							gCC2500RxBuf[7] = (num>>0)&0xff;
							if((gCC2500RxBuf[1] == DEVICE_TYPE_MOVE)||(gCC2500RxBuf[1] == DEVICE_TYPE_MOVE2)){//300010000
                                if(gCC2500RxBuf[1] == DEVICE_TYPE_MOVE2){
							        delay_ms(15);
                                }
								Com_ForLink_Move(Rf_channel_num);
							}else{
								Com_ForLink_Temp(Rf_channel_num);
							}
						}

						sendOk = 0;
						sendCnt = 0;
						do{
							sendOk = SI24R1_TxPacket(gCC2500TxBuf);
							sendCnt ++;
							delay_ms(1);
							IWDG_ReloadCounter();
						}while((sendOk != TX_DS)  && (sendCnt<3));
						count = 8000;
						ret = 1;
						//这里不能直接退出，退出后不执行2.4G低功耗模式，会导致接收不正常
						break;
					}
				}
			}
		}
		
	}
	
	SI24R1_Standby_Mode();
	CC2500_GPIO_Set_Input();
	return ret;

}

//初始化变量
void Variable_Flash(uint8 default_value_flat)
{
	char page_bytes[ENCODE_FACTOR_END_ADD];
	uint16 i,j;
	uint8 check_sum_read, check_sum_calc;
	uint8 set_default_flag;
	uint8 ret;

	set_default_flag = 0;

	// Read Keep-Page bytes
      	for(j=0;j<3;j++){
	    FLASH_Get_Para_Decode((uint8*)page_bytes,ENCODE_FACTOR_START_ADD,ENCODE_FACTOR_END_ADD);
	    check_sum_read = page_bytes[ENCODE_FACTOR_END_ADD-1];
	    for(i = 0, check_sum_calc = 0; i < ENCODE_FACTOR_END_ADD-1; i++){
	        check_sum_calc += *(page_bytes+i);
	    }

	    if (check_sum_calc == check_sum_read){
	         if (strcmp(page_bytes,VSRSION) != 0){
	            set_default_flag = 1;
	         }else{
	         	break;
	         }
	    }
	    else{
	        set_default_flag  = 1;
	    }

	}
	if(default_value_flat){
		set_default_flag  = 1;
	}


	if (set_default_flag){

		memset(page_bytes,0,ENCODE_FACTOR_END_ADD);
		strcpy(page_bytes,VSRSION);

		for(i = 0, check_sum_calc = 0; i < ENCODE_FACTOR_END_ADD-1; i++){
			check_sum_calc += *(page_bytes+i);
		}
		page_bytes[ENCODE_FACTOR_END_ADD-1] = check_sum_calc;
		FLASH_Save_Para_Encode((uint8*)page_bytes,ENCODE_FACTOR_START_ADD,ENCODE_FACTOR_END_ADD);
	}


	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&number, NUMBER_ADDR, sizeof(number));
	}
	if(ret){
		number = 100000001;
		FLASH_Save_Para_Encode((uint8 *)&number, NUMBER_ADDR, sizeof(number));
	}

	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&destinationIP, DESTINATIONIP_ADDR, sizeof(destinationIP));
	}
	if(ret){
		destinationIP[0] = 118;//118  101
		destinationIP[1] = 24;//24  132
		destinationIP[2] = 84;//84  127
		destinationIP[3] = 211;//211   130
		FLASH_Save_Para_Encode((uint8 *)&destinationIP, DESTINATIONIP_ADDR, sizeof(destinationIP));
	}

	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&destinationPort, DESTINATIONPORT_ADDR, sizeof(destinationPort));
	}
	if(ret){
		destinationPort = 1012;//4567
		FLASH_Save_Para_Encode((uint8 *)&destinationPort, DESTINATIONPORT_ADDR, sizeof(destinationPort));
	}

	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&upload_interval, UPLOAD_INTERVAL_ADDR, sizeof(upload_interval));
	}
	if(ret){
		upload_interval = 6;
		FLASH_Save_Para_Encode((uint8 *)&upload_interval, UPLOAD_INTERVAL_ADDR, sizeof(upload_interval));
	}

	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&upload_start, UPLOAD_START_ADDR, sizeof(upload_start));
	}
	if(ret){
		upload_start = 1;
		FLASH_Save_Para_Encode((uint8 *)&upload_start, UPLOAD_START_ADDR, sizeof(upload_start));
	}

	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&sample_interval, SAMPLE_INTERVAL_ADDR, sizeof(sample_interval));
	}
	if(ret){
		sample_interval = 20;
		FLASH_Save_Para_Encode((uint8 *)&sample_interval, SAMPLE_INTERVAL_ADDR, sizeof(sample_interval));
	}

	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&fibre_optical_interval, FIBRE_OPTICAL_INTERVAL_ADDR, sizeof(fibre_optical_interval));
	}
	if(ret){
		fibre_optical_interval = 20;
		FLASH_Save_Para_Encode((uint8 *)&fibre_optical_interval, FIBRE_OPTICAL_INTERVAL_ADDR, sizeof(fibre_optical_interval));
	}
	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&fibre_optical_enable, FIBRE_OPTICAL_ENABLE_ADDR, sizeof(fibre_optical_enable));
	}
	if(ret){
		fibre_optical_enable = 0;
		FLASH_Save_Para_Encode((uint8 *)&fibre_optical_enable, FIBRE_OPTICAL_ENABLE_ADDR, sizeof(fibre_optical_enable));
	}

	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&water_level_enable, WATER_LEVEL_ENABLE_ADDR, sizeof(water_level_enable));
	}
	if(ret){
		water_level_enable = 0;
		FLASH_Save_Para_Encode((uint8 *)&water_level_enable, WATER_LEVEL_ENABLE_ADDR, sizeof(water_level_enable));
	}

	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&temp_number, TEMP_NUMBER_ADDR, sizeof(temp_number));
	}
	if(ret){
		for(i=0;i<mode_number_lenth;i++){
			temp_number[i] = 200000000+0;
		}
		FLASH_Save_Para_Encode((uint8 *)&temp_number, TEMP_NUMBER_ADDR, sizeof(temp_number));
	}

	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&move_number, MOVE_NUMBER_ADDR, sizeof(move_number));
	}
	if(ret){
		for(i=0;i<mode_number_lenth;i++){
			move_number[i] = 300000000+0;
		}
		FLASH_Save_Para_Encode((uint8 *)&move_number, MOVE_NUMBER_ADDR, sizeof(move_number));
	}

	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&water_number, WATER_NUMBER_ADDR, sizeof(water_number));
	}
	if(ret){
		for(i=0;i<mode_number_lenth;i++){
			water_number[i] = 400000000+0;
		}
		FLASH_Save_Para_Encode((uint8 *)&water_number, WATER_NUMBER_ADDR, sizeof(water_number));
	}
	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&smoke_number, SMOKE_NUMBER_ADDR, sizeof(smoke_number));
	}
	if(ret){
		for(i=0;i<mode_number_lenth;i++){
			smoke_number[i] = 500000000+0;
		}
		FLASH_Save_Para_Encode((uint8 *)&smoke_number, SMOKE_NUMBER_ADDR, sizeof(smoke_number));
	}
	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&now_temp_number_lenth, NOW_TEMP_NUMBER_LENTH_ADDR, sizeof(now_temp_number_lenth));
	}
	if(ret){
		now_temp_number_lenth = 0;
		FLASH_Save_Para_Encode((uint8 *)&now_temp_number_lenth, NOW_TEMP_NUMBER_LENTH_ADDR, sizeof(now_temp_number_lenth));
	}

	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&now_move_number_lenth, NOW_MOVE_NUMBER_LENTH_ADDR, sizeof(now_move_number_lenth));
	}
	if(ret){
		now_move_number_lenth = 0;
		FLASH_Save_Para_Encode((uint8 *)&now_move_number_lenth, NOW_MOVE_NUMBER_LENTH_ADDR, sizeof(now_move_number_lenth));
	}
	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&now_water_number_lenth, NOW_WATER_NUMBER_LENTH_ADDR, sizeof(now_water_number_lenth));
	}
	if(ret){
		now_water_number_lenth = 0;
		FLASH_Save_Para_Encode((uint8 *)&now_water_number_lenth, NOW_WATER_NUMBER_LENTH_ADDR, sizeof(now_water_number_lenth));
	}
	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&now_smoke_number_lenth, NOW_SMOKE_NUMBER_LENTH_ADDR, sizeof(now_smoke_number_lenth));
	}
	if(ret){
		now_smoke_number_lenth = 0;
		FLASH_Save_Para_Encode((uint8 *)&now_smoke_number_lenth, NOW_SMOKE_NUMBER_LENTH_ADDR, sizeof(now_smoke_number_lenth));
	}
	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&temperature_alarm_value, TEMPERATURE_ALARM_VALUE_ADDR, sizeof(temperature_alarm_value));
	}
	if(ret){
		temperature_alarm_value = 60;
		FLASH_Save_Para_Encode((uint8 *)&temperature_alarm_value, TEMPERATURE_ALARM_VALUE_ADDR, sizeof(temperature_alarm_value));
	}

	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&temperature_alarm_bound, TEMPERATURE_ALARM_BOUND_ADDR, sizeof(temperature_alarm_bound));
	}
	if(ret){
		temperature_alarm_bound = 10;
		FLASH_Save_Para_Encode((uint8 *)&temperature_alarm_bound, TEMPERATURE_ALARM_BOUND_ADDR, sizeof(temperature_alarm_bound));
	}

	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&temp_sample_time, TEMP_SAMPLE_TIME_ADDR, sizeof(temp_sample_time));
	}
	if(ret){
		temp_sample_time = 15;
		FLASH_Save_Para_Encode((uint8 *)&temp_sample_time, TEMP_SAMPLE_TIME_ADDR, sizeof(temp_sample_time));
	}

	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&temp_upload_time, TEMP_UPLOAD_TIME_ADDR, sizeof(temp_upload_time));
	}
	if(ret){
		temp_upload_time = 60;
		FLASH_Save_Para_Encode((uint8 *)&temp_upload_time, TEMP_UPLOAD_TIME_ADDR, sizeof(temp_upload_time));
	}

	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&temp_temperature_alarm, TEMP_TEMPERATURE_ALARM_ADDR, sizeof(temp_temperature_alarm));
	}
	if(ret){
		temp_temperature_alarm = 60;
		FLASH_Save_Para_Encode((uint8 *)&temp_temperature_alarm, TEMP_TEMPERATURE_ALARM_ADDR, sizeof(temp_temperature_alarm));
	}

	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&temp_temperature_bound, TEMP_TEMPERATURE_BOUND_ADDR, sizeof(temp_temperature_bound));
	}
	if(ret){
		temp_temperature_bound = 5;
		FLASH_Save_Para_Encode((uint8 *)&temp_temperature_bound, TEMP_TEMPERATURE_BOUND_ADDR, sizeof(temp_temperature_bound));
	}

	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&move_detection_time, MOVE_DETECTION_TIME_ADDR, sizeof(move_detection_time));
	}
	if(ret){
		move_detection_time = 5;
		FLASH_Save_Para_Encode((uint8 *)&move_detection_time, MOVE_DETECTION_TIME_ADDR, sizeof(move_detection_time));
	}

	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&move_sensitivity, MOVE_SENSITIVITY_ADDR, sizeof(move_sensitivity));
	}
	if(ret){
		move_sensitivity = 5;
		FLASH_Save_Para_Encode((uint8 *)&move_sensitivity, MOVE_SENSITIVITY_ADDR, sizeof(move_sensitivity));
	}


	//******************************************************
	if(set_default_flag == 1){
		ret = 1;
	}else{
		ret = FLASH_Get_Para_Decode((uint8 *)&Rf_channel_num, RF_CHANNEL_NUM_ADDR, sizeof(Rf_channel_num));
		if(Rf_channel_num > 9){
			Rf_channel_num = 0;
			FLASH_Save_Para_Encode((uint8 *)&Rf_channel_num, RF_CHANNEL_NUM_ADDR, sizeof(Rf_channel_num));
		}
	}
	
	if(ret){
		Rf_channel_num = 0;
		FLASH_Save_Para_Encode((uint8 *)&Rf_channel_num, RF_CHANNEL_NUM_ADDR, sizeof(Rf_channel_num));
	}
}


