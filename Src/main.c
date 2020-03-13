/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 ** This notice applies to any and all portions of this file
 * that are not between comment pairs USER CODE BEGIN and
 * USER CODE END. Other portions of this file, whether
 * inserted by the user or by software development tools
 * are owned by their respective copyright owners.
 *
 * COPYRIGHT(c) 2019 STMicroelectronics
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "yellow_LED.h"
#include "ICM_20602.h"
#include "wait_ms.h"
#include "D_speaker.h"
#include "BATTcheck.h"
#include "IEH2-4096.h"
#include "define.h"
#include "SENSOR_control.h"
#include "motor_control.h"
#include "maze_strategy.h"
#include "record.h"
#include "flash.h"
#include "turning.h"
#include "parameter.h"
#include "mode_select.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */

int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_TIM1_Init();
	MX_ADC1_Init();
	MX_SPI1_Init();
	MX_TIM4_Init();
	MX_UART4_Init();
	MX_TIM6_Init();
	MX_TIM3_Init();
	MX_TIM2_Init();
	MX_TIM8_Init();
	/* USER CODE BEGIN 2 */
	extern float angle;

	ICM20602_init();
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim4);
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start_IT(&htim8);
	HAL_TIM_PWM_MspInit(&htim2);
	HAL_TIM_PWM_MspInit(&htim4);
	HAL_TIM_PWM_MspInit(&htim8);
	HAL_TIM_Encoder_MspInit(&htim1);
	HAL_TIM_Encoder_MspInit(&htim3);

	int MODE=0;
	int subMODE=0;
//input************************************************************
	inputunknow_story();
	inputtyounen();
	inputZelda_song();
	inputitem_get();
	inputseria();
	inputZelda_nazo();
	inputmiss();
	yellow_count(20);
	angle = 0;
	a_speed = 0;
	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
	maze_clean();
	input_parameter();
//input************************************************************
	/* USER CODE END 2 */
	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	battcheak();

//modeの初期化************************************************************************
	speakermode = 0;
	modeacc = 0;
	record_reset();
	sensor_mode = 0;
	slalom_mode = 0;
	No_wall_modeR = 0;
	No_wall_modeL = 0;
	No_wall_modeR2 = 0;
	No_wall_modeL2 = 0;
	no_safty = 0;
	highspeed_mode = 0;
	Avespeed = 1600;
	error_mode = 0;
//modeの初期化************************************************************************
	playSoundData(8, Zelda_nazo);
	speakermode = 0;//0以外で音楽入る
	reset_distance();//距離のリセット
//モーター1717初期化？*************************************************************************
	L_front
	;
	__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3,90);
	R_front
	;
	__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4,90);

//モーター1717初期化？*************************************************************************

	while (1) {

		MODE=mode_decision(MODE);
		reset_ICM();
		enc.sigma_error = 0;
		Gyro.sigma_error = 0;
		playSoundData(8, Zelda_nazo);
		reset_distance();
		speakermode = 0;

		switch (MODE) {
		case 0:
			//モードなし
			break;
		case 1:	//台形加速***********************************
				//HAL_TIM_PWM_Start_IT(&htim8, TIM_CHANNEL_4);
				//	HAL_TIM_PWM_Start_IT(&htim8, TIM_CHANNEL_3);
				//	record_mode_enc=1;
				//	reset_distance();
				//const_accel(0,1000,2000);
				//const_accel(100,200,1000);
				//const_accel(200,500,1500);
				//const_accel(500,600,2000);
				//const_accel(1000,1500,2000);
			p = 0;
			q = 0;
			o = 0;
//			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,150);
//									HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			//	HAL_Delay(1500);
//			reset_ICM();
//			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,160);
//			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
//			HAL_Delay(5000);
//			angle=0;
			HAL_Delay(1000);
			reset_ICM();
			HAL_Delay(100);
			//__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,160);
			//HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);

			//	HAL_Delay(2000);
			//候補1
			//record_mode_enc = 1;
			//record_mode_sensor = 1;

			//straight_table(720, 0, 0, 1000, 2000);//test1

			//printf("%f,%f,%f,%f,%f,%f,%f\n",start_speed, end_speed, max_speed, acceleration,ideal_speed, ideal_distance, ideal_acceleration);

			wall_control_mode = 6;

			STBYON;

//			straight_table(90, 0, 400, 400, 3000);			//test5
//			straight_table(90, 400, 400, 400, 3000);
//			straight_table(90, 400, 400, 400, 6000);
//			straight_table(90, 400, 400, 400, 6000);
//			straight_table(90, 400, 400, 400, 6000);
//			straight_table(90, 400, 0, 400, 3000);

			//	turn90R(1200, 1000, 10000, 45, 70, ON);
			//straight_table(39.5, 0, 1200, 1200, 37000);
//			straight_table((39.5+(90 * 3)), 0, 500, 500, 6000);
//									slalomR(speed500.slalom_R, OFF);
//									straight_table(90, 500, 0, 500, 6000);
			//straight_table(((90 *1.414* 6)), 0, 0, 1500, 6000);
			//slalom_table(180, 0, 400, 13000);
			//straight_table((90 * 8), 1200, 1200,
			//						2100, 6000);
			//straight_table(180, (E_speedR + E_speedL) / 2, 0, (E_speedR + E_speedL) / 2,
			//				6000);
			//straight_table(39.5 + 270, 0, 500, 500, 7000);		//test5
			//		const_speed_wallcut90(48,500,48);
			//	slalom_table(-90, 500, -650, -15000);
			//straight_table(90 + 35, 500, 0, 500, 7000);
			//reset_distance();
			//const_speed_mazemake(20,400);

			//straight_table(70, 400, 0, 400, 6000);
			//const_speed(100,1000);
			//const_accel(1000,0,-2000);
			// const_accel(300,0,-1000);
			//record_mode_enc=0;
			//			HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_3);
			//			HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_4);
			//
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,150);
					HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
					HAL_Delay(5000);
					reset_ICM();
					HAL_Delay(100);
					record_mode_gyro = 1;
					r_blue_on;
					l_blue_on;
					STBYON;
					enc.sigma_error = 0;
					Gyro.sigma_error = 0;
					no_angle();

					HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);


			record_mode_enc = 0;
			record_mode_sensor = 0;
			record_mode_gyro = 0;

			HAL_Delay(700);
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
			//HAL_Delay(700);
			//		HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
			reset_distance();
			HAL_Delay(3000);

			R_stop
			;
			L_stop
			;
			STBYOFF;
			while (SEN_on[0] <= 300 || SEN_on[2] <= 900 || SEN_on[4] <= 300) {
				HAL_Delay(1);
				sensor_mode = 1;
			}
			r_blue_on;
			yellow_count(5);

				//record_out_enc();
			//record_out_sen();
			record_out_gyro();

			break;
		case 2:			//ジャイロ正規分布*********************************************

			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,120);
						HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			wait_ms(1000);
			reset_ICM();
			record_mode_gyro = 1;
			wait_ms(2000);
			record_mode_gyro = 0;
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
			if (SEN_on[2] >= 500) {

				record_out_gyro();
			}
			//ジャイロ正規分布*********************************************
			break;
		case 3:
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,150);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			HAL_Delay(1000);
			reset_ICM();
			r_blue_on;
			l_blue_on;
			STBYON;
			enc.sigma_error = 0;
			Gyro.sigma_error = 0;
			no_angle();

			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);

			break;
		case 4:
			//record_mode_gyro = 1;
			STBYON;
//			turning_table(-180, 0, 0, -400, -5000);
//									HAL_Delay(200);
//									turning_table(-180, 0, 0, -600, -16000);
//									HAL_Delay(200);
//									turning_table(-90, 0, 0, -600, -16000);
//									HAL_Delay(200);
//									turning_table(-90, 0, 0, -600, -16000);
//									HAL_Delay(1000);
			slalom_table(180, 0, 400, 13000);
			//turning_table(180, 0, 0, 400, 13000);
//			turning_table(180, 0, 0, 600, 16000);
//			HAL_Delay(200);
//			turning_table(180, 0, 0, 600, 16000);
//			HAL_Delay(200);
//			turning_table(90, 0, 0, 600, 16000);
//			HAL_Delay(200);
//			turning_table(90, 0, 0, 600, 16000);

//					turning_table(360, 0, 0, 800, 8000);
//					HAL_Delay(200);
//							turning_table(360, 0, 0, 200, 8000);

//			turning_accel(0,800,1000);
//			angle=0;
//			turning_speed(360, 800);
//			angle=0;
//			turning_accel(800,0,-1000);
			record_mode_gyro = 0;
			while (SEN_on[0] <= 300 || SEN_on[2] <= 900 || SEN_on[4] <= 300) {
				HAL_Delay(1);
			}
			record_out_gyro();

			break;
		case 5:

			while (1) {
				//	printf("SENSOR_ON  SEN1=%d,SEN2=%d,SEN3=%d,SEN4=%d,SEN5=%d\n",
				//	SEN_on[0], SEN_on[1], SEN_on[2], SEN_on[3], SEN_on[4]);
//				printf("SEN1=%d,SEN2=%d,SEN3=%d,SEN4=%d,SEN5=%d\n", SEN[0][0],
//						SEN[1][0], SEN[2][0], SEN[3][0], SEN[4][0]);
				HAL_Delay(500);
				//	printf("SENSOR_OFF  SEN1=%d,SEN2=%d,SEN3=%d,SEN4=%d,SEN5=%d\n",
				//					SEN_off[0], SEN_off[1], SEN_off[2], SEN_off[3],SEN_off[4]);
//				printf("R  dis=%f,speed=%f,   L  dis=%f,speed=%f\n",
//						E_distanceR, E_speedR, E_distanceL, E_speedL);

//				printf(
//						"gyro x : %5.5f, y : %5.5f,z : %5.5f, accel x : %5.5f, y :%5.5f, z : %5.5f\r",
//						gyro.omega_x, gyro.omega_y, gyro.omega_z, gyro.accel_x,
//						gyro.accel_y, gyro.accel_z);
				//yellow_on();
				//printf("R  dis=%f,speed=%f,   L  dis=%f,speed=%f\n",E_distanceR,E_speedR,E_distanceL,E_speedL);
				printf("angle=%f,a_speed=%f\n", angle, angle_speed);
			}

			break;
		case 6:
			slalom_mode = 0;
			adati_wayreturn(400, 400, 3000, 13000);
			break;
		case 7:
			maze_maker2(1, 0, 0, 0, 7, 7);
			maze_display();

			break;
		case 8:
			record_out();
			break;
		case 9:
			record_out();
			most_speed(3000, 12000, 0, ON, ON,speed1200);
			break;
		case 10:
			record_out();
			most_speed(2000, 6000, 0, ON, ON,speed1200);
			break;
		case 11:
			record_out();
			most_speed(2100, 6000, 0, ON, OFF,speed1200);
			break;
		case 12:
			slalom_mode = 1;
			adati_wayreturn(500, 400, 7000, 13000);

			break;
		case 13:
			record_out();
			most_speed(1300, 6000, 0, OFF, OFF,speed1200);
			break;
		case 14:
			record_out();
			most_speed(1300, 6000, 0, OFF, ON,speed1200);
			break;
		case 15:
			p = 0;
			q = 0;
			o = 0;
			record_mode_enc = 1;
			//record_mode_sensor = 1;
			//record_mode_gyro = 1;
			//straight_table(720, 0, 0, 1000, 2000);//test1

			//printf("%f,%f,%f,%f,%f,%f,%f\n",start_speed, end_speed, max_speed, acceleration,ideal_speed, ideal_distance, ideal_acceleration);
			__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3,400);
			__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4,400);
			L_back
			;
			R_front
			;
			STBYON;
			HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
			HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
			HAL_Delay(1000);

			HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_3);
			HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_4);
			//

			record_mode_enc = 0;
			record_mode_sensor = 0;
			record_mode_gyro = 0;
			reset_distance();
			HAL_Delay(3000);
			R_stop
			;
			L_stop
			;
			STBYOFF;
			while (SEN_on[0] <= 300 || SEN_on[2] <= 900 || SEN_on[4] <= 300) {
				HAL_Delay(1);
				sensor_mode = 1;
			}
			r_blue_on;
			yellow_count(5);
			record_out_enc();
			//record_out_sen();
			//record_out_gyro();

			//printf("%f,%f,%f,%f,%f,%f,%f\n",start_speed, end_speed, max_speed, acceleration,ideal_speed, ideal_distance, ideal_acceleration);

			break;
		case 16:
			while (1) {
				printf("SEN1=%d,SEN2=%d,SEN3=%d,SEN4=%d,SEN5=%d\n", SEN[0][0],
						SEN[1][0], SEN[2][0], SEN[3][0], SEN[4][0]);
				HAL_Delay(500);
			}
			break;
		case 17:
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,150);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);

			while (SEN_on[0] <= 300 || SEN_on[2] <= 900 || SEN_on[4] <= 300) {

				HAL_Delay(1);
			}
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);

			break;
		case 18:
			playSoundData(169, seria);
			break;
		case 19:
			playSoundData(169, unknow_story);

			break;
		case 20:
			sensor_line();
			break;
		case 21:
			//loadFlash(start_address, (uint16_t*)flash_test, sizeof(flash_test));
			//main_modeR=*flash_test;
			yellow_count(MODE);
			printf("%d\n", MODE);
			//printf("%d\n", *flash_test);
			break;
		case 22:
			//	HAL_FLASH_Unlock();
			//	eraseFlash();
			//	HAL_FLASH_Lock();
			break;
		case 23:
			slalom_mode = 1;
			//		adati_wayreturnkitikunasi(530, 400, 7000, 13000, 650, 15000, 55, 50,
			//		40, 44);			//大会終わったら消す
			break;
		case 24:
			wall_control_mode = 1;
						STBYON;
						straight_table((39.5+(90 * 3)), 0, 500, 500, 6000);
						slalomR(speed500.slalom_R, OFF);
						straight_table(90, 500, 0, 500, 6000);

			break;
		case 25:
			break;
		case 26:
			break;
		case 27:
			break;
		case 28:
			break;
		case 29:
			break;
		case 30:
			break;
		case 31:
			while(1){
			subMODE=mode_decision(subMODE);
			testturning(speed1200,subMODE,ON,100);
			}
			break;
		case 32:
			break;
		case 33:
			break;
		case 34:
			break;
		case 35:
			break;
		case 36:
			break;
		case 37:
			break;
		case 38:
			break;
		case 39:
			break;
		case 40:
			break;
		case 41:
			break;
		case 42:
			break;
		case 43:
			break;
		case 44:
			break;
		case 45:
			break;
		case 46:
			break;
		case 47:
			break;

		case 50://右旋回****************************************************************
			if (angle >= 90 || angle <= -90) {
				HAL_GPIO_WritePin(L_MOTOR_IN2_GPIO_Port, L_MOTOR_IN2_Pin,
						GPIO_PIN_SET);
				HAL_GPIO_WritePin(R_MOTOR_IN2_GPIO_Port, R_MOTOR_IN2_Pin,
						GPIO_PIN_SET);
				HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_3);
				HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_4);
				//	speakermode++;
				//	if(speakermode == 4){speakermode = 1;}
				wait_ms(1000);
				reset_ICM();
				angle = 0;
				angle = 0;
				HAL_GPIO_WritePin(L_MOTOR_IN2_GPIO_Port, L_MOTOR_IN2_Pin,
						GPIO_PIN_SET);
				HAL_GPIO_WritePin(L_MOTOR_IN1_GPIO_Port, L_MOTOR_IN1_Pin,
						GPIO_PIN_RESET);
				__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3,20);

				//モーター駆動(左)
				//モーター駆動(右)
				HAL_GPIO_WritePin(R_MOTOR_IN2_GPIO_Port, R_MOTOR_IN2_Pin,
						GPIO_PIN_SET);
				HAL_GPIO_WritePin(R_MOTOR_IN1_GPIO_Port, R_MOTOR_IN1_Pin,
						GPIO_PIN_RESET);
				__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4,20);
				HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
				HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
			}
			break;
		case 224:
			STBYON;
			wall_control_mode = 1;
			straight_table(39.5 + 270 + 41.5, 0, 400, 400, 3000);		//test5
			slalom_table(-90, 400, -450, -6500);
			straight_table(25, 400, 400, 400, 3000);
			straight_table(38.5, 400, 400, 400, 3000);		//test5
			slalom_table(90, 400, 450, 6500);
			straight_table(20, 400, 400, 400, 3000);
			straight_table(41.5, 400, 400, 400, 3000);		//test5
			slalom_table(-90, 400, -450, -6500);
			straight_table(25, 400, 400, 400, 3000);
			straight_table(38.5, 400, 400, 400, 3000);		//test5
			slalom_table(90, 400, 450, 6500);
			straight_table(25, 400, 400, 400, 3000);
			straight_table(41.5, 400, 400, 400, 3000);		//test5
			slalom_table(-90, 400, -450, -6500);
			straight_table(25, 400, 400, 400, 3000);
			straight_table(38.5, 400, 400, 400, 3000);		//test5
			slalom_table(90, 400, 450, 6500);
			straight_table(20, 400, 400, 400, 3000);
			straight_table(41.5, 400, 400, 400, 3000);		//test5
			slalom_table(-90, 400, -450, -6500);
			straight_table(25, 400, 400, 400, 3000);
			straight_table(38.5, 400, 400, 400, 3000);		//test5
			slalom_table(90, 400, 450, 6500);
			straight_table(90 + 20, 400, 0, 400, 3000);
			reset_distance();
			record_mode_sensor = 0;
			R_stop
			;
			L_stop
			;
			STBYOFF;
			//								while (SEN_on[0] <= 300 || SEN_on[2] <= 900|| SEN_on[4] <= 300) {
			//									HAL_Delay(1);
			//									sensor_mode = 1;
			//								}
			//								r_blue_on;
			//								yellow_count(5);

			//		record_out_sen();
			HAL_Delay(3000);
			R_stop
			;
			L_stop
			;
			break;

		case 225:			//2^7+2^6+2^5+1
			STBYON;
			wall_control_mode = 1;
			straight_table(39.5 + 270 + 41.5, 0, 400, 400, 3000);		//test5
			slalom_table(-90, 400, -450, -6500);
			straight_table(25, 400, 400, 400, 3000);
			straight_table(38.5, 400, 400, 400, 3000);		//test5
			slalom_table(90, 400, 450, 6500);
			straight_table(20, 400, 400, 400, 3000);
			straight_table(38.5, 400, 400, 400, 3000);		//test5
			slalom_table(90, 400, 450, 6500);
			straight_table(20, 400, 400, 400, 3000);
			straight_table(41.5, 400, 400, 400, 3000);		//test5
			slalom_table(-90, 400, -450, -6500);
			straight_table(25, 400, 400, 400, 3000);
			straight_table(41.5, 400, 400, 400, 3000);		//test5
			slalom_table(-90, 400, -450, -6500);
			straight_table(25, 400, 400, 400, 3000);
			straight_table(38.5, 400, 400, 400, 3000);		//test5
			slalom_table(90, 400, 450, 6500);
			straight_table(20, 400, 400, 400, 3000);
			straight_table(38.5, 400, 400, 400, 3000);		//test5
			slalom_table(90, 400, 450, 6500);
			straight_table(20, 400, 400, 400, 3000);
			straight_table(41.5, 400, 400, 400, 3000);		//test5
			slalom_table(-90, 400, -450, -6500);
			straight_table(25 + 90, 400, 0, 400, 3000);

			reset_distance();
			record_mode_sensor = 0;
			R_stop
			;
			L_stop
			;
			STBYOFF;
			//								while (SEN_on[0] <= 300 || SEN_on[2] <= 900|| SEN_on[4] <= 300) {
			//									HAL_Delay(1);
			//									sensor_mode = 1;
			//								}
			//								r_blue_on;
			//								yellow_count(5);

			//		record_out_sen();
			HAL_Delay(3000);
			R_stop
			;
			L_stop
			;
			break;
		case 226:			//2^7+2^6+2^5+2   outR45
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,110);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			HAL_Delay(2000);
			reset_ICM();
			turn45inL(speed800.turn45in_L, connect);
			turn45outR(speed800.turn45out_R, ON);
			HAL_Delay(500);
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
			break;
		case 227:			//2^7+2^6+2^5+3   outL45
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,160);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			HAL_Delay(2000);
			reset_ICM();
			turn45inR(speed800.turn45in_R, connect);
			turn45outL(speed800.turn45out_L, ON);
			HAL_Delay(500);
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
			break;
		case 228:			//2^7+2^6+2^5+4   outR135
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,160);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			HAL_Delay(2000);
			reset_ICM();
			turn135inL(speed800.turn135in_L, connect);
			turn135outR(speed800.turn135out_R, ON);
			HAL_Delay(500);
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
			break;
		case 229:			//2^7+2^6+2^5+5   outL135
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,160);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			HAL_Delay(2000);
			reset_ICM();
			turn135inR(speed800.turn135in_R, connect);
			turn135outL(speed800.turn135out_L, ON);
			HAL_Delay(500);
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
			break;
		case 230:			//2^7+2^6+2^5+6   V90R
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,160);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			HAL_Delay(2000);
			reset_ICM();
			turn45inL(speed800.turn45in_L, connect);
			V90R(speed800.V90_R, ON);
			HAL_Delay(500);
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
			break;
		case 231:			//2^7+2^6+2^5+7   V90L
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,160);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			HAL_Delay(2000);
			reset_ICM();
			turn45inR(speed800.turn45in_R, connect);
			V90L(speed800.V90_L, ON);
			HAL_Delay(500);
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
			break;
			//straight_table(90, 0, inspeed, inspeed, inacc);
			//	const_speed_mazemakeback(20, inspeed);
//調整用だよ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		case 240:			//2^7+2^6+2^5+2^4
			//adati_wayreturn(400, 400, 3000, 13000, 450, 6500, 20, 23, 37, 45);
			//		record_mode_sensor = 1;
			slalomR(speed500.slalom_R, ON);
			break;
		case 241:
			slalomL(speed500.slalom_L, ON);

			break;
		case 242:
			HAL_Delay(1000);
			reset_ICM();
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,110);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			HAL_Delay(2000);
			slalomR(speed1000.slalom_R, ON);
			HAL_Delay(500);
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);

			break;
		case 243:
			HAL_Delay(1000);
			reset_ICM();
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,110);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			HAL_Delay(2000);
			slalomL(speed1000.slalom_L, ON);
			HAL_Delay(500);
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);

			break;
		case 244:
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,110);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			HAL_Delay(500);
			reset_ICM();
//			HAL_Delay(1000);
//			reset_ICM();
//			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,160);
//			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
//			HAL_Delay(2000);
			//	候補1
			turn90R(speed1200.turn90_R, ON);
			HAL_Delay(500);
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);

			break;
		case 245:
			HAL_Delay(1000);
			reset_ICM();
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,110);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			HAL_Delay(1000);

			turn90L(speed1200.turn90_L, ON);
			HAL_Delay(500);
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
			break;
		case 246:
			HAL_Delay(1000);
			reset_ICM();
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,140);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			HAL_Delay(2000);
			turn180R(speed1200.turn180_R, ON);
			HAL_Delay(500);
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
			break;
		case 247:
			HAL_Delay(1000);
			reset_ICM();
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,160);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			HAL_Delay(2000);
			turn180L(speed1200.turn180_L, ON);
			HAL_Delay(500);
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
			break;

		case 248: //45R
			HAL_Delay(1000);
			reset_ICM();
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,160);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			HAL_Delay(2000);
			turn45inR(speed1200.turn45in_R, ON);
			HAL_Delay(500);
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
			break;
		case 249: //45L
			HAL_Delay(1000);
			reset_ICM();
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,160);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			HAL_Delay(2000);
			turn45inL(speed1200.turn45in_L, ON);
			HAL_Delay(500);
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
			break;
		case 250: //135R
			HAL_Delay(1000);
			reset_ICM();
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,160);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			HAL_Delay(2000);
			turn135inR(speed1200.turn135in_R, ON);
			HAL_Delay(500);
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
			break;
		case 251: //135L
			HAL_Delay(1000);
			reset_ICM();
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,160);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			HAL_Delay(2000);
			turn135inL(speed1200.turn135in_L, ON);
			HAL_Delay(500);
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
			break;
		case 252: //V90R
//			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,160);
//			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
//			HAL_Delay(500);
//			reset_ICM();
//			turn45inR(1200, 650, 8000, 10, 10, ON);
//			HAL_Delay(700);
//			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
			break;
		case 253: //V90L
//			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,160);
//			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
//			HAL_Delay(500);
//			reset_ICM();
//			turn45inR(1200, 650, 8000, 10, 10, ON);
//			HAL_Delay(700);
//			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
			break;
		case 255:

			break;
//調整用だよ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

		case 192:
			subMODE=mode_decision(subMODE);
			testturning(speed800,subMODE,0,100);


		}
		error_mode = 0;

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}

	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/**Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE()
	;
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 5;
	RCC_OscInitStruct.PLL.PLLN = 168;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	 tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
