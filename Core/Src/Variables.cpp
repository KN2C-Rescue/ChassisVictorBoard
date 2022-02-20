/*
 * Variables.cpp
 *
 *  Created on: Jan 26, 2022
 *      Author: Nazanin
 */
#include "usart.h"
#include <Variables.hpp>

int test1 = 0;
int test2 = 0;
int test3 = 0;


int		LastTimeDataReceived=0;
int		powerEn;
int		fanEn;
int		LEDEn;
int 	priority=1;

double	batteryVoltage=0;
double 	chassisCurrrent;
double 	logicCurrent;
double  teknicCurrent;
double 	armCurrent;

uint8_t 	recNUC;
uint8_t 	recXBEE;
uint8_t 	recDyna;
uint8_t 	recLog;
uint8_t 	recPower;



uint8_t 	reset=0;

//Powerof motors
uint8_t 	chassisDisarm=0;

//Poweroff components after telling them
uint8_t 	shutdown=0;

//Poweroff every component without them knowing
uint8_t 	emPowerOff=0;

//Poweroff Arm whole power
uint8_t 	armPower=0;

uint16_t 	adcVal[7]={0};

uint32_t 	IC_Val11=0;
uint32_t 	IC_Val12=0;
uint32_t 	Tek1HLFB=0;
uint32_t 	IC_Val21=0;
uint32_t 	IC_Val22=0;
uint32_t 	Tek2HLFB=0;


struct _Buhler BuhlerFront,BuhlerBack;
struct _Teknic TeknicRight,TeknicLeft;

struct _PacketParam PacketNUC	(&huart4,'M','C',NUC_Receive_len,	NUC_Transmit_len);
struct _PacketParam PacketPower	(&huart2,'P','C',Power_Receive_len,	Power_Transmit_len);
struct _PacketParam PacketXBEE	(&huart1,'X','C',XBEE_Receive_len,	XBEE_Transmit_len);
struct _PacketParam PacketLog	(&huart5,'L','C',Log_Receive_len,	Log_Transmit_len);



