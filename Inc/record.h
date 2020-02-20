/*
 * record.h
 *
 *  Created on: 2019/07/06
 *      Author: sf199
 */

#ifndef RECORD_H_
#define RECORD_H_

#include "ICM_20602.h"
#include "IEH2-4096.h"
#include "SENSOR_control.h"
#include "motor_control.h"


int a;

char record_mode_sensor;
int o;
int SEN_record[5][15];
int SEN_recordD[5][15];



float record1[10000];
float record2[20];
float record3[20];
char record_mode_gyro;
int q;


float record4[40];//í«è]óp
float record5[40];//í«è]óp
float record6[40];
int record_mode_enc;
int p;


void record_reset(void);

void record_in_enc(void);

void record_in_gyro(void);

void record_in_sen(void);

void record_out_enc(void);

void record_out_gyro(void);

void record_out_sen(void);




#endif /* RECORD_H_ */
