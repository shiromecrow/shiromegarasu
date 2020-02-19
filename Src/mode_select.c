/*
 * mode_select.c
 *
 *  Created on: 2019/11/27
 *      Author: sf199
 */
#include "yellow_LED.h"
#include "ICM_20602.h"
#include "IEH2-4096.h"
#include "define.h"
#include "SENSOR_control.h"
#include "mode_select.h"
#include "D_speaker.h"

int mode_decision(int now_mode){

int main_modeR=0;
int main_modeL=0;
int main_mode=0;
float dis8 =20;
main_modeR=now_mode%16;
main_modeL=(int)((now_mode-main_modeR)/16);

	yellow_count(main_modeL * 16 + main_modeR);
			MakeMusicScale(main_modeR);
			//ÉÇÅ[ÉhëIë*************************************************************************
			while (gyro.omega_x <= 150) {
				HAL_Delay(1);
				if (E_distanceR >= dis8) {
					if (main_modeR == 15) {
						main_modeR = 0;
					} else {
						main_modeR++;
					}
					reset_distance();

					yellow_count(main_modeL * 16 + main_modeR);
					MakeMusicScale(main_modeR);
				}
				if (E_distanceR <= -dis8) {
					if (main_modeR == 0) {
						main_modeR = 15;
					} else {
						main_modeR = main_modeR - 1;
					}
					reset_distance();
					yellow_count(main_modeL * 16 + main_modeR);
					MakeMusicScale(main_modeR);
				}
				if (E_distanceL >= dis8) {
					if (main_modeL == 15) {
						main_modeL = 0;
					} else {
						main_modeL = main_modeL + 1;
					}
					reset_distance();
					yellow_count(main_modeL * 16 + main_modeR);
					MakeMusicScale(main_modeL);
				}
				if (E_distanceL <= -dis8) {
					if (main_modeL == 0) {
						main_modeL = 15;
					} else {
						main_modeL = main_modeL - 1;
					}
					reset_distance();
					yellow_count(main_modeL * 16 + main_modeR);
					MakeMusicScale(main_modeL);
				}
	//printf("main_mode=%d distance=%f\n",main_mode,E_distanceR);

			}
			yellow_on();
			r_blue_on;
			l_blue_on;
			HAL_Delay(1000);
			sensor_mode = 1;
			while (SEN_on[0] <= 300 || SEN_on[2] <= 900 || SEN_on[4] <= 300) {	//

				if (gyro.omega_x >= 200) {
					main_modeL = 0;
					main_modeR = 0;
					break;
				}
				HAL_Delay(1);
			}
			r_blue_off;
			l_blue_off;
			yellow_off();

			main_mode=main_modeL * 16 + main_modeR;

return main_mode;
}
