#ifndef INCLUDE_H_
#define INCLUDE_H_

//1.Include the head files
#include 	<stdio.h>
#include 	"derivative.h" /* include peripheral declarations */

#include  	".\external_device\external_device.h"
#include	".\chip_device\chip_device.h"
#include	".\menu\menu.h"
#include	".\image\image.h"
#include	".\speedcontrol\speedcontrol.h"
#include 	".\function\function.h"
#include 	".\integral\integral.h"
#include 	".\parameters\parameters.h"

                  
//2.Define the types
#define	ulong	unsigned long
#define uchar 	unsigned char
#define uint 	unsigned int
//#include 	"Public_Parameters.h"

//3.Define interfaces
//4.Redefine the functions


#define   ABS(x) ((x)<0?-(x):(x))
extern unsigned int flag_PITtest;

#endif
