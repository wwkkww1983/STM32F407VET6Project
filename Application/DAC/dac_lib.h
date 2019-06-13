#ifndef DAC_LIB_H_
#define DAC_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "dac_cfg.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===º¯Êý¶¨Òå
	UINT8_T DACLib_DAC1_Init(void);
	UINT8_T DACLib_DAC2_Init(void);
	UINT8_T DACLib_Init(void);
	UINT8_T DACLib_DAC1_WriteVoltageUV(UINT32_T volUV);
	UINT8_T DACLib_DAC1_WriteVoltageMV(UINT32_T volMV);
	UINT8_T DACLib_DAC1_WriteVoltageV(float volV);
	UINT8_T DACLib_DAC2_WriteVoltageUV(UINT32_T volUV);
	UINT8_T DACLib_DAC2_WriteVoltageMV(UINT32_T volMV);
	UINT8_T DACLib_DAC2_WriteVoltageV(float volV);
	UINT8_T DACLib_DAC_WriteVoltageUV(UINT32_T volUV);
	UINT8_T DACLib_DAC_WriteVoltageMV(UINT32_T volMV);
	UINT8_T DACLib_DAC_WriteVoltageV(float volV);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DAC_LIB_H_ */