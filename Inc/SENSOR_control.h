/*
 * SENSOR_control.h
 *
 *  Created on: 2019/06/20
 *      Author: sf199
 */

#ifndef SENSOR_CONTROL_H_
#define SENSOR_CONTROL_H_

#include "main.h"
#include "record.h"

uint16_t g_ADCBuffer[6];
char ADstop;
char sensor_mode;

uint16_t SEN_on[5];
uint16_t SEN_off[5];
int SEN[5][20];
int SEND[5];
int SENAve[5];



float V_batt;
uint16_t V_battAD;

void callback_SENSOR();

void sensor_line();


#endif /* SENSOR_CONTROL_H_ */
