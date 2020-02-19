/**
  ******************************************************************************
  * File Name          : ADC.c
  * Description        : This file provides code for the configuration
  *                      of the ADC instances.
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

/* Includes ------------------------------------------------------------------*/
#include "adc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

/* ADC1 init function */
void MX_ADC1_Init(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};

  /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 6;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
  */
  sConfig.Channel = ADC_CHANNEL_15;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
  */
  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = 2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
  */
  sConfig.Channel = ADC_CHANNEL_12;
  sConfig.Rank = 3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 4;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = 5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
  */
  sConfig.Channel = ADC_CHANNEL_14;
  sConfig.Rank = 6;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();
  
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**ADC1 GPIO Configuration    
    PC0     ------> ADC1_IN10
    PC2     ------> ADC1_IN12
    PA0-WKUP     ------> ADC1_IN0
    PA2     ------> ADC1_IN2
    PC4     ------> ADC1_IN14
    PC5     ------> ADC1_IN15 
    */
    GPIO_InitStruct.Pin = SENSOR1_Pin|SENSOR2_Pin|SENSOR5_Pin|BATT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = SENSOR3_Pin|SENSOR4_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* ADC1 DMA Init */
    /* ADC1 Init */
    hdma_adc1.Instance = DMA2_Stream0;
    hdma_adc1.Init.Channel = DMA_CHANNEL_0;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;
    hdma_adc1.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(adcHandle,DMA_Handle,hdma_adc1);

    /* ADC1 interrupt Init */
    HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC_IRQn);
  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();
  
    /**ADC1 GPIO Configuration    
    PC0     ------> ADC1_IN10
    PC2     ------> ADC1_IN12
    PA0-WKUP     ------> ADC1_IN0
    PA2     ------> ADC1_IN2
    PC4     ------> ADC1_IN14
    PC5     ------> ADC1_IN15 
    */
    HAL_GPIO_DeInit(GPIOC, SENSOR1_Pin|SENSOR2_Pin|SENSOR5_Pin|BATT_Pin);

    HAL_GPIO_DeInit(GPIOA, SENSOR3_Pin|SENSOR4_Pin);

    /* ADC1 DMA DeInit */
    HAL_DMA_DeInit(adcHandle->DMA_Handle);

    /* ADC1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(ADC_IRQn);
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
	callback_SENSOR();

}

//	int j;
//	HAL_ADC_Stop_DMA(&hadc1);
//
////	if(ADstop>=5){
////			ADstop=0;
////		}
//	switch (ADstop) {
//	case 0:
//		SEN_off[0] = g_ADCBuffer[1];
//		SEN_off[1] = g_ADCBuffer[2];
//		SEN_off[2] = g_ADCBuffer[3];
//		SEN_off[3] = g_ADCBuffer[4];
//		SEN_off[4] = g_ADCBuffer[5];
//		HAL_GPIO_WritePin(SENSOR_LED1_GPIO_Port, SENSOR_LED1_Pin, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(SENSOR_LED2_GPIO_Port, SENSOR_LED2_Pin, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(SENSOR_LED3_GPIO_Port, SENSOR_LED3_Pin, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(SENSOR_LED4_GPIO_Port, SENSOR_LED4_Pin, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(SENSOR_LED5_GPIO_Port, SENSOR_LED5_Pin, GPIO_PIN_SET);
//		for (j = 0; j <= 160; j++) {
//		}
//
////		for (j = 0; j <= 80; j++) {
////				}
//		break;
//	case 1:
//		SEN_on[0] = g_ADCBuffer[1];
//		SEN_on[1] = g_ADCBuffer[2];
//		SEN_on[2] = g_ADCBuffer[3];
//		SEN_on[3] = g_ADCBuffer[4];
//		SEN_on[4] = g_ADCBuffer[5];
//		HAL_GPIO_WritePin(SENSOR_LED1_GPIO_Port, SENSOR_LED1_Pin,
//				GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(SENSOR_LED2_GPIO_Port, SENSOR_LED2_Pin, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(SENSOR_LED3_GPIO_Port, SENSOR_LED3_Pin,
//				GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(SENSOR_LED4_GPIO_Port, SENSOR_LED4_Pin,
//				GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(SENSOR_LED5_GPIO_Port, SENSOR_LED5_Pin,
//				GPIO_PIN_RESET);
//		for (j = 0; j <= 500; j++) {
//		}
//		break;
//		case 2:
//			SEN[1]=g_ADCBuffer[2];
//					HAL_GPIO_WritePin(SENSOR_LED1_GPIO_Port, SENSOR_LED1_Pin, GPIO_PIN_RESET);
//						HAL_GPIO_WritePin(SENSOR_LED2_GPIO_Port, SENSOR_LED2_Pin, GPIO_PIN_RESET);
//						HAL_GPIO_WritePin(SENSOR_LED3_GPIO_Port, SENSOR_LED3_Pin, GPIO_PIN_SET);
//						HAL_GPIO_WritePin(SENSOR_LED4_GPIO_Port, SENSOR_LED4_Pin, GPIO_PIN_RESET);
//						HAL_GPIO_WritePin(SENSOR_LED5_GPIO_Port, SENSOR_LED5_Pin, GPIO_PIN_RESET);
//						for(j=0;j<=500;j++){}
//				break;
//		case 3:
//			SEN[2]=g_ADCBuffer[3];
//					HAL_GPIO_WritePin(SENSOR_LED1_GPIO_Port, SENSOR_LED1_Pin, GPIO_PIN_RESET);
//						HAL_GPIO_WritePin(SENSOR_LED2_GPIO_Port, SENSOR_LED2_Pin, GPIO_PIN_RESET);
//						HAL_GPIO_WritePin(SENSOR_LED3_GPIO_Port, SENSOR_LED3_Pin, GPIO_PIN_RESET);
//						HAL_GPIO_WritePin(SENSOR_LED4_GPIO_Port, SENSOR_LED4_Pin, GPIO_PIN_SET);
//						HAL_GPIO_WritePin(SENSOR_LED5_GPIO_Port, SENSOR_LED5_Pin, GPIO_PIN_RESET);
//						for(j=0;j<=500;j++){}
//				break;
//		case 4:
//			SEN[3]=g_ADCBuffer[4];
//					HAL_GPIO_WritePin(SENSOR_LED1_GPIO_Port, SENSOR_LED1_Pin, GPIO_PIN_RESET);
//						HAL_GPIO_WritePin(SENSOR_LED2_GPIO_Port, SENSOR_LED2_Pin, GPIO_PIN_RESET);
//						HAL_GPIO_WritePin(SENSOR_LED3_GPIO_Port, SENSOR_LED3_Pin, GPIO_PIN_RESET);
//						HAL_GPIO_WritePin(SENSOR_LED4_GPIO_Port, SENSOR_LED4_Pin, GPIO_PIN_RESET);
//						HAL_GPIO_WritePin(SENSOR_LED5_GPIO_Port, SENSOR_LED5_Pin, GPIO_PIN_SET);
//						for(j=0;j<=500;j++){}
//				break;
//
//	}
//
//	ADstop++;
//	//for(j=0;j<=2000;j++){}
//	if (ADstop == 1) {
//		HAL_ADC_Start_DMA(&hadc1, g_ADCBuffer,
//				sizeof(g_ADCBuffer) / sizeof(uint16_t));
//	} else {
//		ADstop = 0;
//	}

//for(j=0;j<=10000;j++){}

	/* NOTE : This function Should not be modified, when the callback is needed,
	 the HAL_ADC_ConvCpltCallback could be implemented in the user file
	 */
	//HAL_ADC_Start_DMA(&hadc1, g_ADCBuffer,sizeof(g_ADCBuffer)/sizeof(uint16_t));
	//HAL_ADC_Start_DMA(&hadc1, g_ADCBuffer,
	//	sizeof(g_ADCBuffer) / sizeof(uint16_t));

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
