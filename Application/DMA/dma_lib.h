#ifndef DMA_LIB_H_
#define DMA_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "dma_cfg.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===��������
	UINT8_T DMALib_Clock(DMA_TypeDef* DMAx, UINT8_T isEnable);
	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DMA_LIB_H_ */