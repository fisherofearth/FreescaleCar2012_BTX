#include "function.h"

// 接口参数列表  ------>>>
int P1, P2, P3, P4, P5, P6, P7, P8, P9, P10;

#define P_PointT  P1
#define P_PointH  P2
#define P_K_hi  P3
#define P_K_it  P4
#define P_K_ht  P5
#define P_R  	P6
#define P_TR  	P7//turn right 右转修正系数
// <<<------ 

signed long xCorrect;
signed long xGuideReal[20];
#define xMidGuide  78
unsigned int xMeasure;

/*signed int test0, test1, test2;

 signed long tmp = 0;
 signed long difference_2;

 signed long tmpxC_0, tmpxC_1, tmpxC_2;
 signed long tmp_guide;
 
 */

void InitFunction() {

	lm9033_ClearScreen();
	//OffTailLED();//

	switch (Pt_function) {
	case 1:
		PowerSwitch_SevroDirection(power_on);//前轮舵机电源
		MCU_EnablePITInterrupt1();//使能速度控制中断
		motor_EnableHbridge();//使能H桥驱动
		MCU_EnablePITInterrupt2();//使能积分控制中断

		//encode_DisableCounter();//禁用编码器计数器（同时清除计数器）
		break;
	case 2:
		PowerSwitch_SevroDirection(power_on);//前轮舵机电源
		break;
	case 3:
		PowerSwitch_SevroDirection(power_on);//前轮舵机电源
		break;
	case 4:
		break;
	case 5:
		break;
	default:
		break;
	}
}

struct CHARACTER last_crctr_BTX[2];

#define thresholdLostEdge 3
int Race() {
	uchar i;
	int setSpeed = 200;

	int tmp;
	int tmp1, tmp2;
	int LorR;
	int tailPX;
	int inflectionPX;
	int headPX;
	int tailPZ;
	int inflectionPZ;
	int headPZ;

	struct CHARACTER N_crctr[2];

	//终项
	int E_PointHead = 0, 
		E_PointTail = 0, 
		E_K_hi = 0, 
		E_K_it = 0, 
		E_K_ht = 0,
		E_K_R = 0;

	int wheelOutput;

	if (ov7620_F_VSYNC == 1) {
		ov7620_F_VSYNC = 0;

		SearchEdge();
		ShineTailLed();
		
		
		
		

		if (C_activePoint[right] > thresholdLostEdge)//右线捕获
			N_crctr[right] = crctr_BTX[right];
		else
			//右线丢失
			N_crctr[right] = last_crctr_BTX[right];

		if (C_activePoint[left] > thresholdLostEdge)//左线捕获
			N_crctr[left] = crctr_BTX[left];
		else
			//左线丢失
			N_crctr[left] = last_crctr_BTX[left];

		tailPX = N_crctr[left].tail.x + N_crctr[right].tail.x - 158;
		headPX = N_crctr[left].head.x + N_crctr[right].head.x - 158;

		tmp1 = N_crctr[left].tail.z + N_crctr[right].tail.z;
		tmp2 = N_crctr[left].head.z + N_crctr[right].head.z;
		tailPZ = (ABS(tmp1 - tmp2)) / 5;

		E_PointHead = headPX * P2 / 10;
		E_PointTail = ((tailPX * P_PointT) / (tailPZ + 4));
		E_K_ht = ((N_crctr[left].k_ht + N_crctr[right].k_ht) * P_K_ht) / 5;
		E_K_hi = ((N_crctr[left].k_hi + N_crctr[right].k_hi) * P_K_hi) / 5;

		wheelOutput = 0;
		wheelOutput += E_PointHead;
		wheelOutput += E_PointTail;
		wheelOutput += E_K_ht;
		wheelOutput += E_K_hi;
		wheelOutput += E_K_it;
		wheelOutput += E_K_R;

		if (F_crossRoad == 0)
		{
			if(wheelOutput<0)//右转修正
			{
				wheelOutput = wheelOutput * P_TR / 10; //建议 P_TR >10
			}
			sevro_TurnWheel(wheelOutput);
		}
			

		tmp = ABS(N_crctr[left].k_it + N_crctr[right].k_it);
		setSpeed = D_baseSpeed - tmp;
		tmp = ((D_baseSpeed * minCutveSpeedRate) / 10);
		if (setSpeed < tmp)
			setSpeed = tmp;

		//继承特征量

		last_crctr_BTX[left] = N_crctr[left];
		last_crctr_BTX[right] = N_crctr[right];

	}

	tmp = ABS(wheelOutput);
	if (tmp > 890)
		tmp = 890;
	tmp /= 890;
	tmp = 10 - tmp;
	tmp += 10;
	tmp = (D_maxPower * tmp) / 20;

	if (F_integral == 1)//积分控制
	{
		F_integral = 0;

		ControlSpeed_motor(setSpeed, tmp); //速度控制
	}
	
	
	//start line
	if (F_startLine == 1) {
		if ((ABS(N_crctr[left].k_ht + N_crctr[right].k_ht)) < 10) {
			if ((C_activePoint[left] + C_activePoint[right]) > 30) {
				if(ABS(N_crctr[left].R_hit + N_crctr[left].R_hit) < 10)
				{
					F_startLine = 0;
					TailLED(led_on);
					motor_SetPower(motor_midPWMValue - 800);
					main_delay(0x2FFF);
					motor_DisableHbridge();//使能H桥驱动
				}
			}
		}
	}

	return 1;
}

int TestFunction1() {

	Race();

	DisplayEdge();

	lm9033_WriteASSIC(0, 6, font_6x8, "t:");
	lm9033_DisplayNumber(12, 6, font_6x8, 4, crctr_BTX[left].tail.x);
	lm9033_DisplayNumber(12, 7, font_6x8, 2, crctr_BTX[left].tail.z);
	lm9033_DisplayNumber(50, 6, font_6x8, 4, crctr_BTX[right].tail.x);
	lm9033_DisplayNumber(50, 7, font_6x8, 2, crctr_BTX[right].tail.z);

	lm9033_WriteASSIC(0, 8, font_6x8, "i:");
	lm9033_DisplayNumber(12, 8, font_6x8, 4, crctr_BTX[left].inflection.x);
	lm9033_DisplayNumber(12, 9, font_6x8, 2, crctr_BTX[left].inflection.z);
	lm9033_DisplayNumber(50, 8, font_6x8, 4, crctr_BTX[right].inflection.x);
	lm9033_DisplayNumber(50, 9, font_6x8, 2, crctr_BTX[right].inflection.z);

	lm9033_WriteASSIC(0, 10, font_6x8, "h:");
	lm9033_DisplayNumber(12, 10, font_6x8, 4, crctr_BTX[left].head.x);
	lm9033_DisplayNumber(12, 11, font_6x8, 2, crctr_BTX[left].head.z);
	lm9033_DisplayNumber(50, 10, font_6x8, 4, crctr_BTX[right].head.x);
	lm9033_DisplayNumber(50, 11, font_6x8, 2, crctr_BTX[right].head.z);

	lm9033_WriteASSIC(80, 0, font_6x8, "k_ht");
	lm9033_DisplayNumber(80 + 12, 1, font_6x8, 3, crctr_BTX[left].k_ht);
	lm9033_DisplayNumber(80 + 12, 2, font_6x8, 3, crctr_BTX[right].k_ht);

	lm9033_WriteASSIC(80, 3, font_6x8, "k_it");
	lm9033_DisplayNumber(80 + 12, 4, font_6x8, 3, crctr_BTX[left].k_it);
	lm9033_DisplayNumber(80 + 12, 5, font_6x8, 3, crctr_BTX[right].k_it);

	lm9033_WriteASSIC(80, 6, font_6x8, "k_hi");
	lm9033_DisplayNumber(80 + 12, 7, font_6x8, 3, crctr_BTX[left].k_hi);
	lm9033_DisplayNumber(80 + 12, 8, font_6x8, 3, crctr_BTX[right].k_hi);

	lm9033_WriteASSIC(80, 9, font_6x8, "R_hit");
	lm9033_DisplayNumber(80 + 12, 10, font_6x8, 3, crctr_BTX[left].R_hit);
	lm9033_DisplayNumber(80 + 12, 11, font_6x8, 3, crctr_BTX[right].R_hit);
	return 1;
}

int TestFunction2() {
	
	Race();
	
	DisplayEdge();
	
	lm9033_WriteASSIC(0, 6, font_6x8, "t:");
	lm9033_DisplayNumber(12, 6, font_6x8, 4, (crctr_BTX[left].tail.x + crctr_BTX[right].tail.x));
	lm9033_DisplayNumber(12, 7, font_6x8, 2, (crctr_BTX[left].tail.z + crctr_BTX[right].tail.z));

	lm9033_WriteASSIC(0, 8, font_6x8, "i:");
	lm9033_DisplayNumber(12, 8, font_6x8, 4, (crctr_BTX[left].inflection.x + crctr_BTX[right].inflection.x));
	lm9033_DisplayNumber(12, 9, font_6x8, 2, (crctr_BTX[left].inflection.z + crctr_BTX[right].inflection.z));

	lm9033_WriteASSIC(0, 10, font_6x8, "h:");
	lm9033_DisplayNumber(12, 10, font_6x8, 4, (crctr_BTX[left].head.x + crctr_BTX[right].head.x));
	lm9033_DisplayNumber(12, 11, font_6x8, 2, (crctr_BTX[left].head.z + crctr_BTX[right].head.z));

	lm9033_WriteASSIC(80, 0, font_6x8, "k_ht");
	lm9033_DisplayNumber(80 + 12, 1, font_6x8, 3, (crctr_BTX[left].k_ht + crctr_BTX[right].k_ht));

	lm9033_WriteASSIC(80, 3, font_6x8, "k_it");
	lm9033_DisplayNumber(80 + 12, 4, font_6x8, 3, (crctr_BTX[left].k_it + crctr_BTX[right].k_it));

	lm9033_WriteASSIC(80, 6, font_6x8, "k_hi");
	lm9033_DisplayNumber(80 + 12, 7, font_6x8, 3, (crctr_BTX[left].k_hi + crctr_BTX[right].k_hi));

	lm9033_WriteASSIC(80, 9, font_6x8, "R_hit");
	lm9033_DisplayNumber(80 + 12, 10, font_6x8, 3, (crctr_BTX[left].R_hit + crctr_BTX[right].R_hit));
	
	return 1;
}

int TestFunction3() {
	if (ov7620_F_VSYNC == 1) {
		ov7620_F_VSYNC = 0;

		SearchEdge();
		ShineTailLed();
		DisplayEdge();

	}
	return 1;
}

int TestFunction4() {
	if (ov7620_F_VSYNC == 1) {
		ov7620_F_VSYNC = 0;
		DisplayVideo();//实时显示图像
	}
	/*
	 * keyboard_ScanKeyboard();
	 if(keyboard_D_input == keyboard_S_upPressed)
	 {
	 keyboard_D_input = 0;
	 thresholdEdge ++;
	 }
	 if(keyboard_D_input == keyboard_S_downPressed)
	 {
	 keyboard_D_input = 0;
	 thresholdEdge --;
	 }
	 lm9033_DisplayNumber(82, 0, font_6x8, 4, (uint)(thresholdEdge));
	 */
	return 1;
}
