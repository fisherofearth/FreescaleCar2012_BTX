#include "image.h"

uchar videoData[100][7][2];
uchar d[8] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };
uchar Pr_SelectFIFO = 0;
uchar F_selectFifo = 0;
int thresholdEdge;

struct RANGE searchRange[2];
struct POINT edgePoint[2][30];

int pixelBuffer[3][160];

struct LINE edgeLimitLines[2];

// 图像处理最终特征 ------>>>
struct CHARACTER crctr_BTX[2];

int edgeStartZ[2];
int C_activePoint[2];

int F_crossRoad = 0;
int F_startLine = 0;

// <<<------

// ------------>>>
uint iSkipPixel, iSkipLine;
#define 	SkipOnePixel() 	al422b_SendReadClock()
#define 	SkipOneLine() 	SkipPixels(160)
#define 	ReadPixel()		al422b_ReadData()
#define 	SkipPixels(x) 	for(iSkipPixel=0;iSkipPixel<(x);iSkipPixel++){SkipOnePixel();}
#define 	SkipLines(x) 	for(iSkipLine=0;iSkipLine<(x);iSkipLine++){SkipPixels(160);}
// <<<------------


uchar bufferImage[128][12][2]; //[x][y][gray]
#define grayLeave1 1
#define grayLeave2 2

/*
 * 	函数名称：	DisplayImage
 *  函数功能：	显示图像
 *  输入参数：	length  	（像素）	图像宽度            0~127
 *  			height 		（像素）	图像高度		0~95
 *    			locationX 	（像素）	图像位置X	0~127
 *       		locationY 	（x8像素）图像位置Y	0~95
 *              grayLevel 	（级）	灰阶等级		1、2
 */
void DisplayImage(int length, int height, int locationX, int locationY,
		int grayLevel) {
	int x = 0, y = 0;
	for (y = 0; y < ((height / 8) + 1); y++) {
		lm9033_SetXY(locationX,(locationY + y));
		for(x=0;x<(length+1);x++)
		{
			lm9033_WriteData(bufferImage[x][y][grayLevel-1]);
			lm9033_WriteData(bufferImage[x][y][0]);

			bufferImage[x][y][grayLevel-1] = 0;//dispose bufferImage
			bufferImage[x][y][0] =0;//dispose bufferImage
		}
	}
}

void DisplayVideo(void) {
	int i, j;
	uchar tmp;

	Pr_SelectFIFO = ~Pr_SelectFIFO;
	al422b_SelectFIFO(Pr_SelectFIFO);
	al422b_Reset();

	for (j = 55; j >= 0; j--) {
		for(i=79;i>=0;i--) {
			tmp = ~ReadPixel();

			bufferImage[i][j/8][1] |= ((tmp&0x80)>>7)<<(j%8);
			bufferImage[i][j/8][0] |= ((tmp&0x40)>>6)<<(j%8);

			SkipOnePixel();
		}
		SkipOneLine();
	}
	DisplayImage(80, 56, 0, 0, grayLeave2);
}

#define defaultRange 8
void SetSearchRange(int LorR, int base, int range) {
	searchRange[LorR].start = base - range;
	searchRange[LorR].end = base + range;
	if (LorR == left) {
		if (searchRange[left].end > leftSearchRange)
			searchRange[left].end = leftSearchRange;

	} else {
		if (searchRange[right].start < rightSearchRange)
			searchRange[right].start = rightSearchRange;
	}
}

struct POINT GetInflectionPoint(int LorR) {
	int z;
	struct POINT tmpReturn;
	int tmp = 0;
	int max = 0;
	tmpReturn = edgePoint[LorR][edgeStartZ[LorR]];

	edgeLimitLines[LorR] = LPP(crctr_BTX[LorR].head, crctr_BTX[LorR].tail);

	for (z = edgeStartZ[LorR]; z < C_activePoint[LorR]; z++) {
		tmp = DPL(edgePoint[LorR][z],edgeLimitLines[LorR]);
		tmp = ABS(tmp);
		if(tmp > max)
		{
			max = tmp;
			tmpReturn = edgePoint[LorR][z];
		}
	}
	return tmpReturn;
}

#define thresholdStartLine 35
void SearchEdge() {
	int x = 0;
	int z = 0;
	int tmp;
	int tmp1, tmp2;
	int LorR = 0;
	int buffer[160];
	int F_continueSearch[2] = { 1, 1 };
	int F_maybeCrossRoad[2] = { 0, 0 };
	int F_reborn = 0;

	uchar buffer_startLine[80][2];
	int n_startLine = 1;
	int C_startLine = 0;
	int startLineX[2];

	Pr_SelectFIFO = ~Pr_SelectFIFO;
	al422b_SelectFIFO(Pr_SelectFIFO);
	al422b_Reset();

	// initial parameters --->>>
	F_startLine = 0;

	edgeStartZ[left] = 0;
	edgeStartZ[right] = 0;

	C_activePoint[left] = 0;
	C_activePoint[right] = 0;

	searchRange[right].start = rightSearchRange;
	searchRange[right].end = midSearchRange;
	searchRange[left].start = midSearchRange;
	searchRange[left].end = leftSearchRange;

	SkipLines(skipLines-1);

	SkipPixels(40);
	for (x = 0; x < 80; x++)
		buffer_startLine[x][0] = ReadPixel();
	SkipPixels(40);

	for (z = 0; z < 30; z++) {

		if(z<8)
		{
			SkipLines(((29 - z) / skiplineControl) - 1);
			//起跑线搜索
			startLineX[left] = 79;
			startLineX[right] = 0;

			tmp1 = n_startLine % 2;
			tmp2 = (n_startLine - 1) % 2;

			SkipPixels(40);
			for(x=0;x<80;x++)buffer_startLine[x][tmp1] = ReadPixel();
			SkipPixels(40);

			C_startLine = 0;
			for(x=0;x<50;x++)
			{

				if((ABS(buffer_startLine[x][tmp1] - buffer_startLine[x][tmp2])) > (thresholdEdge+10))
				{
					C_startLine ++;
				}
				else
				{
					if(C_startLine>5)
					{
						startLineX[right] = x;
						break;
					}
					else C_startLine = 0;
				}
			}
			
			C_startLine = 0;
			for(x=79;x>50;x--)
			{
				if((ABS(buffer_startLine[x][tmp1] - buffer_startLine[x][tmp2])) > (thresholdEdge+10))
				{
					C_startLine ++;
				}
				else
				{
					
					if(C_startLine>5)
					{
						startLineX[left] = x;
						break;
					}
					else C_startLine = 0;
				}

			}

			if((ABS(startLineX[left] - startLineX[right])) < (50))
					F_startLine = 1;
			
			n_startLine ++;
		}
		else
		{
			SkipLines((29 - z) / skiplineControl);
		}

		if(searchRange[right].end > searchRange[left].start)
		{
			searchRange[left].start = (searchRange[right].end + searchRange[left].start) / 2;
			searchRange[right].end = searchRange[left].start;
		}

		tmp = searchRange[right].start;
		SkipPixels(tmp);
		for(x=searchRange[right].start;x<searchRange[right].end;x++)buffer[x] = ReadPixel();
		tmp = searchRange[left].start - searchRange[right].end;
		SkipPixels(tmp);
		for(x=searchRange[left].start;x<searchRange[left].end;x++)buffer[x] = ReadPixel();
		tmp = 160 - searchRange[left].end;
		SkipPixels(tmp);

		//right
		LorR = right;
		if(F_continueSearch[LorR] == 1)
		{
			F_continueSearch[LorR] = 0;
			for(x=(searchRange[LorR].end-1-2);x>=searchRange[LorR].start;x--)
			{
				if(Gradient(buffer[x+2] ,buffer[x]) > thresholdEdge)
				{
					if(F_reborn == 1)
					edgeStartZ[LorR] = 10;
					else
					{
						if(z>1)//判断折角
						{
							if((ABS((x - edgePoint[LorR][z-1].x) - (edgePoint[LorR][z-1].x - edgePoint[LorR][z-2].x)))> 5)
							{
								break;
							}
						}
					}
					edgePoint[LorR][z].x = x;
					edgePoint[LorR][z].z = z;
					SetSearchRange(LorR, x, defaultRange);
					F_continueSearch[LorR] = 1;
					C_activePoint[LorR] ++;

					break;
				}
			}
		}

		//left
		LorR = left;
		if(F_continueSearch[LorR] == 1)
		{
			F_continueSearch[LorR] = 0;
			for(x=searchRange[LorR].start+2;x<searchRange[LorR].end;x++)
			{
				if(Gradient(buffer[x-2] ,buffer[x]) > thresholdEdge)
				{
					if(F_reborn == 1)
					edgeStartZ[LorR] = 10;
					else
					{
						if(z>1)//判断折角
						{
							if((ABS((x - edgePoint[LorR][z-1].x) - (edgePoint[LorR][z-1].x - edgePoint[LorR][z-2].x)))> 5)
							{
								break;
							}
						}
					}
					edgePoint[LorR][z].x = x;
					edgePoint[LorR][z].z = z;
					SetSearchRange(LorR, x, defaultRange);
					F_continueSearch[LorR] = 1;
					C_activePoint[LorR] ++;
					break;
				}
			}
		}

		switch(z)
		{
			case 2://头两行都没有抓到边沿的情况 判定
			if((C_activePoint[left] + C_activePoint[right]) < 3)
			F_reborn = 1;
			break;

			case 9://“复活吧,我的勇士”
			if(F_reborn == 1)
			{
				F_continueSearch[left] = 1;
				F_continueSearch[right] = 1;

				C_activePoint[left] = 0;
				C_activePoint[right] = 0;

				searchRange[right].start = 30;
				searchRange[right].end = 79;
				searchRange[left].start = 79;
				searchRange[left].end = 130;

			}
			break;

			case 10:
			if((C_activePoint[left]+ C_activePoint[right]) < 2)goto myEnd;
			break;
		}

	}

	myEnd:

	if ((C_activePoint[left] + C_activePoint[right]) < 8) {
		F_crossRoad = 1;
	}
	if ((C_activePoint[left] + C_activePoint[right]) > 20) {
		F_crossRoad = 0;
	}
	for (LorR = 0; LorR < 2; LorR++) {
		if(C_activePoint[LorR] == 0)C_activePoint[LorR] = 1;
		crctr_BTX[LorR].tail = edgePoint[LorR][(C_activePoint[LorR]-1) + edgeStartZ[LorR]];
		crctr_BTX[LorR].head = edgePoint[LorR][edgeStartZ[LorR]];
		crctr_BTX[LorR].inflection = GetInflectionPoint(LorR);

		crctr_BTX[LorR].k_hi =KPP(crctr_BTX[LorR].inflection,crctr_BTX[LorR].head);
		crctr_BTX[LorR].k_it =KPP(crctr_BTX[LorR].tail,crctr_BTX[LorR].inflection);
		crctr_BTX[LorR].k_ht =KPP(crctr_BTX[LorR].tail,crctr_BTX[LorR].head);

		crctr_BTX[LorR].R_hit = crctr_BTX[LorR].k_it- crctr_BTX[LorR].k_hi;
	}

}

void DisplayEdge() {
	int z, i;

	for (z = (C_activePoint[left] - 1); z >= edgeStartZ[left]; z--) {
		bufferImage[79-(edgePoint[left][z].x/2)][(29+2-z)/8][0] |= d[(edgePoint[left][z].z)%8];
	}
	for (z = (C_activePoint[right] - 1); z >= edgeStartZ[right]; z--) {
		bufferImage[79-(edgePoint[right][z].x/2)][(29+2-z)/8][0] |= d[(edgePoint[right][z].z)%8];
	}
	DisplayImage(80, 30, 0, 0, 1);
}

/*void SendVideoUart(void) {
 uint i, j,p;
 uint tmp;
 Pr_SelectFIFO = ~Pr_SelectFIFO;
 al422b_SelectFIFO(Pr_SelectFIFO);

 al422b_Reset();
 if(F_uartDataReceive == 1)
 {
 F_uartDataReceive = 0;
 
 if(D_uartDataReceive == 0xFF)
 {
 for (j = 0; j < 120; j++) {
 for(i=0;i<160;i++) {
 videoDataUart[i][j] = ReadOnePixel(); 
 }
 }
 
 
 for (j = 0; j < 56; j++) {
 for(i=0;i<80;i++) {
 tmp = videoDataUart[i*2][j*2];
 if(((tmp>>7)&0x01) == 0)
 {
 videoData[i][j/8][1] |=  d[j%8]; 
 }
 else
 {
 videoData[i][j/8][1] &= ~d[j%8]; 
 }
 if(((tmp>>6)&0x01) == 0)
 {
 videoData[i][j/8][0] |=  d[j%8]; 
 }
 else
 {
 videoData[i][j/8][0] &= ~d[j%8]; 
 }
 }
 }
 
 
 
 
 uart_SendChannel2(0xfe); 
 
 for (j = 0; j < 120; j++) 
 {
 uart_SendChannel2(0xFF);
 for(i=0;i<160;i++) {
 if(videoDataUart[i][j]>0xfd)videoDataUart[i][j]=0xfd;
 uart_SendChannel2(videoDataUart[i][j]); 
 }
 }
 uart_SendChannel2(0x00); 
 uart_SendChannel2(0x00); 
 uart_SendChannel2(0x00); 
 }
 
 
 }
 }
 */
