#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_


//1.Include the head files
#include "main.h"

//2.Define the types
#define	ulong	unsigned long
#define uchar 	unsigned char
#define uint 	unsigned int

//3.Define interfaces


//4.Redefine public functions
extern void WritePublicParametersToSD();
extern void GetPublicParametersFromSD();
extern void InitPublicParametersToSD();

//5.Redefine public variable
//6.Define private parameter
#define microSD_address_Parameters 	0

//7.Define Public parameter

#define initValue_baseSpeed 	60
#define initValue_thresholdEdge 	30



#define address_thresholdEdge	30
#define address_baseSpeed 		32
#define address_P_PID			34
#define address_D_maxPower		36
#define address_D_minPower		38
#define address_minCutveSpeedRate	40


#define address_P1		60
#define address_P2		62
#define address_P3		64
#define address_P4		66
#define address_P5		68
#define address_P6		70
#define address_P7		72
#define address_P8		74
#define address_P9		76
#define address_P10		78



#endif







