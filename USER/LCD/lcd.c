
#include "lcd.h"
#include "stdlib.h"
#include "font.h" 
 
#include "delay.h"	   
//////////////////////////////////////////////////////////////////////////////////	 
//±¾³ÌÐòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßÐí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//ALIENTEKÕ½½¢STM32¿ª·¢°å
//2.4/2.8´ç/3.5´ç TFTÒº¾§Çý¶¯	  
//Ö§³ÖÇý¶¯ICÐÍºÅ°üÀ¨:ILI9341/ILI9325/RM68042/RM68021/ILI9320/ILI9328/LGDP4531/LGDP4535/SPFD5408/SSD1289/1505/B505/C505µÈ	    
//ÕýµãÔ­×Ó@ALIENTEK
//¼¼ÊõÂÛÌ³:www.openedv.com
//ÐÞ¸ÄÈÕÆÚ:2012/10/7
//°æ±¾£ºV2.2
//°æÈ¨ËùÓÐ£¬µÁ°æ±Ø¾¿¡£
//Copyright(C) ¹ãÖÝÊÐÐÇÒíµç×Ó¿Æ¼¼ÓÐÏÞ¹«Ë¾ 2009-2019
//All rights reserved	
//********************************************************************************
//V1.2ÐÞ¸ÄËµÃ÷
//Ö§³ÖÁËSPFD5408µÄÇý¶¯,ÁíÍâ°ÑÒº¾§IDÖ±½Ó´òÓ¡³ÉHEX¸ñÊ½.·½±ã²é¿´LCDÇý¶¯IC.
//V1.3
//¼ÓÈëÁË¿ìËÙIOµÄÖ§³Ö
//ÐÞ¸ÄÁË±³¹â¿ØÖÆµÄ¼«ÐÔ£¨ÊÊÓÃÓÚV1.8¼°ÒÔºóµÄ¿ª·¢°å°æ±¾£©
//¶ÔÓÚ1.8°æ±¾Ö®Ç°(²»°üÀ¨1.8)µÄÒº¾§Ä£¿é,ÇëÐÞ¸ÄLCD_Initº¯ÊýµÄLCD_LED=1;ÎªLCD_LED=1;
//V1.4
//ÐÞ¸ÄÁËLCD_ShowCharº¯Êý£¬Ê¹ÓÃ»­µã¹¦ÄÜ»­×Ö·û¡£
//¼ÓÈëÁËºáÊúÆÁÏÔÊ¾µÄÖ§³Ö
//V1.5 20110730
//1,ÐÞ¸ÄÁËB505Òº¾§¶ÁÑÕÉ«ÓÐÎóµÄbug.
//2,ÐÞ¸ÄÁË¿ìËÙIO¼°ºáÊúÆÁµÄÉèÖÃ·½Ê½.
//V1.6 20111116
//1,¼ÓÈë¶ÔLGDP4535Òº¾§µÄÇý¶¯Ö§³Ö
//V1.7 20120713
//1,Ôö¼ÓLCD_RD_DATAº¯Êý
//2,Ôö¼Ó¶ÔILI9341µÄÖ§³Ö
//3,Ôö¼ÓILI9325µÄ¶ÀÁ¢Çý¶¯´úÂë
//4,Ôö¼ÓLCD_Scan_Dirº¯Êý(É÷ÖØÊ¹ÓÃ)	  
//6,ÁíÍâÐÞ¸ÄÁË²¿·ÖÔ­À´µÄº¯Êý,ÒÔÊÊÓ¦9341µÄ²Ù×÷
//V1.8 20120905
//1,¼ÓÈëLCDÖØÒª²ÎÊýÉèÖÃ½á¹¹Ìålcddev
//2,¼ÓÈëLCD_Display_Dirº¯Êý,Ö§³ÖÔÚÏßºáÊúÆÁÇÐ»»
//V1.9 20120911
//1,ÐÂÔöRM68042Çý¶¯£¨ID:6804£©£¬µ«ÊÇ6804²»Ö§³ÖºáÆÁÏÔÊ¾£¡£¡Ô­Òò£º¸Ä±äÉ¨Ãè·½Ê½£¬
//µ¼ÖÂ6804×ø±êÉèÖÃÊ§Ð§£¬ÊÔ¹ýºÜ¶à·½·¨¶¼²»ÐÐ£¬ÔÝÊ±ÎÞ½â¡£
//V2.0 20120924
//ÔÚ²»Ó²¼þ¸´Î»µÄÇé¿öÏÂ,ILI9341µÄID¶ÁÈ¡»á±»Îó¶Á³É9300,ÐÞ¸ÄLCD_Init,½«ÎÞ·¨Ê¶±ð
//µÄÇé¿ö£¨¶Áµ½IDÎª9300/·Ç·¨ID£©,Ç¿ÖÆÖ¸¶¨Çý¶¯ICÎªILI9341£¬Ö´ÐÐ9341µÄ³õÊ¼»¯¡£
//V2.1 20120930
//ÐÞÕýILI9325¶ÁÑÕÉ«µÄbug¡£
//V2.2 20121007
//ÐÞÕýLCD_Scan_DirµÄbug¡£
//////////////////////////////////////////////////////////////////////////////////	 
				 
//LCDµÄ»­±ÊÑÕÉ«ºÍ±³¾°É«	   
u16 POINT_COLOR=0x0000;	//»­±ÊÑÕÉ«
u16 BACK_COLOR=0xFFFF;  //±³¾°É« 

//¹ÜÀíLCDÖØÒª²ÎÊý
//Ä¬ÈÏÎªÊúÆÁ
_lcd_dev lcddev;
	
		   
//Ð´¼Ä´æÆ÷º¯Êý
//regval:¼Ä´æÆ÷Öµ
void LCD_WR_REG(u16 regval)
{ 
	LCD->LCD_REG=regval;//Ð´ÈëÒªÐ´µÄ¼Ä´æÆ÷ÐòºÅ	 
}
//Ð´LCDÊý¾Ý
//data:ÒªÐ´ÈëµÄÖµ
void LCD_WR_DATA(u16 data)
{										    	   
	LCD->LCD_RAM=data;		 
}
//¶ÁLCDÊý¾Ý
//·µ»ØÖµ:¶Áµ½µÄÖµ
u16 LCD_RD_DATA(void)
{										    	   
	return LCD->LCD_RAM;		 
}					   
//Ð´¼Ä´æÆ÷
//LCD_Reg:¼Ä´æÆ÷µØÖ·
//LCD_RegValue:ÒªÐ´ÈëµÄÊý¾Ý
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{	
	LCD->LCD_REG = LCD_Reg;		//Ð´ÈëÒªÐ´µÄ¼Ä´æÆ÷ÐòºÅ	 
	LCD->LCD_RAM = LCD_RegValue;//Ð´ÈëÊý¾Ý	    		 
}	   
//¶Á¼Ä´æÆ÷
//LCD_Reg:¼Ä´æÆ÷µØÖ·
//·µ»ØÖµ:¶Áµ½µÄÊý¾Ý
u16 LCD_ReadReg(u8 LCD_Reg)
{										   
	LCD_WR_REG(LCD_Reg);		//Ð´ÈëÒª¶ÁµÄ¼Ä´æÆ÷ÐòºÅ
	delay_us(5);		  
	return LCD_RD_DATA();		//·µ»Ø¶Áµ½µÄÖµ
}   
//¿ªÊ¼Ð´GRAM
void LCD_WriteRAM_Prepare(void)
{
 	LCD->LCD_REG=lcddev.wramcmd;	  
}	 
//LCDÐ´GRAM
//RGB_Code:ÑÕÉ«Öµ
void LCD_WriteRAM(u16 RGB_Code)
{							    
	LCD->LCD_RAM = RGB_Code;//Ð´Ê®ÁùÎ»GRAM
}
//´ÓILI93xx¶Á³öµÄÊý¾ÝÎªGBR¸ñÊ½£¬¶øÎÒÃÇÐ´ÈëµÄÊ±ºòÎªRGB¸ñÊ½¡£
//Í¨¹ý¸Ãº¯Êý×ª»»
//c:GBR¸ñÊ½µÄÑÕÉ«Öµ
//·µ»ØÖµ£ºRGB¸ñÊ½µÄÑÕÉ«Öµ
u16 LCD_BGR2RGB(u16 c)
{
	u16  r,g,b,rgb;   
	b=(c>>0)&0x1f;
	g=(c>>5)&0x3f;
	r=(c>>11)&0x1f;	 
	rgb=(b<<11)+(g<<5)+(r<<0);		 
	return(rgb);
} 
//µ±mdk -O1Ê±¼äÓÅ»¯Ê±ÐèÒªÉèÖÃ
//ÑÓÊ±i
void opt_delay(u8 i)
{
	while(i--);
}
//¶ÁÈ¡¸öÄ³µãµÄÑÕÉ«Öµ	 
//x,y:×ø±ê
//·µ»ØÖµ:´ËµãµÄÑÕÉ«
u16 LCD_ReadPoint(u16 x,u16 y)
{
 	u16 r=0,g=0,b=0;
	if(x>=lcddev.width||y>=lcddev.height)return 0;	//³¬¹ýÁË·¶Î§,Ö±½Ó·µ»Ø		   
	LCD_SetCursor(x,y);	    
	if(lcddev.id==0X9341||lcddev.id==0X6804)LCD_WR_REG(0X2E);//9341/6804 ·¢ËÍ¶ÁGRAMÖ¸Áî
	else LCD_WR_REG(R34);      		 				//ÆäËûIC·¢ËÍ¶ÁGRAMÖ¸Áî
 	if(lcddev.id==0X9320)opt_delay(2);				//FOR 9320,ÑÓÊ±2us	    
	if(LCD->LCD_RAM)r=0;							//dummy Read	   
	opt_delay(2);	  
 	r=LCD->LCD_RAM;  		  						//Êµ¼Ê×ø±êÑÕÉ«
 	if(lcddev.id==0X9341)//9341Òª·Ö2´Î¶Á³ö
 	{
		opt_delay(2);	  
		b=LCD->LCD_RAM; 
		g=r&0XFF;//¶ÔÓÚ9341,µÚÒ»´Î¶ÁÈ¡µÄÊÇRGµÄÖµ,RÔÚÇ°,GÔÚºó,¸÷Õ¼8Î»
		g<<=8;
	}else if(lcddev.id==0X6804)r=LCD->LCD_RAM;//6804µÚ¶þ´Î¶ÁÈ¡µÄ²ÅÊÇÕæÊµÖµ
	if(lcddev.id==0X9325||lcddev.id==0X4535||lcddev.id==0X4531||lcddev.id==0X8989||lcddev.id==0XB505)return r;//Õâ¼¸ÖÖICÖ±½Ó·µ»ØÑÕÉ«Öµ
	else if(lcddev.id==0X9341)return (((r>>11)<<11)|((g>>10)<<5)|(b>>11));	//ILI9341ÐèÒª¹«Ê½×ª»»Ò»ÏÂ
	else return LCD_BGR2RGB(r);												//ÆäËûIC
}			 
//LCD¿ªÆôÏÔÊ¾
void LCD_DisplayOn(void)
{					   
	if(lcddev.id==0X9341||lcddev.id==0X6804)LCD_WR_REG(0X29);	//¿ªÆôÏÔÊ¾
	else LCD_WriteReg(R7,0x0173); 			//¿ªÆôÏÔÊ¾
}	 
//LCD¹Ø±ÕÏÔÊ¾
void LCD_DisplayOff(void)
{	   
	if(lcddev.id==0X9341||lcddev.id==0X6804)LCD_WR_REG(0X28);	//¹Ø±ÕÏÔÊ¾
	else LCD_WriteReg(R7,0x0);//¹Ø±ÕÏÔÊ¾ 
}   
//ÉèÖÃ¹â±êÎ»ÖÃ
//Xpos:ºá×ø±ê
//Ypos:×Ý×ø±ê
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{	 
 	if(lcddev.id==0X9341||lcddev.id==0X6804)
	{		    
		LCD_WR_REG(lcddev.setxcmd); 
		LCD_WR_DATA(Xpos>>8); 
		LCD_WR_DATA(Xpos&0XFF);	 
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA(Ypos>>8); 
		LCD_WR_DATA(Ypos&0XFF);
	}else
	{
		if(lcddev.dir==1)Xpos=lcddev.width-1-Xpos;//ºáÆÁÆäÊµ¾ÍÊÇµ÷×ªx,y×ø±ê
		LCD_WriteReg(lcddev.setxcmd, Xpos);
		LCD_WriteReg(lcddev.setycmd, Ypos);
	}	 
} 		 
//ÉèÖÃLCDµÄ×Ô¶¯É¨Ãè·½Ïò
//×¢Òâ:ÆäËûº¯Êý¿ÉÄÜ»áÊÜµ½´Ëº¯ÊýÉèÖÃµÄÓ°Ïì(ÓÈÆäÊÇ9341/6804ÕâÁ½¸öÆæÝâ),
//ËùÒÔ,Ò»°ãÉèÖÃÎªL2R_U2D¼´¿É,Èç¹ûÉèÖÃÎªÆäËûÉ¨Ãè·½Ê½,¿ÉÄÜµ¼ÖÂÏÔÊ¾²»Õý³£.
//dir:0~7,´ú±í8¸ö·½Ïò(¾ßÌå¶¨Òå¼ûlcd.h)
//9320/9325/9328/4531/4535/1505/b505/8989/5408/9341µÈICÒÑ¾­Êµ¼Ê²âÊÔ	   	   
void LCD_Scan_Dir(u8 dir)
{
	u16 regval=0;
	u8 dirreg=0;
	u16 temp;  
	if(lcddev.dir==1&&lcddev.id!=0X6804)//ºáÆÁÊ±£¬¶Ô6804²»¸Ä±äÉ¨Ãè·½Ïò£¡
	{			   
		switch(dir)//·½Ïò×ª»»
		{
			case 0:dir=6;break;
			case 1:dir=7;break;
			case 2:dir=4;break;
			case 3:dir=5;break;
			case 4:dir=1;break;
			case 5:dir=0;break;
			case 6:dir=3;break;
			case 7:dir=2;break;	     
		}
	}
	if(lcddev.id==0x9341||lcddev.id==0X6804)//9341/6804,ºÜÌØÊâ
	{
		switch(dir)
		{
			case L2R_U2D://´Ó×óµ½ÓÒ,´ÓÉÏµ½ÏÂ
				regval|=(0<<7)|(0<<6)|(0<<5); 
				break;
			case L2R_D2U://´Ó×óµ½ÓÒ,´ÓÏÂµ½ÉÏ
				regval|=(1<<7)|(0<<6)|(0<<5); 
				break;
			case R2L_U2D://´ÓÓÒµ½×ó,´ÓÉÏµ½ÏÂ
				regval|=(0<<7)|(1<<6)|(0<<5); 
				break;
			case R2L_D2U://´ÓÓÒµ½×ó,´ÓÏÂµ½ÉÏ
				regval|=(1<<7)|(1<<6)|(0<<5); 
				break;	 
			case U2D_L2R://´ÓÉÏµ½ÏÂ,´Ó×óµ½ÓÒ
				regval|=(0<<7)|(0<<6)|(1<<5); 
				break;
			case U2D_R2L://´ÓÉÏµ½ÏÂ,´ÓÓÒµ½×ó
				regval|=(0<<7)|(1<<6)|(1<<5); 
				break;
			case D2U_L2R://´ÓÏÂµ½ÉÏ,´Ó×óµ½ÓÒ
				regval|=(1<<7)|(0<<6)|(1<<5); 
				break;
			case D2U_R2L://´ÓÏÂµ½ÉÏ,´ÓÓÒµ½×ó
				regval|=(1<<7)|(1<<6)|(1<<5); 
				break;	 
		}
		dirreg=0X36;
 		regval|=0X08;//BGR   
		if(lcddev.id==0X6804)regval|=0x02;//6804µÄBIT6ºÍ9341µÄ·´ÁË	   
		LCD_WriteReg(dirreg,regval);
 		if(regval&0X20)
		{
			if(lcddev.width<lcddev.height)//½»»»X,Y
			{
				temp=lcddev.width;
				lcddev.width=lcddev.height;
				lcddev.height=temp;
 			}
		}else  
		{
			if(lcddev.width>lcddev.height)//½»»»X,Y
			{
				temp=lcddev.width;
				lcddev.width=lcddev.height;
				lcddev.height=temp;
 			}
		}  
		LCD_WR_REG(lcddev.setxcmd); 
		LCD_WR_DATA(0);LCD_WR_DATA(0);
		LCD_WR_DATA((lcddev.width-1)>>8);LCD_WR_DATA((lcddev.width-1)&0XFF);
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA(0);LCD_WR_DATA(0);
		LCD_WR_DATA((lcddev.height-1)>>8);LCD_WR_DATA((lcddev.height-1)&0XFF);  
  	}else 
	{
		switch(dir)
		{
			case L2R_U2D://´Ó×óµ½ÓÒ,´ÓÉÏµ½ÏÂ
				regval|=(1<<5)|(1<<4)|(0<<3); 
				break;
			case L2R_D2U://´Ó×óµ½ÓÒ,´ÓÏÂµ½ÉÏ
				regval|=(0<<5)|(1<<4)|(0<<3); 
				break;
			case R2L_U2D://´ÓÓÒµ½×ó,´ÓÉÏµ½ÏÂ
				regval|=(1<<5)|(0<<4)|(0<<3);
				break;
			case R2L_D2U://´ÓÓÒµ½×ó,´ÓÏÂµ½ÉÏ
				regval|=(0<<5)|(0<<4)|(0<<3); 
				break;	 
			case U2D_L2R://´ÓÉÏµ½ÏÂ,´Ó×óµ½ÓÒ
				regval|=(1<<5)|(1<<4)|(1<<3); 
				break;
			case U2D_R2L://´ÓÉÏµ½ÏÂ,´ÓÓÒµ½×ó
				regval|=(1<<5)|(0<<4)|(1<<3); 
				break;
			case D2U_L2R://´ÓÏÂµ½ÉÏ,´Ó×óµ½ÓÒ
				regval|=(0<<5)|(1<<4)|(1<<3); 
				break;
			case D2U_R2L://´ÓÏÂµ½ÉÏ,´ÓÓÒµ½×ó
				regval|=(0<<5)|(0<<4)|(1<<3); 
				break;	 
		}
		if(lcddev.id==0x8989)//8989 IC
		{
			dirreg=0X11;
			regval|=0X6040;	//65K   
	 	}else//ÆäËûÇý¶¯IC		  
		{
			dirreg=0X03;
			regval|=1<<12;  
		}
		LCD_WriteReg(dirreg,regval);
	}
}   
//»­µã
//x,y:×ø±ê
//POINT_COLOR:´ËµãµÄÑÕÉ«
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);		//ÉèÖÃ¹â±êÎ»ÖÃ 
	LCD_WriteRAM_Prepare();	//¿ªÊ¼Ð´ÈëGRAM
	LCD->LCD_RAM=POINT_COLOR; 
}
//¿ìËÙ»­µã
//x,y:×ø±ê
//color:ÑÕÉ«
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color)
{	   
	if(lcddev.id==0X9341||lcddev.id==0X6804)
	{		    
		LCD_WR_REG(lcddev.setxcmd); 
		LCD_WR_DATA(x>>8); 
		LCD_WR_DATA(x&0XFF);	 
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA(y>>8); 
		LCD_WR_DATA(y&0XFF);
	}else
	{
 		if(lcddev.dir==1)x=lcddev.width-1-x;//ºáÆÁÆäÊµ¾ÍÊÇµ÷×ªx,y×ø±ê
		LCD_WriteReg(lcddev.setxcmd,x);
		LCD_WriteReg(lcddev.setycmd,y);
	}			 
	LCD->LCD_REG=lcddev.wramcmd; 
	LCD->LCD_RAM=color; 
}	 


//ÉèÖÃLCDÏÔÊ¾·½Ïò£¨6804²»Ö§³ÖºáÆÁÏÔÊ¾£©
//dir:0,ÊúÆÁ£»1,ºáÆÁ
void LCD_Display_Dir(u8 dir)
{
	if(dir==0)//ÊúÆÁ
	{
		lcddev.dir=0;//ÊúÆÁ
		lcddev.width=240;
		lcddev.height=320;
		if(lcddev.id==0X9341||lcddev.id==0X6804)
		{
			lcddev.wramcmd=0X2C;
	 		lcddev.setxcmd=0X2A;
			lcddev.setycmd=0X2B;  	 
			if(lcddev.id==0X6804)
			{
				lcddev.width=320;
				lcddev.height=480;
			}
		}else if(lcddev.id==0X8989)
		{
			lcddev.wramcmd=R34;
	 		lcddev.setxcmd=0X4E;
			lcddev.setycmd=0X4F;  
		}else
		{
			lcddev.wramcmd=R34;
	 		lcddev.setxcmd=R32;
			lcddev.setycmd=R33;  
		}
	}else if(lcddev.id!=0X6804)//6804²»Ö§³ÖºáÆÁÏÔÊ¾	
	{	  
		lcddev.dir=1;//ºáÆÁ
		lcddev.width=320;
		lcddev.height=240;
		if(lcddev.id==0X9341)
		{
			lcddev.wramcmd=0X2C;
	 		lcddev.setxcmd=0X2A;
			lcddev.setycmd=0X2B;	 
		}else if(lcddev.id==0X8989)
		{
			lcddev.wramcmd=R34;
	 		lcddev.setxcmd=0X4F;
			lcddev.setycmd=0X4E;  
		}else
		{
			lcddev.wramcmd=R34;
	 		lcddev.setxcmd=R33;
			lcddev.setycmd=R32;  
		}
	} 
	LCD_Scan_Dir(DFT_SCAN_DIR);	//Ä¬ÈÏÉ¨Ãè·½Ïò
}	 
//³õÊ¼»¯lcd
//¸Ã³õÊ¼»¯º¯Êý¿ÉÒÔ³õÊ¼»¯¸÷ÖÖILI93XXÒº¾§,µ«ÊÇÆäËûº¯ÊýÊÇ»ùÓÚILI9320µÄ!!!
//ÔÚÆäËûÐÍºÅµÄÇý¶¯Ð¾Æ¬ÉÏÃ»ÓÐ²âÊÔ! 
void LCD_Init(void)
{ 										  
		GPIO_InitTypeDef GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef  readWriteTiming; 
	FSMC_NORSRAMTimingInitTypeDef  writeTiming;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);	//Ê¹ÄÜFSMCÊ±ÖÓ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOG|RCC_APB2Periph_AFIO,ENABLE);//Ê¹ÄÜPORTB,D,E,GÒÔ¼°AFIO¸´ÓÃ¹¦ÄÜÊ±ÖÓ

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;             
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
   PDout(2)=0;

   
    //PORTD reuse push-pull output  
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_14|GPIO_Pin_15;             //   //PORTD?¡ä¨®?¨ª?¨ª¨¬¨º?3?  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;        //Multiplexing push-pull output  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure); 
   //PORTE?¡ä¨®?¨ª?¨ª¨¬¨º?3?  
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;             //   //PORTD?¡ä¨®?¨ª?¨ª¨¬¨º?3?  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;        //Multiplexing push-pull output 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure); 
 
	readWriteTiming.FSMC_AddressSetupTime = 0x01;	 //µØÖ·½¨Á¢Ê±¼ä£¨ADDSET£©Îª2¸öHCLK 1/36M=27ns
    readWriteTiming.FSMC_AddressHoldTime = 0x00;	 //µØÖ·±£³ÖÊ±¼ä£¨ADDHLD£©Ä£Ê½AÎ´ÓÃµ½	
    readWriteTiming.FSMC_DataSetupTime = 0x0f;		 // Êý¾Ý±£´æÊ±¼äÎª16¸öHCLK,ÒòÎªÒº¾§Çý¶¯ICµÄ¶ÁÊý¾ÝµÄÊ±ºò£¬ËÙ¶È²»ÄÜÌ«¿ì£¬ÓÈÆä¶Ô1289Õâ¸öIC¡£
    readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
    readWriteTiming.FSMC_CLKDivision = 0x00;
    readWriteTiming.FSMC_DataLatency = 0x00;
    readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //Ä£Ê½A 
    

	writeTiming.FSMC_AddressSetupTime = 0x00;	 //µØÖ·½¨Á¢Ê±¼ä£¨ADDSET£©Îª1¸öHCLK  
    writeTiming.FSMC_AddressHoldTime = 0x00;	 //µØÖ·±£³ÖÊ±¼ä£¨A		
    writeTiming.FSMC_DataSetupTime = 0x03;		 ////Êý¾Ý±£´æÊ±¼äÎª4¸öHCLK	
    writeTiming.FSMC_BusTurnAroundDuration = 0x00;
    writeTiming.FSMC_CLKDivision = 0x00;
    writeTiming.FSMC_DataLatency = 0x00;
    writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //Ä£Ê½A 

 
    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;//  ÕâÀïÎÒÃÇÊ¹ÓÃNE4 £¬Ò²¾Í¶ÔÓ¦BTCR[6],[7]¡£
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // ²»¸´ÓÃÊý¾ÝµØÖ·
    FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//´æ´¢Æ÷Êý¾Ý¿í¶ÈÎª16bit   
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable; 
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//  ´æ´¢Æ÷Ð´Ê¹ÄÜ
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; // ¶ÁÐ´Ê¹ÓÃ²»Í¬µÄÊ±Ðò
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming; //¶ÁÐ´Ê±Ðò
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming;  //Ð´Ê±Ðò

    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //³õÊ¼»¯FSMCÅäÖÃ

   	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  // Ê¹ÄÜBANK1 
			 
 	delay_ms(50); // delay 50 ms 
 	LCD_WriteReg(0x0000,0x0001);
	delay_ms(50); // delay 50 ms 
  	lcddev.id = LCD_ReadReg(0x0000);   
  	if(lcddev.id<0XFF||lcddev.id==0XFFFF||lcddev.id==0X9300)//¶Áµ½ID²»ÕýÈ·,ÐÂÔölcddev.id==0X9300ÅÐ¶Ï£¬ÒòÎª9341ÔÚÎ´±»¸´Î»µÄÇé¿öÏÂ»á±»¶Á³É9300
	{	
 		//³¢ÊÔ9341 IDµÄ¶ÁÈ¡		
		LCD_WR_REG(0XD3);				   
		LCD_RD_DATA(); 				//dummy read 	
 		LCD_RD_DATA();   	    	//¶Áµ½0X00
  		lcddev.id=LCD_RD_DATA();   	//¶ÁÈ¡93								   
 		lcddev.id<<=8;
		lcddev.id|=LCD_RD_DATA();  	//¶ÁÈ¡41 	   			   
 		if(lcddev.id!=0X9341)		//·Ç9341,³¢ÊÔÊÇ²»ÊÇ6804
		{	
 			LCD_WR_REG(0XBF);				   
			LCD_RD_DATA(); 			//dummy read 	 
	 		LCD_RD_DATA();   	    //¶Á»Ø0X01			   
	 		LCD_RD_DATA(); 			//¶Á»Ø0XD0 			  	
	  		lcddev.id=LCD_RD_DATA();//ÕâÀï¶Á»Ø0X68 
			lcddev.id<<=8;
	  		lcddev.id|=LCD_RD_DATA();//ÕâÀï¶Á»Ø0X04	   	  
 		} 
		if(lcddev.id!=0X9341&&lcddev.id!=0X6804)lcddev.id=0x9341;//ÐÂÔö£¬ÓÃÓÚÊ¶±ð9341 	     
	}

	if(lcddev.id==0X9341)	//9341³õÊ¼»¯
	{	 
		LCD_WR_REG(0xCF);  
		LCD_WR_DATA(0x00); 
		LCD_WR_DATA(0xC1); 
		LCD_WR_DATA(0X30); 
		LCD_WR_REG(0xED);  
		LCD_WR_DATA(0x64); 
		LCD_WR_DATA(0x03); 
		LCD_WR_DATA(0X12); 
		LCD_WR_DATA(0X81); 
		LCD_WR_REG(0xE8);  
		LCD_WR_DATA(0x85); 
		LCD_WR_DATA(0x10); 
		LCD_WR_DATA(0x7A); 
		LCD_WR_REG(0xCB);  
		LCD_WR_DATA(0x39); 
		LCD_WR_DATA(0x2C); 
		LCD_WR_DATA(0x00); 
		LCD_WR_DATA(0x34); 
		LCD_WR_DATA(0x02); 
		LCD_WR_REG(0xF7);  
		LCD_WR_DATA(0x20); 
		LCD_WR_REG(0xEA);  
		LCD_WR_DATA(0x00); 
		LCD_WR_DATA(0x00); 
		LCD_WR_REG(0xC0);    //Power control 
		LCD_WR_DATA(0x1B);   //VRH[5:0] 
		LCD_WR_REG(0xC1);    //Power control 
		LCD_WR_DATA(0x01);   //SAP[2:0];BT[3:0] 
		LCD_WR_REG(0xC5);    //VCM control 
		LCD_WR_DATA(0x30); 	 //3F
		LCD_WR_DATA(0x30); 	 //3C
		LCD_WR_REG(0xC7);    //VCM control2 
		LCD_WR_DATA(0XB7); 
		LCD_WR_REG(0x36);    // Memory Access Control 
		LCD_WR_DATA(0x48); 
		LCD_WR_REG(0x3A);   
		LCD_WR_DATA(0x55); 
		LCD_WR_REG(0xB1);   
		LCD_WR_DATA(0x00);   
		LCD_WR_DATA(0x1A); 
		LCD_WR_REG(0xB6);    // Display Function Control 
		LCD_WR_DATA(0x0A); 
		LCD_WR_DATA(0xA2); 
		LCD_WR_REG(0xF2);    // 3Gamma Function Disable 
		LCD_WR_DATA(0x00); 
		LCD_WR_REG(0x26);    //Gamma curve selected 
		LCD_WR_DATA(0x01); 
		LCD_WR_REG(0xE0);    //Set Gamma 
		LCD_WR_DATA(0x0F); 
		LCD_WR_DATA(0x2A); 
		LCD_WR_DATA(0x28); 
		LCD_WR_DATA(0x08); 
		LCD_WR_DATA(0x0E); 
		LCD_WR_DATA(0x08); 
		LCD_WR_DATA(0x54); 
		LCD_WR_DATA(0XA9); 
		LCD_WR_DATA(0x43); 
		LCD_WR_DATA(0x0A); 
		LCD_WR_DATA(0x0F); 
		LCD_WR_DATA(0x00); 
		LCD_WR_DATA(0x00); 
		LCD_WR_DATA(0x00); 
		LCD_WR_DATA(0x00); 		 
		LCD_WR_REG(0XE1);    //Set Gamma 
		LCD_WR_DATA(0x00); 
		LCD_WR_DATA(0x15); 
		LCD_WR_DATA(0x17); 
		LCD_WR_DATA(0x07); 
		LCD_WR_DATA(0x11); 
		LCD_WR_DATA(0x06); 
		LCD_WR_DATA(0x2B); 
		LCD_WR_DATA(0x56); 
		LCD_WR_DATA(0x3C); 
		LCD_WR_DATA(0x05); 
		LCD_WR_DATA(0x10); 
		LCD_WR_DATA(0x0F); 
		LCD_WR_DATA(0x3F); 
		LCD_WR_DATA(0x3F); 
		LCD_WR_DATA(0x0F); 
		LCD_WR_REG(0x2B); 
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x01);
		LCD_WR_DATA(0x3f);
		LCD_WR_REG(0x2A); 
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xef);	 
		LCD_WR_REG(0x11); //Exit Sleep
		delay_ms(120);
		LCD_WR_REG(0x29); //display on	
	}else if(lcddev.id==0x6804) //6804³õÊ¼»¯
	{
		LCD_WR_REG(0X11);
		delay_ms(20);
		LCD_WR_REG(0XD0);//VCI1  VCL  VGH  VGL DDVDH VREG1OUT power amplitude setting
		LCD_WR_DATA(0X07); 
		LCD_WR_DATA(0X42); 
		LCD_WR_DATA(0X1D); 
		LCD_WR_REG(0XD1);//VCOMH VCOM_AC amplitude setting
		LCD_WR_DATA(0X00);
		LCD_WR_DATA(0X1a);
		LCD_WR_DATA(0X09); 
		LCD_WR_REG(0XD2);//Operational Amplifier Circuit Constant Current Adjust , charge pump frequency setting
		LCD_WR_DATA(0X01);
		LCD_WR_DATA(0X22);
		LCD_WR_REG(0XC0);//REV SM GS 
		LCD_WR_DATA(0X10);
		LCD_WR_DATA(0X3B);
		LCD_WR_DATA(0X00);
		LCD_WR_DATA(0X02);
		LCD_WR_DATA(0X11);
		
		LCD_WR_REG(0XC5);// Frame rate setting = 72HZ  when setting 0x03
		LCD_WR_DATA(0X03);
		
		LCD_WR_REG(0XC8);//Gamma setting
		LCD_WR_DATA(0X00);
		LCD_WR_DATA(0X25);
		LCD_WR_DATA(0X21);
		LCD_WR_DATA(0X05);
		LCD_WR_DATA(0X00);
		LCD_WR_DATA(0X0a);
		LCD_WR_DATA(0X65);
		LCD_WR_DATA(0X25);
		LCD_WR_DATA(0X77);
		LCD_WR_DATA(0X50);
		LCD_WR_DATA(0X0f);
		LCD_WR_DATA(0X00);	  
						  
   		LCD_WR_REG(0XF8);
		LCD_WR_DATA(0X01);	  

 		LCD_WR_REG(0XFE);
 		LCD_WR_DATA(0X00);
 		LCD_WR_DATA(0X02);
		
		LCD_WR_REG(0X20);//Exit invert mode

		LCD_WR_REG(0X36);
		LCD_WR_DATA(0X08);//Ô­À´ÊÇa
		
		LCD_WR_REG(0X3A);
		LCD_WR_DATA(0X55);//16Î»Ä£Ê½	  
		LCD_WR_REG(0X2B);
		LCD_WR_DATA(0X00);
		LCD_WR_DATA(0X00);
		LCD_WR_DATA(0X01);
		LCD_WR_DATA(0X3F);
		
		LCD_WR_REG(0X2A);
		LCD_WR_DATA(0X00);
		LCD_WR_DATA(0X00);
		LCD_WR_DATA(0X01);
		LCD_WR_DATA(0XDF);
		delay_ms(120);
		LCD_WR_REG(0X29); 	 
 	}else if(lcddev.id==0x9325)//9325
	{
		LCD_WriteReg(0x00E5,0x78F0); 
		LCD_WriteReg(0x0001,0x0100); 
		LCD_WriteReg(0x0002,0x0700); 
		LCD_WriteReg(0x0003,0x1030); 
		LCD_WriteReg(0x0004,0x0000); 
		LCD_WriteReg(0x0008,0x0202);  
		LCD_WriteReg(0x0009,0x0000);
		LCD_WriteReg(0x000A,0x0000); 
		LCD_WriteReg(0x000C,0x0000); 
		LCD_WriteReg(0x000D,0x0000);
		LCD_WriteReg(0x000F,0x0000);
		//power on sequence VGHVGL
		LCD_WriteReg(0x0010,0x0000);   
		LCD_WriteReg(0x0011,0x0007);  
		LCD_WriteReg(0x0012,0x0000);  
		LCD_WriteReg(0x0013,0x0000); 
		LCD_WriteReg(0x0007,0x0000); 
		//vgh 
		LCD_WriteReg(0x0010,0x1690);   
		LCD_WriteReg(0x0011,0x0227);
		//delayms(100);
		//vregiout 
		LCD_WriteReg(0x0012,0x009D); //0x001b
		//delayms(100); 
		//vom amplitude
		LCD_WriteReg(0x0013,0x1900);
		//delayms(100); 
		//vom H
		LCD_WriteReg(0x0029,0x0025); 
		LCD_WriteReg(0x002B,0x000D); 
		//gamma
		LCD_WriteReg(0x0030,0x0007);
		LCD_WriteReg(0x0031,0x0303);
		LCD_WriteReg(0x0032,0x0003);// 0006
		LCD_WriteReg(0x0035,0x0206);
		LCD_WriteReg(0x0036,0x0008);
		LCD_WriteReg(0x0037,0x0406); 
		LCD_WriteReg(0x0038,0x0304);//0200
		LCD_WriteReg(0x0039,0x0007); 
		LCD_WriteReg(0x003C,0x0602);// 0504
		LCD_WriteReg(0x003D,0x0008); 
		//ram
		LCD_WriteReg(0x0050,0x0000); 
		LCD_WriteReg(0x0051,0x00EF);
		LCD_WriteReg(0x0052,0x0000); 
		LCD_WriteReg(0x0053,0x013F);  
		LCD_WriteReg(0x0060,0xA700); 
		LCD_WriteReg(0x0061,0x0001); 
		LCD_WriteReg(0x006A,0x0000); 
		//
		LCD_WriteReg(0x0080,0x0000); 
		LCD_WriteReg(0x0081,0x0000); 
		LCD_WriteReg(0x0082,0x0000); 
		LCD_WriteReg(0x0083,0x0000); 
		LCD_WriteReg(0x0084,0x0000); 
		LCD_WriteReg(0x0085,0x0000); 
		//
		LCD_WriteReg(0x0090,0x0010); 
		LCD_WriteReg(0x0092,0x0600); 
		
		LCD_WriteReg(0x0007,0x0133);
		LCD_WriteReg(0x00,0x0022);//
	}else if(lcddev.id==0x9328)//ILI9328   OK  
	{
  		LCD_WriteReg(0x00EC,0x108F);// internal timeing      
 		LCD_WriteReg(0x00EF,0x1234);// ADD        
		//LCD_WriteReg(0x00e7,0x0010);      
        //LCD_WriteReg(0x0000,0x0001);//¿ªÆôÄÚ²¿Ê±ÖÓ
        LCD_WriteReg(0x0001,0x0100);     
        LCD_WriteReg(0x0002,0x0700);//µçÔ´¿ªÆô                    
		//LCD_WriteReg(0x0003,(1<<3)|(1<<4) ); 	//65K  RGB
		//DRIVE TABLE(¼Ä´æÆ÷ 03H)
		//BIT3=AM BIT4:5=ID0:1
		//AM ID0 ID1   FUNCATION
		// 0  0   0	   R->L D->U
		// 1  0   0	   D->U	R->L
		// 0  1   0	   L->R D->U
		// 1  1   0    D->U	L->R
		// 0  0   1	   R->L U->D
		// 1  0   1    U->D	R->L
		// 0  1   1    L->R U->D Õý³£¾ÍÓÃÕâ¸ö.
		// 1  1   1	   U->D	L->R
        LCD_WriteReg(0x0003,(1<<12)|(3<<4)|(0<<3) );//65K    
        LCD_WriteReg(0x0004,0x0000);                                   
        LCD_WriteReg(0x0008,0x0202);	           
        LCD_WriteReg(0x0009,0x0000);         
        LCD_WriteReg(0x000a,0x0000);//display setting         
        LCD_WriteReg(0x000c,0x0001);//display setting          
        LCD_WriteReg(0x000d,0x0000);//0f3c          
        LCD_WriteReg(0x000f,0x0000);
		//µçÔ´ÅäÖÃ
        LCD_WriteReg(0x0010,0x0000);   
        LCD_WriteReg(0x0011,0x0007);
        LCD_WriteReg(0x0012,0x0000);                                                                 
        LCD_WriteReg(0x0013,0x0000);                 
     	LCD_WriteReg(0x0007,0x0001);                 
       	delay_ms(50); 
        LCD_WriteReg(0x0010,0x1490);   
        LCD_WriteReg(0x0011,0x0227);
        delay_ms(50); 
        LCD_WriteReg(0x0012,0x008A);                  
        delay_ms(50); 
        LCD_WriteReg(0x0013,0x1a00);   
        LCD_WriteReg(0x0029,0x0006);
        LCD_WriteReg(0x002b,0x000d);
        delay_ms(50); 
        LCD_WriteReg(0x0020,0x0000);                                                            
        LCD_WriteReg(0x0021,0x0000);           
		delay_ms(50); 
		//Ù¤ÂíÐ£Õý
        LCD_WriteReg(0x0030,0x0000); 
        LCD_WriteReg(0x0031,0x0604);   
        LCD_WriteReg(0x0032,0x0305);
        LCD_WriteReg(0x0035,0x0000);
        LCD_WriteReg(0x0036,0x0C09); 
        LCD_WriteReg(0x0037,0x0204);
        LCD_WriteReg(0x0038,0x0301);        
        LCD_WriteReg(0x0039,0x0707);     
        LCD_WriteReg(0x003c,0x0000);
        LCD_WriteReg(0x003d,0x0a0a);
        delay_ms(50); 
        LCD_WriteReg(0x0050,0x0000); //Ë®Æ½GRAMÆðÊ¼Î»ÖÃ 
        LCD_WriteReg(0x0051,0x00ef); //Ë®Æ½GRAMÖÕÖ¹Î»ÖÃ                    
        LCD_WriteReg(0x0052,0x0000); //´¹Ö±GRAMÆðÊ¼Î»ÖÃ                    
        LCD_WriteReg(0x0053,0x013f); //´¹Ö±GRAMÖÕÖ¹Î»ÖÃ  
 
         LCD_WriteReg(0x0060,0xa700);        
        LCD_WriteReg(0x0061,0x0001); 
        LCD_WriteReg(0x006a,0x0000);
        LCD_WriteReg(0x0080,0x0000);
        LCD_WriteReg(0x0081,0x0000);
        LCD_WriteReg(0x0082,0x0000);
        LCD_WriteReg(0x0083,0x0000);
        LCD_WriteReg(0x0084,0x0000);
        LCD_WriteReg(0x0085,0x0000);
      
        LCD_WriteReg(0x0090,0x0010);     
        LCD_WriteReg(0x0092,0x0600);  
        //¿ªÆôÏÔÊ¾ÉèÖÃ    
        LCD_WriteReg(0x0007,0x0133); 
	}else if(lcddev.id==0x9320)//²âÊÔOK.
	{
		LCD_WriteReg(0x00,0x0000);
		LCD_WriteReg(0x01,0x0100);	//Driver Output Contral.
		LCD_WriteReg(0x02,0x0700);	//LCD Driver Waveform Contral.
		LCD_WriteReg(0x03,0x1030);//Entry Mode Set.
		//LCD_WriteReg(0x03,0x1018);	//Entry Mode Set.
	
		LCD_WriteReg(0x04,0x0000);	//Scalling Contral.
		LCD_WriteReg(0x08,0x0202);	//Display Contral 2.(0x0207)
		LCD_WriteReg(0x09,0x0000);	//Display Contral 3.(0x0000)
		LCD_WriteReg(0x0a,0x0000);	//Frame Cycle Contal.(0x0000)
		LCD_WriteReg(0x0c,(1<<0));	//Extern Display Interface Contral 1.(0x0000)
		LCD_WriteReg(0x0d,0x0000);	//Frame Maker Position.
		LCD_WriteReg(0x0f,0x0000);	//Extern Display Interface Contral 2.	    
		delay_ms(50); 
		LCD_WriteReg(0x07,0x0101);	//Display Contral.
		delay_ms(50); 								  
		LCD_WriteReg(0x10,(1<<12)|(0<<8)|(1<<7)|(1<<6)|(0<<4));	//Power Control 1.(0x16b0)
		LCD_WriteReg(0x11,0x0007);								//Power Control 2.(0x0001)
		LCD_WriteReg(0x12,(1<<8)|(1<<4)|(0<<0));				//Power Control 3.(0x0138)
		LCD_WriteReg(0x13,0x0b00);								//Power Control 4.
		LCD_WriteReg(0x29,0x0000);								//Power Control 7.
	
		LCD_WriteReg(0x2b,(1<<14)|(1<<4));	    
		LCD_WriteReg(0x50,0);	//Set X Star
		//Ë®Æ½GRAMÖÕÖ¹Î»ÖÃSet X End.
		LCD_WriteReg(0x51,239);	//Set Y Star
		LCD_WriteReg(0x52,0);	//Set Y End.t.
		LCD_WriteReg(0x53,319);	//
	
		LCD_WriteReg(0x60,0x2700);	//Driver Output Control.
		LCD_WriteReg(0x61,0x0001);	//Driver Output Control.
		LCD_WriteReg(0x6a,0x0000);	//Vertical Srcoll Control.
	
		LCD_WriteReg(0x80,0x0000);	//Display Position? Partial Display 1.
		LCD_WriteReg(0x81,0x0000);	//RAM Address Start? Partial Display 1.
		LCD_WriteReg(0x82,0x0000);	//RAM Address End-Partial Display 1.
		LCD_WriteReg(0x83,0x0000);	//Displsy Position? Partial Display 2.
		LCD_WriteReg(0x84,0x0000);	//RAM Address Start? Partial Display 2.
		LCD_WriteReg(0x85,0x0000);	//RAM Address End? Partial Display 2.
	
		LCD_WriteReg(0x90,(0<<7)|(16<<0));	//Frame Cycle Contral.(0x0013)
		LCD_WriteReg(0x92,0x0000);	//Panel Interface Contral 2.(0x0000)
		LCD_WriteReg(0x93,0x0001);	//Panel Interface Contral 3.
		LCD_WriteReg(0x95,0x0110);	//Frame Cycle Contral.(0x0110)
		LCD_WriteReg(0x97,(0<<8));	//
		LCD_WriteReg(0x98,0x0000);	//Frame Cycle Contral.	   
		LCD_WriteReg(0x07,0x0173);	//(0x0173)
	}else if(lcddev.id==0X9331)//OK |/|/|			 
	{
		LCD_WriteReg(0x00E7, 0x1014);
		LCD_WriteReg(0x0001, 0x0100); // set SS and SM bit
		LCD_WriteReg(0x0002, 0x0200); // set 1 line inversion
        LCD_WriteReg(0x0003,(1<<12)|(3<<4)|(1<<3));//65K    
		//LCD_WriteReg(0x0003, 0x1030); // set GRAM write direction and BGR=1.
		LCD_WriteReg(0x0008, 0x0202); // set the back porch and front porch
		LCD_WriteReg(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0]
		LCD_WriteReg(0x000A, 0x0000); // FMARK function
		LCD_WriteReg(0x000C, 0x0000); // RGB interface setting
		LCD_WriteReg(0x000D, 0x0000); // Frame marker Position
		LCD_WriteReg(0x000F, 0x0000); // RGB interface polarity
		//*************Power On sequence ****************//
		LCD_WriteReg(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
		LCD_WriteReg(0x0011, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
		LCD_WriteReg(0x0012, 0x0000); // VREG1OUT voltage
		LCD_WriteReg(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
		delay_ms(200); // Dis-charge capacitor power voltage
		LCD_WriteReg(0x0010, 0x1690); // SAP, BT[3:0], AP, DSTB, SLP, STB
		LCD_WriteReg(0x0011, 0x0227); // DC1[2:0], DC0[2:0], VC[2:0]
		delay_ms(50); // Delay 50ms
		LCD_WriteReg(0x0012, 0x000C); // Internal reference voltage= Vci;
		delay_ms(50); // Delay 50ms
		LCD_WriteReg(0x0013, 0x0800); // Set VDV[4:0] for VCOM amplitude
		LCD_WriteReg(0x0029, 0x0011); // Set VCM[5:0] for VCOMH
		LCD_WriteReg(0x002B, 0x000B); // Set Frame Rate
		delay_ms(50); // Delay 50ms
		LCD_WriteReg(0x0020, 0x0000); // GRAM horizontal Address
		LCD_WriteReg(0x0021, 0x013f); // GRAM Vertical Address
		// ----------- Adjust the Gamma Curve ----------//
		LCD_WriteReg(0x0030, 0x0000);
		LCD_WriteReg(0x0031, 0x0106);
		LCD_WriteReg(0x0032, 0x0000);
		LCD_WriteReg(0x0035, 0x0204);
		LCD_WriteReg(0x0036, 0x160A);
		LCD_WriteReg(0x0037, 0x0707);
		LCD_WriteReg(0x0038, 0x0106);
		LCD_WriteReg(0x0039, 0x0707);
		LCD_WriteReg(0x003C, 0x0402);
		LCD_WriteReg(0x003D, 0x0C0F);
		//------------------ Set GRAM area ---------------//
		LCD_WriteReg(0x0050, 0x0000); // Horizontal GRAM Start Address
		LCD_WriteReg(0x0051, 0x00EF); // Horizontal GRAM End Address
		LCD_WriteReg(0x0052, 0x0000); // Vertical GRAM Start Address
		LCD_WriteReg(0x0053, 0x013F); // Vertical GRAM Start Address
		LCD_WriteReg(0x0060, 0x2700); // Gate Scan Line
		LCD_WriteReg(0x0061, 0x0001); // NDL,VLE, REV 
		LCD_WriteReg(0x006A, 0x0000); // set scrolling line
		//-------------- Partial Display Control ---------//
		LCD_WriteReg(0x0080, 0x0000);
		LCD_WriteReg(0x0081, 0x0000);
		LCD_WriteReg(0x0082, 0x0000);
		LCD_WriteReg(0x0083, 0x0000);
		LCD_WriteReg(0x0084, 0x0000);
		LCD_WriteReg(0x0085, 0x0000);
		//-------------- Panel Control -------------------//
		LCD_WriteReg(0x0090, 0x0010);
		LCD_WriteReg(0x0092, 0x0600);
		LCD_WriteReg(0x0007, 0x0133); // 262K color and display ON
	}else if(lcddev.id==0x5408)
	{
		LCD_WriteReg(0x01,0x0100);								  
		LCD_WriteReg(0x02,0x0700);//LCD Driving Waveform Contral 
		LCD_WriteReg(0x03,0x1030);//Entry ModeÉèÖÃ 	   
		//Ö¸Õë´Ó×óÖÁÓÒ×ÔÉÏ¶øÏÂµÄ×Ô¶¯ÔöÄ£Ê½
		//Normal Mode(Window Mode disable)
		//RGB¸ñÊ½
		//16Î»Êý¾Ý2´Î´«ÊäµÄ8×ÜÏßÉèÖÃ
		LCD_WriteReg(0x04,0x0000); //Scalling Control register     
		LCD_WriteReg(0x08,0x0207); //Display Control 2 
		LCD_WriteReg(0x09,0x0000); //Display Control 3	 
		LCD_WriteReg(0x0A,0x0000); //Frame Cycle Control	 
		LCD_WriteReg(0x0C,0x0000); //External Display Interface Control 1 
		LCD_WriteReg(0x0D,0x0000); //Frame Maker Position		 
		LCD_WriteReg(0x0F,0x0000); //External Display Interface Control 2 
 		delay_ms(20);
		//TFT Òº¾§²ÊÉ«Í¼ÏñÏÔÊ¾·½·¨14
		LCD_WriteReg(0x10,0x16B0); //0x14B0 //Power Control 1
		LCD_WriteReg(0x11,0x0001); //0x0007 //Power Control 2
		LCD_WriteReg(0x17,0x0001); //0x0000 //Power Control 3
		LCD_WriteReg(0x12,0x0138); //0x013B //Power Control 4
		LCD_WriteReg(0x13,0x0800); //0x0800 //Power Control 5
		LCD_WriteReg(0x29,0x0009); //NVM read data 2
		LCD_WriteReg(0x2a,0x0009); //NVM read data 3
		LCD_WriteReg(0xa4,0x0000);	 
		LCD_WriteReg(0x50,0x0000); //ÉèÖÃ²Ù×÷´°¿ÚµÄXÖá¿ªÊ¼ÁÐ
		LCD_WriteReg(0x51,0x00EF); //ÉèÖÃ²Ù×÷´°¿ÚµÄXÖá½áÊøÁÐ
		LCD_WriteReg(0x52,0x0000); //ÉèÖÃ²Ù×÷´°¿ÚµÄYÖá¿ªÊ¼ÐÐ
		LCD_WriteReg(0x53,0x013F); //ÉèÖÃ²Ù×÷´°¿ÚµÄYÖá½áÊøÐÐ
		LCD_WriteReg(0x60,0x2700); //Driver Output Control
		//ÉèÖÃÆÁÄ»µÄµãÊýÒÔ¼°É¨ÃèµÄÆðÊ¼ÐÐ
		LCD_WriteReg(0x61,0x0001); //Driver Output Control
		LCD_WriteReg(0x6A,0x0000); //Vertical Scroll Control
		LCD_WriteReg(0x80,0x0000); //Display Position ¨C Partial Display 1
		LCD_WriteReg(0x81,0x0000); //RAM Address Start ¨C Partial Display 1
		LCD_WriteReg(0x82,0x0000); //RAM address End - Partial Display 1
		LCD_WriteReg(0x83,0x0000); //Display Position ¨C Partial Display 2
		LCD_WriteReg(0x84,0x0000); //RAM Address Start ¨C Partial Display 2
		LCD_WriteReg(0x85,0x0000); //RAM address End ¨C Partail Display2
		LCD_WriteReg(0x90,0x0013); //Frame Cycle Control
		LCD_WriteReg(0x92,0x0000);  //Panel Interface Control 2
		LCD_WriteReg(0x93,0x0003); //Panel Interface control 3
		LCD_WriteReg(0x95,0x0110);  //Frame Cycle Control
		LCD_WriteReg(0x07,0x0173);		 
		delay_ms(50);
	}	
	else if(lcddev.id==0x1505)//OK
	{
		// second release on 3/5  ,luminance is acceptable,water wave appear during camera preview
        LCD_WriteReg(0x0007,0x0000);
        delay_ms(50); 
        LCD_WriteReg(0x0012,0x011C);//0x011A   why need to set several times?
        LCD_WriteReg(0x00A4,0x0001);//NVM	 
        LCD_WriteReg(0x0008,0x000F);
        LCD_WriteReg(0x000A,0x0008);
        LCD_WriteReg(0x000D,0x0008);	    
  		//Ù¤ÂíÐ£Õý
        LCD_WriteReg(0x0030,0x0707);
        LCD_WriteReg(0x0031,0x0007); //0x0707
        LCD_WriteReg(0x0032,0x0603); 
        LCD_WriteReg(0x0033,0x0700); 
        LCD_WriteReg(0x0034,0x0202); 
        LCD_WriteReg(0x0035,0x0002); //?0x0606
        LCD_WriteReg(0x0036,0x1F0F);
        LCD_WriteReg(0x0037,0x0707); //0x0f0f  0x0105
        LCD_WriteReg(0x0038,0x0000); 
        LCD_WriteReg(0x0039,0x0000); 
        LCD_WriteReg(0x003A,0x0707); 
        LCD_WriteReg(0x003B,0x0000); //0x0303
        LCD_WriteReg(0x003C,0x0007); //?0x0707
        LCD_WriteReg(0x003D,0x0000); //0x1313//0x1f08
        delay_ms(50); 
        LCD_WriteReg(0x0007,0x0001);
        LCD_WriteReg(0x0017,0x0001);//¿ªÆôµçÔ´
        delay_ms(50); 
  		//µçÔ´ÅäÖÃ
        LCD_WriteReg(0x0010,0x17A0); 
        LCD_WriteReg(0x0011,0x0217);//reference voltage VC[2:0]   Vciout = 1.00*Vcivl
        LCD_WriteReg(0x0012,0x011E);//0x011c  //Vreg1out = Vcilvl*1.80   is it the same as Vgama1out ?
        LCD_WriteReg(0x0013,0x0F00);//VDV[4:0]-->VCOM Amplitude VcomL = VcomH - Vcom Ampl
        LCD_WriteReg(0x002A,0x0000);  
        LCD_WriteReg(0x0029,0x000A);//0x0001F  Vcomh = VCM1[4:0]*Vreg1out    gate source voltage??
        LCD_WriteReg(0x0012,0x013E);// 0x013C  power supply on
        //Coordinates Control//
        LCD_WriteReg(0x0050,0x0000);//0x0e00
        LCD_WriteReg(0x0051,0x00EF); 
        LCD_WriteReg(0x0052,0x0000); 
        LCD_WriteReg(0x0053,0x013F); 
    	//Pannel Image Control//
        LCD_WriteReg(0x0060,0x2700); 
        LCD_WriteReg(0x0061,0x0001); 
        LCD_WriteReg(0x006A,0x0000); 
        LCD_WriteReg(0x0080,0x0000); 
    	//Partial Image Control//
        LCD_WriteReg(0x0081,0x0000); 
        LCD_WriteReg(0x0082,0x0000); 
        LCD_WriteReg(0x0083,0x0000); 
        LCD_WriteReg(0x0084,0x0000); 
        LCD_WriteReg(0x0085,0x0000); 
  		//Panel Interface Control//
        LCD_WriteReg(0x0090,0x0013);//0x0010 frenqucy
        LCD_WriteReg(0x0092,0x0300); 
        LCD_WriteReg(0x0093,0x0005); 
        LCD_WriteReg(0x0095,0x0000); 
        LCD_WriteReg(0x0097,0x0000); 
        LCD_WriteReg(0x0098,0x0000); 
  
        LCD_WriteReg(0x0001,0x0100); 
        LCD_WriteReg(0x0002,0x0700); 
        LCD_WriteReg(0x0003,0x1038);//É¨Ãè·½Ïò ÉÏ->ÏÂ  ×ó->ÓÒ 
        LCD_WriteReg(0x0004,0x0000); 
        LCD_WriteReg(0x000C,0x0000); 
        LCD_WriteReg(0x000F,0x0000); 
        LCD_WriteReg(0x0020,0x0000); 
        LCD_WriteReg(0x0021,0x0000); 
        LCD_WriteReg(0x0007,0x0021); 
        delay_ms(20);
        LCD_WriteReg(0x0007,0x0061); 
        delay_ms(20);
        LCD_WriteReg(0x0007,0x0173); 
        delay_ms(20);
	}else if(lcddev.id==0xB505)
	{
		LCD_WriteReg(0x0000,0x0000);
		LCD_WriteReg(0x0000,0x0000);
		LCD_WriteReg(0x0000,0x0000);
		LCD_WriteReg(0x0000,0x0000);
		
		LCD_WriteReg(0x00a4,0x0001);
		delay_ms(20);		  
		LCD_WriteReg(0x0060,0x2700);
		LCD_WriteReg(0x0008,0x0202);
		
		LCD_WriteReg(0x0030,0x0214);
		LCD_WriteReg(0x0031,0x3715);
		LCD_WriteReg(0x0032,0x0604);
		LCD_WriteReg(0x0033,0x0e16);
		LCD_WriteReg(0x0034,0x2211);
		LCD_WriteReg(0x0035,0x1500);
		LCD_WriteReg(0x0036,0x8507);
		LCD_WriteReg(0x0037,0x1407);
		LCD_WriteReg(0x0038,0x1403);
		LCD_WriteReg(0x0039,0x0020);
		
		LCD_WriteReg(0x0090,0x001a);
		LCD_WriteReg(0x0010,0x0000);
		LCD_WriteReg(0x0011,0x0007);
		LCD_WriteReg(0x0012,0x0000);
		LCD_WriteReg(0x0013,0x0000);
		delay_ms(20);
		
		LCD_WriteReg(0x0010,0x0730);
		LCD_WriteReg(0x0011,0x0137);
		delay_ms(20);
		
		LCD_WriteReg(0x0012,0x01b8);
		delay_ms(20);
		
		LCD_WriteReg(0x0013,0x0f00);
		LCD_WriteReg(0x002a,0x0080);
		LCD_WriteReg(0x0029,0x0048);
		delay_ms(20);
		
		LCD_WriteReg(0x0001,0x0100);
		LCD_WriteReg(0x0002,0x0700);
        LCD_WriteReg(0x0003,0x1038);//É¨Ãè·½Ïò ÉÏ->ÏÂ  ×ó->ÓÒ 
		LCD_WriteReg(0x0008,0x0202);
		LCD_WriteReg(0x000a,0x0000);
		LCD_WriteReg(0x000c,0x0000);
		LCD_WriteReg(0x000d,0x0000);
		LCD_WriteReg(0x000e,0x0030);
		LCD_WriteReg(0x0050,0x0000);
		LCD_WriteReg(0x0051,0x00ef);
		LCD_WriteReg(0x0052,0x0000);
		LCD_WriteReg(0x0053,0x013f);
		LCD_WriteReg(0x0060,0x2700);
		LCD_WriteReg(0x0061,0x0001);
		LCD_WriteReg(0x006a,0x0000);
		//LCD_WriteReg(0x0080,0x0000);
		//LCD_WriteReg(0x0081,0x0000);
		LCD_WriteReg(0x0090,0X0011);
		LCD_WriteReg(0x0092,0x0600);
		LCD_WriteReg(0x0093,0x0402);
		LCD_WriteReg(0x0094,0x0002);
		delay_ms(20);
		
		LCD_WriteReg(0x0007,0x0001);
		delay_ms(20);
		LCD_WriteReg(0x0007,0x0061);
		LCD_WriteReg(0x0007,0x0173);
		
		LCD_WriteReg(0x0020,0x0000);
		LCD_WriteReg(0x0021,0x0000);	  
		LCD_WriteReg(0x00,0x22);  
	}else if(lcddev.id==0xC505)
	{
		LCD_WriteReg(0x0000,0x0000);
		LCD_WriteReg(0x0000,0x0000);
		delay_ms(20);		  
		LCD_WriteReg(0x0000,0x0000);
		LCD_WriteReg(0x0000,0x0000);
		LCD_WriteReg(0x0000,0x0000);
		LCD_WriteReg(0x0000,0x0000);
 		LCD_WriteReg(0x00a4,0x0001);
		delay_ms(20);		  
		LCD_WriteReg(0x0060,0x2700);
		LCD_WriteReg(0x0008,0x0806);
		
		LCD_WriteReg(0x0030,0x0703);//gamma setting
		LCD_WriteReg(0x0031,0x0001);
		LCD_WriteReg(0x0032,0x0004);
		LCD_WriteReg(0x0033,0x0102);
		LCD_WriteReg(0x0034,0x0300);
		LCD_WriteReg(0x0035,0x0103);
		LCD_WriteReg(0x0036,0x001F);
		LCD_WriteReg(0x0037,0x0703);
		LCD_WriteReg(0x0038,0x0001);
		LCD_WriteReg(0x0039,0x0004);
		
		
		
		LCD_WriteReg(0x0090, 0x0015);	//80Hz
		LCD_WriteReg(0x0010, 0X0410);	//BT,AP
		LCD_WriteReg(0x0011,0x0247);	//DC1,DC0,VC
		LCD_WriteReg(0x0012, 0x01BC);
		LCD_WriteReg(0x0013, 0x0e00);
		delay_ms(120);
		LCD_WriteReg(0x0001, 0x0100);
		LCD_WriteReg(0x0002, 0x0200);
		LCD_WriteReg(0x0003, 0x1030);
		
		LCD_WriteReg(0x000A, 0x0008);
		LCD_WriteReg(0x000C, 0x0000);
		
		LCD_WriteReg(0x000E, 0x0020);
		LCD_WriteReg(0x000F, 0x0000);
		LCD_WriteReg(0x0020, 0x0000);	//H Start
		LCD_WriteReg(0x0021, 0x0000);	//V Start
		LCD_WriteReg(0x002A,0x003D);	//vcom2
		delay_ms(20);
		LCD_WriteReg(0x0029, 0x002d);
		LCD_WriteReg(0x0050, 0x0000);
		LCD_WriteReg(0x0051, 0xD0EF);
		LCD_WriteReg(0x0052, 0x0000);
		LCD_WriteReg(0x0053, 0x013F);
		LCD_WriteReg(0x0061, 0x0000);
		LCD_WriteReg(0x006A, 0x0000);
		LCD_WriteReg(0x0092,0x0300); 
 
 		LCD_WriteReg(0x0093, 0x0005);
		LCD_WriteReg(0x0007, 0x0100);
	}else if(lcddev.id==0x8989)//OK |/|/|
	{	   
		LCD_WriteReg(0x0000,0x0001);//´ò¿ª¾§Õñ
    	LCD_WriteReg(0x0003,0xA8A4);//0xA8A4
    	LCD_WriteReg(0x000C,0x0000);    
    	LCD_WriteReg(0x000D,0x080C);   
    	LCD_WriteReg(0x000E,0x2B00);    
    	LCD_WriteReg(0x001E,0x00B0);    
    	LCD_WriteReg(0x0001,0x2B3F);//Çý¶¯Êä³ö¿ØÖÆ320*240  0x6B3F
    	LCD_WriteReg(0x0002,0x0600);
    	LCD_WriteReg(0x0010,0x0000);  
    	LCD_WriteReg(0x0011,0x6078); //¶¨ÒåÊý¾Ý¸ñÊ½  16Î»É« 		ºáÆÁ 0x6058
    	LCD_WriteReg(0x0005,0x0000);  
    	LCD_WriteReg(0x0006,0x0000);  
    	LCD_WriteReg(0x0016,0xEF1C);  
    	LCD_WriteReg(0x0017,0x0003);  
    	LCD_WriteReg(0x0007,0x0233); //0x0233       
    	LCD_WriteReg(0x000B,0x0000);  
    	LCD_WriteReg(0x000F,0x0000); //É¨Ãè¿ªÊ¼µØÖ·
    	LCD_WriteReg(0x0041,0x0000);  
    	LCD_WriteReg(0x0042,0x0000);  
    	LCD_WriteReg(0x0048,0x0000);  
    	LCD_WriteReg(0x0049,0x013F);  
    	LCD_WriteReg(0x004A,0x0000);  
    	LCD_WriteReg(0x004B,0x0000);  
    	LCD_WriteReg(0x0044,0xEF00);  
    	LCD_WriteReg(0x0045,0x0000);  
    	LCD_WriteReg(0x0046,0x013F);  
    	LCD_WriteReg(0x0030,0x0707);  
    	LCD_WriteReg(0x0031,0x0204);  
    	LCD_WriteReg(0x0032,0x0204);  
    	LCD_WriteReg(0x0033,0x0502);  
    	LCD_WriteReg(0x0034,0x0507);  
    	LCD_WriteReg(0x0035,0x0204);  
    	LCD_WriteReg(0x0036,0x0204);  
    	LCD_WriteReg(0x0037,0x0502);  
    	LCD_WriteReg(0x003A,0x0302);  
    	LCD_WriteReg(0x003B,0x0302);  
    	LCD_WriteReg(0x0023,0x0000);  
    	LCD_WriteReg(0x0024,0x0000);  
    	LCD_WriteReg(0x0025,0x8000);  
    	LCD_WriteReg(0x004f,0);        //ÐÐÊ×Ö·0
    	LCD_WriteReg(0x004e,0);        //ÁÐÊ×Ö·0
	}else if(lcddev.id==0x4531)//OK |/|/|
	{
		LCD_WriteReg(0X00,0X0001);   
		delay_ms(10);   
		LCD_WriteReg(0X10,0X1628);   
		LCD_WriteReg(0X12,0X000e);//0x0006    
		LCD_WriteReg(0X13,0X0A39);   
		delay_ms(10);   
		LCD_WriteReg(0X11,0X0040);   
		LCD_WriteReg(0X15,0X0050);   
		delay_ms(10);   
		LCD_WriteReg(0X12,0X001e);//16    
		delay_ms(10);   
		LCD_WriteReg(0X10,0X1620);   
		LCD_WriteReg(0X13,0X2A39);   
		delay_ms(10);   
		LCD_WriteReg(0X01,0X0100);   
		LCD_WriteReg(0X02,0X0300);   
		LCD_WriteReg(0X03,0X1038);//¸Ä±ä·½ÏòµÄ   
		LCD_WriteReg(0X08,0X0202);   
		LCD_WriteReg(0X0A,0X0008);   
		LCD_WriteReg(0X30,0X0000);   
		LCD_WriteReg(0X31,0X0402);   
		LCD_WriteReg(0X32,0X0106);   
		LCD_WriteReg(0X33,0X0503);   
		LCD_WriteReg(0X34,0X0104);   
		LCD_WriteReg(0X35,0X0301);   
		LCD_WriteReg(0X36,0X0707);   
		LCD_WriteReg(0X37,0X0305);   
		LCD_WriteReg(0X38,0X0208);   
		LCD_WriteReg(0X39,0X0F0B);   
		LCD_WriteReg(0X41,0X0002);   
		LCD_WriteReg(0X60,0X2700);   
		LCD_WriteReg(0X61,0X0001);   
		LCD_WriteReg(0X90,0X0210);   
		LCD_WriteReg(0X92,0X010A);   
		LCD_WriteReg(0X93,0X0004);   
		LCD_WriteReg(0XA0,0X0100);   
		LCD_WriteReg(0X07,0X0001);   
		LCD_WriteReg(0X07,0X0021);   
		LCD_WriteReg(0X07,0X0023);   
		LCD_WriteReg(0X07,0X0033);   
		LCD_WriteReg(0X07,0X0133);   
		LCD_WriteReg(0XA0,0X0000); 
	}else if(lcddev.id==0x4535)
	{			      
		LCD_WriteReg(0X15,0X0030);   
		LCD_WriteReg(0X9A,0X0010);   
 		LCD_WriteReg(0X11,0X0020);   
 		LCD_WriteReg(0X10,0X3428);   
		LCD_WriteReg(0X12,0X0002);//16    
 		LCD_WriteReg(0X13,0X1038);   
		delay_ms(40);   
		LCD_WriteReg(0X12,0X0012);//16    
		delay_ms(40);   
  		LCD_WriteReg(0X10,0X3420);   
 		LCD_WriteReg(0X13,0X3038);   
		delay_ms(70);   
		LCD_WriteReg(0X30,0X0000);   
		LCD_WriteReg(0X31,0X0402);   
		LCD_WriteReg(0X32,0X0307);   
		LCD_WriteReg(0X33,0X0304);   
		LCD_WriteReg(0X34,0X0004);   
		LCD_WriteReg(0X35,0X0401);   
		LCD_WriteReg(0X36,0X0707);   
		LCD_WriteReg(0X37,0X0305);   
		LCD_WriteReg(0X38,0X0610);   
		LCD_WriteReg(0X39,0X0610); 
		  
		LCD_WriteReg(0X01,0X0100);   
		LCD_WriteReg(0X02,0X0300);   
		LCD_WriteReg(0X03,0X1030);//¸Ä±ä·½ÏòµÄ   
		LCD_WriteReg(0X08,0X0808);   
		LCD_WriteReg(0X0A,0X0008);   
 		LCD_WriteReg(0X60,0X2700);   
		LCD_WriteReg(0X61,0X0001);   
		LCD_WriteReg(0X90,0X013E);   
		LCD_WriteReg(0X92,0X0100);   
		LCD_WriteReg(0X93,0X0100);   
 		LCD_WriteReg(0XA0,0X3000);   
 		LCD_WriteReg(0XA3,0X0010);   
		LCD_WriteReg(0X07,0X0001);   
		LCD_WriteReg(0X07,0X0021);   
		LCD_WriteReg(0X07,0X0023);   
		LCD_WriteReg(0X07,0X0033);   
		LCD_WriteReg(0X07,0X0133);   
	}		
	LCD_Display_Dir(0);		 	//Ä¬ÈÏÎªÊúÆÁ
	LCD_LED=1;					//µãÁÁ±³¹â
	LCD_Clear(WHITE);
}  
//ÇåÆÁº¯Êý
//color:ÒªÇåÆÁµÄÌî³äÉ«
void LCD_Clear(u16 color)
{
	u32 index=0;      
	u32 totalpoint=lcddev.width;
	totalpoint*=lcddev.height; 	//µÃµ½×ÜµãÊý
	LCD_SetCursor(0x00,0x0000);	//ÉèÖÃ¹â±êÎ»ÖÃ 
	LCD_WriteRAM_Prepare();     //¿ªÊ¼Ð´ÈëGRAM	 	  
	for(index=0;index<totalpoint;index++)
	{
		LCD->LCD_RAM=color;	   
	}
}  
//ÔÚÖ¸¶¨ÇøÓòÄÚÌî³äµ¥¸öÑÕÉ«
//(sx,sy),(ex,ey):Ìî³ä¾ØÐÎ¶Ô½Ç×ø±ê,ÇøÓò´óÐ¡Îª:(ex-sx+1)*(ey-sy+1)   
//color:ÒªÌî³äµÄÑÕÉ«
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{          
	u16 i,j;
	u16 xlen=0;
	xlen=ex-sx+1;	   
	for(i=sy;i<=ey;i++)
	{
	 	LCD_SetCursor(sx,i);      				//ÉèÖÃ¹â±êÎ»ÖÃ 
		LCD_WriteRAM_Prepare();     			//¿ªÊ¼Ð´ÈëGRAM	  
		for(j=0;j<xlen;j++)LCD_WR_DATA(color);	//ÉèÖÃ¹â±êÎ»ÖÃ 	    
	}
}  
//ÔÚÖ¸¶¨ÇøÓòÄÚÌî³äÖ¸¶¨ÑÕÉ«¿é			 
//(sx,sy),(ex,ey):Ìî³ä¾ØÐÎ¶Ô½Ç×ø±ê,ÇøÓò´óÐ¡Îª:(ex-sx+1)*(ey-sy+1)   
//color:ÒªÌî³äµÄÑÕÉ«
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
{  
	u16 height,width;
	u16 i,j;
	width=ex-sx+1; 		//µÃµ½Ìî³äµÄ¿í¶È
	height=ey-sy+1;		//¸ß¶È
 	for(i=0;i<height;i++)
	{
 		LCD_SetCursor(sx,sy+i);   	//ÉèÖÃ¹â±êÎ»ÖÃ 
		LCD_WriteRAM_Prepare();     //¿ªÊ¼Ð´ÈëGRAM
		for(j=0;j<width;j++)LCD->LCD_RAM=color[i*height+j];//Ð´ÈëÊý¾Ý 
	}	  
}  
//»­Ïß
//x1,y1:Æðµã×ø±ê
//x2,y2:ÖÕµã×ø±ê  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //¼ÆËã×ø±êÔöÁ¿ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //ÉèÖÃµ¥²½·½Ïò 
	else if(delta_x==0)incx=0;//´¹Ö±Ïß 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//Ë®Æ½Ïß 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //Ñ¡È¡»ù±¾ÔöÁ¿×ø±êÖá 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//»­ÏßÊä³ö 
	{  
		LCD_DrawPoint(uRow,uCol);//»­µã 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}    
//»­¾ØÐÎ	  
//(x1,y1),(x2,y2):¾ØÐÎµÄ¶Ô½Ç×ø±ê
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}
//ÔÚÖ¸¶¨Î»ÖÃ»­Ò»¸öÖ¸¶¨´óÐ¡µÄÔ²
//(x,y):ÖÐÐÄµã
//r    :°ë¾¶
void Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //ÅÐ¶ÏÏÂ¸öµãÎ»ÖÃµÄ±êÖ¾
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b);             //5
 		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-a,y0+b);             //1       
 		LCD_DrawPoint(x0-b,y0+a);             
		LCD_DrawPoint(x0-a,y0-b);             //2             
  		LCD_DrawPoint(x0-b,y0-a);             //7     	         
		a++;
		//Ê¹ÓÃBresenhamËã·¨»­Ô²     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 									  
//ÔÚÖ¸¶¨Î»ÖÃÏÔÊ¾Ò»¸ö×Ö·û
//x,y:ÆðÊ¼×ø±ê
//num:ÒªÏÔÊ¾µÄ×Ö·û:" "--->"~"
//size:×ÖÌå´óÐ¡ 12/16
//mode:µþ¼Ó·½Ê½(1)»¹ÊÇ·Çµþ¼Ó·½Ê½(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u16 colortemp=POINT_COLOR;      			     
	//ÉèÖÃ´°¿Ú		   
	num=num-' ';//µÃµ½Æ«ÒÆºóµÄÖµ
	if(!mode) //·Çµþ¼Ó·½Ê½
	{
	    for(t=0;t<size;t++)
	    {   
			if(size==12)temp=asc2_1206[num][t];  //µ÷ÓÃ1206×ÖÌå
			else temp=asc2_1608[num][t];		 //µ÷ÓÃ1608×ÖÌå 	                          
	        for(t1=0;t1<8;t1++)
			{			    
		        if(temp&0x80)POINT_COLOR=colortemp;
				else POINT_COLOR=BACK_COLOR;
				LCD_DrawPoint(x,y);	
				temp<<=1;
				y++;
				if(x>=lcddev.width){POINT_COLOR=colortemp;return;}//³¬ÇøÓòÁË
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=lcddev.width){POINT_COLOR=colortemp;return;}//³¬ÇøÓòÁË
					break;
				}
			}  	 
	    }    
	}else//µþ¼Ó·½Ê½
	{
	    for(t=0;t<size;t++)
	    {   
			if(size==12)temp=asc2_1206[num][t];  //µ÷ÓÃ1206×ÖÌå
			else temp=asc2_1608[num][t];		 //µ÷ÓÃ1608×ÖÌå 	                          
	        for(t1=0;t1<8;t1++)
			{			    
		        if(temp&0x80)LCD_DrawPoint(x,y); 
				temp<<=1;
				y++;
				if(x>=lcddev.height){POINT_COLOR=colortemp;return;}//³¬ÇøÓòÁË
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=lcddev.width){POINT_COLOR=colortemp;return;}//³¬ÇøÓòÁË
					break;
				}
			}  	 
	    }     
	}
	POINT_COLOR=colortemp;	    	   	 	  
}   
//m^nº¯Êý
//·µ»ØÖµ:m^n´Î·½.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 
//ÏÔÊ¾Êý×Ö,¸ßÎ»Îª0,Ôò²»ÏÔÊ¾
//x,y :Æðµã×ø±ê	 
//len :Êý×ÖµÄÎ»Êý
//size:×ÖÌå´óÐ¡
//color:ÑÕÉ« 
//num:ÊýÖµ(0~4294967295);	 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
} 
//ÏÔÊ¾Êý×Ö,¸ßÎ»Îª0,»¹ÊÇÏÔÊ¾
//x,y:Æðµã×ø±ê
//num:ÊýÖµ(0~999999999);	 
//len:³¤¶È(¼´ÒªÏÔÊ¾µÄÎ»Êý)
//size:×ÖÌå´óÐ¡
//mode:
//[7]:0,²»Ìî³ä;1,Ìî³ä0.
//[6:1]:±£Áô
//[0]:0,·Çµþ¼ÓÏÔÊ¾;1,µþ¼ÓÏÔÊ¾.
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
} 
//ÏÔÊ¾×Ö·û´®
//x,y:Æðµã×ø±ê
//width,height:ÇøÓò´óÐ¡  
//size:×ÖÌå´óÐ¡
//*p:×Ö·û´®ÆðÊ¼µØÖ·		  
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//ÅÐ¶ÏÊÇ²»ÊÇ·Ç·¨×Ö·û!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//ÍË³ö
        LCD_ShowChar(x,y,*p,size,0);
        x+=size/2;
        p++;
    }  
}



void tftlcd_write_pic(int x0,int y0,const unsigned short *pointer)
     {
	 int x1 = x0 + ((int)*pointer++), y1 = y0 + ((int)*pointer++),counter_x,counter_y;
	 					  
	 if(x0 < 0) x0 = 0;
	 if(y0 < 0) y0 = 0;
	  
     
	 for(counter_y = y0;counter_y < y1;counter_y++)
	 	{
		for(counter_x = x0;counter_x < x1;counter_x++)
			{
					POINT_COLOR=(int)*pointer++;
          LCD_DrawPoint(counter_x,counter_y);
			}; 
     }
	 }



void LCD_BackLight_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; 
  TIM_OCInitTypeDef TIM_OCInitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO , ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
 						 
  /*GPIOB Configuration:  PB5(TIM3 CH2) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);	 /* ¹?½??????? */     



  TIM_TimeBaseStructure.TIM_ClockDivision =0;  /* ?¹???µ?³»ù´??±?? */
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseStructure.TIM_Prescaler = 100;  /* ?±???¤·??µ */
  TIM_TimeBaseStructure.TIM_Period = 1000;   /* TIM3 ARR Register */
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; /* ??³??£?½ */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 700; /* ?¼??±?²??? */
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);
  
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);    /* ?¹??TIM3??CCR2µ??¤×°´¢´??÷ */

  TIM_ARRPreloadConfig(TIM3, ENABLE);  /* ?¹?? ARR×°?? */
  TIM_Cmd(TIM3, ENABLE);			   /* ?¹??TIM3 */

}