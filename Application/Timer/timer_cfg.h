#ifndef TIMER_CFG_H_
#define TIMER_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "gpio_task.h"
	#include "systick_task.h"
	#include "hw_cfg.h"

	//===����ʹ�õ��ⲿ����ģʽ��ͨ����
	#define	CALC_FREQ_EXTERN_COUNT_MODE_CHANNEL_NUM			2
	//===�ṹ�嶨��
	typedef struct _CalcFreq_HandlerType					CalcFreq_HandlerType;
	//===ָ��ṹ�嶨��
	typedef struct _CalcFreq_HandlerType					*pCalcFreq_HandlerType;
	//===����Ƶ�ʵ����ݽṹ��
	struct  _CalcFreq_HandlerType
	{
		VLTUINT8_T  msgChannel;																																						//---����ͨ��
		VLTUINT8_T  msgStep[CALC_FREQ_EXTERN_COUNT_MODE_CHANNEL_NUM];																												//---��������
		float		msgFreqMHz[CALC_FREQ_EXTERN_COUNT_MODE_CHANNEL_NUM];																											//---MHzƵ��
		float		msgFreqKHz[CALC_FREQ_EXTERN_COUNT_MODE_CHANNEL_NUM];																											//---KHzƵ��
		#ifdef CALC_FREQ_USE_lEVEL_SHIFT
			GPIO_HandlerType	msgOE[CALC_FREQ_EXTERN_COUNT_MODE_CHANNEL_NUM];																										//---OE���ƶ˿�
		#endif
	};

	//===�ⲿ���ýӿ�
	extern CalcFreq_HandlerType 	g_CalcFreq;
	extern pCalcFreq_HandlerType 	pCalcFreq;

	//===��������
	void Timer_CalcFreqMode_DeInit(void);
	void Timer_CalcFreq_Task(UINT8_T ch);
	float Timer_GetFreqKHz(void);
	float Timer_GetFreqMHz(void);
	void Timer_Init(void);
	UINT8_T Timer_Clock(TIM_TypeDef *TIMx, UINT8_T isEnable);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*TIMER_CFG_H_ */
