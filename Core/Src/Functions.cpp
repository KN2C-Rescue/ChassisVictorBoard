/*
 * Functions.cpp
 *
 *  Created on: Jan 26, 2022
 *      Author: Nazanin
 */

#include <Functions.hpp>

void Send2Power(void)
{
	//	Power_Transmit[	0	]	=	'C'	;
	//	Power_Transmit[	1	]	=	'P'	;
	//	Power_Transmit[	2	]	=	'd'	;
	//	Power_Transmit[	3	]	=	NUC_Receive[0]	;
	//	Power_Transmit[Power_Transmit_len-1]	=	'\r'	;
	//
	//	HAL_UART_Transmit(&huart2, Power_Transmit, Power_Transmit_len, 10);
}
void Send2NUC(void)
{
	if(priority==MiniPC)
	{
		//		NUC_Feedback[	0	]	=	'C'	;
		//		NUC_Feedback[	1	]	=	'M'	;
		//		NUC_Feedback[	2	]	=	'F'	;
		//		NUC_Feedback[	3	]	=	Power_Receive[0]	;
		//		NUC_Feedback[	4	]	=	(int)(Gas/16)		;
		//		NUC_Feedback[	5	]	=	Tek1HLFB	;
		//		NUC_Feedback[	6	]	=	Tek2HLFB	;
		//		NUC_Feedback[	7	]	=	Power_Receive[1]	;
		//		NUC_Feedback[	8	]	=	Power_Receive[2]	;
		//		NUC_Feedback[	9	]	=	Power_Receive[3]	;
		//		NUC_Feedback[	10]	=	Power_Receive[4]	;
		//		NUC_Feedback[	11]	=	Power_Receive[5]	;
		//
		//		NUC_Feedback[NUC_Feedback_len-1]	=	'\r'	;
		//
		//		HAL_UART_Transmit(&huart4, NUC_Feedback, NUC_Feedback_len, 10);
	}
	else 	if(priority==Xbee)
	{
		//		NUC_Transmit[	0	]	=	'C'	;
		//		NUC_Transmit[	1	]	=	'M'	;
		//		NUC_Transmit[	2	]	=	'X'	;
		//		NUC_Transmit[	3	]	=		0	;
		//
		//		NUC_Transmit[NUC_Transmit_len-1]	=	'\r'	;
		//
		//		HAL_UART_Transmit(&huart4, NUC_Transmit, NUC_Transmit_len, 10);
	}
}
void AssignData(struct _PacketParam* packetParam)
{
	switch(packetParam->firstHeader)
	{
	case 'M':
	{
		emPowerOff	  = ( packetParam->receiveData[0] & 0x01 ) >> 0; //0b00000001
		shutdown	  = ( packetParam->receiveData[0] & 0x02 ) >> 1; //0b00000010
		chassisDisarm = ( packetParam->receiveData[0] & 0x04 ) >> 2; //0b00000100
		reset		  = ( packetParam->receiveData[0] & 0x08 ) >> 3; //0b00001000
		armPower	  = ( packetParam->receiveData[0] & 0x10 ) >> 4; //0b00010000



		if(emPowerOff)
		{
			//			EmergencyPowerOff();
		}
		if(	chassisDisarm || shutdown)
		{
			StopMotors();
		}
		else
		{
			//StartMotors();
		}

		TeknicRight.PWM	= packetParam->receiveData[1];
		TeknicLeft.PWM	= packetParam->receiveData[2];
		BuhlerFront.PWM	= packetParam->receiveData[3];
		BuhlerBack.PWM	= packetParam->receiveData[4];






	}
	break;

	case	'P':
	{

	}
	break;
	case	'X':
	{

	}
	break;
	case	'L':
	{

	}
	break;
	}

}
void sendData2Motors()
{

//	TIM1->CCR2	=	((BuhlerFront.PWM/127)*30 +	50	)	;			//80...20
//	TIM1->CCR3	=	((BuhlerBack.PWM	/127)*30 +	50	)	;			//83...18

	TIM2->CCR4	=	(TeknicRight.PWM * 1000/255	)	;
	TIM12->CCR1	=	(TeknicLeft.PWM 	* 1000/255	)	;
}

void EmergencyPowerOff()
{

}

void Depack(struct _PacketParam* packetParam)
{
	LED_red_Toggle;

	switch(packetParam->depackCounter)
	{
	case 0:
		if(packetParam->receiveHeader==packetParam->firstHeader)
		{
			packetParam->depackCounter++;
		}
		else
		{
			packetParam->depackCounter =0;
		}

		HAL_UART_Receive_IT(packetParam->huart, &packetParam->receiveHeader, 1);

		break;

	case 1:
		if(packetParam->receiveHeader==packetParam->secondHeader)
		{
			packetParam->depackCounter++;
			HAL_UART_Receive_IT(packetParam->huart, packetParam->receiveData	, packetParam->receiveLenght);

		}
		else if(packetParam->receiveHeader==packetParam->firstHeader )
		{
			packetParam->depackCounter=1;
			HAL_UART_Receive_IT(packetParam->huart, &packetParam->receiveHeader, 1);
		}
		else
		{
			packetParam->depackCounter=0;
			HAL_UART_Receive_IT(packetParam->huart,&packetParam->receiveHeader, 1);
		}


		break;

	case 2:
		LED_red_Toggle;

		if( packetParam->receiveData[ packetParam->receiveLenght - 1 ] == '\r' )
			AssignData(packetParam);

		packetParam->depackCounter=0;
		HAL_UART_Receive_IT(packetParam->huart, &packetParam->receiveHeader, 1);


		break;
	}


}
void 	HipHop(void)
{
	for(int i=0;i<6;i++)
	{
		LED_blue_Toggle	;
		LED_red_Toggle	;
		HAL_Delay(100)	;
	}
}

void 	StopMotors(void)
{
	En_Buhler_off;
	En_Teknic_off;
}
void 	StartMotors(void)
{
	En_Buhler_on;
	En_Teknic_on;
}
void 	convertADC2Degree(void)
{


}
