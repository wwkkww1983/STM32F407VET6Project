#include "i2c_cfg.h"

//>>>===ģ��I2C����---��ʼ
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_Init(I2C_HandlerType *I2Cx, void(*pFuncDelayus)(UINT32_T delay))
{
	//---ʹ��GPIO��ʱ��
	GPIOTask_Clock(I2Cx->msgSCL.msgPort, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(I2Cx->msgSDA.msgPort, PERIPHERAL_CLOCK_ENABLE);
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---GPIO�ĳ�ʼ��
	//GPIO_InitStruct.Pin = I2Cx->msgSclBit;						//---��Ӧ��GPIO������
	GPIO_InitStruct.Pin = I2Cx->msgSCL.msgBit;					//---��Ӧ��GPIO������
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;				//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;					//---�˿ڸ���ģʽ
#endif
	//---SCL�ĳ�ʼ��
	LL_GPIO_Init(I2Cx->msgSCL.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---SDA�ĳ�ʼ��
	GPIO_InitStruct.Pin = I2Cx->msgSDA.msgBit;
	LL_GPIO_Init(I2Cx->msgSDA.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	//---ע����ʱ����
	if (pFuncDelayus != NULL)
	{
		I2Cx->msgDelayus = pFuncDelayus;
	}
	else
	{
		I2Cx->msgDelayus = DelayTask_us;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_DeInit(I2C_HandlerType *I2Cx)
{
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---GPIO�ĳ�ʼ��
	GPIO_InitStruct.Pin = I2Cx->msgSCL.msgBit;					//---��Ӧ��GPIO������
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;					//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
#endif
	//---SCL�ĳ�ʼ��
	LL_GPIO_Init(I2Cx->msgSCL.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---SDA�ĳ�ʼ��
	GPIO_InitStruct.Pin = I2Cx->msgSDA.msgBit;
	LL_GPIO_Init(I2Cx->msgSDA.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_START(I2C_HandlerType *I2Cx)
{
	//---������ʼ�����������ź�
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	if (I2Cx->msgPluseWidth>0)
	{
		I2Cx->msgDelayus(I2Cx->msgPluseWidth);
	}
	//---������ʼ�ź�;
	GPIO_OUT_0(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	if (I2Cx->msgPluseWidth>0)
	{
		I2Cx->msgDelayus(I2Cx->msgPluseWidth);
	}
	//---ǯסI2C���ߣ�׼�����ͻ��������
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---�ж�I2C�����ź��Ƿ�ɹ�����ȡSDA��״̬�źţ��ɹ�SDA---0��ʧ��SDA---1
	return  ((GPIO_GET_STATE(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit) != 0x00)?ERROR_1:OK_0);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_STOP(I2C_HandlerType *I2Cx)
{
	//---����ֹͣ�����������ź�
	GPIO_OUT_0(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	if (I2Cx->msgPluseWidth>0)
	{
		I2Cx->msgDelayus(I2Cx->msgPluseWidth);
	}
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	if (I2Cx->msgPluseWidth>0)
	{
		I2Cx->msgDelayus(I2Cx->msgPluseWidth);
	}
	//---�ж�I2C�����ź��Ƿ�ɹ�����ȡSDA��״̬�źţ��ɹ�SDA---1��ʧ��SDA---0
	return ((GPIO_GET_STATE(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit) == 0x00) ? ERROR_1 : OK_0);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ACK(I2C_HandlerType *I2Cx)
{
	GPIO_OUT_0(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	if (I2Cx->msgPluseWidth>0)
	{
		I2Cx->msgDelayus(I2Cx->msgPluseWidth);
	}
	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_NACK(I2C_HandlerType *I2Cx)
{
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	if (I2Cx->msgPluseWidth>0)
	{
		I2Cx->msgDelayus(I2Cx->msgPluseWidth);
	}
	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ReadACK(I2C_HandlerType *I2Cx)
{
	UINT8_T _return = OK_0;
	//---��ȡӦ���ź�
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---��ʱ�ȴ�
	if (I2Cx->msgPluseWidth>0)
	{
		I2Cx->msgDelayus(I2Cx->msgPluseWidth);
	}
	//---��ȡSDA��״̬�ź�---ACK״̬��SDAΪ�͵�ƽ
	_return= ((GPIO_GET_STATE(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit) != 0x00) ? ERROR_1 : OK_0);
	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_WaitACK(I2C_HandlerType *I2Cx)
{
	UINT8_T i = 0;
	//---��ȡӦ���ź�
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---�ȴ�Ӧ���ź�
	for (i = 255; i > 0; i--)
	{
		//---��ȡSDA��״̬
		if (GPIO_GET_STATE(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit))
		{
			break;
		}
	}
	if (i == 0)
	{
		I2C_MSW_STOP(I2Cx);
		return ERROR_1;
	}
	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_SendACK(I2C_HandlerType *I2Cx, UINT8_T isNACK)
{
	if (isNACK)
	{
		return I2C_MSW_NACK(I2Cx);
	}
	else
	{
		return I2C_MSW_ACK(I2Cx);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_SendBit(I2C_HandlerType *I2Cx, UINT8_T bitVal)
{
	((bitVal&0x80)!=0x00)? GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit): GPIO_OUT_0(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	//---һ��ʱ������
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);	
	I2Cx->msgDelayus(I2Cx->msgPluseWidth);
	DELAY_NOP_COUNT(2);
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);	
	I2Cx->msgDelayus(I2Cx->msgPluseWidth);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_SendByte(I2C_HandlerType *I2Cx, UINT8_T val)
{
	UINT8_T i = 0;
	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---����1�ֽڵ�����
	for (i = 0; i < 8; i++)
	{
		//---��ȡ1Bit������
		I2C_MSW_SendBit(I2Cx, val);
		val <<= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_SendBits(I2C_HandlerType *I2Cx, UINT8_T *pVal, UINT8_T bitNum)
{
	//---�����ֽڸ���
	UINT8_T byteCount = (bitNum / 8);
	//---����bit����
	UINT8_T bitCount = (bitNum % 8);
	UINT8_T i = 0;
	//---���������ֽڵĸ���
	for (i = 0; i < byteCount; i++)
	{
		I2C_MSW_SendByte(I2Cx, pVal[i]);
	}
	//---��������---���ݵķ��ͣ����ȷ��͸�λ
	pVal[byteCount] <<= (8 - bitCount);
	//---�жϷ��������ǲ��ǲ�����1�ֽ�
	if (byteCount == 0)
	{
		//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
		GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	}
	//---����ָ��������bit
	for (i = 0; i < bitCount; i++)
	{
		I2C_MSW_SendBit(I2Cx, pVal[byteCount]);
		pVal[byteCount] <<= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_SendWord(I2C_HandlerType *I2Cx, UINT16_T val)
{
	UINT8_T valH = (UINT8_T)(val >> 8);
	UINT8_T valL = (UINT8_T)(val);
	UINT8_T i = 0;
	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---����1�ֽڵ�����
	for (i = 0; i < 8; i++)
	{
		//---��ȡ1Bit������
		I2C_MSW_SendBit(I2Cx, valH);
		//---�������ƶ�
		valH <<= 1;
	}
	//---����1�ֽڵ�����
	for (i = 0; i < 8; i++)
	{
		//---��ȡ1Bit������
		I2C_MSW_SendBit(I2Cx, valL);
		//---��������
		valL <<= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ReadBit(I2C_HandlerType *I2Cx)
{
	UINT8_T _return = OK_0;
	//---ʱ��������
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	I2Cx->msgDelayus(I2Cx->msgPluseWidth);
	DELAY_NOP_COUNT(4);
	//---��ȡ����λ
	_return= ((GPIO_GET_STATE(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit) != 0x00) ? 1 : 0);
	//---ʱ�Ӹ�����
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	I2Cx->msgDelayus(I2Cx->msgPluseWidth);
	return  _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ReadByte(I2C_HandlerType *I2Cx)
{
	UINT8_T i = 0;
	UINT8_T _return = 0;
	//---׼�����ݵĶ�ȡ
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---����1�ֽڵ�����
	for (i = 0; i < 8; i++)
	{
		_return <<= 1;
		_return |= I2C_MSW_ReadBit(I2Cx);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ReadBits(I2C_HandlerType *I2Cx, UINT8_T *pVal, UINT8_T bitNum)
{
	//---��ȡ�ֽڸ���
	UINT8_T byteCount = (bitNum / 8);
	//---��ȡbit����
	UINT8_T bitCount = (bitNum % 8);
	UINT8_T i = 0;
	//---��ȡ�����ֽڵĸ���
	for (i = 0; i < byteCount; i++)
	{
		pVal[i] = I2C_MSW_ReadByte(I2Cx);
	}
	//---���㴦��
	pVal[byteCount] = 0x00;
	//---�ж϶�ȡ��Bit�����ǲ��ǲ�����1�ֽ�
	if (byteCount == 0)
	{
		//---׼�����ݵĶ�ȡ
		GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
		//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
		GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	}
	//---��ȡָ��������bit
	for (i = 0; i < bitCount; i++)
	{
		pVal[byteCount] <<= 1;
		pVal[byteCount] |= I2C_MSW_ReadBit(I2Cx);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_CheckDevice(I2C_HandlerType *I2Cx)
{
	UINT8_T _return = OK_0;
	if ((GPIO_GET_STATE(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit)) && (GPIO_GET_STATE(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit)))
	{
		//---���������ź�
		I2C_MSW_START(I2Cx);
		//---���Ͷ�ȡ��������
		I2Cx->msgAddr |= 0x01;
		//---���ʹӻ���ַ
		I2C_MSW_SendByte(I2Cx, (UINT8_T)I2Cx->msgAddr);
		//---��ȡӦ���ź�
		_return = I2C_MSW_ReadACK(I2Cx);
	}
	else
	{
		_return = ERROR_2;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_SendCMD(I2C_HandlerType *I2Cx, UINT8_T cmd, UINT8_T isStart, UINT8_T isStop)
{
	UINT8_T _return = OK_0;
	if (isStart)
	{
		//---�������������ź�
		_return = I2C_MSW_START(I2Cx);
		if (_return)
		{
			I2C_MSW_STOP(I2Cx);
			return ERROR_1;
		}
	}
	//---��������
	_return = I2C_MSW_SendByte(I2Cx, cmd);
	//---��ȡӦ��
	_return = I2C_MSW_ReadACK(I2Cx);
	//---ֹͣ����������
	if ((isStop) || (_return))
	{
		I2C_MSW_STOP(I2Cx);
	}
	return _return;
}
//////////////////////////////////////////////////////////////////////////////
//<<<===ģ��I2C����---����

//////////////////////////////////////////////////////////////////////////////
//>>>===Ӳ��I2C����---��ʼ


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ʹ��I2C������ʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_Clock(I2C_HandlerType* I2Cx, UINT8_T isEnable)
{
	if (I2Cx->msgI2Cx == I2C1)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I2C1);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C1);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C1);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
	else if (I2Cx->msgI2Cx == I2C2)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I2C2);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C2);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C2);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#ifdef I2C3
	else if (I2Cx->msgI2Cx == I2C3)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I2C3);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C3);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C3);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C3);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif
	else
	{
		return ERROR_2;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_Init(I2C_HandlerType* I2Cx)
{
	//---ʹ��GPIO��ʱ��
	GPIOTask_Clock(I2Cx->msgSCL.msgPort, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(I2Cx->msgSDA.msgPort, PERIPHERAL_CLOCK_ENABLE);
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---GPIO�ĳ�ʼ��
	//GPIO_InitStruct.Pin = I2Cx->msgSclBit;														//---��Ӧ��GPIO������
	GPIO_InitStruct.Pin = I2Cx->msgSCL.msgBit;														//---��Ӧ��GPIO������
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;													//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;												//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;											//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;															//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = I2Cx->msgGPIOAlternate;												//---�˿ڸ���ģʽ
#endif
	//---SCL�ĳ�ʼ��
	LL_GPIO_Init(I2Cx->msgSCL.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---SDA�ĳ�ʼ��
	GPIO_InitStruct.Pin = I2Cx->msgSDA.msgBit;
	LL_GPIO_Init(I2Cx->msgSDA.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);

	//---����I2C����ʱ��
	I2C_Clock(I2Cx, PERIPHERAL_CLOCK_ENABLE);
	//---��λI2C
	LL_I2C_DeInit(I2Cx->msgI2Cx);
	//---��ʼ��I2C
	LL_I2C_InitTypeDef I2C_InitStruct={0};
	I2C_InitStruct.PeripheralMode = LL_I2C_MODE_I2C;												//---����ģʽ
	I2C_InitStruct.ClockSpeed = 100000;																//---SCLʱ��Ƶ��
	I2C_InitStruct.DutyCycle = LL_I2C_DUTYCYCLE_2;													//---ʱ��ռ�ձ�
	I2C_InitStruct.OwnAddress1 = 0;																	//---�����I2C�豸��ַ
	I2C_InitStruct.TypeAcknowledge = LL_I2C_ACK;													//---ʹ�ܻ��߹ر���Ӧ(Ĭ��һ�㿪��)
	I2C_InitStruct.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;											//---ָ����ַ�ĳ��ȣ�7Bit����10BIt
	LL_I2C_Init(I2Cx->msgI2Cx, &I2C_InitStruct);
	//---�ڶ�����ַ
	LL_I2C_SetOwnAddress2(I2Cx->msgI2Cx, 0);
	//---ʹ��I2C
	LL_I2C_Enable(I2Cx->msgI2Cx);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����������ź�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_START(I2C_HandlerType* I2Cx)
{
	/* 1.��֤I2C���費��ʹ����. */
	while (LL_I2C_IsActiveFlag_BUSY(I2Cx->msgI2Cx))
	{
	}
	/* 2.����START�ź� */
	LL_I2C_GenerateStartCondition(I2Cx->msgI2Cx);
	while (!LL_I2C_IsActiveFlag_SB(I2Cx->msgI2Cx))
	{
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ֹͣ�ź�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_STOP(I2C_HandlerType* I2Cx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_SendByte(I2C_HandlerType* I2Cx, UINT8_T val)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_ReadByte(I2C_HandlerType* I2Cx)
{
	return OK_0;
}


void I2C_HW_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
	/* 1.��֤I2C���費��ʹ����. */
	while (LL_I2C_IsActiveFlag_BUSY(I2C1))
	{
	}
	/* 2.����START�ź� */
	LL_I2C_GenerateStartCondition(I2C1);
	while (!LL_I2C_IsActiveFlag_SB(I2C1))
	{
	}
	/* 2.д������ַ */
	LL_I2C_TransmitData8(I2C1, Addr);
	while (!LL_I2C_IsActiveFlag_ADDR(I2C1))
	{
	}
	LL_I2C_ClearFlag_ADDR(I2C1);
	/* 3.��ַλ�Ѿ���λ,ͨ��TXEҲ�����,Ϊ�˽���,�ٲ�һ��. */
	while (!LL_I2C_IsActiveFlag_TXE(I2C1))
	{
	}
	/* 4.���������Ĵ�����ַ. */
	LL_I2C_TransmitData8(I2C1, Reg);
	while (!LL_I2C_IsActiveFlag_TXE(I2C1))
	{
	}
	/* 5.д��Ĵ������� */
	LL_I2C_TransmitData8(I2C1, Value);
	while (!LL_I2C_IsActiveFlag_BTF(I2C1))
	{
	}
	/* 6.���ͽ�������. */
	LL_I2C_GenerateStopCondition(I2C1);
}
uint8_t I2C_HW_Read(uint8_t Addr, uint8_t Reg)
{
	uint8_t Value = 0x00;
	/* 1.��֤I2C���費��ʹ����. */
	while (LL_I2C_IsActiveFlag_BUSY(I2C1))
	{
	}
	/* 2.����START�ź� */
	LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);
	LL_I2C_GenerateStartCondition(I2C1);
	while (!LL_I2C_IsActiveFlag_SB(I2C1))
	{
	}
	/* 2.д������ַ */
	LL_I2C_TransmitData8(I2C1, Addr);
	while (!LL_I2C_IsActiveFlag_ADDR(I2C1))
	{
	}
	LL_I2C_ClearFlag_ADDR(I2C1);
	/* 3.��ַλ�Ѿ���λ,ͨ��TXEҲ�����,Ϊ�˽���,�ٲ�һ��. */
	while (!LL_I2C_IsActiveFlag_TXE(I2C1))
	{
	}
	/* 4.���������Ĵ�����ַ. */
	LL_I2C_TransmitData8(I2C1, Reg);
	while (!LL_I2C_IsActiveFlag_TXE(I2C1))
	{
	}
	/* 5.�ṩRESTART�ź�. */
	LL_I2C_GenerateStopCondition(I2C1);
	LL_I2C_GenerateStartCondition(I2C1);
	while (!LL_I2C_IsActiveFlag_SB(I2C1))
	{
	}
	/* 6.���·��͵�ַ,�����������. */
	LL_I2C_TransmitData8(I2C1, Addr | 0x01);
	while (!LL_I2C_IsActiveFlag_ADDR(I2C1))
	{
	}
	/* 7.��Ƕ����STOP. */
	LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_NACK);
	LL_I2C_ClearFlag_ADDR(I2C1);
	LL_I2C_GenerateStopCondition(I2C1);
	while (!LL_I2C_IsActiveFlag_RXNE(I2C1))
	{
	}
	/* 8.�����Ѷ�ȡ. */
	Value = LL_I2C_ReceiveData8(I2C1);
	return Value;
}

//////////////////////////////////////////////////////////////////////////////
//<<<===Ӳ��I2C����---����