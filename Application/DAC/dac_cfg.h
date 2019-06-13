#ifndef DAC_CFG_H_
#define DAC_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "gpio_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===设置DC的参考电压
	#define DAC_REF_POWER_UV						3300000

	//===函数定义
	UINT8_T DAC_GPIO_Init(void);
	UINT8_T DAC_Clock(UINT8_T isEnableid);
	UINT8_T DAC_DAC1_Init(void);
	UINT8_T DAC_DAC2_Init(void);
	UINT8_T DAC_Init(void);
	UINT8_T DAC_DAC1_WriteVoltageUV(UINT32_T volUV);
	UINT8_T DAC_DAC1_WriteVoltageMV(UINT32_T volMV);
	UINT8_T DAC_DAC1_WriteVoltageV(float volV);
	UINT8_T DAC_DAC2_WriteVoltageUV(UINT32_T volUV);
	UINT8_T DAC_DAC2_WriteVoltageMV(UINT32_T volMV);
	UINT8_T DAC_DAC2_WriteVoltageV(float volV);
	UINT8_T DAC_DAC_WriteVoltageUV(UINT32_T volUV);
	UINT8_T DAC_DAC_WriteVoltageMV(UINT32_T volMV);
	UINT8_T DAC_DAC_WriteVoltageV(float volV);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DAC_CFG_H_ */