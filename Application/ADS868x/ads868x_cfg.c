#include "ADS868X_cfg.h"

//===ȫ�ֱ�������
ADS868X_HandlerType   g_ADS868XDevice0 = { 0 };
pADS868X_HandlerType  pADS868XDevice0 = &g_ADS868XDevice0;

//===ͳһ�����ֽ�����
UINT8_T(*ADS868X_SPI_SEND_CMD)(ADS868X_HandlerType *, UINT8_T, UINT8_T *);
//===ͳһ������������
UINT8_T(*ADS868X_SPI_SEND_ARRAY)(ADS868X_HandlerType*, UINT8_T*, UINT8_T*,UINT16_T);

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void ADS868X_SPI_Device0_Init(ADS868X_HandlerType *ADS868xx)
{

	//---��λ�ź�
	ADS868xx->msgHWRST.msgGPIOPort = NULL;
	ADS868xx->msgHWRST.msgGPIOBit = LL_GPIO_PIN_0;

	//---GPIOʱ��ʹ��
	if (ADS868xx->msgHWRST.msgGPIOPort != NULL)
	{
		GPIOTask_Clock(ADS868xx->msgHWRST.msgGPIOPort, 1);
	}

	//---CS
	ADS868xx->msgSPI.msgCS.msgGPIOPort = GPIOA;
	ADS868xx->msgSPI.msgCS.msgGPIOBit = LL_GPIO_PIN_4;

	//---SCK
	ADS868xx->msgSPI.msgSCK.msgGPIOPort = GPIOA;
	ADS868xx->msgSPI.msgSCK.msgGPIOBit = LL_GPIO_PIN_5;

	//---MISO  SD0
	ADS868xx->msgSPI.msgMISO.msgGPIOPort = GPIOA;
	ADS868xx->msgSPI.msgMISO.msgGPIOBit = LL_GPIO_PIN_6;

	//---MOSI SDI
	ADS868xx->msgSPI.msgMOSI.msgGPIOPort = GPIOA;
	ADS868xx->msgSPI.msgMOSI.msgGPIOBit = LL_GPIO_PIN_7;

	//---GPIO������
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---GPIO�ĳ�ʼ��
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;					//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;		//---GPIO���ٶ�
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;		//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;						//---����ʹ��

	//---��ʼ��RST
	if (ADS868xx->msgHWRST.msgGPIOPort != NULL)
	{
		GPIO_InitStruct.Pin = ADS868xx->msgHWRST.msgGPIOBit;
		GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
		LL_GPIO_Init(ADS868xx->msgHWRST.msgGPIOPort, &GPIO_InitStruct);
		GPIO_OUT_1(ADS868xx->msgHWRST.msgGPIOPort, ADS868xx->msgHWRST.msgGPIOBit);
	}

	//---����ģʽ
	#ifndef USE_MCU_STM32F1
		//---�˿ڸ���ģʽ
		ADS868xx->msgSPI.msgGPIOAlternate = LL_GPIO_AF_5;
	#endif
	//---SPI���
	ADS868xx->msgSPI.msgSPIx = SPI1;
	#ifndef USE_MCU_STM32F1
		//---SPI��Э��
		ADS868xx->msgSPI.msgStandard = LL_SPI_PROTOCOL_MOTOROLA;
	#endif

	UINT8_T i = 0;
	//---�ο���ѹ����
	ADS868xx->msgREFPowerUV = ADS868X_REF_POWER_UV;
	for (i = 0; i < ADS868X_CHANNEL_MAX; i++)
	{
		ADS868xx->msgChannelRange[i] = 0;
		ADS868xx->msgIsPositive[i] = 0;
		ADS868xx->msgChannelNowADCResult[i] = 0;
		ADS868xx->msgChannelOldADCResult[i] = 0;
		ADS868xx->msgChannelPowerResult[i] = 0;
		ADS868X_SPI_ChannelRange(ADS868xx, i);
	}
	ADS868xx->msgDeviceReady = 0;
	ADS868xx->msgInitRetryCount = 3;
	ADS868xx->msgChipID = 0;
	//---Ĭ����������
	ADS868xx->msgFeature = 0x28;
	//---Ĭ����0xFF
	ADS868xx->msgAutoSeqEn = 0xFF;
	//---����������
	ADS868xx->msgSPI.msgPluseWidth = 2;
	//---ʱ�ӿ���Ϊ�͵�ƽ
	ADS868xx->msgSPI.msgCPOL = 0;
	//---���ݲ����ڵڶ���ʱ�ӱ���
	ADS868xx->msgSPI.msgCPOH = 1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void ADS868X_SPI_Device1_Init(ADS868X_HandlerType *ADS868xx)
{
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void ADS868X_SPI_Device2_Init(ADS868X_HandlerType *ADS868xx)
{
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_HW_Init(ADS868X_HandlerType *ADS868xx)
{
	//---ע����ǰ����������
	SPITask_DeInit(&(ADS868xx->msgSPI));
	//---Ӳ���˿ڵ�����---Ӳ��ʵ��
	SPITask_MHW_GPIO_Init(&(ADS868xx->msgSPI));
	//---Ӳ��SPI�ĳ�ʼ��
	LL_SPI_InitTypeDef SPI_InitStruct = {0};
	//---SPI��ģʽ����
	SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
	SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;						//---����ģʽ
	SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;				//---8λ����
	//---ʱ�Ӽ��Ե�����
	if (ADS868xx->msgSPI.msgCPOL == 0)
	{
		//---CLK����ʱΪ�͵�ƽ (CLK������ֻ���ǵ͵�ƽ)
		SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
		GPIO_OUT_0(ADS868xx->msgSPI.msgSCK.msgGPIOPort, ADS868xx->msgSPI.msgSCK.msgGPIOBit);
	}
	else
	{
		//---CLK����ʱΪ�ߵ�ƽ (CLK������ֻ���ǵ͵�ƽ)
		SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_HIGH;
	}
	//---���ݲ�����ʱ�ӱ���λ��
	if (ADS868xx->msgSPI.msgCPOH ==0)
	{
		SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
	}
	else
	{
		SPI_InitStruct.ClockPhase = LL_SPI_PHASE_2EDGE;
	}
	SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;							//---�������
	SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV2;		//---ϵͳʱ��4��Ƶ
	SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;						//---��λ��ǰ
	SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;	//---Ӳ��CRC��ʹ��
	SPI_InitStruct.CRCPoly = 7;
	//---��ʼ����ѯ��ʽ��SPI
	SPITask_MHW_PollMode_Init(&(ADS868xx->msgSPI), SPI_InitStruct);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_SW_Init(ADS868X_HandlerType *ADS868xx)
{
	SPITask_DeInit(&(ADS868xx->msgSPI));

	//---Ӳ���˿ڵ�����---���ʵ��
	SPITask_MSW_GPIO_Init(&(ADS868xx->msgSPI));

	//---ʱ���ߵļ���
	if (ADS868xx->msgSPI.msgCPOL == 0)
	{
		GPIO_OUT_0(ADS868xx->msgSPI.msgSCK.msgGPIOPort, ADS868xx->msgSPI.msgSCK.msgGPIOBit);
	}
	else
	{
		GPIO_OUT_1(ADS868xx->msgSPI.msgSCK.msgGPIOPort, ADS868xx->msgSPI.msgSCK.msgGPIOBit);
	}

	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ֽ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_SW_SendCmd(ADS868X_HandlerType *ADS868xx, UINT8_T cmd, UINT8_T *pRVal)
{
	//---���ݷ���
	return SPITask_MSW_WriteAndReadByteMSB(&(ADS868xx->msgSPI), cmd, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������������
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_SW_SendArray(ADS868X_HandlerType* ADS868xx, UINT8_T* pWVal, UINT8_T* pRVal, UINT16_T length)
{
	//---���ݷ���
	return SPITask_MSW_WriteAndReadDataMSB(&(ADS868xx->msgSPI), pWVal, pRVal, length);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ֽ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_HW_SendCmd(ADS868X_HandlerType *ADS868xx, UINT8_T cmd, UINT8_T *pRVal)
{
	//---���ݷ���
	return SPITask_MHW_PollMode_WriteAndReadByte(&(ADS868xx->msgSPI), cmd, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������������
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_HW_SendArray(ADS868X_HandlerType* ADS868xx, UINT8_T *pWVal, UINT8_T* pRVal,UINT16_T length)
{
	//---���ݷ���
	return SPITask_MHW_PollMode_WriteAndReadData(&(ADS868xx->msgSPI), pWVal, pRVal,length);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_Init(ADS868X_HandlerType *ADS868xx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHW)
{
	//---ʹ�õ�DHT11�Ķ˿�
	if ((ADS868xx != NULL) && (ADS868xx == ADS868X_TASK_ONE))
	{
		ADS868X_SPI_Device0_Init(ADS868xx);
	}
	else if ((ADS868xx != NULL) && (ADS868xx == ADS868X_TASK_TWO))
	{
		ADS868X_SPI_Device1_Init(ADS868xx);
	}
	else if ((ADS868xx != NULL) && (ADS868xx == ADS868X_TASK_THREE))
	{
		ADS868X_SPI_Device2_Init(ADS868xx);
	}
	else
	{
		return ERROR_1;
	}

	//---�жϳ�ʼ���ķ�ʽ
	if (isHW != 0)
	{
		ADS868xx->msgSPI.msgModelIsHW = 1;
		ADS868X_SPI_HW_Init(ADS868xx);
		ADS868X_SPI_SEND_CMD = ADS868X_SPI_HW_SendCmd;
		ADS868X_SPI_SEND_ARRAY = ADS868X_SPI_HW_SendArray;
	}
	else
	{
		ADS868xx->msgSPI.msgModelIsHW = 0;
		ADS868X_SPI_SW_Init(ADS868xx);
		ADS868X_SPI_SEND_CMD = ADS868X_SPI_SW_SendCmd;
		ADS868X_SPI_SEND_ARRAY = ADS868X_SPI_SW_SendArray;
	}

	//---ע��ms��ʱʱ��
	if (pFuncDelayms != NULL)
	{
		ADS868xx->msgFuncDelayms = pFuncDelayms;
	}
	else
	{
		ADS868xx->msgFuncDelayms = DelayTask_ms;
	}

	//---ע��us��ʱ����
	if (pFuncDelayus != NULL)
	{
		ADS868xx->msgSPI.msgFuncDelayus = pFuncDelayus;
	}
	else
	{
		ADS868xx->msgSPI.msgFuncDelayus = DelayTask_us;
	}

	//---ע��δ���
	ADS868xx->msgSPI.msgFuncTimeTick = pFuncTimerTick;

	//---����ADS868X
	return ADS868X_SPI_ConfigInit(ADS868xx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�дADS868X����Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteCommandReg(ADS868X_HandlerType *ADS868xx, UINT32_T cmd)
{
	UINT8_T _return = OK_0;
	UINT8_T wTemp[2] = { 0 };
	wTemp[0] = (UINT8_T)((cmd >> 8)&0xFF);
	wTemp[1] = (UINT8_T)(cmd & 0xFF);
	if (ADS868xx->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_0(ADS868xx->msgSPI.msgCS.msgGPIOPort, ADS868xx->msgSPI.msgCS.msgGPIOBit);
	}
	_return = ADS868X_SPI_SEND_ARRAY(ADS868xx, wTemp, NULL, 2);
	if (ADS868xx->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_1(ADS868xx->msgSPI.msgCS.msgGPIOPort, ADS868xx->msgSPI.msgCS.msgGPIOBit);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�Program Registerд����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteProgramReg(ADS868X_HandlerType *ADS868xx, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	UINT8_T wTemp[2] = { 0 };
	wTemp[0] = (addr << 1) | 0x01;
	wTemp[1] = val;
	if (ADS868xx->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_0(ADS868xx->msgSPI.msgCS.msgGPIOPort, ADS868xx->msgSPI.msgCS.msgGPIOBit);
	}
	_return = ADS868X_SPI_SEND_ARRAY(ADS868xx, wTemp, NULL, 2);
	if (ADS868xx->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_1(ADS868xx->msgSPI.msgCS.msgGPIOPort, ADS868xx->msgSPI.msgCS.msgGPIOBit);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�Program Register������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ReadProgramReg(ADS868X_HandlerType *ADS868xx, UINT8_T addr, UINT8_T *pVal)
{
	UINT8_T _return = OK_0;
	UINT8_T wTemp[3] = { 0 };
	UINT8_T rTemp[3] = { 0 };
	wTemp[0] = (addr << 1) & 0xFE;
	if (ADS868xx->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_0(ADS868xx->msgSPI.msgCS.msgGPIOPort, ADS868xx->msgSPI.msgCS.msgGPIOBit);
	}
	_return = ADS868X_SPI_SEND_ARRAY(ADS868xx, wTemp, rTemp, 3);
	if (ADS868xx->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_1(ADS868xx->msgSPI.msgCS.msgGPIOPort, ADS868xx->msgSPI.msgCS.msgGPIOBit);
	}

	//---���ݿ���
	pVal[0] = rTemp[1];
	pVal[1] = rTemp[2];

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ReadCommandBack(ADS868X_HandlerType* ADS868xx, UINT8_T* pVal)
{
	return ADS868X_SPI_ReadProgramReg(ADS868xx, ADS868X_CMD_READ_BACK, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�����������ѡ�е�״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_NO_OP(ADS868X_HandlerType* ADS868xx)
{
	return ADS868X_SPI_WriteCommandReg(ADS868xx, ADS868X_CMD_REG_NO_OP);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_STDBY(ADS868X_HandlerType* ADS868xx)
{
	return ADS868X_SPI_WriteCommandReg(ADS868xx, ADS868X_CMD_REG_STDBY);
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�
//////�������:
//////�������:
//////˵		�����˳���ģʽ��ִ��AUTO_RST����MAN_CH_n�������Ҫ�ȴ�����20us�Ա�֤�������ݵ�ADת��
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_PWRDN(ADS868X_HandlerType* ADS868xx)
{
	return ADS868X_SPI_WriteCommandReg(ADS868xx, ADS868X_CMD_REG_PWR_DN);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�Ӳ����λ�豸
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  ADS868X_SPI_HardReset(ADS868X_HandlerType *ADS868xx)
{
	if (ADS868xx->msgHWRST.msgGPIOPort!=NULL)
	{
		GPIO_OUT_0(ADS868xx->msgHWRST.msgGPIOPort, ADS868xx->msgHWRST.msgGPIOBit);
		ADS868xx->msgFuncDelayms(1);
		GPIO_OUT_1(ADS868xx->msgHWRST.msgGPIOPort, ADS868xx->msgHWRST.msgGPIOBit);
		ADS868xx->msgFuncDelayms(1);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������λ�豸
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  ADS868X_SPI_SoftReset(ADS868X_HandlerType *ADS868xx)
{
	return ADS868X_SPI_WriteCommandReg(ADS868xx, ADS868X_CMD_REG_RST);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ��豸��λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_Reset(ADS868X_HandlerType* ADS868xx)
{
	UINT8_T _return = OK_0;
	if (ADS868xx->msgHWRST.msgGPIOPort != NULL)
	{
		_return = ADS868X_SPI_HardReset(ADS868xx);
	}
	else
	{
		_return = ADS868X_SPI_SoftReset(ADS868xx);
	}
	ADS868xx->msgDeviceReady = 0;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������Զ�ɨ��ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_AUTORST(ADS868X_HandlerType* ADS868xx)
{
	return ADS868X_SPI_WriteCommandReg(ADS868xx, ADS868X_CMD_REG_AUTO_RST);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ������ֶ�ɨ��ͨ��
//////�������:
//////�������:
//////˵		�����˳���ģʽ��ִ��AUTO_RST����MAN_CH_n�������Ҫ�ȴ�����20us�Ա�֤�������ݵ�ADת��
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ManualChannel(ADS868X_HandlerType* ADS868xx,UINT16_T manualCHCmd)
{
	return ADS868X_SPI_WriteCommandReg(ADS868xx, manualCHCmd);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ������豸ID
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteChipID(ADS868X_HandlerType* ADS868xx, UINT8_T devid)
{
	devid <<= 6;
	ADS868xx->msgChipID = (devid & 0xC0) | ADS868xx->msgFeature;
	return ADS868X_SPI_WriteProgramReg(ADS868xx, ADS868X_PROG_REG_FEATURE_SELECT, ADS868xx->msgChipID);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ���ȡ�豸ID
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ReadChipID(ADS868X_HandlerType* ADS868xx, UINT8_T *pDevID)
{
	UINT8_T _return= ADS868X_SPI_ReadProgramReg(ADS868xx, ADS868X_PROG_REG_FEATURE_SELECT, pDevID);
	*pDevID &= 0xC0;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�У���豸ID
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_CheckChipID(ADS868X_HandlerType* ADS868xx)
{
	UINT8_T tempChipID = 0x00;
	UINT8_T _return = OK_0;
	_return = ADS868X_SPI_ReadChipID(ADS868xx, &tempChipID);
	//---У���ȡ��ID��Ϣ
	if (tempChipID!=ADS868xx->msgChipID)
	{
		_return += ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�̽���豸�Ƿ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_DetectionDevice(ADS868X_HandlerType* ADS868xx)
{
	UINT8_T tempAutoSeqEn[2] = { 0 };
	UINT8_T _return = OK_0;
	_return=ADS868X_SPI_ReadProgramReg(pADS868XDevice0, ADS868X_PROG_REG_AUTO_SEQ_EN, tempAutoSeqEn);
	//---У�����Ƿ���ȷ
	if (tempAutoSeqEn[1]!=ADS868xx->msgAutoSeqEn)
	{
		_return += ERROR_1;
	}
	else
	{
		//---У���豸��ID��Ϣ
		_return = ADS868X_SPI_CheckChipID(ADS868xx);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������Զ�ɨ������ͨ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteAUTOSEQEN(ADS868X_HandlerType* ADS868xx, UINT8_T seq)
{
	ADS868xx->msgAutoSeqEn = seq;
	return ADS868X_SPI_WriteProgramReg(ADS868xx, ADS868X_PROG_REG_AUTO_SEQ_EN, seq);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�Զ�ɨ������ͨ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ReadAUTOSEQEN(ADS868X_HandlerType* ADS868xx, UINT8_T *pAutoSeqEn)
{
	UINT8_T tempAutoSeqEn[2] = { 0 };
	UINT8_T _return= ADS868X_SPI_ReadProgramReg(ADS868xx, ADS868X_PROG_REG_AUTO_SEQ_EN, tempAutoSeqEn);
	if (_return==OK_0)
	{
		if (tempAutoSeqEn[1]==ADS868xx->msgAutoSeqEn)
		{
			*pAutoSeqEn = tempAutoSeqEn[1];
		}
		else
		{
			_return = ERROR_2;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ������ģʽ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteChannelPWRDN(ADS868X_HandlerType* ADS868xx, UINT8_T ch)
{
	ADS868xx->msgChannelPWRDN = ch;
	return ADS868X_SPI_WriteProgramReg(ADS868xx, ADS868X_PROG_REG_CH_PWR_DN, ch);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ������ģʽ��ȡ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ReadChannelPWRDN(ADS868X_HandlerType* ADS868xx, UINT8_T *pPWRDN)
{
	UINT8_T tempPWRDN[2] = { 0 };
	UINT8_T _return = ADS868X_SPI_ReadProgramReg(ADS868xx, ADS868X_PROG_REG_CH_PWR_DN, tempPWRDN);
	if (_return == OK_0)
	{
		if (tempPWRDN[1] == ADS868xx->msgChannelPWRDN)
		{
			*pPWRDN = tempPWRDN[1];
		}
		else
		{
			_return = ERROR_2;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ������ģʽ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteFeature(ADS868X_HandlerType* ADS868xx, UINT8_T feature)
{
	ADS868xx->msgFeature = (feature&0x3F)|ADS868xx->msgChipID;
	return ADS868X_SPI_WriteProgramReg(ADS868xx, ADS868X_PROG_REG_FEATURE_SELECT, feature);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ������ģʽ��ȡ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ReadFeature(ADS868X_HandlerType* ADS868xx, UINT8_T *pFeature)
{
	UINT8_T tempFeature[2] = { 0 };
	UINT8_T _return = ADS868X_SPI_ReadProgramReg(ADS868xx, ADS868X_PROG_REG_FEATURE_SELECT, tempFeature);
	if (_return == OK_0)
	{
		if (tempFeature[1] == ADS868xx->msgFeature)
		{
			*pFeature = tempFeature[1];
		}
		else
		{
			_return = ERROR_2;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ͨ�������̷�Χ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteChannelRange(ADS868X_HandlerType* ADS868xx, UINT8_T chReg, UINT8_T range)
{
	UINT8_T ch = ADS868X_CHANNEL_MAX;
	switch (chReg)
	{
		case ADS868X_PROG_REG_CH0_SET_RANGE:
			ADS868xx->msgChannelRange[0] = range;
			ch = 0;
			break;
		case ADS868X_PROG_REG_CH1_SET_RANGE:
			ADS868xx->msgChannelRange[1] = range;
			ch = 1;
			break;
		case ADS868X_PROG_REG_CH2_SET_RANGE:
			ADS868xx->msgChannelRange[2] = range;
			ch = 2;
			break;
		case ADS868X_PROG_REG_CH3_SET_RANGE:
			ADS868xx->msgChannelRange[3] = range;
			ch = 3;
			break;
		case ADS868X_PROG_REG_CH4_SET_RANGE:
			ADS868xx->msgChannelRange[4] = range;
			ch = 4;
			break;
		case ADS868X_PROG_REG_CH5_SET_RANGE:
			ADS868xx->msgChannelRange[5] = range;
			ch = 5;
			break;
		case ADS868X_PROG_REG_CH6_SET_RANGE:
			ADS868xx->msgChannelRange[6] = range;
			ch = 6;
			break;
		case ADS868X_PROG_REG_CH7_SET_RANGE:
			ADS868xx->msgChannelRange[7] = range;
			ch = 7;
			break;
		default:
			return ERROR_1;
	}

	//---ÿ��ͨ�������̵�����
	ADS868X_SPI_ChannelRange(ADS868xx, ch);
	//---����ͨ��������
	return ADS868X_SPI_WriteProgramReg(ADS868xx, chReg, range);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ͨ�������̷�Χ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ReadChannelRange(ADS868X_HandlerType* ADS868xx, UINT8_T chReg, UINT8_T *pRange)
{
	UINT8_T ch = ADS868X_CHANNEL_MAX;
	UINT8_T tempChannelRange[2] = { 0 };
	UINT8_T _return = OK_0;
	switch (chReg)
	{
		case ADS868X_PROG_REG_CH0_SET_RANGE:
			ch = 0;
			break;
		case ADS868X_PROG_REG_CH1_SET_RANGE:
			ch = 1;
			break;
		case ADS868X_PROG_REG_CH2_SET_RANGE:
			ch = 2;
			break;
		case ADS868X_PROG_REG_CH3_SET_RANGE:
			ch = 3;
			break;
		case ADS868X_PROG_REG_CH4_SET_RANGE:
			ch = 4;
			break;
		case ADS868X_PROG_REG_CH5_SET_RANGE:
			ch = 5;
			break;
		case ADS868X_PROG_REG_CH6_SET_RANGE:
			ch = 6;
			break;
		case ADS868X_PROG_REG_CH7_SET_RANGE:
			ch = 7;
			break;
		default:
			return ERROR_1;
	}
	//---��ȡͨ��������
	_return=ADS868X_SPI_ReadProgramReg(ADS868xx, chReg, tempChannelRange);
	//---�ж϶�ȡ���
	if (_return == OK_0)
	{
		if (tempChannelRange[1] == ADS868xx->msgChannelRange[ch])
		{
			*pRange = tempChannelRange[1];
		}
		else
		{
			_return = ERROR_2;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����òο���ѹuv
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteREFPowerUV(ADS868X_HandlerType* ADS868xx, UINT32_T refUV)
{
	ADS868xx->msgREFPowerUV = refUV;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�ο���ѹ
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT32_T ADS868X_SPI_ReadREFPowerUV(ADS868X_HandlerType* ADS868xx, UINT32_T refUV)
{
	return ADS868xx->msgREFPowerUV;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����òο���ѹmv
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteREFPowerMV(ADS868X_HandlerType* ADS868xx, UINT32_T refMV)
{
	ADS868xx->msgREFPowerUV = refMV*1000;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ÿͨ�������̺��������ֵ
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ChannelRange(ADS868X_HandlerType* ADS868xx, UINT8_T chIndex)
{
	UINT8_T _return = OK_0;
	if (chIndex==ADS868X_CHANNEL_MAX)
	{
		_return = ERROR_1;
	}
	else
	{
		switch (ADS868xx->msgChannelRange[chIndex])
		{
			//---����1.25����VREF
			case ADS868X_RANGE_5120MV_5120MV:
				ADS868xx->msgChannelRangeIsPositive[chIndex] = 0;
				ADS868xx->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS868xx->msgREFPowerUV * 1250);//5120000000;
				ADS868xx->msgChannelRangeBaseUVX1000[chIndex] = (ADS868xx->msgChannelRangeFullUVX1000[chIndex] * 2) / 65536; //156250;
				break;
			//---����0.625����VREF
			case ADS868X_RANGE_2560MV_2560MV:
				ADS868xx->msgChannelRangeIsPositive[chIndex] = 0;
				ADS868xx->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS868xx->msgREFPowerUV * 625); //2560000000;
				ADS868xx->msgChannelRangeBaseUVX1000[chIndex] = (ADS868xx->msgChannelRangeFullUVX1000[chIndex] * 2) / 65536; //78125;
				break;
			//---��2.5����VREF
			case ADS868X_RANGE_0MV_10240MV:
				ADS868xx->msgChannelRangeIsPositive[chIndex] = 1;
				ADS868xx->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS868xx->msgREFPowerUV * 2500);//10240000000;
				ADS868xx->msgChannelRangeBaseUVX1000[chIndex] = ADS868xx->msgChannelRangeFullUVX1000[chIndex] / 65536; //156250;
				break;
			//---��1.25����VREF
			case ADS868X_RANGE_0MV_5120MV:
				ADS868xx->msgChannelRangeIsPositive[chIndex] = 1;
				ADS868xx->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS868xx->msgREFPowerUV* 1250);//5120000000;
				ADS868xx->msgChannelRangeBaseUVX1000[chIndex] = ADS868xx->msgChannelRangeFullUVX1000[chIndex] / 65536; //78125;
				break;
			//---����2.5����VREF
			case ADS868X_RANGE_10240MV_10240MV:
			default:
				ADS868xx->msgChannelRangeIsPositive[chIndex] = 0;
				ADS868xx->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS868xx->msgREFPowerUV * 2500);//10240000000;
				ADS868xx->msgChannelRangeBaseUVX1000[chIndex] = (ADS868xx->msgChannelRangeFullUVX1000[chIndex] * 2) / 65536; //312500;
				break;
		}
	}
	return _return;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ��ADC�Ĳɼ��������ADCͨ���ĵ�ѹֵ
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_CalcChannelPower(ADS868X_HandlerType* ADS868xx, UINT8_T chIndex,UINT8_T isCalcDelta)
{
	//---����������
	ADS868xx->msgIsPositive[chIndex] = 0;
	UINT32_T adcDelta = 0;
	UINT64_T calcPower = 0;
	//---�ж��Ƿ���Ҫ�����ֵ
	if (isCalcDelta != 0)
	{
		//---��ȡ�ϴκͱ��εĲ�������ľ��Բ�ֵ
		adcDelta = ABS_SUB(ADS868xx->msgChannelNowADCResult[chIndex], ADS868xx->msgChannelOldADCResult[chIndex]);
		//---������ݲ�����Ͽ�ʼ
		if (adcDelta < 15)
		{
			if (adcDelta>5)
			{
				ADS868xx->msgChannelOldADCResult[chIndex] = MAX(ADS868xx->msgChannelNowADCResult[chIndex], ADS868xx->msgChannelOldADCResult[chIndex])-2;
			}
			else if (ADS868xx->msgChannelNowADCResult[chIndex] > ADS868xx->msgChannelOldADCResult[chIndex])
			{
				ADS868xx->msgChannelOldADCResult[chIndex] = ADS868xx->msgChannelNowADCResult[chIndex];
				if(adcDelta>2)
				{
					ADS868xx->msgChannelOldADCResult[chIndex] -=2;
				}
			}
			else
			{
				ADS868xx->msgChannelOldADCResult[chIndex] = MAX(ADS868xx->msgChannelNowADCResult[chIndex], ADS868xx->msgChannelOldADCResult[chIndex]);
			}
			calcPower = ADS868xx->msgChannelOldADCResult[chIndex];
		}
		else
		{
			calcPower = ADS868xx->msgChannelNowADCResult[chIndex];
			ADS868xx->msgChannelOldADCResult[chIndex] = ADS868xx->msgChannelNowADCResult[chIndex];
		}
	}
	else
	{
		calcPower = ADS868xx->msgChannelNowADCResult[chIndex];
	}
	calcPower &= 0xFFFC;
	//---������ݲ�����Ͻ���
	//---��������ת��Ϊģ����
	calcPower *= ADS868xx->msgChannelRangeBaseUVX1000[chIndex];
	double adcPower = 0;
	//---�ж�ADC������������˫���Ի��ǵ�����
	if (ADS868xx->msgChannelRangeIsPositive[chIndex] == 0)
	{
		if ((ADS868xx->msgChannelNowADCResult[chIndex] & 0x8000) != 0)
		{
			ADS868xx->msgIsPositive[chIndex] = 2;
			ADS868xx->msgChannelPowerResult[chIndex] = (UINT32_T)((calcPower - ADS868xx->msgChannelRangeFullUVX1000[chIndex]) / 1000);
		}
		else
		{
			ADS868xx->msgIsPositive[chIndex] = 1;
			ADS868xx->msgChannelPowerResult[chIndex] = (UINT32_T)((ADS868xx->msgChannelRangeFullUVX1000[chIndex] - calcPower) / 1000);
		}
	}
	else
	{
		ADS868xx->msgIsPositive[chIndex] = 2;
		ADS868xx->msgChannelPowerResult[chIndex] = (UINT32_T)(calcPower / 1000);
	}
	//---�����������
	if (ADS868xx->msgADCKP[chIndex] != 0)
	{
		adcPower = ADS868xx->msgChannelPowerResult[chIndex];
		adcPower *= ADS868xx->msgADCKP[chIndex];
		if (adcPower< ADS868xx->msgADCDelta[chIndex])
		{
			ADS868xx->msgIsPositive[chIndex] = 1;
			adcPower = (ADS868xx->msgADCDelta[chIndex] - adcPower);
		}
		else
		{
			adcPower -= ADS868xx->msgADCDelta[chIndex];
		}
		ADS868xx->msgChannelPowerResult[chIndex] = (UINT32_T)adcPower;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�Զ�ɨ��ͨ�����е�ADת������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_GetAutoRSTResult(ADS868X_HandlerType *ADS868xx, UINT8_T chNum)
{
	UINT8_T i = 0;
	UINT8_T adcRTemp[4] = {0};
	UINT8_T adcWTemp[4] = { 0 };
	UINT8_T _return = 0;
	UINT8_T rstMode = ADS868xx->msgAutoSeqEn;
	//---�ж��豸�Ƿ��ʼ���ɹ�
	if (ADS868xx->msgDeviceReady == 1)
	{
		_return = ADS868X_SPI_ConfigInit(ADS868xx);
		if (_return != OK_0)
		{
			goto GoToExit;
		}
	}

	//---�����Զ�ɨ��ģʽ
	_return =ADS868X_SPI_AUTORST(ADS868xx);

	//---ɨ��ͨ���Ľ��
	for (i = 0; i < chNum; i++)
	{
		//---�ж��Ƿ�ʹ���Զ�RSTɨ�蹦��
		if (rstMode & 0x01)
		{
			adcWTemp[3] = i;
			//---׼����ȡ����
			if (ADS868xx->msgSPI.msgCS.msgGPIOPort != NULL)
			{
				GPIO_OUT_0(ADS868xx->msgSPI.msgCS.msgGPIOPort, ADS868xx->msgSPI.msgCS.msgGPIOBit);
			}
			_return=ADS868X_SPI_SEND_ARRAY(ADS868xx, adcWTemp, adcRTemp, 4);
			//---�������ݵĶ�ȡ
			if (ADS868xx->msgSPI.msgCS.msgGPIOPort != NULL)
			{
				GPIO_OUT_1(ADS868xx->msgSPI.msgCS.msgGPIOPort, ADS868xx->msgSPI.msgCS.msgGPIOBit);
			}
			//---�����ȡ������
			ADS868xx->msgChannelNowADCResult[i] = adcRTemp[2];
			ADS868xx->msgChannelNowADCResult[i] = (ADS868xx->msgChannelNowADCResult[i] << 8) + adcRTemp[3];
			//---����������
			ADS868X_SPI_CalcChannelPower(ADS868xx, i,0);
		}
		rstMode >>= 1;
	}
	GoToExit:
	return  _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_GetAutoRSTNSampleResult(ADS868X_HandlerType* ADS868xx, UINT8_T chNum)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	UINT8_T j = 0;
	UINT8_T rstMode = ADS868xx->msgAutoSeqEn;
	//---����������
	UINT16_T adcSampleTemp[ADS868X_CHANNEL_MAX][ADS868X_N_SAMPLE_COUNT] = { 0 };
	//---��ȡ�������
	for (i = 0; i < ADS868X_N_SAMPLE_COUNT; i++)
	{
		//---��ȡ�������
		_return = ADS868X_SPI_GetAutoRSTResult(ADS868xx, chNum);
		//---�������ݰ���
		for (j=0;j< ADS868X_CHANNEL_MAX;j++)
		{
			adcSampleTemp[j][i] = ADS868xx->msgChannelNowADCResult[j];
		}
		//---У������
		if (_return != OK_0)
		{
			break;
		}
	}
	if (_return == OK_0)
	{
		//---�������ݰ���
		for (j = 0; j < ADS868X_CHANNEL_MAX; j++)
		{
			//---�ж��Ƿ�ʹ���Զ�RSTɨ�蹦��
			if (rstMode & 0x01)
			{
				//---������������
				AscSortFun2(adcSampleTemp[j], ADS868X_N_SAMPLE_COUNT);
				//---�����ֵ
				ADS868xx->msgChannelNowADCResult[j] = CalcAvgFun1(adcSampleTemp[j], (ADS868X_N_SAMPLE_COUNT - 2), 2);
				//---��������ĵ�ѹֵ
				ADS868X_SPI_CalcChannelPower(ADS868xx, j,1);
			}
			rstMode >>= 1;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ���ȡ�յ�ɨ��ͨ����ֵ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  ADS868X_SPI_GetManualChannelResult(ADS868X_HandlerType* ADS868xx, UINT16_T manualChannel)
{
	UINT8_T _return = OK_0;
	UINT8_T adcRTemp[4] = { 0 };
	UINT8_T adcWTemp[4] = { 0 };
	UINT8_T adcChannel = 0;
	//---�ж��豸�Ƿ��ʼ���ɹ�
	if (ADS868xx->msgDeviceReady==1)
	{
		_return=ADS868X_SPI_ConfigInit(ADS868xx);
		if (_return!=OK_0)
		{
			goto GoToExit;
		}
	}
	//---�����ֶ�ɨ��ͨ��
	_return = ADS868X_SPI_ManualChannel(ADS868xx, manualChannel);
	//---׼����ȡ���õ�ɨ��ͨ����ֵ
	if (ADS868xx->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_0(ADS868xx->msgSPI.msgCS.msgGPIOPort, ADS868xx->msgSPI.msgCS.msgGPIOBit);
	}
	//---��ȡADC�����Ľ��
	_return = ADS868X_SPI_SEND_ARRAY(ADS868xx, adcWTemp, adcRTemp, 4);
	//---������ȡ���õ�ɨ��ͨ����ֵ
	if (ADS868xx->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_1(ADS868xx->msgSPI.msgCS.msgGPIOPort, ADS868xx->msgSPI.msgCS.msgGPIOBit);
	}
	//---ͨ����ת��
	adcChannel = (UINT8_T)(manualChannel >> 10) & 0x0F;
	//---�ж��Ƿ���AUXͨ������
	if (adcChannel<8)
	{
		ADS868xx->msgChannelNowADCResult[adcChannel] = adcRTemp[2];
		ADS868xx->msgChannelNowADCResult[adcChannel] = (ADS868xx->msgChannelNowADCResult[adcChannel] << 8) + adcRTemp[3];
		//---����������
		ADS868X_SPI_CalcChannelPower(ADS868xx, adcChannel,0);
	}
	GoToExit:
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ��ֶ�ͨ������N�εĲ��Խ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_GetManualChannelNSampleResult(ADS868X_HandlerType* ADS868xx, UINT16_T manualChannel)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---����������
	UINT16_T adcSampleTemp[ADS868X_N_SAMPLE_COUNT] = { 0 };
	//---��ȡADC����ͨ�������
	UINT8_T adcChannelIndex = (UINT8_T)(manualChannel >> 10) & 0x0F;
	//---��ȡ�������
	for ( i = 0; i < ADS868X_N_SAMPLE_COUNT; i++)
	{
		_return = ADS868X_SPI_GetManualChannelResult(ADS868xx, manualChannel);
		adcSampleTemp[i] = ADS868xx->msgChannelNowADCResult[adcChannelIndex];
		if (_return!=OK_0)
		{
			break;
		}
	}
	if (_return==OK_0)
	{
		//---������������
		AscSortFun2(adcSampleTemp, ADS868X_N_SAMPLE_COUNT);
		//---�����ֵ
		ADS868xx->msgChannelNowADCResult[adcChannelIndex] = CalcAvgFun1(adcSampleTemp, (ADS868X_N_SAMPLE_COUNT - 2), 2);
		//---��������ĵ�ѹֵ
		ADS868X_SPI_CalcChannelPower(ADS868xx, adcChannelIndex,1);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�У׼ͨ�������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_CalibrationChannelErr(ADS868X_HandlerType* ADS868xx)
{
	UINT8_T i = 0;
	UINT8_T rstMode = ADS868xx->msgAutoSeqEn;
	for (i = 0; i < ADS868X_CHANNEL_MAX; i++)
	{
		if ((rstMode&0x01)==0)
		{
			if (i==0)
			{
				////---1�Ű����
				//ADS868xx->msgADCKP[i] = 1.013216;
				//ADS868xx->msgADCDelta[i] = 27130;

				//---2�Ű����
				ADS868xx->msgADCKP[i] = 1.013216;
				ADS868xx->msgADCDelta[i] = 26430;
			}
			else
			{
				////---1�Ű����
				//ADS868xx->msgADCKP[i] = 1.0129;
				//ADS868xx->msgADCDelta[i] = 25870;

				//---2�Ű����
				ADS868xx->msgADCKP[i] = 1.0129;
				ADS868xx->msgADCDelta[i] = 27070;
			}
			
		}
		rstMode >>= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ���ʼ������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ConfigInit(ADS868X_HandlerType* ADS868xx)
{
	UINT8_T _return = OK_0;
	UINT8_T tempBuffer[3] = { 0 };
	UINT8_T i = 0;
	if (ADS868xx->msgInitRetryCount==0)
	{
		ADS868xx->msgInitRetryCount = 1;
	}

	//---ѭ����γ�ʼ���豸
	for (i=0;i< ADS868xx->msgInitRetryCount;i++)
	{
		//---��λоƬ
		_return = ADS868X_SPI_Reset(ADS868xx);
		//---У��
		if (_return == OK_0)
		{
			//---�豸��������
			_return = ADS868X_SPI_WriteFeature(ADS868xx, 0x28);
			//---У��
			if (_return == OK_0)
			{
				//---��ȡ�豸������
				_return = ADS868X_SPI_ReadFeature(ADS868xx, tempBuffer);
				//---У��
				if (_return == OK_0)
				{
					break;
				}
			}
		}
	}

	//---����ɨ�跽ʽ
	_return = ADS868X_SPI_WriteAUTOSEQEN(ADS868xx, 0xF0);
	//---��ȡ���õ�ֵ
	_return = ADS868X_SPI_ReadProgramReg(ADS868xx, ADS868X_PROG_REG_AUTO_SEQ_EN, tempBuffer);

	//---�ж�У��
	if (ADS868xx->msgAutoSeqEn != tempBuffer[1])
	{
		_return = ERROR_1;
		ADS868xx->msgDeviceReady = 1;
	}
	else
	{
		//---����ͨ��������
		ADS868X_SPI_WriteChannelRange(ADS868xx, ADS868X_PROG_REG_CH0_SET_RANGE, ADS868X_RANGE_0MV_5120MV);
		ADS868X_SPI_WriteChannelRange(ADS868xx, ADS868X_PROG_REG_CH1_SET_RANGE, ADS868X_RANGE_0MV_5120MV);
		ADS868X_SPI_WriteChannelRange(ADS868xx, ADS868X_PROG_REG_CH2_SET_RANGE, ADS868X_RANGE_0MV_5120MV);
		//---���ù���ģʽ
		ADS868X_SPI_AUTORST(ADS868xx);
	}
	ADS868X_SPI_CalibrationChannelErr(ADS868xx);
	return _return;
}