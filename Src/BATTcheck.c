/*
 * BATTcheck.c
 *
 *  Created on: 2019/05/16
 *      Author: sf199
 */


#include "adc.h"
#include "tim.h"
#include "BATTcheck.h"
#include "main.h"
#include "define.h"
#include "wait_ms.h"

volatile char speakermode;

void battcheak(void){



	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 50);
	battAD = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);
	batt = 3.3  * (float) battAD / 4095.0 * (100.0 + 50.0) / 50.0;
	if(batt <= 7.5){
	HAL_TIM_Base_Stop_IT(&htim2);
	speakermode=0;
		HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
		while(1){
		r_blue_on;
		l_blue_on;
		wait_ms(500);
		r_blue_off;
				l_blue_off;
				wait_ms(500);
		}
	}


}




