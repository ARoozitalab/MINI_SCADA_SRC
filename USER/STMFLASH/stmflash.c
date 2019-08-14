
/*********************************************************************************************************
*
* File                : stm_flash.c
* Version             : V1.0
* By                  : alireza roozitalab
* email               : alireza.roozitalab@gmail.com
* git user            : ARoozitalab
*                                                
*                                          All Rights Reserved
*
*********************************************************************************************************/

#include "stmflash.h"
#include "delay.h"
#include "stm32f10x_flash.h"



u16 STMFLASH_ReadHalfWord(u32 faddr)
{
	return *(vu16*)faddr; 
}
#if STM32_FLASH_WREN

void STMFLASH_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)   
{ 			 		 
	u16 i;
	for(i=0;i<NumToWrite;i++)
	{
		FLASH_ProgramHalfWord(WriteAddr,pBuffer[i]);
	    WriteAddr+=2;
	}  
} 
#if STM32_FLASH_SIZE<256
#define STM_SECTOR_SIZE 1024 
#else 
#define STM_SECTOR_SIZE	2048
#endif		 
u16 STMFLASH_BUF[STM_SECTOR_SIZE/2];

/*******************************************************************************
* Function Name  : STMFLASH_Write
* Description    : write 16 bit on stm32f internatl flash
* Input          :  WriteAddr ; write address , pBuffer = addres of flash ,NumToWrite : size of 
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)	
{
	u32 secpos;	   
	u16 secoff;	   
	u16 secremain; 
 	u16 i;    
	u32 offaddr;   
	if(WriteAddr<STM32_FLASH_BASE||(WriteAddr>=(STM32_FLASH_BASE+1024*STM32_FLASH_SIZE)))return;
	FLASH_Unlock();						
	offaddr=WriteAddr-STM32_FLASH_BASE;	
	secpos=offaddr/STM_SECTOR_SIZE;		
	secoff=(offaddr%STM_SECTOR_SIZE)/2;	
	secremain=STM_SECTOR_SIZE/2-secoff;	
	if(NumToWrite<=secremain)secremain=NumToWrite;
	while(1) 
	{	
		STMFLASH_Read(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);
		for(i=0;i<secremain;i++)
		{
			if(STMFLASH_BUF[secoff+i]!=0XFFFF)break;
		}
		if(i<secremain)
		{
			FLASH_ErasePage(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE);
			for(i=0;i<secremain;i++)
			{
				STMFLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			STMFLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);
		}else STMFLASH_Write_NoCheck(WriteAddr,pBuffer,secremain);
		if(NumToWrite==secremain)break;
		else
		{
			secpos++;				
			secoff=0;				
		   	pBuffer+=secremain;  	
			WriteAddr+=secremain;	
		   	NumToWrite-=secremain;	
			if(NumToWrite>(STM_SECTOR_SIZE/2))secremain=STM_SECTOR_SIZE/2;
			else secremain=NumToWrite;
		}	 
	};	
	FLASH_Lock();
}
#endif



/*******************************************************************************
* Function Name  : STMFLASH_Read
* Description    : read 16 bit from stm32f internatl flash
* Input          : ReadAddr ; read address , pBuffer = addres of flash ,NumToRead : size
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead)   	
{
	u16 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadHalfWord(ReadAddr);
		ReadAddr+=2;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Test_Write(u32 WriteAddr,u16 WriteData)   	
{
	STMFLASH_Write(WriteAddr,&WriteData,1);
}
















