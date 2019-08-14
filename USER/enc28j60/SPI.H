#ifndef __SPI_H
#define __SPI_H


//下面的定义3.50与3.22的库不一样
//----------------------------------------------
#define SPI_FLAG_RXNE           SPI_I2S_FLAG_RXNE
#define SPI_FLAG_TXE            SPI_I2S_FLAG_TXE
//#define SPI_FLAG_CRCERR                    ((u16)0x0010)
//#define SPI_FLAG_MODF                      ((u16)0x0020)
#define SPI_FLAG_OVR            SPI_I2S_FLAG_OVR
#define SPI_FLAG_BSY            SPI_I2S_FLAG_BSY
//----------------------------------------------
#define SPI_GetFlagStatus       SPI_I2S_GetFlagStatus
#define SPI_SendData            SPI_I2S_SendData
#define SPI_ReceiveData         SPI_I2S_ReceiveData


#define  SPInet_ReadWrite  SPI1_ReadWrite
#define  SPInet_Init   SPI1_Init

//SPI1初始化
void SPI1_Init(void);
//SPI1读写一字节数据
unsigned char SPI1_ReadWrite(unsigned char writedat);


//SPI2初始化
void SPI2_Init(void);
//SPI2读写一字节数据
unsigned char SPI2_ReadWrite(unsigned char writedat);

#endif
