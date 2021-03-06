#ifndef POWER_LIB_H_
#define POWER_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "power_cfg.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===函数定义
	void PowerLib_Init(void);
	void PowerLib_DeInit(void);
	
	//===函数定义
	UINT8_T LM317Lib_Init(UINT8_T isPowerON, UINT32_T volMV);
	UINT8_T LM317Lib_DeInit(void);
	UINT8_T LM317Lib_PowerMV(UINT32_T volMV);
	UINT8_T LM317Lib_PowerV(float volV);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*POWER_LIB_H_ */