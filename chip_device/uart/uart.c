#include "uart.h"

uchar D_uartDataReceive = 0;
uchar F_uartDataReceive = 0;

void uart2_sendChar(uchar data)
{
	//unsigned long k = 0;
        
	//for (k = 0; k < 0xFFFFFFFF; k++)       //��ʱ������
	//{
									   //�жϷ��ͻ������Ƿ�Ϊ��
	  //if ((ReSendStatusR(uartch) & (1<<SendTestBit)) != 0)
	  //{ 
		  ReSendDataR(UART2_BASE_PTR) = data;
		 // break;
	 // }
	//}
 }


void uart_SendChannel2 (uchar data)
{
    //�ȴ����ͻ�������
    while(!(UART_S1_REG(UART2_BASE_PTR) & UART_S1_TDRE_MASK));
    //��������
    ReSendDataR(UART2_BASE_PTR) = data;
}


void uart_ReceiveData()
{
	D_uartDataReceive = UART2_D;
	F_uartDataReceive = 1;
}
