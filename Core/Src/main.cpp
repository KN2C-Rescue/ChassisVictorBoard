/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
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
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "Functions.hpp"
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
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM3)
	{
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
		{
			IC_Val11 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
			if (IC_Val11 != 0)
			{
				IC_Val12 	= HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
				Tek1HLFB = roundf(((float)IC_Val11*100.0/(float)IC_Val12));
			}
			else
			{
				Tek1HLFB = 0;
			}
		}
	}
	else if(htim->Instance==TIM4)
	{
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
		{
			IC_Val21 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
			if (IC_Val21 != 0)
			{
				IC_Val22 	= HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
				Tek2HLFB = roundf(((float)IC_Val21*100.0/(float)IC_Val22));
			}
			else
			{
				Tek2HLFB = 0;
			}
		}
	}
}
void HAL_UART_RxCpltCallback	(UART_HandleTypeDef *huart	)
{

	if(huart->Instance	==	UsartNUC)
	{
		Depack(&PacketNUC);
		LED_blue_Toggle;
	}
	else 	if(huart->Instance	==	UsartPower)
	{
		Depack(&PacketPower);
	}
	else 	if(huart->Instance	==	UsartXBEE)
	{
		Depack(&PacketXBEE);
	}
	else 	if(huart->Instance	==	UsartLog)
	{
		Depack(&PacketLog);
	}

}
void HAL_TIM_PeriodElapsedCallback	(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM10)		//this timer gives an interrupt every 1ms
	{
		LastTimeDataReceived++;//this variable must be inside the Controling loop and be plused every 10ms
		if(LastTimeDataReceived>=100)
		{
			//stopRobot();
			//Priority=MiniPC;
		}
		//stops the motors if no data were recived for a long while
	}
	if(htim->Instance == TIM11)
	{
		sendData2Motors();
	}
}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
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
	MX_ADC1_Init();
	MX_TIM1_Init();
	MX_TIM2_Init();
	MX_TIM3_Init();
	MX_TIM4_Init();
	MX_UART4_Init();
	MX_USART1_UART_Init();
	MX_USART2_UART_Init();
	MX_USART6_UART_Init();
	MX_TIM12_Init();
	MX_UART5_Init();
	MX_DMA_Init();
	MX_TIM10_Init();
	MX_TIM11_Init();
	/* USER CODE BEGIN 2 */

	HipHop();

	HAL_ADC_Start_DMA		(&hadc1,(uint32_t *)adcVal,7);

	HAL_TIM_Base_Start		(&htim1);	//Buhler 			Timer Start
	HAL_TIM_PWM_Start		(&htim1, TIM_CHANNEL_2);	//Buhler	1 	PWM 	Start
	HAL_TIMEx_PWMN_Start	(&htim1, TIM_CHANNEL_2);	//Buhler	1 	PWMN 	Start
	HAL_TIM_PWM_Start		(&htim1, TIM_CHANNEL_3);	//Buhler	2 	PWM	 	Start
	HAL_TIMEx_PWMN_Start	(&htim1, TIM_CHANNEL_3);	//Buhler	2 	PWMN 	Start

	HAL_TIM_Base_Start		(&htim12);	//Teknic	1 	Timer Start
	HAL_TIM_PWM_Start		(&htim12, TIM_CHANNEL_1);	//Teknic	1 	Velocity	PWM  	Start
	HAL_TIM_PWM_Start		(&htim12, TIM_CHANNEL_2);	//Teknic	1 	Torque		PWM 	Start

	HAL_TIM_Base_Start		(&htim2);	//Teknic	2 	Timer Start
	HAL_TIM_PWM_Start		(&htim2, TIM_CHANNEL_3);	//Teknic	2 	Torque		PWM 	Start
	HAL_TIM_PWM_Start		(&htim2, TIM_CHANNEL_4);	//Teknic	2 	Velocity	PWM  	Start

	HAL_TIM_Base_Start_IT	(&htim3);	//Teknic1 HLFB
	HAL_TIM_IC_Start_IT		(&htim3, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT		(&htim3, TIM_CHANNEL_2);

	HAL_TIM_Base_Start_IT	(&htim4);	//Teknic2 HLFB
	HAL_TIM_IC_Start_IT		(&htim4, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT		(&htim4, TIM_CHANNEL_2);

	HAL_TIM_Base_Start_IT	(&htim10);	//10ms Interrupt
	HAL_TIM_Base_Start_IT	(&htim11);  //20ms Interrupt


	//	HAL_UART_Receive_IT		(&huart1, &recXBE , 1)						;	//XBEE
	//	HAL_UART_Receive_IT		(&huart2, &recPWR , 1)						;	//Power	Board
	HAL_UART_Receive_IT		(&huart4, &recNUC , 1);	//USRk1
	//	HAL_UART_Receive_IT		(&huart5, &recLOG , 1)						;	//Log
	//	HAL_UART_Receive_IT		(&huart6, &recDXL , 1)						;	//Dynamixel



	StopMotors();
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		/* USER CODE END WHILE */


		/* USER CODE BEGIN 3 */



	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 168;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
	{
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

