/*
 * parameter.h
 *
 *  Created on: 2019/11/18
 *      Author: sf199
 */

#ifndef PARAMETER_H_
#define PARAMETER_H_

typedef struct {
	float g_speed;
		float f_ofset;
		float e_ofset;
		float t_speed;
		float t_acc;
} parameter;


typedef struct {

parameter slalom_R;
parameter slalom_L;
parameter turn90_R;
parameter turn90_L;
parameter turn180_R;
parameter turn180_L;
parameter turn45in_R;
parameter turn45in_L;
parameter turn135in_R;
parameter turn135in_L;
parameter turn45out_R;
parameter turn45out_L;
parameter turn135out_R;
parameter turn135out_L;
parameter V90_R;
parameter V90_L;

}parameter_speed;

parameter_speed speed500;
parameter_speed speed800;
parameter_speed speed1000;
parameter_speed speed1200;

void input_parameter();



//ifndef PARAMETER_H_
//#define PARAMETER_H_
//
//typedef struct {
//	float g_speed;
//		float f_ofset;
//		float e_ofset;
//		float t_speed;
//		float t_acc;
//} parameter;
//
//
//struct parameter_speed{
//
//parameter slalom_R;
//parameter slalom_L;
//parameter turn90_R;
//parameter turn90_L;
//parameter turn180_R;
//parameter turn180_L;
//parameter turn45in_R;
//parameter turn45in_L;
//parameter turn135in_R;
//parameter turn135in_L;
//parameter turn45out_R;
//parameter turn45out_L;
//parameter turn135out_R;
//parameter turn135out_L;
//parameter V90_R;
//parameter V90_L;
//
//};
//
//struct parameter_speed speed500;
//struct parameter_speed speed800;
//struct parameter_speed speed1000;
//struct parameter_speed speed1200;
//
//void input_parameter();





#endif /* PARAMETER_H_ */
