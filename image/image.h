#ifndef __IMAGE_H__
#define __IMAGE_H__

// Include the head files ------>>>
#include 	".\external_device\ov7620\ov7620.h"
#include  	".\external_device\lm9033\lm9033.h"
#include 	"main.h"
// <<<------

// define my types ------>>>
#define	ulong	unsigned long
#define uchar 	unsigned char
#define uint 	unsigned int

typedef struct POINT {
	int x;
	int z;
};

typedef struct LINE {
	int k;
	int b;
};

typedef struct RANGE {
	int start;
	int end;
};
typedef struct CHARACTER
{
	struct POINT tail;
	struct POINT inflection;
	struct POINT head;
	int k_hi;
	int k_it;
	int k_ht;
	int R_hit;
	
};
// <<<------ 

//
#define left  1
#define right 0

#define valid  	1
#define invalid 0
// <<<------

// math calculation ------>>>
#define	Average(v1,v2) 	((v1 + v2) / 2)
#define Gradient(v1,v2)	(v1 - v2)
#define	ABS(x) 			((x)<0?-(x):(x))
extern struct POINT MPP(struct POINT P1, struct POINT P2);
extern struct LINE LPP(struct POINT P1, struct POINT P2);
extern int DPL(struct POINT P, struct LINE L);
extern int KPP(struct POINT P1, struct POINT P2);

// <<<------

// re-void variables ------>>>
extern uchar videoData[100][7][2];
extern uchar d[8];
extern uchar Pr_SelectFIFO;
extern int thresholdEdge;
// <<<------

// re-void functions ------>>>
extern void DisplayVideo(void);
extern void InitPublicParameters();
extern void SearchEdge();
extern void DisplayEdge();
// <<<-----

// ͼ������������ ------>>>
extern struct CHARACTER crctr_BTX[2];
extern int edgeStartZ[2];
extern int C_activePoint[2];
extern int F_crossRoad;
extern int F_startLine;
// <<<------

// interface ------>>>
#define skipLines 			40
#define skiplineControl 	11
#define skiplineControl_C 	29

#define leftSearchRange 	158
#define midSearchRange 		79
#define rightSearchRange 	1
// <<<------

#endif
