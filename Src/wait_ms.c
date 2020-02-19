/*
 * wait_ms.c
 *
 *  Created on: 2019/05/07
 *      Author: sf199
 */

#include "tim.h"

volatile uint32_t g_timCount;

void wait_ms(uint32_t waitTime) {

        g_timCount = 0;
        __HAL_TIM_SET_COUNTER(&htim6, 0);
        while (g_timCount < waitTime) {
        }

}

