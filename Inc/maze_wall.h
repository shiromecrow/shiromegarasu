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

unsigned short row[15]; //�Ǐ��@��
unsigned short column[15]; //�Ǐ��@�s
unsigned short row_look[15]; //�Ǐ��@��@�m�F�������ǂ���
unsigned short column_look[15]; //�Ǐ��@�s�@�m�F�������ǂ���
unsigned short shift1; //�V�t�g���Z�p
unsigned short shift2; //�V�t�g���Z�p
unsigned short walk_count[256]; //��������锠
unsigned short walk_count_slant[480]; //��������锠
unsigned char walk_direction[256]; //�����̕��p
unsigned char coordinate; //���W
unsigned short count_number; //�����̒l

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
