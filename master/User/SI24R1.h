#ifndef __nRF24L01P__
#define __nRF24L01P__

#include "typedef.h"
#include "stm32l1xx_gpio.h"

#define CC_GPIO      GPIOB
#define CC_CSn      GPIO_Pin_12     //PB12
#define CC_SCLK     GPIO_Pin_13     //PB13
#define CC_MISO     GPIO_Pin_14     //PB14
#define CC_MOSI     GPIO_Pin_15     //PB15
#define CC_IRQ     GPIO_Pin_0      //PA8
#define CC_CE     GPIO_Pin_11     //PA11


#define CC_SLK_H		GPIO_SetBits(CC_GPIO,CC_SCLK)
#define CC_SLK_L		GPIO_ResetBits(CC_GPIO,CC_SCLK)

#define CC_MO_H		GPIO_SetBits(CC_GPIO,CC_MOSI)
#define CC_MO_L		GPIO_ResetBits(CC_GPIO,CC_MOSI)

#define CC2500_MI		GPIO_ReadInputDataBit(CC_GPIO,CC_MISO)

#define CC_CSn_H		GPIO_SetBits(CC_GPIO,CC_CSn)
#define CC_CSn_L		GPIO_ResetBits(CC_GPIO,CC_CSn)

#define CC_CE_H		GPIO_SetBits(CC_GPIO,CC_CE)
#define CC_CE_L		GPIO_ResetBits(CC_GPIO,CC_CE)

#define IRQ_IN		GPIO_ReadInputDataBit(CC_GPIO,CC_IRQ)




#define TX_ADR_WIDTH   5  				// 5�ֽڿ�ȵķ���/���յ�ַ
#define TX_PLOAD_WIDTH 32  				// ����ͨ����Ч���ݿ��

#define CH_NUM 11//ͨѶͨ������ 
#define DEFAULT_CH   10

//********************************************************************************************************************//
// SPI(SI24R1) commands
#define READ_REG1        0x00  // Define read command to register
#define WRITE_REG1       0x20  // Define write command to register
#define RD_RX_PLOAD     0x61  // Define RX payload register address
#define WR_TX_PLOAD     0xA0  // Define TX payload register address
#define FLUSH_TX        0xE1  // Define flush TX register command
#define FLUSH_RX        0xE2  // Define flush RX register command
#define REUSE_TX_PL     0xE3  // Define reuse TX payload register command
#define NOP             0xFF  // Define No Operation, might be used to read status register

//********************************************************************************************************************//
// SPI(SI24R1) registers(addresses)
#define CONFIG          0x00  // 'Config' register address
#define EN_AA           0x01  // 'Enable Auto Acknowledgment' register address
#define EN_RXADDR       0x02  // 'Enabled RX addresses' register address
#define SETUP_AW        0x03  // 'Setup address width' register address
#define SETUP_RETR      0x04  // 'Setup Auto. Retrans' register address
#define RF_CH           0x05  // 'RF channel' register address
#define RF_SETUP        0x06  // 'RF setup' register address
#define STATUS          0x07  // 'Status' register address
#define OBSERVE_TX      0x08  // 'Observe TX' register address
#define RSSI            0x09  // 'Received Signal Strength Indecator' register address
#define RX_ADDR_P0      0x0A  // 'RX address pipe0' register address
#define RX_ADDR_P1      0x0B  // 'RX address pipe1' register address
#define RX_ADDR_P2      0x0C  // 'RX address pipe2' register address
#define RX_ADDR_P3      0x0D  // 'RX address pipe3' register address
#define RX_ADDR_P4      0x0E  // 'RX address pipe4' register address
#define RX_ADDR_P5      0x0F  // 'RX address pipe5' register address
#define TX_ADDR         0x10  // 'TX address' register address
#define RX_PW_P0        0x11  // 'RX payload width, pipe0' register address
#define RX_PW_P1        0x12  // 'RX payload width, pipe1' register address
#define RX_PW_P2        0x13  // 'RX payload width, pipe2' register address
#define RX_PW_P3        0x14  // 'RX payload width, pipe3' register address
#define RX_PW_P4        0x15  // 'RX payload width, pipe4' register address
#define RX_PW_P5        0x16  // 'RX payload width, pipe5' register address
#define FIFO_STATUS     0x17  // 'FIFO Status Register' register address

//********************************************************************************************************************//
// STATUS Register 
#define RX_DR						0x40  /**/
#define TX_DS						0x20
#define MAX_RT					0x10

//********************************************************************************************************************//
//                                        FUNCTION's PROTOTYPES                                                       //
//********************************************************************************************************************//
//SI24R1 API Functions
void SI24R1_Init(void); //SI24R1 Pin Init
u8 SI24R1_Write_Reg(u8 reg, u8 value); 
u8 SI24R1_Write_Buf(u8 reg, const u8 *pBuf, u8 bytes);
u8 SI24R1_Read_Reg(u8 reg);
u8 SI24R1_Read_Buf(u8 reg, u8 *pBuf, u8 bytes);
void SI24R1_Standby_Mode(void);

void SI24R1_RX_Mode(uint8 ch);
void SI24R1_TX_Mode(uint8 ch);
u8 SI24R1_RxPacket(u8 *rxbuf);
u8 SI24R1_TxPacket(u8 *txbuf);

//********************************************************************************************************************//
#endif

