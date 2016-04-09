#include "PowerManagement.h"


void PowerSwitch_SevroDirection(uchar s)
{	
	switch(s)
	{
		case power_on:
			PORT_PM |= PM_SevroDirection;
		break;
		default :
			PORT_PM &= ~PM_SevroDirection;
	}
}

void PowerSwitch_Camera(uchar s)
{
	switch(s)
	{
		case power_on:
			PORT_PM |= PM_Camera;
		break;
		default :
			PORT_PM &= ~PM_Camera;
	}		
}

