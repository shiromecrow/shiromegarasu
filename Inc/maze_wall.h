/*
 * maze_wall.h
 *
 *  Created on: 2019/07/02
 *      Author: sf199
 */

#ifndef MAZE_WALL_H_
#define MAZE_WALL_H_

#include"define.h"
#include"main.h"

typedef struct{
	uint16_t row[15];
	uint16_t column[15];
	uint16_t row_look[15];
	uint16_t column_look[15];

}WALL;

WALL record;

unsigned short row[15]; //壁情報　列
unsigned short column[15]; //壁情報　行
unsigned short row_look[15]; //壁情報　列　確認したかどうか
unsigned short column_look[15]; //壁情報　行　確認したかどうか
unsigned short shift1; //シフト演算用
unsigned short shift2; //シフト演算用
unsigned short walk_count[256]; //歩数いれる箱
unsigned short walk_count_slant[480]; //歩数いれる箱
unsigned char walk_direction[256]; //歩数の方角
unsigned char coordinate; //座標
unsigned short count_number; //歩数の値

unsigned char Xcheak_result;
unsigned char Ycheak_result;
unsigned char Xcoordinate;
unsigned char Ycoordinate;
unsigned short wall_north;
unsigned short wall_south;
unsigned short wall_east;
unsigned short wall_west;
unsigned short front_count;
unsigned short left_count;
unsigned short right_count;
unsigned short back_count;
unsigned short count_box[40];
unsigned char box;
unsigned short count_boxnext[40];
unsigned char boxnext;



void maze_clear();

void maze_maker(int,int,int,int,int,int);
void maze_maker2(int,int,int,int,int,int);
void maze_makerhosuu(int,int,int);
void maze_makerST(int);
void maze_makerRun(int,int,int,int,int,int);
void maze_makeronly(int,int,int,int,int,int);
void maze_makerback(int,int,int,int,int,int);
void maze_makerslant(void);

void maze_display();


#endif /* MAZE_WALL_H_ */
