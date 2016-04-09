#include "lm9033.h" 
#include "assic_6x8.h"

void lm9033_delay(unsigned int t)
{
	while(t--);
}
void lm9033_SwitchSID(unsigned char SID_data)
{
	switch(SID_data)
	{
	case 1:
		PORT_LM9033_SID |= SID;
		break;
	case 0:
		PORT_LM9033_SID &= ~SID;
		break;
	default:
		PORT_LM9033_SID &= ~SID;
		break;
	}
}
void lm9033_SendClock()
{
	PORT_LM9033_SCLK &= ~SCLK;
	PORT_LM9033_SCLK |= SCLK;
}
void lm9033_WriteCMD(unsigned char dat){
	
	PORT_LM9033_CS &= ~CS;
	lm9033_delay (10);
	PORT_LM9033_RS &= ~RS;	//INSTRUCTION
	lm9033_delay (10);
	
	lm9033_SwitchSID(((dat & 0x80) == 0x80)); lm9033_SendClock(); // send MSB
	lm9033_SwitchSID(((dat & 0x40) == 0x40)); lm9033_SendClock();
	lm9033_SwitchSID(((dat & 0x20) == 0x20)); lm9033_SendClock();
	lm9033_SwitchSID(((dat & 0x10) == 0x10)); lm9033_SendClock();
	lm9033_SwitchSID(((dat & 0x08) == 0x08)); lm9033_SendClock();
	lm9033_SwitchSID(((dat & 0x04) == 0x04)); lm9033_SendClock();
	lm9033_SwitchSID(((dat & 0x02) == 0x02)); lm9033_SendClock();
	lm9033_SwitchSID(((dat & 0x01) == 0x01)); lm9033_SendClock(); // sedn LSB

	PORT_LM9033_CS |= CS;
}

void lm9033_WriteData(unsigned char dat){
	PORT_LM9033_CS &= ~CS;
	PORT_LM9033_RS |= RS;	//DISPLAY DATA

  	lm9033_SwitchSID(((dat & 0x80) == 0x80)); lm9033_SendClock(); // send MSB
  	lm9033_SwitchSID(((dat & 0x40) == 0x40)); lm9033_SendClock();
  	lm9033_SwitchSID(((dat & 0x20) == 0x20)); lm9033_SendClock();
  	lm9033_SwitchSID(((dat & 0x10) == 0x10)); lm9033_SendClock();
  	lm9033_SwitchSID(((dat & 0x08) == 0x08)); lm9033_SendClock();
  	lm9033_SwitchSID(((dat & 0x04) == 0x04)); lm9033_SendClock();
  	lm9033_SwitchSID(((dat & 0x02) == 0x02)); lm9033_SendClock();
  	lm9033_SwitchSID(((dat & 0x01) == 0x01)); lm9033_SendClock(); // sedn LSB

  	PORT_LM9033_CS |= CS;
}

void lm9033_SetXY(unsigned char X, unsigned char Y){
    lm9033_WriteCMD(0xB0 | Y);	
    lm9033_WriteCMD(0x10 | (X>>4));    
	lm9033_WriteCMD(0x0F & X);  

}

void lm9033_ClearScreen(void){
    unsigned char x,y;
   
	for(y=0;y<12;y++)
	{ 
		lm9033_SetXY(0,y);
		for(x=0;x<128;x++)
		{
			lm9033_WriteData(0x00);
			lm9033_WriteData(0x00);
		}
	}		      	
}


void lm9033_InitDevice(void)
{	
	PORT_LM9033_SCLK |= SCLK;
	
	PORT_LM9033_RST |= RST;
	lm9033_delay(100);
	PORT_LM9033_RST &= ~RST;
	lm9033_delay(100);										 	
	PORT_LM9033_RST |= RST;
	lm9033_delay(1000);
	
	PORT_LM9033_CS |= CS;//¹Ø±ÕLCD
	lm9033_delay(100);
	lm9033_WriteCMD(0x48);	
	lm9033_WriteCMD(0x60);	 
	
	lm9033_WriteCMD(0xa1);	
	lm9033_WriteCMD(0xc8);	
	lm9033_WriteCMD(0x44);
	lm9033_WriteCMD(0x10);
	
	lm9033_WriteCMD(0x40);	
	lm9033_WriteCMD(0x00);
	lm9033_WriteCMD(0xab);	
	lm9033_WriteCMD(0x66);	
	lm9033_WriteCMD(0x27);
	lm9033_WriteCMD(0x81);
	
	lm9033_WriteCMD(0x20);	
	lm9033_WriteCMD(0x54);//select LCD bias
	
	lm9033_WriteCMD(0x93);	//set FRC and PWM mode			 
	
	lm9033_WriteCMD(0x2c);
	lm9033_delay(0xF);
	lm9033_WriteCMD(0x2e);
	lm9033_delay(0xF);	
	lm9033_WriteCMD(0x2f);
	lm9033_delay(0xF);	
	lm9033_WriteCMD(0xaf); 	
	
	
	lm9033_WriteCMD(0x88); 
	lm9033_WriteCMD(0x00); 
	
	lm9033_WriteCMD(0x89); 
	lm9033_WriteCMD(0x00); 
	
	lm9033_WriteCMD(0x8a); 
	lm9033_WriteCMD(0x88); 
	
	lm9033_WriteCMD(0x8b); 
	lm9033_WriteCMD(0x88); 
	
	lm9033_WriteCMD(0x8c); 
	lm9033_WriteCMD(0xbb); 
	

	lm9033_WriteCMD(0x8d); 
	lm9033_WriteCMD(0xbb); 

	lm9033_WriteCMD(0x8e); 
	lm9033_WriteCMD(0xee); 
	

	lm9033_WriteCMD(0x8f); 
	lm9033_WriteCMD(0xee); 
	
	lm9033_ClearScreen();	  

}

void lm9033_WriteASSIC(uchar X,uchar Y, uchar font, char *s){
unsigned char i;
unsigned char j=0;
switch(font)
{
	case font_6x8:
		while (*s!=0){
			lm9033_SetXY((X+(j*6)),Y);
			for (i=0; i<6; i++)
			{
				lm9033_WriteData(assic_6x8[(*s-32)  ][i]);
				lm9033_WriteData(assic_6x8[(*s-32)  ][i]);
			}
			
			s++;
			j++;
		}			
	break;
	case font_8x16:
	break;	
}
    
}
void lm9033_WriteNumber(uchar X,uchar Y,uchar font, uchar num){

	uchar i;
	switch(font)
	{
		case font_6x8: 
			lm9033_SetXY((X),Y);
			for (i=0; i<6; i++)
			{
				lm9033_WriteData(assic_6x8[num+16][i]);
				lm9033_WriteData(assic_6x8[num+16][i]);
			}		
		break;
		case font_8x16:
		break;
	}
} 


void lm9033_DisplayNumber(uchar x , uchar y, uchar font, uchar length, int num){
	uchar i;
	if(num<0)
	{
		num = (-num);
		for(i = 0; i < length ;i++ ){
			lm9033_WriteNumber((uchar)(x + 6 + ((length -1 - i) * (2*font+6))), y, font, (uchar)(num % 10));
			num = num / 10;
		}
		lm9033_WriteASSIC(x ,y,font_6x8, "-");
	}
	else
	{
		for(i = 0; i < length ;i++ ){
			lm9033_WriteNumber((uchar)(x + 6 + ((length -1 - i) * (2*font+6))), y, font, (uchar)(num % 10));
			num = num / 10;
		}
		lm9033_WriteASSIC(x ,y,font_6x8, " ");
	}
}
