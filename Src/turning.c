/*
 * turning.c
 *
 *  Created on: 2019/10/02
 *      Author: sf199
 */
#include "motor_control.h"
#include "turning.h"

void slalomR(parameter turnpara,char test_mode) {
	if (test_mode == 1) {
		highspeed_mode = 1;
		STBYON;
		wall_control_mode = 1;
		straight_table(39.5 + 270, 0, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 90);		//test5
		const_speed_wallcut90(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(-90, turnpara.g_speed, -turnpara.t_speed, -turnpara.t_acc);
		wall_control_mode = 0;
		straight_table(90 + turnpara.e_ofset, turnpara.g_speed, 0, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 90);
		reset_distance();
		record_mode_sensor = 0;
		R_stop
		;
		L_stop
		;
		HAL_Delay(700);
		STBYOFF;
		highspeed_mode = 0;
	} else {
		wall_control_mode = 1;
		const_speed_wallcut90(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(-90, turnpara.g_speed, -turnpara.t_speed, -turnpara.t_acc);
		wall_control_mode = 1;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed, 23456);

	}
}
void slalomL(parameter turnpara, char test_mode) {
	if (test_mode == 1) {
		highspeed_mode = 1;
		STBYON;
		wall_control_mode = 1;
		straight_table(39.5 + 270, 0, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 90);		//test5
		const_speed_wallcut90(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(90, turnpara.g_speed, turnpara.t_speed, turnpara.t_acc);
		wall_control_mode = 0;
		straight_table(90 + turnpara.e_ofset, turnpara.g_speed, 0, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 90);
		reset_distance();
		record_mode_sensor = 0;
		R_stop
		;
		L_stop
		;
		HAL_Delay(700);
		STBYOFF;
		highspeed_mode = 0;
	} else {
		wall_control_mode = 1;
		const_speed_wallcut90(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(90, turnpara.g_speed, turnpara.t_speed, turnpara.t_acc);
		wall_control_mode = 1;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed, 23456);
		wall_control_mode = 1;
	}

}
void turn90R(parameter turnpara, char test_mode) {
	if (test_mode == 1) {
		highspeed_mode = 1;
		STBYON;
		wall_control_mode = 1;
		straight_table(39.5 + 180, 0, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);		//test5
		const_speed_wallcut45(turnpara.f_ofset, turnpara.g_speed,
				turnpara.f_ofset);
		slalom_table(-90, turnpara.g_speed, -turnpara.t_speed, -turnpara.t_acc);
		straight_table(180 + turnpara.e_ofset, turnpara.g_speed, 0,
				turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);
		reset_distance();
		record_mode_sensor = 0;
		R_stop
		;
		L_stop
		;
		HAL_Delay(700);
		STBYOFF;
		highspeed_mode = 0;
	} else {
		const_speed_wallcut45(turnpara.f_ofset, turnpara.g_speed,
				turnpara.f_ofset);
		slalom_table(-90, turnpara.g_speed, -turnpara.t_speed, -turnpara.t_acc);
		wall_control_mode = 1;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed, 23456);
	}

}
void turn90L(parameter turnpara, char test_mode) {
	if (test_mode == 1) {
		highspeed_mode = 1;
		STBYON;
		wall_control_mode = 1;
		straight_table(39.5 + 180, 0, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);		//test5
		const_speed_wallcut45(turnpara.f_ofset, turnpara.g_speed,
				turnpara.f_ofset);
		slalom_table(90, turnpara.g_speed, turnpara.t_speed, turnpara.t_acc);
		straight_table(180 + turnpara.e_ofset, turnpara.g_speed, 0,
				turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);
		reset_distance();
		record_mode_sensor = 0;
		R_stop
		;
		L_stop
		;
		HAL_Delay(700);
		STBYOFF;
		highspeed_mode = 0;
	} else {
		const_speed_wallcut45(turnpara.f_ofset, turnpara.g_speed,
				turnpara.f_ofset);
		slalom_table(90, turnpara.g_speed, turnpara.t_speed, turnpara.t_acc);
		wall_control_mode = 1;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed, 23456);
	}

}
void turn180R(parameter turnpara, char test_mode) {
	if (test_mode == 1) {
		highspeed_mode = 1;
		STBYON;
		wall_control_mode = 1;
		straight_table(39.5 + 180, 0, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);		//test5
		const_speed_wallcut45(turnpara.f_ofset, turnpara.g_speed,
				turnpara.f_ofset);
		slalom_table(-180, turnpara.g_speed, -turnpara.t_speed,
				-turnpara.t_acc);
		straight_table(180 + turnpara.e_ofset, turnpara.g_speed, 0,
				turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);
		reset_distance();
		record_mode_sensor = 0;
		R_stop
		;
		L_stop
		;
		HAL_Delay(700);
		STBYOFF;
		highspeed_mode = 0;
	} else {
		const_speed_wallcut45(turnpara.f_ofset, turnpara.g_speed,
				turnpara.f_ofset);
		slalom_table(-180, turnpara.g_speed, -turnpara.t_speed,
				-turnpara.t_acc);
		wall_control_mode = 1;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed, 23456);
	}

}
void turn180L(parameter turnpara, char test_mode) {
	if (test_mode == 1) {
		highspeed_mode = 1;
		STBYON;
		wall_control_mode = 1;
		straight_table(39.5 + 180, 0, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);		//test5
		const_speed_wallcut45(turnpara.f_ofset, turnpara.g_speed,
				turnpara.f_ofset);
		slalom_table(180, turnpara.g_speed, turnpara.t_speed, turnpara.t_acc);
		straight_table(180 + turnpara.e_ofset, turnpara.g_speed, 0,
				turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);
		reset_distance();
		record_mode_sensor = 0;
		R_stop
		;
		L_stop
		;
		HAL_Delay(700);
		STBYOFF;
		highspeed_mode = 0;
	} else {
		const_speed_wallcut45(turnpara.f_ofset, turnpara.g_speed,
				turnpara.f_ofset);
		slalom_table(180, turnpara.g_speed, turnpara.t_speed, turnpara.t_acc);
		wall_control_mode = 1;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed, 0);
	}

}
void turn45inR(parameter turnpara, char test_mode) {
	if (test_mode == 1) {
		highspeed_mode = 1;
		STBYON;
		wall_control_mode = 1;
		straight_table(39.5 + 180, 0, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);		//test5
		const_speed_wallcut45(turnpara.f_ofset, turnpara.g_speed,
				turnpara.f_ofset);
		slalom_table(-45, turnpara.g_speed, -turnpara.t_speed, -turnpara.t_acc);
		straight_table(180 * 1.4142 + turnpara.e_ofset, turnpara.g_speed, 0,
				turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);
		reset_distance();
		record_mode_sensor = 0;
		R_stop
		;
		L_stop
		;
		HAL_Delay(700);
		STBYOFF;
		highspeed_mode = 0;
	}
	if (test_mode == 0) {
		const_speed_wallcut45(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(-45, turnpara.g_speed, -turnpara.t_speed, -turnpara.t_acc);
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed, 23456);
		wall_control_mode = 5;
	}
	if (test_mode >= 2) {
		highspeed_mode = 1;
		STBYON;
		wall_control_mode = 1;
		straight_table(39.5 + 180, 0, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);		//test5
		const_speed_wallcut45(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(-45, turnpara.g_speed, -turnpara.t_speed, -turnpara.t_acc);
		straight_table(90 * 1.4142 * (test_mode - 2) + turnpara.e_ofset, turnpara.g_speed,
				turnpara.g_speed, turnpara.g_speed, 23456);
		wall_control_mode = 5;
	}

}

void turn45inL(parameter turnpara,  char test_mode) {
	if (test_mode == 1) {
		highspeed_mode = 1;
		STBYON;
		wall_control_mode = 1;
		straight_table(39.5 + 180, 0, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);		//test5
		const_speed_wallcut45(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(45, turnpara.g_speed, turnpara.t_speed, turnpara.t_acc);
		straight_table(180 * 1.4142 + turnpara.e_ofset, turnpara.g_speed, 0, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);
		reset_distance();
		record_mode_sensor = 0;
		R_stop
		;
		L_stop
		;
		HAL_Delay(700);
		STBYOFF;
		highspeed_mode = 0;
	}
	if (test_mode == 0) {
		const_speed_wallcut45(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(45, turnpara.g_speed, turnpara.t_speed, turnpara.t_acc);
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed, 23456);
		wall_control_mode = 5;
	}
	if (test_mode >= 2) {
		highspeed_mode = 1;
		STBYON;
		wall_control_mode = 1;
		straight_table(39.5 + 180, 0, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);		//test5
		const_speed_wallcut45(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(45, turnpara.g_speed, turnpara.t_speed, turnpara.t_acc);
		straight_table(90 * 1.4142 * (test_mode - 2) + turnpara.e_ofset, turnpara.g_speed,
				turnpara.g_speed, turnpara.g_speed, 23456);
		wall_control_mode = 5;
	}

}
void turn135inR(parameter turnpara,  char test_mode) {
	if (test_mode == 1) {
		highspeed_mode = 1;
		STBYON;
		wall_control_mode = 1;
		straight_table(39.5 + 180, 0, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);		//test5
		const_speed_wallcut45(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(-135, turnpara.g_speed, -turnpara.t_speed, -turnpara.t_acc);
		straight_table(180 * 1.4142 + turnpara.e_ofset, turnpara.g_speed, 0, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);
		reset_distance();
		record_mode_sensor = 0;
		R_stop
		;
		L_stop
		;
		HAL_Delay(700);
		STBYOFF;
		highspeed_mode = 0;
	}
	if (test_mode == 0) {
		const_speed_wallcut45(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(-135, turnpara.g_speed, -turnpara.t_speed, -turnpara.t_acc);
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed, 23456);
		wall_control_mode = 5;
	}
	if (test_mode >= 2) {
		highspeed_mode = 1;
		STBYON;
		wall_control_mode = 1;
		straight_table(39.5 + 180, 0, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);		//test5
		const_speed_wallcut45(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(-135, turnpara.g_speed, -turnpara.t_speed, -turnpara.t_acc);
		straight_table(90 * 1.4142 * (test_mode - 2) + turnpara.e_ofset, turnpara.g_speed,
				turnpara.g_speed, turnpara.g_speed, 23456);
		wall_control_mode = 5;

	}

}
void turn135inL(parameter turnpara, char test_mode) {
	if (test_mode == 1) {
		highspeed_mode = 1;
		STBYON;
		wall_control_mode = 1;
		straight_table(39.5 + 180, 0, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);		//test5
		const_speed_wallcut45(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(135, turnpara.g_speed, turnpara.t_speed, turnpara.t_acc);
		straight_table(180 * 1.4142 + turnpara.e_ofset, turnpara.g_speed, 0, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);
		reset_distance();
		record_mode_sensor = 0;
		R_stop
		;
		L_stop
		;
		HAL_Delay(700);
		STBYOFF;
		highspeed_mode = 0;
	}
	if (test_mode == 0) {
		const_speed_wallcut45(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(135, turnpara.g_speed, turnpara.t_speed, turnpara.t_acc);
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed, 23456);
		wall_control_mode = 5;
	}
	if (test_mode >= 2) {
		highspeed_mode = 1;
		STBYON;
		wall_control_mode = 1;
		straight_table(39.5 + 180, 0, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);		//test5
		const_speed_wallcut45(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(135, turnpara.g_speed, turnpara.t_speed, turnpara.t_acc);
		straight_table(90 * 1.4142 * (test_mode - 2) + turnpara.e_ofset, turnpara.g_speed,
				turnpara.g_speed, turnpara.g_speed, 23456);
		wall_control_mode = 5;

	}
}
void turn45outR(parameter turnpara,  char test_mode) {
	if (test_mode == 1) {
		//straight_table(90 * 1.4142 , turnpara.g_speed, turnpara.g_speed, turnpara.g_speed, 23456);
		const_speed_wallcutslantR(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(-45, turnpara.g_speed, -turnpara.t_speed, -turnpara.t_acc);
		straight_table(180 + turnpara.e_ofset, turnpara.g_speed, 0, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);
		reset_distance();
		record_mode_sensor = 0;
		R_stop
		;
		L_stop
		;
		HAL_Delay(700);
		STBYOFF;
		highspeed_mode = 0;
	} else {
		const_speed_wallcutslantR(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(-45, turnpara.g_speed, -turnpara.t_speed, -turnpara.t_acc);
		wall_control_mode = 1;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed, 23456);
	}

}

void turn45outL(parameter turnpara,  char test_mode) {
	if (test_mode == 1) {
		highspeed_mode = 1;
		//straight_table(90 * 1.4142 , turnpara.g_speed, turnpara.g_speed, turnpara.g_speed, 0);
		const_speed_wallcutslantL(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(45, turnpara.g_speed, turnpara.t_speed, turnpara.t_acc);
		straight_table(180 + turnpara.e_ofset, turnpara.g_speed, 0, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);
		reset_distance();
		record_mode_sensor = 0;
		R_stop
		;
		L_stop
		;
		HAL_Delay(700);
		STBYOFF;
		highspeed_mode = 0;

	} else {
		const_speed_wallcutslantL(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(45, turnpara.g_speed, turnpara.t_speed, turnpara.t_acc);
		wall_control_mode = 1;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed, 23456);
	}
}
void turn135outR(parameter turnpara, char test_mode) {
	if (test_mode == 1) {
		highspeed_mode = 1;
		//straight_table(90 * 1.4142 , turnpara.g_speed, turnpara.g_speed, turnpara.g_speed, 0);
		const_speed_wallcutslantR(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(-135, turnpara.g_speed, -turnpara.t_speed, -turnpara.t_acc);
		straight_table(180 + turnpara.e_ofset, turnpara.g_speed, 0, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);
		reset_distance();
		record_mode_sensor = 0;
		R_stop
		;
		L_stop
		;
		HAL_Delay(700);
		STBYOFF;
		highspeed_mode = 0;
	} else {
		const_speed_wallcutslantR(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(-135, turnpara.g_speed, -turnpara.t_speed, -turnpara.t_acc);
		wall_control_mode = 1;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed, 23456);
	}
}
void turn135outL(parameter turnpara, char test_mode) {
	if (test_mode == 1) {
		highspeed_mode = 1;
		//straight_table(90 * 1.4142 , turnpara.g_speed, turnpara.g_speed, turnpara.g_speed, 0);
		const_speed_wallcutslantL(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(135, turnpara.g_speed, turnpara.t_speed, turnpara.t_acc);
		straight_table(180 + turnpara.e_ofset, turnpara.g_speed, 0, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);
		reset_distance();
		record_mode_sensor = 0;
		R_stop
		;
		L_stop
		;
		HAL_Delay(700);
		STBYOFF;
		highspeed_mode = 0;
	} else {
		const_speed_wallcutslantL(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(135, turnpara.g_speed, turnpara.t_speed, turnpara.t_acc);
		wall_control_mode = 1;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed, 23456);
	}

}
void V90R(parameter turnpara, char test_mode) {
	if (test_mode == 1) {
		highspeed_mode = 1;
		//straight_table(90 * 1.4142 , turnpara.g_speed, turnpara.g_speed, turnpara.g_speed, 0);
		const_speed_wallcutslantR(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(-90, turnpara.g_speed, -turnpara.t_speed, -turnpara.t_acc);
		straight_table(180 * 1.4142 + turnpara.e_ofset, turnpara.g_speed, 0, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);
		reset_distance();
		record_mode_sensor = 0;
		R_stop
		;
		L_stop
		;
		HAL_Delay(700);
		STBYOFF;
		highspeed_mode = 0;
	} else {
		const_speed_wallcutslantR(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(-90, turnpara.g_speed, -turnpara.t_speed, -turnpara.t_acc);
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed, 23456);
		wall_control_mode = 5;
	}

}
void V90L(parameter turnpara, char test_mode) {
	if (test_mode == 1) {
		highspeed_mode = 1;
		//straight_table(90 * 1.4142 , turnpara.g_speed, turnpara.g_speed, turnpara.g_speed, 0);
		const_speed_wallcutslantL(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(90, turnpara.g_speed, turnpara.t_speed, turnpara.t_acc);
		straight_table(180 * 1.4142 + turnpara.e_ofset, turnpara.g_speed, 0, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed * 3 / 2 / 180);
		reset_distance();
		record_mode_sensor = 0;
		R_stop
		;
		L_stop
		;
		HAL_Delay(700);
		highspeed_mode = 0;
		STBYOFF;

	} else {
		const_speed_wallcutslantL(turnpara.f_ofset, turnpara.g_speed, turnpara.f_ofset);
		slalom_table(90, turnpara.g_speed, turnpara.t_speed, turnpara.t_acc);
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed, 23456);
		wall_control_mode = 5;
	}
}

void testturning(parameter_speed Howspeed,int turnmode,char funmode,int funduty){
	//0=slalomR,1=slalomL,2=90R,3=90L,4=180R,5=180L,6=in45R,7=in45L,8=in135R,9=in135L
	//10=out45R,11=out45L,12=out135R,13=out135L,14=V90R,15=V90L
	if(funmode==ON){

					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,funduty);
					HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
					HAL_Delay(600);
					reset_ICM();
					enc.sigma_error = 0;
						Gyro.sigma_error = 0;
						angle=0;


	}else{
		HAL_Delay(500);
		reset_ICM();
		HAL_Delay(500);
	}

	if(turnmode==0){slalomR(Howspeed.slalom_R,ON);}
	if(turnmode==1){slalomL(Howspeed.slalom_L,ON);}
	if(turnmode==2){turn90R(Howspeed.turn90_R,ON);}
	if(turnmode==3){turn90L(Howspeed.turn90_L,ON);}
	if(turnmode==4){turn180R(Howspeed.turn180_R,ON);}
	if(turnmode==5){turn180L(Howspeed.turn180_L,ON);}
	if(turnmode==6){turn45inR(Howspeed.turn45in_R,ON);}
	if(turnmode==7){turn45inL(Howspeed.turn45in_L,ON);}
	if(turnmode==8){turn135inR(Howspeed.turn135in_R,ON);}
	if(turnmode==9){turn135inL(Howspeed.turn135in_L,ON);}
	if(turnmode==10){turn45inL(Howspeed.turn45in_L, connect);turn45outR(Howspeed.turn45out_R,ON);}
	if(turnmode==11){turn45inR(Howspeed.turn45in_R, connect);turn45outL(Howspeed.turn45out_L,ON);}
	if(turnmode==12){turn135inL(Howspeed.turn135in_L, connect);turn135outR(Howspeed.turn135out_R,ON);}
	if(turnmode==13){turn135inR(Howspeed.turn135in_R, connect);turn135outL(Howspeed.turn135out_L,ON);}
	if(turnmode==14){turn45inL(Howspeed.turn45in_L, connect);V90R(Howspeed.V90_R,ON);}
	if(turnmode==15){turn45inR(Howspeed.turn45in_R, connect);V90L(Howspeed.V90_L,ON);}

	HAL_Delay(500);
				HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
}
