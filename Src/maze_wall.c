/*
 * maze_wall.c
 *
 *  Created on: 2019/07/02
 *      Author: sf199
 */

/*
 * maze_wall.c

 *
 *  Created on: 2018/07/12
 *      Author: sf199
 */

#include "maze_wall.h"
#include"maze_strategy.h"

int tt = 0;
int ss = 0;
int mode_255 = 0;
unsigned char Xend_cheak = 240; //x終わりの判定240
unsigned char Yend_cheak = 15; //y終わりの判定15

unsigned short presence[16];

void maze_clear(void) { //初期化
	tt = 0;
	while (tt <= 14) {
		row[tt] = 0;
		column[tt] = 0;
		row_look[tt] = 0;
		column_look[tt] = 0;
		tt++;
	}
	tt = 0;

	while (tt <= 255) {
		walk_count[tt] = 255;

		tt++;
	}
	tt = 0;

//ここから歩数マップの初期状態を作る．

	walk_count[(goal_x * 16) + goal_y] = 0;
	walk_count[((goal_x + 1) * 16) + goal_y] = 0;
	walk_count[(goal_x * 16) + goal_y + 1] = 0;
	walk_count[((goal_x + 1) * 16) + goal_y + 1] = 0;
	count_number = 1;
	while (count_number <= 255) {
		coordinate = 0;
		while (coordinate <= 255) {
			if (walk_count[coordinate] == count_number - 1) {
				Xcheak_result = coordinate & Xend_cheak;
				Ycheak_result = coordinate & Yend_cheak;
				Xcoordinate = Xcheak_result >> 4;
				Ycoordinate = Ycheak_result;

//壁情報のときに使う
//				shift1 = 1;
//							shift1 = shift1 << Ycoordinate;
//
//							row[Xcoordinate] = row[Xcoordinate] | shift1;

				if (walk_count[coordinate + 1] <= 254 || Ycoordinate == 15) {
				} else {
					walk_count[coordinate + 1] = count_number;
				}
				if (walk_count[coordinate - 1] <= 254 || Ycoordinate == 0) {
				} else {
					walk_count[coordinate - 1] = count_number;
				}
				if (walk_count[coordinate + 16] <= 254 || Xcoordinate == 15) {
				} else {
					walk_count[coordinate + 16] = count_number;
				}
				if (walk_count[coordinate - 16] <= 254 || Xcoordinate == 0) {
				} else {
					walk_count[coordinate - 16] = count_number;
				}

			}
			if (coordinate == 255) {
				break;
			}
			coordinate++;

		}

		if (count_number == 255) {
			break;
		}
		count_number++;
	}

	count_number = 1;

//kokomade

}

void maze_maker(int direction, int front_SEN, int left_SEN, int right_SEN,
		int x, int y) {

	switch (direction) {
	case 1:
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (front_SEN >= f_presence && y <= 14) {

			column[y] = column[y] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (left_SEN >= l_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (right_SEN >= r_presence && x <= 14) {

			row[x] = row[x] | shift1;

		}

		break;
	case 2:
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (front_SEN >= f_presence && x <= 14) {

			row[x] = row[x] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (left_SEN >= l_presence && y <= 14) {

			column[y] = column[y] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (right_SEN >= r_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;

		}

		break;
	case 3:
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (front_SEN >= f_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;
		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (left_SEN >= l_presence && x <= 14) {

			row[x] = row[x] | shift1;
		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (right_SEN >= r_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;
		}

		break;
	case 4:
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (front_SEN >= f_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (left_SEN >= l_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (right_SEN >= r_presence && y <= 14) {

			column[y] = column[y] | shift1;
		}

		break;

	}

//ここから歩数マッppuを作る．*************************************
	tt = 0;
	while (tt <= 255) {
		walk_count[tt] = 255;

		tt++;
	}
	tt = 0;

	walk_count[(goal_x * 16) + goal_y] = 0;
	walk_count[((goal_x + 1) * 16) + goal_y] = 0;
	walk_count[(goal_x * 16) + goal_y + 1] = 0;
	walk_count[((goal_x + 1) * 16) + goal_y + 1] = 0;
	count_number = 1;
	while (count_number <= 255) {
		coordinate = 0;
		while (coordinate <= 255) {
			if (walk_count[coordinate] == count_number - 1) {
				Xcheak_result = coordinate & Xend_cheak;
				Ycheak_result = coordinate & Yend_cheak;
				Xcoordinate = Xcheak_result >> 4;
				Ycoordinate = Ycheak_result;

//壁情報のときに使う
				shift1 = 1;
				shift1 = shift1 << Xcoordinate;
				if (Ycoordinate <= 14) {
					wall_north = column[Ycoordinate] & shift1;
				}
				shift1 = 1;
				shift1 = shift1 << Xcoordinate;
				if (Ycoordinate >= 1) {
					wall_south = column[Ycoordinate - 1] & shift1;
				}

				shift1 = 1;
				shift1 = shift1 << Ycoordinate;
				if (Xcoordinate <= 14) {
					wall_east = row[Xcoordinate] & shift1;
				}

				shift1 = 1;
				shift1 = shift1 << Ycoordinate;
				if (Xcoordinate >= 1) {
					wall_west = row[Xcoordinate - 1] & shift1;
				}
				shift1 = 1;

				if (walk_count[coordinate + 1] <= 254 || Ycoordinate == 15
						|| wall_north >= 1) {
				} else {
					walk_count[coordinate + 1] = count_number;
				}
				if (walk_count[coordinate - 1] <= 254 || Ycoordinate == 0
						|| wall_south >= 1) {
				} else {
					walk_count[coordinate - 1] = count_number;
				}
				if (walk_count[coordinate + 16] <= 254 || Xcoordinate == 15
						|| wall_east >= 1) {
				} else {
					walk_count[coordinate + 16] = count_number;
				}
				if (walk_count[coordinate - 16] <= 254 || Xcoordinate == 0
						|| wall_west >= 1) {
				} else {
					walk_count[coordinate - 16] = count_number;
				}

			}
			if (coordinate == 255) {
				break;
			}
			coordinate++;
		}
		if (count_number == 255) {
			break;
		}
		count_number++;
	}
	count_number = 1;

}

//試験用歩数マップ作成短縮方法＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊

void maze_maker2(int direction, int front_SEN, int left_SEN, int right_SEN,
		int x, int y) {

	switch (direction) {
	case 1:
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (front_SEN >= f_presence && y <= 14) {

			column[y] = column[y] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (left_SEN >= l_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (right_SEN >= r_presence && x <= 14) {

			row[x] = row[x] | shift1;

		}

		break;
	case 2:
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (front_SEN >= f_presence && x <= 14) {

			row[x] = row[x] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (left_SEN >= l_presence && y <= 14) {

			column[y] = column[y] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (right_SEN >= r_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;

		}

		break;
	case 3:
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (front_SEN >= f_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;
		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (left_SEN >= l_presence && x <= 14) {

			row[x] = row[x] | shift1;
		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (right_SEN >= r_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;
		}

		break;
	case 4:
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (front_SEN >= f_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (left_SEN >= l_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (right_SEN >= r_presence && y <= 14) {

			column[y] = column[y] | shift1;
		}

		break;

	}

//ここから歩数マッppuを作る．*************************************
	tt = 0;
	while (tt <= 255) {
		walk_count[tt] = 255;

		tt++;
	}
	tt = 0;
	while (tt <= 39) {
		count_box[tt] = 256;
		count_boxnext[tt] = 256;
		tt++;
	}
	tt = 0;

	walk_count[(goal_x * 16) + goal_y] = 0;
	walk_count[((goal_x + 1) * 16) + goal_y] = 0;
	walk_count[(goal_x * 16) + goal_y + 1] = 0;
	walk_count[((goal_x + 1) * 16) + goal_y + 1] = 0;
	count_box[0] = (goal_x * 16) + goal_y;
	count_box[1] = ((goal_x + 1) * 16) + goal_y;
	count_box[2] = (goal_x * 16) + goal_y + 1;
	count_box[3] = ((goal_x + 1) * 16) + goal_y + 1;
	count_number = 1;
	while (count_number <= 255) {
		box = 0;
		boxnext = 0;
		while (box <= 39) {

			coordinate = count_box[box];
			Xcheak_result = coordinate & Xend_cheak;
			Ycheak_result = coordinate & Yend_cheak;
			Xcoordinate = Xcheak_result >> 4;
			Ycoordinate = Ycheak_result;

//壁情報のときに使う
			shift1 = 1;
			shift1 = shift1 << Xcoordinate;
			if (Ycoordinate <= 14) {
				wall_north = column[Ycoordinate] & shift1;
			}
			shift1 = 1;
			shift1 = shift1 << Xcoordinate;
			if (Ycoordinate >= 1) {
				wall_south = column[Ycoordinate - 1] & shift1;
			}

			shift1 = 1;
			shift1 = shift1 << Ycoordinate;
			if (Xcoordinate <= 14) {
				wall_east = row[Xcoordinate] & shift1;
			}

			shift1 = 1;
			shift1 = shift1 << Ycoordinate;
			if (Xcoordinate >= 1) {
				wall_west = row[Xcoordinate - 1] & shift1;
			}
			shift1 = 1;

			if (walk_count[coordinate + 1] <= 254 || Ycoordinate == 15
					|| wall_north >= 1) {
			} else {

				walk_count[coordinate + 1] = count_number;
				count_boxnext[boxnext] = coordinate + 1;
				boxnext++;
			}
			if (walk_count[coordinate - 1] <= 254 || Ycoordinate == 0
					|| wall_south >= 1) {
			} else {

				walk_count[coordinate - 1] = count_number;
				count_boxnext[boxnext] = coordinate - 1;
				boxnext++;
			}
			if (walk_count[coordinate + 16] <= 254 || Xcoordinate == 15
					|| wall_east >= 1) {
			} else {

				walk_count[coordinate + 16] = count_number;
				count_boxnext[boxnext] = coordinate + 16;
				boxnext++;
			}
			if (walk_count[coordinate - 16] <= 254 || Xcoordinate == 0
					|| wall_west >= 1) {
			} else {

				walk_count[coordinate - 16] = count_number;
				count_boxnext[boxnext] = coordinate - 16;
				boxnext++;
			}

			if (box == 39) {

				break;
			}
			box++;
			if (count_box[box] == 256) {
				break;
			}

		}
		tt = 0;
		while (tt <= 39) {

			count_box[tt] = count_boxnext[tt];
			count_boxnext[tt] = 256;
			tt++;
		}
		tt = 0;
		if (count_number == 255 || count_box[0] == 256) {
			break;
		}
		count_number++;

	}
	count_number = 1;

}

void maze_makerhosuu(int direction, int x, int y) {

//ここから歩数マッppuを作る．*************************************
	tt = 0;
	while (tt <= 255) {
		walk_count[tt] = 255;

		tt++;
	}
	tt = 0;

	walk_count[(goal_x * 16) + goal_y] = 0;
	walk_count[((goal_x + 1) * 16) + goal_y] = 0;
	walk_count[(goal_x * 16) + goal_y + 1] = 0;
	walk_count[((goal_x + 1) * 16) + goal_y + 1] = 0;

	count_number = 1;
	while (count_number <= 255) {
		coordinate = 0;
		while (coordinate <= 255) {
			if (walk_count[coordinate] == count_number - 1) {
				Xcheak_result = coordinate & Xend_cheak;
				Ycheak_result = coordinate & Yend_cheak;
				Xcoordinate = Xcheak_result >> 4;
				Ycoordinate = Ycheak_result;

				//壁情報のときに使う
				shift1 = 1;
				shift1 = shift1 << Xcoordinate;
				if (Ycoordinate <= 14) {
					wall_north = column[Ycoordinate] & shift1;
				}
				shift1 = 1;
				shift1 = shift1 << Xcoordinate;
				if (Ycoordinate >= 1) {
					wall_south = column[Ycoordinate - 1] & shift1;
				}

				shift1 = 1;
				shift1 = shift1 << Ycoordinate;
				if (Xcoordinate <= 14) {
					wall_east = row[Xcoordinate] & shift1;
				}

				shift1 = 1;
				shift1 = shift1 << Ycoordinate;
				if (Xcoordinate >= 1) {
					wall_west = row[Xcoordinate - 1] & shift1;
				}
				shift1 = 1;

				if (walk_count[coordinate + 1] <= 254 || Ycoordinate == 15
						|| wall_north >= 1) {
				} else {
					walk_count[coordinate + 1] = count_number;
				}
				if (walk_count[coordinate - 1] <= 254 || Ycoordinate == 0
						|| wall_south >= 1) {
				} else {
					walk_count[coordinate - 1] = count_number;
				}
				if (walk_count[coordinate + 16] <= 254 || Xcoordinate == 15
						|| wall_east >= 1) {
				} else {
					walk_count[coordinate + 16] = count_number;
				}
				if (walk_count[coordinate - 16] <= 254 || Xcoordinate == 0
						|| wall_west >= 1) {
				} else {
					walk_count[coordinate - 16] = count_number;
				}

			}
			if (coordinate == 255) {
				break;
			}
			coordinate++;
		}
		if (count_number == 255) {
			break;
		}
		count_number++;
	}
	count_number = 1;
}
void maze_makerST(int STmass) { //いつか作る直進優先の歩数マップ
//XXX
//ここから歩数マッppuを作る．*************************************
	tt = 0;
	while (tt <= 255) {
		walk_count[tt] = 65535;

		tt++;
	}
	tt = 0;

	walk_count[(goal_x * 16) + goal_y] = 0;
	walk_count[((goal_x + 1) * 16) + goal_y] = 0;
	walk_count[(goal_x * 16) + goal_y + 1] = 0;
	walk_count[((goal_x + 1) * 16) + goal_y + 1] = 0;
	walk_direction[(goal_x * 16) + goal_y] = 0;
	walk_direction[((goal_x + 1) * 16) + goal_y] = 0;
	walk_direction[(goal_x * 16) + goal_y + 1] = 0;
	walk_direction[((goal_x + 1) * 16) + goal_y + 1] = 0;

	count_number = 1;
	while (count_number <= 255) {
		coordinate = 0;
		while (coordinate <= 255) {
			if (walk_count[coordinate] == count_number - 1) {
				Xcheak_result = coordinate & Xend_cheak;
				Ycheak_result = coordinate & Yend_cheak;
				Xcoordinate = Xcheak_result >> 4;
				Ycoordinate = Ycheak_result;

				//壁情報のときに使う
				shift1 = 1;
				shift1 = shift1 << Xcoordinate;
				if (Ycoordinate <= 14) {
					wall_north = column[Ycoordinate] & shift1;
				}
				shift1 = 1;
				shift1 = shift1 << Xcoordinate;
				if (Ycoordinate >= 1) {
					wall_south = column[Ycoordinate - 1] & shift1;
				}

				shift1 = 1;
				shift1 = shift1 << Ycoordinate;
				if (Xcoordinate <= 14) {
					wall_east = row[Xcoordinate] & shift1;
				}

				shift1 = 1;
				shift1 = shift1 << Ycoordinate;
				if (Xcoordinate >= 1) {
					wall_west = row[Xcoordinate - 1] & shift1;
				}
				shift1 = 1;

				if (walk_count[coordinate + 1] <= 254 || Ycoordinate == 15
						|| wall_north >= 1) {
				} else {
					if (walk_direction[coordinate] == 0) {
						walk_count[coordinate + 1] = count_number;
						walk_direction[coordinate + 1] = 1;
					} else {
//					if(walk_count[coordinate - 1] == count_number-1 || )
						if (walk_direction[coordinate] == 1) {
							walk_count[coordinate + 1] = count_number;
							walk_direction[coordinate + 1] = 1;
						} else {
							walk_count[coordinate + 1] = count_number + STmass;
							walk_direction[coordinate + 1] = 1;
						}
					}

				}
				if (walk_count[coordinate - 1] <= 254 || Ycoordinate == 0
						|| wall_south >= 1) {
				} else {
					if (walk_direction[coordinate] == 0) {
						walk_count[coordinate - 1] = count_number;
						walk_direction[coordinate - 1] = 3;
					} else {
						if (walk_direction[coordinate] == 3) {
							walk_count[coordinate - 1] = count_number;
							walk_direction[coordinate - 1] = 3;
						} else {
							walk_count[coordinate - 1] = count_number + STmass;
							walk_direction[coordinate - 1] = 3;
						}
					}
				}
				if (walk_count[coordinate + 16] <= 254 || Xcoordinate == 15
						|| wall_east >= 1) {
				} else {
					if (walk_direction[coordinate] == 0) {
						walk_count[coordinate + 16] = count_number;
						walk_direction[coordinate + 16] = 2;
					} else {
						if (walk_direction[coordinate] == 2) {
							walk_count[coordinate + 16] = count_number;
							walk_direction[coordinate + 16] = 2;
						} else {
							walk_count[coordinate + 16] = count_number + STmass;
							walk_direction[coordinate + 16] = 2;
						}
					}
				}
				if (walk_count[coordinate - 16] <= 254 || Xcoordinate == 0
						|| wall_west >= 1) {
				} else {
					if (walk_direction[coordinate] == 0) {
						walk_count[coordinate - 16] = count_number;
						walk_direction[coordinate - 16] = 4;
					} else {
						if (walk_direction[coordinate] == 4) {
							walk_count[coordinate - 16] = count_number;
							walk_direction[coordinate - 16] = 4;
						} else {
							walk_count[coordinate - 16] = count_number + STmass;
							walk_direction[coordinate - 16] = 4;
						}
					}
				}

			}
			if (coordinate == 255) {
				break;
			}
			coordinate++;
		}
		if (count_number == 255) {
			break;
		}
		count_number++;
	}
	count_number = 1;
}

void maze_makerRun(int direction, int front_SEN, int left_SEN, int right_SEN,
		int x, int y) {

	switch (direction) {
	case 1:
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (front_SEN >= f_presence && y <= 14) {

			column[y] = column[y] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (left_SEN >= l_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (right_SEN >= r_presence && x <= 14) {

			row[x] = row[x] | shift1;

		}

		break;
	case 2:
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (front_SEN >= f_presence && x <= 14) {

			row[x] = row[x] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (left_SEN >= l_presence && y <= 14) {

			column[y] = column[y] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (right_SEN >= r_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;

		}

		break;
	case 3:
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (front_SEN >= f_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;
		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (left_SEN >= l_presence && x <= 14) {

			row[x] = row[x] | shift1;
		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (right_SEN >= r_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;
		}

		break;
	case 4:
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (front_SEN >= f_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (left_SEN >= l_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (right_SEN >= r_presence && y <= 14) {

			column[y] = column[y] | shift1;
		}

		break;

	}

//ここから歩数マッppuを作る．*************************************
	tt = 0;
	while (tt <= 255) {
		walk_count[tt] = 255;

		tt++;
	}
	tt = 0;
	while (tt <= 39) {
		count_box[tt] = 256;
		count_boxnext[tt] = 256;
		tt++;
	}
	tt = 0;

	walk_count[(goal_x * 16) + goal_y] = 0;
	walk_count[((goal_x + 1) * 16) + goal_y] = 0;
	walk_count[(goal_x * 16) + goal_y + 1] = 0;
	walk_count[((goal_x + 1) * 16) + goal_y + 1] = 0;
	count_box[0] = (goal_x * 16) + goal_y;
	count_box[1] = ((goal_x + 1) * 16) + goal_y;
	count_box[2] = (goal_x * 16) + goal_y + 1;
	count_box[3] = ((goal_x + 1) * 16) + goal_y + 1;
	count_number = 1;
	while (count_number <= 255) {
		box = 0;
		boxnext = 0;
		while (box <= 39) {
			coordinate = count_box[box];
			Xcheak_result = coordinate & Xend_cheak;
			Ycheak_result = coordinate & Yend_cheak;
			Xcoordinate = Xcheak_result >> 4;
			Ycoordinate = Ycheak_result;

//壁情報のときに使う
			shift1 = 1;
			shift1 = shift1 << Xcoordinate;
			if (Ycoordinate <= 14) {
				wall_north = column[Ycoordinate] & shift1;
			}
			shift1 = 1;
			shift1 = shift1 << Xcoordinate;
			if (Ycoordinate >= 1) {
				wall_south = column[Ycoordinate - 1] & shift1;
			}

			shift1 = 1;
			shift1 = shift1 << Ycoordinate;
			if (Xcoordinate <= 14) {
				wall_east = row[Xcoordinate] & shift1;
			}

			shift1 = 1;
			shift1 = shift1 << Ycoordinate;
			if (Xcoordinate >= 1) {
				wall_west = row[Xcoordinate - 1] & shift1;
			}
			shift1 = 1;

			if (walk_count[coordinate + 1] <= 254 || Ycoordinate == 15
					|| wall_north >= 1) {
			} else {
				walk_count[coordinate + 1] = count_number;
				count_boxnext[boxnext] = coordinate + 1;
				boxnext++;
			}
			if (walk_count[coordinate - 1] <= 254 || Ycoordinate == 0
					|| wall_south >= 1) {
			} else {
				walk_count[coordinate - 1] = count_number;
				count_boxnext[boxnext] = coordinate - 1;
				boxnext++;
			}
			if (walk_count[coordinate + 16] <= 254 || Xcoordinate == 15
					|| wall_east >= 1) {
			} else {
				walk_count[coordinate + 16] = count_number;
				count_boxnext[boxnext] = coordinate + 16;
				boxnext++;
			}
			if (walk_count[coordinate - 16] <= 254 || Xcoordinate == 0
					|| wall_west >= 1) {
			} else {
				walk_count[coordinate - 16] = count_number;
				count_boxnext[boxnext] = coordinate - 16;
				boxnext++;
			}

			if (box == 39) {
				break;
			}
			box++;
			if (count_box[box] == 256) {
				break;
			}
		}
		tt = 0;
		while (tt <= 39) {

			count_box[tt] = count_boxnext[tt];
			count_boxnext[tt] = 256;
			tt++;
		}
		tt = 0;
		if (count_number == 255 || count_box[0] == 256) {
			break;
		}
		if (walk_count[(x * 16) + y + 1] <= 254
				&& walk_count[(x * 16) + y - 1] <= 254
				&& walk_count[((x + 1) * 16) + y] <= 254
				&& walk_count[((x - 1) * 16) + y] <= 254) {
			break;
		}
		count_number++;
	}
	count_number = 1;

}

void maze_makeronly(int direction, int front_SEN, int left_SEN, int right_SEN,
		int x, int y) {

	switch (direction) {
	case 1:
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (front_SEN >= f_presence && y <= 14) {

			column[y] = column[y] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (left_SEN >= l_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (right_SEN >= r_presence && x <= 14) {

			row[x] = row[x] | shift1;

		}

		break;
	case 2:
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (front_SEN >= f_presence && x <= 14) {

			row[x] = row[x] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (left_SEN >= l_presence && y <= 14) {

			column[y] = column[y] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (right_SEN >= r_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;

		}

		break;
	case 3:
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (front_SEN >= f_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;
		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (left_SEN >= l_presence && x <= 14) {

			row[x] = row[x] | shift1;
		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (right_SEN >= r_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;
		}

		break;
	case 4:
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (front_SEN >= f_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (left_SEN >= l_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (right_SEN >= r_presence && y <= 14) {

			column[y] = column[y] | shift1;
		}

		break;

	}

}

void maze_makerback(int direction, int front_SEN, int left_SEN, int right_SEN,
		int x, int y) {

	switch (direction) {
	case 1:
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (front_SEN >= f_presence && y <= 14) {

			column[y] = column[y] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (left_SEN >= l_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (right_SEN >= r_presence && x <= 14) {

			row[x] = row[x] | shift1;

		}

		break;
	case 2:
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (front_SEN >= f_presence && x <= 14) {

			row[x] = row[x] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (left_SEN >= l_presence && y <= 14) {

			column[y] = column[y] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (right_SEN >= r_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;

		}

		break;
	case 3:
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (front_SEN >= f_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;
		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (left_SEN >= l_presence && x <= 14) {

			row[x] = row[x] | shift1;
		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (right_SEN >= r_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;
		}

		break;
	case 4:
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (front_SEN >= f_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (left_SEN >= l_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (right_SEN >= r_presence && y <= 14) {

			column[y] = column[y] | shift1;
		}

		break;

	}

//ここから歩数マッppuを作る．*************************************
	tt = 0;
	while (tt <= 255) {
		walk_count[tt] = 255;

		tt++;
	}
	tt = 0;
	while (tt <= 39) {
		count_box[tt] = 256;
		count_boxnext[tt] = 256;
		tt++;
	}
	tt = 0;

	walk_count[0] = 0;
	count_box[0] = 0;
	count_number = 1;
	while (count_number <= 255) {
		box = 0;
		boxnext = 0;
		while (box <= 39) {

			coordinate = count_box[box];
			Xcheak_result = coordinate & Xend_cheak;
			Ycheak_result = coordinate & Yend_cheak;
			Xcoordinate = Xcheak_result >> 4;
			Ycoordinate = Ycheak_result;

//壁情報のときに使う
			shift1 = 1;
			shift1 = shift1 << Xcoordinate;
			if (Ycoordinate <= 14) {
				wall_north = column[Ycoordinate] & shift1;
			}
			shift1 = 1;
			shift1 = shift1 << Xcoordinate;
			if (Ycoordinate >= 1) {
				wall_south = column[Ycoordinate - 1] & shift1;
			}

			shift1 = 1;
			shift1 = shift1 << Ycoordinate;
			if (Xcoordinate <= 14) {
				wall_east = row[Xcoordinate] & shift1;
			}

			shift1 = 1;
			shift1 = shift1 << Ycoordinate;
			if (Xcoordinate >= 1) {
				wall_west = row[Xcoordinate - 1] & shift1;
			}
			shift1 = 1;

			if (walk_count[coordinate + 1] <= 254 || Ycoordinate == 15
					|| wall_north >= 1) {
			} else {

				walk_count[coordinate + 1] = count_number;
				count_boxnext[boxnext] = coordinate + 1;
				boxnext++;
			}
			if (walk_count[coordinate - 1] <= 254 || Ycoordinate == 0
					|| wall_south >= 1) {
			} else {

				walk_count[coordinate - 1] = count_number;
				count_boxnext[boxnext] = coordinate - 1;
				boxnext++;
			}
			if (walk_count[coordinate + 16] <= 254 || Xcoordinate == 15
					|| wall_east >= 1) {
			} else {

				walk_count[coordinate + 16] = count_number;
				count_boxnext[boxnext] = coordinate + 16;
				boxnext++;
			}
			if (walk_count[coordinate - 16] <= 254 || Xcoordinate == 0
					|| wall_west >= 1) {
			} else {

				walk_count[coordinate - 16] = count_number;
				count_boxnext[boxnext] = coordinate - 16;
				boxnext++;
			}

			if (box == 39) {

				break;
			}
			box++;
			if (count_box[box] == 256) {
				break;
			}

		}
		tt = 0;
		while (tt <= 39) {

			count_box[tt] = count_boxnext[tt];
			count_boxnext[tt] = 256;
			tt++;
		}
		tt = 0;
		if (count_number == 255 || count_box[0] == 256) {
			break;
		}
		count_number++;
	}
	count_number = 1;

}

void maze_makerslant(void) { //いつか作る直進優先の歩数マップ
//XXX
//ここから歩数マッppuを作る．*************************************
	int count1, count2;
	int row_exist, column_exist;
	tt = 0;
	while (tt <= 255) {
		walk_count_slant[tt] = 65535 - 1;

		tt++;
	}
	tt = 0;

	walk_count_slant[columnnumber + 16 * goal_y + goal_x] = 0;
	walk_count_slant[columnnumber + 16 * goal_y + goal_x + 1] = 0;
	walk_count_slant[rownumber + 16 * goal_x + goal_y] = 0;
	walk_count_slant[rownumber + 16 * goal_x + goal_y + 1] = 0;
//	walk_direction[(goal_x * 16) + goal_y] = 0;
//	walk_direction[((goal_x + 1) * 16) + goal_y] = 0;
//	walk_direction[(goal_x * 16) + goal_y + 1] = 0;
//	walk_direction[((goal_x + 1) * 16) + goal_y + 1] = 0;

	for (count1 = 0; count1 < 15; count1++) {
		for (count2 = 0; count2 < 16; count2++) {
			shift1 = 1;
			shift1 = shift1 << count2;
			column_exist = column[count1] && shift1;
			shift1 = 1;
			shift1 = shift1 << count2;
			row_exist = row[count1] && shift1;
			if (column_exist >= 1) {
				walk_count_slant[columnnumber + 16 * count1 + count2] = 65535;
			}
			if (row_exist >= 1) {
				walk_count_slant[rownumber + 16 * count1 + count2] = 65535;
			}
		}

	}

	count_number = 1;
	while (count_number <= 255) {
		coordinate = 0;
		while (coordinate <= 255) {
			if (walk_count[coordinate] == count_number - 1) {
				Xcheak_result = coordinate & Xend_cheak;
				Ycheak_result = coordinate & Yend_cheak;
				Xcoordinate = Xcheak_result >> 4;
				Ycoordinate = Ycheak_result;

				//壁情報のときに使う
				shift1 = 1;
				shift1 = shift1 << Xcoordinate;
				if (Ycoordinate <= 14) {
					wall_north = column[Ycoordinate] & shift1;
				}
				shift1 = 1;
				shift1 = shift1 << Xcoordinate;
				if (Ycoordinate >= 1) {
					wall_south = column[Ycoordinate - 1] & shift1;
				}

				shift1 = 1;
				shift1 = shift1 << Ycoordinate;
				if (Xcoordinate <= 14) {
					wall_east = row[Xcoordinate] & shift1;
				}

				shift1 = 1;
				shift1 = shift1 << Ycoordinate;
				if (Xcoordinate >= 1) {
					wall_west = row[Xcoordinate - 1] & shift1;
				}
				shift1 = 1;

				if (walk_count[coordinate + 1] <= 254 || Ycoordinate == 15
						|| wall_north >= 1) {
				} else {
					if (walk_direction[coordinate] == 0) {
						walk_count[coordinate + 1] = count_number;
						walk_direction[coordinate + 1] = 1;
					} else {
//					if(walk_count[coordinate - 1] == count_number-1 || )
						if (walk_direction[coordinate] == 1) {
							walk_count[coordinate + 1] = count_number;
							walk_direction[coordinate + 1] = 1;
						} else {
							walk_count[coordinate + 1] = count_number;
							walk_direction[coordinate + 1] = 1;
						}
					}

				}
				if (walk_count[coordinate - 1] <= 254 || Ycoordinate == 0
						|| wall_south >= 1) {
				} else {
					if (walk_direction[coordinate] == 0) {
						walk_count[coordinate - 1] = count_number;
						walk_direction[coordinate - 1] = 3;
					} else {
						if (walk_direction[coordinate] == 3) {
							walk_count[coordinate - 1] = count_number;
							walk_direction[coordinate - 1] = 3;
						} else {
							walk_count[coordinate - 1] = count_number;
							walk_direction[coordinate - 1] = 3;
						}
					}
				}
				if (walk_count[coordinate + 16] <= 254 || Xcoordinate == 15
						|| wall_east >= 1) {
				} else {
					if (walk_direction[coordinate] == 0) {
						walk_count[coordinate + 16] = count_number;
						walk_direction[coordinate + 16] = 2;
					} else {
						if (walk_direction[coordinate] == 2) {
							walk_count[coordinate + 16] = count_number;
							walk_direction[coordinate + 16] = 2;
						} else {
							walk_count[coordinate + 16] = count_number;
							walk_direction[coordinate + 16] = 2;
						}
					}
				}
				if (walk_count[coordinate - 16] <= 254 || Xcoordinate == 0
						|| wall_west >= 1) {
				} else {
					if (walk_direction[coordinate] == 0) {
						walk_count[coordinate - 16] = count_number;
						walk_direction[coordinate - 16] = 4;
					} else {
						if (walk_direction[coordinate] == 4) {
							walk_count[coordinate - 16] = count_number;
							walk_direction[coordinate - 16] = 4;
						} else {
							walk_count[coordinate - 16] = count_number;
							walk_direction[coordinate - 16] = 4;
						}
					}
				}

			}
			if (coordinate == 255) {
				break;
			}
			coordinate++;
		}
		if (count_number == 255) {
			break;
		}
		count_number++;
	}
	count_number = 1;
}

void maze_display(void) {

	tt = 14;

	printf(
			"+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n");
	while (tt >= -1) { //ttはｙ軸
		shift2 = 1;

		shift2 = shift2 << (tt + 1);
		ss = 0;
		printf("|%5d", walk_count[tt + 1]);
		while (ss < 15) {
			presence[ss] = row[ss] & shift2;
			if (presence[ss] == 0) {
				printf(" %5d", walk_count[tt + 1 + (ss + 1) * 16]);
			} else {
				printf("|%5d", walk_count[tt + 1 + (ss + 1) * 16]);
			}
			ss++;
		}
		printf("|\n");
		ss = 0;
		while (ss <= 15) { // all clear***************************************
			presence[ss] = 0;

			ss++;
		}
		ss = 0; // all clear***************************************
		if (tt <= -1) {
			break;
		}
		while (ss <= 15) {
			shift2 = 1;
			shift2 = shift2 << ss;
			presence[ss] = column[tt] & shift2;

			if (presence[ss] == 0) {
				printf("+     ");
			} else {
				printf("+-----");
			}
			ss++;
		}

		printf("+\n");

		ss = 0;

		while (ss <= 15) { // all clear***************************************
			presence[ss] = 0;

			ss++;
		}
		ss = 0; // all clear***************************************

		tt--;
	}

	printf(
			"+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n\n");

//  myprintf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n\n");
//look_display
//	tt = 0;
//		while (tt <= 14) {
//			row_look[tt] = ~ row_look[tt];
//column_look[tt]= ~ column_look[tt];
//				tt++;
//			}
//		tt=0;
	tt = 14;
	printf(
			"+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n");

	while (tt >= -1) { //ttはｙ軸
		shift2 = 1;

		shift2 = shift2 << (tt + 1);
		ss = 0;
		printf("|%5d", walk_count[tt + 1]);
		while (ss < 15) {
			presence[ss] = row_look[ss] & shift2;
			if (presence[ss] == 0) {
				printf(" %5d", walk_count[tt + 1 + (ss + 1) * 16]);
			} else {
				printf("|%5d", walk_count[tt + 1 + (ss + 1) * 16]);
			}
			ss++;
		}
		printf("|\n");
		ss = 0;
		while (ss <= 15) { // all clear***************************************
			presence[ss] = 0;

			ss++;
		}
		ss = 0; // all clear***************************************
		if (tt <= -1) {
			break;
		}
		while (ss <= 15) {
			shift2 = 1;
			shift2 = shift2 << ss;
			presence[ss] = column_look[tt] & shift2;

			if (presence[ss] == 0) {
				printf("+     ");
			} else {
				printf("+-----");
			}
			ss++;
		}

		printf("+\n");

		ss = 0;

		while (ss <= 15) { // all clear***************************************
			presence[ss] = 0;

			ss++;
		}
		ss = 0; // all clear***************************************

		tt--;
	}

	printf(
			"+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n\n");

}

