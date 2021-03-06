#ifndef TIMER_TASK_H_
#define TIMER_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "timer_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===��������
	void TimerTask_Init(void);
	void TimerTask_CalcFreq_Task(UINT8_T ch);
	float TimerTask_GetFreqKHz(void);
	float TimerTask_GetFreqMHz(void);
	UINT8_T TimerTask_Clock(TIM_TypeDef *TIMx, UINT8_T isEnable);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*TIMER_TASK_H_ */