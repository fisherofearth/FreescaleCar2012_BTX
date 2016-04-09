#ifndef __LM9033_H__
#define __LM9033_H__

//1.Include the head files
#include "derivative.h" /* include peripheral declarations */


//2.Define types
#define	ulong	unsigned long
#define uchar 	unsigned char
#define uint 	unsigned int

//3.Define interfaces
#define PORT_LM9033_SID   	GPIOA_PDOR 	//define this LCD use which port of MCU
#define PORT_LM9033_SCLK	GPIOA_PDOR
#define PORT_LM9033_RS		GPIOB_PDOR
#define PORT_LM9033_RST		GPIOB_PDOR
#define PORT_LM9033_CS		GPIOC_PDOR

#define SID 	(((ulong)0x01)<<(26)) 	//BIT 26
#define SCLK 	(((ulong)0x01)<<(28)) 	//BIT 28
#define RS		(((ulong)0x01)<<(20)) 	//BIT 20
#define RST 	(((ulong)0x01)<<(22)) 	//BIT 22
#define CS 		(((ulong)0x01)<<( 0)) 	//BIT 0 

//4.Redefine public functions
extern void lm9033_InitDevice(void);
extern void lm9033_ClearScreen(void);
extern void lm9033_SetXY(unsigned char X, unsigned char Y);
extern void lm9033_WriteData(unsigned char dat);
extern void lm9033_WriteASSIC(uchar X, uchar Y,uchar font, char *s);
extern void lm9033_DisplayNumber(uchar x , uchar y, uchar font, uchar length, int num);

//5.Redefine public variable


//6.Define private parameter
#define font_6x8  	0
#define font_8x16 	1

#endif
