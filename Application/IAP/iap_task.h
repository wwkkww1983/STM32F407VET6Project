#ifndef IAP_TASK_H_
#define IAP_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include"iap_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===��������
	void IAPTask_ToAPP(UINT32_T appAddr);
	void IAPTask_ToIAP(UINT32_T iapAddr);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*IAP_TASK_H_ */