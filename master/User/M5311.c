#include "M5311.h"
#include "rtl.h"
#include "main.h"

extern __IO uint8_t set_state;//启动状态，是否手动启动显示
extern __IO uint8_t led_need_blink;//附网标志

M5311_INF m5311Inf;//模块信息
Test_M5311 testM5311;//测试M5311
/*********************************************************************************/
//M5311 硬件控制相关

//******************************************
//M5311 上电开机
//将 PWR_ON/OFF 置为低电平，保持 2s 以上即可开机，开机之后需要置高电平。
void Set_M5311_Power(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = M5311_POWER_EN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(M5311_POWER_EN_GPIO, &GPIO_InitStructure);
	
	GPIO_SetBits(M5311_POWER_EN_GPIO,M5311_POWER_EN_PIN);
	os_dly_wait(3000);
	GPIO_ResetBits(M5311_POWER_EN_GPIO,M5311_POWER_EN_PIN);

	//Clr_M5311_Power();
}


//******************************************
//M5311 上电开机
//将 PWR_ON/OFF 置为低电平，保持 12s 实现关机操作，并且延时 20s后，进行其它操作。
void Set_M5311_PowerOff(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = M5311_POWER_EN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(M5311_POWER_EN_GPIO, &GPIO_InitStructure);
	
	GPIO_SetBits(M5311_POWER_EN_GPIO,M5311_POWER_EN_PIN);
	os_dly_wait(12000);
	GPIO_ResetBits(M5311_POWER_EN_GPIO,M5311_POWER_EN_PIN);

	os_dly_wait(20000);
}

//******************************************
//M5311 PWR_ON/OFF 置为输出，进入休眠时调用
void Clr_M5311_Power(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = M5311_POWER_EN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(M5311_POWER_EN_GPIO, &GPIO_InitStructure);
}

//******************************************
//M5311 复位置为输出，进入休眠时调用
void M5311_RST_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = M5311_RST_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(M5311_RST_GPIO, &GPIO_InitStructure);

	GPIO_ResetBits(M5311_RST_GPIO,M5311_RST_PIN);
}

//******************************************
//M5311 复位置为输出，进入休眠时调用
void Ctr_M5311_RST(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = M5311_RST_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(M5311_RST_GPIO, &GPIO_InitStructure);
}

//M5311 复位 RST拉低200ms
//请在模块无反应的情况下使用
void ResetM5311(void)
{
	M5311_RST_Init();
	GPIO_SetBits(M5311_RST_GPIO,M5311_RST_PIN);
	os_dly_wait(200);
	GPIO_ResetBits(M5311_RST_GPIO,M5311_RST_PIN);
	Ctr_M5311_RST();
}

//******************************************
//M5311 PMS模式状态
void M5311_PMS_PIN_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = M5311_PMSIN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(M5311_PMSIN_GPIO, &GPIO_InitStructure);
}
void Ctr_M5311_PMS_PIN(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = M5311_PMSIN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(M5311_WAKE_GPIO, &GPIO_InitStructure);
}

//******************************************
//M5311 获取工作： Active_mode PSM_mode
M5311Status Get_M5311_Status()
{
	M5311_PMS_PIN_Init();
	if(GPIO_ReadInputDataBit(M5311_PMSIN_GPIO,M5311_PMSIN_PIN) == 1){
		Ctr_M5311_PMS_PIN();
		return PSM_mode;
	}else{
		Ctr_M5311_PMS_PIN();
		return Active_mode;
	}
}

//******************************************
//M5311 WAKE_PIN 输出模式 OD NOPULL
void Set_M5311_WakeIn_Gpio(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = M5311_WAKE_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(M5311_WAKE_GPIO, &GPIO_InitStructure);
}

//******************************************
//M5311 WAKE_PIN 复位置为输出，进入休眠时调用
void Ctr_M5311_WakeIn_Gpio(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = M5311_WAKE_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(M5311_WAKE_GPIO, &GPIO_InitStructure);
}

//******************************************
//M5311 将模块有PSM模式唤醒
void M5311_WakeUp_FromPSM(void)
{
	if(Get_M5311_Status() == PSM_mode){
		Set_M5311_WakeIn_Gpio();
		GPIO_SetBits(M5311_WAKE_GPIO,M5311_WAKE_PIN);
		delay_ms(100);
		GPIO_ResetBits(M5311_WAKE_GPIO,M5311_WAKE_PIN);
		Ctr_M5311_WakeIn_Gpio();
	}
}



//********************************************************
 //关闭睡眠
uint8_t M5311_LOCK_Sleep(void)
{
	uint8_t res = 0;
	if(M5311_send_cmd("AT+SM=LOCK","OK",100))
	{
		res = 1;
	}
	return res;
}

//********************************************************
//打开睡眠
uint8_t M5311_UNLOCK_Sleep(void)
{
	uint8_t res = 0;
	if(M5311_send_cmd("AT+SM=UNLOCK","OK",100))
	{
		res = 1;
	}
	return res;
}


//********************************************************
uint8_t check_ack_timeout = 10;
uint8_t ue_exist_flag = 0;
uint8_t ue_need_reboot_flag = 0;
//检查返回的响应是否符合预期
//传入参数为预期返回的字符串
//返回NULL，返回值中没有预期字符串
//其他值，预期字符所在的位置
uint8_t* M5311_check_ack(char *str)
{
    char *strx = NULL;
    if(usart2_rcvd_flag)		
    { 
        usart2_rcvd_buf[usart2_rcvd_len]='\0';
        strx = strstr((const char*)usart2_rcvd_buf, (const char*)str);
    } 
    return (uint8_t*)strx;
}

//发生at指令函数
//cmd:at指令，ack：预期响应，waittime,超时时间
//返回0，发送成功
//返回1，发送超时
uint8_t M5311_send_cmd(char *cmd,char *ack,uint16_t waittime)
{
	char buff[500]={0};
	uint8_t res=0; 
	usart2_rcvd_flag=0;
	usart2_rcvd_len = 0;
	memset(usart2_rcvd_buf,0,USART2_RX_BUF_LEN);
	sprintf(buff , "%s\r\n",cmd);
	usart_send_str(USART2,buff);
	if(ack&&waittime)
	{
		while(--waittime)	
		{
			IWDG_ReloadCounter();
			os_dly_wait(20);
			if(usart2_rcvd_flag)
			{
			    
				if(M5311_check_ack(ack) )
				{
					break;
				}
				usart2_rcvd_flag=0;
			}
			if(set_state == 1)
			{
			}
		}
		if(waittime==0)
		{
			res=1;
		} 
	}
	return res;
}

//检测返回包是否为预期值 返回值：0 正确 1 错误
uint8 M5311_Check_Reback(char *ack,uint16_t waittime)
{
	uint8_t res=0; 
	
	if(ack&&waittime)
	{
		while(--waittime)	
		{
			os_dly_wait(20);
			IWDG_ReloadCounter();
			if(usart2_rcvd_flag)
			{
			    
				if(M5311_check_ack(ack))
				{
					break;
				}
			    	usart2_rcvd_flag=0;
			}
			if(set_state == 1)
			{
				
			}
		}
		if(waittime==0)
		{
			res=1;
		}
	}
   	return res;
}


void HexToStr(char *pbDest, char *pbSrc, int nLen)
{
    char ddl,ddh;
    int i;
    for (i=0; i<nLen; i++)
    {
        ddh = 0x30 + pbSrc[i] / 16;
        ddl = 0x30 + pbSrc[i] % 16;
        if (ddh > 0x39) ddh = ddh + 7;
        if (ddl > 0x39) ddl = ddl + 7;
        pbDest[i*2] = ddh;
        pbDest[i*2+1] = ddl;
    }
    pbDest[nLen*2] = '\0';
}

void HexToInt(char *pbDest, char *pbSrc, int nLen)
{
    char ddl,ddh;
    int i;
    for (i=0; i<nLen; i++)
    {
    	if(pbSrc[i*2]>='0' && pbSrc[i*2]<='9'){
			ddh = (pbSrc[i*2]-'0')*16;
		}else if(pbSrc[i*2]>='A' && pbSrc[i*2]<='F'){
			ddh = (pbSrc[i*2]-'A'+10)*16;
		}else if(pbSrc[i*2]>='a' && pbSrc[i*2]<='f'){
			ddh = (pbSrc[i*2]-'a'+10)*16;
		}
		if(pbSrc[i*2+1]>='0' && pbSrc[i*2+1]<='9'){
			ddl = pbSrc[i*2+1]-'0';
		}else if(pbSrc[i*2+1]>='A' && pbSrc[i*2+1]<='F'){
			ddl = pbSrc[i*2+1]-'A'+10;
		}else if(pbSrc[i*2+1]>='a' && pbSrc[i*2+1]<='f'){
			ddl = pbSrc[i*2+1]-'a'+10;
		}
        pbDest[i] = ddh+ddl;
    }
    pbDest[nLen] = '\0';
}

void ByteToHexStr( unsigned char* source, char* dest, int sourceLen)  
{  
    short i;  
    unsigned char highByte, lowByte;  
    
    for (i = 0; i < sourceLen; i++)  
    {  
        highByte = source[i] >> 4;  
        lowByte = source[i] & 0x0f ;  
        
        highByte += 0x30;  
        
        if (highByte > 0x39)  
            dest[i * 2] = highByte + 0x07;  
        else  
            dest[i * 2] = highByte;  
        
        lowByte += 0x30;  
        if (lowByte > 0x39)  
            dest[i * 2 + 1] = lowByte + 0x07;  
        else  
            dest[i * 2 + 1] = lowByte;  
					dest[i * 2 + 2] = 0;
    }  
    return ;  
}

unsigned char HexToChar(unsigned char bHex)
{
	if((bHex>=0)&&(bHex<=9))
	{
		bHex += 0x30;
	}
	else if((bHex>=10)&&(bHex<=15))//Capital
	{
		bHex += 0x37;
	}
	else 
	{
		bHex = 0xff;
	}
	return bHex;
}

//*******************************************
//获取M5311信号量
uint8 Get_M5311_signal(void)
{
	//value:
	/************************************
	AT+ICCID
	
	+CSQ:16,7
	OK
	
	0 -113dBm or less
	1 -111dBm
	2...30 -109dBm... -53dBm
	31 -51dBm or greater
	99 Not known or not detectable
	*************************************/

	char* p =NULL;
	int8 value = 0;
	static uint8 last_value = 99;
	static uint8 error_count = 0;
	M5311_send_cmd("AT+CSQ","OK",200);//AT+CSQ
	p = strstr(usart2_rcvd_buf,"CSQ");
	if(p != NULL)
	{
		if(strlen(p) > 9)
		{
			if((p[12]>='0' && p[12]<='9'))
			{
				if(p[13] == ',')
				{
					value = (p[12]-'0');
					
					if(p[15]>='0' && p[15]<='9'){
						m5311Inf.rxlevel = (p[14]-'0')*10 + (p[15]-'0');
					}else{
						m5311Inf.rxlevel = (p[14]-'0');
					}
					
				}
				else
				{
					value = (p[12]-'0')*10 + (p[13]-'0');
					
					if(p[16]>='0' && p[16]<='9'){
						m5311Inf.rxlevel = (p[15]-'0')*10 + (p[16]-'0');
					}else{
						m5311Inf.rxlevel = (p[15]-'0');
					}
				}
				
				if(value >= 0 && value <= 31)
				{
					last_value = value;
					error_count = 0;
				}
				else
				{
					error_count++;
				}
				
				if(error_count >= 10)
				{
					error_count = 10;
					//last_value = value;
				}
			}

		}
	}
	return value;
}

//*******************************************
//读取通讯卡号码
uint8 Get_M5311_IMSI(uint8* str)
{
	//value:
	/************************************
	AT+CIMI
	460041912306456
	OK
	*************************************/
	char* p =NULL;
	uint8 n = 0;
	uint8 t = 0;

	M5311_send_cmd("AT+CIMI","OK",100);//AT+CIMI
	p = usart2_rcvd_buf;
	if(p != NULL)
	{
		n = 0;
		t = 0;
		while(p[n] != 0){
			if(p[n]>='0' && p[n]<='9'){
				if(t<30){
					str[t] = p[n];
					t++;
				}
				else{
					break;
				}
			}
			n++;
		}
	}
}

//*******************************************
//查询SOCKET_ID 是否已经绑定,如果已绑定，返回socket_id, 没有绑定则返回0
uint8_t M5311_Inquire_port(uint8 socket_id,uint16_t waittime)
{
	char buff[100] = "AT+IPSTATUS=";
	
	uint8 socketid = socket_id;
	usart2_rcvd_flag=0;
	usart2_rcvd_len = 0;
	memset(usart2_rcvd_buf,0,USART2_RX_BUF_LEN);
	sprintf(buff , "AT+IPSTATUS=%d\r\n",socketid);
	usart_send_str(USART2,buff);
	if(waittime)
	{
		while(--waittime)	
		{
			os_dly_wait(20);
			if(usart2_rcvd_flag)
			{
				if(M5311_check_ack("CONNECTED") )
				{
					break;
				}
			    	usart2_rcvd_flag=0;
			}
		}
		if(waittime==0)
		{
			return 0;
		} 
	}
	return socket_id;
}

//*******************************************
//读取数据，截取接收缓存中所需的数据保存到des,pos为起始地址，len为截取长度
void get_str_data(char* des,char pos,char len)
{
    memcpy(des,usart2_rcvd_buf+pos,len);
}

//*******************************************
//创建UDP链接，传入设置的UDP sockit号(0-4)，返回设置的socket id号，失败返回0
uint8 creat_UDP_socket(uint8 sockt_id,char *hostIP,char *port)
{
	char temp[64]={0};
	sprintf(temp, "AT+IPSTART=%d,\"UDP\",\"%s\",%s", sockt_id,hostIP, port);
	if(!M5311_send_cmd(temp,"OK",100))//如果创建UDP套接字成功
	{
		return sockt_id;
	}
    return 0xff;
}

//*******************************************
//关闭UDP链接
ErrorStatus close_socket(uint8 sockt_id)
{
	char temp[64]={0};
	sprintf(temp, "AT+IPCLOSE=%d", sockt_id);
	if(!M5311_send_cmd(temp,"OK",200))//如果创建UDP套接字成功
	{
		return SUCCESS;
	}
    return ERROR;
}


//*******************************************
//创建TCP链接，传入设置的TCP sockit号(0-4)，返回设置的socket id号，失败返回0
uint8 creat_TCP_socket(uint8 sockt_id,char *hostIP,char *port)
{
	char temp[64]={0};
	sprintf(temp, "AT+IPSTART=%d,\"TCP\",\"%s\",%s", sockt_id,hostIP, port);
	if(!M5311_send_cmd(temp,"OK",100))//如果创建UDP套接字成功
	{
		return sockt_id;
	}
    return 0xff;
}

//*******************************************
//发送数据函数，传入sockt_id,数据长度，数据,主机IP，远程主机端口，
//考虑网络不稳定，发送等待10秒钟
//返回值0，发送成功（鉴于UDP为报文传输，数据主机是否接收到模块是无法确认的）
//返回值1，发送失败
ErrorStatus send_UDP_msg(uint8 sockt_id,uint16 dataLen,char *data,char *hostIP,char *port)
{
	char ptr[500] = {0};	    
	//AT+IPSEND=0,0,"1233","118.24.84.211",1012 OR AT+IPSEND=0,0,1233,118.24.84.211,1012 
	sprintf(ptr,"AT+IPSEND=%d,%d,\"%s\",\"%s\",%s",sockt_id,dataLen,data,hostIP,port);
	if(!M5311_send_cmd(ptr,"OK",600))
	{
		return SUCCESS;
	}
	return ERROR;
}

//*******************************************
//发送数据函数，传入sockt_id,数据长度，数据, IPTOS优先级
//这里暂时使用字符串参数
//返回值0，发送成功（鉴于UDP为报文传输，数据主机是否接收到模块是无法确认的）
//返回值1，发送失败
ErrorStatus send_TCP_msg(uint8 sockt_id,uint16 dataLen,char *data,uint8 pri_flag)
{
	char ptr[500] = {0};	    
	//AT+IPSEND=0,0,"1233",1
	sprintf(ptr,"AT+IPSEND=%d,%d,\"%s\",%d",sockt_id,dataLen,data,pri_flag);
	if(!M5311_send_cmd(ptr,"OK",200))
	{
		return SUCCESS;
	}
	return ERROR;
}

//**************************************************
//获取M5311模组信息
ErrorStatus Get_M5311Inf(void)
{
	m5311Inf.cardOk = 0;
	m5311Inf.connect_time = 1;
	m5311Inf.communica_time = 1;
	m5311Inf.error = E_OK;
	memset(m5311Inf.imsi,0,30);
	m5311Inf.rssi = 99;
	m5311Inf.rxlevel = 99;
	m5311Inf.linkNet = 0;

	//初始化GPIO
	Ctr_M5311_WakeIn_Gpio();
	Ctr_M5311_RST();
	Ctr_M5311_PMS_PIN();
	
	Init_USART2();
	Set_BTDE_Power();//启动电平转换电源
	
	//硬件上电
	Set_M5311_Power();
	
	//PSM
	M5311_WakeUp_FromPSM();

	//AT cmd
	check_ack_timeout = 20;//
	while(M5311_send_cmd("AT","OK",100)&&check_ack_timeout)
	{
	    if(check_ack_timeout)
	    {
	        check_ack_timeout--;
	        ue_exist_flag = 0;
	    }
	    os_dly_wait(50);
	}

	if(check_ack_timeout == 0){
		USART2_Close();
		Clr_BTDE_Power();
		return ERROR;
	}
	else{
		M5311_LOCK_Sleep();
		//获取信号质量
		m5311Inf.rssi = Get_M5311_signal();
		//读取手机卡号
		Get_M5311_IMSI(m5311Inf.imsi);
		//检测附网
		M5311_InitNetWork();
		//进入休眠
		M5311_UNLOCK_Sleep();

		USART2_Close();
		Clr_BTDE_Power();
		
		return SUCCESS;
	}
}

//**************************************************
//M5311驻网流程
void M5311_power_on(void)
{
	check_ack_timeout = 20;
	ue_exist_flag = 1;
	while(M5311_send_cmd("AT","OK",100)&&check_ack_timeout)
	{
	    if(check_ack_timeout)
	    {
	        check_ack_timeout--;
	        ue_exist_flag = 0;
	    }
	    os_dly_wait(500);
		if(set_state == 1){

		}
		IWDG_ReloadCounter();
	}

	//获取信号质量
	m5311Inf.rssi = Get_M5311_signal();
	
	M5311_LOCK_Sleep();//关闭睡眠
}

//**************************************************
uint8_t query_net_status(void)
{
	uint8_t res = 0;
	uint8_t attached_flag = 0;
	
	led_need_blink = 1;

	 //附网  
	 check_ack_timeout = 20;//
	while((attached_flag == 0) && check_ack_timeout)
	{
		if(!M5311_send_cmd("AT+CGPADDR=1","+CGPADDR: 1",200))//AT+CEREG?//查询附网状态
		{//附网成功
			res =1;
			break;
		}
		check_ack_timeout--;
		os_dly_wait(500);
		IWDG_ReloadCounter();
	}
	
    return res;
}



//**************************************************
//M5311 初始化网络：注册网络，并附网
ErrorStatus M5311_InitNetWork(void)
{
	uint8 stepNum = 0;
	
	//获取信号质量
	m5311Inf.rssi = Get_M5311_signal();

	//M5311_send_cmd("AT+CSCON=1","OK",100);//AT+CSQ

	//注册网络
	check_ack_timeout = 20;//
	while(check_ack_timeout)
	{
		// 1 已注册，注册到归属网络
		// 5 已注册，注册到漫游网络CEREG: 0,1
		if(M5311_send_cmd("AT+CEREG?","CEREG: 0,1",50)==0 || M5311_send_cmd("AT+CEREG?","CEREG: 0,5",50)==0)//AT+CEREG?//查询附网状态
		{
			//注册网络成功
			stepNum = 1;
			break;
		}
		check_ack_timeout--;
		os_dly_wait(200);
	}

	//附网
	if(stepNum == 1){
		check_ack_timeout = 200;//最长180s
		while(check_ack_timeout)
		{
			check_ack_timeout--;
			if(M5311_send_cmd("AT+CGACT?","CGACT: 1,1",50)==0)//AT+CEREG?//查询附网状态
			{
				//附网成功
				stepNum = 2;
				m5311Inf.connect_time = 200 - check_ack_timeout;
				break;
			}
			os_dly_wait(50);
		}

		if(stepNum == 2){
			m5311Inf.linkNet = 1;
			return SUCCESS;
		}
		else{
			m5311Inf.linkNet = 0;
			m5311Inf.error = E_CGACT;
			testM5311.connectErro_cnt++;
			return ERROR;
		}
	}
	else{
		m5311Inf.linkNet = 0;
		m5311Inf.error = E_CEREG;
		return ERROR;
	}
}


//**************************************************
//M5311 上电开机初始化，模块上电时调用
ErrorStatus M5311_InitPowerOn(void)
{
	m5311Inf.cardOk = 0;
	m5311Inf.connect_time = 0;
	m5311Inf.error = E_OK;
	memset(m5311Inf.imsi,0,30);
	m5311Inf.rssi = 99;
	m5311Inf.rxlevel = 99;
	m5311Inf.linkNet = 0;

	//初始化GPIO
	Ctr_M5311_WakeIn_Gpio();
	Ctr_M5311_RST();
	Ctr_M5311_PMS_PIN();
	
	Init_USART2();
	Set_BTDE_Power();//启动电平转换电源
	
	//硬件上电
	Set_M5311_Power();
	
	//PSM
	M5311_WakeUp_FromPSM();

	//AT cmd
	check_ack_timeout = 20;//
	while(M5311_send_cmd("AT","OK",100)&&check_ack_timeout)
	{
	    if(check_ack_timeout)
	    {
	        check_ack_timeout--;
	        ue_exist_flag = 0;
	    }
	    os_dly_wait(50);
	}

	if(check_ack_timeout == 0){
		USART2_Close();
		Clr_BTDE_Power();
		return ERROR;
	}
	else{
		M5311_LOCK_Sleep();
		//获取信号质量
		m5311Inf.rssi = Get_M5311_signal();
		//读取手机卡号
		Get_M5311_IMSI(m5311Inf.imsi);
		//进入休眠
		M5311_UNLOCK_Sleep();
	
		USART2_Close();
		Clr_BTDE_Power();
		
		return SUCCESS;
	}
}

//**************************************************
//M5311 通讯失败，重启模块初始化
//模块通讯3次失败后调用，将模块关机，然后复位模块，在按上电流程
ErrorStatus M5311_FailurePowerOn(void)
{
	//硬件上电
	//Set_M5311_PowerOff();
	ResetM5311();
	os_dly_wait(500);

	//AT CMD
	check_ack_timeout = 20;//
	while(M5311_send_cmd("AT","OK",100)&&check_ack_timeout)
	{
	    if(check_ack_timeout)
	    {
	        check_ack_timeout--;
	        ue_exist_flag = 0;
	    }
	    os_dly_wait(200);
	}

	if(check_ack_timeout == 0)
		return ERROR;
	else{
		M5311_LOCK_Sleep();//关闭睡眠
		return SUCCESS;
	}
}

//**************************************************
//M5311 将模块由休眠模式唤醒：模块开始通讯时调用
ErrorStatus M5311_WakeUpPowerOn(void)
{
	if(Get_M5311_Status() == PSM_mode){
		Set_M5311_WakeIn_Gpio();
		GPIO_SetBits(M5311_WAKE_GPIO,M5311_WAKE_PIN);
		delay_ms(200);
		GPIO_ResetBits(M5311_WAKE_GPIO,M5311_WAKE_PIN);
		Ctr_M5311_WakeIn_Gpio();
		
		//GPIO_SetBits(M5311_POWER_EN_GPIO,M5311_POWER_EN_PIN);
		//os_dly_wait(200);
		//GPIO_ResetBits(M5311_POWER_EN_GPIO,M5311_POWER_EN_PIN);

		os_dly_wait(150);

		if(Get_M5311_Status() == Active_mode){
			//AT CMD
			check_ack_timeout = 20;//
			while(M5311_send_cmd("AT","OK",100)&&check_ack_timeout)
			{
			    if(check_ack_timeout)
			    {
			        check_ack_timeout--;
			        ue_exist_flag = 0;
			    }
			    os_dly_wait(200);
			}

			if(check_ack_timeout == 0)
				return ERROR;
			else{
				M5311_LOCK_Sleep();//关闭睡眠
				return SUCCESS;
			}
		}
	}
	else{
		return ERROR;
	}
}


//**************************************************
//M5311 模块PowerOn，根据不同状态自动选择模式
ErrorStatus M5311_PowerOn(void)
{
	ErrorStatus status;

	if(Get_M5311_Status() == PSM_mode){
		status = M5311_WakeUpPowerOn();
		return status;
	}
	else{
		check_ack_timeout = 20;//
		while(M5311_send_cmd("AT","OK",50)&&check_ack_timeout)
		{
		    if(check_ack_timeout)
		    {
		        check_ack_timeout--;
		        ue_exist_flag = 0;
		    }
		    os_dly_wait(50);
		}

		if(check_ack_timeout == 0)
			return ERROR;
		else{
			M5311_LOCK_Sleep();//关闭睡眠
			return SUCCESS;
		}
	}
}

#if 1

//UDP发送监测数据至服务器
ErrorStatus  M5311_UDPSend_InfData(void)
{
	uint8 i;
	char buff[40]={0};
	char port_buff[10];
	char data_buff[500];
	uint16 UDP_lenth = 0;
	char *p_value = NULL;
	uint16 check_ack_timeout = 0;
	ErrorStatus sendRet;
	uint8 *receive_flag=NULL;
	if(testM5311.test_Mode != 0){
		//测试UDP数据收发时间
		testM5311.communica_flag = 1;
		TIM3_Int_Init(9999,3199,ENABLE);
	}
	sprintf(buff, "%d.%d.%d.%d",destinationIP[0],destinationIP[1],destinationIP[2],destinationIP[3]);
	sprintf(port_buff, "%d",destinationPort);
	
	creat_UDP_socket(LOCAL_UDP_SOCKIT_ID,buff,port_buff);
	//配置接收模式：自动输出 hex 类型，格式：+IPRD:<socket_id>,<remote_addr>,<remote_port>,<data_len>,<data>
	M5311_send_cmd("AT+IPRCFG=1,2,1","OK",100);
	
	Com_Send_State();
	ByteToHexStr(UDP_Buff ,data_buff, UDP_Buff[3]+6);
	UDP_lenth = UDP_Buff[3] + 6;

	sendRet = send_UDP_msg(LOCAL_UDP_SOCKIT_ID,UDP_lenth,data_buff,buff,port_buff);
	if(sendRet == ERROR)
	{
		for(i = 0;i<10;i++){
			sendRet = send_UDP_msg(LOCAL_UDP_SOCKIT_ID,UDP_lenth,data_buff,buff,port_buff);
			os_dly_wait(1000);
			if(sendRet == SUCCESS){
				break;
			}
		}
	}

	if(sendRet == SUCCESS){
		usart2_rcvd_flag=0;
		usart2_rcvd_len = 0;
		memset(usart2_rcvd_buf,0,USART2_RX_BUF_LEN);
		
		check_ack_timeout = 0;
		//等待30S接收数据
		while((receive_flag == NULL) && (check_ack_timeout<1500))
		{		
			receive_flag = M5311_check_ack("+IPRD:");
			check_ack_timeout++;
			os_dly_wait(20);
		}
		
		//接收到数据再延时等待全部接收完毕
		if(receive_flag != NULL){
			os_dly_wait(1000);
		}
		sprintf(buff ,",22,AAD02011%08X", number);
		p_value = strstr(usart2_rcvd_buf , buff);
		if(p_value != NULL){
			HexToInt(data_buff,p_value+4,22);
			if(data_buff[9] == 1){
				upload_interval = data_buff[10];
				sample_interval = data_buff[11];
				temperature_alarm_value = data_buff[12];
				temperature_alarm_bound = data_buff[13];
				temp_upload_time = data_buff[14];					
				temp_sample_time= data_buff[15];
				temp_temperature_alarm = data_buff[16];
				temp_temperature_bound = data_buff[17];
				move_detection_time = data_buff[18];
				move_sensitivity = data_buff[19];    
				
				/*******利用移动模块设置灵敏度改变光电报警开关*************/
				if(move_sensitivity==0)
				{
						IR_alarm_Enable=0;//0没有光电报警 
				}else if(move_sensitivity==1)
				{
				    IR_alarm_Enable=1;//1开始报警
				}
				/*********************************************************/      	
				
				if(temperature_alarm_bound == 0)
					temperature_alarm_bound = 1;							
			}
			Test_NB_flag = 1;
			memset(usart2_rcvd_buf,0,USART2_RX_BUF_LEN);
			return SUCCESS;
		}
		memset(usart2_rcvd_buf,0,USART2_RX_BUF_LEN);
	}

	return ERROR;
}




//系统信息上传：采样温度值
void M5311_Send_Inf(void)
{
	uint8 i=0;
	uint8 j=0;
	uint8 succeed = 1;
	uint8 count = 0;
	ErrorStatus status;
	
	//初始化GPIO
	Ctr_M5311_WakeIn_Gpio();
	Ctr_M5311_RST();
	Ctr_M5311_PMS_PIN();
	
	Init_USART2();
	Set_BTDE_Power();//启动电平转换电源
	
	//硬件上电
	//Set_M5311_Power();
	
	//PSM
	//M5311_WakeUp_FromPSM();

	//根据模块状态选择启动模式
	status = M5311_PowerOn();
	if(status == ERROR){
		//正常启动失败，模块没有反映，重启模块
		M5311_FailurePowerOn();
	}

	//注册网络，附网
	status = M5311_InitNetWork();
	if(status == SUCCESS)
		succeed = 1;
	else
		succeed = 0;
	
	while(succeed){
		signal = m5311Inf.rssi;
		status = M5311_UDPSend_InfData();
		if(status == SUCCESS){
			succeed = 0;
			close_socket(LOCAL_UDP_SOCKIT_ID);
			if(testM5311.test_Mode != 0){
				testM5311.test_ok++;
			}
			break;
		}
		else{
			//根据模块状态选择启动模式
			status = M5311_PowerOn();
			if(status == ERROR){
				//正常启动失败，模块没有反映，重启模块
				M5311_FailurePowerOn();
			}
			//注册网络，附网
			status = M5311_InitNetWork();
			if(testM5311.test_Mode != 0){
				testM5311.test_error++;
			}
		}

		count++;
		if(count >= 5){
			succeed = 0;
		}
	}
	
	if(testM5311.test_Mode != 0){
		testM5311.communica_flag = 0;
		m5311Inf.communica_time = testM5311.communica_cnt*1;//定时器任务1S
		m5311Inf.connect_time = testM5311.connectErro_cnt*180 + m5311Inf.connect_time;//附网失败总时间+成功附网时间
		if(testM5311.test_cnt !=0 ){
			testM5311.linkTime[testM5311.cach] = m5311Inf.connect_time;
			testM5311.CommTime[testM5311.cach] = m5311Inf.communica_time;
			testM5311.cach++;
		}
		TIM3_Int_Init(9999,3199,DISABLE);
		testM5311.communica_cnt = 0;
		testM5311.connectErro_cnt = 0;
	}

	M5311_UNLOCK_Sleep();
	
	USART2_Close();
	Clr_BTDE_Power();
}



ErrorStatus  M5311_UDPSend_InfData_ALARM(uint8 sockit_id)
{
	uint8 i;
	char buff[40]={0};
	char port_buff[10];
	char data_buff[500];
	uint16 UDP_lenth = 0;

	char *p_value = NULL;
	uint16 check_ack_timeout = 0;

	ErrorStatus sendRet;
	uint8 *receive_flag=NULL;

	//配置接收模式：自动输出 hex 类型，格式：+IPRD:<socket_id>,<remote_addr>,<remote_port>,<data_len>,<data>
	M5311_send_cmd("AT+IPRCFG=1,2,1","OK",100);
	
	Com_Send_State();
	ByteToHexStr(UDP_Buff ,data_buff, UDP_Buff[3]+6);
	UDP_lenth = UDP_Buff[3] + 6;
	
	sendRet = send_UDP_msg(sockit_id,UDP_lenth,data_buff,buff,port_buff);
	if(sendRet == ERROR)
	{
		for(i = 0;i<10;i++){
			sendRet = send_UDP_msg(sockit_id,UDP_lenth,data_buff,buff,port_buff);
			os_dly_wait(1000);
			if(sendRet == 0){
				break;
			}
		}
	}

	if(sendRet == SUCCESS){
		check_ack_timeout = 0;
		//等待30S接收数据
		while((receive_flag == NULL) && (check_ack_timeout<1500))
		{		
			receive_flag = M5311_check_ack("+IPRD:");
			check_ack_timeout++;
			os_dly_wait(20);
		}
		
		//接收到数据再延时等待全部接收完毕
		if(receive_flag != NULL){
			os_dly_wait(1000);
		}
		sprintf(buff ,",22,AAD02011%08X", number);
		p_value = strstr(usart2_rcvd_buf , buff);
		if(p_value != NULL){
			HexToInt(data_buff,p_value+4,22);
			if(data_buff[9] == 1){
				upload_interval = data_buff[10];
				sample_interval = data_buff[11];
				temperature_alarm_value = data_buff[12];
				temperature_alarm_bound = data_buff[13];
				temp_upload_time = data_buff[14];					
				temp_sample_time= data_buff[15];
				temp_temperature_alarm = data_buff[16];
				temp_temperature_bound = data_buff[17];
				move_detection_time = data_buff[18];
				move_sensitivity = data_buff[19];    
				
				/*******利用移动模块设置灵敏度改变光电报警开关*************/
				if(move_sensitivity==0)
				{
						IR_alarm_Enable=0;//0没有光电报警 
				}else if(move_sensitivity==1)
				{
				    IR_alarm_Enable=1;//1开始报警
				}
				/*********************************************************/      	
				
				if(temperature_alarm_bound == 0)
					temperature_alarm_bound = 1;							
			}
			Test_NB_flag = 1;
			return SUCCESS;
		}
	}

	return ERROR;
}


//UDP发送报警数据至服务器
ErrorStatus  M5311_UDPSend_ALARMData(uint8 alarm_type)
{
	uint8 i;
	char buff[40]={0};
	char port_buff[10];
	char data_buff[500];
	uint16 UDP_lenth = 0;

	char *p_value = NULL;
	uint16 check_ack_timeout = 0;

	ErrorStatus sendRet;
	uint8 *receive_flag=NULL;

	sprintf(buff, "%d.%d.%d.%d",destinationIP[0],destinationIP[1],destinationIP[2],destinationIP[3]);
	sprintf(port_buff, "%d",destinationPort);
	
	creat_UDP_socket(LOCAL_UDP_SOCKIT_ID,buff,port_buff);
	//配置接收模式：自动输出 hex 类型，格式：+IPRD:<socket_id>,<remote_addr>,<remote_port>,<data_len>,<data>
	M5311_send_cmd("AT+IPRCFG=1,2,1","OK",100);
	
	Com_Send_Alarm(alarm_type);
	ByteToHexStr(UDP_Buff ,data_buff, UDP_Buff[3]+6);
	UDP_lenth = UDP_Buff[3] + 6;
	
	sendRet = send_UDP_msg(LOCAL_UDP_SOCKIT_ID,UDP_lenth,data_buff,buff,port_buff);
	if(sendRet == ERROR)
	{
		for(i = 0;i<10;i++){
			sendRet = send_UDP_msg(LOCAL_UDP_SOCKIT_ID,UDP_lenth,data_buff,buff,port_buff);
			os_dly_wait(1000);
			if(sendRet == 0){
				break;
			}
		}
	}

	if(sendRet == SUCCESS){
		check_ack_timeout = 0;
		//等待30S接收数据
		while((receive_flag == NULL) && (check_ack_timeout<1500))
		{		
			receive_flag = M5311_check_ack("+IPRD:");
			check_ack_timeout++;
			os_dly_wait(20);
		}
		
		//接收到数据再延时等待全部接收完毕
		if(receive_flag != NULL){
			os_dly_wait(1000);
		}

		sprintf(buff ,",11,AAD03005%08X", number );
		p_value = strstr(usart2_rcvd_buf , buff);
		if(p_value != NULL){
			//同时发送测量数据
			M5311_UDPSend_InfData_ALARM(LOCAL_UDP_SOCKIT_ID);		
		}

		return SUCCESS;
	}

	return ERROR;
}


void M5311_Send_alarm(uint8 alarm_type)
{
	uint8 i;
	uint8 succeed = 1;
	uint8 count = 0;
	ErrorStatus status;
	
	//初始化GPIO
	Ctr_M5311_WakeIn_Gpio();
	Ctr_M5311_RST();
	Ctr_M5311_PMS_PIN();
	
	Init_USART2();
	Set_BTDE_Power();//启动电平转换电源
	
	//硬件上电
	//Set_M5311_Power();
	
	//PSM
	//M5311_WakeUp_FromPSM();

	//根据模块状态选择启动模式
	status = M5311_PowerOn();
	if(status == ERROR){
		//正常启动失败，模块没有反映，重启模块
		M5311_FailurePowerOn();
	}

	//注册网络，附网
	status = M5311_InitNetWork();
	if(status == SUCCESS)
		succeed = 1;
	else
		succeed = 0;
	
	while(succeed){

		signal = m5311Inf.rssi;

		status = M5311_UDPSend_ALARMData(alarm_type);

		if(status == SUCCESS){
			close_socket(LOCAL_UDP_SOCKIT_ID);
		}
		else{
			//根据模块状态选择启动模式
			status = M5311_PowerOn();
			if(status == ERROR){
				//正常启动失败，模块没有反映，重启模块
				M5311_FailurePowerOn();
			}

			//注册网络，附网
			status = M5311_InitNetWork();
		}

		count++;
		if(count >= 5){
			succeed = 0;
		}
	}

	
	M5311_UNLOCK_Sleep();
	
	USART2_Close();
	Clr_BTDE_Power();
}



#else

void M5311_Send_Inf(void){
	uint8 i;
	char buff[50]={0};
	char port_buff[10];
	char data_buff[500];
	uint16 UDP_lenth = 0;
	uint8 succeed = 1;
	char *p_value = NULL;
	uint8 count = 0;
	uint8 check_ack_timeout = 0;

	uint8 sendRet = 1;
	
	
	Init_USART2();
	M5311_PMS_Init();
	M5311_Wake();
	Set_BTDE_Power();//启动电平转换电源
	IWDG_ReloadCounter();
	Set_M5311_Power();//启动M5311电源
	os_dly_wait(100);
	M5311_Wake_UP();//如果睡眠唤醒模块
	
	M5311_power_on();//发送指令
	IWDG_ReloadCounter();
	os_dly_wait(1000);
	succeed = query_net_status();//附网

	while(succeed){

		if(!M5311_send_cmd("AT+CGPADDR=1","+CGPADDR: 1",100))	
		{
				signal = Get_M5311_signal();
				sprintf(buff, "%d.%d.%d.%d",destinationIP[0],destinationIP[1],destinationIP[2],destinationIP[3]);
				sprintf(port_buff, "%d",destinationPort);
				creat_UDP_socket(LOCAL_UDP_SOCKIT_ID,buff,port_buff);
				Com_Send_State();
				ByteToHexStr(UDP_Buff ,data_buff, UDP_Buff[3]+6);
				UDP_lenth = UDP_Buff[3] + 6;
				
				sendRet = send_UDP_msg(LOCAL_UDP_SOCKIT_ID,UDP_lenth,data_buff,buff,port_buff);
				IWDG_ReloadCounter();
				os_dly_wait(2000);
				if(sendRet == 1)
				{
					for(i = 0;i<10;i++){
						IWDG_ReloadCounter();
						sendRet = send_UDP_msg(LOCAL_UDP_SOCKIT_ID,UDP_lenth,data_buff,buff,port_buff);
						os_dly_wait(2000);
						if(sendRet == 0){
							break;
						}
					}
				}

				if(sendRet == 0)
				{
					//10000010--->0x05F5E10A
					while(M5311_send_cmd("AT+IPRCFG=1,2,1","+IPRD:",100)&&(check_ack_timeout<6))
					{		
							check_ack_timeout++;
							os_dly_wait(100);
							IWDG_ReloadCounter();
					}
					IWDG_ReloadCounter();
					sprintf(buff ,",22,AAD02011%08X", number);
					p_value = strstr(usart2_rcvd_buf , buff);
						if(p_value != NULL){
							HexToInt(data_buff,p_value+4,22);
							if(data_buff[9] == 1){
								upload_interval = data_buff[10];
								sample_interval = data_buff[11];
								temperature_alarm_value = data_buff[12];
								temperature_alarm_bound = data_buff[13];
								temp_upload_time = data_buff[14];					
								temp_sample_time= data_buff[15];
								temp_temperature_alarm = data_buff[16];
								temp_temperature_bound = data_buff[17];
								move_detection_time = data_buff[18];
								move_sensitivity = data_buff[19];    
	/*******利用移动模块设置灵敏度改变光电报警开关*************/
								if(move_sensitivity==0)
								{
										IR_alarm_Enable=0;//0没有光电报警 
								}else if(move_sensitivity==1)
								{
								    IR_alarm_Enable=1;//1开始报警
								}
	/*********************************************************/      								
								if(temperature_alarm_bound == 0)
									temperature_alarm_bound = 1;							
							}
							succeed = 0;
							Test_NB_flag = 1;
						}
				}
					sprintf(buff, "at+ipclose=%d",LOCAL_UDP_SOCKIT_ID);
					M5311_send_cmd(buff,"OK",50);
		}
			else{
				M5311_power_on();
				os_dly_wait(100);
				query_net_status();
			}
			if(set_state == 1){
					succeed = 0;
				}

			count++;
			if(count >= 5){
				succeed = 0;
			}
		}
		M5311_UNLOCK_Sleep();
		
	USART2_Close();
	Clr_M5311_Power();
	Clr_BTDE_Power();
		Ctr_M5311_RST();
		Ctr_M5311_Wake();
}







void Send_Inf_Online(uint8 socket_id){
	uint8 i;
	char buff[50]={0};
	char port_buff[10];
	char data_buff[500];
	uint16 UDP_lenth = 0;
	char *p_value = NULL;
	uint8 check_ack_timeout = 0;

	uint8 sendRet = 1;
	IWDG_ReloadCounter();
	signal = Get_M5311_signal();
	sprintf(buff, "%d.%d.%d.%d",destinationIP[0],destinationIP[1],destinationIP[2],destinationIP[3]);
	sprintf(port_buff, "%d",destinationPort);
	creat_UDP_socket(LOCAL_UDP_SOCKIT_ID,buff,port_buff);
	Com_Send_State();
	ByteToHexStr(UDP_Buff ,data_buff, UDP_Buff[3]+6);
	UDP_lenth = UDP_Buff[3] + 6;
	
	sendRet = send_UDP_msg(LOCAL_UDP_SOCKIT_ID,UDP_lenth,data_buff,buff,port_buff);
	IWDG_ReloadCounter();
	os_dly_wait(2000);
	if(sendRet == 1)
	{
		for(i = 0;i<10;i++){
			sendRet = send_UDP_msg(LOCAL_UDP_SOCKIT_ID,UDP_lenth,data_buff,buff,port_buff);
			os_dly_wait(2000);
			IWDG_ReloadCounter();
			if(sendRet == 0){
				break;
			}
		}
	}

	if(sendRet == 0)
	{
		//10000010--->0x05F5E10A
		while(M5311_send_cmd("AT+IPRCFG=1,2,1","+IPRD:",100)&&(check_ack_timeout<6))
		{		
				check_ack_timeout++;
				os_dly_wait(100);
				IWDG_ReloadCounter();
		}
		IWDG_ReloadCounter();
		sprintf(buff ,",22,AAD02011%08X", number);
		p_value = strstr(usart2_rcvd_buf , buff);
			if(p_value != NULL){
							HexToInt(data_buff,p_value+4,22);
				if(data_buff[9] == 1){
					upload_interval = data_buff[10];
					sample_interval = data_buff[11];
					temperature_alarm_value = data_buff[12];
					temperature_alarm_bound = data_buff[13];
					temp_upload_time = data_buff[14];					
					temp_sample_time= data_buff[15];
					temp_temperature_alarm = data_buff[16];
					temp_temperature_bound = data_buff[17];
					move_detection_time = data_buff[18];
					move_sensitivity = data_buff[19];       
					if(temperature_alarm_bound == 0)
						temperature_alarm_bound = 1;							
				}
			}
	}
}

void M5311_Send_alarm(uint8 alarm_type){
	uint8 i;
	char buff[50]={0};
	char port_buff[10];
	char data_buff[500];
	uint16 UDP_lenth = 0;
	uint8 succeed = 1;
	char *p_value = NULL;
	uint8 count = 0;
	uint8 check_ack_timeout = 0;

	uint8 sendRet = 1;
	
	IWDG_ReloadCounter();
	Init_USART2();
	M5311_PMS_Init();
	M5311_Wake();
	Set_BTDE_Power();//启动电平转换电源
	Set_M5311_Power();//启动M5311电源
	os_dly_wait(100);
	M5311_Wake_UP();//如果睡眠唤醒模块
	
	M5311_power_on();//发送指令
	IWDG_ReloadCounter();
	os_dly_wait(1000);
	IWDG_ReloadCounter();
	succeed = query_net_status();//附网

	while(succeed){
		IWDG_ReloadCounter();
		if(!M5311_send_cmd("AT+CGPADDR=1","+CGPADDR: 1",100))	
		{
				signal = Get_M5311_signal();
				sprintf(buff, "%d.%d.%d.%d",destinationIP[0],destinationIP[1],destinationIP[2],destinationIP[3]);
				sprintf(port_buff, "%d",destinationPort);
				creat_UDP_socket(LOCAL_UDP_SOCKIT_ID,buff,port_buff);
				Com_Send_Alarm(alarm_type);
				ByteToHexStr(UDP_Buff ,data_buff, UDP_Buff[3]+6);
				UDP_lenth =UDP_Buff[3]+6;
				
				sendRet = send_UDP_msg(LOCAL_UDP_SOCKIT_ID,UDP_lenth,data_buff,buff,port_buff);
				IWDG_ReloadCounter();
				os_dly_wait(2000);
				if(sendRet == 1)
				{
					for(i = 0;i<10;i++){
						sendRet = send_UDP_msg(LOCAL_UDP_SOCKIT_ID,UDP_lenth,data_buff,buff,port_buff);
						os_dly_wait(2000);
						IWDG_ReloadCounter();
						if(sendRet == 0){
							break;
						}
					}
				}

				if(sendRet == 0)
				{
					//10000010--->0x05F5E10A
					while(M5311_send_cmd("AT+IPRCFG=1,2,1","+IPRD:",100)&&(check_ack_timeout<6))
					{		
							check_ack_timeout++;
							os_dly_wait(100);
							IWDG_ReloadCounter();
					}
					IWDG_ReloadCounter();
					sprintf(buff ,",11,AAD03005%08X", number );
					p_value = strstr(usart2_rcvd_buf , buff);
						if(p_value != NULL){
							succeed = 0;
							//同时发送测量数据
							Send_Inf_Online(LOCAL_UDP_SOCKIT_ID);		
						}
				}
					sprintf(buff, "at+ipclose=%d",LOCAL_UDP_SOCKIT_ID);
					M5311_send_cmd(buff,"OK",50);
		}
			else{
				M5311_power_on();
				os_dly_wait(100);
				query_net_status();
			}
			if(set_state == 1){
					succeed = 0;
				}

			count++;
			if(count >= 5){
				succeed = 0;
			}
		}
		M5311_UNLOCK_Sleep();
		
		USART2_Close();
		Clr_M5311_Power();
		Clr_BTDE_Power();
		Ctr_M5311_RST();
		Ctr_M5311_Wake();
}

#endif


