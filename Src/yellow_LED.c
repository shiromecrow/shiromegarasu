/*
 * yellow_LED.c
 *
 *  Created on: 2019/04/22
 *      Author: sf199
 */
//#include "stm32f4xx_hal.h"
#include "gpio.h"
#include "main.h"

//#define LED3_Pin GPIO_PIN_13
//#define LED3_GPIO_Port GPIOC
//#define LED2_Pin GPIO_PIN_14
//#define LED2_GPIO_Port GPIOC
//#define LED1_Pin GPIO_PIN_15
//#define LED1_GPIO_Port GPIOC
//#define SENSOR1_Pin GPIO_PIN_0
//#define SENSOR1_GPIO_Port GPIOC
//#define SENSOR_LED1_Pin GPIO_PIN_1
//#define SENSOR_LED1_GPIO_Port GPIOC
//#define SENSOR2_Pin GPIO_PIN_2
//#define SENSOR2_GPIO_Port GPIOC
//#define SENSOR_LED2_Pin GPIO_PIN_3
//#define SENSOR_LED2_GPIO_Port GPIOC
//#define SENSOR3_Pin GPIO_PIN_0
//#define SENSOR3_GPIO_Port GPIOA
//#define SENSOR_LED3_Pin GPIO_PIN_1
//#define SENSOR_LED3_GPIO_Port GPIOA
//#define SENSOR4_Pin GPIO_PIN_2
//#define SENSOR4_GPIO_Port GPIOA
//#define SENSOR_LED4_Pin GPIO_PIN_3
//#define SENSOR_LED4_GPIO_Port GPIOA
//#define CS1_Pin GPIO_PIN_4
//#define CS1_GPIO_Port GPIOA
//#define SENSOR5_Pin GPIO_PIN_4
//#define SENSOR5_GPIO_Port GPIOC
//#define BATT_Pin GPIO_PIN_5
//#define BATT_GPIO_Port GPIOC
//#define SENSOR_LED5_Pin GPIO_PIN_0
//#define SENSOR_LED5_GPIO_Port GPIOB
//#define D_LED1_Pin GPIO_PIN_1
//#define D_LED1_GPIO_Port GPIOB
//#define D_LED2_Pin GPIO_PIN_2
//#define D_LED2_GPIO_Port GPIOB
//#define SWITCH_Pin GPIO_PIN_10
//#define SWITCH_GPIO_Port GPIOB
//#define SPEAKER_Pin GPIO_PIN_11
//#define SPEAKER_GPIO_Port GPIOB
//#define STBY_Pin GPIO_PIN_13
//#define STBY_GPIO_Port GPIOB
//#define L_MOTOR_IN2_Pin GPIO_PIN_14
//#define L_MOTOR_IN2_GPIO_Port GPIOB
//#define L_MOTOR_IN1_Pin GPIO_PIN_15
//#define L_MOTOR_IN1_GPIO_Port GPIOB
//#define L_ENC_B_Pin GPIO_PIN_6
//#define L_ENC_B_GPIO_Port GPIOC
//#define L_ENC_A_Pin GPIO_PIN_7
//#define L_ENC_A_GPIO_Port GPIOC
//#define L_MOTOR_PWM_Pin GPIO_PIN_8
//#define L_MOTOR_PWM_GPIO_Port GPIOC
//#define R_MOTOR_PWM_Pin GPIO_PIN_9
//#define R_MOTOR_PWM_GPIO_Port GPIOC
//#define R_ENC_B_Pin GPIO_PIN_8
//#define R_ENC_B_GPIO_Port GPIOA
//#define R_ENC_A_Pin GPIO_PIN_9
//#define R_ENC_A_GPIO_Port GPIOA
//#define R_MOTOR_IN2_Pin GPIO_PIN_10
//#define R_MOTOR_IN2_GPIO_Port GPIOA
//#define R_MOTOR_IN1_Pin GPIO_PIN_11
//#define R_MOTOR_IN1_GPIO_Port GPIOA
//#define LED8_Pin GPIO_PIN_4
//#define LED8_GPIO_Port GPIOB
//#define LED7_Pin GPIO_PIN_5
//#define LED7_GPIO_Port GPIOB
//#define LED6_Pin GPIO_PIN_6
//#define LED6_GPIO_Port GPIOB
//#define LED5_Pin GPIO_PIN_7
//#define LED5_GPIO_Port GPIOB
//#define SUCTION_FAN_Pin GPIO_PIN_8
//#define SUCTION_FAN_GPIO_Port GPIOB
//#define LED4_Pin GPIO_PIN_9
//#define LED4_GPIO_Port GPIOB


unsigned char yy1,yy2,yy3,yy4,yy5,yy6,yy7,yy8;



void yellow_off(void){
	HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED5_GPIO_Port,LED5_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED6_GPIO_Port,LED6_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED7_GPIO_Port,LED7_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED8_GPIO_Port,LED8_Pin,GPIO_PIN_RESET);
}
void yellow_on(void){
	HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED5_GPIO_Port,LED5_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED6_GPIO_Port,LED6_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED7_GPIO_Port,LED7_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED8_GPIO_Port,LED8_Pin,GPIO_PIN_SET);
}


void yellow_count(unsigned char yy){

yy1 = yy & 1;
yy2 = yy & 2;
yy3 = yy & 4;
yy4 = yy & 8;
yy5 = yy & 16;
yy6 = yy & 32;
yy7 = yy & 64;
yy8 = yy & 128;

if(yy1 >= 1){
	HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
}else{
	HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
}
if(yy2 >= 1){
	HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
}
else{
	HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);
}
if(yy3 >= 1){
	HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_SET);
}else{
	HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_RESET);
}
if(yy4 >= 1){
	HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,GPIO_PIN_SET);
}else{
	HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,GPIO_PIN_RESET);
}
if(yy5 >= 1){
	HAL_GPIO_WritePin(LED5_GPIO_Port,LED5_Pin,GPIO_PIN_SET);
}else{
	HAL_GPIO_WritePin(LED5_GPIO_Port,LED5_Pin,GPIO_PIN_RESET);
}
if(yy6 >= 1){
	HAL_GPIO_WritePin(LED6_GPIO_Port,LED6_Pin,GPIO_PIN_SET);
}else{
	HAL_GPIO_WritePin(LED6_GPIO_Port,LED6_Pin,GPIO_PIN_RESET);
}
if(yy7 >= 1){
	HAL_GPIO_WritePin(LED7_GPIO_Port,LED7_Pin,GPIO_PIN_SET);
}else{
	HAL_GPIO_WritePin(LED7_GPIO_Port,LED7_Pin,GPIO_PIN_RESET);
}
if(yy8 >= 1){
	HAL_GPIO_WritePin(LED8_GPIO_Port,LED8_Pin,GPIO_PIN_SET);
}else{
	HAL_GPIO_WritePin(LED8_GPIO_Port,LED8_Pin,GPIO_PIN_RESET);
}
}








