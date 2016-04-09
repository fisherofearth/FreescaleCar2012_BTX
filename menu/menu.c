#include 	"menu.h"

int *parameterAddress;

uchar Pt_menu[2] = { 1, 0 };
uchar F_seettingParameter = 0;
char *termName[10];
int NC;
int maxValueParameter, minValueParameter;

uchar Pt_function = 0;//主功能指针

void SelectParameter(void) {
	switch (Pt_menu[0]) {
	case parameterSeting1Number:
		switch (Pt_menu[1]) {
		case 1:
			parameterAddress = &setParamete1Address_1;
			maxValueParameter = setParamete1MaxValue_1;
			minValueParameter = setParamete1MinValue_1;
			break;
		case 2:
			parameterAddress = &setParamete1Address_2;
			maxValueParameter = setParamete1MaxValue_2;
			minValueParameter = setParamete1MinValue_2;
			break;
		case 3:
			parameterAddress = &setParamete1Address_3;
			maxValueParameter = setParamete1MaxValue_3;
			minValueParameter = setParamete1MinValue_3;
			break;
		case 4:
			parameterAddress = &setParamete1Address_4;
			maxValueParameter = setParamete1MaxValue_4;
			minValueParameter = setParamete1MinValue_4;
			break;
		case 5:
			parameterAddress = &setParamete1Address_5;
			maxValueParameter = setParamete1MaxValue_5;
			minValueParameter = setParamete1MinValue_5;
			break;
		case 6:
			parameterAddress = &setParamete1Address_6;
			maxValueParameter = setParamete1MaxValue_6;
			minValueParameter = setParamete1MinValue_6;
			break;
		case 7:
			parameterAddress = &setParamete1Address_7;
			maxValueParameter = setParamete1MaxValue_7;
			minValueParameter = setParamete1MinValue_7;
			break;
		case 8:
			parameterAddress = &setParamete1Address_8;
			maxValueParameter = setParamete1MaxValue_8;
			minValueParameter = setParamete1MinValue_8;
			break;
		case 9:
			parameterAddress = &setParamete1Address_9;
			maxValueParameter = setParamete1MaxValue_9;
			minValueParameter = setParamete1MinValue_9;
			break;
		case 10:
			parameterAddress = &setParamete1Address_10;
			maxValueParameter = setParamete1MaxValue_10;
			minValueParameter = setParamete1MinValue_10;
			break;
		default:
			parameterAddress = &NC;
			maxValueParameter = 1;
			minValueParameter = 0;
			break;
		}
		break;
	case parameterSeting2Number:
		switch (Pt_menu[1]) {
		case 1:
			parameterAddress = &setParamete2Address_1;
			maxValueParameter = setParamete2MaxValue_1;
			minValueParameter = setParamete2MinValue_1;
			break;
		case 2:
			parameterAddress = &setParamete2Address_2;
			maxValueParameter = setParamete2MaxValue_2;
			minValueParameter = setParamete2MinValue_2;
			break;
		case 3:
			parameterAddress = &setParamete2Address_3;
			maxValueParameter = setParamete2MaxValue_3;
			minValueParameter = setParamete2MinValue_3;
			break;
		case 4:
			parameterAddress = &setParamete2Address_4;
			maxValueParameter = setParamete2MaxValue_4;
			minValueParameter = setParamete2MinValue_4;
			break;
		case 5:
			parameterAddress = &setParamete2Address_5;
			maxValueParameter = setParamete2MaxValue_5;
			minValueParameter = setParamete2MinValue_5;
			break;
		case 6:
			parameterAddress = &setParamete2Address_6;
			maxValueParameter = setParamete2MaxValue_6;
			minValueParameter = setParamete2MinValue_6;
			break;
		case 7:
			parameterAddress = &setParamete2Address_7;
			maxValueParameter = setParamete2MaxValue_7;
			minValueParameter = setParamete2MinValue_7;
			break;
		case 8:
			parameterAddress = &setParamete2Address_8;
			maxValueParameter = setParamete2MaxValue_8;
			minValueParameter = setParamete2MinValue_8;
			break;
		case 9:
			parameterAddress = &setParamete2Address_9;
			maxValueParameter = setParamete2MaxValue_9;
			minValueParameter = setParamete2MinValue_9;
			break;
		case 10:
			parameterAddress = &setParamete2Address_10;
			maxValueParameter = setParamete2MaxValue_10;
			minValueParameter = setParamete2MinValue_10;
			break;
		default:
			parameterAddress = &NC;
			maxValueParameter = 1;
			minValueParameter = 0;
			break;
		}
		break;

	}

}

void InitMenuTermName(void) {
	if (Pt_menu[1] == 0) {
		termName[0] = mainMenuTermName_1;
		termName[1] = mainMenuTermName_2;
		termName[2] = mainMenuTermName_3;
		termName[3] = mainMenuTermName_4;
		termName[4] = mainMenuTermName_5;
		termName[5] = mainMenuTermName_6;
		termName[6] = mainMenuTermName_7;
		termName[7] = mainMenuTermName_8;
		termName[8] = mainMenuTermName_9;
		termName[9] = mainMenuTermName_10;
	} else {
		switch (Pt_menu[0]) {
		case 0:

			break;
		case parameterSeting1Number:
			termName[0] = setParamete1TermName_1;
			termName[1] = setParamete1TermName_2;
			termName[2] = setParamete1TermName_3;
			termName[3] = setParamete1TermName_4;
			termName[4] = setParamete1TermName_5;
			termName[5] = setParamete1TermName_6;
			termName[6] = setParamete1TermName_7;
			termName[7] = setParamete1TermName_8;
			termName[8] = setParamete1TermName_9;
			termName[9] = setParamete1TermName_10;
			break;
		case parameterSeting2Number:
			termName[0] = setParamete2TermName_1;
			termName[1] = setParamete2TermName_2;
			termName[2] = setParamete2TermName_3;
			termName[3] = setParamete2TermName_4;
			termName[4] = setParamete2TermName_5;
			termName[5] = setParamete2TermName_6;
			termName[6] = setParamete2TermName_7;
			termName[7] = setParamete2TermName_8;
			termName[8] = setParamete2TermName_9;
			termName[9] = setParamete2TermName_10;
			break;
		}
	}

}

void DisplayMenu(void) {
	int *Pt_display;
	uchar i;
	uchar tmp;
	for (i = 0; i < 10; i++)
		lm9033_WriteASSIC(0, i + 1, font_6x8, "  ");
	switch (Pt_menu[1]) {
	case 0:
		lm9033_WriteASSIC(0, Pt_menu[0], font_6x8, ">>");
		break;
	default:
		switch (Pt_menu[0]) {
		case parameterSeting1Number:
		case parameterSeting2Number:

			if (F_seettingParameter == 1) {
				SelectParameter();
				lm9033_DisplayNumber(60, Pt_menu[1], font_6x8, 6,
						(*parameterAddress));
				lm9033_WriteASSIC(110, Pt_menu[1], font_6x8, "<<");
				lm9033_WriteASSIC(0, Pt_menu[1], font_6x8, "  ");
			} else {
				lm9033_WriteASSIC(110, Pt_menu[1], font_6x8, "  ");
				lm9033_WriteASSIC(0, Pt_menu[1], font_6x8, ">>");
			}
			break;
		}
		break;
	}
	InitMenuTermName();

	tmp = Pt_menu[1];
	NC = 0;

	for (i = 0; i < 10; i++) {
		lm9033_WriteASSIC(12,i+1,font_6x8,termName[i]);

		if(tmp != 0)
		{
			Pt_menu[1] = i;
			SelectParameter();
			if((parameterAddress) != (&NC))
			{
				lm9033_DisplayNumber(60,i,font_6x8,6,(*parameterAddress));
			}
			else
			{
				lm9033_WriteASSIC(60,i,font_6x8,"      ");
			}
		}
	}
	Pt_menu[1] = tmp;
}

void ScanMenu() {

	keyboard_ScanKeyboard();
	if (Pt_menu[1] == 0) {//一级菜单
		switch (keyboard_D_input) {
		case keyboard_S_upPressed:
			if (Pt_menu[0] == 1)
				Pt_menu[0] = 11;
			Pt_menu[0] -= 1;

			break;
		case keyboard_S_downPressed:
			Pt_menu[0] += 1;
			if (Pt_menu[0] > 10)
				Pt_menu[0] = 1;
			break;
		case keyboard_S_enterPressed:
			switch (Pt_menu[0]) {
			case 1:
				Pt_function = 1;
				lm9033_ClearScreen();
				break;
			case 2:
				Pt_menu[1] = 1;
				lm9033_ClearScreen();
				break;
			case 3:
				Pt_menu[1] = 1;
				lm9033_ClearScreen();
				break;
			case 5:
				Pt_function = 2;
				lm9033_ClearScreen();
				break;
			case 6:
				Pt_function = 3;
				lm9033_ClearScreen();
				break;
			case 7:
				Pt_function = 4;
				lm9033_ClearScreen();
				break;
			case 8:
				Pt_function = 5;
				lm9033_ClearScreen();
				break;
			default:
				break;
			}
			break;
		case keyboard_S_closePressed://在主菜单按下CLOSE键
			Pt_menu[0] = 1;
			break;
		default:
			break;
		}
	} else //二级菜单
	{
		switch (keyboard_D_input) {
			case keyboard_S_upPressed:
				if (F_seettingParameter == 1) {
					SelectParameter();//选择需要设定的参数
					(*parameterAddress)++;
					if ((*parameterAddress) > maxValueParameter) {
						(*parameterAddress) = maxValueParameter;
					}
				} else {
					if (Pt_menu[1] == 1)
						Pt_menu[1] = 11;
					Pt_menu[1] -= 1;
				}
				break;
			case keyboard_S_downPressed:
				if (F_seettingParameter == 1) {
					SelectParameter();//选择需要设定的参数
					if ((*parameterAddress) == minValueParameter) {
						(*parameterAddress) = minValueParameter + 1;
					}
					(*parameterAddress)--;
				} else {
					Pt_menu[1] += 1;
					if (Pt_menu[1] > 10)
						Pt_menu[1] = 1;
				}
				break;
			case keyboard_S_enterPressed:
				F_seettingParameter = 1;
				break;
			case keyboard_S_closePressed:
				if (F_seettingParameter == 1) {
					F_seettingParameter = 0;
				} else {
					Pt_menu[1] = 0;
					lm9033_ClearScreen();
					WritePublicParametersToSD();
				}
				break;
			default:
				break;
		}
	}
	if (keyboard_D_input != 0) {
		DisplayMenu();
		keyboard_D_input = 0;
	}
	
}
void InitMenu(void) {
	Pt_menu[0] = 1;
	Pt_menu[1] = 0;
	Pt_function = 0;
	lm9033_ClearScreen();
	InitMenuTermName();
	ScanMenu();
	DisplayMenu();
	keyboard_EnableLonePress();
}
void ScanMenuCircularly()
{
	for(;Pt_function == 0;)
	{
		ScanMenu();
	}
	keyboard_F_buttonCloseInterrupt = 0;
}

