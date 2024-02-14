/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.c
  * @brief   This file provides code for the configuration
  *          of the ADC instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "adc.h"

/* USER CODE BEGIN 0 */
/* USER CODE END 0 */
ADC_HandleTypeDef hadc2;
/* ADC2 init function */
void MX_ADC2_Init(void)
{
    /* USER CODE BEGIN ADC2_Init 0 */
    /* USER CODE END ADC2_Init 0 */
    ADC_ChannelConfTypeDef sConfig = {0};
    /* USER CODE BEGIN ADC2_Init 1 */
    /* USER CODE END ADC2_Init 1 */
    /** Common config
    */
    hadc2.Instance = ADC2;
    hadc2.Init.ScanConvMode = ADC_SCAN_DISABLE;
    hadc2.Init.ContinuousConvMode = DISABLE;
    hadc2.Init.DiscontinuousConvMode = DISABLE;
    hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc2.Init.NbrOfConversion = 1;
    if (HAL_ADC_Init(&hadc2) != HAL_OK)
    {
        Error_Handler();
    }
    /** Configure Regular Channel
    */
    sConfig.Channel = ADC_CHANNEL_0;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
    if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN ADC2_Init 2 */
    /* USER CODE END ADC2_Init 2 */
}
void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(adcHandle->Instance==ADC2)
    {
    /* USER CODE BEGIN ADC2_MspInit 0 */
    /* USER CODE END ADC2_MspInit 0 */
        /* ADC2 clock enable */
        __HAL_RCC_ADC2_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**ADC2 GPIO Configuration
        PA0-WKUP         ------> ADC2_IN0
        PA1         ------> ADC2_IN1
        PA2         ------> ADC2_IN2
        PA3         ------> ADC2_IN3
        PA4         ------> ADC2_IN4
        PB0         ------> ADC2_IN8
        */
        GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                                                    |GPIO_PIN_4;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        GPIO_InitStruct.Pin = GPIO_PIN_0;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    /* USER CODE BEGIN ADC2_MspInit 1 */
    /* USER CODE END ADC2_MspInit 1 */
    }
}
void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{
    if(adcHandle->Instance==ADC2)
    {
    /* USER CODE BEGIN ADC2_MspDeInit 0 */
    /* USER CODE END ADC2_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_ADC2_CLK_DISABLE();
        /**ADC2 GPIO Configuration
        PA0-WKUP         ------> ADC2_IN0
        PA1         ------> ADC2_IN1
        PA2         ------> ADC2_IN2
        PA3         ------> ADC2_IN3
        PA4         ------> ADC2_IN4
        PB0         ------> ADC2_IN8
        */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                                                    |GPIO_PIN_4);
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0);
    /* USER CODE BEGIN ADC2_MspDeInit 1 */
    /* USER CODE END ADC2_MspDeInit 1 */
    }
}
/* USER CODE BEGIN 1 */
/* USER CODE END 1 */