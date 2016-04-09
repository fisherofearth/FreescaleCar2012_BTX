#ifndef __MENU_H__
#define __MENU_H__

//1.Include the head files
#include  	".\external_device\keyboard\keyboard.h"
#include  	".\external_device\lm9033\lm9033.h"
#include	".\speedcontrol\speedcontrol.h"
#include 	"main.h"

//2.Define the types
#define	ulong	unsigned long
#define uchar 	unsigned char
#define uint 	unsigned int

//3.Define interfaces


//4.Redefine the functions
extern void ScanMenu();
extern void InitMenu(void);
extern uchar Pt_function;//主功能指针
extern void ScanMenuCircularly();

#define 	parameterSeting1Number 2 //参数设定选项在主菜单中选项的序号
#define 	parameterSeting2Number 3

#define 	mainMenuTermName_1 	"01.RACE"
#define 	mainMenuTermName_2 	"02.Set Patameters 1"
#define 	mainMenuTermName_3 	"03.Set Patameters 2"
#define 	mainMenuTermName_4 	"04.NC"
#define 	mainMenuTermName_5 	"05.Analyze Image 1"
#define 	mainMenuTermName_6 	"06.Analyze Image 2"
#define 	mainMenuTermName_7 	"07.Clean Floor"
#define 	mainMenuTermName_8 	"08.Display Video"
#define 	mainMenuTermName_9 	"09.NC"
#define 	mainMenuTermName_10 "10.NC"

#define 	setParamete1TermName_1 	"01.Speed"
#define 	setParamete1Address_1 	D_baseSpeed
#define 	setParamete1MaxValue_1 	500
#define 	setParamete1MinValue_1	0

#define 	setParamete1TermName_2 	"02.MCSR%"
#define 	setParamete1Address_2 	minCutveSpeedRate
#define 	setParamete1MaxValue_2 	10
#define 	setParamete1MinValue_2	0

#define 	setParamete1TermName_3 	"03.thres"
#define 	setParamete1Address_3 	thresholdEdge
#define 	setParamete1MaxValue_3 	255
#define 	setParamete1MinValue_3	0

#define 	setParamete1TermName_4 	"04.P_PID"
#define 	setParamete1Address_4 	P_PID
#define 	setParamete1MaxValue_4 	100
#define 	setParamete1MinValue_4	1

#define 	setParamete1TermName_5 	"05.maxPwr"
#define 	setParamete1Address_5 	D_maxPower
#define 	setParamete1MaxValue_5 	1249
#define 	setParamete1MinValue_5	D_minPower

#define 	setParamete1TermName_6 	"06.minPwr"
#define 	setParamete1Address_6 	D_minPower
#define 	setParamete1MaxValue_6 	D_maxPower	
#define 	setParamete1MinValue_6	0

#define 	setParamete1TermName_7 	"07.NC"
#define 	setParamete1Address_7 	NC
#define 	setParamete1MaxValue_7 	30
#define 	setParamete1MinValue_7	1

#define 	setParamete1TermName_8 	"08.NC"
#define 	setParamete1Address_8 	NC
#define 	setParamete1MaxValue_8 	30
#define 	setParamete1MinValue_8	1

#define 	setParamete1TermName_9 	"09.NC"
#define 	setParamete1Address_9 	NC
#define 	setParamete1MaxValue_9 	30
#define 	setParamete1MinValue_9	1

#define 	setParamete1TermName_10 "10.NC"
#define 	setParamete1Address_10 	NC
#define 	setParamete1MaxValue_10 30
#define 	setParamete1MinValue_10	1

#define 	setParamete2TermName_1 	"11.PT"
#define 	setParamete2Address_1 	P1
#define 	setParamete2MaxValue_1 	200
#define 	setParamete2MinValue_1	0

#define 	setParamete2TermName_2 	"12.PH"
#define 	setParamete2Address_2 	P2
#define 	setParamete2MaxValue_2 	200
#define 	setParamete2MinValue_2	0

#define 	setParamete2TermName_3 	"13.K_hi"
#define 	setParamete2Address_3 	P3
#define 	setParamete2MaxValue_3 	200
#define 	setParamete2MinValue_3	0

#define 	setParamete2TermName_4 	"14.K_it"
#define 	setParamete2Address_4 	P4
#define 	setParamete2MaxValue_4 	200
#define 	setParamete2MinValue_4	0

#define 	setParamete2TermName_5 	"15.K_ht"
#define 	setParamete2Address_5 	P5
#define 	setParamete2MaxValue_5 	200
#define 	setParamete2MinValue_5	0

#define 	setParamete2TermName_6 	"16.R"
#define 	setParamete2Address_6 	P6
#define 	setParamete2MaxValue_6 	200
#define 	setParamete2MinValue_6	0

#define 	setParamete2TermName_7 	"17.P_TR"
#define 	setParamete2Address_7 	P7
#define 	setParamete2MaxValue_7 	200
#define 	setParamete2MinValue_7	0

#define 	setParamete2TermName_8 	"18.NC"
#define 	setParamete2Address_8 	P8
#define 	setParamete2MaxValue_8 	200
#define 	setParamete2MinValue_8	0

#define 	setParamete2TermName_9 	"19.P9*"
#define 	setParamete2Address_9 	P9
#define 	setParamete2MaxValue_9 	200
#define 	setParamete2MinValue_9	0

#define 	setParamete2TermName_10 "20.P10*"
#define 	setParamete2Address_10 	P10
#define 	setParamete2MaxValue_10 200
#define 	setParamete2MinValue_10	0

#endif
