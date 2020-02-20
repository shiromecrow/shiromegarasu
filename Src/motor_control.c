/*
 * motor_control.c
 *
 *  Created on: 2019/06/20
 *      Author: sf199
 */
#include "tim.h"
#include "IEH2-4096.h"
#include "define.h"
#include "motor_control.h"
#include "SENSOR_control.h"
#include "ICM_20602.h"
#include "yellow_LED.h"
#include "maze_wall.h"
#include "maze_strategy.h"

//float PID_straight(void) {
//	float PID_s = 0;
//	if (modeacc == 1 || modeacc == 4 || modeacc == 2) {
//		PID_s = Ksp * (ideal_speed - (E_speedR + E_speedL) / 2)
//				+ Ksi * enc.sigma_error //(ideal_distance - (E_distanceR + E_distanceL) / 2)
//				+ Ksd * enc.delta_error; //(ideal_acceleration
//				//	- (E_accelerationR + E_accelerationL) / 2);
//		enc.old_error = enc.error;
//		enc.error = (ideal_speed - (E_speedR + E_speedL) / 2);
//		enc.delta_error = enc.error - enc.old_error;
//		enc.sigma_error += enc.error;
//
//	}
////	if(modeacc==2){
////		PID_s=0;
////	}
//	if (modeacc == 3) {
//		PID_s = Ksdenkai * (-gf_speed) + Ksienkai * (-gf_distance);
//		// PID_s =( Ksp * (ideal_speed - (E_speedR + E_speedL) / 2)
//		//			+ Ksi * (ideal_distance - (E_distanceR + E_distanceL) / 2)
//		//		+ Ksd
//		//			* (ideal_acceleration
//		//				- (E_accelerationR + E_accelerationL) / 2))/2;
//
//		//PID_s =0;
//	}
//	return PID_s;
//
//}
//float PID_turning(void) {
//	float PID_t = 0;
//	float PID_sen, PID_turn;
//	PID_t = 0;
//	PID_sen = 0;
//	PID_turn = 0;
//	if (SEN[1][0] >= SENnoR2 && SEN[3][0] >= SENnoL2) {
//		PID_sen = SENGain2 * ((SEN[1][0] - SENR2) - (SEN[3][0] - SENL2));
//	}		 			//SENGainD*(SEND[0]-SEND[4])
//	if (SEN[1][0] < SENnoR2 && SEN[3][0] >= SENnoL2) {
//		PID_sen = SENGain2 * (-2 * (SEN[3][0] - SENL2));	//SENGainD*-SEND[4]
//	}
//	if (SEN[1][0] >= SENnoR2 && SEN[3][0] < SENnoL2) {
//		PID_sen = SENGain2 * (2 * (SEN[1][0] - SENR2));		 //SENGainD*SEND[0]
//	}
//	if (SEN[1][0] < SENnoR2 && SEN[3][0] < SENnoL2) {
//		PID_sen = 0;
//	}
//	if (SEND[1] <= -SENkireR2) {
//		PID_sen = SENGain2 * (-2 * (SEN[3][0] - SENL2));
//	}
//	if (SEND[3] <= -SENkireL2) {
//		PID_sen = SENGain2 * (2 * (SEN[1][0] - SENR2));
//	}
//	if (SEND[3] <= -SENkireL2 && SEND[1] <= -SENkireR2) {
//		PID_sen = 0;
//	}
//	if (SEN[2][0] >= f_presence) {
//		PID_sen = 0;
//	}
//
//	PID_turn = Ktp * (Turn_ideal_speed - angle_speed) + Kti * Gyro.sigma_error//(Turn_ideal_distance - angle)
//	+ Ktd * Gyro.delta_error;		 			//(Turn_ideal_acceleration
//	//	- angle_acceleration);
//	Gyro.old_error = Gyro.error;
//	Gyro.error = (Turn_ideal_speed - angle_speed);
//	Gyro.delta_error = Gyro.error - Gyro.old_error;
//	Gyro.sigma_error += Gyro.error;
////	if(SEN[0][0]>=SENnoR && SEN[4][0]>=SENnoL){
////	PID_sen = SENGain * (-(SEN[0][0] - SENR) + (SEN[4][0] - SENL));
////	}//SENGainD*(SEND[0]-SEND[4])
////	if(SEN[0][0]<SENnoR && SEN[4][0]>=SENnoL){
////		PID_sen = SENGain * (2*(SEN[4][0] - SENL));//SENGainD*-SEND[4]
////	}
////	if(SEN[0][0]>=SENnoR && SEN[4][0]<SENnoL){
////	PID_sen = SENGain * (-2*(SEN[0][0] - SENR) );//SENGainD*SEND[0]
////	}
////	if(SEN[0][0]<SENnoR && SEN[4][0]<SENnoL){
////	PID_sen = 0;
////	}
////	if(SEN[2][0]>=f_presence){PID_sen = 0;}
////	PID_turn= Ktp * (Turn_ideal_speed - angle_speed)
////			+ Kti * (Turn_ideal_distance - angle)
////			+ Ktd
////					* (Turn_ideal_acceleration
////							- angle_acceleration);
//	PID_sen = 0;
//	if (modeacc == 2 || modeacc == 3 || modeacc == 4) {
//		PID_t = PID_turn;
//	}
//	if (modeacc == 1) {
//
//		PID_t = PID_turn;						//*****************************
//		//PID_sen+
//	}
//
//	return PID_t;
//
//}
//
//

void motor_PID(void) {
//XXXX壁制御OFFFFFFFFF

	PID_all_R = 0;
	PID_all_L = 0;

	if (modeacc == 0) {
		straight_mode = 0;
		turning_mode = 0;
		wall_control_mode = 0;
	}
	if (modeacc == 1) {
		straight_mode = 1;
		turning_mode = 1;
		//wall_control_mode = 0;
	} //直線
	if (modeacc == 2) {
		straight_mode = 1;
		turning_mode = 1;
		wall_control_mode = 0;
	} //旋回
	if (modeacc == 3) {
		straight_mode = 1;
		turning_mode = 1;
		wall_control_mode = 0;
	} //宴会芸
	if (modeacc == 4) {
		straight_mode = 1;
		turning_mode = 1;
		wall_control_mode = 0;
	} //スラローム

	if (straight_mode == 1) {
		PID_stra = Ksp * (ideal_speed - (E_speedR + E_speedL) / 2)
				+ Ksi * enc.sigma_error + Ksd * enc.delta_error; //(ideal_distance - (E_distanceR + E_distanceL) / 2)
				//(ideal_acceleration-(E_accelerationR + E_accelerationL) / 2);
		enc.old_error = enc.error;
		enc.error = (ideal_speed - (E_speedR + E_speedL) / 2);
		enc.delta_error = enc.error - enc.old_error;
		enc.sigma_error += enc.error;

		PID_all_R += PID_stra;
		PID_all_L += PID_stra;
	}

	if (turning_mode == 1) {
		if (pulse_turnR_mode == 0 && pulse_turnL_mode == 0) {
			PID_turn = Ktp * (Turn_ideal_speed - angle_speed)
					+ Kti * Gyro.sigma_error //(ideal_distance - (E_distanceR + E_distanceL) / 2)
					+ Ktd * Gyro.delta_error; //(ideal_acceleration-(E_accelerationR + E_accelerationL) / 2);
			Gyro.old_error = Gyro.error;
			Gyro.error = (Turn_ideal_speed - angle_speed);
			Gyro.delta_error = Gyro.error - Gyro.old_error;
			Gyro.sigma_error += Gyro.error;
			PID_all_R += PID_turn;
			PID_all_L -= PID_turn;

		} else {
			PID_turn = Ktp * ((Turn_ideal_speed + pulse_speed) - angle_speed)
					+ Kti * Gyro.sigma_error //(ideal_distance - (E_distanceR + E_distanceL) / 2)
					+ Ktd * Gyro.delta_error; //(ideal_acceleration-(E_accelerationR + E_accelerationL) / 2);
			Gyro.old_error = Gyro.error;
			Gyro.error = (Turn_ideal_speed + pulse_speed - angle_speed);
			Gyro.delta_error = Gyro.error - Gyro.old_error;
			Gyro.sigma_error += Gyro.error;
			PID_all_R += PID_turn;
			PID_all_L -= PID_turn;

		}

	}

	SEN_distanceR = -0.0000001684 * SEN[0][0] * SEN[0][0] * SEN[0][0]
			+ 0.0004061427 * SEN[0][0] * SEN[0][0] - 0.3784837856 * SEN[0][0]
			+ 197.1162;
	//= -0.0000001684 x3 + 0.0004061427 x2 - 0.3784837856 x + 198.2431153122
//	if(SEN_distanceR<=45){
//		SEN_distanceR=SEN_distanceR- 1.00*SEN[1][0];
//	}
////	if(SEN[1][0]<=R_SEN_MIN){}
//
////	= -0.000000098976806 x3 + 0.000271717250210 x2 - 0.268910429926034 x + 146.265920044494000
//
	SEN_distanceL = -0.0000003162 * SEN[4][0] * SEN[4][0] * SEN[4][0]
			+ 0.0006010785 * SEN[4][0] * SEN[4][0] - 0.4363050788 * SEN[4][0]
			+ 190.114;
	//-0.0000003162 x3 + 0.0006010785 x2 - 0.4363050788 x + 186.9452260971
//	if(SEN_distanceL<=45){
//		SEN_distanceL=SEN_distanceL- 1.0*SEN[3][0];
//
//	}

	//0.000000162180790 x3
	//0.000428097590856 x2
	//- 0.382634232978450 x
	//+ 164.233684896545000

	if (wall_control_mode == 1) {
		//wall_status = 3;
//		if (SEN[1][0] >= SENnoR2 && SEN[3][0] >= SENnoL2 && SEND[1] >= -SENstayR2 && SEND[1] <= SENstayR2 && SEND[3] >= -SENstayL2 && SEND[3] <= SENstayL2) {
//			wall_status = 0;
//		}		 			//SENGainD*(SEND[0]-SEND[4])
//		if (SEN[1][0] < SENnoR2 && SEN[3][0] >= SENnoL2 && SEND[3] >= -SENstayL2 && SEND[3] <= SENstayL2) {
//
//			wall_status = 1;
//		}
//		if (SEN[1][0] >= SENnoR2 && SEN[3][0] < SENnoL2 && SEND[1] >= -SENstayR2 && SEND[1] <= SENstayR2) {
//			//SENGainD*SEND[0]
//			wall_status = 2;
//		}
//
//		if (SEND[1] <= -SENkireR2) {
//			wall_status = 1;
//		}
//		if (SEND[3] <= -SENkireL2) {
//			wall_status = 2;
//		}
//
//		if (SEN[1][0] < SENnoR2 && SEN[3][0] < SENnoL2) {
//			wall_status = 3;
//		}
//		if (SEND[3] <= -SENkireL2 && SEND[1] <= -SENkireR2) {
//			wall_status = 3;
		//}
		if (wall_status == 0) {
			if ((SEND[0] <= -SENstayR && SEND[4] >= -SENstayL)
					|| (SEN[0][0] < SENnoR && SEN[4][0] >= SENnoL)
					|| (SEND[4] <= SENstayL && SEND[0] >= SENstayR)) {
				wall_status = 1;
				status_change = 1;
			}
			if ((SEND[4] <= -SENstayL && SEND[0] >= -SENstayR)
					|| (SEN[0][0] >= SENnoR && SEN[4][0] < SENnoL)
					|| (SEND[4] >= SENstayL && SEND[0] <= SENstayR)) {
				wall_status = 2;
				status_change = 1;
			}

			if (SEND[4] <= -SENstayL && SEND[0] <= -SENstayR) {
				wall_status = 3;
				status_change = 1;
			}
			if (SEN[0][0] < SENnoR && SEN[4][0] < SENnoL) {
				wall_status = 3;
				status_change = 1;
			}
			if (SEND[4] >= SENstayL && SEND[0] >= SENstayR) {
				wall_status = 3;
				status_change = 1;
			}
		}
		if (wall_status == 1 && status_change == 0) {
			if (SEND[4] <= -SENstayL || (SEN[4][0] < SENnoL)
					|| (SEND[4] >= SENstayL)) {
				wall_status = 3;
				status_change = 1;
			}
			if (SEN[0][0] >= SENnoR && SEN[4][0] >= SENnoL
					&& SEND[0] >= -SENstayR && SEND[0] <= SENstayR) {
				count_stay++;

			} else {
				count_stay = 0;
			}
			if (count_stay >= 12) {
				wall_status = 0;
				status_change = 1;
			}

		}

		if (wall_status == 2 && status_change == 0) {
			if ((SEND[0] <= -SENstayR) || (SEN[0][0] < SENnoR)
					|| (SEND[0] >= SENstayR)) {
				wall_status = 3;
				status_change = 1;
			}
			if (SEN[0][0] >= SENnoR && SEN[4][0] >= SENnoL
					&& SEND[4] >= -SENstayL && SEND[4] <= SENstayL) {
				count_stay++;

			} else {
				count_stay = 0;
			}
			if (count_stay >= 12) {
				wall_status = 0;
				status_change = 1;
			}

		}
		if (wall_status == 3 && status_change == 0) {

			if (SEN[0][0] >= SENnoR && SEND[0] >= -SENstayR
					&& SEND[0] <= SENstayR) {
				count_stay++;

			} else {
				count_stay = 0;
			}
			if (SEN[4][0] >= SENnoL && SEND[4] >= -SENstayL
					&& SEND[4] <= SENstayL) {
				count_stay2++;

			} else {
				count_stay2 = 0;
			}
			if (count_stay >= 12) {
				wall_status = 2;
				status_change = 1;
			}
			if (count_stay2 >= 12) {
				wall_status = 1;
				status_change = 1;
			}

		}
		if (wall_status == 4 && status_change == 0) {

			if (SEN[0][0] >= SENnoR) {
				wall_status = 2;
				status_change = 1;

			}
			if (SEN[4][0] >= SENnoL) {
				wall_status = 1;
				status_change = 1;

			}
			if (SEN[4][0] >= SENnoL && SEN[0][0] >= SENnoR) {
				wall_status = 0;
				status_change = 1;

			}
			if (SEN[4][0] < SENnoL && SEN[0][0] < SENnoR) {
				wall_status = 3;
				status_change = 1;

			}

		}
//		if (SEN[2][0] >= SENFno) {
//			wall_status = 3;
//		}
//
//		if (SEN[0][0] <= l_presence) {
//			wall_status = 3;
//		}
//		if (SEN[4][0] <= r_presence) {
//			wall_status = 3;
//		}
//センサー13がある一定以上であるとき一定距離走ったらセンサONにするように工夫しろ
		if (wall_status == 0) {
			//PID_wall = SENGain2 * ((SEN[1][0] - SENR2) - (SEN[3][0] - SENL2));
			//PID_wall = SENGain * ((SEN[0][0] - SENR) - (SEN[4][0] - SENL));
			PID_wall = SENGain3
					* (-(SEN_distanceR - 85) + (SEN_distanceL - 85));
			//			if (angle < 0) {
//				PID_wall = SENGain3
//						* (-(SEN_distanceR + SENanglegain * angle - 85)
//								+ (SEN_distanceL - 85));
//			}
//			if (angle >= 0) {
//				PID_wall = SENGain3
//						* (-(SEN_distanceR - 85)
//								+ (SEN_distanceL - 85 - SENanglegain * angle));
//				yellow_on();
//			}

		}
		if (wall_status == 1) {
			//PID_wall = SENGain2 * (-2 * (SEN[3][0] - SENL2));
			PID_wall = SENGain3 * (2 * (SEN_distanceL - 85));
//			if (angle < 0) {
//				PID_wall = SENGain3 * (2 * (SEN_distanceL - 85));
//			} else {
//				PID_wall = SENGain3
//						* (2 * (SEN_distanceL - 85 - SENanglegain * angle));
//			}
			yellow_count(240);
		}
		if (wall_status == 2) {
			//	PID_wall = SENGain2 * (2 * (SEN[1][0] - SENR2));
			PID_wall = SENGain3 * (-2 * (SEN_distanceR - 85));
//			if (angle < 0) {
//				PID_wall = SENGain3
//						* (-2 * (SEN_distanceR - 85 + SENanglegain * angle));
//			} else {
//				PID_wall = SENGain3 * (-2 * (SEN_distanceR - 85));
//			}
			yellow_count(15);
		}
		if (wall_status == 3 && wall_status == 4) {
			PID_wall = 0;
			yellow_off();
		}
//		if (SEN[2][0] >= 1200) {
//			PID_wall = 0;
//		}
		if (highspeed_mode == 1) {
			PID_wall = PID_wall * 0.7;
		}

		PID_all_R += PID_wall;
		PID_all_L -= PID_wall;
		status_change = 0;
	}
	if (wall_control_mode == 0) {
		wall_status = 4;
		count_stay = 0;
		count_stay2 = 0;
		yellow_off();
	}

	if (wall_control_mode == 6) {			//5と6はミスや直すのめんどい

		if (SEN[1][0] >= SENslantR && pulse_turnR_mode == 0
				&& pulse_turnL_mode == 0) {
			pulse_turnR_mode = 1;			//modeの立てる
			pulse_time = 0;
			if (ideal_speed <= 800) {
							input_pulse_speed = 0;
						}
			if (ideal_speed <= 1200 && ideal_speed > 800) {
				input_pulse_speed = 0.0000925607 * ideal_speed * ideal_speed
						- 0.23652355 * ideal_speed + 182.17;
			}
			if (ideal_speed > 1200 && ideal_speed <= 3500) {
				input_pulse_speed = 0.00000284 * ideal_speed * ideal_speed
						- 0.0216506908 * ideal_speed + 51.2905149161-1;
			}
			if (ideal_speed >= 3500) {
				input_pulse_speed = 5;
			}
		}
		if (SEN[3][0] >= SENslantL && pulse_turnR_mode == 0
				&& pulse_turnL_mode == 0) {
			pulse_turnL_mode = 1;			//modeの立てる
			pulse_time = 0;
			if (ideal_speed <= 800) {
										input_pulse_speed = 0;
									}
			if (ideal_speed <= 1200 && ideal_speed > 800) {
				input_pulse_speed = 0.0000925607 * ideal_speed * ideal_speed
						- 0.23652355 * ideal_speed + 182.17;
			}
			if (ideal_speed > 1200 && ideal_speed <= 3500) {
				input_pulse_speed = 0.00000284 * ideal_speed * ideal_speed
						- 0.0216506908 * ideal_speed + 51.2905149161;
			}
			if (ideal_speed >= 3500) {
				input_pulse_speed = 5;
			}
		}
		if (pulse_turnR_mode == 1) {
			PID_all_R -= PID_turn;			//turnの制御を0にする.
			PID_all_L += PID_turn;			//turnの制御を0にする.
			if (pulse_time >= slant_period_Gain / ideal_speed * 1000) {
				if (pulse_time <= slant_period_Gain / ideal_speed * 1000 / 2) {

					pulse_speed = input_pulse_speed;
				} else {
					pulse_speed = -input_pulse_speed;
				}

				pulse_time++;
			} else {
				pulse_turnL_mode = 0;
				pulse_turnR_mode = 0;
				pulse_time = 0;
				pulse_speed = 0;
			}

		}
		if (pulse_turnL_mode == 1) {
			PID_all_R -= PID_turn;			//turnの制御を0にする.
			PID_all_L += PID_turn;			//turnの制御を0にする.
			if (pulse_time >= slant_period_Gain / ideal_speed * 1000) {
				if (pulse_time <= slant_period_Gain / ideal_speed * 1000 / 2) {
					PID_all_R += PID_wall;
					pulse_speed = -input_pulse_speed;
				} else {
					pulse_speed = input_pulse_speed;
				}

				pulse_time++;
			} else {
				pulse_turnL_mode = 0;
				pulse_turnR_mode = 0;
				pulse_time = 0;
				pulse_speed = 0;
			}
		}

	} else {
		pulse_turnL_mode = 0;
		pulse_turnR_mode = 0;
		pulse_time = 0;
		pulse_speed = 0;
	}

//		if (No_wall_modeRslant == 1) {
//			s_disR += (E_speedR + E_speedL) / 2000;
//			if (s_disR <= 70) {
//				slantRSEN = (int) (-0.0007917 * s_disR * s_disR * s_disR
//						+ 0.2620983 * s_disR * s_disR - 0.7279555 * s_disR
//						+ 280.9759381);
//			} else {
////				slantRSEN =
////						(int) (-0.0002516 * s_disR * s_disR * s_disR
////								+ 0.1715433 * s_disR * s_disR
////								- 37.4327746 * s_disR + 2750.51316);
//				slantRSEN = SEN[0][0];
//			}
//		}
//		if (SEN[1][0] >= 2000) {
//			slantRSEN = SEN[0][0];
//			s_disR = 0;
//		}
//
//		if (No_wall_modeLslant == 1) {
//			s_disL += (E_speedR + E_speedL) / 2000;
//			if (s_disL <= 70) {
//				slantLSEN = (int) (-0.0000321 * s_disL * s_disL * s_disL
//						+ 0.1234085 * s_disL * s_disL + 0.2954131 * s_disL
//						+ 179.2419508);
//			} else {
////				slantLSEN = (int) (-0.0001276 * s_disL * s_disL * s_disL
////						+ 0.0954629 * s_disL * s_disL - 22.6835213 * s_disL
////						+ 1811.4144672);
//				slantLSEN = SEN[4][0];
//			}
//		}
//		if (SEN[3][0] >= 2000) {
//			slantRSEN = SEN[0][0];
//			s_disL = 0;
//		}
//		if (slant_start == 1) {
//			wall_status = 0;
//
//			if (wall_status == 0) {
//
//				PID_wall = SENGainslant
//						* (-(SEN[0][0] - slantRSEN) + (SEN[4][0] - slantLSEN));
//				yellow_on();
//			}
//
//			if (wall_status == 1) {
//				PID_wall = SENGainslant * (2 * (SEN[4][0] - slantLSEN));
//				yellow_count(240);
//			}
//			if (wall_status == 2) {
//				PID_wall = SENGainslant * (-2 * (SEN[0][0] - slantRSEN));
//				yellow_count(15);
//			}
//			if (wall_status == 3 && wall_status == 4) {
//				PID_wall = 0;
//				yellow_off();
//			}
//
//			PID_all_R += PID_wall;
//			PID_all_L -= PID_wall;
//			status_change = 0;
//
//		} else {
//			slant_dis += (E_speedR + E_speedL) / 2000;
//			if (slant_dis >= 180 * 1.414 + 10) {
//				slant_start = 1;
//				slant_dis = 0;
//
//			}
//
//		}
//
//	} else {
//		slant_start = 0;
//		slant_dis = 0;
//	}

}

void get_duty(float V_R, float V_L) {
//トルクの方向決定
	if (V_R <= 0) {
		R_back
		;
		duty_R = (int) (-V_R / 8 * MAXMOTOR);
	}
	if (V_L <= 0) {
		L_back
		;
		duty_L = (int) (-V_L / 8 * MAXMOTOR);
	}
	if (V_R >= 0) {
		R_front
		;
		duty_R = (int) (V_R / 8 * MAXMOTOR);
	}
	if (V_L >= 0) {
		L_front
		;
		duty_L = (int) (V_L / 8 * MAXMOTOR);
	}
	//XX
	if (duty_R >= (int) (MAXMOTOR)) {
		duty_R = (int) (MAXMOTOR);
//		r_blue_on;
	}
	if (duty_L >= (int) (MAXMOTOR)) {
		duty_L = (int) (MAXMOTOR);
//		l_blue_on;
	}

}
void get_duty2(int V_R, int V_L) {
//トルクの方向決定
	if (V_R <= 0) {
		R_back
		;
		duty_R = -V_R;
	}
	if (V_L <= 0) {
		L_back
		;
		duty_L = -V_L;
	}
	if (V_R >= 0) {
		R_front
		;
		duty_R = V_R;
	}
	if (V_L >= 0) {
		L_front
		;
		duty_L = V_L;
	}
	//XX
	if (duty_R >= MAXMOTOR) {
		duty_R = MAXMOTOR;
//		r_blue_on;
	}
	if (duty_L >= MAXMOTOR) {
		duty_L = MAXMOTOR;
//		l_blue_on;
	}

}

void const_accel(float input_start_speed, float input_max_speed,
		float input_acceleration) {

	float V_R, V_L;
	start_speed = input_start_speed;
	max_speed = input_max_speed;
	acceleration = input_acceleration;
	Turn_start_speed = 0;
	Turn_max_speed = 0;
	Turn_acceleration = 0;
//if(input_acceleration<=0){
//	input_acceleration=input_acceleration*-1;
//}
	m_timCount = 0;
	modeacc = 1;
//	V_R = (((Im * ng * acceleration / 1000 / tireR) + Tw) * Rm / kt)
//			+ (E_speedR / 1000 * ng * kb / tireR);
//	V_L = (((Im * ng * acceleration / 1000 / tireR) + Tw) * Rm / kt)
//			+ (E_speedL / 1000 * ng * kb / tireR);
//	get_duty(V_R, V_L);

	while (m_timCount
			<= (int) ((max_speed - start_speed) / input_acceleration * 1000)) {
//ww++;
//if(ww >= 256){ww=0;}
//yellow_count(ww);
		HAL_Delay(1);
		//printf("%f\n", E_accelerationR);
		//printf("R=%d L=%d %d %d\n",duty_R,duty_L,(int)((max_speed - start_speed) / acceleration * 1000),m_timCount);
		//printf("R  dis=%f,speed=%f,   L  dis=%f,speed=%f\n",E_distanceR,E_speedR,E_distanceL,E_speedL);
		//printf("%f %f %f %d\n",ideal_speed,E_speedR,dutyper_R,duty_R);
	}
	modeacc = 0;

}

void straight_const_accel(float input_min_distance, float input_start_speed,
		float input_max_speed, float input_acceleration) {

	float V_R, V_L;
	start_speed = input_start_speed;
	max_speed = input_max_speed;
	acceleration = input_acceleration;
	Turn_start_speed = 0;
	Turn_max_speed = 0;
	Turn_acceleration = 0;
//if(input_acceleration<=0){
//	input_acceleration=input_acceleration*-1;
//}
	m_timCount = 0;
	modeacc = 1;
//	V_R = (((Im * ng * acceleration / 1000 / tireR) + Tw) * Rm / kt)
//			+ (E_speedR / 1000 * ng * kb / tireR);
//	V_L = (((Im * ng * acceleration / 1000 / tireR) + Tw) * Rm / kt)
//			+ (E_speedL / 1000 * ng * kb / tireR);
	//get_duty(V_R, V_L);
	if (acceleration >= 0) {
		while ((m_timCount
				<= (int) ((max_speed - start_speed) / acceleration * 1000))
				&& (input_min_distance - (E_distanceR + E_distanceL) / 2
						>= ((E_speedR + E_speedL) * (E_speedR + E_speedL) / 4
								- end_speed * end_speed) / acceleration / 2)) {

//ww++;
//if(ww >= 256){ww=0;}
//yellow_count(ww);
			HAL_Delay(1);
			//printf("R=%d L=%d %d %d\n",duty_R,duty_L,(int)((max_speed - start_speed) / acceleration * 1000),m_timCount);
			//printf("R  dis=%f,speed=%f,   L  dis=%f,speed=%f\n",E_distanceR,E_speedR,E_distanceL,E_speedL);
			//printf("%f %f %f %d\n",ideal_speed,E_speedR,dutyper_R,duty_R);
		}
	} else {
		while ((m_timCount
				<= (int) ((max_speed - start_speed) / acceleration * 1000))
				&& (input_min_distance - (E_distanceR + E_distanceL) / 2
						<= ((E_speedR + E_speedL) * (E_speedR + E_speedL) / 4
								- end_speed * end_speed) / acceleration)) {
			HAL_Delay(1);

		}
	}
	modeacc = 0;

}

void const_speed(float input_distance, float input_speed) {
	//float V_R, V_L;
	start_speed = input_speed;
	max_speed = input_speed;
	end_speed = input_speed;
	acceleration = 0;

	m_timCount = 0;
	modeacc = 1;
//	V_R = (Tw * Rm / kt) + (max_speed / 1000 * ng * kb / tireR);
//	V_L = (Tw * Rm / kt) + (max_speed / 1000 * ng * kb / tireR);
//	get_duty(V_R, V_L);

	while (m_timCount <= input_distance / input_speed * 1000) {	//時間変換**************
		HAL_Delay(1);
		//printf("%f %f %f %d\n",ideal_speed,E_speedR,dutyper_R,duty_R);
	}
	modeacc = 0;

}
void const_speed_wallcut90(float input_distance, float input_speed,
		float cut_distance) {
	//float V_R, V_L;
	start_speed = input_speed;
	max_speed = input_speed;
	end_speed = input_speed;
	acceleration = 0;

	m_timCount = 0;
	modeacc = 1;
//	V_R = (Tw * Rm / kt) + (max_speed / 1000 * ng * kb / tireR);
//	V_L = (Tw * Rm / kt) + (max_speed / 1000 * ng * kb / tireR);
//	get_duty(V_R, V_L);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
	if (no_wall_timeR >= (cut_distance + 35) / input_speed * 1000) {
		while (No_wall_modeR == 1) {
			HAL_Delay(1);
		}
	}
	if (no_wall_timeL >= (cut_distance + 35) / input_speed * 1000) {
		while (No_wall_modeL == 1) {
			HAL_Delay(1);
		}
	}
	while (no_wall_timeR <= cut_distance / input_speed * 1000
			&& no_wall_timeL <= cut_distance / input_speed * 1000) {//時間変換**************
		HAL_Delay(1);

		//printf("%f %f %f %d\n",ideal_speed,E_speedR,dutyper_R,duty_R);
	}
	no_wall_timeR = 0;
	no_wall_timeL = 0;
	no_wall_timeR2 = 0;
	no_wall_timeL2 = 0;
	modeacc = 0;

}
void const_speed_wallcut45(float input_distance, float input_speed,
		float cut_distance) {
	//float V_R, V_L;
	start_speed = input_speed;
	max_speed = input_speed;
	end_speed = input_speed;
	acceleration = 0;

	m_timCount = 0;
	modeacc = 1;
//	V_R = (Tw * Rm / kt) + (max_speed / 1000 * ng * kb / tireR);
//	V_L = (Tw * Rm / kt) + (max_speed / 1000 * ng * kb / tireR);
//	get_duty(V_R, V_L);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
	if (no_wall_timeR2 >= (cut_distance + 25) / input_speed * 1000) {
		while (No_wall_modeR2 == 1) {
			HAL_Delay(1);
		}
	}
	if (no_wall_timeL2 >= (cut_distance + 25) / input_speed * 1000) {
		while (No_wall_modeL2 == 1) {
			HAL_Delay(1);
		}
	}
	while (no_wall_timeR2 <= cut_distance / input_speed * 1000
			&& no_wall_timeL2 <= cut_distance / input_speed * 1000) {//時間変換**************
		//m_timCount <= (input_distance+12) / input_speed * 1000 &&
		HAL_Delay(1);

		//printf("%f %f %f %d\n",ideal_speed,E_speedR,dutyper_R,duty_R);
	}
	no_wall_timeR = 0;
	no_wall_timeL = 0;
	no_wall_timeR2 = 0;
	no_wall_timeL2 = 0;
	modeacc = 0;

}
void const_speed_wallcutslantR(float input_distance, float input_speed,
		float cut_distance) {
	//float V_R, V_L;
	start_speed = input_speed;
	max_speed = input_speed;
	end_speed = input_speed;
	acceleration = 0;

	m_timCount = 0;
	modeacc = 1;
//	V_R = (Tw * Rm / kt) + (max_speed / 1000 * ng * kb / tireR);
//	V_L = (Tw * Rm / kt) + (max_speed / 1000 * ng * kb / tireR);
//	get_duty(V_R, V_L);

	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
	if (no_wall_timeRslant >= (cut_distance + 25) / input_speed * 1000) {
		while (No_wall_modeRslant == 1) {
			HAL_Delay(1);
		}
	}
	while (no_wall_timeRslant <= cut_distance / input_speed * 1000) {//時間変換**************
		//m_timCount <= (input_distance+12) / input_speed * 1000 &&
		HAL_Delay(1);

		//printf("%f %f %f %d\n",ideal_speed,E_speedR,dutyper_R,duty_R);
	}
	no_wall_timeRslant = 0;
	no_wall_timeLslant = 0;

	modeacc = 0;

}
void const_speed_wallcutslantL(float input_distance, float input_speed,
		float cut_distance) {
	//float V_R, V_L;
	start_speed = input_speed;
	max_speed = input_speed;
	end_speed = input_speed;
	acceleration = 0;

	m_timCount = 0;
	modeacc = 1;
//	V_R = (Tw * Rm / kt) + (max_speed / 1000 * ng * kb / tireR);
//	V_L = (Tw * Rm / kt) + (max_speed / 1000 * ng * kb / tireR);
//	get_duty(V_R, V_L);

	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);

	if (no_wall_timeLslant >= (cut_distance + 25) / input_speed * 1000) {
		while (No_wall_modeLslant == 1) {
			HAL_Delay(1);
		}
	}
	while (no_wall_timeLslant <= cut_distance / input_speed * 1000) {//時間変換**************
		//m_timCount <= (input_distance+12) / input_speed * 1000 &&
		HAL_Delay(1);

		//printf("%f %f %f %d\n",ideal_speed,E_speedR,dutyper_R,duty_R);
	}
	no_wall_timeRslant = 0;
	no_wall_timeLslant = 0;

	modeacc = 0;

}

void const_speed_mazemake(float input_distance, float input_speed) {

	start_speed = input_speed;
	max_speed = input_speed;
	end_speed = input_speed;
	acceleration = 0;

	m_timCount = 0;
	ideal_speed = input_speed;
	ideal_acceleration = 0;
	reset_distance();
	ideal_distance = 0;
	modeacc = 1;
//	V_R = (Tw * Rm / kt) + (max_speed / 1000 * ng * kb / tireR);
//	V_L = (Tw * Rm / kt) + (max_speed / 1000 * ng * kb / tireR);
//	get_duty(V_R, V_L);
	__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3,duty_R);
	__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4,duty_L);
//	STBYON;
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
//	if (SENF_maze <= f_presence && SENL_maze >= l_presence
//			&& SENR_maze >= r_presence) {  //前進のみしかないとき
//		maze_makeronly(direction, SENF_maze, SENL_maze, SENR_maze, x, y); //歩数マップ更新しない壁情報のみ更新
//	} else {
	maze_maker2(direction, SENF_maze, SENL_maze, SENR_maze, x, y); //すべて更新
//	}
			//decision_kitiku();
	while (m_timCount <= input_distance / input_speed * 1000) {	//時間変換**************
		HAL_Delay(1);
		//printf("%f %f %f %d\n",ideal_speed,E_speedR,dutyper_R,duty_R);
	}
	modeacc = 0;

}

void const_speed_mazemakeback(float input_distance, float input_speed) {

	start_speed = input_speed;
	max_speed = input_speed;
	end_speed = input_speed;
	acceleration = 0;

	m_timCount = 0;
	ideal_speed = input_speed;
	ideal_acceleration = 0;
	reset_distance();
	ideal_distance = 0;
	modeacc = 1;
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);

//	V_R = (Tw * Rm / kt) + (max_speed / 1000 * ng * kb / tireR);
//	V_L = (Tw * Rm / kt) + (max_speed / 1000 * ng * kb / tireR);
//	get_duty(V_R, V_L);
//	if (SENF_maze <= f_presence && SENL_maze >= l_presence
//			&& SENR_maze >= r_presence) {
//		maze_makeronly(direction, SENF_maze, SENL_maze, SENR_maze, x, y);
//	} else {
	maze_makerback(direction, SENF_maze, SENL_maze, SENR_maze, x, y);

//	}
	//decision_kitiku();
	while (m_timCount <= input_distance / input_speed * 1000) {	//時間変換**************
		HAL_Delay(1);
		//printf("%f %f %f %d\n",ideal_speed,E_speedR,dutyper_R,duty_R);
	}
	modeacc = 0;

}

void const_speed_kitiku(float input_distance, float input_speed) {

	start_speed = input_speed;
	max_speed = input_speed;
	end_speed = input_speed;
	acceleration = 0;

	m_timCount = 0;
	ideal_speed = input_speed;
	ideal_acceleration = 0;
	reset_distance();
	ideal_distance = 0;
	modeacc = 1;
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);

	//compress_kitiku();

	while (m_timCount <= input_distance / input_speed * 1000) {	//時間変換**************
		HAL_Delay(1);
	}
	modeacc = 0;

}

void interupt_const_accel(void) {

	int V_R, V_L;
	//float PID_r, PID_l, PID_s, PID_t;
//	PID_s = PID_straight();
//	PID_t = PID_turning();

	ideal_speed = ((float) (m_timCount) / 1000 * acceleration) + start_speed;

	Turn_ideal_speed = 0;
	motor_PID();
//	PID_r = PID_s + PID_t;		//feedback
//	PID_l = PID_s - PID_t;		//feedback

	//PID_r = 0;		//feedback
	//PID_l = 0;		//feedback
	V_R = (int) (PID_all_R);
	V_L = (int) (PID_all_L);
//	if (E_speedR >= 0) {
//		if ((Im * ng * acceleration / 1000 / tireR * Rm / kt) + PID_r > 0) {
//			V_R = (((Im * ng * acceleration / 1000 / tireR) + Tw) * Rm / kt)
//					+ (E_speedR / 1000 * ng * kb / tireR) + PID_r;
//		} else {
//			V_R = (((Im * ng * acceleration / 1000 / tireR) + Tw * Tstop) * Rm
//					/ kt) + (E_speedR / 1000 * ng * kb / tireR) + PID_r;
//		}
//	} else {
//
//		if ((Im * ng * acceleration / 1000 / tireR * Rm / kt) + PID_r > 0) {
//			V_R = (((Im * ng * acceleration / 1000 / tireR) - Tw * Tstop) * Rm
//					/ kt) + (E_speedR / 1000 * ng * kb / tireR) + PID_r;
//		} else {
//			V_R = (((Im * ng * acceleration / 1000 / tireR) - Tw) * Rm / kt)
//					+ (E_speedR / 1000 * ng * kb / tireR) + PID_r;
//		}
//	}
//	if (E_speedL >= 0) {
//		if ((Im * ng * acceleration / 1000 / tireR * Rm / kt) + PID_l > 0) {
//			V_L = (((Im * ng * acceleration / 1000 / tireR) + Tw) * Rm / kt)
//					+ (E_speedL / 1000 * ng * kb / tireR) + PID_l;
//		} else {
//			V_L = (((Im * ng * acceleration / 1000 / tireR) + Tw * Tstop) * Rm
//					/ kt) + (E_speedL / 1000 * ng * kb / tireR) + PID_l;
//		}
//	} else {
//		if ((Im * ng * acceleration / 1000 / tireR * Rm / kt) + PID_l > 0) {
//			V_L = (((Im * ng * acceleration / 1000 / tireR) - Tw * Tstop) * Rm
//					/ kt) + (E_speedL / 1000 * ng * kb / tireR) + PID_l;
//		} else {
//			V_L = (((Im * ng * acceleration / 1000 / tireR) - Tw) * Rm / kt)
//					+ (E_speedL / 1000 * ng * kb / tireR) + PID_l;
//		}
//	}
	get_duty2(V_R, V_L);
__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3,duty_L);
__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4,duty_R);

}

void straight_table(float input_distance, float input_start_speed,
	float input_end_speed, float input_max_speed, float input_acceleration) {
float V_R, V_L;

start_speed = input_start_speed;
max_speed = input_max_speed;
end_speed = input_end_speed;
acceleration = input_acceleration;

m_timCount = 0;
ideal_speed = input_start_speed;
ideal_acceleration = acceleration;
//V_R = (((Im * ng * acceleration / 1000 / tireR) + Tw) * Rm / kt)
//		+ (E_speedR / 1000 * ng * kb / tireR);
//V_L = (((Im * ng * acceleration / 1000 / tireR) + Tw) * Rm / kt)
//		+ (E_speedL / 1000 * ng * kb / tireR);
//get_duty(V_R, V_L);

reset_distance();
ideal_distance = 0;
get_duty(V_R, V_L);
__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3,duty_R);
__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4,duty_L);
//printf("%f,%f,%f,%f,%f,%f,%f\n",start_speed, end_speed, max_speed, acceleration,ideal_speed, ideal_distance, ideal_acceleration);

//STBYON;
HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);

straight_const_accel(input_distance, input_start_speed, input_max_speed,
		input_acceleration);
//		if (input_distance - (E_distanceR + E_distanceL) / 2
//					<= ((E_speedR + E_speedL) * (E_speedR + E_speedL) / 4
//							- input_end_speed * input_end_speed) / input_acceleration) {
const_speed(
		input_distance
				- (2 * input_max_speed * input_max_speed
						- input_start_speed * input_start_speed
						- input_end_speed * input_end_speed) / 2
						/ input_acceleration, input_max_speed);
//yellow_count(200);
//}
const_accel(ideal_speed, input_end_speed, -input_acceleration);

HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_3);
HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_4);
//		yellow_count(120);

}

void no_angle() {
ideal_distance = 0;
ideal_acceleration = 0;
ideal_speed = 0;
acceleration = 0;
start_speed = 0;
angle = 0;
Turn_ideal_distance = 0;
Turn_ideal_acceleration = 0;
Turn_ideal_speed = 0;
Turn_acceleration = 0;
Turn_start_speed = 0;

STBYON;
HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
modeacc = 3;

while (SEN_on[0] <= 300 || SEN_on[2] <= 900 || SEN_on[4] <= 300) {

	HAL_Delay(1);
}

HAL_TIM_PWM_Stop_IT(&htim8, TIM_CHANNEL_4);
HAL_TIM_PWM_Stop_IT(&htim8, TIM_CHANNEL_3);

}
void no_move(float input_distance) {
ideal_distance = input_distance;
ideal_acceleration = 0;
ideal_speed = 0;
acceleration = 0;
start_speed = 0;

STBYON;
HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
modeacc = 1;
while (1) {
	HAL_Delay(1);
}

}

void interupt_angle_const_accel(void) {

int V_R, V_L;
//	float PID_r, PID_l, PID_s, PID_t;
//	PID_s = PID_straight();
//	PID_t = PID_turning();
ideal_speed = 0;
Turn_ideal_speed = ((float) (m_timCount) / 1000 * Turn_acceleration)
		+ Turn_start_speed;

//	PID_r = PID_s + PID_t;		//feedback
//	PID_l = PID_s - PID_t;		//feedback
motor_PID();
//PID_r = 0;		//feedback
//PID_l = 0;		//feedback

V_R = (int) (PID_all_R);
V_L = (int) (PID_all_L);
get_duty2(V_R, V_L);
__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3,duty_L);
__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4,duty_R);

}

void turning_accel(float input_distance, float input_start_speed,
float input_max_speed, float input_acceleration) {	//入力はdeg/sで
//float V_R, V_L;
start_speed = 0;
max_speed = 0;
acceleration = 0;
Turn_start_speed = input_start_speed;
Turn_max_speed = input_max_speed;
Turn_acceleration = input_acceleration;
//Turn_ideal_distance= 0;
Turn_ideal_speed = Turn_start_speed;
Turn_ideal_acceleration = Turn_acceleration;

m_timCount = 0;

HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
//	V_R = 2;
//	V_L = -2;
//	get_duty(V_R, V_L);
modeacc = 2;
while (m_timCount
	< (int) ((Turn_max_speed - Turn_start_speed) / Turn_acceleration * 1000)) {
HAL_Delay(1);
//printf("V_R=%f,V_L=%f",V_R,V_L);
}
//	Turn_start_speed=0;
//	Turn_ideal_acceleration=0;
//	Turn_ideal_speed=0;
//	Turn_ideal_distance=input_distance;
//
//	while((Turn_ideal_distance-angle) >=2 ||(Turn_ideal_distance-angle)<=-2){
//		HAL_Delay(1);
//
//	}
modeacc = 0;
HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_3);
HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_4);

}
void turningtable_accel(float min_distance, float input_start_speed,
float input_max_speed, float input_acceleration) {	//入力はdeg/sで
float V_R, V_L;
float delta;
start_speed = 0;
max_speed = 0;
acceleration = 0;
Turn_start_speed = input_start_speed;
Turn_max_speed = input_max_speed;
Turn_acceleration = input_acceleration;
//Turn_ideal_distance= 0;
Turn_ideal_speed = Turn_start_speed;
Turn_ideal_acceleration = input_acceleration;

m_timCount = 0;

HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
//	V_R = 2;
//	V_L = -2;
//	get_duty(V_R, V_L);
modeacc = 2;
while (m_timCount
	<= (int) ((Turn_max_speed - Turn_start_speed) / Turn_acceleration * 1000)) {
//&& (min_distance - angle>= (angle_speed * angle_speed
//								- Turn_end_speed * Turn_end_speed) / Turn_acceleration)
HAL_Delay(1);
if (min_distance >= 0
		&& (min_distance / 2
				<= (Turn_ideal_speed * Turn_ideal_speed
						- Turn_end_speed * Turn_end_speed) / Turn_acceleration
						/ 2)) {
	break;
}
if (min_distance < 0
		&& (min_distance / 2
				>= (Turn_ideal_speed * Turn_ideal_speed
						- Turn_end_speed * Turn_end_speed) / Turn_acceleration
						/ 2)) {
	break;
}
//printf("V_R=%f,V_L=%f",V_R,V_L);
}
modeacc = 0;
HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_3);
HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_4);

}

void turning_speed(float input_distance, float input_speed) {
float V_R, V_L;
start_speed = 0;
max_speed = 0;
acceleration = 0;
Turn_start_speed = input_speed;
Turn_max_speed = input_speed;
Turn_acceleration = 0;
//Turn_ideal_distance= 0;
Turn_ideal_speed = input_speed;
Turn_ideal_acceleration = 0;

m_timCount = 0;

HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
//	V_R = 2;
//	V_L = -2;
//	get_duty(V_R, V_L);
modeacc = 2;
while (m_timCount <= input_distance / input_speed * 1000) {
HAL_Delay(1);
//printf("V_R=%f,V_L=%f",V_R,V_L);
}
modeacc = 0;
HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_3);
HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_4);

}

void turning_table(float input_distance, float input_start_speed,
float input_end_speed, float input_max_speed, float input_acceleration) {
float V_R, V_L;
HAL_Delay(200);

Turn_start_speed = input_start_speed;
Turn_end_speed = input_end_speed;
Turn_max_speed = input_max_speed;
Turn_acceleration = input_acceleration;
Turn_ideal_distance = 0;
Turn_ideal_speed = Turn_start_speed;
Turn_ideal_acceleration = Turn_acceleration;
m_timCount = 0;

//get_duty(V_R, V_L);

//angle = 0;//ここいらないヨ--------------------------------------------------

//printf("%f,%f,%f,%f,%f,%f,%f\n",start_speed, end_speed, max_speed, acceleration,ideal_speed, ideal_distance, ideal_acceleration);
get_duty(0, 0);	//******************************************************************************************************************************
__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3,duty_R);
__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4,duty_L);

HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
get_duty(0, 0);
//straight_const_accel(input_distance, input_start_speed, input_max_speed,
//	input_acceleration);
turningtable_accel(input_distance, input_start_speed, input_max_speed,
	input_acceleration);
//		if (input_distance - (E_distanceR + E_distanceL) / 2
//					<= ((E_speedR + E_speedL) * (E_speedR + E_speedL) / 4
//							- input_end_speed * input_end_speed) / input_acceleration) {

turning_speed(
	input_distance
			- (2 * input_max_speed * input_max_speed
					- input_start_speed * input_start_speed
					- input_end_speed * input_end_speed) / 2
					/ input_acceleration, input_max_speed);

//yellow_count(200);
//}
turning_accel(input_distance, input_max_speed, input_end_speed,
	-input_acceleration);

HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_3);
HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_4);

angle = angle - input_distance;

//		yellow_count(120);
HAL_Delay(200);
}

void interupt_slalom_const_accel(void) {

int V_R, V_L;
//	float PID_r, PID_l, PID_s, PID_t;
//PID_s = PID_straight();
//PID_t = PID_turning();
//Turn_ideal_acceleration = Turn_acceleration;
Turn_ideal_speed = ((float) (m_timCount) / 1000 * Turn_ideal_acceleration)
	+ Turn_start_speed;
//	Turn_ideal_distance += Turn_ideal_speed * 0.001;
//	ideal_distance += ideal_speed * 0.001;
ideal_speed = max_speed;
//ideal_acceleration = 0;

//	PID_r = PID_s + PID_t;		//feedback
//	PID_l = PID_s - PID_t;		//feedback

//PID_r = 0;		//feedback
//PID_l = 0;		//feedback
motor_PID();

V_R = (int) (PID_all_R);
V_L = (int) (PID_all_L);
get_duty2(V_R, V_L);
__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3,duty_L);
__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4,duty_R);

}

void slalom_accel(float input_distance, float input_start_speed,
float input_max_speed, float input_acceleration) {	//入力はdeg/sで
	//float V_R, V_L;

Turn_start_speed = input_start_speed;
Turn_max_speed = input_max_speed;
Turn_acceleration = input_acceleration;
	//Turn_ideal_distance= 0;
Turn_ideal_speed = Turn_start_speed;
Turn_ideal_acceleration = Turn_acceleration;

m_timCount = 0;

HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
//	V_R = 2;
//	V_L = -2;
//	get_duty(V_R, V_L);
modeacc = 4;
while (m_timCount
< (int) ((Turn_max_speed - Turn_start_speed) / Turn_acceleration * 1000)) {
HAL_Delay(1);
//printf("V_R=%f,V_L=%f",V_R,V_L);
}
//	Turn_start_speed=0;
//	Turn_ideal_acceleration=0;
//	Turn_ideal_speed=0;
//	Turn_ideal_distance=input_distance;
//
//	while((Turn_ideal_distance-angle) >=2 ||(Turn_ideal_distance-angle)<=-2){
//		HAL_Delay(1);
//
//	}
modeacc = 0;
HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_3);
HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_4);

}
void slalomtable_accel(float min_distance, float input_start_speed,
float input_max_speed, float input_acceleration) {	//入力はdeg/sで
float V_R, V_L;
float delta;

Turn_start_speed = input_start_speed;
Turn_max_speed = input_max_speed;
Turn_acceleration = input_acceleration;
	//Turn_ideal_distance= 0;
Turn_ideal_speed = Turn_start_speed;
Turn_ideal_acceleration = input_acceleration;

m_timCount = 0;

HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
//	V_R = 2;
//	V_L = -2;
//	get_duty(V_R, V_L);
modeacc = 4;
while (m_timCount
<= (int) ((Turn_max_speed - Turn_start_speed) / Turn_acceleration * 1000)) {
//&& (min_distance - angle>= (angle_speed * angle_speed
//								- Turn_end_speed * Turn_end_speed) / Turn_acceleration)
HAL_Delay(1);
if (min_distance >= 0
	&& (min_distance / 2
			<= (Turn_ideal_speed * Turn_ideal_speed
					- Turn_end_speed * Turn_end_speed) / Turn_acceleration / 2)) {
break;
}
if (min_distance < 0
	&& (min_distance / 2
			>= (Turn_ideal_speed * Turn_ideal_speed
					- Turn_end_speed * Turn_end_speed) / Turn_acceleration / 2)) {
break;
}
//printf("V_R=%f,V_L=%f",V_R,V_L);
}

modeacc = 0;
HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_3);
HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_4);

}

void slalom_speed(float input_distance, float input_speed) {
float V_R, V_L;

Turn_start_speed = input_speed;
Turn_max_speed = input_speed;
Turn_acceleration = 0;
	//Turn_ideal_distance= 0;
Turn_ideal_speed = input_speed;
Turn_ideal_acceleration = 0;

m_timCount = 0;

HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
	//	V_R = 2;
	//	V_L = -2;
	//	get_duty(V_R, V_L);
modeacc = 4;
while (m_timCount <= input_distance / input_speed * 1000) {
HAL_Delay(1);
//printf("V_R=%f,V_L=%f",V_R,V_L);
}
modeacc = 0;
HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_3);
HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_4);

}

void slalom_table(float input_angle, float g_speed, float a_max_speed,
float input_a_acceleration) {
float V_R, V_L;
	//HAL_Delay(200);
start_speed = g_speed;
max_speed = g_speed;
end_speed = g_speed;
acceleration = 0;
Turn_start_speed = 0;
Turn_end_speed = 0;
Turn_max_speed = a_max_speed;
Turn_acceleration = input_a_acceleration;
Turn_ideal_distance = 0;
Turn_ideal_speed = 0;
Turn_ideal_acceleration = input_a_acceleration;
ideal_speed = g_speed;
ideal_acceleration = 0;
reset_distance();

m_timCount = 0;

	//get_duty(V_R, V_L);

//angle = 0;//ここいらないヨ--------------------------------------------------

//printf("%f,%f,%f,%f,%f,%f,%f\n",start_speed, end_speed, max_speed, acceleration,ideal_speed, ideal_distance, ideal_acceleration);
// get_duty(0, 0);//******************************************************************************************************************************
__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3,duty_R);
__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4,duty_L);

HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
	//get_duty(0, 0);
	//straight_const_accel(input_distance, input_start_speed, input_max_speed,
	//	input_acceleration);
slalomtable_accel(input_angle, 0, a_max_speed, input_a_acceleration);
//		if (input_distance - (E_distanceR + E_distanceL) / 2
//					<= ((E_speedR + E_speedL) * (E_speedR + E_speedL) / 4
//							- input_end_speed * input_end_speed) / input_acceleration) {

slalom_speed(
input_angle - (2 * a_max_speed * a_max_speed) / 2 / input_a_acceleration,
Turn_ideal_speed);

	//yellow_count(200);
	//}
slalom_accel(input_angle, Turn_ideal_speed, 0, -input_a_acceleration);

HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_3);
HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_4);

angle = angle - input_angle;
enc.sigma_error = 0;

No_wall_modeR = 0;
No_wall_modeL = 0;
No_wall_modeR2 = 0;
No_wall_modeL2 = 0;

//		yellow_count(120);
//	HAL_Delay(200);
}
