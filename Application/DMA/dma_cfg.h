#ifndef DMA_CFG_H_
#define DMA_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////

	//===��������
	UINT8_T DMA_Clock(DMA_TypeDef* DMAx, UINT8_T isEnable);
	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DMA_CFG_H_ */