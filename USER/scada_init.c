
/*********************************************************************************************************
*
* File                : scada_init.c
* Version             : V1.0
* By                  : alireza roozitalab
* email               : alireza.roozitalab@gmail.com
* git user            : ARoozitalab
*                                                
*                                          All Rights Reserved
*
*********************************************************************************************************/


#include  "scada_init.h"
#include  "config.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_adc.h"
#include "misc.h"
vu16 ADC_ConvertedValue[7];




/*******************************************************************************
* Function Name  : relay_init
* Description    : init output pins for relay
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void relay_init(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;
RCC_APB2PeriphClockCmd(RELAY1_GPIO_CLK| RELAY2_GPIO_CLK|RELAY3_GPIO_CLK|RELAY4_GPIO_CLK|RCC_APB2Periph_GPIOG,ENABLE); 						 				

	
	//-----------LED ON BEREAD BOARD
	
	  GPIO_InitStructure.GPIO_Pin = RELAY1_PIN;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(RELAY1_PORT, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOA, GPIO_Pin_0);
	
	GPIO_InitStructure.GPIO_Pin = RELAY2_PIN;	  
  GPIO_Init(RELAY2_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = RELAY3_PIN;	  
  GPIO_Init(RELAY3_PORT, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = RELAY4_PIN;	  
  GPIO_Init(RELAY4_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	  
  GPIO_Init(GPIOG, &GPIO_InitStructure);

}








/*******************************************************************************
* Function Name  : input_init
* Description    : init digital input pins
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/

void input_init(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
  
 RCC_APB2PeriphClockCmd(INPUT1_GPIO_CLK| INPUT2_GPIO_CLK|INPUT3_GPIO_CLK|INPUT4_GPIO_CLK|INPUT5_GPIO_CLK
												|INPUT6_GPIO_CLK|INPUT7_GPIO_CLK|INPUT8_GPIO_CLK|INPUT9_GPIO_CLK|INPUT10_GPIO_CLK
												|INPUT11_GPIO_CLK|INPUT12_GPIO_CLK,ENABLE); 						 				

	

}
 
/*******************************************************************************
* Function Name  : adc_init
* Description    : analog pins init
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void adc_init()
{
	
	  GPIO_InitTypeDef GPIO_InitStructure;
	  ADC_InitTypeDef ADC_InitStructure;
  DMA_InitTypeDef DMA_InitStructure;
	RCC_APB2PeriphClockCmd(C_INPUT1_GPIO_CLK| C_INPUT2_GPIO_CLK|C_INPUT3_GPIO_CLK|C_INPUT4_GPIO_CLK|C_INPUT5_GPIO_CLK
												|C_INPUT6_GPIO_CLK|C_INPUT7_GPIO_CLK,ENABLE); 	
												
	GPIO_InitStructure.GPIO_Pin = C_INPUT1_PIN;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  
  GPIO_Init(C_INPUT1_PORT, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = C_INPUT2_PIN;	  
  GPIO_Init(C_INPUT2_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = C_INPUT3_PIN;	  
  GPIO_Init(C_INPUT3_PORT, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = C_INPUT4_PIN;	  
  GPIO_Init(C_INPUT4_PORT, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = C_INPUT5_PIN;	  
  GPIO_Init(C_INPUT5_PORT, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = C_INPUT6_PIN;	  
  GPIO_Init(C_INPUT6_PORT, &GPIO_InitStructure);
	

	GPIO_InitStructure.GPIO_Pin = C_INPUT7_PIN;	  
  GPIO_Init(C_INPUT7_PORT, &GPIO_InitStructure);


  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_AFIO, ENABLE);
  /* DMA channel1 configuration ----------------------------------------------*/
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR;
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ADC_ConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 7;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
  /* Enable DMA1 channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);
    
  /* ADC1 configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 7;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel8 configuration */ 
  ADC_RegularChannelConfig(ADC1, C_INPUT1_CH, 1, ADC_SampleTime_71Cycles5);
  ADC_RegularChannelConfig(ADC1, C_INPUT2_CH, 2, ADC_SampleTime_71Cycles5);
	ADC_RegularChannelConfig(ADC1, C_INPUT3_CH, 3, ADC_SampleTime_71Cycles5);
  ADC_RegularChannelConfig(ADC1, C_INPUT4_CH, 4, ADC_SampleTime_71Cycles5);
  ADC_RegularChannelConfig(ADC1, C_INPUT5_CH, 5, ADC_SampleTime_71Cycles5);
  ADC_RegularChannelConfig(ADC1, C_INPUT6_CH, 6, ADC_SampleTime_71Cycles5);
  ADC_RegularChannelConfig(ADC1, C_INPUT7_CH, 7, ADC_SampleTime_71Cycles5);
//	ADC_RegularChannelConfig(ADC1, C_V_CH, 9, ADC_SampleTime_55Cycles5);

  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 reset calibaration register */   
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibaration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
     
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);	
	
}



/*******************************************************************************
* Function Name  : pwm_init
* Description    : pwm pins init
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void pwm_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE); 						 				

	

	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);



  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  /* -----------------------------------------------------------------------
    TIM3CLK = 36 MHz, Prescaler = 35, TIM3 counter clock = 1 MHz
    TIM3 ARR Register = 999 => TIM3 Frequency = TIM3 counter clock/(ARR + 1)
    TIM3 Frequency = 1 KHz.
    TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR)* 100 
----------------------------------------------------------------------- */


//-----TIMER2
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;  
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseStructure.TIM_Prescaler = 35; 
  TIM_TimeBaseStructure.TIM_Period = 1021;  
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0; 
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;


  TIM_OC2Init(TIM2, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);   

	
	

  TIM_OC3Init(TIM2, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  




  TIM_ARRPreloadConfig(TIM2, ENABLE); 
  TIM_Cmd(TIM2, ENABLE);
	
}


/*******************************************************************************
* Function Name  : key_init
* Description    : user key init
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/

void key_init()
{
		  GPIO_InitTypeDef GPIO_InitStructure;
	  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);

//	

	
	
	GPIO_InitStructure.GPIO_Pin = LEFT_PIN;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
  GPIO_Init(LEFT_PORT, &GPIO_InitStructure);
	
	
	
	
	GPIO_InitStructure.GPIO_Pin = RIGHT_PIN;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
  GPIO_Init(RIGHT_PORT, &GPIO_InitStructure);
	
	
	
	
	GPIO_InitStructure.GPIO_Pin = ENTER_PIN;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
  GPIO_Init(ENTER_PORT, &GPIO_InitStructure);
	
	
		GPIO_InitStructure.GPIO_Pin = BACK_PIN;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
  GPIO_Init(BACK_PORT, &GPIO_InitStructure);
	
	
	
	
			GPIO_InitStructure.GPIO_Pin = MENU_PIN;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
  GPIO_Init(MENU_PORT, &GPIO_InitStructure);
	
	
	
	
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOF, GPIO_PinSource15);
  EXTI_InitStructure.EXTI_Line = EXTI_Line15;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising ;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
 // EXTI_GenerateSWInterrupt(EXTI_LINE_VSYNC_CMOS);

  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	
	
	
}



