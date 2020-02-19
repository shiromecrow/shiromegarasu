/*
 * IEH2-4096.c
 *
 *  Created on: 2019/05/21
 *      Author: sf199
 */

#include "tim.h"
#include "IEH2-4096.h"
#include "define.h"

int16_t count_encoderR(void) {
	int16_t count = 0;
	uint16_t enc_count = TIM1->CNT;
	TIM1->CNT = 0;

	if (enc_count > 32767) {
		count = (int16_t) enc_count;
	} else {
		count = (int16_t) enc_count;
	}

	return count;
}
int16_t count_encoderL(void) {
	int16_t count = 0;
	uint16_t enc_count = TIM3->CNT;
	TIM3->CNT = 0;

	if (enc_count > 32767) {
		count = -(int16_t) enc_count;
	} else {
		count = -(int16_t) enc_count;
	}

	return count;
}

void reset_distance(void) {

	all_countR = 0;
	all_countL = 0;

}
void encoder_speed(void) {
	E_speedR0 = E_speedR;
	E_speedL0 = E_speedL;
	one_countR = count_encoderR();
	one_countL = count_encoderL();

	E_speedR = (float) (one_countR) * tireR * 1000 * pi / 4 / 4096 / 40 * 11
			* 1000;
	E_speedL = (float) (one_countL) * tireR * 1000 * pi / 4 / 4096 / 40 * 11
			* 1000;

	record_in_enc();
}
void encoder_distance(void) {
	all_countR += one_countR;
	all_countL += one_countL;
	E_distanceR = (float) (all_countR) * tireR * 1000 * pi / 4 / 4096 / 40 * 11;
	E_distanceL = (float) (all_countL) * tireR * 1000 * pi / 4 / 4096 / 40 * 11;

}

void encoder_acceleration(void) {

	E_accelerationR = (E_speedR - E_speedR0) * 1000;
	E_accelerationL = (E_speedL - E_speedL0) * 1000;

}
