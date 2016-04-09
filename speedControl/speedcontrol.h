#ifndef __SPEEDCONTROL_H__
#define __SPEEDCONTROL_H__

//1.Include the head files
#include  	".\external_device\motor\motor.h"
#include  	".\external_device\encode\encode.h"
#include 	"MCUinit.h"
#include "main.h"

//2.Define the types
#define	ulong	unsigned long
#define uchar 	unsigned char
#define uint 	unsigned int

//3.Define interfaces

//4.Redefine the functions
extern void ClockSpeedControl();
extern void ControlSpeed_motor(int D_Speed, int myMaxPower);

//extern uchar F_speedControlClock;

extern int D_baseSpeed;
extern int C_pulse_Encode;
extern int D_speedNow;
extern int minCutveSpeedRate;

extern long D_speedIntegration;

extern int D_maxPower;//max value :1249
extern int D_minPower;
extern int P_PID;

#endif
