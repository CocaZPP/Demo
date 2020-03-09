#include "M5311.h"
#include "rtl.h"
#include "main.h"

extern __IO uint8_t set_state;//����״̬���Ƿ��ֶ�������ʾ
extern __IO uint8_t led_need_blink;//������־

M5311_INF m5311Inf;//ģ����Ϣ
Test_M5311 testM5311;//����M5311
/*********************************************************************************/
//M5311 Ӳ���������

//******************************************
//M5311 �ϵ翪��
//�� PWR_ON/OFF ��Ϊ�͵�ƽ������ 2s ���ϼ��ɿ���������֮����Ҫ�øߵ�ƽ��
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
//M5311 �ϵ翪��
//�� PWR_ON/OFF ��Ϊ�͵�ƽ������ 12s ʵ�ֹػ�������������ʱ 20s�󣬽�������������
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
//M5311 PWR_ON/OFF ��Ϊ�������������ʱ����
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
//M5311 ��λ��Ϊ�������������ʱ����
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
//M5311 ��λ��Ϊ�������������ʱ����
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

//M5311 ��λ RST����200ms
//����ģ���޷�Ӧ�������ʹ��
void ResetM5311(void)
{
	M5311_RST_Init();
	GPIO_SetBits(M5311_RST_GPIO,M5311_RST_PIN);
	os_dly_wait(200);
	GPIO_ResetBits(M5311_RST_GPIO,M5311_RST_PIN);
	Ctr_M5311_RST();
}

//******************************************
//M5311 PMSģʽ״̬
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
//M5311 ��ȡ������ Active_mode PSM_mode
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
//M5311 WAKE_PIN ���ģʽ OD NOPULL
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
//M5311 WAKE_PIN ��λ��Ϊ�������������ʱ����
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
//M5311 ��ģ����PSMģʽ����
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
 //�ر�˯��
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
//��˯��
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
//��鷵�ص���Ӧ�Ƿ����Ԥ��
//�������ΪԤ�ڷ��ص��ַ���
//����NULL������ֵ��û��Ԥ���ַ���
//����ֵ��Ԥ���ַ����ڵ�λ��
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

//����atָ���
//cmd:atָ�ack��Ԥ����Ӧ��waittime,��ʱʱ��
//����0�����ͳɹ�
//����1�����ͳ�ʱ
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

//��ⷵ�ذ��Ƿ�ΪԤ��ֵ ����ֵ��0 ��ȷ 1 ����
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
//��ȡM5311�ź���
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
//��ȡͨѶ������
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
//��ѯSOCKET_ID �Ƿ��Ѿ���,����Ѱ󶨣�����socket_id, û�а��򷵻�0
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
//��ȡ���ݣ���ȡ���ջ�������������ݱ��浽des,posΪ��ʼ��ַ��lenΪ��ȡ����
void get_str_data(char* des,char pos,char len)
{
    memcpy(des,usart2_rcvd_buf+pos,len);
}

//*******************************************
//����UDP���ӣ��������õ�UDP sockit��(0-4)���������õ�socket id�ţ�ʧ�ܷ���0
uint8 creat_UDP_socket(uint8 sockt_id,char *hostIP,char *port)
{
	char temp[64]={0};
	sprintf(temp, "AT+IPSTART=%d,\"UDP\",\"%s\",%s", sockt_id,hostIP, port);
	if(!M5311_send_cmd(temp,"OK",100))//�������UDP�׽��ֳɹ�
	{
		return sockt_id;
	}
    return 0xff;
}

//*******************************************
//�ر�UDP����
ErrorStatus close_socket(uint8 sockt_id)
{
	char temp[64]={0};
	sprintf(temp, "AT+IPCLOSE=%d", sockt_id);
	if(!M5311_send_cmd(temp,"OK",200))//�������UDP�׽��ֳɹ�
	{
		return SUCCESS;
	}
    return ERROR;
}


//*******************************************
//����TCP���ӣ��������õ�TCP sockit��(0-4)���������õ�socket id�ţ�ʧ�ܷ���0
uint8 creat_TCP_socket(uint8 sockt_id,char *hostIP,char *port)
{
	char temp[64]={0};
	sprintf(temp, "AT+IPSTART=%d,\"TCP\",\"%s\",%s", sockt_id,hostIP, port);
	if(!M5311_send_cmd(temp,"OK",100))//�������UDP�׽��ֳɹ�
	{
		return sockt_id;
	}
    return 0xff;
}

//*******************************************
//�������ݺ���������sockt_id,���ݳ��ȣ�����,����IP��Զ�������˿ڣ�
//�������粻�ȶ������͵ȴ�10����
//����ֵ0�����ͳɹ�������UDPΪ���Ĵ��䣬���������Ƿ���յ�ģ�����޷�ȷ�ϵģ�
//����ֵ1������ʧ��
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
//�������ݺ���������sockt_id,���ݳ��ȣ�����, IPTOS���ȼ�
//������ʱʹ���ַ�������
//����ֵ0�����ͳɹ�������UDPΪ���Ĵ��䣬���������Ƿ���յ�ģ�����޷�ȷ�ϵģ�
//����ֵ1������ʧ��
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
//��ȡM5311ģ����Ϣ
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

	//��ʼ��GPIO
	Ctr_M5311_WakeIn_Gpio();
	Ctr_M5311_RST();
	Ctr_M5311_PMS_PIN();
	
	Init_USART2();
	Set_BTDE_Power();//������ƽת����Դ
	
	//Ӳ���ϵ�
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
		//��ȡ�ź�����
		m5311Inf.rssi = Get_M5311_signal();
		//��ȡ�ֻ�����
		Get_M5311_IMSI(m5311Inf.imsi);
		//��⸽��
		M5311_InitNetWork();
		//��������
		M5311_UNLOCK_Sleep();

		USART2_Close();
		Clr_BTDE_Power();
		
		return SUCCESS;
	}
}

//**************************************************
//M5311פ������
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

	//��ȡ�ź�����
	m5311Inf.rssi = Get_M5311_signal();
	
	M5311_LOCK_Sleep();//�ر�˯��
}

//**************************************************
uint8_t query_net_status(void)
{
	uint8_t res = 0;
	uint8_t attached_flag = 0;
	
	led_need_blink = 1;

	 //����  
	 check_ack_timeout = 20;//
	while((attached_flag == 0) && check_ack_timeout)
	{
		if(!M5311_send_cmd("AT+CGPADDR=1","+CGPADDR: 1",200))//AT+CEREG?//��ѯ����״̬
		{//�����ɹ�
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
//M5311 ��ʼ�����磺ע�����磬������
ErrorStatus M5311_InitNetWork(void)
{
	uint8 stepNum = 0;
	
	//��ȡ�ź�����
	m5311Inf.rssi = Get_M5311_signal();

	//M5311_send_cmd("AT+CSCON=1","OK",100);//AT+CSQ

	//ע������
	check_ack_timeout = 20;//
	while(check_ack_timeout)
	{
		// 1 ��ע�ᣬע�ᵽ��������
		// 5 ��ע�ᣬע�ᵽ��������CEREG: 0,1
		if(M5311_send_cmd("AT+CEREG?","CEREG: 0,1",50)==0 || M5311_send_cmd("AT+CEREG?","CEREG: 0,5",50)==0)//AT+CEREG?//��ѯ����״̬
		{
			//ע������ɹ�
			stepNum = 1;
			break;
		}
		check_ack_timeout--;
		os_dly_wait(200);
	}

	//����
	if(stepNum == 1){
		check_ack_timeout = 200;//�180s
		while(check_ack_timeout)
		{
			check_ack_timeout--;
			if(M5311_send_cmd("AT+CGACT?","CGACT: 1,1",50)==0)//AT+CEREG?//��ѯ����״̬
			{
				//�����ɹ�
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
//M5311 �ϵ翪����ʼ����ģ���ϵ�ʱ����
ErrorStatus M5311_InitPowerOn(void)
{
	m5311Inf.cardOk = 0;
	m5311Inf.connect_time = 0;
	m5311Inf.error = E_OK;
	memset(m5311Inf.imsi,0,30);
	m5311Inf.rssi = 99;
	m5311Inf.rxlevel = 99;
	m5311Inf.linkNet = 0;

	//��ʼ��GPIO
	Ctr_M5311_WakeIn_Gpio();
	Ctr_M5311_RST();
	Ctr_M5311_PMS_PIN();
	
	Init_USART2();
	Set_BTDE_Power();//������ƽת����Դ
	
	//Ӳ���ϵ�
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
		//��ȡ�ź�����
		m5311Inf.rssi = Get_M5311_signal();
		//��ȡ�ֻ�����
		Get_M5311_IMSI(m5311Inf.imsi);
		//��������
		M5311_UNLOCK_Sleep();
	
		USART2_Close();
		Clr_BTDE_Power();
		
		return SUCCESS;
	}
}

//**************************************************
//M5311 ͨѶʧ�ܣ�����ģ���ʼ��
//ģ��ͨѶ3��ʧ�ܺ���ã���ģ��ػ���Ȼ��λģ�飬�ڰ��ϵ�����
ErrorStatus M5311_FailurePowerOn(void)
{
	//Ӳ���ϵ�
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
		M5311_LOCK_Sleep();//�ر�˯��
		return SUCCESS;
	}
}

//**************************************************
//M5311 ��ģ��������ģʽ���ѣ�ģ�鿪ʼͨѶʱ����
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
				M5311_LOCK_Sleep();//�ر�˯��
				return SUCCESS;
			}
		}
	}
	else{
		return ERROR;
	}
}


//**************************************************
//M5311 ģ��PowerOn�����ݲ�ͬ״̬�Զ�ѡ��ģʽ
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
			M5311_LOCK_Sleep();//�ر�˯��
			return SUCCESS;
		}
	}
}

#if 1

//UDP���ͼ��������������
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
		//����UDP�����շ�ʱ��
		testM5311.communica_flag = 1;
		TIM3_Int_Init(9999,3199,ENABLE);
	}
	sprintf(buff, "%d.%d.%d.%d",destinationIP[0],destinationIP[1],destinationIP[2],destinationIP[3]);
	sprintf(port_buff, "%d",destinationPort);
	
	creat_UDP_socket(LOCAL_UDP_SOCKIT_ID,buff,port_buff);
	//���ý���ģʽ���Զ���� hex ���ͣ���ʽ��+IPRD:<socket_id>,<remote_addr>,<remote_port>,<data_len>,<data>
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
		//�ȴ�30S��������
		while((receive_flag == NULL) && (check_ack_timeout<1500))
		{		
			receive_flag = M5311_check_ack("+IPRD:");
			check_ack_timeout++;
			os_dly_wait(20);
		}
		
		//���յ���������ʱ�ȴ�ȫ���������
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
				
				/*******�����ƶ�ģ�����������ȸı��籨������*************/
				if(move_sensitivity==0)
				{
						IR_alarm_Enable=0;//0û�й�籨�� 
				}else if(move_sensitivity==1)
				{
				    IR_alarm_Enable=1;//1��ʼ����
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




//ϵͳ��Ϣ�ϴ��������¶�ֵ
void M5311_Send_Inf(void)
{
	uint8 i=0;
	uint8 j=0;
	uint8 succeed = 1;
	uint8 count = 0;
	ErrorStatus status;
	
	//��ʼ��GPIO
	Ctr_M5311_WakeIn_Gpio();
	Ctr_M5311_RST();
	Ctr_M5311_PMS_PIN();
	
	Init_USART2();
	Set_BTDE_Power();//������ƽת����Դ
	
	//Ӳ���ϵ�
	//Set_M5311_Power();
	
	//PSM
	//M5311_WakeUp_FromPSM();

	//����ģ��״̬ѡ������ģʽ
	status = M5311_PowerOn();
	if(status == ERROR){
		//��������ʧ�ܣ�ģ��û�з�ӳ������ģ��
		M5311_FailurePowerOn();
	}

	//ע�����磬����
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
			//����ģ��״̬ѡ������ģʽ
			status = M5311_PowerOn();
			if(status == ERROR){
				//��������ʧ�ܣ�ģ��û�з�ӳ������ģ��
				M5311_FailurePowerOn();
			}
			//ע�����磬����
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
		m5311Inf.communica_time = testM5311.communica_cnt*1;//��ʱ������1S
		m5311Inf.connect_time = testM5311.connectErro_cnt*180 + m5311Inf.connect_time;//����ʧ����ʱ��+�ɹ�����ʱ��
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

	//���ý���ģʽ���Զ���� hex ���ͣ���ʽ��+IPRD:<socket_id>,<remote_addr>,<remote_port>,<data_len>,<data>
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
		//�ȴ�30S��������
		while((receive_flag == NULL) && (check_ack_timeout<1500))
		{		
			receive_flag = M5311_check_ack("+IPRD:");
			check_ack_timeout++;
			os_dly_wait(20);
		}
		
		//���յ���������ʱ�ȴ�ȫ���������
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
				
				/*******�����ƶ�ģ�����������ȸı��籨������*************/
				if(move_sensitivity==0)
				{
						IR_alarm_Enable=0;//0û�й�籨�� 
				}else if(move_sensitivity==1)
				{
				    IR_alarm_Enable=1;//1��ʼ����
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


//UDP���ͱ���������������
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
	//���ý���ģʽ���Զ���� hex ���ͣ���ʽ��+IPRD:<socket_id>,<remote_addr>,<remote_port>,<data_len>,<data>
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
		//�ȴ�30S��������
		while((receive_flag == NULL) && (check_ack_timeout<1500))
		{		
			receive_flag = M5311_check_ack("+IPRD:");
			check_ack_timeout++;
			os_dly_wait(20);
		}
		
		//���յ���������ʱ�ȴ�ȫ���������
		if(receive_flag != NULL){
			os_dly_wait(1000);
		}

		sprintf(buff ,",11,AAD03005%08X", number );
		p_value = strstr(usart2_rcvd_buf , buff);
		if(p_value != NULL){
			//ͬʱ���Ͳ�������
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
	
	//��ʼ��GPIO
	Ctr_M5311_WakeIn_Gpio();
	Ctr_M5311_RST();
	Ctr_M5311_PMS_PIN();
	
	Init_USART2();
	Set_BTDE_Power();//������ƽת����Դ
	
	//Ӳ���ϵ�
	//Set_M5311_Power();
	
	//PSM
	//M5311_WakeUp_FromPSM();

	//����ģ��״̬ѡ������ģʽ
	status = M5311_PowerOn();
	if(status == ERROR){
		//��������ʧ�ܣ�ģ��û�з�ӳ������ģ��
		M5311_FailurePowerOn();
	}

	//ע�����磬����
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
			//����ģ��״̬ѡ������ģʽ
			status = M5311_PowerOn();
			if(status == ERROR){
				//��������ʧ�ܣ�ģ��û�з�ӳ������ģ��
				M5311_FailurePowerOn();
			}

			//ע�����磬����
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
	Set_BTDE_Power();//������ƽת����Դ
	IWDG_ReloadCounter();
	Set_M5311_Power();//����M5311��Դ
	os_dly_wait(100);
	M5311_Wake_UP();//���˯�߻���ģ��
	
	M5311_power_on();//����ָ��
	IWDG_ReloadCounter();
	os_dly_wait(1000);
	succeed = query_net_status();//����

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
	/*******�����ƶ�ģ�����������ȸı��籨������*************/
								if(move_sensitivity==0)
								{
										IR_alarm_Enable=0;//0û�й�籨�� 
								}else if(move_sensitivity==1)
								{
								    IR_alarm_Enable=1;//1��ʼ����
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
	Set_BTDE_Power();//������ƽת����Դ
	Set_M5311_Power();//����M5311��Դ
	os_dly_wait(100);
	M5311_Wake_UP();//���˯�߻���ģ��
	
	M5311_power_on();//����ָ��
	IWDG_ReloadCounter();
	os_dly_wait(1000);
	IWDG_ReloadCounter();
	succeed = query_net_status();//����

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
							//ͬʱ���Ͳ�������
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


