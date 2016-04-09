#include "keyboard.h"
//#include  	".\external_device\LCD_LM9033\LCD_LM9033.H"
uchar keyboard_D_input = 0;
uchar F_anyPressed_keyboard = 0;
ulong T_keyPressed_keyboard = 0;

uchar keyboard_F_buttonCloseInterrupt = 0;

void delay_keyboard(unsigned int t) {
	while (t--)
		;
}
void keyboard_ScanKeyboard(void) {
	//LCD_display_number(0,0,font_6x8,6,T_keyPressed_keyboard);
	delay_keyboard(0x5FFF);
	switch (keyboard_I_input) {
	case 14:
		if (F_anyPressed_keyboard == 0 || T_keyPressed_keyboard > 100) {

			keyboard_D_input = keyboard_S_enterPressed ;
			Switch_beep(1);
			F_anyPressed_keyboard = 1;
			delay_keyboard(100);
		}
		break;
	case 13:
		if (F_anyPressed_keyboard == 0 || T_keyPressed_keyboard > 100) {
			keyboard_D_input = keyboard_S_closePressed;
			Switch_beep(1);
			F_anyPressed_keyboard = 1;
			delay_keyboard(100);
		}
		break;
	case 11:
		if (F_anyPressed_keyboard == 0 || T_keyPressed_keyboard > 100) {
			keyboard_D_input = keyboard_S_downPressed;
			Switch_beep(1);
			F_anyPressed_keyboard = 1;
			delay_keyboard(100);
		}
		break;
	case 7:
		if (F_anyPressed_keyboard == 0 || T_keyPressed_keyboard > 100) {
			keyboard_D_input = keyboard_S_upPressed;
			Switch_beep(1);
			F_anyPressed_keyboard = 1;
			delay_keyboard(100);
		}
		break;
	default:
		F_anyPressed_keyboard = 0;
		keyboard_D_input = 0;
		T_keyPressed_keyboard = 0;
		Switch_beep(0);
		delay_keyboard(100);
		break;
	}
}

void keyboard_InputClose(void) {
	keyboard_F_buttonCloseInterrupt = 1;
}
void keyboard_TimerKeyPressed(void) {
	T_keyPressed_keyboard++;
}

