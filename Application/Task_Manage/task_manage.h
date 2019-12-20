#ifndef TASK_MANAGE_CFG_H_
#define TASK_MANAGE_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include"config.h"
	//////////////////////////////////////////////////////////////////////////////////////
	
	//===定义结构体
	typedef struct _TASK_HandlerType				TASK_HandlerType;
	//===定义指针结构体
	typedef	struct _TASK_HandlerType				* pTASK_HandlerType;
	//===结构定义
	struct _TASK_HandlerType
	{
		UINT8_T msgTaskIndex;			//---任务索引号；0---空任务，1---非空任务
		UINT8_T (*msgTaskFunc)();		//---任务执行函数
	};

	//===定义执行的任务
	#define	TASK_MANAGE_NONE						0		//---空任务
	#define	TASK_MANAGE_ISP_USART					1		//---ISP编程，通讯方式串口
	#define	TASK_MANAGE_JTAG_USART					2		//---JTAG编程，通讯方式串口
	#define	TASK_MANAGE_HVPP_USART					3		//---HVPP编程，通讯方式串口
	#define	TASK_MANAGE_HVSP_USART					4		//---HVSP编程，通讯方式串口

	//===函数定义
	UINT8_T Task_Manage_Init();
	UINT8_T Task_Manage();

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*TASK_MANAGE_CFG_H_ */