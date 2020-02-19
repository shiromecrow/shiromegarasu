/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    stm32f4xx_it.c
 * @brief   Interrupt Service Routines.
 ******************************************************************************
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
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "D_speaker.h"
#include "ICM_20602.h"
#include "adc.h"
#include "IEH2-4096.h"
#include "SENSOR_control.h"
#include "motor_control.h"
#include "tim.h"
#include"maze_strategy.h"

#include"maze_wall.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

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
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
volatile uint32_t g_timCount;

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc1;
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim8;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
 * @brief This function handles Non maskable interrupt.
 */
void NMI_Handler(void) {
	/* USER CODE BEGIN NonMaskableInt_IRQn 0 */

	/* USER CODE END NonMaskableInt_IRQn 0 */
	/* USER CODE BEGIN NonMaskableInt_IRQn 1 */

	/* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
 * @brief This function handles Hard fault interrupt.
 */
void HardFault_Handler(void)

{
	/* USER CODE BEGIN HardFault_IRQn 0 */

	/* USER CODE END HardFault_IRQn 0 */
	while (1) {
		/* USER CODE BEGIN W1_HardFault_IRQn 0 */
		/* USER CODE END W1_HardFault_IRQn 0 */
	}
}

/**
 * @brief This function handles Memory management fault.
 */
void MemManage_Handler(void) {
	/* USER CODE BEGIN MemoryManagement_IRQn 0 */

	/* USER CODE END MemoryManagement_IRQn 0 */
	while (1) {
		/* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
		/* USER CODE END W1_MemoryManagement_IRQn 0 */
	}
}

/**
 * @brief This function handles Pre-fetch fault, memory access fault.
 */
void BusFault_Handler(void) {
	/* USER CODE BEGIN BusFault_IRQn 0 */

	/* USER CODE END BusFault_IRQn 0 */
	while (1) {
		/* USER CODE BEGIN W1_BusFault_IRQn 0 */
		/* USER CODE END W1_BusFault_IRQn 0 */
	}
}

/**
 * @brief This function handles Undefined instruction or illegal state.
 */
void UsageFault_Handler(void) {
	/* USER CODE BEGIN UsageFault_IRQn 0 */

	/* USER CODE END UsageFault_IRQn 0 */
	while (1) {
		/* USER CODE BEGIN W1_UsageFault_IRQn 0 */
		/* USER CODE END W1_UsageFault_IRQn 0 */
	}
}

/**
 * @brief This function handles System service call via SWI instruction.
 */
void SVC_Handler(void) {
	/* USER CODE BEGIN SVCall_IRQn 0 */

	/* USER CODE END SVCall_IRQn 0 */
	/* USER CODE BEGIN SVCall_IRQn 1 */

	/* USER CODE END SVCall_IRQn 1 */
}

/**
 * @brief This function handles Debug monitor.
 */
void DebugMon_Handler(void) {
	/* USER CODE BEGIN DebugMonitor_IRQn 0 */

	/* USER CODE END DebugMonitor_IRQn 0 */
	/* USER CODE BEGIN DebugMonitor_IRQn 1 */

	/* USER CODE END DebugMonitor_IRQn 1 */
}

/**
 * @brief This function handles Pendable request for system service.
 */
void PendSV_Handler(void) {
	/* USER CODE BEGIN PendSV_IRQn 0 */

	/* USER CODE END PendSV_IRQn 0 */
	/* USER CODE BEGIN PendSV_IRQn 1 */

	/* USER CODE END PendSV_IRQn 1 */
}

/**
 * @brief This function handles System tick timer.
 */
void SysTick_Handler(void) {
	/* USER CODE BEGIN SysTick_IRQn 0 */

	/* USER CODE END SysTick_IRQn 0 */
	HAL_IncTick();
	/* USER CODE BEGIN SysTick_IRQn 1 */

	/* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
 * @brief This function handles ADC1, ADC2 and ADC3 global interrupts.
 */
void ADC_IRQHandler(void) {
	/* USER CODE BEGIN ADC_IRQn 0 */

	/* USER CODE END ADC_IRQn 0 */
	HAL_ADC_IRQHandler(&hadc1);
	/* USER CODE BEGIN ADC_IRQn 1 */

	/* USER CODE END ADC_IRQn 1 */
}

/**
 * @brief This function handles TIM8 capture compare interrupt.
 */
void TIM8_CC_IRQHandler(void) {
	/* USER CODE BEGIN TIM8_CC_IRQn 0 */

	/* USER CODE END TIM8_CC_IRQn 0 */
	HAL_TIM_IRQHandler(&htim8);
	/* USER CODE BEGIN TIM8_CC_IRQn 1 */

//  	HAL_TIM_PWM_Start_IT(&htim8, TIM_CHANNEL_4);
//  	HAL_TIM_PWM_Start_IT(&htim8, TIM_CHANNEL_3);
	/* USER CODE END TIM8_CC_IRQn 1 */
}

/**
 * @brief This function handles TIM6 global interrupt, DAC1 and DAC2 underrun error interrupts.
 */
void TIM6_DAC_IRQHandler(void) {
	/* USER CODE BEGIN TIM6_DAC_IRQn 0 */

	/* USER CODE END TIM6_DAC_IRQn 0 */
	HAL_TIM_IRQHandler(&htim6);
	/* USER CODE BEGIN TIM6_DAC_IRQn 1 */
	g_timCount++;

	interrupt_ICM();
	encoder_speed();
	encoder_distance();
	encoder_acceleration();
	if (modeacc == 0) {
	}
	if (modeacc == 1) {
		m_timCount++;
		interupt_const_accel();
	}
	if (modeacc == 2 || modeacc == 3) {
		m_timCount++;
		interupt_angle_const_accel();
	}
	if (modeacc == 4) {
		m_timCount++;
		interupt_slalom_const_accel();
	}

	if (maze_mode == 1 || (modeacc != 0 && modeacc != 3)) {

		if (modeacc == 1) {
			if (No_wall_modeR == 0) {
				if (SEN[0][0] <= SENnoR) { //SEND[0] <= -SENkireR ||
					speakermode = -1;
					No_wall_modeR = 1;
				}
			}
			if (No_wall_modeL == 0) {
				if (SEN[4][0] <= SENnoL) { //SEND[4] <= -SENkireL ||
					speakermode = -2;
					No_wall_modeL = 1;
				}
			}
			if (No_wall_modeR2 == 0) {
				if (SEN[1][0] <= SENnoR2) { //SEND[1] <= -SENkireR2 ||
					speakermode = -3;
					No_wall_modeR2 = 1;
				}
			}
			if (No_wall_modeL2 == 0) {
				if (SEN[3][0] <= SENnoL2) { //SEND[3] <= -SENkireL2 ||
					speakermode = -4;
					No_wall_modeL2 = 1;
				}
			}
			if (SEN[0][0] > SENnoR) { //SEND[0] >= SENkireR ||
				No_wall_modeR = 0;
			}
			if (SEN[4][0] > SENnoL) { //SEND[4] >= SENkireL ||
				No_wall_modeL = 0;
			}
			if (SEN[1][0] > SENnoR2) { //SEND[1] >= SENkireR2 ||
				No_wall_modeR2 = 0;
			}
			if (SEN[3][0] > SENnoL2) { //SEND[3] >= SENkireL2 ||
				No_wall_modeL2 = 0;
			}
			if (No_wall_modeR == 1) {
				no_wall_timeR++;
			} else {
				no_wall_timeR = 0;
			}
			if (No_wall_modeL == 1) {
				no_wall_timeL++;
			} else {
				no_wall_timeL = 0;
			}
			if (No_wall_modeR2 == 1) {
				no_wall_timeR2++;
			} else {
				no_wall_timeR2 = 0;
			}
			if (No_wall_modeL2 == 1) {
				no_wall_timeL2++;
			} else {
				no_wall_timeL2 = 0;
			}
		} else {
			no_wall_timeR = 0;
			no_wall_timeL = 0;
			no_wall_timeR2 = 0;
			no_wall_timeL2 = 0;
			no_wall_timeRslant = 0;
			no_wall_timeLslant = 0;
		}
		if (wall_control_mode >= 5) {

			if (No_wall_modeRslant == 0) {
				if (SEN[1][0] <= SENnoRslant) { //SEND[1] <= -SENkireR2 ||
					speakermode = -20;
					No_wall_modeRslant = 1;
				}
			}
			if (No_wall_modeLslant == 0) {
				if (SEN[3][0] <= SENnoLslant) { //SEND[3] <= -SENkireL2 ||
					speakermode = -21;
					No_wall_modeLslant = 1;
				}
			}

			if (SEN[1][0] > SENnoRslant) { //SEND[1] >= SENkireR2 ||
				No_wall_modeRslant = 0;
			}
			if (SEN[3][0] > SENnoLslant) { //SEND[3] >= SENkireL2 ||
				No_wall_modeLslant = 0;
			}

			if (No_wall_modeRslant == 1) {
				no_wall_timeRslant++;
			} else {
				no_wall_timeRslant = 0;
			}
			if (No_wall_modeLslant == 1) {
				no_wall_timeLslant++;
			} else {
				no_wall_timeLslant = 0;
			}

		} else {
			no_wall_timeRslant = 0;
			no_wall_timeLslant = 0;
		}

//	  if(anglex >= 90){
//
//	  }

		if (no_safty == 0 && error_mode == 0) {
			if ((-Turn_ideal_speed + angle_speed) >= Avespeed
					|| (Turn_ideal_speed - angle_speed) >= Avespeed ) {
				//(gyro.omega_x >= 320 && gyro.omega_y >= 320) ||
				HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_3);
				HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_4);
				HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
				STBYOFF;
				x = 0;
				y = 0;
				//speakermode=100;
				playSoundData(15, miss);
				no_wall_timeR = 10000;
				no_wall_timeL = 10000;
				no_wall_timeR2 = 10000;
				no_wall_timeL2 = 10000;
				gg = 0;
				while (gg <= 255) {
					pass[gg] = 0;

					gg++;
				}
				gg = 0;
				error_mode = 1;
			}
			if (highspeed_mode == 0 && gyro.omega_x >= 320) {
				HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_3);
				HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_4);
				HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
				STBYOFF;
				x = 0;
				y = 0;
				//speakermode=100;
				playSoundData(15, miss);
				error_mode = 1;
			}
			if((ideal_speed - (E_speedR+E_speedL)/2) <= -Avespeed*1.1 && modeacc==1){
				HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_3);
								HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_4);
								HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
								STBYOFF;
								x = 0;
								y = 0;
								//speakermode=100;
								playSoundData(15, miss);
								no_wall_timeR = 10000;
								no_wall_timeL = 10000;
								no_wall_timeR2 = 10000;
								no_wall_timeL2 = 10000;
								gg = 0;
								while (gg <= 255) {
									pass[gg] = 0;

									gg++;
								}
								gg = 0;
								error_mode = 1;
			}

		}

	}
	if (speakermode <= -1) {
		interupt_oneSound(-speakermode * 4, 40);
	}
	if (speakermode == 1) {
		interupt_Sound(843, unknow_story);
	}
	if (speakermode == 100) {
		interupt_Sound(14, miss);
	}
	if (speakermode >= 101) {
		speakermode = 0;
	}
//  if(speakermode == 2){
//   interupt_Sound(170, seria);
//   }
	if (sensor_mode == 1) {
		HAL_ADC_Start_DMA(&hadc1, g_ADCBuffer,
				sizeof(g_ADCBuffer) / sizeof(uint16_t));
	}
	//  if(speakermode == 3){
//   interupt_Sound(8, Zelda_nazo);
//   }
	/* USER CODE END TIM6_DAC_IRQn 1 */
}

/**
 * @brief This function handles DMA2 stream0 global interrupt.
 */
void DMA2_Stream0_IRQHandler(void) {
	/* USER CODE BEGIN DMA2_Stream0_IRQn 0 */

	/* USER CODE END DMA2_Stream0_IRQn 0 */
	HAL_DMA_IRQHandler(&hdma_adc1);
	/* USER CODE BEGIN DMA2_Stream0_IRQn 1 */

	/* USER CODE END DMA2_Stream0_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
