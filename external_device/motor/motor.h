#ifndef __MOTOR_H__
#define __MOTOR_H__

//1.Include the head files
#include "derivative.h" /* include peripheral declarations */

//2.Define types

//3.Define interfaces
#define motor_I_powerOutput 	FTM0_C4V
#define motor_I_enableHbridge 	GPIOD_PDOR
#define motor_Pn_enableHbridge	(0x00000001 << 6)

//4.Redefine public functions
#define 	motor_EnableHbridge()	motor_I_enableHbridge &= ~motor_Pn_enableHbridge
#define 	motor_DisableHbridge()	motor_I_enableHbridge |=  motor_Pn_enableHbridge
#define 	motor_SetPower(x)	(motor_I_powerOutput = (x))
#define 	motor_StopMotor()	(motor_I_powerOutput = (motor_midPWMValue))
//5.Redefine public variable


//6.Define private parameter
#define 	motor_midPWMValue	1249

#endif
