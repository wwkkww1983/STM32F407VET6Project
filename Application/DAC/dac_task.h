#ifndef DAC_TASK_H_
#define DAC_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "dac_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===º¯Êý¶¨Òå
	UINT8_T DACTask_DAC1_Init(void);
	UINT8_T DACTask_DAC2_Init(void);
	UINT8_T DACTask_Init(void);
	UINT8_T DACTask_DAC1_WriteVoltageUV(UINT32_T volUV);
	UINT8_T DACTask_DAC1_WriteVoltageMV(UINT32_T volMV);
	UINT8_T DACTask_DAC1_WriteVoltageV(float volV);
	UINT8_T DACTask_DAC2_WriteVoltageUV(UINT32_T volUV);
	UINT8_T DACTask_DAC2_WriteVoltageMV(UINT32_T volMV);
	UINT8_T DACTask_DAC2_WriteVoltageV(float volV);
	UINT8_T DACTask_DAC_WriteVoltageUV(UINT32_T volUV);
	UINT8_T DACTask_DAC_WriteVoltageMV(UINT32_T volMV);
	UINT8_T DACTask_DAC_WriteVoltageV(float volV);
	
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DAC_TASK_H_ */