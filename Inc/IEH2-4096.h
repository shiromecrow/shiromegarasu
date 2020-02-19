/*
 * IEH2-4096.h
 *
 *  Created on: 2019/05/21
 *      Author: sf199
 */

#ifndef IEH2_4096_H_
#define IEH2_4096_H_

#include "record.h"

int32_t all_countR;
int32_t all_countL;
int32_t one_countR;
int32_t one_countL;

int16_t count_encoderR();
int16_t count_encoderL();


float E_distanceR,E_distanceL;
float E_speedR,E_speedL;
float E_speedR0,E_speedL0;
float E_accelerationR,E_accelerationL;



void reset_distance();
void encoder_distance();
void encoder_speed();
void encoder_acceleration();

#endif /* IEH2_4096_H_ */
