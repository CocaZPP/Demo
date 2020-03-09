/* Includes ------------------------------------------------------------------*/
#include "Data.h"
#include "Flash_Map.h"
#include "main.h"
#include <string.h>


//**********************************
u8 gCC2500RxBuf[32];
u8 gCC2500TxBuf[32];
__IO uint8_t led_need_blink = 0;//������־
__IO uint8_t key_value;
__IO uint8_t set_state;//����״̬���Ƿ��ֶ�������ʾ
__IO uint8_t TMP112_Alarm = 0;//�����¶ȱ�����־λ 1��Ч
__IO uint8_t OPT3001_Alarm = 0;//��ǿ������־λ 1��Ч


uint8 menu_flag;

float Vref;
uint8 SI24_Receive_Enable=0;//2.4Gģ��ʹ��
int8 temperature = 25;//�¶�
int8 temperature_buff[4];//�¶�
uint8 signal = 31;//�ź�ǿ��
uint8 battery = 100;//��ص���
uint8 battery_voltage = 36;//��ص�ѹ
uint8 water_level = 0;// 1 ��ˮ��0 ��ˮ
uint8 Smoke_Alarm = 0;//0�̸�������1������

uint8 UDP_Buff[1000];
uint32 upload_delay_count;//BC95����ʱ�������
uint32 sample_delay_count;//�¶Ȳ���ʱ��
uint32 detection_delay_count;//���˼��ʱ��
uint32 com_delay_count1;//ͨѶ���ʱ��
uint32 com_delay_count2;//ͨѶ���ʱ��


uint16 alarm_inf_upload_flag = 0;//�Ѿ��ϴ��ı�����Ϣ��־λ  bit0λ�̸б����ϴ� bit1λˮλ�����ϴ�
uint8 com_error;//ͨѶ����

uint8 temp_move_alarm;//�¶Ȼ����ƶ�������־  1 �¶ȱ��� 2 �ƶ�����
uint8 alarm_value;//2.4ͨѶ�ı���ֵ
uint32 alarm_number;//2.4ͨѶ�ı������
uint8 temp_alarm_com_count[20];
uint8 move_alarm_com_count[20];

uint8 Temp_IR_alarm = 0;//��籨��  0û�й�籨��   1��ʼ������2��������
uint8 IR_alarm_Enable=0;//��籨��ʹ��
uint8 IR_alarm;//��籨��  0û�й�籨��   1��ʼ������2��������
uint8 IR_alarm_start;//1��ʼ����  2��������
uint8 IR_alarm_end;//1��ʼ����  2��������
uint8 IR_alarm_time;//
uint8 IR_alarm_flag;

/*******************************************************************************************************/

//EEPROM   START
uint32 number = 100001234;//1+8λΨһ����  1 0000 1234��ʮ���ƣ�
uint8 destinationIP[4] = {118,24,84,211};//101,132,127,130  //{118,24,84,211}
uint16 destinationPort = 1012;//1012  4567

uint32 upload_interval = 6;//0-9999 min  ��ʮ����Ϊһ����λ
uint8 upload_start=1;//0ֹͣ�ϴ�  1�����ϴ�
uint32 sample_interval = 60;//�������ʱ��0-9999 min
uint8 water_level_enable = 0;//ˮλ��⹦��ʹ��
uint32 fibre_optical_interval = 60;//���˼��ʱ��0-9999 min
uint8 fibre_optical_enable = 0;//���˼�⹦��ʹ��
const uint8 mode_number_lenth = 20;
uint8 now_temp_number_lenth = 20;
uint8 now_move_number_lenth = 20;
uint8 now_water_number_lenth = 20;
uint8 now_smoke_number_lenth = 20;
uint32 temp_number[20];//�¶ȼ��    2+8λΨһ����  2 0000 1234��ʮ���ƣ�
uint32 move_number[20];//�ƶ����    3+8λΨһ����  3 0000 1234��ʮ���ƣ�
uint32 water_number[20];//ˮλ���    4+8λΨһ����  4 0000 1234��ʮ���ƣ�
uint32 smoke_number[20];//�̸м��    5+8λΨһ����  5 0000 1234��ʮ���ƣ�
uint8 online_number[20];//���߱��	bit0��ʾ�¶�   bit1��ʾ�ƶ�     0�����ߣ�1����

uint8 temperature_alarm_value = 60;//�¶�����ֵ�������򱨾�
uint8 temperature_alarm_bound = 5;//�¶�����ֵ�������򱨾�

uint8 temp_com_value[20][6];//�����¶�5�������һ����ѹֵ

//����ģ�鱨������
uint8 temp_sample_time = 15;//����ʱ��
uint8 temp_upload_time = 60;//�ϴ�ʱ��
uint8 temp_temperature_alarm = 50;//�����¶�
uint8 temp_temperature_bound = 3;//�¶�����ֵ�������򱨾�

//����ģ���������
uint8 Module_upload_time  = 120;//ģ���ϴ�ʱ��
//�ƶ�����ģ�����
uint8 move_detection_time = 5;//���ʱ��
uint8 move_sensitivity = 5;//������(����)


uint8 Test_NB_flag = 0;

uint8 Rf_channel_num = 1;//RFͨѶ�ŵ� 
uint8 Set_Rf_channel_flag = 0;// ����ͨѶͨ����־  0 ͨѶģʽ   1 �ŵ�����ģʽ

//EEPROM   END
/*******************************************************************************************************/
//�¶ȹ���ģ��
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

//ģ�鱨����Ϣ
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

//�豸״̬
void Com_Send_State(void)
{
	uint16 i;
	uint8 check = 0;
	
	uint8 temp_num = 0;//���ߵ��¶�ģ������
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
	UDP_Buff[8] = (uint8)(temperature_buff[0]);//�¶�
	UDP_Buff[9] = (uint8)(temperature_buff[1]);//�¶�
	UDP_Buff[10] = (uint8)(temperature_buff[2]);//�¶�
	UDP_Buff[11] = (uint8)(temperature_buff[3]);//�¶�
	UDP_Buff[12] = (Smoke_Alarm<<7)|(water_level<<0);//�̸б�����ˮλ����
	UDP_Buff[13] = battery_voltage;//��ص���
	UDP_Buff[14] = (uint8)(upload_interval&0xff);//ʱ����
	UDP_Buff[15] = signal;//�ź�ǿ��
	UDP_Buff[16] = temp_num;//now_temp_number_lenth;//�¶ȱ���ģ�����
	
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
		UDP_Buff[16+i*10+10] = temp_com_value[value][5];//��ѹ
	}
	
	for(i=0;i<17+temp_num*10;i++){
		check += UDP_Buff[i];
	}
	
	UDP_Buff[i++] = check;//check
	UDP_Buff[i++] = COM_STOP;//data2
	
}



//2.4GͨѶ��Ӧ�¶ȼ�����
void Com_Respond_Temp(void)
{
    uint8 i;
    uint8 check = 0;
    gCC2500TxBuf[0] = COM_START;
    gCC2500TxBuf[1] = DEVICE_TYPE_TEMP;
    gCC2500TxBuf[2] = gCC2500RxBuf[2];//������
    gCC2500TxBuf[3] = 10;//data lenth
    gCC2500TxBuf[4] = gCC2500RxBuf[4];//num
    gCC2500TxBuf[5] = gCC2500RxBuf[5];//num
    gCC2500TxBuf[6] = gCC2500RxBuf[6];//num
    gCC2500TxBuf[7] = gCC2500RxBuf[7];//num
    gCC2500TxBuf[8] = temp_sample_time;//����ʱ��(min)
    gCC2500TxBuf[9] = temp_upload_time;//�ϴ�ʱ��(min)
    gCC2500TxBuf[10] = temp_temperature_alarm;//�����¶�
    gCC2500TxBuf[11] = temp_temperature_bound;//�����¶ȴ���
    gCC2500TxBuf[12] = 0;//IR_alarm
    gCC2500TxBuf[13] = 0;//NC
    for(i=0;i<14;i++){
        check += gCC2500TxBuf[i];
    }
    gCC2500TxBuf[14] = check;//check
    gCC2500TxBuf[15] = COM_STOP;//data2
    
}


//2.4GͨѶ��Ӧ�ƶ�������
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
    	gCC2500TxBuf[8] = 0x80;//Ӧ��
    }else{
    	gCC2500TxBuf[8] = 0xee;//Ӧ��
    }
    gCC2500TxBuf[9] = move_detection_time;//���ʱ��
    gCC2500TxBuf[10] = move_sensitivity;//������(����)
    gCC2500TxBuf[11] = 0;//NC
    gCC2500TxBuf[12] = 0;//NC
    gCC2500TxBuf[13] = 0;//NC
    for(i=0;i<14;i++){
        check += gCC2500TxBuf[i];
    }
    gCC2500TxBuf[14] = check;//check
    gCC2500TxBuf[15] = COM_STOP;//data2
}
//2.4GͨѶ��Ӧˮλ������
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
    gCC2500TxBuf[8] = Module_upload_time;//�ϴ�ʱ����
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
//2.4GͨѶ��Ӧ�̸м�����
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
    gCC2500TxBuf[8] = Module_upload_time;//�ϴ�ʱ����
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


//2.4GͨѶ��Ӧ�ƶ�������
void Com_ForLink_Temp(uint8 ch)
{
    uint8 i;
    uint8 check = 0;
	
    gCC2500TxBuf[0] = COM_START;
    gCC2500TxBuf[1] = DEVICE_TYPE_TEMP;
    gCC2500TxBuf[2] = gCC2500RxBuf[2];//������
    gCC2500TxBuf[3] = 10;//data lenth
    gCC2500TxBuf[4] = gCC2500RxBuf[4];//num
    gCC2500TxBuf[5] = gCC2500RxBuf[5];//num
    gCC2500TxBuf[6] = gCC2500RxBuf[6];//num
    gCC2500TxBuf[7] = gCC2500RxBuf[7];//num
    gCC2500TxBuf[8] = temp_sample_time;//����ʱ��(min)
    gCC2500TxBuf[9] = temp_upload_time;//�ϴ�ʱ��(min)
    gCC2500TxBuf[10] = temp_temperature_alarm;//�����¶�
    gCC2500TxBuf[11] = temp_temperature_bound;//�����¶ȴ���
    gCC2500TxBuf[12] = 0xaa;//NC
    gCC2500TxBuf[13] = ch;//NC
    for(i=0;i<14;i++){
        check += gCC2500TxBuf[i];
    }
    gCC2500TxBuf[14] = check;//check
    gCC2500TxBuf[15] = COM_STOP;//data2
}

//2.4GͨѶ��Ӧ�ƶ�������
void Com_ForLink_Move(uint8 ch)
{
    uint8 i;
    uint8 check = 0;
	
    gCC2500TxBuf[0] = COM_START;
    gCC2500TxBuf[1] = DEVICE_TYPE_TEMP;
    gCC2500TxBuf[2] = gCC2500RxBuf[2];//������
    gCC2500TxBuf[3] = 10;//data lenth
    gCC2500TxBuf[4] = gCC2500RxBuf[4];//num
    gCC2500TxBuf[5] = gCC2500RxBuf[5];//num
    gCC2500TxBuf[6] = gCC2500RxBuf[6];//num
    gCC2500TxBuf[7] = gCC2500RxBuf[7];//num
    gCC2500TxBuf[8] = 0;//����ʱ��(min)
    gCC2500TxBuf[9] = move_detection_time;//�ϴ�ʱ��(min)
    gCC2500TxBuf[10] = move_sensitivity;//�����¶�
    gCC2500TxBuf[11] = 0;//�����¶ȴ���
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
	uint8 send_flag = 0;// 1�ظ��¶�2�ظ�λ��3�ظ�ˮλ4�ظ��̸�
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
                 
							//��Ӧָ��
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
									//��ǰ̨���������ƶ�����ģ��Ĵ�����װָ�ֻ���ں�̨�˵������½��մ���
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
						//���ﲻ��ֱ���˳����˳���ִ��2.4G�͹���ģʽ���ᵼ�½��ղ�����
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

//��ʼ������
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


