/*
 * maze_strategy.h
 *
 *  Created on: 2019/07/02
 *      Author: sf199
 */

#ifndef MAZE_STRATEGY_H_
#define MAZE_STRATEGY_H_

#include "parameter.h"

int x;
int y;
int wall_control;
int SENF_maze, SENR_maze, SENL_maze;
int direction;
char slalom_mode;

char maze_mode;
int kitikukan;
int no_safty;
int highspeed_mode;
int error_mode;

int pass[255]; //1f 2r 3l
//unsigned short front_count;
//unsigned short left_count;
//unsigned short right_count;
//unsigned short back_count;
//unsigned short walk_count[256];
//unsigned short row[15];
//unsigned short column[15];
//unsigned short row_look[15];
//unsigned short column_look[15];
int gg;



void maze_clean(void);
void record_in(void);
void record_out(void);

void left_way(void);

void decision_kitiku(void);
void compress_kitiku(void);


void adati_wayreturn(float,float,float,float);

void adati_wayreturnSL(float,float,float,float,float,float,float,float,float,float,float,float,float);
void adati_wayonlybackSL(float,float,float,float,float,float,float,float,float,float,float,float,float,int);



void most_speed(float,float,int,char,char,parameter_speed);
void most_speed3(float,float,int);
//void most_speedSlant(float,float);
void most_speed_kitikukan(char);
void most_speed_kitikukan_play(float,float);


#endif /* MAZE_STRATEGY_H_ */
