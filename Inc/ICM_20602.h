/*
 * ICM_20602.h
 *
 *  Created on: 2019/05/07
 *      Author: sf199
 */

#ifndef ICM_20602_H_
#define ICM_20602_H_

#include <stdint.h>
#include "record.h"



typedef struct {

float omega_x;

float omega_y;

float omega_z;

float accel_x;

float accel_y;

float accel_z;

}GYRO_DATA;



extern GYRO_DATA gyro;

float angle,a_speed;
float angle_speed,angle_speed0;
float angle_acceleration;
float anglex,a_speedx,angle_speedx;

float acc0,gf_speed,gf_distance;
float angle_speed_ave[10];


void ICM20602_init( void );

void ICM20602_DataUpdate( void );

void reset_ICM(void);

void interrupt_ICM(void);


#endif /* ICM_20602_H_ */
