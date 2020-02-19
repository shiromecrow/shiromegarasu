/*
 * SENSOR_control.c
 *
 *  Created on: 2019/06/20
 *      Author: sf199
 */
#include "SENSOR_control.h"
#include "adc.h"
#include "dma.h"
#include "yellow_LED.h"
#include "D_speaker.h"

void callback_SENSOR(void) {
	int j;
	HAL_ADC_Stop_DMA(&hadc1);

	//	if(ADstop>=5){
	//			ADstop=0;
	//		}
	switch (ADstop) {
	case 0:
		HAL_GPIO_WritePin(SENSOR_LED1_GPIO_Port, SENSOR_LED1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SENSOR_LED2_GPIO_Port, SENSOR_LED2_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED3_GPIO_Port, SENSOR_LED3_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED4_GPIO_Port, SENSOR_LED4_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED5_GPIO_Port, SENSOR_LED5_Pin,
				GPIO_PIN_RESET);
		for (j = 0; j <= 3000; j++) {
		}

		//		for (j = 0; j <= 80; j++) {
		//				}
		break;
	case 1:
		SEN_on[0] = g_ADCBuffer[1];

		HAL_GPIO_WritePin(SENSOR_LED1_GPIO_Port, SENSOR_LED1_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED2_GPIO_Port, SENSOR_LED2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SENSOR_LED3_GPIO_Port, SENSOR_LED3_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED4_GPIO_Port, SENSOR_LED4_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED5_GPIO_Port, SENSOR_LED5_Pin,
				GPIO_PIN_RESET);
		for (j = 0; j <= 500; j++) {
		}
		break;
	case 2:
		SEN_on[1] = g_ADCBuffer[2];
		HAL_GPIO_WritePin(SENSOR_LED1_GPIO_Port, SENSOR_LED1_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED2_GPIO_Port, SENSOR_LED2_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED3_GPIO_Port, SENSOR_LED3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SENSOR_LED4_GPIO_Port, SENSOR_LED4_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED5_GPIO_Port, SENSOR_LED5_Pin,
				GPIO_PIN_RESET);
		for (j = 0; j <= 1000; j++) {
		}
		break;
	case 3:
		SEN_on[2] = g_ADCBuffer[3];
		HAL_GPIO_WritePin(SENSOR_LED1_GPIO_Port, SENSOR_LED1_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED2_GPIO_Port, SENSOR_LED2_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED3_GPIO_Port, SENSOR_LED3_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED4_GPIO_Port, SENSOR_LED4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SENSOR_LED5_GPIO_Port, SENSOR_LED5_Pin,
				GPIO_PIN_RESET);
		for (j = 0; j <= 120; j++) {
		}
		break;
	case 4:
		SEN_on[3] = g_ADCBuffer[4];
		HAL_GPIO_WritePin(SENSOR_LED1_GPIO_Port, SENSOR_LED1_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED2_GPIO_Port, SENSOR_LED2_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED3_GPIO_Port, SENSOR_LED3_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED4_GPIO_Port, SENSOR_LED4_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED5_GPIO_Port, SENSOR_LED5_Pin, GPIO_PIN_SET);
		for (j = 0; j <= 500; j++) {
		}
		break;
	case 5:
		SEN_on[4] = g_ADCBuffer[5];
		HAL_GPIO_WritePin(SENSOR_LED1_GPIO_Port, SENSOR_LED1_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED2_GPIO_Port, SENSOR_LED2_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED3_GPIO_Port, SENSOR_LED3_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED4_GPIO_Port, SENSOR_LED4_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED5_GPIO_Port, SENSOR_LED5_Pin,
				GPIO_PIN_RESET);
		for (j = 0; j <= 500; j++) {
		}
		break;
	case 6:
		SEN_off[0] = g_ADCBuffer[1];
		SEN_off[1] = g_ADCBuffer[2];
		SEN_off[2] = g_ADCBuffer[3];
		SEN_off[3] = g_ADCBuffer[4];
		SEN_off[4] = g_ADCBuffer[5];

		for (j = 0; j <= 10; j++) {
		}
		break;

	}

	V_battAD = g_ADCBuffer[0];
	V_batt = 3.3 * (float) V_battAD / 4095.0 * (100.0 + 50.0) / 50.0;
	ADstop++;
	//for(j=0;j<=2000;j++){}
	if (ADstop != 7) {
		HAL_ADC_Start_DMA(&hadc1, g_ADCBuffer,
				sizeof(g_ADCBuffer) / sizeof(uint16_t));
	} else {
		ADstop = 0;
		for (j = 19; j >= 1; j--) {
			SEN[0][j] = SEN[0][j - 1];
			SEN[1][j] = SEN[1][j - 1];
			SEN[2][j] = SEN[2][j - 1];
			SEN[3][j] = SEN[3][j - 1];
			SEN[4][j] = SEN[4][j - 1];
		}
		SEN[0][0] = SEN_on[0] - SEN_off[0];
		SEN[1][0] = SEN_on[1] - SEN_off[1];
		SEN[2][0] = SEN_on[2] - SEN_off[2];
		SEN[3][0] = SEN_on[3] - SEN_off[3];
		SEN[4][0] = SEN_on[4] - SEN_off[4];
		for (j = 0; j <= 4; j++) {
//			SEND[j] =
//					(SEN[j][0] + SEN[j][1] + SEN[j][2] + SEN[j][3] + SEN[j][4])
//							- (SEN[j][19] + SEN[j][18] + SEN[j][17] + SEN[j][16]
//									+ SEN[j][15]);
			//“ªˆ«‚¢SEND[j]=SEN[j][0]-SEN[j][11?]‚Å‚Ä‚·‚Æ‘½‚·‚¬‚é‚Æ•½sˆÚ“®‚Ì‰e‹¿‚à¬‚³‚·‚¬‚é‚ÆŒŸ’m‚Å‚«‚È‚¢
			SEND[j]=SEN[j][0]-SEN[j][11];
			SENAve[j] = (SEN[j][0] + SEN[j][1] + SEN[j][2]) / 3;
		}

		record_in_sen();

	}

	//for(j=0;j<=10000;j++){}

	/* NOTE : This function Should not be modified, when the callback is needed,
	 the HAL_ADC_ConvCpltCallback could be implemented in the user file
	 */
	//HAL_ADC_Start_DMA(&hadc1, g_ADCBuffer,sizeof(g_ADCBuffer)/sizeof(uint16_t));
	//HAL_ADC_Start_DMA(&hadc1, g_ADCBuffer,
	//	sizeof(g_ADCBuffer) / sizeof(uint16_t));
}


void sensor_line(void){
	float L_dis[19],R_dis[19];
	int L_SEN[19],R_SEN[19];
int ee;
	for(ee=0;ee<19;ee++){
	while (SEN_on[2] <= 900) {
					HAL_Delay(1);
				}
	HAL_Delay(100);
	while (SEN_on[2] >= 900) {
						HAL_Delay(1);
					}
	HAL_Delay(500);
	printf("SEN1=%d,SEN2=%d,SEN3=%d,SEN4=%d,SEN5=%d\n", SEN[0][0],
											SEN[1][0], SEN[2][0], SEN[3][0], SEN[4][0]);
	L_dis[ee]=ee*5+40;
	R_dis[18-ee]=130-ee*5;
	L_SEN[ee]=SEN[4][0];
	R_SEN[18-ee]=SEN[0][0];
	yellow_count(ee);
					MakeMusicScale(ee);
	}
	while (SEN_on[0] <= 300 || SEN_on[2] <= 900 || SEN_on[4] <= 300) {
						HAL_Delay(1);
					}


	printf("L_SEN,L_dis,R_SEN,R_dis\n");
	for(ee=0;ee<19;ee++){
	printf("%d,%f,%d,%f\n",L_SEN[ee],L_dis[ee], R_SEN[ee], R_dis[ee]);
	}
}
