#ifndef __SEVRO_H__
#define __SEVRO_H__

//1.Include the head files
#include "derivative.h" /* include peripheral declarations */

//2.Define types
#define	ulong	unsigned long
#define uchar 	unsigned char
#define uint 	unsigned int

//3.Define interfaces
#define sevro_I_wheelPWM	FTM1_C1V	//0~62499
#define sevro_I_cameraPWM	FTM1_C0V  	//0~62499

//4.Redefine public functions
extern void sevro_TurnCamera(signed int direction);
extern void sevro_TurnWheel(signed int direction);

//5.Redefine public variable


//6.Define private parameter
#define midValueWheelSevro 	(58450 )
#define maxValueWheelSevro	(midValueWheelSevro + 890)
#define minValueWheelSevro 	(midValueWheelSevro - 890)


#define midValueCameraSevro (57168-100)
#define maxValueCameraSevro (midValueCameraSevro + 1000)
#define minValueCameraSevro (midValueCameraSevro - 1000)

#endif
