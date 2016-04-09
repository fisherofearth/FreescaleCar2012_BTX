/*
 * Project 	: 	BT-X
 * Designer : 	Fish(IM-Lab, Shanghai Institute of Technology)
 * Versions :		
 */
#define PE_MCUINIT

#include "main.h"

void MCU_init(void); /* Device initialization function declaration */

void main_delay(unsigned long t) {
	unsigned int tmp;
	while (t--)
		for (tmp = 0; tmp < 1000; tmp++)
			;
}

void InitialSystem() {
	uchar tmp = 0;
	uchar C_tmp = 0;
	do{
	MCU_init(); /* call device initialization */
	MCU_enableIQR();

	lm9033_InitDevice();
	switch(C_tmp)
	{
		case 0:
		lm9033_ClearScreen();
		break;
		case 1:
		case 2:
		lm9033_ClearScreen();
		lm9033_WriteASSIC(0, 3, font_6x8, "Rebooting...");
		main_delay(0x3000);
		lm9033_ClearScreen();
		break;
		default:
		PowerSwitch_SevroDirection(power_off);
		lm9033_ClearScreen();
		lm9033_WriteASSIC(0, 0, font_6x8, "BT-X V2.3.0 --Fish");
		lm9033_WriteASSIC(0, 1, font_6x8, "Error...");
		lm9033_WriteASSIC(0, 2, font_6x8, "Tragical...");
		lm9033_WriteASSIC(0, 3, font_6x8, "Oh my god...");
		lm9033_WriteASSIC(0, 4, font_6x8, "Shit...");
		lm9033_WriteASSIC(0, 5, font_6x8, "Give up...");
		while(1);
		break;
	}
	C_tmp ++;

	lm9033_WriteASSIC(0, 0, font_6x8, "BT-X V2.3.0 --Fish");
	lm9033_WriteASSIC(0, 1, font_6x8, "INITIALIZING-->>");
	lm9033_WriteASSIC(6, 2, font_6x8, ">MCU--KinetisK60");
	lm9033_WriteASSIC(6, 3, font_6x8, ">LCD--LM9033");

	lm9033_WriteASSIC(6, 4, font_6x8, ">MOTOR");
	motor_DisableHbridge();
	motor_StopMotor();

	lm9033_WriteASSIC(6, 6, font_6x8, ">WheelSevro--S3010");
	sevro_TurnWheel(0);
	PowerSwitch_SevroDirection(power_on);

	lm9033_WriteASSIC(6, 7, font_6x8, ">Camera--OV7620");
	ov7620_Init();

	lm9033_WriteASSIC(6, 8, font_6x8, ">FIFO--AL422B");
	al422b_Init();

	lm9033_WriteASSIC(6, 10, font_6x8, ">MicroSD");
	main_delay(5000);
	tmp = microSD_InitDevice();
	main_delay(5000);
	tmp = microSD_InitDevice();
	//tmp =0 ;//跳过MicroSD检查
	
	
	
}while(tmp != 0);

	PowerSwitch_SevroDirection(power_off);
	lm9033_WriteASSIC(24, 11, font_6x8, "BT-X is ready !!!");
//main_delay(10000);
}

void main(void) {
	//private parameters definition	
	uchar tmp;
	uint i;
	uint Tr_keyPress = 0;
	//initialization
	InitialSystem();
	//WritePublicParametersToSD();		
	GetPublicParametersFromSD();
	MCU_EnablePITInterrupt0();
	MCU_DisablePITInterrupt1();//关闭速度控制中断

	while (1) {
		motor_DisableHbridge();
		motor_StopMotor();
		PowerSwitch_Camera(power_off);
		PowerSwitch_SevroDirection(power_off);
		//OnTailLED();


		InitMenu();
		ScanMenuCircularly();

		InitFunction();
		while (1)
		{

			switch(Pt_function)
			{
				case 1://竞赛
				Race();
				break;
				case 2://测试功能1
				TestFunction1();
				break;
				case 3://测试功能2
				TestFunction2();
				break;
				case 4://测试功能3
				TestFunction3();
				break;
				case 5://测试功能4
				TestFunction4();
				break;
				default:
				break;
			}

			if(keyboard_I_input == 13)//按下了key_close
			{
				Tr_keyPress ++;
				if(Tr_keyPress > 3)
				{
					Tr_keyPress= 0;
					break;
				}
			}
			
		}
	}
}

