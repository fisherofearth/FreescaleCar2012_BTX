#include "speedcontrol.h"
#define	ABS(x) 			((x)<0?-(x):(x))

//uchar F_speedControlClock = 0;
int D_speedNow;
long D_speedIntegration;
long D_speedOutput; 
int D_baseSpeed;

int minCutveSpeedRate;


int D_maxPower ;//max value :1249
int D_minPower;
int P_PID;

void ClockSpeedControl()//write into MCUinit.c
{
	//F_speedControlClock = 1;
	D_speedNow = I_pulseCounter_encode;
	encode_ClearCounter();
}
int D_last_speedIntegration = 0;
void ControlSpeed_motor(int D_Speed, int myMaxPower) //
{
		
	D_speedIntegration = D_Speed - D_speedNow;
	 
	D_speedOutput += ((D_speedIntegration) * (ABS(D_speedIntegration * P_PID) / 10));
	D_speedOutput += (D_speedIntegration - D_last_speedIntegration);
	
	if (D_speedOutput < (D_minPower))D_speedOutput = D_minPower;
	if (D_speedOutput > (myMaxPower))D_speedOutput = myMaxPower;

	motor_SetPower(motor_midPWMValue + (int)(D_speedOutput));
	D_last_speedIntegration = D_speedIntegration ; 
}

