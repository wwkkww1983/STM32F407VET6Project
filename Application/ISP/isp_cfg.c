#include "isp_cfg.h"

//===ȫ�ֱ����Ķ���
ISP_HandlerType  g_ISPDevice0 = { 0 };
pISP_HandlerType pISPDevice0 = &g_ISPDevice0;

//===ͳһ���ͺ���
UINT8_T(*ISP_SEND_CMD)(ISP_HandlerType *, UINT8_T, UINT8_T, UINT8_T, UINT8_T);

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�Ӳ����ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_HW_Init(ISP_HandlerType *ISPx)
{
	//---ע����ǰ����������
	SPITask_DeInit(&(ISPx->msgSPI),1);
	
	//---Ӳ���˿ڵ�����---Ӳ��ʵ��
	SPITask_MHW_GPIO_Init(&(ISPx->msgSPI));

	//---Ӳ��SPI�ĳ�ʼ��
	LL_SPI_InitTypeDef SPI_InitStruct={0};

	//---SPI��ģʽ����
	SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
	SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;									//---����ģʽ
	SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;							//---8λ����
	
	//---ʱ�ӿ���ʱ�ļ���
	if(ISPx->msgSPI.msgCPOL==0)
	{
		SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;						//---CLK����ʱΪ�͵�ƽ (CLK������ֻ���ǵ͵�ƽ)
		GPIO_OUT_0(ISPx->msgSPI.msgSCK.msgGPIOPort, ISPx->msgSPI.msgSCK.msgGPIOBit);
	}
	else
	{
		SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_HIGH;					//---CLK����ʱΪ�ߵ�ƽ (CLK������ֻ���ǵ͵�ƽ)
	}
	
	//---���ݲ�����ʱ�ӱ���λ��
	if (ISPx->msgSPI.msgCPOL == 0)
	{
		SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
	}
	else
	{
		SPI_InitStruct.ClockPhase = LL_SPI_PHASE_2EDGE;
	}
	
	SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;										//---�������
	SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV256;					//---ϵͳʱ��256��Ƶ
	SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;									//---��λ��ǰ
	SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;				//---Ӳ��CRC��ʹ��
	SPI_InitStruct.CRCPoly = 7;
	SPITask_MHW_PollMode_Init(&(ISPx->msgSPI), SPI_InitStruct);
	ISPx->msgInit = 1;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ģ���ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_SW_Init(ISP_HandlerType *ISPx)
{
	SPITask_DeInit(&(ISPx->msgSPI),1);

	//---Ӳ���˿ڵ�����---���ʵ��
	SPITask_MSW_GPIO_Init(&(ISPx->msgSPI));

	//---ʱ�ӿ���ʱ�ļ���
	if (ISPx->msgSPI.msgCPOL == 0)
	{
		GPIO_OUT_0(ISPx->msgSPI.msgSCK.msgGPIOPort, ISPx->msgSPI.msgSCK.msgGPIOBit);
	}
	else
	{
		GPIO_OUT_1(ISPx->msgSPI.msgSCK.msgGPIOPort, ISPx->msgSPI.msgSCK.msgGPIOBit);
	}

	//---��Ƭѡ�ź�����ߵ�ƽ������˿ڶ�����͵�ƽ��Ĭ�ϵĳ�ʼ���Ǹߵ�ƽ����������Ҫ�Ķ�
	GPIO_OUT_0(ISPx->msgSPI.msgMOSI.msgGPIOPort, ISPx->msgSPI.msgMOSI.msgGPIOBit);
	GPIO_OUT_0(ISPx->msgSPI.msgMISO.msgGPIOPort, ISPx->msgSPI.msgMISO.msgGPIOBit);

	ISPx->msgInit = 1;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��豸0�ĳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_Device0_Init(ISP_HandlerType *ISPx)
{
	//---�趨���״̬Ϊ����ģʽ
	ISPx->msgState=0;
	//---�趨��ʼ��״̬
	ISPx->msgInit = 0;
	//---�趨Ӳ����ʱ��
	ISPx->msgSetClok = ISP_SCK_PRE_32;// ISP_SCK_PRE_64;//ISP_SCK_KHZ_32;//ISP_SCK_KHZ_64
	//---��ʼ��
	ISPx->msgDelayms = 0;
	//---��ʼ��
	ISPx->msgHideAddr = 0;
	//---���㷢�ͻ�����
	memset(ISPx->msgWriteByte, 0x00, 4);
	memset(ISPx->msgReadByte, 0x00, 4);
	//---��ƽת��ʹ�ܿ��ƶ�
#ifdef ISP_USE_lEVEL_SHIFT
	ISPx->msgOE.msgGPIOPort=GPIOD;
	ISPx->msgOE.msgGPIOBit = LL_GPIO_PIN_14;
#endif

	/**SPI2 GPIO Configuration
	PB12   ------> SPI2_NSS
	PB13   ------> SPI2_SCK
	PB14   ------> SPI2_MISO
	PB15   ------> SPI2_MOSI
	*/
	//---CS
	ISPx->msgSPI.msgCS.msgGPIOPort = GPIOB;
	ISPx->msgSPI.msgCS.msgGPIOBit = LL_GPIO_PIN_12;
	//---SCK
	ISPx->msgSPI.msgSCK.msgGPIOPort = GPIOB;
	ISPx->msgSPI.msgSCK.msgGPIOBit = LL_GPIO_PIN_13;
	//---MISO
	ISPx->msgSPI.msgMISO.msgGPIOPort = GPIOB;
	ISPx->msgSPI.msgMISO.msgGPIOBit = LL_GPIO_PIN_14;
	//---MOSI
	ISPx->msgSPI.msgMOSI.msgGPIOPort = GPIOB;
	ISPx->msgSPI.msgMOSI.msgGPIOBit = LL_GPIO_PIN_15;
	//---����ģʽ
#ifndef USE_MCU_STM32F1
	ISPx->msgSPI.msgGPIOAlternate = LL_GPIO_AF_5;
#endif
	//---SPI���
	ISPx->msgSPI.msgSPIx = SPI2;
#ifndef USE_MCU_STM32F1
	//---SPI��Э��
	ISPx->msgSPI.msgStandard = LL_SPI_PROTOCOL_MOTOROLA;
#endif	
	//---ʱ�ӿ���Ϊ�͵�ƽ
	ISPx->msgSPI.msgCPOL=0;
	//---���ݲ����ڵ�һ��ʱ�ӱ���
	ISPx->msgSPI.msgCPOH=0;	
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��豸1�ĳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_Device1_Init(ISP_HandlerType *ISPx)
{
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��豸2�ĳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_Device2_Init(ISP_HandlerType *ISPx)
{
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_Init(ISP_HandlerType *ISPx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	//---ʹ�õ�DHT11�Ķ˿�
	if ((ISPx != NULL) && (ISPx == ISP_TASK_ONE))
	{
		ISP_Device0_Init(ISPx);
	}
	else if ((ISPx != NULL) && (ISPx == ISP_TASK_TWO))
	{
		ISP_Device1_Init(ISPx);
	}
	else if ((ISPx != NULL) && (ISPx == ISP_TASK_THREE))
	{
		ISP_Device2_Init(ISPx);
	}
	else
	{
		return ERROR_1;
	}
	//---ע��ms����ʱ����
	if (pFuncDelayms!=NULL)
	{
		ISPx->msgFuncDelayms = pFuncDelayms;
	}
	else
	{
		ISPx->msgFuncDelayms = DelayTask_ms;
	}
	//---ע��us��ʱ����
	if (pFuncDelayus!=NULL)
	{
		ISPx->msgSPI.msgFuncDelayus = pFuncDelayus;
	}
	else
	{
		ISPx->msgSPI.msgFuncDelayus = DelayTask_us;
	}
	//---ע��δ���
	ISPx->msgSPI.msgFuncTimeTick = pFuncTimerTick;
	//---����OE�˿�
#ifdef ISP_USE_lEVEL_SHIFT
	if (ISPx->msgOE.msgGPIOPort != NULL)
	{
		//---ʹ��GPIO��ʱ��
		GPIOTask_Clock(ISPx->msgOE.msgGPIOPort, 1);
		//---GPIO�Ľṹ��
		LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
		GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
		GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO���ٶ�---�����豸
		GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;			//---���ģʽ---�������
		GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
#ifndef USE_MCU_STM32F1
		GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
#endif
	//---ISP_OE_BIT�ĳ�ʼ��
		GPIO_InitStruct.Pin = ISPx->msgOE.msgGPIOBit;
		LL_GPIO_Init(ISPx->msgOE.msgGPIOPort, &GPIO_InitStruct);
		GPIO_OUT_1(ISPx->msgOE.msgGPIOPort, ISPx->msgOE.msgGPIOBit);
	}
#endif
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ٳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_DeInit(ISP_HandlerType *ISPx)
{
	SPITask_DeInit(&(ISPx->msgSPI),1);
	ISPx->msgInit = 0;
#ifdef ISP_USE_lEVEL_SHIFT
	GPIO_OUT_1(ISPx->msgOE.msgGPIOPort, ISPx->msgOE.msgGPIOBit);
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ٳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_AutoInit(ISP_HandlerType* ISPx)
{
	if (ISPx->msgSPI.msgModelIsHW != 0)
	{
		ISP_HW_Init(ISPx);
#ifdef USE_MCU_STM32
		//---���Ʊ�̵�����ٶȣ�С��1MHz
		if (ISPx->msgSPI.msgClockSpeed > ISP_SCK_PRE_32)
		{
			ISPx->msgSPI.msgClockSpeed = ISP_SCK_PRE_32;
		}
#endif
		//---����SPI��Ӳ��ʱ��
		SPITask_MHW_SetClock(&(ISPx->msgSPI), ISPx->msgSPI.msgClockSpeed);
		//---���ݷ��������
		ISP_SEND_CMD = ISP_HW_SendCmd;
	}
	else
	{
		ISP_SW_Init(ISPx);
		//---�������ģ�������
		SPITask_MSW_SetClock(&(ISPx->msgSPI), ISPx->msgSPI.msgPluseWidth);
		//---���ݷ��������
		ISP_SEND_CMD = ISP_SW_SendCmd;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��Զ�ע��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_AutoDeInit(ISP_HandlerType* ISPx)
{
	//---ע����ǰ����������
	return	ISP_DeInit(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ñ��ʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_SetClock(ISP_HandlerType *ISPx, UINT8_T clok)
{
	switch (clok)
	{
		case ISP_SCK_KHZ_0_5:
			ISPx->msgSPI.msgModelIsHW = 0;
			ISPx->msgSPI.msgPluseWidth = 1000;
			break;
		case ISP_SCK_KHZ_1:
			ISPx->msgSPI.msgModelIsHW = 0;
			ISPx->msgSPI.msgPluseWidth = 500;
			break;
		case ISP_SCK_KHZ_2:
			ISPx->msgSPI.msgModelIsHW = 0;
			ISPx->msgSPI.msgPluseWidth = 250;
			break;
		case ISP_SCK_KHZ_4:
			ISPx->msgSPI.msgModelIsHW = 0;
			ISPx->msgSPI.msgPluseWidth = 125;
			break;
		case ISP_SCK_KHZ_8:
			ISPx->msgSPI.msgModelIsHW = 0;
			ISPx->msgSPI.msgPluseWidth = 64;
			break;
		case ISP_SCK_KHZ_16:
			ISPx->msgSPI.msgModelIsHW = 0;
			ISPx->msgSPI.msgPluseWidth = 32;
			break;
		case ISP_SCK_KHZ_32:
			ISPx->msgSPI.msgModelIsHW = 0;
			ISPx->msgSPI.msgPluseWidth = 16;
			break;
		case ISP_SCK_KHZ_64:
			ISPx->msgSPI.msgModelIsHW = 0;
			ISPx->msgSPI.msgPluseWidth = 8;
			break;
		case ISP_SCK_KHZ_128	:
			ISPx->msgSPI.msgModelIsHW = 0;
			ISPx->msgSPI.msgPluseWidth = 4;
			break;
		case ISP_SCK_KHZ_256	:
			ISPx->msgSPI.msgModelIsHW = 0;
			ISPx->msgSPI.msgPluseWidth = 2;
			break;
		case ISP_SCK_PRE_256:
			ISPx->msgSPI.msgModelIsHW = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV256;
			break;
		case ISP_SCK_PRE_128:
			ISPx->msgSPI.msgModelIsHW = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV128;
			break;
		case ISP_SCK_PRE_64:
			ISPx->msgSPI.msgModelIsHW = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV64;
			break;
		case ISP_SCK_PRE_32:
			ISPx->msgSPI.msgModelIsHW = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV32;
			break;
		case ISP_SCK_PRE_16:
		#ifdef USE_MCU_STM32
			ISPx->msgSPI.msgModelIsHW = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV16;
		#endif
			break;
		case ISP_SCK_PRE_8:
			ISPx->msgSPI.msgModelIsHW = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV8;
			break;
		case ISP_SCK_PRE_4:
			ISPx->msgSPI.msgModelIsHW = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV4;
			break;
		case ISP_SCK_PRE_2:
			ISPx->msgSPI.msgModelIsHW = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV2;
			break;
		default:
			ISPx->msgSPI.msgModelIsHW = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV256;
			break;
	}
	if (ISPx->msgSPI.msgModelIsHW == 1)
	{
		//---��һ����Ҫ��ʼ���˿ڣ������ģ�ⷽʽ�л���Ӳ����ʽ��Ҳ��Ҫ���³�ʼ��һ�¶˿�
		if ((ISPx->msgInit == 0) || (ISP_SEND_CMD == ISP_SW_SendCmd))
		{
			ISP_HW_Init(ISPx);
		}
	#ifdef USE_MCU_STM32
		//---���Ʊ�̵�����ٶȣ�С��1MHz��ע����������������ʹ�ã�һ��������ISP��ʱ�ӵȼ���һ��������Ӳ��SPI��ʱ��
		if (ISPx->msgSetClok > ISP_SCK_PRE_32)
		{
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV32;
		}
	#endif
		//---����SPI��Ӳ��ʱ��
		SPITask_MHW_SetClock(&(ISPx->msgSPI), ISPx->msgSPI.msgClockSpeed);
		//---���ݷ��������
		ISP_SEND_CMD = ISP_HW_SendCmd;
	}
	else
	{
		//---��һ����Ҫ��ʼ���˿ڣ������Ӳ����ʽ�л���ģ�ⷽʽ��Ҳ��Ҫ���³�ʼ��һ�¶˿�
		if ((ISPx->msgInit == 0) || (ISP_SEND_CMD == ISP_HW_SendCmd))
		{
			ISP_SW_Init(ISPx);
		}
		//---�������ģ�������
		SPITask_MSW_SetClock(&(ISPx->msgSPI), ISPx->msgSPI.msgPluseWidth);
		//---���ݷ��������
		ISP_SEND_CMD = ISP_SW_SendCmd;
	}
#ifdef ISP_USE_lEVEL_SHIFT
	GPIO_OUT_0(ISPx->msgOE.msgGPIOPort, ISPx->msgOE.msgGPIOBit);
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_SW_SendCmd(ISP_HandlerType *ISPx, UINT8_T val1, UINT8_T Val2, UINT8_T val3, UINT8_T val4)
{
	//---���㷢�ͻ�����
	memset(ISPx->msgWriteByte, 0x00, 4);
	memset(ISPx->msgReadByte, 0x00, 4);
	//---��䷢�ͻ�����
	ISPx->msgWriteByte[0] = val1;
	ISPx->msgWriteByte[1] = Val2;
	ISPx->msgWriteByte[2] = val3;
	ISPx->msgWriteByte[3] = val4;
	//---���ݷ��ͣ���λ��ǰ
	return SPITask_MSW_WriteAndReadDataMSB(&(ISPx->msgSPI), ISPx->msgWriteByte, ISPx->msgReadByte, ISP_COMM_MAX_SIZE);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�Ӳ����������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_HW_SendCmd(ISP_HandlerType *ISPx, UINT8_T val1, UINT8_T Val2, UINT8_T val3, UINT8_T val4)
{
	//---���㷢�ͻ�����
	memset(ISPx->msgWriteByte, 0x00, 4);
	memset(ISPx->msgReadByte, 0x00, 4);
	//---��䷢�ͻ�����
	ISPx->msgWriteByte[0] = val1;
	ISPx->msgWriteByte[1] = Val2;
	ISPx->msgWriteByte[2] = val3;
	ISPx->msgWriteByte[3] = val4;
	//---���ݷ���
	return SPITask_MHW_PollMode_WriteAndReadData(&(ISPx->msgSPI), ISPx->msgWriteByte, ISPx->msgReadByte, ISP_COMM_MAX_SIZE);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�׼��������ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_PreEnterProg(ISP_HandlerType *ISPx)
{
	//---���ö˿�CS�˿�Ϊ���ģʽ
	GPIO_SET_WRITE(ISPx->msgSPI.msgCS.msgGPIOPort, ISPx->msgSPI.msgCS.msgGPIOBit);
	//---��������ʱ����
	GPIO_OUT_0(ISPx->msgSPI.msgSCK.msgGPIOPort, ISPx->msgSPI.msgSCK.msgGPIOBit);
	GPIO_OUT_0(ISPx->msgSPI.msgCS.msgGPIOPort, ISPx->msgSPI.msgCS.msgGPIOBit);
	//---�򿪵�Դ
	//POWER_DUT_ON;
	//---��������ʱ����
	GPIO_OUT_0(ISPx->msgSPI.msgSCK.msgGPIOPort, ISPx->msgSPI.msgSCK.msgGPIOBit);
	GPIO_OUT_0(ISPx->msgSPI.msgCS.msgGPIOPort, ISPx->msgSPI.msgCS.msgGPIOBit);
	ISPx->msgFuncDelayms(1);
	GPIO_OUT_1(ISPx->msgSPI.msgCS.msgGPIOPort, ISPx->msgSPI.msgCS.msgGPIOBit);
	ISPx->msgFuncDelayms(1);
	GPIO_OUT_0(ISPx->msgSPI.msgCS.msgGPIOPort, ISPx->msgSPI.msgCS.msgGPIOBit);
	ISPx->msgFuncDelayms(1);
	//---���64K������
	ISPx->msgHideAddr = 0xFF;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������ģʽ
//////�������: isPollReady��0---��ʱģʽ��1---��ѯ׼�����ź�
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_EnterProg(ISP_HandlerType *ISPx,UINT8_T isPollReady)
{
	UINT8_T count = ISP_SCK_AUTO_MAX_COUNT;
	//---����ʱ��
	ISP_SetClock(ISPx, ISPx->msgSetClok);
	//---���ģʽ׼��
	ISP_PreEnterProg(ISPx);
	//---�Զ���ȡ���ʵ��ٶ�
	while (count--)
	{
		//---���ͱ������
		ISP_SEND_CMD(ISPx, 0xAC, 0x53, 0x00, 0x00);
		//---����Ƿ����ɹ�
		if (ISPx->msgReadByte[2] == 0x53)
		{
			//---���״̬Ϊ���ģʽ
			ISPx->msgState = 1;
			//---���ò�ѯ׼�����źŵı�־
			ISPx->msgIsPollReady=isPollReady;
			return OK_0;
		}
		//---���ٴ���
		if (ISPx->msgSetClok >= ISP_SCK_KHZ_2)
		{
			ISPx->msgSetClok = ISPx->msgSetClok;
		}
		//---����ʱ��
		ISP_SetClock(ISPx, ISPx->msgSetClok);
		//---��λʱ���ߺ�Ƭѡ��
		//GPIO_OUT_1(ISPx->msgSPI.msgSCK.msgGPIOPort, ISPx->msgSPI.msgSCK.msgGPIOBit);
		GPIO_OUT_1(ISPx->msgSPI.msgCS.msgGPIOPort, ISPx->msgSPI.msgCS.msgGPIOBit);
		ISPx->msgFuncDelayms(1);
		//---����ʱ���ߺ�Ƭѡ��
		//GPIO_OUT_0(ISPx->msgSPI.msgSCK.msgGPIOPort, ISPx->msgSPI.msgSCK.msgGPIOBit);
		GPIO_OUT_0(ISPx->msgSPI.msgCS.msgGPIOPort, ISPx->msgSPI.msgCS.msgGPIOBit);
		ISPx->msgFuncDelayms(1);
	}
#ifdef ISP_USE_lEVEL_SHIFT
	GPIO_OUT_1(ISPx->msgOE.msgGPIOPort, ISPx->msgOE.msgGPIOBit);
#endif
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��˳����ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ExitProg(ISP_HandlerType *ISPx)
{
	ISP_DeInit(ISPx);
	//---�ָ�ʱ�ӵ��ٶ�
	ISPx->msgSetClok = ISP_SCK_MAX_CLOCK;
	//---���64K������
	ISPx->msgHideAddr = 0xFF;
	//---���״̬Ϊ����ģʽ
	ISPx->msgState=0;
	//---�Ƴ�ע��ļ�غ���
	ISP_RemoveWatch(ISPx);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���̼������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void ISP_WatchTask(ISP_HandlerType* ISPx)
{
	UINT32_T nowTime = 0;
	UINT32_T cnt = 0;
	if (ISPx->msgState!=0)
	{
		//---��ȡ��ǰʱ�����
		nowTime= ISPx->msgSPI.msgFuncTimeTick();
		//---����ʱ����
		if (ISPx->msgRecordTime > nowTime)
		{
			cnt = (0xFFFFFFFF - nowTime + ISPx->msgRecordTime);
		}
		else
		{
			cnt = nowTime - ISPx->msgRecordTime;
		}
		if (cnt > ISP_STATE_TIME_OUT_MS)
		{
			ISP_ExitProg(ISPx);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����豸1�ļ�غ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void ISP_AddWatchDevice0(void)
{
	ISP_WatchTask(ISP_TASK_ONE);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����豸2�ļ�غ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void ISP_AddWatchDevice1(void)
{
	ISP_WatchTask(ISP_TASK_TWO);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����豸3�ļ�غ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void ISP_AddWatchDevice2(void)
{
	ISP_WatchTask(ISP_TASK_THREE);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���Ӽ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_AddWatch(ISP_HandlerType* ISPx)
{
	//---ʹ�õ�ISP�Ķ˿�
	if ((ISPx != NULL) && (ISPx == ISP_TASK_ONE))
	{
		SysTickTask_CreateTickTask(ISP_AddWatchDevice0);
	}
	else if ((ISPx != NULL) && (ISPx == ISP_TASK_TWO))
	{
		SysTickTask_CreateTickTask(ISP_AddWatchDevice1);
	}
	else if ((ISPx != NULL) && (ISPx == ISP_TASK_THREE))
	{
		SysTickTask_CreateTickTask(ISP_AddWatchDevice2);
	}
	else
	{
		return ERROR_1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��Ƴ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_RemoveWatch(ISP_HandlerType* ISPx)
{
	//---ʹ�õ�ISP�Ķ˿�
	if ((ISPx != NULL) && (ISPx == ISP_TASK_ONE))
	{
		SysTick_DeleteTickTask(ISP_AddWatchDevice0);
	}
	else if ((ISPx != NULL) && (ISPx == ISP_TASK_TWO))
	{
		SysTick_DeleteTickTask(ISP_AddWatchDevice1);
	}
	else if ((ISPx != NULL) && (ISPx == ISP_TASK_THREE))
	{
		SysTick_DeleteTickTask(ISP_AddWatchDevice2);
	}
	else
	{
		return ERROR_1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ˢ�¼��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_RefreshWatch(ISP_HandlerType* ISPx)
{
	ISPx->msgRecordTime= ISPx->msgSPI.msgFuncTimeTick();
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ׼���ñ�־λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ReadReady(ISP_HandlerType *ISPx)
{
	UINT8_T _return = 0;
	//---��ȡʱ���ǩ
	UINT32_T nowTime = 0;
	UINT32_T oldTime = 0;
	UINT64_T cnt = 0;
	if (ISPx->msgSPI.msgFuncTimeTick != NULL)
	{
		//nowTime = ISPx->msgSPI.msgFuncTick();
		oldTime = ISPx->msgSPI.msgFuncTimeTick();
	}
	//---��ѯæ��־λ
	while (1)
	{
		//---���Ͷ�ȡæ��־������
		_return = ISP_SEND_CMD(ISPx, 0xF0, 0x00, 0x00, 0x00);
		//---����Ƿ��ȡ��æ��־
		if (_return)
		{
			break;
		}
		else
		{
			if ((ISPx->msgReadByte[3] & 0x01) == 0x00)
			{
				_return = OK_0;
				break;
			}
			else
			{
				if (ISPx->msgSPI.msgFuncTimeTick != NULL)
				{
					//---��ǰʱ��
					nowTime = ISPx->msgSPI.msgFuncTimeTick();
					//---�жϵδ�ʱ�Ƿ����������
					if (nowTime < oldTime)
					{
						cnt = (0xFFFFFFFF - oldTime + nowTime);
					}
					else
					{
						cnt = nowTime - oldTime;
					}
					//---�ж��Ƿ�ʱ
					if (cnt > 100)
					{
						//---���ͷ�����ʱ����
						_return = ERROR_2;
						break;
					}
				}
				else
				{
					nowTime++;
					if (nowTime > 100000)
					{
						//---���ͷ�����ʱ����
						_return = ERROR_3;
						break;
					}
				}
			}
		}
		WDT_RESET();
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������豸
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_EraseChip(ISP_HandlerType *ISPx)
{
	UINT8_T _return = 0;
	//---���Ͳ�������
	_return = ISP_SEND_CMD(ISPx, 0xAC, 0x80, 0x00, 0x00);
	if (_return == 0)
	{
		//---�����ѯ��ʽ
		if (ISPx->msgIsPollReady!=0)
		{
			_return = ISP_ReadReady(ISPx);
			_return+=0x80;
		}
		else
		{
			//---����֮��ĵȴ���ʱ
			ISPx->msgFuncDelayms(10 + ISPx->msgDelayms);
		}
		
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�豸ID
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ReadChipID(ISP_HandlerType *ISPx, UINT8_T *pVal)
{
	UINT8_T _return = 0;
	UINT8_T i = 0;
	for (i = 0; i < 3; i++)
	{
		_return = ISP_SEND_CMD(ISPx, 0x30, 0x00, i, 0x0);
		if (_return != 0)
		{
			_return = (i + 2);
			break;
		}
		pVal[i] = ISPx->msgReadByte[3];
	}
	return _return;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ��׼��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ReadChipCalibration(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T length)
{
	UINT8_T _return = 0;
	UINT8_T i = 0;
	for (i = 0; i < length; i++)
	{
		_return = ISP_SEND_CMD(ISPx, 0x38, 0x00, i, 0x00);
		if (_return != 0)
		{
			_return = (i + 2);
			break;
		}
		pVal[i] = ISPx->msgReadByte[3];
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ��˿λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ReadChipFuse(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse)
{
	UINT8_T _return = 0;
	//---��ȡ��˿λ��λ
	_return = ISP_SEND_CMD(ISPx, 0x50, 0x00, 0x00, 0x00);
	if (_return != 0x00)
	{
		return ERROR_2;
	}
	//---�����λֵ
	*(pVal++) = ISPx->msgReadByte[3];
	//---��ȡ��˿λ��λ
	_return = ISP_SEND_CMD(ISPx, 0x58, 0x08, 0x00, 0x00);
	if (_return != 0x00)
	{
		return ERROR_3;
	}
	//---�����λֵ
	*(pVal++) = ISPx->msgReadByte[3];
	//---��ȡ��˿λ��չλ
	if (isNeedExternFuse != 0x00)
	{
		//---��ȡ��˿����չλֵ
		_return = ISP_SEND_CMD(ISPx, 0x50, 0x08, 0x00, 0x00);
		//---������չλֵ
		*(pVal) = ISPx->msgReadByte[3];
	}
	else
	{
		*pVal = 0xFF;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ����λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ReadChipLock(ISP_HandlerType *ISPx, UINT8_T *pVal)
{
	//---��ȡ����λ
	UINT8_T _return = ISP_SEND_CMD(ISPx, 0x58, 0x00, 0x00, 0x00);
	*(pVal) = ISPx->msgReadByte[3];
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡROMҳ��Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ReadChipRom(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T addr, UINT16_T length)
{
	UINT8_T _return = 0;
	UINT8_T i = 0;
	//---�ж����ݳ����Ƿ���ż��
	if ((length & 0x01) != 0)
	{
		return ERROR_2;
	}
	//---����λ���㵱����2����
	length >>= 1;
	for (i = 0; i < length; i++)
	{
		//---ROMҳ��λ����
		_return = ISP_SEND_CMD(ISPx, 0x30, 0x00, (addr + i), 0x00);
		if (_return != 0)
		{
			return ERROR_3;
		}
		else
		{
			*(pVal++) = ISPx->msgReadByte[3];
		}
		//---ROMҳ���ֽ�����
		_return = ISP_SEND_CMD(ISPx, 0x38, 0x00, (addr + i), 0x00);
		if (_return != 0)
		{
			return 4;
		}
		else
		{
			*(pVal++) = ISPx->msgReadByte[3];
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������˿λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_WriteChipFuse(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse)
{
	UINT8_T _return = 0;
	//---д����˿λ��λ
	_return = ISP_SEND_CMD(ISPx, 0xAC, 0xA0, 0x00, pVal[0]);
	if (_return != 0x00)
	{
		return ERROR_2;
	}
	//---�����ѯ��ʽ
	if (ISPx->msgIsPollReady != 0)
	{
		_return = ISP_ReadReady(ISPx);
		_return += 0x80;
	}
	else
	{
		//---д��֮����ʱ�ȴ�
		ISPx->msgFuncDelayms(6 + ISPx->msgDelayms);
	}
	//---д����˿λ��λ
	_return = ISP_SEND_CMD(ISPx, 0xAC, 0xA8, 0x00, pVal[1]);
	if (_return != 0x00)
	{
		return ERROR_3;
	}
	//---�����ѯ��ʽ
	if (ISPx->msgIsPollReady != 0)
	{
		_return = ISP_ReadReady(ISPx);
		_return += 0x80;
	}
	else
	{
		//---д��֮����ʱ�ȴ�
		ISPx->msgFuncDelayms(6 + ISPx->msgDelayms);
	}
	//---д����˿λ��չλ
	if (isNeedExternFuse != 0x00)
	{
		//---д����չλ
		_return = ISP_SEND_CMD(ISPx, 0xAC, 0xA4, 0x00, pVal[2]);
		//---�ж�д���Ƿ�ɹ�
		if (_return == OK_0)
		{
			//---�����ѯ��ʽ
			if (ISPx->msgIsPollReady != 0)
			{
				_return = ISP_ReadReady(ISPx);
				_return += 0x80;
			}
			else
			{
				//---д��֮����ʱ�ȴ�
				ISPx->msgFuncDelayms(6 + ISPx->msgDelayms);
			}
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���̼���λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_WriteChipLock(ISP_HandlerType *ISPx, UINT8_T *pVal)
{
	//---д�����λ
	UINT8_T _return = ISP_SEND_CMD(ISPx, 0xAC, 0xE0, 0x00, pVal[0]);
	//---�ж�д���Ƿ�ɹ�
	if (_return == OK_0)
	{
		//---�����ѯ��ʽ
		if (ISPx->msgIsPollReady != 0)
		{
			_return = ISP_ReadReady(ISPx);
			_return += 0x80;
		}
		else
		{
			//---д��֮����ʱ�ȴ�
			ISPx->msgFuncDelayms(6 + ISPx->msgDelayms);
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡEEPROM
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ReadChipEepromAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	for (i = 0; i < length; i++)
	{
		_return = ISP_SEND_CMD(ISPx, 0xA0, highAddr, lowAddr, 0x00);
		if (_return != OK_0)
		{
			break;
		}
		//---�����ȡ������
		*(pVal++) = ISPx->msgReadByte[3];
		//---��ַƫ��
		lowAddr++;
		if (lowAddr == 0x00)
		{
			highAddr++;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡEEPROM
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ReadChipEepromLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return ISP_ReadChipEepromAddr(ISPx, pVal, (UINT8_T)(addr >> 8), (UINT8_T)(addr & 0xFF), length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����EEPROM
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_WriteChipEepromAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	for (i = 0; i < length; i++)
	{
		_return = ISP_SEND_CMD(ISPx, 0xC0, highAddr, lowAddr, pVal[i]);
		if (_return != OK_0)
		{
			break;
		}
		//---�����ѯ��ʽ
		if (ISPx->msgIsPollReady != 0)
		{
			_return = ISP_ReadReady(ISPx);
			_return += 0x80;
		}
		else
		{
			//---д��֮����ʱ�ȴ�
			ISPx->msgFuncDelayms(5 + ISPx->msgDelayms);
		}
		//---��ַƫ��
		lowAddr++;
		if (lowAddr == 0x00)
		{
			highAddr++;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����EEPROM
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_WriteChipEepromLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return ISP_WriteChipEepromAddr(ISPx, pVal, (UINT8_T)(addr >> 8), (UINT8_T)(addr & 0xFF), length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ձ��EEPROM
//////�������:
//////�������:
//////˵		�������д��������ǿ����ݣ���ô������д��
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_WriteChipEepromAddrWithJumpEmpty(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	for (i = 0; i < length; i++)
	{
		if (pVal[i] != 0xFF)
		{
			_return = ISP_SEND_CMD(ISPx, 0xC0, highAddr, lowAddr, pVal[i]);
			if (_return != OK_0)
			{
				break;
			}
			//---�����ѯ��ʽ
			if (ISPx->msgIsPollReady != 0)
			{
				_return = ISP_ReadReady(ISPx);
				_return += 0x80;
			}
			else
			{
				//---д��֮����ʱ�ȴ�
				ISPx->msgFuncDelayms(5 + ISPx->msgDelayms);
			}
		}
		//---��ַƫ��
		lowAddr++;
		if (lowAddr == 0x00)
		{
			highAddr++;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ձ��EEPROM
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_WriteChipEepromLongAddrWithJumpEmpty(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return ISP_WriteChipEepromAddrWithJumpEmpty(ISPx, pVal, (UINT8_T)(addr >> 8), (UINT8_T)(addr & 0xFF), length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������չλ��ַ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_UpdateExternAddr(ISP_HandlerType *ISPx, UINT8_T addr)
{
	UINT8_T _return = OK_0;
	if (ISPx->msgHideAddr != addr)
	{
		ISPx->msgHideAddr = addr;
		_return = ISP_SEND_CMD(ISPx, 0x4D, 0x00, addr, 0x00);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������չλ��ַ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_UpdateExternLongAddr(ISP_HandlerType *ISPx, UINT32_T addr)
{
	return ISP_UpdateExternAddr(ISPx, (UINT8_T)(addr >> 16));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ַ��ȡFlash����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ReadChipFlashAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	//---�ж����ݳ����Ƿ�Ϊż��
	if ((length & 0x01) != 0)
	{
		return ERROR_2;
	}
	//---����λ���㵱����2����
	length >>= 1;
	//---������չλ
	_return = ISP_UpdateExternAddr(ISPx, externAddr);
	if (_return != OK_0)
	{
		return ERROR_3;
	}
	for (i = 0; i < length; i++)
	{
		//---��ȡ��λ����
		_return = ISP_SEND_CMD(ISPx, 0x20, highAddr, lowAddr, 0x00);
		if (_return != OK_0)
		{
			return ERROR_4;
		}
		else
		{
			*(pVal++) = ISPx->msgReadByte[3];
		}
		//---��ȡ��λ����
		_return = ISP_SEND_CMD(ISPx, 0x28, highAddr, lowAddr, 0x00);
		if (_return != 0x00)
		{
			return ERROR_5;
		}
		else
		{
			*(pVal++) = ISPx->msgReadByte[3];
		}
		lowAddr++;
		if (lowAddr == 0x00)
		{
			highAddr++;
			if (highAddr == 0x00)
			{
				externAddr++;

				//---������չλ
				_return = ISP_UpdateExternAddr(ISPx, externAddr);
				if (_return != 0x00)
				{
					return ERROR_6;
				}
			}
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ַ��ȡFlash����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ReadChipFlashLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT32_T addr, UINT16_T length)
{
	return  ISP_ReadChipFlashAddr(ISPx, pVal, (UINT8_T)(addr >> 16), (UINT8_T)(addr >> 8), (UINT8_T)(addr), length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����Flash������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_UpdateChipFlashBuffer(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T index, UINT16_T length)
{
	UINT8_T _return = 0;
	UINT8_T i = 0;
	//---�ж����ݳ����Ƿ�Ϊż��
	if ((length & 0x01) != 0x00)
	{
		return ERROR_2;
	}
	//---����λ���㵱����2����
	length >>= 1;
	for (i = 0; i < length; i++)
	{
		//---���µ�λ��ַ�Ļ�����
		_return = ISP_SEND_CMD(ISPx, 0x40, 0x00, (index + i), *(pVal++));
		if (_return != 0x00)
		{
			return ERROR_3;
		}
		//---���¸�λ��ַ�Ļ�����
		_return = ISP_SEND_CMD(ISPx, 0x48, 0x00, (index + i), *(pVal++));
		if (_return != 0x00)
		{
			return ERROR_4;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������ݵ�ָ��ҳ��ַ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_UpdateChipFlashAddr(ISP_HandlerType *ISPx, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr)
{
	UINT8_T _return = ISP_UpdateExternAddr(ISPx, externAddr);
	if (_return == OK_0)
	{
		_return = ISP_SEND_CMD(ISPx, 0x4C, highAddr, lowAddr, 0x00);
		if (_return == OK_0)
		{
			//---�����ѯ��ʽ
			if (ISPx->msgIsPollReady != 0)
			{
				_return = ISP_ReadReady(ISPx);
				_return += 0x80;
			}
			else
			{
				//---д��֮����ʱ�ȴ�
				ISPx->msgFuncDelayms(5 + ISPx->msgDelayms);
			}
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������ݵ�ָ��ҳ��ַ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_UpdateChipFlashLongAddr(ISP_HandlerType *ISPx, UINT32_T addr)
{
	return ISP_UpdateChipFlashAddr(ISPx, (UINT8_T)(addr >> 16), (UINT8_T)(addr >> 8), (UINT8_T)(addr));
}
