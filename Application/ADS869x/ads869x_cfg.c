#include "ads869x_cfg.h"

//===ȫ�ֱ�������
ADS869X_HandlerType   g_ADS869XDevice0 = { 0 };
pADS869X_HandlerType  pADS869XDevice0 = &g_ADS869XDevice0;

//===ͳһ�����ֽ�����
UINT8_T(*ADS869X_SPI_SEND_CMD)(ADS869X_HandlerType *, UINT8_T, UINT8_T *);
//===ͳһ������������
UINT8_T(*ADS869X_SPI_SEND_ARRAY)(ADS869X_HandlerType*, UINT8_T*, UINT8_T*,UINT16_T);

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void ADS869X_SPI_Device0_Init(ADS869X_HandlerType *ADS869xx)
{

	//---��λ�ź�
	ADS869xx->msgHWRST.msgGPIOPort = NULL;
	ADS869xx->msgHWRST.msgGPIOBit = LL_GPIO_PIN_0;

	//---GPIOʱ��ʹ��
	if (ADS869xx->msgHWRST.msgGPIOPort != NULL)
	{
		GPIOTask_Clock(ADS869xx->msgHWRST.msgGPIOPort, 1);
	}

	//---SPI1�ӿ�
	//---PA4------ > SPI1_NSS
	//---PA5------ > SPI1_SCK
	//---PA6------ > SPI1_MISO
	//---PA7------ > SPI1_MOSI
	
	//---SPI2�ӿ�
	//---PB12------ > SPI2_NSS
	//---PB13------ > SPI2_SCK
	//---PB14------ > SPI2_MISO
	//---PB15------ > SPI2_MOSI

	//---CS
	ADS869xx->msgSPI.msgCS.msgGPIOPort = GPIOB;				//GPIOA;
	ADS869xx->msgSPI.msgCS.msgGPIOBit  = LL_GPIO_PIN_12;	//LL_GPIO_PIN_4;

	//---SCK
	ADS869xx->msgSPI.msgSCK.msgGPIOPort = GPIOB;			//GPIOA;
	ADS869xx->msgSPI.msgSCK.msgGPIOBit = LL_GPIO_PIN_13;	//LL_GPIO_PIN_5;

	//---MISO  SD0
	ADS869xx->msgSPI.msgMISO.msgGPIOPort = GPIOB;			//GPIOA;
	ADS869xx->msgSPI.msgMISO.msgGPIOBit  = LL_GPIO_PIN_14;	//LL_GPIO_PIN_6;

	//---MOSI SDI
	ADS869xx->msgSPI.msgMOSI.msgGPIOPort = GPIOB;			//GPIOA;
	ADS869xx->msgSPI.msgMOSI.msgGPIOBit  = LL_GPIO_PIN_15;	//LL_GPIO_PIN_7;

	//---GPIO������
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---GPIO�ĳ�ʼ��
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;					//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;		//---GPIO���ٶ�
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;		//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;						//---����ʹ��

	//---��ʼ��RST
	if (ADS869xx->msgHWRST.msgGPIOPort != NULL)
	{
		GPIO_InitStruct.Pin = ADS869xx->msgHWRST.msgGPIOBit;
		GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
		LL_GPIO_Init(ADS869xx->msgHWRST.msgGPIOPort, &GPIO_InitStruct);
		GPIO_OUT_1(ADS869xx->msgHWRST.msgGPIOPort, ADS869xx->msgHWRST.msgGPIOBit);
	}

	//---����ģʽ
	#ifndef USE_MCU_STM32F1
		//---�˿ڸ���ģʽ
		ADS869xx->msgSPI.msgGPIOAlternate = LL_GPIO_AF_5;
	#endif
	//---SPI���
		ADS869xx->msgSPI.msgSPIx = SPI2;//SPI1;
	#ifndef USE_MCU_STM32F1
		//---SPI��Э��
		ADS869xx->msgSPI.msgStandard = LL_SPI_PROTOCOL_MOTOROLA;
	#endif

	UINT8_T i = 0;
	//---�ο���ѹ����
	ADS869xx->msgREFPowerUV = ADS869X_REF_POWER_UV;
	for (i = 0; i < ADS869X_CHANNEL_MAX; i++)
	{
		ADS869xx->msgChannelRange[i] = 0;
		ADS869xx->msgIsPositive[i] = 0;
		ADS869xx->msgChannelNowADCResult[i] = 0;
		ADS869xx->msgChannelOldADCResult[i] = 0;
		ADS869xx->msgChannelPowerResult[i] = 0;
		ADS869X_SPI_ChannelRange(ADS869xx, i);
	}
	ADS869xx->msgDeviceReady = 0;
	ADS869xx->msgInitRetryCount = 3;
	ADS869xx->msgChipID = 0;
	//---Ĭ����������
	ADS869xx->msgFeature = 0x28;
	//---Ĭ����0xFF
	ADS869xx->msgAutoSeqEn = 0xFF;
	//---����������
	ADS869xx->msgSPI.msgPluseWidth = 2;
	//---ʱ�ӿ���Ϊ�͵�ƽ
	ADS869xx->msgSPI.msgCPOL = 0;
	//---���ݲ����ڵڶ���ʱ�ӱ���
	ADS869xx->msgSPI.msgCPOH = 1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void ADS869X_SPI_Device1_Init(ADS869X_HandlerType *ADS869xx)
{
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void ADS869X_SPI_Device2_Init(ADS869X_HandlerType *ADS869xx)
{
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_HW_Init(ADS869X_HandlerType *ADS869xx)
{
	//---ע����ǰ����������
	SPITask_DeInit(&(ADS869xx->msgSPI));
	//---Ӳ���˿ڵ�����---Ӳ��ʵ��
	SPITask_MHW_GPIO_Init(&(ADS869xx->msgSPI));
	//---Ӳ��SPI�ĳ�ʼ��
	LL_SPI_InitTypeDef SPI_InitStruct = {0};
	//---SPI��ģʽ����
	SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
	SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;						//---����ģʽ
	SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;				//---8λ����
	//---ʱ�Ӽ��Ե�����
	if (ADS869xx->msgSPI.msgCPOL == 0)
	{
		//---CLK����ʱΪ�͵�ƽ (CLK������ֻ���ǵ͵�ƽ)
		SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
		GPIO_OUT_0(ADS869xx->msgSPI.msgSCK.msgGPIOPort, ADS869xx->msgSPI.msgSCK.msgGPIOBit);
	}
	else
	{
		//---CLK����ʱΪ�ߵ�ƽ (CLK������ֻ���ǵ͵�ƽ)
		SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_HIGH;
	}
	//---���ݲ�����ʱ�ӱ���λ��
	if (ADS869xx->msgSPI.msgCPOH ==0)
	{
		SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
	}
	else
	{
		SPI_InitStruct.ClockPhase = LL_SPI_PHASE_2EDGE;
	}
	SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;							//---�������
	SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV2;		//---ϵͳʱ��2��Ƶ
	SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;						//---��λ��ǰ
	SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;	//---Ӳ��CRC��ʹ��
	SPI_InitStruct.CRCPoly = 7;
	//---��ʼ����ѯ��ʽ��SPI
	SPITask_MHW_PollMode_Init(&(ADS869xx->msgSPI), SPI_InitStruct);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_SW_Init(ADS869X_HandlerType *ADS869xx)
{
	SPITask_DeInit(&(ADS869xx->msgSPI));

	//---Ӳ���˿ڵ�����---���ʵ��
	SPITask_MSW_GPIO_Init(&(ADS869xx->msgSPI));

	//---ʱ���ߵļ���
	if (ADS869xx->msgSPI.msgCPOL == 0)
	{
		GPIO_OUT_0(ADS869xx->msgSPI.msgSCK.msgGPIOPort, ADS869xx->msgSPI.msgSCK.msgGPIOBit);
	}
	else
	{
		GPIO_OUT_1(ADS869xx->msgSPI.msgSCK.msgGPIOPort, ADS869xx->msgSPI.msgSCK.msgGPIOBit);
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
UINT8_T ADS869X_SPI_SW_SendCmd(ADS869X_HandlerType *ADS869xx, UINT8_T cmd, UINT8_T *pRVal)
{
	//---���ݷ���
	return SPITask_MSW_WriteAndReadByteMSB(&(ADS869xx->msgSPI), cmd, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������������
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_SW_SendArray(ADS869X_HandlerType* ADS869xx, UINT8_T* pWVal, UINT8_T* pRVal, UINT16_T length)
{
	//---���ݷ���
	return SPITask_MSW_WriteAndReadDataMSB(&(ADS869xx->msgSPI), pWVal, pRVal, length);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ֽ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_HW_SendCmd(ADS869X_HandlerType *ADS869xx, UINT8_T cmd, UINT8_T *pRVal)
{
	//---���ݷ���
	return SPITask_MHW_PollMode_WriteAndReadByte(&(ADS869xx->msgSPI), cmd, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������������
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_HW_SendArray(ADS869X_HandlerType* ADS869xx, UINT8_T *pWVal, UINT8_T* pRVal,UINT16_T length)
{
	//---���ݷ���
	return SPITask_MHW_PollMode_WriteAndReadData(&(ADS869xx->msgSPI), pWVal, pRVal,length);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_Init(ADS869X_HandlerType *ADS869xx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHW)
{
	//---ʹ�õ�DHT11�Ķ˿�
	if ((ADS869xx != NULL) && (ADS869xx == ADS869X_TASK_ONE))
	{
		ADS869X_SPI_Device0_Init(ADS869xx);
	}
	else if ((ADS869xx != NULL) && (ADS869xx == ADS869X_TASK_TWO))
	{
		ADS869X_SPI_Device1_Init(ADS869xx);
	}
	else if ((ADS869xx != NULL) && (ADS869xx == ADS869X_TASK_THREE))
	{
		ADS869X_SPI_Device2_Init(ADS869xx);
	}
	else
	{
		return ERROR_1;
	}

	//---�жϳ�ʼ���ķ�ʽ
	if (isHW != 0)
	{
		ADS869xx->msgSPI.msgModelIsHW = 1;
		ADS869X_SPI_HW_Init(ADS869xx);
		ADS869X_SPI_SEND_CMD = ADS869X_SPI_HW_SendCmd;
		ADS869X_SPI_SEND_ARRAY = ADS869X_SPI_HW_SendArray;
	}
	else
	{
		ADS869xx->msgSPI.msgModelIsHW = 0;
		ADS869X_SPI_SW_Init(ADS869xx);
		ADS869X_SPI_SEND_CMD = ADS869X_SPI_SW_SendCmd;
		ADS869X_SPI_SEND_ARRAY = ADS869X_SPI_SW_SendArray;
	}

	//---ע��ms��ʱʱ��
	if (pFuncDelayms != NULL)
	{
		ADS869xx->msgFuncDelayms = pFuncDelayms;
	}
	else
	{
		ADS869xx->msgFuncDelayms = DelayTask_ms;
	}

	//---ע��us��ʱ����
	if (pFuncDelayus != NULL)
	{
		ADS869xx->msgSPI.msgFuncDelayus = pFuncDelayus;
	}
	else
	{
		ADS869xx->msgSPI.msgFuncDelayus = DelayTask_us;
	}

	//---ע��δ���
	ADS869xx->msgSPI.msgFuncTimeTick = pFuncTimerTick;

	//---����ADS869X
	return ADS869X_SPI_ConfigInit(ADS869xx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�дADS869X����Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_WriteCommandReg(ADS869X_HandlerType *ADS869xx, UINT32_T cmd)
{
	UINT8_T _return = OK_0;
	UINT8_T wTemp[2] = { 0 };
	wTemp[0] = (UINT8_T)((cmd >> 8)&0xFF);
	wTemp[1] = (UINT8_T)(cmd & 0xFF);
	if (ADS869xx->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_0(ADS869xx->msgSPI.msgCS.msgGPIOPort, ADS869xx->msgSPI.msgCS.msgGPIOBit);
	}
	_return = ADS869X_SPI_SEND_ARRAY(ADS869xx, wTemp, NULL, 2);
	if (ADS869xx->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_1(ADS869xx->msgSPI.msgCS.msgGPIOPort, ADS869xx->msgSPI.msgCS.msgGPIOBit);
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
UINT8_T ADS869X_SPI_WriteProgramReg(ADS869X_HandlerType *ADS869xx, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	UINT8_T wTemp[2] = { 0 };
	wTemp[0] = (addr << 1) | 0x01;
	wTemp[1] = val;
	if (ADS869xx->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_0(ADS869xx->msgSPI.msgCS.msgGPIOPort, ADS869xx->msgSPI.msgCS.msgGPIOBit);
	}
	_return = ADS869X_SPI_SEND_ARRAY(ADS869xx, wTemp, NULL, 2);
	if (ADS869xx->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_1(ADS869xx->msgSPI.msgCS.msgGPIOPort, ADS869xx->msgSPI.msgCS.msgGPIOBit);
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
UINT8_T ADS869X_SPI_ReadProgramReg(ADS869X_HandlerType *ADS869xx, UINT8_T addr, UINT8_T *pVal)
{
	UINT8_T _return = OK_0;
	UINT8_T wTemp[3] = { 0 };
	UINT8_T rTemp[3] = { 0 };
	wTemp[0] = (addr << 1) & 0xFE;
	if (ADS869xx->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_0(ADS869xx->msgSPI.msgCS.msgGPIOPort, ADS869xx->msgSPI.msgCS.msgGPIOBit);
	}
	_return = ADS869X_SPI_SEND_ARRAY(ADS869xx, wTemp, rTemp, 3);
	if (ADS869xx->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_1(ADS869xx->msgSPI.msgCS.msgGPIOPort, ADS869xx->msgSPI.msgCS.msgGPIOBit);
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
UINT8_T ADS869X_SPI_ReadCommandBack(ADS869X_HandlerType* ADS869xx, UINT8_T* pVal)
{
	return ADS869X_SPI_ReadProgramReg(ADS869xx, ADS869X_CMD_READ_BACK, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�����������ѡ�е�״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_NO_OP(ADS869X_HandlerType* ADS869xx)
{
	return ADS869X_SPI_WriteCommandReg(ADS869xx, ADS869X_CMD_REG_NO_OP);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_STDBY(ADS869X_HandlerType* ADS869xx)
{
	return ADS869X_SPI_WriteCommandReg(ADS869xx, ADS869X_CMD_REG_STDBY);
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�
//////�������:
//////�������:
//////˵		�����˳���ģʽ��ִ��AUTO_RST����MAN_CH_n�������Ҫ�ȴ�����20us�Ա�֤�������ݵ�ADת��
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_PWRDN(ADS869X_HandlerType* ADS869xx)
{
	return ADS869X_SPI_WriteCommandReg(ADS869xx, ADS869X_CMD_REG_PWR_DN);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�Ӳ����λ�豸
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  ADS869X_SPI_HardReset(ADS869X_HandlerType *ADS869xx)
{
	if (ADS869xx->msgHWRST.msgGPIOPort!=NULL)
	{
		GPIO_OUT_0(ADS869xx->msgHWRST.msgGPIOPort, ADS869xx->msgHWRST.msgGPIOBit);
		ADS869xx->msgFuncDelayms(1);
		GPIO_OUT_1(ADS869xx->msgHWRST.msgGPIOPort, ADS869xx->msgHWRST.msgGPIOBit);
		ADS869xx->msgFuncDelayms(1);
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
UINT8_T  ADS869X_SPI_SoftReset(ADS869X_HandlerType *ADS869xx)
{
	return ADS869X_SPI_WriteCommandReg(ADS869xx, ADS869X_CMD_REG_RST);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ��豸��λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_Reset(ADS869X_HandlerType* ADS869xx)
{
	UINT8_T _return = OK_0;
	if (ADS869xx->msgHWRST.msgGPIOPort != NULL)
	{
		_return = ADS869X_SPI_HardReset(ADS869xx);
	}
	else
	{
		_return = ADS869X_SPI_SoftReset(ADS869xx);
	}
	ADS869xx->msgDeviceReady = 0;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������Զ�ɨ��ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_AUTORST(ADS869X_HandlerType* ADS869xx)
{
	return ADS869X_SPI_WriteCommandReg(ADS869xx, ADS869X_CMD_REG_AUTO_RST);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ������ֶ�ɨ��ͨ��
//////�������:
//////�������:
//////˵		�����˳���ģʽ��ִ��AUTO_RST����MAN_CH_n�������Ҫ�ȴ�����20us�Ա�֤�������ݵ�ADת��
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ManualChannel(ADS869X_HandlerType* ADS869xx,UINT16_T manualCHCmd)
{
	return ADS869X_SPI_WriteCommandReg(ADS869xx, manualCHCmd);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ������豸ID
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_WriteChipID(ADS869X_HandlerType* ADS869xx, UINT8_T devid)
{
	devid <<= 6;
	ADS869xx->msgChipID = (devid & 0xC0) | ADS869xx->msgFeature;
	return ADS869X_SPI_WriteProgramReg(ADS869xx, ADS869X_PROG_REG_FEATURE_SELECT, ADS869xx->msgChipID);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ���ȡ�豸ID
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ReadChipID(ADS869X_HandlerType* ADS869xx, UINT8_T *pDevID)
{
	UINT8_T _return= ADS869X_SPI_ReadProgramReg(ADS869xx, ADS869X_PROG_REG_FEATURE_SELECT, pDevID);
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
UINT8_T ADS869X_SPI_CheckChipID(ADS869X_HandlerType* ADS869xx)
{
	UINT8_T tempChipID = 0x00;
	UINT8_T _return = OK_0;
	_return = ADS869X_SPI_ReadChipID(ADS869xx, &tempChipID);
	//---У���ȡ��ID��Ϣ
	if (tempChipID!=ADS869xx->msgChipID)
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
UINT8_T ADS869X_SPI_DetectionDevice(ADS869X_HandlerType* ADS869xx)
{
	UINT8_T tempAutoSeqEn[2] = { 0 };
	UINT8_T _return = OK_0;
	_return=ADS869X_SPI_ReadProgramReg(pADS869XDevice0, ADS869X_PROG_REG_AUTO_SEQ_EN, tempAutoSeqEn);
	//---У�����Ƿ���ȷ
	if (tempAutoSeqEn[1]!=ADS869xx->msgAutoSeqEn)
	{
		_return += ERROR_1;
	}
	else
	{
		//---У���豸��ID��Ϣ
		_return = ADS869X_SPI_CheckChipID(ADS869xx);
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
UINT8_T ADS869X_SPI_WriteAUTOSEQEN(ADS869X_HandlerType* ADS869xx, UINT8_T seq)
{
	ADS869xx->msgAutoSeqEn = seq;
	return ADS869X_SPI_WriteProgramReg(ADS869xx, ADS869X_PROG_REG_AUTO_SEQ_EN, seq);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�Զ�ɨ������ͨ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ReadAUTOSEQEN(ADS869X_HandlerType* ADS869xx, UINT8_T *pAutoSeqEn)
{
	UINT8_T tempAutoSeqEn[2] = { 0 };
	UINT8_T _return= ADS869X_SPI_ReadProgramReg(ADS869xx, ADS869X_PROG_REG_AUTO_SEQ_EN, tempAutoSeqEn);
	if (_return==OK_0)
	{
		if (tempAutoSeqEn[1]==ADS869xx->msgAutoSeqEn)
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
UINT8_T ADS869X_SPI_WriteChannelPWRDN(ADS869X_HandlerType* ADS869xx, UINT8_T ch)
{
	ADS869xx->msgChannelPWRDN = ch;
	return ADS869X_SPI_WriteProgramReg(ADS869xx, ADS869X_PROG_REG_CH_PWR_DN, ch);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ������ģʽ��ȡ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ReadChannelPWRDN(ADS869X_HandlerType* ADS869xx, UINT8_T *pPWRDN)
{
	UINT8_T tempPWRDN[2] = { 0 };
	UINT8_T _return = ADS869X_SPI_ReadProgramReg(ADS869xx, ADS869X_PROG_REG_CH_PWR_DN, tempPWRDN);
	if (_return == OK_0)
	{
		if (tempPWRDN[1] == ADS869xx->msgChannelPWRDN)
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
UINT8_T ADS869X_SPI_WriteFeature(ADS869X_HandlerType* ADS869xx, UINT8_T feature)
{
	ADS869xx->msgFeature = (feature&0x3F)|ADS869xx->msgChipID;
	return ADS869X_SPI_WriteProgramReg(ADS869xx, ADS869X_PROG_REG_FEATURE_SELECT, feature);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ������ģʽ��ȡ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ReadFeature(ADS869X_HandlerType* ADS869xx, UINT8_T *pFeature)
{
	UINT8_T tempFeature[2] = { 0 };
	UINT8_T _return = ADS869X_SPI_ReadProgramReg(ADS869xx, ADS869X_PROG_REG_FEATURE_SELECT, tempFeature);
	if (_return == OK_0)
	{
		if (tempFeature[1] == ADS869xx->msgFeature)
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
UINT8_T ADS869X_SPI_WriteChannelRange(ADS869X_HandlerType* ADS869xx, UINT8_T chReg, UINT8_T range)
{
	UINT8_T ch = ADS869X_CHANNEL_MAX;
	switch (chReg)
	{
		case ADS869X_PROG_REG_CH0_SET_RANGE:
			ADS869xx->msgChannelRange[0] = range;
			ch = 0;
			break;
		case ADS869X_PROG_REG_CH1_SET_RANGE:
			ADS869xx->msgChannelRange[1] = range;
			ch = 1;
			break;
		case ADS869X_PROG_REG_CH2_SET_RANGE:
			ADS869xx->msgChannelRange[2] = range;
			ch = 2;
			break;
		case ADS869X_PROG_REG_CH3_SET_RANGE:
			ADS869xx->msgChannelRange[3] = range;
			ch = 3;
			break;
		case ADS869X_PROG_REG_CH4_SET_RANGE:
			ADS869xx->msgChannelRange[4] = range;
			ch = 4;
			break;
		case ADS869X_PROG_REG_CH5_SET_RANGE:
			ADS869xx->msgChannelRange[5] = range;
			ch = 5;
			break;
		case ADS869X_PROG_REG_CH6_SET_RANGE:
			ADS869xx->msgChannelRange[6] = range;
			ch = 6;
			break;
		case ADS869X_PROG_REG_CH7_SET_RANGE:
			ADS869xx->msgChannelRange[7] = range;
			ch = 7;
			break;
		default:
			return ERROR_1;
	}

	//---ÿ��ͨ�������̵�����
	ADS869X_SPI_ChannelRange(ADS869xx, ch);
	//---����ͨ��������
	return ADS869X_SPI_WriteProgramReg(ADS869xx, chReg, range);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ͨ�������̷�Χ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ReadChannelRange(ADS869X_HandlerType* ADS869xx, UINT8_T chReg, UINT8_T *pRange)
{
	UINT8_T ch = ADS869X_CHANNEL_MAX;
	UINT8_T tempChannelRange[2] = { 0 };
	UINT8_T _return = OK_0;
	switch (chReg)
	{
		case ADS869X_PROG_REG_CH0_SET_RANGE:
			ch = 0;
			break;
		case ADS869X_PROG_REG_CH1_SET_RANGE:
			ch = 1;
			break;
		case ADS869X_PROG_REG_CH2_SET_RANGE:
			ch = 2;
			break;
		case ADS869X_PROG_REG_CH3_SET_RANGE:
			ch = 3;
			break;
		case ADS869X_PROG_REG_CH4_SET_RANGE:
			ch = 4;
			break;
		case ADS869X_PROG_REG_CH5_SET_RANGE:
			ch = 5;
			break;
		case ADS869X_PROG_REG_CH6_SET_RANGE:
			ch = 6;
			break;
		case ADS869X_PROG_REG_CH7_SET_RANGE:
			ch = 7;
			break;
		default:
			return ERROR_1;
	}
	//---��ȡͨ��������
	_return=ADS869X_SPI_ReadProgramReg(ADS869xx, chReg, tempChannelRange);
	//---�ж϶�ȡ���
	if (_return == OK_0)
	{
		if (tempChannelRange[1] == ADS869xx->msgChannelRange[ch])
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
UINT8_T ADS869X_SPI_WriteREFPowerUV(ADS869X_HandlerType* ADS869xx, UINT32_T refUV)
{
	ADS869xx->msgREFPowerUV = refUV;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�ο���ѹ
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT32_T ADS869X_SPI_ReadREFPowerUV(ADS869X_HandlerType* ADS869xx, UINT32_T refUV)
{
	return ADS869xx->msgREFPowerUV;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����òο���ѹmv
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_WriteREFPowerMV(ADS869X_HandlerType* ADS869xx, UINT32_T refMV)
{
	ADS869xx->msgREFPowerUV = refMV*1000;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ÿͨ�������̺��������ֵ
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ChannelRange(ADS869X_HandlerType* ADS869xx, UINT8_T chIndex)
{
	UINT8_T _return = OK_0;
	if (chIndex==ADS869X_CHANNEL_MAX)
	{
		_return = ERROR_1;
	}
	else
	{
		switch (ADS869xx->msgChannelRange[chIndex])
		{
			//---����1.25����VREF
			case ADS869X_RANGE_5120MV_5120MV:
				ADS869xx->msgChannelRangeIsPositive[chIndex] = 0;
				ADS869xx->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS869xx->msgREFPowerUV * 1250);//5120000000;
				ADS869xx->msgChannelRangeBaseUVX1000[chIndex] = (ADS869xx->msgChannelRangeFullUVX1000[chIndex] * 2) / (1<< ADS869X_ADC_SAMPLE_BITS); //39.0625;
				break;
			//---����0.625����VREF
			case ADS869X_RANGE_2560MV_2560MV:
				ADS869xx->msgChannelRangeIsPositive[chIndex] = 0;
				ADS869xx->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS869xx->msgREFPowerUV * 625); //2560000000;
				ADS869xx->msgChannelRangeBaseUVX1000[chIndex] = (ADS869xx->msgChannelRangeFullUVX1000[chIndex] * 2) / (1 << ADS869X_ADC_SAMPLE_BITS); //19.53125;
				break;
			//---��2.5����VREF
			case ADS869X_RANGE_0MV_10240MV:
				ADS869xx->msgChannelRangeIsPositive[chIndex] = 1;
				ADS869xx->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS869xx->msgREFPowerUV * 2500);//10240000000;
				ADS869xx->msgChannelRangeBaseUVX1000[chIndex] = ADS869xx->msgChannelRangeFullUVX1000[chIndex] / (1 << ADS869X_ADC_SAMPLE_BITS); //39.0625;
				break;
			//---��1.25����VREF
			case ADS869X_RANGE_0MV_5120MV:
				ADS869xx->msgChannelRangeIsPositive[chIndex] = 1;
				ADS869xx->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS869xx->msgREFPowerUV* 1250);//5120000000;
				ADS869xx->msgChannelRangeBaseUVX1000[chIndex] = ADS869xx->msgChannelRangeFullUVX1000[chIndex] / (1 << ADS869X_ADC_SAMPLE_BITS); //19.53125;
				break;
			//---����2.5����VREF
			case ADS869X_RANGE_10240MV_10240MV:
			default:
				ADS869xx->msgChannelRangeIsPositive[chIndex] = 0;
				ADS869xx->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS869xx->msgREFPowerUV * 2500);//10240000000;
				ADS869xx->msgChannelRangeBaseUVX1000[chIndex] = (ADS869xx->msgChannelRangeFullUVX1000[chIndex] * 2) / (1 << ADS869X_ADC_SAMPLE_BITS); //78.125
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
UINT8_T ADS869X_SPI_CalcChannelPower(ADS869X_HandlerType* ADS869xx, UINT8_T chIndex,UINT8_T isCalcDelta)
{
	//---����������
	ADS869xx->msgIsPositive[chIndex] = 0;
	UINT32_T adcDelta = 0;
	UINT64_T calcPower = 0;
	//---�ж��Ƿ���Ҫ�����ֵ
	if (isCalcDelta != 0)
	{
		//---��ȡ�ϴκͱ��εĲ�������ľ��Բ�ֵ
		adcDelta = ABS_SUB(ADS869xx->msgChannelNowADCResult[chIndex], ADS869xx->msgChannelOldADCResult[chIndex]);
		//---������ݲ�����Ͽ�ʼ
		if (adcDelta < 15)
		{
			if (adcDelta>5)
			{
				ADS869xx->msgChannelOldADCResult[chIndex] = MAX(ADS869xx->msgChannelNowADCResult[chIndex], ADS869xx->msgChannelOldADCResult[chIndex])-2;
			}
			else if (ADS869xx->msgChannelNowADCResult[chIndex] > ADS869xx->msgChannelOldADCResult[chIndex])
			{
				ADS869xx->msgChannelOldADCResult[chIndex] = ADS869xx->msgChannelNowADCResult[chIndex];
				if(adcDelta>2)
				{
					ADS869xx->msgChannelOldADCResult[chIndex] -=2;
				}
			}
			else if (ADS869xx->msgChannelNowADCResult[chIndex] < ADS869xx->msgChannelOldADCResult[chIndex])
			{
				ADS869xx->msgChannelOldADCResult[chIndex] -= 1;
			}
			else
			{
				ADS869xx->msgChannelOldADCResult[chIndex] = MAX(ADS869xx->msgChannelNowADCResult[chIndex], ADS869xx->msgChannelOldADCResult[chIndex]);
			}
			calcPower = ADS869xx->msgChannelOldADCResult[chIndex];
		}
		else
		{
			calcPower = ADS869xx->msgChannelNowADCResult[chIndex];
			ADS869xx->msgChannelOldADCResult[chIndex] = ADS869xx->msgChannelNowADCResult[chIndex];
		}
	}
	else
	{
		calcPower = ADS869xx->msgChannelNowADCResult[chIndex];
	}
	calcPower &= ((1<< ADS869X_ADC_SAMPLE_BITS)-1);
	//---������ݲ�����Ͻ���
	//---��������ת��Ϊģ����
	calcPower *= ADS869xx->msgChannelRangeBaseUVX1000[chIndex];
	double adcPower = 0;
	//---�ж�ADC������������˫���Ի��ǵ�����
	if (ADS869xx->msgChannelRangeIsPositive[chIndex] == 0)
	{
		if ((ADS869xx->msgChannelNowADCResult[chIndex] & (1<< (ADS869X_ADC_SAMPLE_BITS-1))) != 0)
		{
			ADS869xx->msgIsPositive[chIndex] = 2;
			ADS869xx->msgChannelPowerResult[chIndex] = (UINT32_T)((calcPower - ADS869xx->msgChannelRangeFullUVX1000[chIndex]) / 1000);
		}
		else
		{
			ADS869xx->msgIsPositive[chIndex] = 1;
			ADS869xx->msgChannelPowerResult[chIndex] = (UINT32_T)((ADS869xx->msgChannelRangeFullUVX1000[chIndex] - calcPower) / 1000);
		}
	}
	else
	{
		ADS869xx->msgIsPositive[chIndex] = 2;
		ADS869xx->msgChannelPowerResult[chIndex] = (UINT32_T)(calcPower / 1000);
	}
	//---�����������
	if (ADS869xx->msgADCKP[chIndex] != 0)
	{
		adcPower = ADS869xx->msgChannelPowerResult[chIndex];
		adcPower *= ADS869xx->msgADCKP[chIndex];
		if (adcPower< ADS869xx->msgADCDelta[chIndex])
		{
			ADS869xx->msgIsPositive[chIndex] = 1;
			adcPower = (ADS869xx->msgADCDelta[chIndex] - adcPower);
		}
		else
		{
			adcPower -= ADS869xx->msgADCDelta[chIndex];
		}
		ADS869xx->msgChannelPowerResult[chIndex] = (UINT32_T)adcPower;
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
UINT8_T ADS869X_SPI_GetAutoRSTResult(ADS869X_HandlerType *ADS869xx, UINT8_T chNum)
{
	UINT8_T i = 0;
	UINT8_T adcRTemp[5] = { 0 };
	UINT8_T adcWTemp[5] = { 0 };
	UINT8_T _return = 0;
	UINT8_T rstMode = ADS869xx->msgAutoSeqEn;
	//---�ж��豸�Ƿ��ʼ���ɹ�
	if (ADS869xx->msgDeviceReady == 1)
	{
		_return = ADS869X_SPI_ConfigInit(ADS869xx);
		if (_return != OK_0)
		{
			goto GoToExit;
		}
	}

	//---�����Զ�ɨ��ģʽ
	_return =ADS869X_SPI_AUTORST(ADS869xx);

	//---ɨ��ͨ���Ľ��
	for (i = 0; i < chNum; i++)
	{
		//---�ж��Ƿ�ʹ���Զ�RSTɨ�蹦��
		if (rstMode & 0x01)
		{
			adcWTemp[3] = i;
			//---׼����ȡ����
			if (ADS869xx->msgSPI.msgCS.msgGPIOPort != NULL)
			{
				GPIO_OUT_0(ADS869xx->msgSPI.msgCS.msgGPIOPort, ADS869xx->msgSPI.msgCS.msgGPIOBit);
			}
			_return=ADS869X_SPI_SEND_ARRAY(ADS869xx, adcWTemp, adcRTemp, 5);
			//---�������ݵĶ�ȡ
			if (ADS869xx->msgSPI.msgCS.msgGPIOPort != NULL)
			{
				GPIO_OUT_1(ADS869xx->msgSPI.msgCS.msgGPIOPort, ADS869xx->msgSPI.msgCS.msgGPIOBit);
			}
			//---�����ȡ������
			ADS869xx->msgChannelNowADCResult[i] = adcRTemp[2];
			ADS869xx->msgChannelNowADCResult[i] = (ADS869xx->msgChannelNowADCResult[i] << 8) + adcRTemp[3];
			ADS869xx->msgChannelNowADCResult[i] = (ADS869xx->msgChannelNowADCResult[i] << 8) + adcRTemp[4];
			ADS869xx->msgChannelNowADCResult[i] >>= ADS869X_DATA_SAMPLE_BITS;
			//---����������
			ADS869X_SPI_CalcChannelPower(ADS869xx, i,0);
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
UINT8_T ADS869X_SPI_GetAutoRSTNSampleResult(ADS869X_HandlerType* ADS869xx, UINT8_T chNum)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	UINT8_T j = 0;
	UINT8_T rstMode = ADS869xx->msgAutoSeqEn;
	//---����������
	UINT32_T adcSampleTemp[ADS869X_CHANNEL_MAX][ADS869X_N_SAMPLE_COUNT] = { 0 };
	//---��ȡ�������
	for (i = 0; i < ADS869X_N_SAMPLE_COUNT; i++)
	{
		//---��ȡ�������
		_return = ADS869X_SPI_GetAutoRSTResult(ADS869xx, chNum);
		//---�������ݰ���
		for (j=0;j< ADS869X_CHANNEL_MAX;j++)
		{
			adcSampleTemp[j][i] = ADS869xx->msgChannelNowADCResult[j];
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
		for (j = 0; j < ADS869X_CHANNEL_MAX; j++)
		{
			//---�ж��Ƿ�ʹ���Զ�RSTɨ�蹦��
			if (rstMode & 0x01)
			{
				//---������������
				AscSortFun3(adcSampleTemp[j], ADS869X_N_SAMPLE_COUNT);
				//---�����ֵ
				ADS869xx->msgChannelNowADCResult[j] = CalcAvgFun5(adcSampleTemp[j], (ADS869X_N_SAMPLE_COUNT - 2), 2);
				//---��������ĵ�ѹֵ
				ADS869X_SPI_CalcChannelPower(ADS869xx, j,1);
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
UINT8_T  ADS869X_SPI_GetManualChannelResult(ADS869X_HandlerType* ADS869xx, UINT16_T manualChannel)
{
	UINT8_T _return = OK_0;
	UINT8_T adcRTemp[5] = { 0 };
	UINT8_T adcWTemp[5] = { 0 };
	UINT8_T adcChannel = 0;
	//---�ж��豸�Ƿ��ʼ���ɹ�
	if (ADS869xx->msgDeviceReady==1)
	{
		_return=ADS869X_SPI_ConfigInit(ADS869xx);
		if (_return!=OK_0)
		{
			goto GoToExit;
		}
	}
	//---�����ֶ�ɨ��ͨ��
	_return = ADS869X_SPI_ManualChannel(ADS869xx, manualChannel);
	//---׼����ȡ���õ�ɨ��ͨ����ֵ
	if (ADS869xx->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_0(ADS869xx->msgSPI.msgCS.msgGPIOPort, ADS869xx->msgSPI.msgCS.msgGPIOBit);
	}
	//---��ȡADC�����Ľ��
	_return = ADS869X_SPI_SEND_ARRAY(ADS869xx, adcWTemp, adcRTemp, 5);
	//---������ȡ���õ�ɨ��ͨ����ֵ
	if (ADS869xx->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_1(ADS869xx->msgSPI.msgCS.msgGPIOPort, ADS869xx->msgSPI.msgCS.msgGPIOBit);
	}
	//---ͨ����ת��
	adcChannel = (UINT8_T)(manualChannel >> 10) & 0x0F;
	//---�ж��Ƿ���AUXͨ������
	if (adcChannel<8)
	{
		ADS869xx->msgChannelNowADCResult[adcChannel] = adcRTemp[2];
		ADS869xx->msgChannelNowADCResult[adcChannel] = (ADS869xx->msgChannelNowADCResult[adcChannel] << 8) + adcRTemp[3];
		ADS869xx->msgChannelNowADCResult[adcChannel] = (ADS869xx->msgChannelNowADCResult[adcChannel] << 8) + adcRTemp[4];
		ADS869xx->msgChannelNowADCResult[adcChannel] >>= ADS869X_DATA_SAMPLE_BITS;
		//---����������
		ADS869X_SPI_CalcChannelPower(ADS869xx, adcChannel,0);
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
UINT8_T ADS869X_SPI_GetManualChannelNSampleResult(ADS869X_HandlerType* ADS869xx, UINT16_T manualChannel)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---����������
	UINT32_T adcSampleTemp[ADS869X_N_SAMPLE_COUNT] = { 0 };
	//---��ȡADC����ͨ�������
	UINT8_T adcChannelIndex = (UINT8_T)(manualChannel >> 10) & 0x0F;
	//---��ȡ�������
	for ( i = 0; i < ADS869X_N_SAMPLE_COUNT; i++)
	{
		_return = ADS869X_SPI_GetManualChannelResult(ADS869xx, manualChannel);
		adcSampleTemp[i] = ADS869xx->msgChannelNowADCResult[adcChannelIndex];
		if (_return!=OK_0)
		{
			break;
		}
	}
	if (_return==OK_0)
	{
		//---������������
		AscSortFun3(adcSampleTemp, ADS869X_N_SAMPLE_COUNT);
		//---�����ֵ
		ADS869xx->msgChannelNowADCResult[adcChannelIndex] = CalcAvgFun5(adcSampleTemp, (ADS869X_N_SAMPLE_COUNT - 4), 4);
		//---��������ĵ�ѹֵ
		ADS869X_SPI_CalcChannelPower(ADS869xx, adcChannelIndex,1);
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
UINT8_T ADS869X_SPI_CalibrationChannelErr(ADS869X_HandlerType* ADS869xx)
{
	UINT8_T i = 0;
	UINT8_T rstMode = ADS869xx->msgAutoSeqEn;
	for (i = 0; i < ADS869X_CHANNEL_MAX; i++)
	{
		if ((rstMode&0x01)==0)
		{
			if (i==0)
			{
				////---1�Ű����
				//ADS869xx->msgADCKP[i] = 1.013216;
				//ADS869xx->msgADCDelta[i] = 27130;

				//---2�Ű����
				ADS869xx->msgADCKP[i] = 0;//1.013216;
				ADS869xx->msgADCDelta[i] = 26430;
			}
			else
			{
				////---1�Ű����
				//ADS869xx->msgADCKP[i] = 1.0129;
				//ADS869xx->msgADCDelta[i] = 25870;

				//---2�Ű����
				ADS869xx->msgADCKP[i] = 0;//1.0129;
				ADS869xx->msgADCDelta[i] = 27070;
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
UINT8_T ADS869X_SPI_ConfigInit(ADS869X_HandlerType* ADS869xx)
{
	UINT8_T _return = OK_0;
	UINT8_T tempBuffer[3] = { 0 };
	UINT8_T i = 0;
	if (ADS869xx->msgInitRetryCount==0)
	{
		ADS869xx->msgInitRetryCount = 1;
	}

	//---ѭ����γ�ʼ���豸
	for (i=0;i< ADS869xx->msgInitRetryCount;i++)
	{
		//---��λоƬ
		_return = ADS869X_SPI_Reset(ADS869xx);
		//---У��
		if (_return == OK_0)
		{
			//---�豸��������
			_return = ADS869X_SPI_WriteFeature(ADS869xx, 0x28);
			//---У��
			if (_return == OK_0)
			{
				//---��ȡ�豸������
				_return = ADS869X_SPI_ReadFeature(ADS869xx, tempBuffer);
				//---У��
				if (_return == OK_0)
				{
					break;
				}
			}
		}
	}

	//---����ɨ�跽ʽ
	_return = ADS869X_SPI_WriteAUTOSEQEN(ADS869xx, 0xF0);
	//---��ȡ���õ�ֵ
	_return = ADS869X_SPI_ReadProgramReg(ADS869xx, ADS869X_PROG_REG_AUTO_SEQ_EN, tempBuffer);

	//---�ж�У��
	if (ADS869xx->msgAutoSeqEn != tempBuffer[1])
	{
		_return = ERROR_1;
		ADS869xx->msgDeviceReady = 1;
	}
	else
	{
		//---����ͨ��������
		ADS869X_SPI_WriteChannelRange(ADS869xx, ADS869X_PROG_REG_CH0_SET_RANGE, ADS869X_RANGE_0MV_5120MV);
		ADS869X_SPI_WriteChannelRange(ADS869xx, ADS869X_PROG_REG_CH1_SET_RANGE, ADS869X_RANGE_0MV_5120MV);
		ADS869X_SPI_WriteChannelRange(ADS869xx, ADS869X_PROG_REG_CH2_SET_RANGE, ADS869X_RANGE_0MV_5120MV);
		//---���ù���ģʽ
		ADS869X_SPI_AUTORST(ADS869xx);
	}
	ADS869X_SPI_CalibrationChannelErr(ADS869xx);
	return _return;
}