#ifndef _DATA_H_
#define _DATA_H_

#include "stm32l1xx.h"
#include "typedef.h"

#define VSRSION "SW1.0 HW6.1"
#define ALARM_TYPE_SHAKE	1//0�ƶ�����ʹ�ô��𶯺�С��ͬһ������    1���𶯺�С�𶯲�ͬ���ͱ���





extern u8 gCC2500RxBuf[32];
extern u8 gCC2500TxBuf[32];

extern float Vref;
extern uint8 SI24_Receive_Enable;//2.4Gģ��ʹ��
extern uint8 temp_move_alarm;//�¶Ȼ����ƶ�������־
extern uint8 alarm_value;
extern uint32 alarm_number;
extern uint8 temp_sample_time;//����ʱ��
extern uint8 temp_upload_time;//�ϴ�ʱ��
extern uint8 temp_temperature_alarm;//�����¶�
extern uint8 temp_temperature_bound;//�¶�����ֵ�������򱨾�

extern uint32 number;//���
extern int8 temperature;//�¶�
extern int8 temperature_buff[4];//�¶�
extern uint8 signal;//�ź�ǿ��
extern uint8 battery;//��ص���
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
extern uint8 water_level_enable;//ˮλ��⹦��ʹ��
extern uint32 fibre_optical_interval;//���˼��ʱ��0-9999 min
extern uint8 fibre_optical_enable;//���˼�⹦��ʹ��
extern const uint8 mode_number_lenth;
extern uint8 now_temp_number_lenth;
extern uint8 now_move_number_lenth;
extern uint8 now_water_number_lenth;
extern uint8 now_smoke_number_lenth;
extern uint32 temp_number[20];
extern uint32 move_number[20];
extern uint32 water_number[20];
extern uint32 smoke_number[20];
extern uint8 online_number[20];//���߱��	bit0��ʾ�¶�   bit1��ʾ�ƶ�     0�����ߣ�1����

extern uint8 temp_alarm_com_count[20];
extern uint8 move_alarm_com_count[20];
extern uint8 Temp_IR_alarm;//��籨��  0û�й�籨��   1��ʼ������2��������

extern uint8 IR_alarm_Enable;
extern uint8 IR_alarm;//��籨��  0û�й�籨��   1��ʼ������2��������
extern uint8 IR_alarm_start;//1��ʼ����  2��������
extern uint8 IR_alarm_end;//1��ʼ����  2��������
extern uint8 IR_alarm_time;//
extern uint8 IR_alarm_flag;

extern uint8 temp_com_value[20][6];//�����¶�

extern uint8 UDP_Buff[];
extern uint32 upload_delay_count;
extern uint32 sample_delay_count;
extern uint32 detection_delay_count;//��������ʱ�������
extern uint32 com_delay_count1;//ͨѶ���ʱ��
extern uint32 com_delay_count2;//ͨѶ���ʱ��

extern uint8 com_error;//ͨѶ����

extern __IO uint8_t set_state;
extern uint8 menu_flag;

extern uint16 alarm_inf_upload_flag;//�Ѿ��ϴ��ı�����Ϣ��־λ  bit0λ���˱����ϴ� bit1λˮλ�����ϴ�
extern uint8 temperature_alarm_value;//�¶�����ֵ�������򱨾�
extern uint8 temperature_alarm_bound;//�¶�����ֵ�������򱨾�
extern uint8 Module_upload_time;//ģ���ϴ�ʱ��
extern uint8 move_detection_time;//���ʱ��
extern uint8 move_sensitivity;//������(����)

extern uint8 upload_start;

extern uint8 Test_NB_flag;

extern uint8 Rf_channel_num;//RFͨѶ�ŵ� 
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

