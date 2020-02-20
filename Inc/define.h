/*
 * define.h
 *
 *  Created on: 2019/05/20
 *      Author: sf199
 */

#ifndef DEFINE_H_
#define DEFINE_H_

#define BATTlimit 7.3
#define r_blue_on HAL_GPIO_WritePin(D_LED1_GPIO_Port,D_LED1_Pin,GPIO_PIN_SET)
#define l_blue_on HAL_GPIO_WritePin(D_LED2_GPIO_Port,D_LED2_Pin,GPIO_PIN_SET)
#define r_blue_off HAL_GPIO_WritePin(D_LED1_GPIO_Port,D_LED1_Pin,GPIO_PIN_RESET)
#define l_blue_off HAL_GPIO_WritePin(D_LED2_GPIO_Port,D_LED2_Pin,GPIO_PIN_RESET)
#define ON 1
#define OFF 0
#define connect 2
#define IEH_1cycle 4096
#define L_front do{HAL_GPIO_WritePin(L_MOTOR_IN2_GPIO_Port, L_MOTOR_IN2_Pin, GPIO_PIN_SET);HAL_GPIO_WritePin(L_MOTOR_IN1_GPIO_Port, L_MOTOR_IN1_Pin, GPIO_PIN_RESET);}while(0)
#define L_back do{HAL_GPIO_WritePin(L_MOTOR_IN2_GPIO_Port, L_MOTOR_IN2_Pin, GPIO_PIN_RESET);HAL_GPIO_WritePin(L_MOTOR_IN1_GPIO_Port, L_MOTOR_IN1_Pin, GPIO_PIN_SET);}while(0)
#define L_stop do{HAL_GPIO_WritePin(L_MOTOR_IN2_GPIO_Port, L_MOTOR_IN2_Pin, GPIO_PIN_RESET);HAL_GPIO_WritePin(L_MOTOR_IN1_GPIO_Port, L_MOTOR_IN1_Pin, GPIO_PIN_RESET);}while(0)
#define L_break do{HAL_GPIO_WritePin(L_MOTOR_IN2_GPIO_Port, L_MOTOR_IN2_Pin, GPIO_PIN_SET);HAL_GPIO_WritePin(L_MOTOR_IN1_GPIO_Port, L_MOTOR_IN1_Pin, GPIO_PIN_SET);}while(0)
#define R_front do{HAL_GPIO_WritePin(R_MOTOR_IN2_GPIO_Port, R_MOTOR_IN2_Pin, GPIO_PIN_RESET);HAL_GPIO_WritePin(R_MOTOR_IN1_GPIO_Port, R_MOTOR_IN1_Pin, GPIO_PIN_SET);}while(0)
#define R_back do{HAL_GPIO_WritePin(R_MOTOR_IN2_GPIO_Port, R_MOTOR_IN2_Pin, GPIO_PIN_SET);HAL_GPIO_WritePin(R_MOTOR_IN1_GPIO_Port, R_MOTOR_IN1_Pin, GPIO_PIN_RESET);}while(0)
#define R_stop do{HAL_GPIO_WritePin(R_MOTOR_IN2_GPIO_Port, R_MOTOR_IN2_Pin, GPIO_PIN_RESET);HAL_GPIO_WritePin(R_MOTOR_IN1_GPIO_Port, R_MOTOR_IN1_Pin, GPIO_PIN_RESET);}while(0)
#define R_break do{HAL_GPIO_WritePin(R_MOTOR_IN2_GPIO_Port, R_MOTOR_IN2_Pin, GPIO_PIN_SET);HAL_GPIO_WritePin(R_MOTOR_IN1_GPIO_Port, R_MOTOR_IN1_Pin, GPIO_PIN_SET);}while(0)
#define STBYON HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_SET)
#define STBYOFF HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_RESET)
#define tireR 0.0238//m  dayo*****************************************
#define tread 0.0675//mトレッド幅*****************************************
#define pi 3.1415926535
#define rownumber 15*16*1
#define columnnumber 0

#define MAXMOTOR 1679


//#define Im 0.00000//259//kg/m^2 ロータ慣性モーメント
//#define ng 40/11//ギヤ比
//#define kt 0.00198//Nm/A トルク定数
//#define kb 0.00//35767//Vs/rad 逆起電力定数
//#define Rm 1.37//1.07+0.3Ω 端子間抵抗*******************************************
//#define Tw 0//0.00007//0.00013//Nm 摩擦によるロス調整項目******************************
//#define Tstop 6.7//減速時摩擦倍数
//
//#define ImT 0.0000028//kg/m^2 ロータ慣性モーメントターン用
//#define TwT 0.000//7
//#define TstopT 1//6.7//減速時摩擦倍数
//#define kbT 0.0045//Vs/rad 逆起電力定数 deg->rad->m変換sitenai




#define Ksp 5.1//3//P項の制御量直進*****************************************************
#define Ksi 0.08//5//43//I項の制御量直進*****************************************************
#define Ksd 0.00//D項の制御量直進*****************************************************
#define Ktp 2.5//295//P項の制御量旋回*****************************************************
#define Kti 0.06//1//.6//I項の制御量旋回*****************************************************
#define Ktifun 0.01//1//.6//I項の制御量旋回*****************************************************
#define Ktd 0.006//205//D項の制御量旋回*****************************************************
//
//#define Ksp 0.029//3//P項の制御量直進*****************************************************
//#define Ksi 0.0004//5//43//I項の制御量直進*****************************************************
//#define Ksd 0.00//D項の制御量直進*****************************************************
//#define Ktp 0.0145//295//P項の制御量旋回*****************************************************
//#define Kti 0.001//1//.6//I項の制御量旋回*****************************************************
//#define Ktd 0.00//205//D項の制御量旋回*****************************************************
#define funON 10


#define SENGain 0.7//0.006にしたいけどね
#define SENGainD 0//0.004
#define SENR 845
#define SENL 770
#define SENR85 -0.967157 / 100000000*SENR * SENR * SENR+ 0.622613 / 10000 * SENR * SENR - 0.1346056 * SENR-85
#define SENL85 -0.176541 / 10000000* SENL * SENL * SENL+ 0.924589415615916 / 10000 * SENL * SENL- 0.169330 * SENL-85

#define SENGain2 2.7
#define SENR2 278
#define SENL2 325
#define SENnoR 230
#define SENnoL 180
#define SENnoR2 200
#define SENnoL2 200
#define SENkireR 200
#define SENkireL 200
#define SENkireR2 60
#define SENkireL2 60
#define SENstayR 150
#define SENstayL 150
#define SENstayR2 50
#define SENstayL2 50
#define SENGain3 8.5
#define SENanglegain 0.1//1.2
#define SENGainslant 0.4
#define SENslantR 3000
#define SENslantL 2500
#define slant_period_Gain 40.0//[mm]だよ.縦の進む量
//#define slant_haba_Gain 2.0


#define SENFno 200

#define SENnoRslant 300
#define SENnoLslant 300


#define goal_x 7
#define goal_y 7
#define f_presence 130
#define l_presence 130//180//900
#define r_presence 135//180//900






			#endif /* DEFINE_H_ */
