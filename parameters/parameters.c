#include "parameters.h"

#define BufferChar(address, data)	\
	microSD_fifoData[address] = data

#define BufferInt(address, data)	\
	microSD_fifoData[address] = (uchar)data;\
	microSD_fifoData[address + 1] = (uchar)(data >> 8)

#define BufferLong(address, data)	\
	microSD_fifoData[address] = (uchar)data;\
	microSD_fifoData[address + 1] = (uchar)(data >> 8);\
	microSD_fifoData[address + 2] = (uchar)(data >> 16);\
	microSD_fifoData[address + 3] = (uchar)(data >> 24)

#define RestoreChar(address, parameter)	\
	parameter = microSD_fifoData[address]

#define RestoreInt(address, parameter)	\
	parameter =  (int)microSD_fifoData[address];\
	parameter += (((int)microSD_fifoData[address+1]) << 8)

#define RestoreLong(address, parameter)	\
	parameter =  (long)microSD_fifoData[address];\
	parameter += (((long)microSD_fifoData[address+1]) << 8);\
	parameter += (((long)microSD_fifoData[address+2]) << 16);\
	parameter += (((long)microSD_fifoData[address+3]) << 24)


void WritePublicParametersToSD()
{
	BufferInt(address_baseSpeed, D_baseSpeed);
	BufferInt(address_thresholdEdge, thresholdEdge);

	BufferInt(address_P_PID, P_PID);
	BufferInt(address_D_maxPower, D_maxPower);
	BufferInt(address_D_minPower, D_minPower);
	BufferInt(address_minCutveSpeedRate, minCutveSpeedRate);
	
	
	BufferInt(address_P1, P1);
	BufferInt(address_P2, P2);
	BufferInt(address_P3, P3);
	BufferInt(address_P4, P4);
	BufferInt(address_P5, P5);
	BufferInt(address_P6, P6);
	BufferInt(address_P7, P7);
	BufferInt(address_P8, P8);
	BufferInt(address_P9, P9);
	BufferInt(address_P10, P10);
	
	microSD_WriteSector(microSD_address_Parameters);
}
	


void GetPublicParametersFromSD()
{
	microSD_ReadSector(microSD_address_Parameters);
	
	RestoreInt(address_baseSpeed,D_baseSpeed);
	RestoreInt(address_thresholdEdge,thresholdEdge);
	RestoreInt(address_P_PID, P_PID);
	RestoreInt(address_D_maxPower, D_maxPower);
	
	RestoreInt(address_D_minPower, D_minPower);
	RestoreInt(address_minCutveSpeedRate, minCutveSpeedRate);
	
	RestoreInt(address_P1, P1);
	RestoreInt(address_P2, P2);
	RestoreInt(address_P3, P3);
	RestoreInt(address_P4, P4);
	RestoreInt(address_P5, P5);
	RestoreInt(address_P6, P6);
	RestoreInt(address_P7, P7);
	RestoreInt(address_P8, P8);
	RestoreInt(address_P9, P9);
	RestoreInt(address_P10, P10);
	
	
	
	
}

void InitPublicParametersToSD()
{
	BufferInt(address_baseSpeed, initValue_baseSpeed);
	BufferInt(address_thresholdEdge, initValue_thresholdEdge);
	microSD_WriteSector(microSD_address_Parameters);
}
