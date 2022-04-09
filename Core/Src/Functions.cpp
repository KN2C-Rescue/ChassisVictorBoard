/*
 * Functions.cpp
 *
 *  Created on: Jan 26, 2022
 *      Author: Nazanin
 */

#include <Functions.hpp>


void Send2NUC(void)
{

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
			EmergencyPowerOff();
		}
		if(	chassisDisarm || shutdown)
		{
			StopMotors();
		}
		else
		{
			StartMotors();
		}

		TeknicRight.PWM	= 1000 - packetParam->receiveData[1]*1000/128;
		TeknicLeft.PWM	= 1000 - packetParam->receiveData[2]*1000/128;
		TeknicRight.Direction = 0;
		TeknicLeft.Direction = 0;

		if(TeknicRight.PWM < 0)
		{
			TeknicRight.PWM = -TeknicRight.PWM;
			TeknicRight.Direction = 1;
		}

		if(TeknicLeft.PWM < 0)
		{
			TeknicLeft.PWM = -TeknicLeft.PWM;
			TeknicLeft.Direction = 1;
		}



		BuhlerFront.PWM	= packetParam->receiveData[3];
		BuhlerBack.PWM	= packetParam->receiveData[4];



		if(BuhlerFront.PWM	> 127)
			BuhlerFront.PWM = BuhlerFront.PWM-256;



		if(BuhlerBack.PWM	> 127)
			BuhlerBack.PWM = BuhlerBack.PWM-256;




	}
	break;

	case	'P':
	{

		PacketPower.receiveData[0]; //powerbyte
		batteryVoltage 	= PacketPower.receiveData[1];
		logicCurrent	= PacketPower.receiveData[2];
		teknicCurrent 	= PacketPower.receiveData[3];
		armCurrent 		= PacketPower.receiveData[4];
		chassisCurrrent = PacketPower.receiveData[5];



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
void CheckPacketValidation(void)
{
	if(PacketNUC.isPacketFullyReceived == true)
	{
		AssignData(&PacketNUC);

		MakeCPPacket();

		SendPacket(&PacketPower);

		sendData2Motors();

		LED_red_Toggle;

		PacketNUC.isPacketFullyReceived = false;

	}
	if(PacketPower.isPacketFullyReceived == true)
	{
		AssignData(&PacketPower);

		MakeCNPacket();

		SendPacket(&PacketNUC);

		LED_blue_Toggle;

		PacketPower.isPacketFullyReceived = false;

	}
	if(PacketLog.isPacketFullyReceived == true)
	{
		AssignData(&PacketLog);

		PacketLog.isPacketFullyReceived = false;
	}
	if(PacketXBEE.isPacketFullyReceived == true)
	{
		AssignData(&PacketXBEE);

		PacketXBEE.isPacketFullyReceived = false;

	}

}

void MakeCPPacket()
{
	PacketPower.transmitData[0] = PacketPower.secondHeader;
	PacketPower.transmitData[1] = PacketPower.firstHeader;

	PacketPower.transmitData[2] = 'd';
	PacketPower.transmitData[3] = PacketNUC.receiveData[0];
	PacketPower.transmitData[4] = '\r';

}
void MakeCNPacket()
{

	TeknicRight.Feedback = HAL_GPIO_ReadPin(Tek1HLFB1_GPIO_Port, Tek1HLFB1_Pin);
	TeknicLeft.Feedback	 = HAL_GPIO_ReadPin(Tek2HLFB1_GPIO_Port, Tek2HLFB1_Pin);


	PacketNUC.transmitData[0] = PacketNUC.secondHeader;
	PacketNUC.transmitData[1] = PacketNUC.firstHeader;
	PacketNUC.transmitData[2] = 0; //Packetstatus
	PacketNUC.transmitData[3] = 0; //powerbyte
	PacketNUC.transmitData[4] = TeknicRight.Feedback;
	PacketNUC.transmitData[5] = TeknicLeft.Feedback;
	PacketNUC.transmitData[6] = batteryVoltage;
	PacketNUC.transmitData[7] = logicCurrent;
	PacketNUC.transmitData[8] = teknicCurrent;
	PacketNUC.transmitData[9] = armCurrent;
	PacketNUC.transmitData[10]= chassisCurrrent;
	PacketNUC.transmitData[11]= '\r';

}



void SendPacket(struct _PacketParam* packetParam)
{
	HAL_UART_Transmit_IT(packetParam->huart, packetParam->transmitData, packetParam->transmitLenght);

}
void sendData2Motors()
{

	if(BuhlerFront.PWM == 127)
	{
		HAL_GPIO_WritePin(Flipper_Front_B_GPIO_Port, Flipper_Front_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Flipper_Front_A_GPIO_Port, Flipper_Front_A_Pin, GPIO_PIN_RESET);
	}
	else if(BuhlerFront.PWM == -127)
	{
		HAL_GPIO_WritePin(Flipper_Front_B_GPIO_Port, Flipper_Front_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Flipper_Front_A_GPIO_Port, Flipper_Front_A_Pin, GPIO_PIN_SET);
	}
	else if(BuhlerFront.PWM == 0)
	{
		HAL_GPIO_WritePin(Flipper_Front_B_GPIO_Port, Flipper_Front_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Flipper_Front_A_GPIO_Port, Flipper_Front_A_Pin, GPIO_PIN_RESET);
	}


	if(BuhlerBack.PWM == 127)
	{
		HAL_GPIO_WritePin(Flipper_Back_B_GPIO_Port, Flipper_Back_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Flipper_Back_A_GPIO_Port, Flipper_Back_A_Pin, GPIO_PIN_RESET);
	}
	else if(BuhlerBack.PWM == -127)
	{
		HAL_GPIO_WritePin(Flipper_Back_B_GPIO_Port, Flipper_Back_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Flipper_Back_A_GPIO_Port, Flipper_Back_A_Pin, GPIO_PIN_SET);
	}
	else if(BuhlerBack.PWM == 0)
	{
		HAL_GPIO_WritePin(Flipper_Back_B_GPIO_Port, Flipper_Back_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Flipper_Back_A_GPIO_Port, Flipper_Back_A_Pin, GPIO_PIN_RESET);
	}




	TIM2->CCR4	=	(TeknicRight.PWM )	;
	TIM12->CCR1	=	(TeknicLeft.PWM )	;

	if(TeknicRight.Direction == 1)
		HAL_GPIO_WritePin(TEK1PWM1_GPIO_Port, TEK1PWM1_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(TEK1PWM1_GPIO_Port, TEK1PWM1_Pin, GPIO_PIN_RESET);


	if(TeknicLeft.Direction == 1)
		HAL_GPIO_WritePin(TEK2PWM1_GPIO_Port, TEK2PWM1_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(TEK2PWM1_GPIO_Port, TEK2PWM1_Pin, GPIO_PIN_RESET);
}

void EmergencyPowerOff()
{

}

void CheckRecData(struct _PacketParam* packetParam)
{
	packetParam->receiveStatus = receiveStatusHeader;
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

		break;

	case 1:
		if(packetParam->receiveHeader==packetParam->secondHeader)
		{
			packetParam->depackCounter++;
			packetParam->receiveStatus = receiveStatusPayload;
		}
		else if(packetParam->receiveHeader==packetParam->firstHeader )
		{
			packetParam->depackCounter=1;
		}
		else
		{
			packetParam->depackCounter=0;
		}


		break;

	case 2:

		if( packetParam->receiveData[ packetParam->receiveLenght - 3 ] == '\r' )
		{
			packetParam->isPacketFullyReceived = true;
		}
		else
		{
			packetParam->isPacketFullyReceived = false;
		}
		packetParam->depackCounter=0;


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
