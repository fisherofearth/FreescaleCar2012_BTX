#include "uart.h"

uchar D_uartDataReceive = 0;
uchar F_uartDataReceive = 0;

void uart2_sendChar(uchar data)
{
	//unsigned long k = 0;
        
	//for (k = 0; k < 0xFFFFFFFF; k++)       //有时间限制
	//{
									   //判断发送缓冲区是否为空
	  //if ((ReSendStatusR(uartch) & (1<<SendTestBit)) != 0)
	  //{ 
		  ReSendDataR(UART2_BASE_PTR) = data;
		 // break;
	 // }
	//}
 }


void uart_SendChannel2 (uchar data)
{
    //等待发送缓冲区空
    while(!(UART_S1_REG(UART2_BASE_PTR) & UART_S1_TDRE_MASK));
    //发送数据
    ReSendDataR(UART2_BASE_PTR) = data;
}


void uart_ReceiveData()
{
	D_uartDataReceive = UART2_D;
	F_uartDataReceive = 1;
}
