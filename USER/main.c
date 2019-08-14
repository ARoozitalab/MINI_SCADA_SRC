/*********************************************************************************************************
*
* File                : MAIN.c
* Version             : V1.0
* By                  : alireza roozitalab
* email               : alireza.roozitalab@gmail.com
* git user            : ARoozitalab
*                                                
*                                          All Rights Reserved
*
*********************************************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "systick.h"
#include "GLCD.h"
#include "spi.h"
#include "config.h"
#include  "scada_init.h"
#include "FreeRTOS.h"
#include "task.h"
#include "simple_server.h"
#include "niawell.h"
#include "scadazoom.h"
#include "stm32f10x_flash.h"

#define MESSAGE0   "     Message 0    " //lenght  should be 18 char
#define MESSAGE1   "Every Things OK   "
#define MESSAGE2   "     Message 2    "
#define MESSAGE3   "     Message 3    "
#define MESSAGE4   "     Message 4    "
#define MESSAGE5   "     Message 5    "
#define MESSAGE6   "     Message 6    "
#define MESSAGE7   "     Message 7    "
#define MESSAGE8   "     Message 8    "
#define MESSAGE9   "     Message 9    "
#define MESSAGE10  "     Message 10   "
#define MESSAGE11  "     Message 11   "
#define MESSAGE12  "     Message 12   "
#define MESSAGE13  "     Message 13   "
#define MESSAGE14  "     Message 14   "
#define MESSAGE15  "     Message 15   "

#define MENU_B_D  500000
#define AVG_NUM 	 10000
//////////////////////
//char mesage_num=0;
char f_help_me=0;
uint16_t polldata[MAX_REG]={0,0,0,0,0,0,0,0,0,0,0,0,0,1,0};
extern vu16 ADC_ConvertedValue[7];
///////////////////// poll registers
#define PWM1_REG    11
#define PWM2_REG    12
#define RELAY_REG   10
#define INPUT_REG   8
#define FLAG_REG    13
#define FLAG2_REG		7
//////////////////////////
extern  u8 myip[4];
extern u16 mywwwport;
extern mymac[6];
uint16_t adc_avg[7];
char ip_Set_act=0;
#define IP_SAVE 0X08070000



/*******************************************************************************
* Function Name  : Digital_show
* Description    : show input parametr on lcd
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Digital_show(char show_d)
{
	static uint16_t l_digit_in=0 ,l_digit_out=0 ,l_pwm1=0,l_pwm2=0;
  char b[25];
	int i=0;
	
	if((l_digit_in!=polldata[INPUT_REG])|(show_d==1))
	{	
		for(i=0;i<12;i++)
		{
		if(polldata[INPUT_REG] & 1<<i)
		tftlcd_draw_rectangle(((i*25)+10),100,((i*25)+30),120,Green);
		else
		tftlcd_draw_rectangle(((i*25)+10),100,((i*25)+30),120,Red);
		if(i<9)
		sprintf(b," %u",i+1);	
		else
		sprintf(b,"%u",i+1);	
		GUI_Text(((i*25)+10),80,b,Black,White);
		
		
		}
//		sprintf(b,"Digital In=%u   ",polldata[INPUT_REG]);	
		GUI_Text(10, 60,"Digital Input",Black,White);
		l_digit_in=polldata[INPUT_REG];
	
	
	}
	
	
	
	if((l_digit_out!=polldata[RELAY_REG])|(show_d==1))
	{	
		for(i=0;i<4;i++)
		{
		if(polldata[RELAY_REG] & 1<<i)
		tftlcd_draw_rectangle(((i*25)+10),170,((i*25)+30),190,Green);
		else
		tftlcd_draw_rectangle(((i*25)+10),170,((i*25)+30),190,Red);
		
		sprintf(b," %u",i+1);	
		GUI_Text(((i*25)+10),150,b,Black,White);
		
		
		}
//		sprintf(b,"Digital Out=%u   ",polldata[RELAY_REG]);	
			GUI_Text(10,130,"Digital Out",Black,White);
	
		l_digit_out=polldata[RELAY_REG];
	
	
	}
	
	if((l_pwm1!=polldata[PWM1_REG])|(show_d==1))
	{	

		sprintf(b,"PWM1=%u  ",polldata[PWM1_REG]);	
		GUI_Text(120,160,b,Black,White);
		tftlcd_draw_rectangle(198,158,302,177,Grey);
		tftlcd_draw_rectangle(200,160,polldata[PWM1_REG]+200,175,Green);
		l_pwm1=polldata[PWM1_REG];	
	}
	
	if((l_pwm2!=polldata[PWM2_REG])|(show_d==1))
	{	

		sprintf(b,"PWM1=%u   ",polldata[PWM2_REG]);	
		GUI_Text(120,180,b,Black,White);
		tftlcd_draw_rectangle(198,178,302,197,Grey);
		tftlcd_draw_rectangle(200,180,polldata[PWM2_REG]+200,195,Green);
		l_pwm2=polldata[PWM2_REG];	
	}

	
}



/*******************************************************************************
* Function Name  : ADC_show
* Description    : show message on home page according parameters
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/




void ADC_show(char show_d)
{
	static uint16_t l_adc[7];
  char b[25];
	int i=0;
	

		for(i=0;i<7;i++)
		{
			if((l_adc[i]!=polldata[i])|(show_d==1))
				{	
						sprintf(b,"Analog in%d=%d",i+1,polldata[i]/40);
						if(i<4)
						{
						GUI_Text(10, 70+(i*25),b,Black,White);
						GUI_Text(120, 70+(i*25),"%",Black,White);
						}
						else
						{
						GUI_Text(180, (70+((i-3)*20)),b,Black,White);
							GUI_Text(290, (70+((i-3)*20)),"%",Black,White);
						}
						l_adc[i]=polldata[i];
				}
		
		}

	
	}
	


/*******************************************************************************
* Function Name  : message_show
* Description    : show message on home page according parameters
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void message_show(char show_d)
		{

			static char msgl=0;
						Set_font(1);
			if((msgl!=polldata[FLAG_REG])|(show_d==1))
			{	

					switch(polldata[FLAG_REG])
					{
						
						case 0:	
						GUI_Text(15, 130,(uint8_t*)MESSAGE0,Black,White);
						
						break;
						
						case 1:	
						GUI_Text(15, 130,(uint8_t*)MESSAGE1,Black,White);
						f_help_me=0;
						GUI_Text(270, 220, "    ",Red,White);
						break;
						
						case 2:	
						GUI_Text(15, 130,(uint8_t*)MESSAGE2,Black,White);
						break;
						
						case 3:	
						GUI_Text(15, 130,(uint8_t*)MESSAGE3,Black,White);
						break;			
			
						case 4:	
						GUI_Text(15, 130,(uint8_t*)MESSAGE4,Black,White);
						break;
						
						case 5:	
						GUI_Text(15, 130,(uint8_t*)MESSAGE5,Black,White);
						break;	
						
						case 6:	
						GUI_Text(15, 130,(uint8_t*)MESSAGE6,Black,White);
						break;	
												
												
						case 7:	
						GUI_Text(15, 130,(uint8_t*)MESSAGE7,Black,White);
						break;	
																														
						case 8:	
						GUI_Text(15, 130,(uint8_t*)MESSAGE8,Black,White);
						break;	
																								
																								
						case 9:	
						GUI_Text(15, 130,(uint8_t*)MESSAGE9,Black,White);
						break;	
																																																					
						case 10:	
						GUI_Text(15, 130,(uint8_t*)MESSAGE10,Black,White);
						break;	
																																				
						case 11:	
						GUI_Text(15, 130,(uint8_t*)MESSAGE11,Black,White);
						break;	
						
						case 12:	
						GUI_Text(15, 130,(uint8_t*)MESSAGE12,Black,White);
						break;	

						case 13:	
						GUI_Text(15, 130,(uint8_t*)MESSAGE13,Black,White);
						break;												
						
						case 14:	
						GUI_Text(15, 130,(uint8_t*)MESSAGE14,Black,White);
						break;	

						case 15:	
						GUI_Text(15, 130,(uint8_t*)MESSAGE15,Black,White);
						break;		
						

					}
									  	msgl=polldata[FLAG_REG];
				}
				Set_font(0);
			}
/*******************************************************************************
* Function Name  : home_show
* Description    : home page on lcd
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/

void home_show()
	{
			char b[30];
			LCD_Clear(White);
			tftlcd_write_pic(5,0,niawell);
			tftlcd_write_pic(110,5,scadazoom);		

			Set_font(0);
			//GUI_Text(20, 100, "Device ip:",Black,White);
			sprintf(b,"%d.%d.%d.%d  ",myip[0],myip[1],myip[2],myip[3]);	
			GUI_Text(10, 220,b,Black,White);
			tftlcd_draw_rectangle(10,110,310,113,Green);
			tftlcd_draw_rectangle(10,170,310,173,Green);
			tftlcd_draw_rectangle(10,110,13,170,Green);
			tftlcd_draw_rectangle(307,110,310,170,Green);
		//	tftlcd_draw_rectangle(70,112,100,310,Green);
		tftlcd_draw_rectangle(112,70,310,100,Green);
			GUI_Text(170, 77, "Message:",Black,Green);

			message_show(1);
	
			if(	f_help_me)
						GUI_Text(280, 220, "HELP",Red,White);
	
	}
	
	
	/*******************************************************************************
* Function Name  : ETH_Task
* Description    : modbus tcp task
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void ETH_Task(void * pvArg)
{
	simple_server();
	GPIO_SetBits(GPIOG,GPIO_Pin_1);
	for(;;);
}

	

/*******************************************************************************
* Function Name  : Poll_Handle
* Description    : read Inputs and Analogs set relay and pwm
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/


void Poll_Handle(void * pvArg)
{
	int j=0;
	uint16_t pwm1=0,pwm2=0;
	uint16_t last_r=0;

	char z=0;
	uint16_t z1=0;
		char b[30];
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
	for(;;)
	{
	
	if(last_r!=polldata[RELAY_REG])
	{
	//---relay 1
	if((polldata[RELAY_REG]& 0x1)==1)
	GPIO_SetBits(RELAY1_PORT,RELAY1_PIN);
	
	else
	GPIO_ResetBits(RELAY1_PORT,RELAY1_PIN);	
	
	//---relay 2
	if((polldata[RELAY_REG]& 0x2)==2)
	GPIO_SetBits(RELAY2_PORT,RELAY2_PIN);
	
	else
	GPIO_ResetBits(RELAY2_PORT,RELAY2_PIN);		
	
	
	//---relay 3
	if((polldata[RELAY_REG]& 0x4)==4)
	GPIO_SetBits(RELAY3_PORT,RELAY3_PIN);
	
	else
	GPIO_ResetBits(RELAY3_PORT,RELAY3_PIN);	

	//---relay 4
	if((polldata[RELAY_REG]& 0x8)==8)
	GPIO_SetBits(RELAY4_PORT,RELAY4_PIN);
	
	else
	GPIO_ResetBits(RELAY4_PORT,RELAY4_PIN);		
	
	last_r=polldata[RELAY_REG];
	
	}
	//----------ADC STORE
	if(z1>=AVG_NUM)
	{
	for(j=0;j<7;j++)
		polldata[j]=adc_avg[j];
		z1=0;
	}
	adc_avg[z]=(ADC_ConvertedValue[z]+adc_avg[z])/2;
	
	z++;
	if(z>=7)
	{
	z=0;
		z1++;
	}
	//------------INPUT STORE
	
	
  //input1	
	if(!(GPIO_ReadInputDataBit(INPUT1_PORT, INPUT1_PIN)))
	polldata[INPUT_REG]=polldata[INPUT_REG]|(1<<0);
	else
	polldata[INPUT_REG]=(polldata[INPUT_REG] & ~(1<<0));
	
 //input2	
	if(!(GPIO_ReadInputDataBit(INPUT2_PORT, INPUT2_PIN)))
	polldata[INPUT_REG]=polldata[INPUT_REG]|(1<<1);
	else
	polldata[INPUT_REG]=(polldata[INPUT_REG] & (~(1<<1)));
	
 //input3	
	if(!(GPIO_ReadInputDataBit(INPUT3_PORT, INPUT3_PIN)))
	polldata[INPUT_REG]=polldata[INPUT_REG]|(1<<2);
	else
	polldata[INPUT_REG]=(polldata[INPUT_REG] & ~(1<<2));	
	
	
	 //input4	
	if(!(GPIO_ReadInputDataBit(INPUT4_PORT, INPUT4_PIN)))
	polldata[INPUT_REG]=polldata[INPUT_REG]|(1<<3);
	else
	polldata[INPUT_REG]=(polldata[INPUT_REG] & ~(1<<3));	
	
	
		 //input5	
	if(!(GPIO_ReadInputDataBit(INPUT5_PORT, INPUT5_PIN)))
	polldata[INPUT_REG]=polldata[INPUT_REG]|(1<<4);
	else
	polldata[INPUT_REG]=(polldata[INPUT_REG] & ~(1<<4));	
	
	
			 //input6	
	if(!(GPIO_ReadInputDataBit(INPUT6_PORT, INPUT6_PIN)))
	polldata[INPUT_REG]=polldata[INPUT_REG]|(1<<5);
	else
	polldata[INPUT_REG]=(polldata[INPUT_REG] & ~(1<<5));	
	
	
	
		//input7	
	if(!(GPIO_ReadInputDataBit(INPUT7_PORT, INPUT7_PIN)))
	polldata[INPUT_REG]=polldata[INPUT_REG]|(1<<6);
	else
	polldata[INPUT_REG]=(polldata[INPUT_REG] & ~(1<<6));	
	
	
	
			//input8	
	if(!(GPIO_ReadInputDataBit(INPUT8_PORT, INPUT8_PIN)))
	polldata[INPUT_REG]=polldata[INPUT_REG]|(1<<7);
	else
	polldata[INPUT_REG]=(polldata[INPUT_REG] & ~(1<<7));	
	
	
	
				//input9	
	if(!(GPIO_ReadInputDataBit(INPUT9_PORT, INPUT9_PIN)))
	polldata[INPUT_REG]=polldata[INPUT_REG]|(1<<8);
	else
	polldata[INPUT_REG]=(polldata[INPUT_REG] & ~(1<<8));	
	
	
	
					//input10	
	if(!(GPIO_ReadInputDataBit(INPUT10_PORT, INPUT10_PIN)))
	polldata[INPUT_REG]=polldata[INPUT_REG]|(1<<9);
	else
	polldata[INPUT_REG]=(polldata[INPUT_REG] & ~(1<<9));
	
	
	
	
			//input11	
	if(!(GPIO_ReadInputDataBit(INPUT11_PORT, INPUT11_PIN)))
	polldata[INPUT_REG]=polldata[INPUT_REG]|(1<<10);
	else
	polldata[INPUT_REG]=(polldata[INPUT_REG] & ~(1<<10));
	
	
	
				//input12	
	if(!(GPIO_ReadInputDataBit(INPUT12_PORT, INPUT12_PIN)))
	polldata[INPUT_REG]=polldata[INPUT_REG]|(1<<11);
	else
	polldata[INPUT_REG]=(polldata[INPUT_REG] & ~(1<<11));
	
	
	

polldata[7]=f_help_me;


if((pwm1!=polldata[PWM1_REG]))
	
{		
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = polldata[PWM1_REG]*10; 
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);   	
	pwm1=polldata[PWM1_REG];	
}


if((pwm2!=polldata[PWM2_REG]))
{
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = polldata[PWM2_REG]*10; 
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);   	
	pwm2=polldata[PWM2_REG];	
}
	


	if(polldata[FLAG_REG]==0)
	GPIO_SetBits(GPIOG,GPIO_Pin_0);
	else
	GPIO_ResetBits(GPIOG,GPIO_Pin_0);
	







	}

	
}



/*******************************************************************************
* Function Name  : GUI_Task
* Description    : LCD User Interface Task
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/





void GUI_Task(void * pvArg)
{
uint8_t ipv[4],ipvl[4];
	char b[30];
	uint8_t menu_state=0;
	uint8_t lcount=1;
	uint8_t change=0;
uint8_t setip=1;
			ipv[0]=	myip[0];
			ipv[1]=	myip[1];
			ipv[2]=	myip[2];
			ipv[3]=	myip[3];
	
	
				ipvl[0]=	myip[0];
			ipvl[1]=	myip[1];
			ipvl[2]=	myip[2];
			ipvl[3]=	myip[3];
	for(;;)
	{
		if(setip==1)
		{

			if((myip[0]!=ipv[0])|(myip[1]==ipv[1])|(myip[2]==ipv[2])|(myip[3]==ipv[3]))
				{
				STMFLASH_Write(IP_SAVE,(u16*)myip,4);
				

			myip[0]=ipv[0];
			myip[1]=ipv[1];
			myip[2]=ipv[2];
			myip[3]=ipv[3];
			init_ip_arp_udp_tcp(mymac, myip, mywwwport);
			STMFLASH_Write(IP_SAVE,(u16*)myip,4);			
				}
			home_show();		
			setip=0;
		}
		switch(menu_state)
		{
			case 0:
		  message_show(0);
			if(change==0)
			{
					if (lcount==1)
					{
					tftlcd_draw_rectangle(5,180,105,210,Green);
					GUI_Text(23, 187, "IP Menu",Black,Green);
					}
					else
					{
					tftlcd_draw_rectangle(5,180,105,210,Black);
					GUI_Text(23, 187,"IP Menu",White,Black);
					}
					
					
					if (lcount==2)
					{
					tftlcd_draw_rectangle(110,180,210,210,Green);
					GUI_Text(128, 187, "I/O Menu",Black,Green);
					}
					else
					{
					tftlcd_draw_rectangle(110,180,210,210,Black);
					GUI_Text(128, 187,"I/O Menu",White,Black);
					}
					
					
					
					if (lcount==3)
					{
					tftlcd_draw_rectangle(215,180,315,210,Green);
					GUI_Text(233, 187, "ADC Menu",Black,Green);
					}
					else
					{
					tftlcd_draw_rectangle(215,180,315,210,Black);
					GUI_Text(233, 187,"ADC Menu",White,Black);
					}
			
			change=1;
			}
			
			if((!(GPIO_ReadInputDataBit(LEFT_PORT, LEFT_PIN)))&(dif_count1()))
			{
			lcount--;
			change=0;
				setms_timecount1(1000);
			}
			
		if((!(GPIO_ReadInputDataBit(RIGHT_PORT, RIGHT_PIN)))&(dif_count1()))
			{
			lcount++;
			change=0;	
				setms_timecount1(1000);
			}
			
			if(!(GPIO_ReadInputDataBit(ENTER_PORT, ENTER_PIN)))
			{
			if ((lcount==1) &(ip_Set_act))
			{
				menu_state=1;	
				LCD_Clear(White);
				tftlcd_write_pic(0,0,niawell);			
				if(	f_help_me)
						GUI_Text(280, 220, "HELP",Red,White);
				setms_timecount(MENU_B_D);
				tftlcd_draw_rectangle(0,160,320,190,Green);
				tftlcd_draw_rectangle(0,160,5,240,Green);
				tftlcd_draw_rectangle(315,160,320,240,Green);
				GUI_Text(135, 168, "Help :",Black,Green);
				GUI_Text(10, 200, "Left/Right for increase/decreas Values",Black,White);
				GUI_Text(10, 220, "Enter/Back for set Next/Before values",Black,White);
			}
			if (lcount==2)
			{
				menu_state=2;	
				LCD_Clear(White);
				tftlcd_write_pic(80,5,scadazoom);	
				tftlcd_draw_rectangle(0,210,320,240,Green);

				GUI_Text(5, 220, "NIAWELL",Green,Black);
				if(	f_help_me)
						GUI_Text(280, 220, "HELP",Red,White);
				Digital_show(1);
				setms_timecount(MENU_B_D);
			}
			
			if (lcount==3)
			{
				menu_state=3;	
				LCD_Clear(White);
				tftlcd_write_pic(80,5,scadazoom);	
				tftlcd_draw_rectangle(0,210,320,240,Green);
				GUI_Text(5, 220, "NIAWELL",Green,Black);
				if(	f_help_me)
						GUI_Text(280, 220, "HELP",Red,White);
				 ADC_show(1);
				setms_timecount(MENU_B_D);
			}
			 change=0;
			}
			
			if(lcount==4)
				lcount=1;
			
			if(lcount==0)
				lcount=3;
		break;
			
			case 1:
				
			if(change==0)
			{
				
					if (lcount==0)
					{
					tftlcd_draw_rectangle(10,110,50,140,Green);
					sprintf(b,"%d",ipvl[0]);	
					GUI_Text(12, 118, b ,Black,Green);
					}
					else
					{
					tftlcd_draw_rectangle(10,110,50,140,Black);
						sprintf(b,"%d",ipvl[0]);	
					GUI_Text(15, 118,b ,White,Black);
					}
					
					
					if (lcount==1)
					{
					tftlcd_draw_rectangle(60,110,100,140,Green);
						sprintf(b,"%d",ipvl[1]);	
					GUI_Text(65, 118, b,Black,Green);
					}
					else
					{
					tftlcd_draw_rectangle(60,110,100,140,Black);
						sprintf(b,"%d",ipvl[1]);	
					GUI_Text(65, 118,b,White,Black);
					}
					
					
					
					if (lcount==2)
					{
					tftlcd_draw_rectangle(110,110,150,140,Green);
						sprintf(b,"%d",ipvl[2]);	
					GUI_Text(115, 118, b,Black,Green);
					}
					else
					{
					tftlcd_draw_rectangle(110,110,150,140,Black);
						sprintf(b,"%d",ipvl[2]);	
					GUI_Text(115, 118,b,White,Black);
					}
			
					
					if (lcount==3)
					{
					tftlcd_draw_rectangle(160,110,200,140,Green);
						sprintf(b,"%d",ipvl[3]);	
					GUI_Text(165, 118,b,Black,Green);
					}
					else
					{
					tftlcd_draw_rectangle(160,110,200,140,Black);
						sprintf(b,"%d",ipvl[3]);	
					GUI_Text(165, 118,b,White,Black);
					}
			change=1;
				
			}
			
			
			
		if((!(GPIO_ReadInputDataBit(BACK_PORT, BACK_PIN)))&(dif_count1()))
			{
				change=0;
				setms_timecount(MENU_B_D);
				setms_timecount1(1000);
				if(lcount==0)
				{
				menu_state=0;
				lcount=1;	
				setip=1;
				LCD_Clear(White);
				}
				else
				lcount--;
				
			}
			
			if(dif_count())
			{
				change=0;
				menu_state=0;
				lcount=1;	
				setip=1;
				LCD_Clear(White);
				
			}
			if((!(GPIO_ReadInputDataBit(ENTER_PORT, ENTER_PIN)))&(dif_count1()))
			{
				change=0;
				setms_timecount(MENU_B_D);
			  setms_timecount1(1000);
				if(lcount==3)
				{
				menu_state=0;	
					lcount=1;
					setip=1;
			ipv[0]=	ipvl[0];
			ipv[1]=	ipvl[1];
			ipv[2]=	ipvl[2];
			ipv[3]=	ipvl[3];
					
				LCD_Clear(White);
					
					
				}
				else
				lcount++;
				
			}		
			
			
			if((!(GPIO_ReadInputDataBit(LEFT_PORT, LEFT_PIN)))& (ipv[lcount]<=255)&(dif_count1()))
			{
			ipvl[lcount]++;
			setms_timecount(MENU_B_D);
			change=0;	
			setms_timecount1(1000);
			}	
			
			if((!(GPIO_ReadInputDataBit(RIGHT_PORT, RIGHT_PIN)))& (ipv[lcount]>=0)&(dif_count1()))
			{
			ipvl[lcount]--;
			setms_timecount(MENU_B_D);
			change=0;	
			setms_timecount1(1000);
			}	
			break;
			case 2:
				
			
			Digital_show(0);
			if((!(GPIO_ReadInputDataBit(ENTER_PORT, ENTER_PIN)))|(!(GPIO_ReadInputDataBit(BACK_PORT, BACK_PIN)))|(dif_count()))
			{
				change=0;
				setip=1;
					menu_state=0;	
					LCD_Clear(White);
				}	
			
			
			break;
			case 3:
				ADC_show(0);
			if((!(GPIO_ReadInputDataBit(ENTER_PORT, ENTER_PIN)))|(!(GPIO_ReadInputDataBit(BACK_PORT, BACK_PIN)))|(dif_count()))
			{
				change=0;
				setip=1;
					menu_state=0;	
				LCD_Clear(White);
				}	
			
			
			break;				

	
	}
	}
}

/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/



int main(void)
{
uint8_t ip_s[4];
	
	STMFLASH_Read(IP_SAVE,(u16*)ip_s,4);
	if((ip_s[0]==0xff)&(ip_s[1]==0xff)&(ip_s[2]==0xff)&(ip_s[3]==0xff))
	{
	STMFLASH_Write(IP_SAVE,(u16*)myip,4);
	}
	else
	{
	myip[0]=ip_s[0];
	myip[1]=ip_s[1];	
	myip[2]=ip_s[2];
	myip[3]=ip_s[3];		
	}
	relay_init();
	SPI1_Init();
	adc_init();
 	input_init();
	pwm_init();
	key_init();
  delay_init();
	if((!(GPIO_ReadInputDataBit(MENU_PORT, MENU_PIN))))
	{
		ip_Set_act=1;
	}
  LCD_Initializtion();
  LCD_BackLight_Init();
  LCD_Clear(White);

	
	
	
	

	xTaskCreate( ETH_Task , ( signed char * ) NULL , 1500 , NULL , 3 , NULL );
  xTaskCreate( Poll_Handle , ( signed char * ) NULL , 500 , NULL ,2, NULL );
	xTaskCreate( GUI_Task , ( signed char * ) NULL , 1024 , NULL ,2, NULL );
  vTaskStartScheduler();	
  while (1);

}



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
