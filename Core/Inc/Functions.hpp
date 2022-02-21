/*
 * Functions.hpp
 *
 *  Created on: Jan 26, 2022
 *      Author: Nazanin
 */

#ifndef INC_FUNCTIONS_HPP_
#define INC_FUNCTIONS_HPP_

#include "math.h"
#include "Variables.hpp"
#include "tim.h"
#include "usart.h"
#include "gpio.h"



extern 	void 		CheckRecData(struct _PacketParam* PacketParam);
extern	void 		AssignData			(struct _PacketParam* PacketParam)	;
extern 	void 		HipHop				(void)	;
extern	void 		StopMotors			(void)	;
extern	void 		StartMotors			(void)	;
extern 	void		ConvertADC2Degree	(void)	;
extern 	void 		Send2NUC			(void)	;
extern	void 		EmergencyPowerOff	(void);
extern 	void 		sendData2Motors		(void);
extern 	void 		CheckPacketValidation(void);
extern 	void 		MakeCPPacket		(void);
extern 	void 		SendPacket			(struct _PacketParam* packetParam);


#endif /* INC_FUNCTIONS_HPP_ */
