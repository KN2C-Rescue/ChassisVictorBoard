/*
 * Variables.hpp
 *
 *  Created on: Jan 26, 2022
 *      Author: Nazanin
 */

#ifndef INC_VARIABLES_HPP_
#define INC_VARIABLES_HPP_



#include <Defines.hpp>
 #include <cstdlib>


extern int test1;
extern int test2;
extern int test3;


extern	int		LastTimeDataReceived;
extern	int		powerEn;
extern	int		fanEn;
extern	int		LEDEn;
extern	int 	priority;




extern	uint8_t 	batteryVoltage;
extern	uint8_t 	chassisCurrrent;
extern	uint8_t 	logicCurrent;
extern	uint8_t  	teknicCurrent;
extern	uint8_t 	armCurrent;

extern	uint8_t 	recNUC;
extern	uint8_t 	recXBEE;
extern	uint8_t 	recDyna;
extern	uint8_t 	recLog;
extern	uint8_t 	recPower;


extern	uint8_t 	reset;
extern	uint8_t 	chassisDisarm;
extern	uint8_t 	shutdown;
extern	uint8_t 	emPowerOff;
extern	uint8_t 	armPower;

//extern	uint32_t 	adcVal[7];

extern	uint32_t 	IC_Val11;
extern	uint32_t 	IC_Val12;
extern	uint32_t 	Tek1HLFB;
extern	uint32_t 	IC_Val21;
extern	uint32_t 	IC_Val22;
extern	uint32_t 	Tek2HLFB;

struct _PacketParam
{
	char 		firstHeader;
	char 		secondHeader;
	int 		depackCounter ;
	int 		receiveLenght;
	int 		transmitLenght;
	uint8_t* 	receiveData;
	uint8_t* 	transmitData;
	uint8_t 	receiveHeader;
	int 		isPacketFullyReceived;
	int 		payloadReceived;
	int 		receiveStatus;

	UART_HandleTypeDef *huart;



	_PacketParam(UART_HandleTypeDef *_huart,char _firstHeader,char _secondHeader,int _receiveLenght, int _transmitLenght)
	{
		firstHeader = _firstHeader;
		secondHeader = _secondHeader;

		receiveLenght = _receiveLenght;
		transmitLenght = _transmitLenght;
		receiveData = (uint8_t*) malloc((receiveLenght-2) * sizeof(uint8_t));
		transmitData = (uint8_t*) malloc(transmitLenght * sizeof(uint8_t));
		huart = _huart;
		payloadReceived = false;


		//delete
		receiveStatus = receiveStatusHeader;
	}
};
struct _ControlParam
{
	float kp,ki,kd;
	float P,I,D ;
	float setPoint,point,error;
};

struct _Buhler
{
	int PWM;
	int Direction;
	int Orientation;
	int Enable;

	float Velocity;
	float Torque;


	struct _ControlParam curController,angVelController,angController;
};

struct _Teknic
{
	int PWM;
	int Direction;
	int Orientation;
	int Enable;

	uint8_t Feedback;

	float AngVel;
	float Angle;
	float CurrentBTN1;
	float CurrentBTN2;



	struct _ControlParam curController,angVelController,angController;
};


extern	struct _Buhler BuhlerFront,BuhlerBack;
extern	struct _Teknic TeknicRight,TeknicLeft;


extern struct _PacketParam PacketNUC;
extern struct _PacketParam PacketPower;
extern struct _PacketParam PacketXBEE;
extern struct _PacketParam PacketLog;


#endif /* INC_VARIABLES_HPP_ */
