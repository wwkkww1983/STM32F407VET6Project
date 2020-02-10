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
	//===�豸ͨѶ��ַ
	#define BMP180_WADDR								0xEE															//---�豸��д��ַ
	#define BMP180_RADDR								0xEF															//---�豸�Ķ���ַ
	//===BMP180У������
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
	//===�ṹ�嶨��
	typedef struct _BMP180_HandlerType					BMP180_HandlerType;
	//===ָ��ṹ�嶨��
	typedef struct _BMP180_HandlerType					*pBMP180_HandlerType;
	//===HMC5883�����ݽṹ��
	struct _BMP180_HandlerType
	{
		BMP180_ParamType	msgParam;																					//---��������
		INT32_T				msgDefaultTemp;																				//---δУ�����¶�ֵ
		INT32_T				msgDefaultGasPress;																			//---δУ������ѹֵ
		INT32_T				msgTempX100;																				//---У������¶�ֵ
		INT32_T				msgGasPress;																				//---У�������ѹֵ
		I2C_HandlerType		msgI2C;																						//---ʹ�õ�I2C
		void(*msgDelayms)(UINT32_T delay);																				//---��ʱ����
	};

	//===�����������
	#define BMP180_TASK_ONE								pBmp180Device0													//---����1
	#define BMP180_TASK_TWO								0																//---����2
	#define BMP180_TASK_THREE							0																//---����3

	//===�ⲿ����
	extern BMP180_HandlerType							g_Bmp180Device0;
	extern pBMP180_HandlerType							pBmp180Device0;

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*BMP180_CFG_H_ */