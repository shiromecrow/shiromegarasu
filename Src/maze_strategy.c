/*
 * maze_strategy.c
 *
 *  Created on: 2019/07/02
 *      Author: sf199
 */

/*
 * maze_strategy.c
 *
 *  Created on: 2018/07/11
 *      Author: sf199
 */

#include"motor_control.h"
#include"define.h"
#include"turning.h"
#include"maze_strategy.h"
#include"maze_wall.h"
#include"flash.h"

extern short SEN1[21];
extern short SEN2[21];
extern short SEN3[21];
extern short SEN4[21];
extern int SEN1_Ave1, SEN1_Ave2;
extern int SEN2_Ave1, SEN2_Ave2;
extern int SEN3_Ave1, SEN3_Ave2;
extern int SEN4_Ave1, SEN4_Ave2;
extern int SEN1_change, SEN2_change, SEN3_change, SEN4_change;

//extern char highspeed_mode;
//extern int safe;
//extern int mode_safty;
//extern char slant_direction;
//extern char slant_count;
//
//unsigned short row_record[15];
//unsigned short column_record[15];
//unsigned short row_record_look[15];
//unsigned short column_record_look[15];

int do_move;
unsigned short shift5 = 1;
unsigned short kakuninn;
unsigned short wall_N;
unsigned short wall_S;
unsigned short wall_E;
unsigned short wall_W;
unsigned short wall_f;
unsigned short wall_r;
unsigned short wall_l;
unsigned short look_f;
unsigned short look_l;
unsigned short look_r;
unsigned short fb_control;
unsigned short rl_control;

unsigned char min;
unsigned char min_coordinate;

unsigned char pass_count;

int x_change;
int y_change;

int hosuu = 0;
char first_most = 0;
char kitiku;
int kitiku_distance;
char know_road = 0;
float first_v;
float last_v;

//拡張左手法**************************************************
//
//unsigned short shift = 1;
//
//unsigned short aa;
//unsigned short bb;
//
int t = 0;

//int way = 0;
//int p = 0;
//int s = 0;
//int q = 0;
//char last_slant;
//char slant_break;
//拡張左手法***********************************************
void maze_clean(void) {
	x = 0;
	y = 0;
	direction = 1;
	t = 0;
	while (t <= 14) {
		row[t] = record.row[t];
		column[t] = record.column[t];
		row_look[t] = record.row_look[t];
		column_look[t] = record.column_look[t];
		t++;
	}
	t = 0;

}
void record_in(void) {
	t = 0;
	while (t <= 14) {
		record.row[t] = row[t];
		record.column[t] = column[t];
		t++;
	}
	t = 0;
	while (t <= 14) {
		record.row_look[t] = row_look[t];
		record.column_look[t] = column_look[t];
		t++;
	}
	t = 0;
	writeFlash(start_address, (uint16_t*) record.row, sizeof(record.row), ON);
	writeFlash(start_address + sizeof(record.row), (uint16_t*) record.column,
			sizeof(record.column), OFF);
	writeFlash(start_address + 2 * sizeof(record.row),
			(uint16_t*) record.row_look, sizeof(record.row_look),
			OFF);
	writeFlash(start_address + 3 * sizeof(record.row),
			(uint16_t*) record.column_look, sizeof(record.column_look),
			OFF);
}
void record_out(void) {
	loadFlash(start_address, (uint16_t*) record.row, sizeof(record.row));
	loadFlash(start_address + sizeof(record.row), (uint16_t*) record.column,
			sizeof(record.column));
	loadFlash(start_address + 2 * sizeof(record.row),
			(uint16_t*) record.row_look, sizeof(record.row_look));
	loadFlash(start_address + 3 * sizeof(record.row),
			(uint16_t*) record.column_look, sizeof(record.column_look));

	t = 0;
	while (t <= 14) {
		row[t] = record.row[t];
		column[t] = record.column[t];
		t++;
	}
	t = 0;
	while (t <= 14) {
		row_look[t] = record.row_look[t];
		column_look[t] = record.column_look[t];
		t++;
	}

	t = 0;

}
void decision_kitiku(void) {
	switch (direction) {
	case 1:

		if (y >= 14) {
		} else {

			shift5 = 1;
			shift5 = shift5 << x;
			look_f = column_look[y + 1] & shift5;
			if (look_f >= 1) {
				shift5 = 1;
				shift5 = shift5 << (y + 1);
				look_f = row_look[x] & shift5;
			}
			if (x == 0 || look_f == 0) {
			} else {
				shift5 = 1;
				shift5 = shift5 << (y + 1);
				look_f = row_look[x - 1] & shift5;
			}

		}

		break;
	case 2:

		if (x >= 14) {
		} else {
			shift5 = 1;
			shift5 = shift5 << y;
			look_f = row_look[x + 1] & shift5;
			if (look_f >= 1) {
				shift5 = 1;
				shift5 = shift5 << (x + 1);
				look_f = column_look[y] & shift5;
			}
			if (y == 0 || look_f == 0) {
			} else {
				shift5 = 1;
				shift5 = shift5 << (x + 1);
				look_f = column_look[y - 1] & shift5;
			}
		}
		break;
	case 3:

		if (y <= 0) {
		} else {

			shift5 = 1;
			shift5 = shift5 << (y - 1);
			look_f = row_look[x] & shift5;

			if (y <= 1 || look_f == 0) {
			} else {
				shift5 = 1;
				shift5 = shift5 << x;
				look_f = column_look[y - 2] & shift5;
			}
			if (x == 0 || look_f == 0) {
			} else {
				shift5 = 1;
				shift5 = shift5 << (y - 1);
				look_f = row_look[x - 1] & shift5;
			}
		}
		break;

	case 4:

		if (x <= 0) {
		} else {

			shift5 = 1;
			shift5 = shift5 << (x - 1);
			look_f = column_look[y] & shift5;

			if (x <= 1 || look_f == 0) {
			} else {
				shift5 = 1;
				shift5 = shift5 << y;
				look_f = row_look[x - 2] & shift5;
			}
			if (y == 0 || look_f == 0) {
			} else {
				shift5 = 1;
				shift5 = shift5 << (x - 1);
				look_f = column_look[y - 1] & shift5;
			}
		}
		break;

	}

	//ここでOFFできるぞ

	if (SENF_maze >= f_presence) {
		front_count = 255;
	}
	if (SENR_maze >= r_presence) {
		right_count = 255;
	}
	if (SENL_maze >= l_presence) {
		left_count = 255;
	}

	if (SENF_maze < f_presence && look_f != 0 && front_count <= right_count
			&& front_count <= left_count && front_count <= back_count) {
		kitikukan = 1;
	} else {
		kitikukan = 0;
	}
//	if (look_f == 0 || SENF_maze >= f_presence || front_count >= right_count
//			|| front_count >= left_count || front_count >= back_count) {
//		kitikukan = 0;
//	} else {
//		kitikukan = 1;
//	}

}

void compress_kitiku(void) {
	kitiku_distance = 1;
	kitiku = 1;
	while (1) {

		switch (direction) {
		case 1:
			y++;
			break;
		case 2:
			x++;
			break;
		case 3:
			y--;
			break;
		case 4:
			x--;
			break;

		}
		switch (direction) {
		case 1:
			if (y == 15) {
			} else {

				if (y == 14) {
					look_f = 1;
				} else {
					shift5 = 1;
					shift5 = shift5 << x;
					look_f = column_look[y + 1] & shift5;
					if (look_f >= 1) {
						shift5 = 1;
						shift5 = shift5 << (y + 1);
						look_f = row_look[x] & shift5;
					}
					if (x == 0 || look_f == 0) {
					} else {
						shift5 = 1;
						shift5 = shift5 << (y + 1);
						look_f = row_look[x - 1] & shift5;
					}
				}
			}
			if (x == 0) {
				look_l = 1;
			} else {

				shift5 = 1;
				shift5 = shift5 << (x - 1);
				look_l = column_look[y] & shift5;

				if (x <= 1 || look_l == 0) {
				} else {
					shift5 = 1;
					shift5 = shift5 << y;
					look_l = row_look[x - 2] & shift5;
				}
				if (y == 0 || look_l == 0) {
				} else {
					shift5 = 1;
					shift5 = shift5 << (x - 1);
					look_l = column_look[y - 1] & shift5;
				}

			}
			if (x == 15) {
				look_r = 1;
			} else {

				if (x == 14) {
				} else {
					shift5 = 1;
					shift5 = shift5 << y;
					look_r = row_look[x + 1] & shift5;
					if (look_r >= 1) {
						shift5 = 1;
						shift5 = shift5 << (x + 1);
						look_r = column_look[y] & shift5;
					}
					if (y == 0 || look_l == 0) {
					} else {
						shift5 = 1;
						shift5 = shift5 << (x + 1);
						look_r = column_look[y - 1] & shift5;
					}
				}
			}

			break;
		case 2:
			if (x == 15) {
				look_f = 1;
			} else {

				if (x == 14) {
				} else {
					shift5 = 1;
					shift5 = shift5 << y;
					look_f = row_look[x + 1] & shift5;
					if (look_f >= 1) {
						shift5 = 1;
						shift5 = shift5 << (x + 1);
						look_f = column_look[y] & shift5;
					}
					if (y == 0 || look_f == 0) {
					} else {
						shift5 = 1;
						shift5 = shift5 << (x + 1);
						look_f = column_look[y - 1] & shift5;
					}
				}
			}
			if (y == 15) {
				look_l = 1;
			} else {

				if (y == 14) {
				} else {
					shift5 = 1;
					shift5 = shift5 << x;
					look_l = column_look[y + 1] & shift5;
					if (look_l >= 1) {
						shift5 = 1;
						shift5 = shift5 << (y + 1);
						look_l = row_look[x] & shift5;
					}
					if (x == 0 || look_l == 0) {
					} else {
						shift5 = 1;
						shift5 = shift5 << (y + 1);
						look_l = row_look[x - 1] & shift5;
					}
				}
			}
			if (y == 0) {
				look_r = 1;
			} else {

				shift5 = 1;
				shift5 = shift5 << (y - 1);
				look_r = row_look[x] & shift5;

				if (y <= 1 || look_r == 0) {
				} else {
					shift5 = 1;
					shift5 = shift5 << x;
					look_r = column_look[y - 2] & shift5;
				}
				if (x == 0 || look_r == 0) {
				} else {
					shift5 = 1;
					shift5 = shift5 << (y - 1);
					look_r = row_look[x - 1] & shift5;
				}

			}

			break;
		case 3:
			if (y == 0) {
				look_f = 1;
			} else {

				shift5 = 1;
				shift5 = shift5 << (y - 1);
				look_f = row_look[x] & shift5;

				if (y <= 1 || look_f == 0) {
				} else {
					shift5 = 1;
					shift5 = shift5 << x;
					look_f = column_look[y - 2] & shift5;
				}
				if (x == 0 || look_f == 0) {
				} else {
					shift5 = 1;
					shift5 = shift5 << (y - 1);
					look_f = row_look[x - 1] & shift5;
				}

			}
			if (x == 15) {
				look_l = 1;
			} else {

				if (x == 14) {
				} else {
					shift5 = 1;
					shift5 = shift5 << y;
					look_l = row_look[x + 1] & shift5;
					if (look_l >= 1) {
						shift5 = 1;
						shift5 = shift5 << (x + 1);
						look_l = column_look[y] & shift5;
					}
					if (y == 0 || look_l == 0) {
					} else {
						shift5 = 1;
						shift5 = shift5 << (x + 1);
						look_l = column_look[y - 1] & shift5;
					}
				}
			}
			if (x == 0) {
				look_r = 1;
			} else {

				shift5 = 1;
				shift5 = shift5 << (x - 1);
				look_r = column_look[y] & shift5;

				if (x <= 1 || look_r == 0) {
				} else {
					shift5 = 1;
					shift5 = shift5 << y;
					look_r = row_look[x - 2] & shift5;
				}
				if (y == 0 || look_r == 0) {
				} else {
					shift5 = 1;
					shift5 = shift5 << (x - 1);
					look_r = column_look[y - 1] & shift5;
				}

			}

			break;

		case 4:
			if (x == 0) {
				look_f = 1;
			} else {

				shift5 = 1;
				shift5 = shift5 << (x - 1);
				look_f = column_look[y] & shift5;

				if (x <= 1 || look_f == 0) {
				} else {
					shift5 = 1;
					shift5 = shift5 << y;
					look_f = row_look[x - 2] & shift5;
				}
				if (y == 0 || look_f == 0) {
				} else {
					shift5 = 1;
					shift5 = shift5 << (x - 1);
					look_f = column_look[y - 1] & shift5;
				}

			}
			if (y == 0) {
				look_l = 1;
			} else {

				shift5 = 1;
				shift5 = shift5 << (y - 1);
				look_l = row_look[x] & shift5;

				if (y <= 1 || look_l == 0) {
				} else {
					shift5 = 1;
					shift5 = shift5 << x;
					look_l = column_look[y - 2] & shift5;
				}
				if (x == 0 || look_l == 0) {
				} else {
					shift5 = 1;
					shift5 = shift5 << (y - 1);
					look_l = row_look[x - 1] & shift5;
				}

			}
			if (y == 15) {
				look_r = 1;
			} else {

				if (y == 14) {
				} else {
					shift5 = 1;
					shift5 = shift5 << x;
					look_r = column_look[y + 1] & shift5;
					if (look_r >= 1)
						shift5 = 1;
					shift5 = shift5 << (y + 1);
					look_r = row_look[x] & shift5;
					if (x == 0 || look_r == 0) {
					} else {
						shift5 = 1;
						shift5 = shift5 << (y + 1);
						look_r = row_look[x - 1] & shift5;
					}
				}
			}

			break;

		}

		shift5 = 1;
		shift5 = shift5 << x;
		if (y <= 14) {
			wall_N = column[y] & shift5;
		} else {
			wall_N = 1;
		}
		shift5 = 1;
		shift5 = shift5 << x;
		if (y >= 1) {
			wall_S = column[y - 1] & shift5;
		} else {
			wall_S = 1;
		}

		shift5 = 1;
		shift5 = shift5 << y;
		if (x <= 14) {
			wall_E = row[x] & shift5;
		} else {
			wall_E = 1;
		}

		shift5 = 1;
		shift5 = shift5 << y;
		if (x >= 1) {
			wall_W = row[x - 1] & shift5;
		} else {
			wall_W = 1;
		}
		shift5 = 1;

		switch (direction) {
		case 1:
			wall_f = wall_N;
			wall_l = wall_W;
			wall_r = wall_E;
			if (y == 15) {
				front_count = 255;
			} else {
				front_count = walk_count[16 * x + y + 1];

			}
			if (x == 0) {
				left_count = 255;
			} else {
				left_count = walk_count[16 * (x - 1) + y];
			}
			if (x == 15) {
				right_count = 255;
			} else {
				right_count = walk_count[16 * (x + 1) + y];
			}
			if (y == 0) {
				back_count = 255;
			} else {
				back_count = walk_count[16 * x + y - 1];
			}
			break;
		case 2:
			wall_f = wall_E;
			wall_l = wall_N;
			wall_r = wall_S;
			if (x == 15) {
				front_count = 255;
			} else {
				front_count = walk_count[16 * (x + 1) + y];
			}
			if (y == 15) {
				left_count = 255;
			} else {
				left_count = walk_count[16 * x + y + 1];
			}
			if (y == 0) {
				right_count = 255;
			} else {
				right_count = walk_count[16 * x + y - 1];
			}
			if (x == 0) {
				back_count = 255;
			} else {
				back_count = walk_count[16 * (x - 1) + y];
			}
			break;
		case 3:
			wall_f = wall_S;
			wall_l = wall_E;
			wall_r = wall_W;
			if (y == 0) {
				front_count = 255;
			} else {
				front_count = walk_count[16 * x + y - 1];
			}
			if (x == 15) {
				left_count = 255;
			} else {
				left_count = walk_count[16 * (x + 1) + y];
			}
			if (x == 0) {
				right_count = 255;
			} else {
				right_count = walk_count[16 * (x - 1) + y];
			}
			if (y == 15) {
				back_count = 255;
			} else {
				back_count = walk_count[16 * x + y + 1];
			}

			break;
		case 4:
			wall_f = wall_W;
			wall_l = wall_S;
			wall_r = wall_N;
			if (x == 0) {
				front_count = 255;
			} else {
				front_count = walk_count[16 * (x - 1) + y];
			}
			if (y == 0) {
				left_count = 255;
			} else {
				left_count = walk_count[16 * x + y - 1];
			}
			if (y == 15) {
				right_count = 255;
			} else {
				right_count = walk_count[16 * x + y + 1];
			}
			if (x == 15) {
				back_count = 255;
			} else {
				back_count = walk_count[16 * (x + 1) + y];
			}
			break;

		}
		if (walk_count[16 * x + y] <= 1) {

			break;
		}

		if (wall_f == 0 && wall_l >= 1 && wall_r >= 1) {
			if (look_f == 0) {
				kitiku = 0;
				break;
			}
			kitiku_distance = kitiku_distance + 2;

		}

		if (wall_f >= 1) {
			break;
		}

		if (wall_f == 0 && wall_l == 0 && wall_r >= 1) {
			if (front_count >= left_count) {
				kitiku = 0;
				break;
			}

			if (look_f == 0) {
				kitiku = 0;
				break;
			}
			kitiku_distance = kitiku_distance + 2;

		}
		if (wall_f == 0 && wall_l >= 1 && wall_r == 0) {
			if (front_count >= right_count) {
				kitiku = 0;
				break;
			}

			if (look_f == 0) {
				kitiku = 0;
				break;
			}
			kitiku_distance = kitiku_distance + 2;

		}
		if (wall_f == 0 && wall_l == 0 && wall_r == 0) {
			if (front_count >= right_count || front_count >= left_count) {
				kitiku = 0;
				break;
			}
			if (look_f == 0) {
				kitiku = 0;
				break;
			}
			kitiku_distance = kitiku_distance + 2;

		}
		if (wall_f >= 1 && wall_l >= 1 && wall_r >= 1) {
			break;
		}

		if (direction == 5) {
			direction = 1;
		}
		if (direction == 6) {
			direction = 2;
		}
		if (direction == 0) {
			direction = 4;
		}
		if (direction == -1) {
			direction = 3;
		}
		if (kitiku == 0) {

			break;
		}

	}

	switch (direction) {
	case 1:
		y--;
		break;
	case 2:
		x--;
		break;
	case 3:
		y++;
		break;
	case 4:
		x++;
		break;

	}

}

void adati_wayreturn(float inspeed, float inanglespeed, float inacc,
		float inangleacc) {
	maze_mode = 1; //***************************************************************************************
	Avespeed = 700;
	STBYON;
	HAL_Delay(500);

	SENF_maze = SENAve[2];
	SENR_maze = SENAve[1];
	SENL_maze = SENAve[3];
	x = 0;
	y = 0;
	maze_maker2(direction, SENF_maze, SENL_maze, SENR_maze, x, y);

	//back_clean(100, 200); //ケツ当て
	//traight3(30, 200);
	//rotationrightNocontrol(91, 280);

	//back_clean(100, 200);
	//straight3(30, 200);
	//rotationleftNocontrol(91, 280);
	HAL_Delay(100);

	//wall_control = 0; //壁制御ON
	wall_control_mode = 1;
	straight_table(90 + 39.5, 0, inspeed, inspeed, inacc); //半区画前進

	while (1) {

		//straight_table2(90, 300, 300, 500);

		switch (direction) {		//方向における座標更新
		case 1:
			y++;
			break;
		case 2:
			x++;
			break;
		case 3:
			y--;
			break;
		case 4:
			x--;
			break;

		}

		SENF_maze = SENAve[2];
		SENR_maze = SENAve[1];
		SENL_maze = SENAve[3];

		const_speed_mazemake(20, inspeed);

		switch (direction) {		//
		case 1:
			if (y == 15) {
			} else {
				front_count = walk_count[16 * x + y + 1];
			}
			if (x == 0) {
			} else {
				left_count = walk_count[16 * (x - 1) + y];
			}
			if (x == 15) {
			} else {
				right_count = walk_count[16 * (x + 1) + y];
			}
			if (y == 0) {
			} else {
				back_count = walk_count[16 * x + y - 1];
			}
			break;
		case 2:
			if (x == 15) {
			} else {
				front_count = walk_count[16 * (x + 1) + y];
			}
			if (y == 15) {
			} else {
				left_count = walk_count[16 * x + y + 1];
			}
			if (y == 0) {
			} else {
				right_count = walk_count[16 * x + y - 1];
			}
			if (x == 0) {
			} else {
				back_count = walk_count[16 * (x - 1) + y];
			}
			break;
		case 3:
			if (y == 0) {
			} else {
				front_count = walk_count[16 * x + y - 1];
			}
			if (x == 15) {
			} else {
				left_count = walk_count[16 * (x + 1) + y];
			}
			if (x == 0) {
			} else {
				right_count = walk_count[16 * (x - 1) + y];
			}
			if (y == 15) {
			} else {
				back_count = walk_count[16 * x + y + 1];
			}

			break;
		case 4:
			if (x == 0) {
			} else {
				front_count = walk_count[16 * (x - 1) + y];
			}
			if (y == 0) {
			} else {
				left_count = walk_count[16 * x + y - 1];
			}
			if (y == 15) {
			} else {
				right_count = walk_count[16 * x + y + 1];
			}
			if (x == 15) {
			} else {
				back_count = walk_count[16 * (x + 1) + y];
			}
			break;

		}

		//	straight_table(70, inspeed,inspeed,inspeed,inacc);
		if (x == 0 && y == 0) {
			break;
		}		//XX//
		if ((x == goal_x && y == goal_y) || (x == goal_x + 1 && y == goal_y)
				|| (x == goal_x && y == goal_y + 1)
				|| (x == goal_x + 1 && y == goal_y + 1)) {
			while (SENF_maze < f_presence) {
				straight_table(160, inspeed, inspeed, inspeed, inacc);
				switch (direction) {		//方向における座標更新
				case 1:
					y++;
					break;
				case 2:
					x++;
					break;
				case 3:
					y--;
					break;
				case 4:
					x--;
					break;

				}

				SENF_maze = SENAve[2];
				SENR_maze = SENAve[1];
				SENL_maze = SENAve[3];

				const_speed_mazemake(20, inspeed);

				switch (direction) {		//
				case 1:
					if (y == 15) {
					} else {
						front_count = walk_count[16 * x + y + 1];
					}
					if (x == 0) {
					} else {
						left_count = walk_count[16 * (x - 1) + y];
					}
					if (x == 15) {
					} else {
						right_count = walk_count[16 * (x + 1) + y];
					}
					if (y == 0) {
					} else {
						back_count = walk_count[16 * x + y - 1];
					}
					break;
				case 2:
					if (x == 15) {
					} else {
						front_count = walk_count[16 * (x + 1) + y];
					}
					if (y == 15) {
					} else {
						left_count = walk_count[16 * x + y + 1];
					}
					if (y == 0) {
					} else {
						right_count = walk_count[16 * x + y - 1];
					}
					if (x == 0) {
					} else {
						back_count = walk_count[16 * (x - 1) + y];
					}
					break;
				case 3:
					if (y == 0) {
					} else {
						front_count = walk_count[16 * x + y - 1];
					}
					if (x == 15) {
					} else {
						left_count = walk_count[16 * (x + 1) + y];
					}
					if (x == 0) {
					} else {
						right_count = walk_count[16 * (x - 1) + y];
					}
					if (y == 15) {
					} else {
						back_count = walk_count[16 * x + y + 1];
					}

					break;
				case 4:
					if (x == 0) {
					} else {
						front_count = walk_count[16 * (x - 1) + y];
					}
					if (y == 0) {
					} else {
						left_count = walk_count[16 * x + y - 1];
					}
					if (y == 15) {
					} else {
						right_count = walk_count[16 * x + y + 1];
					}
					if (x == 15) {
					} else {
						back_count = walk_count[16 * (x + 1) + y];
					}
					break;

				}

			}
			straight_table(70, inspeed, 0, inspeed, inacc); //半区画前進

			//turning_table(180, 0, 0, inanglespeed, inangleacc);
			HAL_Delay(400);
			slalom_table(180, 0, inanglespeed, inangleacc);
			HAL_Delay(200);
			no_safty = 1;
			straight_table(-90, 0, 0, -200, -inacc); //半区画後退
			HAL_Delay(100);
			maze_mode = 0;
			no_safty = 0;

			enc.sigma_error = 0;
			Gyro.sigma_error = 0;
			angle = 0;
			wall_control_mode = 1;
			reset_ICM();
			maze_mode = 1;
			//straight_table(39.5, 0, 0, inspeed, inacc);
			//	HAL_Delay(500);
			direction = direction + 2;

			if (direction == 5) {
				direction = 1;
			}
			if (direction == 6) {
				direction = 2;
			}
			if (direction == 0) {
				direction = 4;
			}
			if (direction == -1) {
				direction = 3;
			}
			break;
		}
		kitikukan = 0;
		if (kitikukan == OFF) {
			do_move = 0;

			if (SENF_maze >= f_presence) {
				front_count = 255;
			}
			if (SENR_maze >= r_presence) {
				right_count = 255;
			}
			if (SENL_maze >= l_presence) {
				left_count = 255;
			}

			if (SENF_maze < f_presence) {
				if (front_count <= right_count && front_count <= left_count
						&& front_count <= back_count) {
					wall_control_mode = 1;
					straight_table(160, inspeed, inspeed, inspeed, inacc); //半区画前進
//					wall_control_mode = 0;
//					straight_table(50, inspeed, inspeed, inspeed, inacc);
					wall_control_mode = 1;
					do_move = 1;
				}
			}
			if (SENR_maze < r_presence) {
				if (right_count < front_count && right_count <= left_count
						&& right_count <= back_count) {
					slalomR(speed500.slalom_R, OFF);
					direction++;
					do_move = 1;
				}
			}
			if (SENL_maze < l_presence) {
				if (left_count < front_count && left_count < right_count
						&& left_count <= back_count) {
					slalomL(speed500.slalom_L, OFF);
					direction--;
					do_move = 1;
				}
			}
			if (do_move == 0) {
				if (SENF_maze >= f_presence) {
					straight_table(70, inspeed, 0, inspeed, inacc); //半区画前進
					//turning_table(180, 0, 0, inanglespeed, inangleacc);
					HAL_Delay(400);
					slalom_table(180, 0, inanglespeed, inangleacc);
					HAL_Delay(200);
					no_safty = 1;
					straight_table(-90, 0, 0, -200, -inacc); //半区画後退
					no_safty = 0;
					HAL_Delay(600);
					enc.sigma_error = 0;
					Gyro.sigma_error = 0;
					angle = 0;
					wall_control_mode = 0;
					straight_table(39.5 + 90, 0, inspeed, inspeed, inacc);
					wall_control_mode = 1;
					direction = direction + 2;
				} else {
					wall_control_mode = 0;
					straight_table(70, inspeed, 0, inspeed, inacc); //半区画前進
					//turning_table(-180, 0, 0, -inanglespeed, -inangleacc);
					HAL_Delay(400);
					slalom_table(-180, 0, -inanglespeed, -inangleacc);
					HAL_Delay(200);
					no_safty = 1;
					straight_table(-39.5 - 12, 0, 0, -200, -inacc); //半区画後退
					no_safty = 0;
					HAL_Delay(500);
					wall_control_mode = 0;
					straight_table(39.5 + 90, 0, inspeed, inspeed, inacc);
					wall_control_mode = 1;
					direction = direction + 2;
				}
			}

		} else {
			const_speed_kitiku(70, inspeed);
			wall_control_mode = 1;
			straight_table((90 * kitiku_distance), inspeed, inspeed, 1000,
					5000);

		}

		if (direction == 5) {
			direction = 1;
		}
		if (direction == 6) {
			direction = 2;
		}
		if (direction == 0) {
			direction = 4;
		}
		if (direction == -1) {
			direction = 3;
		}
//基地区間**********************************************************************
//		if (know_road == 1) {
//			most_speed_kitikukan_play(850, 1600);
//		}
//基地区間

	}
	record_in();
//	HAL_Delay(200);
	straight_table(90 + 39.5, 0, inspeed, inspeed, inacc);
	while (1) {

		//straight_table2(90, 300, 300, 500);

		SENF_maze = SENAve[2];
		SENR_maze = SENAve[1];
		SENL_maze = SENAve[3];

		switch (direction) {
		case 1:
			y++;
			break;
		case 2:
			x++;
			break;
		case 3:
			y--;
			break;
		case 4:
			x--;
			break;

		}
		//		seg(x);

		const_speed_mazemakeback(20, inspeed); ///backni**************************

		switch (direction) {
		case 1:
			if (y == 15) {
			} else {
				front_count = walk_count[16 * x + y + 1];
			}
			if (x == 0) {
			} else {
				left_count = walk_count[16 * (x - 1) + y];
			}
			if (x == 15) {
			} else {
				right_count = walk_count[16 * (x + 1) + y];
			}
			if (y == 0) {
			} else {
				back_count = walk_count[16 * x + y - 1];
			}
			break;
		case 2:
			if (x == 15) {
			} else {
				front_count = walk_count[16 * (x + 1) + y];
			}
			if (y == 15) {
			} else {
				left_count = walk_count[16 * x + y + 1];
			}
			if (y == 0) {
			} else {
				right_count = walk_count[16 * x + y - 1];
			}
			if (x == 0) {
			} else {
				back_count = walk_count[16 * (x - 1) + y];
			}
			break;
		case 3:
			if (y == 0) {
			} else {
				front_count = walk_count[16 * x + y - 1];
			}
			if (x == 15) {
			} else {
				left_count = walk_count[16 * (x + 1) + y];
			}
			if (x == 0) {
			} else {
				right_count = walk_count[16 * (x - 1) + y];
			}
			if (y == 15) {
			} else {
				back_count = walk_count[16 * x + y + 1];
			}

			break;
		case 4:
			if (x == 0) {
			} else {
				front_count = walk_count[16 * (x - 1) + y];
			}
			if (y == 0) {
			} else {
				left_count = walk_count[16 * x + y - 1];
			}
			if (y == 15) {
			} else {
				right_count = walk_count[16 * x + y + 1];
			}
			if (x == 15) {
			} else {
				back_count = walk_count[16 * (x + 1) + y];
			}
			break;

		}
		//straight_mazebreak(70, inspeed);

		if (x == 0 && y == 0) { ///////goal************************

			straight_table(70, inspeed, 0, inspeed, inacc); //半区画前進

			HAL_Delay(1000);
			maze_display();
			turning_table(180, 0, 0, inanglespeed, inangleacc);
			wall_control_mode = 1;
			direction = direction + 2;
			if (direction == 5) {
				direction = 1;
			}
			if (direction == 6) {
				direction = 2;
			}
			if (direction == 0) {
				direction = 4;
			}
			if (direction == -1) {
				direction = 3;
			}

			break;
		}
		//		straight_table_mazebreak(90, 300, 300, 500);

		//wall_cheak+direction********************************************

		//seg(y);
		//wall_cheak+direction********************************************
		kitikukan = 0;
		kitikukan = 0;
		if (kitikukan == OFF) {
			do_move = 0;

			if (SENF_maze >= f_presence) {
				front_count = 255;
			}
			if (SENR_maze >= r_presence) {
				right_count = 255;
			}
			if (SENL_maze >= l_presence) {
				left_count = 255;
			}

			if (SENF_maze < f_presence) {
				if (front_count <= right_count && front_count <= left_count
						&& front_count <= back_count) {
					wall_control_mode = 1;
					straight_table(160, inspeed, inspeed, inspeed, inacc); //半区画前進
					//					wall_control_mode = 0;
					//					straight_table(50, inspeed, inspeed, inspeed, inacc);
					wall_control_mode = 1;
					do_move = 1;
				}
			}
			if (SENR_maze < r_presence) {
				if (right_count < front_count && right_count <= left_count
						&& right_count <= back_count) {
					slalomR(speed500.slalom_R, OFF);
					direction++;
					do_move = 1;
				}
			}
			if (SENL_maze < l_presence) {
				if (left_count < front_count && left_count < right_count
						&& left_count <= back_count) {
					slalomL(speed500.slalom_L, OFF);
					direction--;
					do_move = 1;
				}
			}
			if (do_move == 0) {
				if (SENF_maze >= f_presence) {
					straight_table(70, inspeed, 0, inspeed, inacc); //半区画前進
					//turning_table(180, 0, 0, inanglespeed, inangleacc);
					HAL_Delay(400);
					slalom_table(180, 0, inanglespeed, inangleacc);
					HAL_Delay(200);
					no_safty = 1;
					straight_table(-90, 0, 0, -200, -inacc); //半区画後退
					no_safty = 0;
					HAL_Delay(600);
					enc.sigma_error = 0;
					Gyro.sigma_error = 0;
					angle = 0;
					wall_control_mode = 1;
					straight_table(39.5 + 90, 0, inspeed, inspeed, inacc);
					wall_control_mode = 1;
					direction = direction + 2;
				} else {
					wall_control_mode = 0;
					straight_table(70, inspeed, 0, inspeed, inacc); //半区画前進
					//turning_table(-180, 0, 0, -inanglespeed, -inangleacc);
					HAL_Delay(400);
					slalom_table(-180, 0, -inanglespeed, -inangleacc);
					HAL_Delay(200);
					no_safty = 1;
					straight_table(-39.5 - 12, 0, 0, -200, -inacc); //半区画後退
					no_safty = 0;
					HAL_Delay(500);
					wall_control_mode = 1;
					straight_table(39.5 + 90, 0, inspeed, inspeed, inacc);
					wall_control_mode = 1;
					direction = direction + 2;
				}
			}

		} else {
			const_speed_kitiku(70, inspeed);
			wall_control_mode = 1;
			straight_table((90 * kitiku_distance), inspeed, inspeed, 1000,
					5000);

		}

		enc.sigma_error = 0; ///XX//

		if (direction == 5) {
			direction = 1;
		}
		if (direction == 6) {
			direction = 2;
		}
		if (direction == 0) {
			direction = 4;
		}
		if (direction == -1) {
			direction = 3;
		}

//だ出ツール
//		if (red_switch == 0) {
//			while (green_switch == 1) {
//			}
//			while (green_switch == 0) {
//			}

	}
	STBYOFF; //MTU2.TSTR.BIT.CST0 = 0;
	maze_mode = 0;
	HAL_Delay(100);
	maze_display();
	if (error_mode == 0) {
		record_in();
	} else {
		record_out();
	}

}

void most_speed(float inspeed, float inacc, int stmass, char fun_mode,
		char slant_mode, parameter_speed howspeed) {
	unsigned char slant_count;
	int slant_direction;
	float f_speed, e_speed;

	x = 0;
	y = 0;
	direction = 1;
	t = 0;
	slant_direction = -2;

	//highspeed_mode = 1;
	while (t <= 255) {
		pass[t] = 0;

		t++;
	}

	t = 0;
	while (t <= 14) {
		record.row[t] = row[t];
		record.column[t] = column[t];
		t++;
	}
	t = 0;
	while (t <= 14) {
		record.row_look[t] = row_look[t];
		record.column_look[t] = column_look[t];
		t++;
	}

	t = 0;
	while (t <= 14) {
		row_look[t] = ~row_look[t];
		column_look[t] = ~column_look[t];
		t++;
	}
	t = 0;
	while (t <= 14) {
		row[t] = row[t] | row_look[t];
		column[t] = column[t] | column_look[t];
		t++;
	}

	t = 0;
	pass_count = 0;
//	maze_makerhosuu(direction, x, y);
	maze_makerST(stmass);
	maze_display();
	pass[0] = 1;
	while (1) {
//		if (mode_safty == 1) {
//
//			break;
//		}
		switch (direction) {
		case 1:
			y++;
			break;
		case 2:
			x++;
			break;
		case 3:
			y--;
			break;
		case 4:
			x--;
			break;

		}
//		seg(x);
//		wait(1000);
//		seg(y);
//		bit();
//		wait(1000);
//		clear();
		if (x == goal_x && y == goal_y) {
			if (pass[pass_count] >= 0) {
			} else {
				pass_count++;
			}
			pass[pass_count] = pass[pass_count] + 1;
//			wait(10);
//			maze_display();
//			x = 0;
//			y = 0;
			direction = direction + 2;
			if (direction == 5) {
				direction = 1;
			}
			if (direction == 6) {
				direction = 2;
			}
			if (direction == 0) {
				direction = 4;
			}
			if (direction == -1) {
				direction = 3;
			}
			break;
		}
		if (x == goal_x + 1 && y == goal_y + 1) {
			if (pass[pass_count] >= 0) {
			} else {
				pass_count++;
			}
			pass[pass_count] = pass[pass_count] + 1;
//			wait(10);
//			maze_display();
//			x = 0;
//			y = 0;
			direction = direction + 2;
			if (direction == 5) {
				direction = 1;
			}
			if (direction == 6) {
				direction = 2;
			}
			if (direction == 0) {
				direction = 4;
			}
			if (direction == -1) {
				direction = 3;
			}
			break;
		}
		if (x == goal_x + 1 && y == goal_y) {
			if (pass[pass_count] >= 0) {
			} else {
				pass_count++;
			}
			pass[pass_count] = pass[pass_count] + 1;
//			wait(10);
//			maze_display();
//			x = 0;
//			y = 0;
			direction = direction + 2;
			if (direction == 5) {
				direction = 1;
			}
			if (direction == 6) {
				direction = 2;
			}
			if (direction == 0) {
				direction = 4;
			}
			if (direction == -1) {
				direction = 3;
			}
			break;
		}
		if (x == goal_x && y == goal_y + 1) {
			if (pass[pass_count] >= 0) {
			} else {
				pass_count++;
			}
			pass[pass_count] = pass[pass_count] + 1;
//			wait(10);
//			maze_display();
//			x = 0;
//			y = 0;
			direction = direction + 2;
			if (direction == 5) {
				direction = 1;
			}
			if (direction == 6) {
				direction = 2;
			}
			if (direction == 0) {
				direction = 4;
			}
			if (direction == -1) {
				direction = 3;
			}
			break;
		}

		shift5 = 1;
		shift5 = shift5 << x;
		if (y <= 14) {
			wall_N = column[y] & shift5;
		} else {
			wall_N = 1;
		}
		shift5 = 1;
		shift5 = shift5 << x;
		if (y >= 1) {
			wall_S = column[y - 1] & shift5;
		} else {
			wall_S = 1;
		}

		shift5 = 1;
		shift5 = shift5 << y;
		if (x <= 14) {
			wall_E = row[x] & shift5;
		} else {
			wall_E = 1;
		}

		shift5 = 1;
		shift5 = shift5 << y;
		if (x >= 1) {
			wall_W = row[x - 1] & shift5;
		} else {
			wall_W = 1;
		}
		shift5 = 1;

		switch (direction) {
		case 1:
			wall_f = wall_N;
			wall_l = wall_W;
			wall_r = wall_E;
			if (y == 15) {
			} else {
				front_count = walk_count[16 * x + y + 1];

			}
			if (x == 0) {
			} else {
				left_count = walk_count[16 * (x - 1) + y];
			}
			if (x == 15) {
			} else {
				right_count = walk_count[16 * (x + 1) + y];
			}
			if (y == 0) {
			} else {
				back_count = walk_count[16 * x + y - 1];
			}
			break;
		case 2:
			wall_f = wall_E;
			wall_l = wall_N;
			wall_r = wall_S;
			if (x == 15) {
			} else {
				front_count = walk_count[16 * (x + 1) + y];
			}
			if (y == 15) {
			} else {
				left_count = walk_count[16 * x + y + 1];
			}
			if (y == 0) {
			} else {
				right_count = walk_count[16 * x + y - 1];
			}
			if (x == 0) {
			} else {
				back_count = walk_count[16 * (x - 1) + y];
			}
			break;
		case 3:
			wall_f = wall_S;
			wall_l = wall_E;
			wall_r = wall_W;
			if (y == 0) {
			} else {
				front_count = walk_count[16 * x + y - 1];
			}
			if (x == 15) {
			} else {
				left_count = walk_count[16 * (x + 1) + y];
			}
			if (x == 0) {
			} else {
				right_count = walk_count[16 * (x - 1) + y];
			}
			if (y == 15) {
			} else {
				back_count = walk_count[16 * x + y + 1];
			}

			break;
		case 4:
			wall_f = wall_W;
			wall_l = wall_S;
			wall_r = wall_N;
			if (x == 0) {
			} else {
				front_count = walk_count[16 * (x - 1) + y];
			}
			if (y == 0) {
			} else {
				left_count = walk_count[16 * x + y - 1];
			}
			if (y == 15) {
			} else {
				right_count = walk_count[16 * x + y + 1];
			}
			if (x == 15) {
			} else {
				back_count = walk_count[16 * (x + 1) + y];
			}
			break;

		}

		//		straight_table_mazebreak(90, 300, 300, 500);

		//wall_cheak+direction********************************************

		//seg(y);
		//wall_cheak+direction********************************************

		if (wall_f == 0 && wall_l >= 1 && wall_r >= 1) {
			if (pass[pass_count] >= 0) {
			} else {
				pass_count++;
			}
			pass[pass_count] = pass[pass_count] + 2;
		}

		if (wall_f >= 1 && wall_l == 0 && wall_r >= 1) {
			pass_count++;

			pass[pass_count] = -3;

			direction--;
		}

		if (wall_f >= 1 && wall_l >= 1 && wall_r == 0) {
			pass_count++;
			pass[pass_count] = -2;

			direction++;

		}

		if (wall_f >= 1 && wall_l == 0 && wall_r == 0) {
			if (right_count <= left_count) {
				pass_count++;
				pass[pass_count] = -2;

				direction++;
			} else {
				pass_count++;

				pass[pass_count] = -3;

				direction--;
			}

		}

		if (wall_f == 0 && wall_l == 0 && wall_r >= 1) {
			if (front_count <= left_count) {
				if (pass[pass_count] >= 0) {
				} else {
					pass_count++;
				}
				pass[pass_count] = pass[pass_count] + 2;
			} else {
				pass_count++;

				pass[pass_count] = -3;

				direction--;
			}

		}
		if (wall_f == 0 && wall_l >= 1 && wall_r == 0) {
			if (front_count <= right_count) {
				if (pass[pass_count] >= 0) {
				} else {
					pass_count++;
				}
				pass[pass_count] = pass[pass_count] + 2;

			} else {
				pass_count++;
				pass[pass_count] = -2;

				direction++;
			}

		}
		if (wall_f == 0 && wall_l == 0 && wall_r == 0) {
			if (front_count <= right_count && front_count <= left_count) {
				if (pass[pass_count] >= 0) {
				} else {
					pass_count++;
				}
				pass[pass_count] = pass[pass_count] + 2;

			} else {
				if (right_count <= left_count) {
					pass_count++;
					pass[pass_count] = -2;

					direction++;
				} else {
					pass_count++;

					pass[pass_count] = -3;

					direction--;
				}

			}

		}

		if (direction == 5) {
			direction = 1;
		}
		if (direction == 6) {
			direction = 2;
		}
		if (direction == 0) {
			direction = 4;
		}
		if (direction == -1) {
			direction = 3;
		}

//	seg(x);
//	bit();
//		wait(500);
//	clear();
//seg(y);
//		wait(500);

	}
	pass_count = 1;

	while (1) {		//パス圧縮
//		if (mode_safty == 1) {
//
//			break;
//		}
		if (pass[pass_count] == 0) {
			break;
		}

		if (pass[pass_count] == -2 && pass[pass_count - 1] >= 1	//右90度大回りの条件
		&& pass[pass_count + 1] >= 1) {
			pass[pass_count - 1] = pass[pass_count - 1] - 1;	//前90直進の削除
			pass[pass_count + 1] = pass[pass_count + 1] - 1;	//後90直進の削除
			pass[pass_count] = -4;		//右90度大回り

		}
		if (pass[pass_count] == -3 && pass[pass_count - 1] >= 1	//左90度大回りの条件
		&& pass[pass_count + 1] >= 1) {
			pass[pass_count - 1] = pass[pass_count - 1] - 1;	//前90直進の削除
			pass[pass_count + 1] = pass[pass_count + 1] - 1;	//後90直進の削除
			pass[pass_count] = -5;		//左90度大回り

		}
		if (pass[pass_count - 1] >= 1 && pass[pass_count] == -2
				&& pass[pass_count + 1] == -2 && pass[pass_count + 2] >= 1) {//右180度大回りの条件
			pass[pass_count - 1] = pass[pass_count - 1] - 1;
			pass[pass_count] = -6;
			pass[pass_count + 1] = -1;
			pass[pass_count + 2] = pass[pass_count + 2] - 1;

		}
		if (pass[pass_count - 1] >= 1 && pass[pass_count] == -3
				&& pass[pass_count + 1] == -3 && pass[pass_count + 2] >= 1) {//左180度大回りの条件
			pass[pass_count - 1] = pass[pass_count - 1] - 1;
			pass[pass_count] = -7;
			pass[pass_count + 1] = -1;
			pass[pass_count + 2] = pass[pass_count + 2] - 1;
		}
		if (pass[pass_count] == -2 && pass[pass_count - 1] == -3	//左90度大回りの条件

				) {
		}
//		if(){}
		if (pass[pass_count - 1] == 0) {
			pass[pass_count - 1] = -1;		//passが0になってしまったときの対策
		}

		pass_count++;
	}

	pass_count = 1;
	if (slant_mode == 1) {
		while (1) {		//斜め入出の圧縮
			if (pass[pass_count] == 0) {
				break;
			}

			if (pass[pass_count - 1] >= 1) {
				if (pass[pass_count] == -2 || pass[pass_count] == -3) {
//***************************************************************************************入りのモーションstart
					if (pass[pass_count] == -2 && pass[pass_count + 1] == -3) {
						pass[pass_count - 1] = pass[pass_count - 1] - 1;
						if (pass[pass_count - 1] == 0) {
							pass[pass_count - 1] = -1;	//passが0になってしまったときの対策
						}
						pass[pass_count] = -8;		//右45
					}
					if (pass[pass_count] == -3 && pass[pass_count + 1] == -2) {
						pass[pass_count - 1] = pass[pass_count - 1] - 1;
						if (pass[pass_count - 1] == 0) {
							pass[pass_count - 1] = -1;	//passが0になってしまったときの対策
						}
						pass[pass_count] = -9;		//左45
					}
					if (pass[pass_count] == -2 && pass[pass_count + 1] == -2) {
						pass[pass_count - 1] = pass[pass_count - 1] - 1;
						if (pass[pass_count - 1] == 0) {
							pass[pass_count - 1] = -1;	//passが0になってしまったときの対策
						}
						pass[pass_count] = -10;		//右135
						pass[pass_count + 1] = -1;
					}
					if (pass[pass_count] == -3 && pass[pass_count + 1] == -3) {
						pass[pass_count - 1] = pass[pass_count - 1] - 1;
						if (pass[pass_count - 1] == 0) {
							pass[pass_count - 1] = -1;	//passが0になってしまったときの対策
						}
						pass[pass_count] = -11;		//左135
						pass[pass_count + 1] = -1;
					}
//***************************************************************************************入りのモーションend

//***************************************************************************************途中のモーションstart
					while (pass[pass_count] <= -1) {
						pass_count++;
					}
//***************************************************************************************途中のモーションend

//***************************************************************************************出のモーションstart
					if (pass[pass_count - 1] == -2) {
						if (pass[pass_count - 2] == -2) {
							pass[pass_count] = pass[pass_count] - 1;
							if (pass[pass_count] == 0) {
								pass[pass_count] = -1;	//passが0になってしまったときの対策
							}
							pass[pass_count - 1] = -14;		//右135
							pass[pass_count - 2] = -1;
						} else {
							pass[pass_count] = pass[pass_count] - 1;
							if (pass[pass_count] == 0) {
								pass[pass_count] = -1;	//passが0になってしまったときの対策
							}
							pass[pass_count - 1] = -12;		//右45
						}

					}
					if (pass[pass_count - 1] == -3) {
						if (pass[pass_count - 2] == -3) {
							pass[pass_count] = pass[pass_count] - 1;
							if (pass[pass_count] == 0) {
								pass[pass_count] = -1;	//passが0になってしまったときの対策
							}
							pass[pass_count - 1] = -15;		//左135
							pass[pass_count - 2] = -1;
						} else {
							pass[pass_count] = pass[pass_count] - 1;
							if (pass[pass_count] == 0) {
								pass[pass_count] = -1;	//passが0になってしまったときの対策
							}
							pass[pass_count - 1] = -13;		//左45
						}

					}
//***************************************************************************************出のモーションend
				}
			}
			//		if(){}

			pass_count++;
		}

		pass_count = 1;
		while (1) {		//斜の圧縮
			if (pass[pass_count] == 0) {
				break;
			}

			if (pass[pass_count] == -8 || pass[pass_count] == -9
					|| pass[pass_count] == -10 || pass[pass_count] == -11) {
				if (pass[pass_count] == -8 || pass[pass_count] == -10) {
					slant_direction = -3;
				}
				if (pass[pass_count] == -9 || pass[pass_count] == -11) {
					slant_direction = -2;
				}
				pass_count++;
				if (pass[pass_count] == -1) {		//135ターンようのー１を進めるため
					pass_count++;
				}
				if (pass[pass_count] == -1) {		//135ターンようのー１を進めるため
					pass_count++;
				}
				if (pass[pass_count] >= -3) {
					slant_count = pass_count;
					pass[slant_count] = 51;
					pass_count++;
				}

				//***************************************************************************************途中のモーションstart
				while (pass[pass_count] >= -3) {
					if (pass[pass_count] == -1) {		//135ターンようのー１を進めるため
						pass_count++;
					}
					if (pass[pass_count] == -12 || pass[pass_count] == -13
							|| pass[pass_count] == -14
							|| pass[pass_count] == -15) {
						break;
					}
					if (pass[pass_count] == slant_direction) {
						pass[slant_count] = pass[slant_count] - 1;
						slant_count = pass_count;
						if (slant_direction == -2) {
							pass[pass_count] = -16;
						}
						if (slant_direction == -3) {
							pass[pass_count] = -17;
						}

					} else {
						if (pass[slant_count] >= 50) {
							pass[pass_count] = -1;
						} else {
							slant_count = pass_count;
							pass[slant_count] = 50;
						}
						pass[slant_count] = pass[slant_count] + 1;
						if (slant_direction == -2) {
							slant_direction = -3;
						} else {
							slant_direction = -2;
						}

					}

					pass_count++;
				}
				//***************************************************************************************途中のモーションend

			}

			//		if(){}

			pass_count++;
		}
	}
	t = 0;
	while (pass[t] != 0) {
		printf("pass_count %d pass %d\n", t, pass[t]);
		t++;
	}
	t = 0;

	HAL_Delay(500);
	STBYON;
	no_safty = 1;
	straight_table(-55, 0, 0, -200, -3000); //半区画後退
	no_safty = 0;
	enc.sigma_error = 0;
	Gyro.sigma_error = 0;
	wall_control_mode = 1;
	if (fun_mode == 1) {
		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,100);
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
		HAL_Delay(500);
		reset_ICM();

//		HAL_Delay(1000);
//				reset_ICM();
//				enc.sigma_error = 0;
//					Gyro.sigma_error = 0;
//				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,160);
//						HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
//						HAL_Delay(2000);	//候補1

	}
	maze_mode = 1;
	highspeed_mode = 1;
	Avespeed = 1400;
	wall_control = 0;
	pass_count = 0;

	if (pass[pass_count] == -2 || pass[pass_count] == -3) {
		straight_table(39.5, 0, 800, 800, 26000);
	} else {
		straight_table(39.5, 0, howspeed.turn90_R.g_speed,
				howspeed.turn90_R.g_speed,
				howspeed.turn90_R.g_speed * howspeed.turn90_R.g_speed / 39.5);
	}

	while (pass_count <= 255) {

		if (pass[pass_count] == -1) {
			pass_count++;
		}
		if (pass[pass_count] == -2) {

			//const_speed_wallcut90(39,800,39);//test5
			//	slalom_table(-90, 600, -650, -15000);
			//wall_control_mode = 1;
			//straight_table(29, 600, 600, 600, inacc);
			slalomR(howspeed.slalom_R, OFF);
			//const_speed_wallcut90(5, 1000, 5);
			//slalom_table(-90, 1000, -1000, -15000);
			//wall_control_mode = 1;
			//straight_table(5, 1000, 1000, 1000, inacc);

			pass_count++;
		}
		if (pass[pass_count] == -3) {

			slalomL(howspeed.slalom_L, OFF);

			pass_count++;
		}
		if (pass[pass_count] == -4) {

			//			straight_Wallcut(10, 600);
			//	const_speed_wallcut45(42,800,42); //test5
			//slalom_table(-90, 800, -400, -4200);
			//straight_table(32, 800, 800, 800, inacc);
			turn90R(howspeed.turn90_R, OFF);
			pass_count++;
		}
		if (pass[pass_count] == -5) {
			//			straight_Wallcut(10, 600);
			turn90L(howspeed.turn90_L, OFF);
			pass_count++;
		}
		if (pass[pass_count] == -6) {

			//			straight_Wallcut(10, 600);
			turn180R(howspeed.turn180_R, OFF);

			pass_count++;
		}
		if (pass[pass_count] == -7) {
			//			straight_Wallcut(10, 600);
			turn180L(howspeed.turn180_L, OFF);
			pass_count++;
		}
		if (pass[pass_count] == -8) { //入り45R

			//			straight_Wallcut(10, 600);
			turn45inR(howspeed.turn45in_R, OFF);

			pass_count++;
		}
		if (pass[pass_count] == -9) { //入り45L
			//			straight_Wallcut(10, 600);
			turn45inL(howspeed.turn45in_L, OFF);
			pass_count++;
		}
		if (pass[pass_count] == -10) { //入り135R

			//			straight_Wallcut(10, 600);
			turn135inR(howspeed.turn135in_R, OFF);

			pass_count++;
		}
		if (pass[pass_count] == -11) { //入り135L
			//			straight_Wallcut(10, 600);
			turn135inL(howspeed.turn135in_L, OFF);
			pass_count++;
		}
		if (pass[pass_count] == -12) { //出り45R

			//			straight_Wallcut(10, 600);
			turn45outR(howspeed.turn45out_R, OFF);
			pass_count++;
		}
		if (pass[pass_count] == -13) { //出り45L
			//			straight_Wallcut(10, 600);
			turn45outL(howspeed.turn45out_L, OFF);
			pass_count++;
		}
		if (pass[pass_count] == -14) { //出り135R

			//			straight_Wallcut(10, 600);
			turn135outR(howspeed.turn135out_R, OFF);

			pass_count++;
		}
		if (pass[pass_count] == -15) { //出り135L
			//			straight_Wallcut(10, 600);
			turn135outL(howspeed.turn135out_L, OFF);
			pass_count++;
		}
		if (pass[pass_count] == -16) { //V90R

			//			straight_Wallcut(10, 600);
			V90R(howspeed.V90_R, OFF);

			pass_count++;
		}
		if (pass[pass_count] == -17) { //V90L
			//			straight_Wallcut(10, 600);
			V90L(howspeed.V90_L, OFF);
			pass_count++;
		}

		if (pass[pass_count] >= 1) {
			first_v = howspeed.turn90_R.g_speed;
			last_v = howspeed.turn90_R.g_speed;
			if (pass_count >= 1) {

				if (pass[pass_count - 1] == -2 || pass[pass_count - 1] == -3) {
					first_v = 800;
				}
			}
			if (pass[pass_count + 1] == -2 || pass[pass_count + 1] == -3) {
				last_v = 800;
			}
			if (pass[pass_count] >= 50) {
				wall_control_mode = 6;
				straight_table((90 * 1.414 * (pass[pass_count] - 50)), first_v,
						last_v, inspeed, inacc);

			} else {
				wall_control_mode = 1;
				straight_table((90 * pass[pass_count]), first_v, last_v,
						inspeed, inacc);
			}
			pass_count++;
		}

		if (pass[pass_count] == 0) {
			break;
		}

		if (x == 0 && y == 0) {
			break;
		}
//		if (safe == 1) {
//			safe = 0;
//			break;
//		}
//		if (mode_safty == 1) {
//
//			break;
//		}

	}
	if (x == 0 && y == 0) {
	} else {
		straight_table(180, (E_speedR + E_speedL) / 2, 0,
				(E_speedR + E_speedL) / 2, inacc);
		HAL_Delay(700);
		HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);

		turning_table(180, 0, 0, 400, 5000);
	}
	maze_mode = 0;
	highspeed_mode = 0;
	STBYOFF;
	//highspeed_mode = 0;
	x = 0;
	y = 0;

	t = 0;

	while (t <= 14) {
		row[t] = record.row[t];
		column[t] = record.column[t];
		t++;
	}
	t = 0;
	while (t <= 14) {
		row_look[t] = ~row_look[t];
		column_look[t] = ~column_look[t];
		t++;
	}

}
