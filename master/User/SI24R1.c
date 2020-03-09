#include "SI24R1.h"

const u8 TX_ADDRESS[TX_ADR_WIDTH] = {0x0A,0x01,0x07,0x0E,0x01};  // ����һ����̬���͵�ַ
const u8 RF_CHANNEL[CH_NUM] = {2, 10, 20, 30, 40, 50, 60, 70, 80, 90, 120};//����RF��ͨѶͨ����һ������ 0 -9 ���� 10��



static u8 SPI_RW(u8 byte)
{
	u8 bit_ctr;
	for(bit_ctr=0; bit_ctr<8; bit_ctr++)
	{
		if(byte & 0x80)
			CC_MO_H;//MOSI = 1;
		else
			CC_MO_L;//MOSI = 0;																 
		byte = (byte << 1);                      
		CC_SLK_H;//SCK = 1;                                   
		byte |= CC2500_MI;//MISO;     
		//SPIWait();
		CC_SLK_L;//SCK = 0;                                
	}
	return(byte);                              
}


/********************************************************
�������ܣ�SI24R1���ų�ʼ��                
��ڲ�������
����  ֵ����
*********************************************************/
void SI24R1_Init(void)
{
	//SCK = 0; 													//SPIʱ��������
	//CSN = 1;				
	//CE 	= 0;				
	//IRQ = 1;

	GPIO_InitTypeDef GPIO_InitStru;

    //SPI_2 Interface
    GPIO_InitStru.GPIO_Pin = CC_SCLK + CC_MOSI;
    GPIO_InitStru.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStru.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStru.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStru.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(CC_GPIO,&GPIO_InitStru);
	GPIO_ResetBits(CC_GPIO,CC_SCLK);


    GPIO_InitStru.GPIO_Pin = CC_MISO;
    GPIO_InitStru.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStru.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStru.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStru.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(CC_GPIO,&GPIO_InitStru);
    
    GPIO_InitStru.GPIO_Pin = CC_CSn;
    GPIO_InitStru.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStru.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStru.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStru.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(CC_GPIO,&GPIO_InitStru);
	GPIO_SetBits(CC_GPIO,CC_CSn);

	GPIO_InitStru.GPIO_Pin = CC_CE;
    GPIO_InitStru.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStru.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStru.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStru.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(CC_GPIO,&GPIO_InitStru);
	GPIO_ResetBits(CC_GPIO,CC_CE);

    //GDO PINs
    GPIO_InitStru.GPIO_Pin = CC_IRQ;
    GPIO_InitStru.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStru.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStru.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(CC_GPIO,&GPIO_InitStru);
	
}


/********************************************************
�������ܣ�д�Ĵ�����ֵ�����ֽڣ�                
��ڲ�����reg:�Ĵ���ӳ���ַ����ʽ��WRITE_REG��reg��
					value:�Ĵ�����ֵ
����  ֵ��״̬�Ĵ�����ֵ
*********************************************************/
u8 SI24R1_Write_Reg(u8 reg, u8 value)
{
	u8 status;

	CC_CSn_L;//CSN = 0;                 
	status = SPI_RW(reg);				
	SPI_RW(value);
	CC_CSn_H;//CSN = 1;  
	
	return(status);
}


/********************************************************
�������ܣ�д�Ĵ�����ֵ�����ֽڣ�                  
��ڲ�����reg:�Ĵ���ӳ���ַ����ʽ��WRITE_REG��reg��
					pBuf:д�����׵�ַ
					bytes:д�����ֽ���
����  ֵ��״̬�Ĵ�����ֵ
*********************************************************/
u8 SI24R1_Write_Buf(u8 reg, const u8 *pBuf, u8 bytes)
{
	u8 status,byte_ctr;

  CC_CSn_L;//CSN = 0;                                  			
  status = SPI_RW(reg);                          
  for(byte_ctr=0; byte_ctr<bytes; byte_ctr++)     
    SPI_RW(*pBuf++);
  CC_CSn_H;//CSN = 1;                                      	

  return(status);       
}							  					   


/********************************************************
�������ܣ���ȡ�Ĵ�����ֵ�����ֽڣ�                  
��ڲ�����reg:�Ĵ���ӳ���ַ����ʽ��READ_REG��reg��
����  ֵ���Ĵ���ֵ
*********************************************************/
u8 SI24R1_Read_Reg(u8 reg)
{
 	u8 value;

	CC_CSn_L;//CSN = 0;    
	SPI_RW(reg);			
	value = SPI_RW(0);
	CC_CSn_H;//CSN = 1;              

	return(value);
}


/********************************************************
�������ܣ���ȡ�Ĵ�����ֵ�����ֽڣ�                  
��ڲ�����reg:�Ĵ���ӳ���ַ��READ_REG��reg��
					pBuf:���ջ��������׵�ַ
					bytes:��ȡ�ֽ���
����  ֵ��״̬�Ĵ�����ֵ
*********************************************************/
u8 SI24R1_Read_Buf(u8 reg, u8 *pBuf, u8 bytes)
{
	u8 status,byte_ctr;

  CC_CSn_L;//CSN = 0;                                        
  status = SPI_RW(reg);                           
  for(byte_ctr=0;byte_ctr<bytes;byte_ctr++)
    pBuf[byte_ctr] = SPI_RW(0);                   //��ȡ���ݣ����ֽ���ǰ
  CC_CSn_H;//CSN = 1;                                        

  return(status);    
}

void SI24R1_Standby_Mode(void)
{
	CC_CE_L;//CE=0;	
	//SI24R1_Write_Reg(WRITE_REG1 + CONFIG, 0x00);
}

/********************************************************
�������ܣ�SI24R1����ģʽ��ʼ��                      
��ڲ�������
����  ֵ����
*********************************************************/
void SI24R1_RX_Mode(uint8 ch)
{
	CC_CE_L;//CE=0;	
	SI24R1_Write_Buf(WRITE_REG1 + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);	// �����豸����ͨ��0ʹ�úͷ����豸��ͬ�ķ��͵�ַ
	SI24R1_Write_Reg(WRITE_REG1 + EN_AA, 0x01);               						// ʹ�ܽ���ͨ��0�Զ�Ӧ��
	SI24R1_Write_Reg(WRITE_REG1 + EN_RXADDR, 0x01);           						// ʹ�ܽ���ͨ��0
	SI24R1_Write_Reg(WRITE_REG1 + RF_CH, RF_CHANNEL[ch]);                 						// ѡ����Ƶͨ��0x40
	SI24R1_Write_Reg(WRITE_REG1 + RX_PW_P0, TX_PLOAD_WIDTH);  						// ����ͨ��0ѡ��ͷ���ͨ����ͬ��Ч���ݿ��
	SI24R1_Write_Reg(WRITE_REG1 + RF_SETUP, 0x0f);            						// ���ݴ�����2Mbps�����书��7dBm
	SI24R1_Write_Reg(WRITE_REG1 + CONFIG, 0x0f);              						// CRCʹ�ܣ�16λCRCУ�飬�ϵ磬����ģʽ
	SI24R1_Write_Reg(WRITE_REG1 + STATUS, 0xff);  												//������е��жϱ�־λ
	CC_CE_H;//CE=1;	                                          									// ����CE���������豸
}						


/********************************************************
�������ܣ�SI24R1����ģʽ��ʼ��                      
��ڲ�������
����  ֵ����
*********************************************************/
void SI24R1_TX_Mode(uint8 ch)
{
	CC_CE_L;//CE=0;	
	SI24R1_Write_Buf(WRITE_REG1 + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);     // д�뷢�͵�ַ
	SI24R1_Write_Buf(WRITE_REG1 + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);  // Ϊ��Ӧ������豸������ͨ��0��ַ�ͷ��͵�ַ��ͬ

	SI24R1_Write_Reg(WRITE_REG1 + EN_AA, 0x01);       											// ʹ�ܽ���ͨ��0�Զ�Ӧ��
	SI24R1_Write_Reg(WRITE_REG1 + EN_RXADDR, 0x01);   											// ʹ�ܽ���ͨ��0
	SI24R1_Write_Reg(WRITE_REG1 + SETUP_RETR, 0x0a);  											// �Զ��ط���ʱ�ȴ�250us+86us���Զ��ط�10��
	SI24R1_Write_Reg(WRITE_REG1 + RF_CH, RF_CHANNEL[ch]);         											// ѡ����Ƶͨ��0x40
	SI24R1_Write_Reg(WRITE_REG1 + RF_SETUP, 0x0f);    											// ���ݴ�����2Mbps�����书��7dBm
	SI24R1_Write_Reg(WRITE_REG1 + CONFIG, 0x0e);      											// CRCʹ�ܣ�16λCRCУ�飬�ϵ�
	//CE = 1;
}


/********************************************************
�������ܣ���ȡ��������                       
��ڲ�����rxbuf:�������ݴ���׵�ַ
����  ֵ��0:���յ�����
          1:û�н��յ�����
*********************************************************/
u8 SI24R1_RxPacket(u8 *rxbuf)
{
	u8 state;
	state = SI24R1_Read_Reg(STATUS);  			                 //��ȡ״̬�Ĵ�����ֵ    	  
	SI24R1_Write_Reg(WRITE_REG1+STATUS,state);               //���RX_DS�жϱ�־

	if(state & RX_DR)								                           //���յ�����
	{
		SI24R1_Read_Buf(RD_RX_PLOAD,rxbuf,TX_PLOAD_WIDTH);     //��ȡ����
		SI24R1_Write_Reg(FLUSH_RX,0xff);					              //���RX FIFO�Ĵ���
		return 0; 
	}
	return 1;//û�յ��κ�����
}


/********************************************************
�������ܣ�����һ�����ݰ�                      
��ڲ�����txbuf:Ҫ���͵�����
����  ֵ��0x10:�ﵽ����ط�����������ʧ�� 
          0x20:���ͳɹ�            
          0xff:����ʧ��                  
*********************************************************/
u8 SI24R1_TxPacket(u8 *txbuf)
{
	u8 state;
	u32 count = 0;
	CC_CE_L;//CE=0;																										  //CE���ͣ�ʹ��SI24R1����
	SI24R1_Write_Buf(WR_TX_PLOAD, txbuf, TX_PLOAD_WIDTH);	    //д���ݵ�TX FIFO,32���ֽ�
 	CC_CE_H;//CE=1;																										  //CE�øߣ�ʹ�ܷ���	   
	
	while((IRQ_IN != 0) && (count<100000)){count++;}																				  //�ȴ��������
	state = SI24R1_Read_Reg(STATUS);  											  //��ȡ״̬�Ĵ�����ֵ	   
	SI24R1_Write_Reg(WRITE_REG1+STATUS, state); 								//���TX_DS��MAX_RT�жϱ�־
	if(state&MAX_RT)																			    //�ﵽ����ط�����
	{
		SI24R1_Write_Reg(FLUSH_TX,0xff);										    //���TX FIFO�Ĵ��� 
		return MAX_RT; 
	}
	if(state&TX_DS)																			      //�������
	{
		return TX_DS;
	}
	return 0XFF;																						  //����ʧ��
}

