#ifndef BMP180_CFG_H_
#define BMP180_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include"complier_lib.h"
	#include "i2c_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===设备通讯地址
	#define BMP180_WADDR								0xEE															//---设备的写地址
	#define BMP180_RADDR								0xEF															//---设备的读地址
	//===BMP180校正参数
	typedef struct
	{
		INT16_T		msgAC1;
		INT16_T		msgAC2;
		INT16_T		msgAC3;
		UINT16_T	msgAC4;
		UINT16_T	msgAC5;
		UINT16_T	msgAC6;
		INT16_T		msgB1;
		INT16_T		msgB2;
		INT16_T		msgMB;
		INT16_T		msgMC;
		INT16_T		msgMD;
	}BMP180_ParamType;
	//===结构体定义
	typedef struct _BMP180_HandlerType					BMP180_HandlerType;
	//===指针结构体定义
	typedef struct _BMP180_HandlerType					*pBMP180_HandlerType;
	//===HMC5883的数据结构体
	struct _BMP180_HandlerType
	{
		BMP180_ParamType	msgParam;																					//---矫正参数
		INT32_T				msgDefaultTemp;																				//---未校正的温度值
		INT32_T				msgDefaultGasPress;																			//---未校正的气压值
		INT32_T				msgTempX100;																				//---校正后的温度值
		INT32_T				msgGasPress;																				//---校正后的气压值
		I2C_HandlerType		msgI2C;																						//---使用的I2C
		void(*msgDelayms)(UINT32_T delay);																				//---延时参数
	};

	//===定义的任务函数
	#define BMP180_TASK_ONE								pBmp180Device0													//---任务1
	#define BMP180_TASK_TWO								0																//---任务2
	#define BMP180_TASK_THREE							0																//---任务3

	//===外部调用
	extern BMP180_HandlerType							g_Bmp180Device0;
	extern pBMP180_HandlerType							pBmp180Device0;

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*BMP180_CFG_H_ */