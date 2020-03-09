#ifndef _DATA_H_
#define _DATA_H_

#include "stm32l1xx.h"
#include "typedef.h"

#define VSRSION "SW1.0 HW6.1"
#define ALARM_TYPE_SHAKE	1//0移动报警使用大震动和小震动同一个类型    1打震动和小震动不同类型报警





extern u8 gCC2500RxBuf[32];
extern u8 gCC2500TxBuf[32];

extern float Vref;
extern uint8 SI24_Receive_Enable;//2.4G模块使能
extern uint8 temp_move_alarm;//温度或者移动报警标志
extern uint8 alarm_value;
extern uint32 alarm_number;
extern uint8 temp_sample_time;//采样时间
extern uint8 temp_upload_time;//上传时间
extern uint8 temp_temperature_alarm;//报警温度
extern uint8 temp_temperature_bound;//温度上限值，超过则报警

extern uint32 number;//编号
extern int8 temperature;//温度
extern int8 temperature_buff[4];//温度
extern uint8 signal;//信号强度
extern uint8 battery;//电池电量
extern uint8 battery_voltage;
extern uint8 Smoke_Alarm;
extern uint8 water_level;

extern __IO uint8_t led_need_blink;
extern __IO uint8_t key_value;
extern __IO uint8_t TMP112_Alarm;
extern __IO uint8_t OPT3001_Alarm;

extern uint8 destinationIP[4];//101.132.127.130
extern uint16 destinationPort;//1012  4567
extern uint32 upload_interval;
extern uint32 sample_interval;//0-999 s
extern uint8 water_level_enable;//水位检测功能使能
extern uint32 fibre_optical_interval;//光纤检测时间0-9999 min
extern uint8 fibre_optical_enable;//光纤检测功能使能
extern const uint8 mode_number_lenth;
extern uint8 now_temp_number_lenth;
extern uint8 now_move_number_lenth;
extern uint8 now_water_number_lenth;
extern uint8 now_smoke_number_lenth;
extern uint32 temp_number[20];
extern uint32 move_number[20];
extern uint32 water_number[20];
extern uint32 smoke_number[20];
extern uint8 online_number[20];//在线编号	bit0表示温度   bit1表示移动     0不在线，1在线

extern uint8 temp_alarm_com_count[20];
extern uint8 move_alarm_com_count[20];
extern uint8 Temp_IR_alarm;//光电报警  0没有光电报警   1开始报警，2报警结束

extern uint8 IR_alarm_Enable;
extern uint8 IR_alarm;//光电报警  0没有光电报警   1开始报警，2报警结束
extern uint8 IR_alarm_start;//1开始报警  2结束报警
extern uint8 IR_alarm_end;//1开始报警  2结束报警
extern uint8 IR_alarm_time;//
extern uint8 IR_alarm_flag;

extern uint8 temp_com_value[20][6];//报警温度

extern uint8 UDP_Buff[];
extern uint32 upload_delay_count;
extern uint32 sample_delay_count;
extern uint32 detection_delay_count;//采样启动时间计数器
extern uint32 com_delay_count1;//通讯检测时间
extern uint32 com_delay_count2;//通讯检测时间

extern uint8 com_error;//通讯错误

extern __IO uint8_t set_state;
extern uint8 menu_flag;

extern uint16 alarm_inf_upload_flag;//已经上传的报警信息标志位  bit0位光纤报警上传 bit1位水位报警上传
extern uint8 temperature_alarm_value;//温度上限值，超过则报警
extern uint8 temperature_alarm_bound;//温度上限值，超过则报警
extern uint8 Module_upload_time;//模块上传时间
extern uint8 move_detection_time;//检测时间
extern uint8 move_sensitivity;//灵敏度(次数)

extern uint8 upload_start;

extern uint8 Test_NB_flag;

extern uint8 Rf_channel_num;//RF通讯信道 
extern uint8 Set_Rf_channel_flag;

extern uint16 Tmp112Config_Reg;
extern uint16 Tmp112_LimUp;
extern uint16 Tmp112_LimDown;
extern uint16 TempValue;

extern uint16 OPT3001_M_ID;
extern uint16 OPT3001_D_ID;
extern uint16 OPT3001Config_Reg;
extern uint16 OPT3001_LimUp;
extern uint16 OPT3001_LimDown;
extern uint32 LightValue;

void Com_Send_Alarm(uint8 alarm_type);

void Com_Send_State(void);
void Com_Respond_Move(void);
void Com_Respond_Temp(void);
uint8 Read_Si24r1_Data(uint8 ch , uint32 id_temp);
void Com_ForLink_Temp(uint8 ch);
void Com_ForLink_Move(uint8 ch);


void Variable_Flash(uint8 default_value_flat);


#endif

