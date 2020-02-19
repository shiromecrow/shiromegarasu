/*
 * motor_control.h
 *
 *  Created on: 2019/06/20
 *      Author: sf199
 */

#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

#include "tim.h"
#include "ICM_20602.h"
#include "IEH2-4096.h"
#include "motor_control.h"
#include "SENSOR_control.h"
#include "yellow_LED.h"
#include "define.h"
#include"maze_wall.h"
#include"maze_strategy.h"


struct PID{

	float error;
	float old_error;
	float sigma_error;
	float delta_error;

};

struct PID enc;
struct PID Gyro;

struct gain{


};


uint32_t m_timCount;

int duty_R, duty_L;

float Avespeed;
float start_speed, end_speed, max_speed, acceleration;
float Turn_start_speed, Turn_end_speed, Turn_max_speed, Turn_acceleration;
float ideal_speed, ideal_distance, ideal_acceleration;
float Turn_ideal_speed, Turn_ideal_distance, Turn_ideal_acceleration;

//mode一覧
char modeacc;
char straight_mode;
char turning_mode;
char wall_control_mode;
char wall_status;
char status_change;
int count_stay;
int count_stay2;
char No_wall_modeR;
char No_wall_modeL;
char No_wall_modeR2;
char No_wall_modeL2;
char No_wall_modeRslant;
char No_wall_modeLslant;
int no_wall_timeR;
int no_wall_timeL;
int no_wall_timeR2;
int no_wall_timeL2;
int no_wall_timeRslant;
int no_wall_timeLslant;
int pulse_turnR_mode,pulse_turnL_mode;//幅寄せのやつ
int pulse_time;
float pulse_speed;
float input_pulse_speed;

//mode一覧

//PIDのグローバル変数
float PID_all_R;
float PID_all_L;
float PID_stra;
float PID_turn;
float PID_wall;
float SEN_distanceL,SEN_distanceR;
float s_disR,s_disL;
float slant_dis;
int slant_start;
int slantRSEN, slantLSEN;

float s_P,s_I,s_D;
//PIDのグローバル変数

//float PID_straight();
//float PID_turning();
//float PID_right();
//float PID_left();
void motor_PID();


void get_duty(float, float);
void get_duty2(int, int);
void const_accel(float, float, float);
void straight_const_accel(float,float, float, float);

void const_speed(float, float);
void const_speed_mazemake(float, float);
void const_speed_mazemakeback(float,float);
void const_speed_kitiku(float, float);

void const_speed_wallcut45(float,float,float);
void const_speed_wallcut90(float,float,float);
void const_speed_wallcutslantR(float,float,float);
void const_speed_wallcutslantL(float,float,float);


void interupt_const_accel();

void straight_table(float, float, float,float,float);
void no_move(float);
void no_angle();

void interupt_angle_const_accel();

void turning_accel(float,float,float,float);
void turningtable_accel(float,float,float,float);
void turning_speed(float, float);
void turning_table(float, float, float,float,float);

void interupt_slalom_const_accel();

void slalom_accel(float,float,float,float);
void slalomtable_accel(float,float,float,float);
void slalom_speed(float, float);
void slalom_table(float, float, float,float);

#endif /* MOTOR_CONTROL_H_ */
