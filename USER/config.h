/*
  ******************************************************************************
  * @file   		 Config.h
  * @author  		alireza roozitalab
  * @version 		V0.0.1
  * @date    		10-azar-1394
  * @brief   		for gonfig pins
	* @project  	mr kokabi home automative solution
	******************************************************************************
	*/


#ifndef _CONFIG_H
#define _CONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif
	 
	 

	 
	 
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include  <stdint.h>
#include "misc.h"
#include "stm32f10x_exti.h"
	 
	 
	 
//-----------------------------------------------------------------TCP POLL

#define MAXREG_RO 10
#define MAXREG_RW 5

#define MAX_REG  (MAXREG_RO+MAXREG_RW)
	 
//------------------------------------------------------------------MODBUS CONFIG PINS
#define RX_PIN               	 	GPIO_Pin_10
#define RX_PORT            		 	GPIOA
#define RX_GPIO_CLK            	RCC_APB2Periph_GPIOA


#define TX_PIN               	  GPIO_Pin_9
#define TX_PORT            			GPIOA
#define TX_GPIO_CLK             RCC_APB2Periph_GPIOA


#define DE_PIN               	  GPIO_Pin_2
#define DE_PORT            			GPIOB
#define DE_GPIO_CLK             RCC_APB2Periph_GPIOB

	
#define OPEN_UASRT 							USART1 	
#define IRQ_UASRT 							USART1_IRQn
	
	
	
#define  MODBUS_BUF_SIZE  			50

//-----------------------------------------------------------------realy
#define RELAY1_PIN               	 	GPIO_Pin_2
#define RELAY1_PORT            		 	GPIOE
#define RELAY1_GPIO_CLK            	RCC_APB2Periph_GPIOE


#define RELAY2_PIN               	 	GPIO_Pin_3
#define RELAY2_PORT            		 	GPIOE
#define RELAY2_GPIO_CLK            	RCC_APB2Periph_GPIOE

#define RELAY3_PIN               	 	GPIO_Pin_6
#define RELAY3_PORT            		 	GPIOF
#define RELAY3_GPIO_CLK            	RCC_APB2Periph_GPIOF

#define RELAY4_PIN               	 	GPIO_Pin_1
#define RELAY4_PORT            		 	GPIOF
#define RELAY4_GPIO_CLK            	RCC_APB2Periph_GPIOF


	
	//-----------------------------------------------------------------DIGITAL input
#define INPUT1_PIN               	 	GPIO_Pin_7
#define INPUT1_PORT            		 	GPIOG
#define INPUT1_GPIO_CLK            	RCC_APB2Periph_GPIOG


#define INPUT2_PIN               	 	GPIO_Pin_6
#define INPUT2_PORT            		 	GPIOG
#define INPUT2_GPIO_CLK            	RCC_APB2Periph_GPIOG

#define INPUT3_PIN               	 	GPIO_Pin_5
#define INPUT3_PORT            		 	GPIOG
#define INPUT3_GPIO_CLK            	RCC_APB2Periph_GPIOG

#define INPUT4_PIN               	 	GPIO_Pin_4
#define INPUT4_PORT            		 	GPIOG
#define INPUT4_GPIO_CLK            	RCC_APB2Periph_GPIOG


#define INPUT5_PIN               	 	GPIO_Pin_3
#define INPUT5_PORT            		 	GPIOG
#define INPUT5_GPIO_CLK            	RCC_APB2Periph_GPIOG


#define INPUT6_PIN               	 	GPIO_Pin_2
#define INPUT6_PORT            		 	GPIOG
#define INPUT6_GPIO_CLK            	RCC_APB2Periph_GPIOG


#define INPUT7_PIN               	 	GPIO_Pin_8
#define INPUT7_PORT            		 	GPIOG
#define INPUT7_GPIO_CLK            	RCC_APB2Periph_GPIOG


#define INPUT8_PIN               	 	GPIO_Pin_6
#define INPUT8_PORT            		 	GPIOC
#define INPUT8_GPIO_CLK            	RCC_APB2Periph_GPIOC

#define INPUT9_PIN               	 	GPIO_Pin_7
#define INPUT9_PORT            		 	GPIOC
#define INPUT9_GPIO_CLK            	RCC_APB2Periph_GPIOC


#define INPUT10_PIN               	 	GPIO_Pin_8
#define INPUT10_PORT            		 	GPIOC
#define INPUT10_GPIO_CLK            	RCC_APB2Periph_GPIOC


#define INPUT11_PIN               	 	GPIO_Pin_9
#define INPUT11_PORT            		 	GPIOC
#define INPUT11_GPIO_CLK            	RCC_APB2Periph_GPIOC

#define INPUT12_PIN               	 	GPIO_Pin_8
#define INPUT12_PORT            		 	GPIOA
#define INPUT12_GPIO_CLK            	RCC_APB2Periph_GPIOA
//------------------------------------------------------------ANALOG IN
	
#define C_INPUT1_PIN               	 	GPIO_Pin_0
#define C_INPUT1_PORT            		 	GPIOC
#define C_INPUT1_GPIO_CLK            	RCC_APB2Periph_GPIOC
#define C_INPUT1_CH            				ADC_Channel_10


#define C_INPUT2_PIN               	 	GPIO_Pin_1
#define C_INPUT2_PORT            		 	GPIOC
#define C_INPUT2_GPIO_CLK            	RCC_APB2Periph_GPIOC
#define C_INPUT2_CH            				ADC_Channel_11


#define C_INPUT3_PIN               	 	GPIO_Pin_2
#define C_INPUT3_PORT            		 	GPIOC
#define C_INPUT3_GPIO_CLK            	RCC_APB2Periph_GPIOC
#define C_INPUT3_CH            				ADC_Channel_12



#define C_INPUT4_PIN               	 	GPIO_Pin_3
#define C_INPUT4_PORT            		 	GPIOC
#define C_INPUT4_GPIO_CLK            	RCC_APB2Periph_GPIOC
#define C_INPUT4_CH            				ADC_Channel_13



#define C_INPUT5_PIN               	 	GPIO_Pin_4
#define C_INPUT5_PORT            		 	GPIOC
#define C_INPUT5_GPIO_CLK            	RCC_APB2Periph_GPIOC
#define C_INPUT5_CH            				ADC_Channel_14


#define C_INPUT6_PIN               	 	GPIO_Pin_5
#define C_INPUT6_PORT            		 	GPIOC
#define C_INPUT6_GPIO_CLK            	RCC_APB2Periph_GPIOC
#define C_INPUT6_CH            				ADC_Channel_15
	
	
#define C_INPUT7_PIN               	 	GPIO_Pin_0
#define C_INPUT7_PORT            		 	GPIOB
#define C_INPUT7_GPIO_CLK            	RCC_APB2Periph_GPIOB
#define C_INPUT7_CH            				ADC_Channel_8	
	
//-----------------------------------------------------------------TIMER CONFIG
#define TIME_PERIOD               	  (uint16_t) (SystemCoreClock / 1000) - 1

//-------------------------------------------------------MENU KEY
#define LEFT_PIN                  GPIO_Pin_12
#define LEFT_PORT								  GPIOF

#define RIGHT_PIN                 GPIO_Pin_13
#define RIGHT_PORT								GPIOF

#define ENTER_PIN                 GPIO_Pin_14
#define ENTER_PORT								GPIOF

#define MENU_PIN                  GPIO_Pin_15
#define MENU_PORT									GPIOF
	 
#define BACK_PIN                  GPIO_Pin_11
#define BACK_PORT									GPIOF
//------------------------------------------------------------------ 
	 



#define TICK_PPS					1000


#if (TICK_PPS<1000)

	#define  ms_devider			1
	#define  ms_multiple		(1000/TICK_PPS)
	#define  us_devider			1
	#define  us_multiple		(1000000/TICK_PPS)
	
#endif

#if (TICK_PPS>=1000)&&(TICK_PPS<=1000000)

	#define  ms_devider			(TICK_PPS/1000)
	#define  ms_multiple		1
	#define  us_devider			1
	#define  us_multiple		(1000000/TICK_PPS)
#endif

#if (TICK_PPS>1000000)

	#define  ms_devider			(TICK_PPS/1000)
	#define  ms_multiple		1
	#define  us_devider			(TICK_PPS/1000000)
	#define  us_multiple		1
	
#endif

#ifdef __cplusplus
}
#endif

#endif 
