#ifndef __M5311_H__
#define __M5311_H__

#include "stm32l1xx.h"
#include "Usart.h"
#include "typedef.h"
#include <string.h>
#include <stdio.h>
#include "Drive.h"

/*M5311相关信息*/
typedef enum{
	Active_mode = 0,
	PSM_mode
}M5311Status;

typedef enum{
	E_OK = 0,//正常
	E_NOCARD,//无卡
	E_CEREG,//注册失败
	E_CGACT,//附网失败
	E_UDP_TCP,//网络连接失败
	E_SENDDATA,//发送数据失败
	E_RECEIVE//接收反馈数据失败
}M5311Error;

typedef  struct{
	uint8 cardOk;//是否有卡
	uint8 linkNet;//是否附网
	int rssi;//信号强度
	int rxlevel;//信号质量
	uint8 imsi[30];//手机卡号
	uint16 connect_time;//附网时间单位s
	uint16 communica_time;//发送数据-接收数据时间单位s
	M5311Error error;
}M5311_INF;

typedef  struct{
	uint8 test_Mode;//测试模式
	uint8 connectErro_cnt;//附网失败计次
	uint8 communica_cnt;//NB通讯时间计次
	uint8 communica_flag;//启动NB通讯标志
	uint16 test_cnt;//设置测试次数
	uint8 cach;//缓存数据
	uint16 test_ok;//测试成功次数
	uint16 test_error;//测试失败次数
	uint16 linkTime[100];//附网时间
	uint16 CommTime[100];//通讯时间
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

