/*
 * record.c
 *
 *  Created on: 2019/07/06
 *      Author: sf199
 */

#include "record.h"

void record_reset(void) {
	record_mode_enc = 0;
	record_mode_gyro = 0;
	record_mode_sensor = 0;
	p = 0;
	q = 0;
	o = 0;
}

void record_in_enc(void) {
	if (record_mode_enc == 1) {
		record1[p] = E_speedR;
		record2[p] = E_speedL;
		record3[p] = (E_speedR + E_speedL) / 2;
		record4[p] = ideal_speed;
		record5[p] = angle_speed;
		record6[p] = angle;

//		record1[p] = Ksp*(ideal_speed - (E_speedR + E_speedL) / 2);
//				record2[p] = Ksi*enc.sigma_error;
//				record3[p] =Ksd*enc.delta_error;
//				record4[p]=PID_stra;
//				record5[p] = (record_ideal_speed[p] / V_batt * MAXMOTOR);
//				record6[p]=(float) (duty_R);
		p++;
	}
}

void record_in_gyro(void) {
	if (record_mode_gyro == 1) {
			record1[q] = angle_speed;
			record2[q]=Turn_ideal_speed;
			record3[q] = angle;
//					record4[q] = -E_speedL;
//					record5[q]=(E_speedR+E_speedL)/2;
//					record6[q] = ideal_speed;
//		record1[q] = Ksp*(ideal_speed - (E_speedR + E_speedL) / 2);
//			record2[q]=Ksi*enc.sigma_error;
//			record3[q] = Ksd*enc.delta_error;
//					record4[q] = Ktp * (Turn_ideal_speed - angle_speed);
//					record5[q]=Kti * Gyro.sigma_error;
//					record6[q] = Ktd*Gyro.delta_error;

		q++;
	}
}

void record_in_sen(void) {
	int sensor_num = 0;
	if (record_mode_sensor == 1) {
		for (sensor_num = 0; sensor_num <= 4; sensor_num++) {
			SEN_record[sensor_num][o]=SEN[sensor_num][0];
			SEN_recordD[sensor_num][o]=SEND[sensor_num];
		}
		record1[o] = (E_distanceR+E_distanceL)/2;
//		record2[o] = (float)(slantRSEN);
//		record3[o] = (float)(slantLSEN);
//		SEN_recordD[0][o]=SEND[0];
//		SEN_recordD[4][o]=SEND[4];

		o++;
	}
}

void record_out_enc(void) {

	for (a = 0; a <= p; a++) {
		printf("%d,%f,%f,%f,%f,%f,%f\n", a, record1[a], record2[a], record3[a],
				record4[a], record5[a], record6[a]);
	}
}

void record_out_gyro(void) {
	for (a = 0; a <= q; a++) {
		printf("%d,%f,%f,%f\n", a,record1[a], record2[a],record3[a]);
	}
}

void record_out_sen(void) {
	for (a = 0; a <= o; a++) {
//		printf("%f,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", record1[a], SEN_record[0][a],
//				SEN_recordD[0][a], SEN_record[1][a], SEN_recordD[1][a],
//				SEN_record[2][a], SEN_recordD[2][a], SEN_record[3][a],
//				SEN_recordD[3][a], SEN_record[4][a], SEN_recordD[4][a]);
		printf("%d,%f,%d,%d,%d,%d\n", a, record1[a], SEN_record[1][a],SEN_record[0][a],SEN_record[3][a],SEN_record[4][a]);
	}
}
