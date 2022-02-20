/*
 * Defines.hpp
 *
 *  Created on: Jan 26, 2022
 *      Author: Nazanin
 */

#ifndef DEFINES_HPP_
#define DEFINES_HPP_

#include <main.h>

#define Motor1CCR 							TIM1->CCR2
#define Motor2CCR 							TIM1->CCR3


////placing ADC data into their variables
#define	Pot1										adcVal[0]
#define	Pot2										adcVal[1]
#define Current2R								adcVal[2]
#define Current2L								adcVal[3]
#define	Current1R								adcVal[4]
#define	Current1L								adcVal[5]
#define	Gas											adcVal[6]





//.......................................

#define TIMCallBack   					void HAL_TIM_PeriodElapsedCallback	(TIM_HandleTypeDef *htim		)
#define TxCallBack   						void HAL_UART_TxCpltCallback				(UART_HandleTypeDef *huart	)
#define RxCallBack    					void HAL_UART_RxCpltCallback				(UART_HandleTypeDef *huart	)


//LED
#define	LED_blue_Toggle	 				HAL_GPIO_TogglePin(LED1_GPIO_Port				,LED1_Pin					)
#define	LED_red_Toggle	 				HAL_GPIO_TogglePin(LED2_GPIO_Port				,LED2_Pin					)
#define	LED3pin_red_Toggle	 		HAL_GPIO_TogglePin(LED3pin1_GPIO_Port		,LED3pin1_Pin			)
#define	LED3pin_green_Toggle 		HAL_GPIO_TogglePin(LED3pin2_GPIO_Port		,LED3pin2_Pin			)

#define	LED_blue_on	 						HAL_GPIO_WritePin(LED1_GPIO_Port				,LED1_Pin				,GPIO_PIN_SET)
#define	LED_red_on	 						HAL_GPIO_WritePin(LED2_GPIO_Port				,LED2_Pin				,GPIO_PIN_SET)
#define	LED3pin_red_on	 				HAL_GPIO_WritePin(LED3pin1_GPIO_Port		,LED3pin1_Pin		,GPIO_PIN_SET)
#define	LED3pin_green_on 				HAL_GPIO_WritePin(LED3pin2_GPIO_Port		,LED3pin2_Pin		,GPIO_PIN_SET)

#define	LED_blue_off	 					HAL_GPIO_WritePin(LED1_GPIO_Port			,LED1_Pin					,GPIO_PIN_RESET)
#define	LED_red_off	 						HAL_GPIO_WritePin(LED2_GPIO_Port			,LED2_Pin					,GPIO_PIN_RESET)
#define	LED3pin_red_off	 				HAL_GPIO_WritePin(LED3pin1_GPIO_Port	,LED3pin1_Pin			,GPIO_PIN_RESET)
#define	LED3pin_green_off 			HAL_GPIO_WritePin(LED3pin2_GPIO_Port	,LED3pin2_Pin			,GPIO_PIN_RESET)


//Enable
#define En_Buhler_on 					HAL_GPIO_WritePin(INH_GPIO_Port,INH_Pin,GPIO_PIN_SET)
#define En_Buhler_off 					HAL_GPIO_WritePin(INH_GPIO_Port,INH_Pin,GPIO_PIN_RESET)

#define En_Teknic_on 					HAL_GPIO_WritePin(TekEN_GPIO_Port,TekEN_Pin,GPIO_PIN_RESET)
#define En_Teknic_off 					HAL_GPIO_WritePin(TekEN_GPIO_Port,TekEN_Pin,GPIO_PIN_SET)


//ADM
#define ADM_Transmit						HAL_GPIO_WritePin(EN_ADM_GPIO_Port,EN_ADM_Pin,1)
#define ADM_Receive							HAL_GPIO_WritePin(EN_ADM_GPIO_Port,EN_ADM_Pin,0)


//USART
#define	UsartNUC								UART4
#define	UsartXBEE 							USART1
#define	UsartPower							USART2
#define	UsartLog								UART5
#define	UsartDyna								USART6


//size
#define	NUC_Transmit_len				6
#define	NUC_Receive_len					6
#define	NUC_Feedback_len				13
#define	Power_Transmit_len			5
#define	Power_Receive_len				7
#define	XBEE_Transmit_len				5
#define	XBEE_Receive_len					5
#define	Log_Transmit_len				5
#define	Log_Receive_len					5


//direction
#define stop 										1
#define forward 								2
#define reverse 								3

//boolian States
#define valid										1
#define unvalid 								0

#define yes											1
#define no											0



//ArmFunctioningModes
#define	pwmMode 								11
#define angMode									22
#define angvelMode 							33

//priority
#define	Xbee										0
#define	MiniPC									1






//Packets...

//1.NUC	->	|	'M'	|	'C'	|	Power Byte	|	Right Motor PWM	|	Left Motor PWM |	Front Flipper PWM	|	Back Flipper PWM	|	/r	|




#endif /* DEFINES_HPP_ */
