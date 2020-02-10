#include "bmp180_cfg.h"

//===ȫ�ֱ�������
BMP180_HandlerType		g_Bmp180Device0 = { 0 };
pBMP180_HandlerType		pBmp180Device0 = &g_Bmp180Device0;


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_Device0_Init(BMP180_HandlerType* BMP180x)
{
	BMP180x->msgI2C.msgI2Cx = NULL;
	BMP180x->msgI2C.msgSCL.msgPort = GPIOB;
	BMP180x->msgI2C.msgSCL.msgBit = LL_GPIO_PIN_6;
	BMP180x->msgI2C.msgSDA.msgPort = GPIOB;
	BMP180x->msgI2C.msgSDA.msgBit = LL_GPIO_PIN_7;
	BMP180x->msgI2C.msgHwMode = 0;
	BMP180x->msgI2C.msgPluseWidth = 0;
	BMP180x->msgI2C.msgDelayus = NULL;
	BMP180x->msgI2C.msgAddr = BMP180_WADDR;
	BMP180x->msgI2C.msgClockSpeed = 100000;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_Device1_Init(BMP180_HandlerType* BMP180x)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_Device2_Init(BMP180_HandlerType* BMP180x)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ���ʼ��
//////�������:isHWI2C---1 Ӳ����0 ���
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_Init(BMP180_HandlerType* BMP180x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;
	//---ָ���豸�ĳ�ʼ��
	if ((BMP180x != NULL) && (BMP180x == BMP180_TASK_ONE))
	{
		BMP180_I2C_Device0_Init(BMP180x);
	}
	else if ((BMP180x != NULL) && (BMP180x == BMP180_TASK_TWO))
	{
		BMP180_I2C_Device1_Init(BMP180x);
	}
	else if ((BMP180x != NULL) && (BMP180x == BMP180_TASK_THREE))
	{
		BMP180_I2C_Device2_Init(BMP180x);
	}
	else
	{
		return ERROR_1;
	}
	//---�ж���Ӳ��I2C�������I2C
	if (isHWI2C)
	{
		//---��ʼ��Ӳ��I2C
		_return = I2CTask_MHW_Init(&(BMP180x->msgI2C), pFuncTimerTick);
		//---����ΪӲ��ģʽ
		BMP180x->msgI2C.msgHwMode = 1;
	}
	else
	{
		//---��ʼ�����ģ��I2C
		_return = I2CTask_MSW_Init(&(BMP180x->msgI2C), pFuncDelayus, pFuncTimerTick);
		//---����Ϊ�����ģʽ
		BMP180x->msgI2C.msgHwMode = 0;
	}
	//---ms��ʱ����
	BMP180x->msgDelayms = ((pFuncDelayms != NULL) ? pFuncDelayms : DelayTask_ms);
	//---���ó�ʼ��
	return _return;
}