#ifndef TASK_MANAGE_CFG_H_
#define TASK_MANAGE_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include"config.h"
	//////////////////////////////////////////////////////////////////////////////////////
	
	//===����ṹ��
	typedef struct _TASK_HandlerType				TASK_HandlerType;
	//===����ָ��ṹ��
	typedef	struct _TASK_HandlerType				* pTASK_HandlerType;
	//===�ṹ����
	struct _TASK_HandlerType
	{
		UINT8_T msgTaskIndex;			//---���������ţ�0---������1---�ǿ�����
		UINT8_T (*msgTaskFunc)();		//---����ִ�к���
	};

	//===����ִ�е�����
	#define	TASK_MANAGE_NONE						0		//---������
	#define	TASK_MANAGE_ISP_USART					1		//---ISP��̣�ͨѶ��ʽ����
	#define	TASK_MANAGE_JTAG_USART					2		//---JTAG��̣�ͨѶ��ʽ����
	#define	TASK_MANAGE_HVPP_USART					3		//---HVPP��̣�ͨѶ��ʽ����
	#define	TASK_MANAGE_HVSP_USART					4		//---HVSP��̣�ͨѶ��ʽ����

	//===��������
	UINT8_T Task_Manage_Init();
	UINT8_T Task_Manage();

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*TASK_MANAGE_CFG_H_ */