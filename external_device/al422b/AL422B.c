#include "al422b.h"
void AL422B_delay(uint t)
{
	while(t--);
}
/*---------FIFO_���Ͷ�ʱ��---------*/
void al422b_SendReadClock() 
{
	AL422B_Control_Interface |= AL422B_RCK_MASK;
	AL422B_Control_Interface &= ~AL422B_RCK_MASK;
}
/*---------FIFO_���Ͷ�ʱ��---------*/

/*---------��ȡ����----------------*/
uchar al422b_ReadData(void) { //��ȡ����

	al422b_SendReadClock();
	return AL422B_Data_Interface;
}
/*---------��ȡ����----------------*/

/*---------FIFO_��ʱ������---------*/
void al422b_Reset(void) { //FIFO��ָ�븴λ
	AL422B_Control_Interface &= ~AL422B_RRST_MASK;
	AL422B_delay(T_RRS);
	al422b_SendReadClock();
	al422b_SendReadClock();
	AL422B_delay(T_RRH);
	AL422B_Control_Interface |= AL422B_RRST_MASK;

}
/*---------FIFO_��ʱ������---------*/

/*---------FIFO_����ʼ�� ----------*/
void al422b_Init(void) {
	AL422B_delay(100);
	al422b_SelectFIFO(0);
}
/*---------FIFO_����ʼ�� ----------*/

void al422b_SelectRead(int device) {
	switch (device) {
	case 0:
		AL422B_delay(T_REH);
		AL422B_Control_Interface |= AL422B_RE2_MASK;
		AL422B_Control_Interface &= ~AL422B_RE1_MASK;
		AL422B_delay(T_RES);
		break;
	case 1:
		AL422B_delay(T_WEH);
		AL422B_Control_Interface &= ~AL422B_RE2_MASK;
		AL422B_Control_Interface |= AL422B_RE1_MASK;
		AL422B_delay(T_WES);
		
		break;
	}
}

void al422b_SelectWrite(int device) {
	switch (device) {
	case 0:
		AL422B_delay(T_REH);
		AL422B_Control_Interface |= AL422B_WE2_MASK;
		AL422B_Control_Interface &= ~AL422B_WE1_MASK;
		AL422B_delay(T_RES);
		break;
	case 1:
		AL422B_delay(T_WEH);
		AL422B_Control_Interface &= ~AL422B_WE2_MASK;
		AL422B_Control_Interface |= AL422B_WE1_MASK;
		AL422B_delay(T_WES);
		break;
	}
}

/*---------�л���ƬFIFO------------*/
void al422b_SelectFIFO(int device) {
	if(device == 1)
	{
		al422b_SelectRead(1);
		al422b_SelectWrite(0);
	}
	else
	{
		al422b_SelectRead(0);
		al422b_SelectWrite(1);
	}
		
}
/*---------�л���ƬFIFO------------*/

