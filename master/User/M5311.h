#ifndef __M5311_H__
#define __M5311_H__

#include "stm32l1xx.h"
#include "Usart.h"
#include "typedef.h"
#include <string.h>
#include <stdio.h>
#include "Drive.h"

/*M5311�����Ϣ*/
typedef enum{
	Active_mode = 0,
	PSM_mode
}M5311Status;

typedef enum{
	E_OK = 0,//����
	E_NOCARD,//�޿�
	E_CEREG,//ע��ʧ��
	E_CGACT,//����ʧ��
	E_UDP_TCP,//��������ʧ��
	E_SENDDATA,//��������ʧ��
	E_RECEIVE//���շ�������ʧ��
}M5311Error;

typedef  struct{
	uint8 cardOk;//�Ƿ��п�
	uint8 linkNet;//�Ƿ���
	int rssi;//�ź�ǿ��
	int rxlevel;//�ź�����
	uint8 imsi[30];//�ֻ�����
	uint16 connect_time;//����ʱ�䵥λs
	uint16 communica_time;//��������-��������ʱ�䵥λs
	M5311Error error;
}M5311_INF;

typedef  struct{
	uint8 test_Mode;//����ģʽ
	uint8 connectErro_cnt;//����ʧ�ܼƴ�
	uint8 communica_cnt;//NBͨѶʱ��ƴ�
	uint8 communica_flag;//����NBͨѶ��־
	uint16 test_cnt;//���ò��Դ���
	uint8 cach;//��������
	uint16 test_ok;//���Գɹ�����
	uint16 test_error;//����ʧ�ܴ���
	uint16 linkTime[100];//����ʱ��
	uint16 CommTime[100];//ͨѶʱ��
}Test_M5311;

#define LOCAL_UDP_SOCKIT_ID     1

void Set_M5311_Power(void);
void Clr_M5311_Power(void);
void M5311_RST_Init(void);
void Ctr_M5311_RST(void);
void M5311_Wake(void);
void Ctr_M5311_Wake(void);
void M5311_PMS_Init(void);
void M5311_Wake_UP(void);


uint8_t* M5311_check_ack(char *str);
uint8_t M5311_send_cmd(char *cmd,char *ack,uint16_t waittime);
uint8 M5311_Check_Reback(char *ack,uint16_t waittime);
void M5311_power_on(void);
uint8_t query_net_status(void);
uint8 Get_M5311_signal(void);
uint8_t M5311_Inquire_port(uint8 socket_id,uint16_t waittime);
void get_str_data(char* des,char pos,char len);
uint8_t creat_UDP_socket(uint8 sockt_id,char *hostIP,char *port);
uint8_t send_UDP_msg(uint8 socket,uint16 dataLen,char *data,char *hostIP,char *port);

void HexToStr(char *pbDest, char *pbSrc, int nLen);
void HexToInt(char *pbDest, char *pbSrc, int nLen);
void ByteToHexStr( unsigned char* source, char* dest, int sourceLen);
uint8_t M5311_LOCK_Sleep(void);
uint8_t M5311_UNLOCK_Sleep(void);

ErrorStatus Get_M5311Inf(void);
ErrorStatus M5311_InitPowerOn(void);
ErrorStatus M5311_InitNetWork(void);


#endif

