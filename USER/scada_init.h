

#ifndef _SCADAINIT_H
#define _SCADAINIT_H

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include  <stdint.h>
#include "misc.h"
#include "stm32f10x_exti.h"
	 









void relay_init(void);
void input_init(void);
void adc_init(void);
void pwm_init(void);
void key_init(void);

#endif

#ifdef __cplusplus
}
#endif

