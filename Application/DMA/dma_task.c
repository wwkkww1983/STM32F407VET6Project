#include "dma_task.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DMATask_Clock(DMA_TypeDef* DMAx, UINT8_T isEnable)
{
	return  DMALib_Clock(DMAx,isEnable);
}